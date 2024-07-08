#include "loggerwidget.h"
#include "DMMM.h"
LoggerWidget::LoggerWidget(QWidget *parent) : QWidget(parent)
{
    widgetInit();
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
}

void LoggerWidget::widgetInit()
{
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("日志管理"));
        w_title->setMaximumHeight(40);
    }

    if(this->tableWidget == nullptr){
        this->tableWidget = new QTabWidget();
        this->tableWidget->setObjectName("SystemTabWidget");
    }

    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }

    if(this->systemLogWidget == nullptr){
        this->systemLogWidget = new SystemLogWidget();
    }
    if(this->systemDataWidget == nullptr){
        this->systemDataWidget = new SystemLogDataWidget();
    }
    if(this->planeLogDownWidget == nullptr){
        this->planeLogDownWidget = new PlaneLogDownLoadWidget();
    }
    if(this->loggerReplayWidget == nullptr){
        this->loggerReplayWidget = new ReplayWidget();
    }

    this->tableWidget->addTab(this->planeLogDownWidget ,QStringLiteral("机载日志下载"));
    this->tableWidget->addTab(this->systemLogWidget ,QStringLiteral("系统运行日志"));
//    this->addTab(this->systemDataWidget ,QStringLiteral("系统运行数据"));
//    this->addTab(this->loggerReplayWidget ,QStringLiteral("日志回放"));

    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addWidget(this->tableWidget,1,0,15,1);
    this->mainLayout->setMargin(0);
    this->mainLayout->setSpacing(0);
    this->setLayout(this->mainLayout);
    this->setObjectName("loggerWidget");
    this->resize(QSize(1080,700));
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();});
}







LogFileCerializeTask::LogFileCerializeTask(int cnt) : signalCount(cnt)
{
    this->readFinish = false;

}

void LogFileCerializeTask::run()
{
    while(this->fileData.count() != 0 || this->readFinish != true){
        if(this->fileData.count() > 0){
            QString str = this->fileData.dequeue();
            QStringList list = str.split("-: ");
            LogInfo info;
            if(list.count() > 0){
                QString headStr = QString(list.at(0)).trimmed();                //去掉字符串前后空格
                info.logName = headStr.mid(headStr.lastIndexOf(" "));
                headStr = headStr.mid(0,headStr.lastIndexOf("[")).trimmed();
                info.logTime = QDateTime::fromString(headStr,"yyyy-MM-dd hh:mm:ss.zzz");
                if(list.count() > 1){
                    info.text = list.at(1);
                }
            }
             this->cerializeData.enqueue(info);

            if(this->cerializeData.count() > signalCount){

                QQueue<LogInfo> resultsData;
                for(int i = 0; i < signalCount; i++){
                    resultsData.enqueue(cerializeData.dequeue());
                }
                emit resultsCerializeDataSignal(resultsData);
            }
        }else{
            QThread::msleep(1);
        }
    }

    emit cerializeFinishSignal();
}

void LogFileCerializeTask::addCerializeData(QQueue<QString> _fileData)
{
    for(int i = 0; i < _fileData.count(); i++){
        this->fileData.enqueue(_fileData.dequeue());
    }
}

void LogFileCerializeTask::fileReadFinishSlot()
{
    this->readFinish = true;
}








InfoViewModel::InfoViewModel()
{

}

QVariant InfoViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        if(role == Qt::DisplayRole){
            QHash<int, QByteArray> roles = headerNames();
            return QVariant(roles[section + Qt::UserRole + 1]);
        }else {
            return QVariant();
        }
    }
    return QVariant();
}

QModelIndex InfoViewModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex InfoViewModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int InfoViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return logMap.count();
}

int InfoViewModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant InfoViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    int row = index.row();
    int column = index.column();
    if(row < this->logMap.count() && row >= 0 && column < this->columnCount() && column >= 0){
        if(this->logMap.find(row) == this->logMap.end()){
            return QVariant();
        }
        LogInfo info = this->logMap.find(row).value();
        switch(role){
            case (Qt::TextAlignmentRole):
                switch (column + Qt::UserRole + 1) {
                case LogInfoRoles::LogTime:
                case LogInfoRoles::LogType:
                case LogInfoRoles::LogName:
                    return Qt::AlignCenter;
                case LogInfoRoles::LogText:
                    return Qt::AlignLeft;
                default:
                    return Qt::AlignCenter;
                }

            case (Qt::DisplayRole):{
                switch (column + Qt::UserRole + 1) {
                case LogInfoRoles::LogTime:{
                    return info.logTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
                }case LogInfoRoles::LogType:{
                    return QString("info");
                }case LogInfoRoles::LogName:{
                    return info.logName;
                }case LogInfoRoles::LogText:{
                    return info.text;
                }
                break;
            default:
                break;
            }
            }case (Qt::TextColorRole):{
                return QColor(0,0,0);
            }
            default:
                return QVariant();
        }

    }
    return QVariant();
}

QHash<int, QByteArray> InfoViewModel::roleNames() const
{
    QHash<int, QByteArray> roleName;
    roleName[LogTime] = "LogTime";
    roleName[LogType] = "LogType";
    roleName[LogName] = "LogName";
    roleName[LogText] = "LogText";
    return roleName;
}

QHash<int, QByteArray> InfoViewModel::headerNames() const
{
    QHash<int, QByteArray> headerName;
    headerName[LogTime] = QStringLiteral("时间").toUtf8();
    headerName[LogType] = QStringLiteral("类别").toUtf8();
    headerName[LogName] = QStringLiteral("来源").toUtf8();
    headerName[LogText] = QStringLiteral("详细").toUtf8();
    return headerName;
}

void InfoViewModel::changedLogFile(QString filePath)
{
    Q_UNUSED(filePath)
    this->beginResetModel();
    this->logMap.clear();
    this->endResetModel();
}

void InfoViewModel::addLogMap(QMap<int, LogInfo> map)
{
    this->beginResetModel();
    QMap<int, LogInfo>::Iterator iter = map.begin();
    while(iter != map.end()){
        this->logMap.insert(this->logMap.count(),iter.value());
        iter ++;
    }

    this->endResetModel();
}

void InfoViewModel::addLogMapForQueue(QQueue<LogInfo> map)
{
    qDebug()<<"void InfoViewModel::addLogMapForQueue(QQueue<LogInfo> map)";
    this->beginResetModel();
    for(int i = 0; i < map.count(); i++){
        this->logMap.insert(this->logMap.count(),map.dequeue());
    }
    this->endResetModel();
}





SystemLogWidget::SystemLogWidget()
{
    widgetInit();
}

void SystemLogWidget::widgetInit()
{
    if(this->fileView == nullptr){
        this->fileView = new QTreeView();
        this->fileView->setObjectName("widgetTreeView");
//        this->fileView->setMaximumWidth(200);
    }

    if(this->infoView == nullptr){
        this->infoView = new QTableView();
        this->infoView->setObjectName("widgetTableView");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

//    this->widgetLayout->addWidget(this->fileView,0,0,5,1);
//    this->widgetLayout->addWidget(this->infoView,0,1,5,4);

//    this->setLayout(this->widgetLayout);
    this->addWidget(this->fileView);
    this->addWidget(this->infoView);
    this->setOrientation(Qt::Horizontal);
    this->setSizes(QList<int>()<<50<<200);

    if(this->fileModel == nullptr){
        this->fileModel = new FileSystemModel();
        this->fileModel->setRootPath(QCoreApplication::applicationDirPath() + "/../log/");
        QStringList filter;
        filter<<"*.log"<<"*.data";
        this->fileModel->setNameFilters(filter);
        this->fileModel->setNameFilterDisables(false);
    }

    this->fileView->setModel(this->fileModel);
    this->fileView->setRootIndex(this->fileModel->index(QCoreApplication::applicationDirPath() + "/../log/"));


    if(this->logModel == nullptr){
        this->logModel = new InfoViewModel();
    }

    this->infoView->setModel(this->logModel);

    this->setObjectName("widgetSplitter");

}

void SystemLogWidget::connectSignalAndSlot()
{
    connect(this->fileView,&QTreeView::doubleClicked,this,&SystemLogWidget::doubleClickedSlot);
}

void SystemLogWidget::doubleClickedSlot(const QModelIndex &index)
{
    QFileInfo fileInfo(this->fileModel->filePath(index));
    if(fileInfo.isFile()){
        if(fileInfo.completeSuffix().compare("log") == 0 || fileInfo.completeSuffix().compare("data") == 0){
            //清除当前显示数据
            this->logModel->changedLogFile(this->fileModel->filePath(index));

            //初始化任务资源
            this->readFinish = false;
            this->cerializeFinist = false;

            //初始化数据读取任务
            if(readTask != nullptr){
                delete readTask;
                readTask = nullptr;
            }
            this->readTask = new FileReadTask(this->fileModel->filePath(index),3000);

            //初始化数据序列化任务
            if(this->cerializeTask != nullptr){
                delete this->cerializeTask;
                this->cerializeTask = nullptr;
            }
            this->cerializeTask = new LogFileCerializeTask(3000);

            connect(readTask,&FileReadTask::fileReadDataSignal,this->cerializeTask,&LogFileCerializeTask::addCerializeData,Qt::QueuedConnection);
            connect(readTask,&FileReadTask::fileReadFinishSignal,this->cerializeTask,&LogFileCerializeTask::fileReadFinishSlot,Qt::QueuedConnection);
            connect(this->cerializeTask,&LogFileCerializeTask::resultsCerializeDataSignal,this->logModel,&InfoViewModel::addLogMapForQueue,Qt::DirectConnection);
            //线程池中执行任务
            TPool::tPool->start(readTask);
            TPool::tPool->start(this->cerializeTask);
        }
    }else{

    }
}


SystemLogDataWidget::SystemLogDataWidget()
{

}














PlaneLogDownLoadWidget::PlaneLogDownLoadWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void PlaneLogDownLoadWidget::widgetInit()
{


    if(this->seleceAllCheckBox == nullptr){
        this->seleceAllCheckBox = new QCheckBox(QStringLiteral("全选"));
        this->seleceAllCheckBox->setObjectName("widgetCheckBox");
        this->seleceAllCheckBox->setEnabled(false);
    }
    if(this->getFileListButton == nullptr){
        this->getFileListButton = new QPushButton(QStringLiteral("获取日志列表"));
        this->getFileListButton->setObjectName("widgetButton");
    }
    if(this->downLoadButton == nullptr){
        this->downLoadButton = new QPushButton(QStringLiteral("下载选中日志"));
        this->downLoadButton->setObjectName("widgetButton");
        this->downLoadButton->setEnabled(false);
    }
    if(this->cancelButton == nullptr){
        this->cancelButton = new QPushButton(QStringLiteral("取消当前下载"));
        this->cancelButton->setObjectName("widgetButton");
        this->cancelButton->setEnabled(false);
    }
    if(this->cancelAllButton == nullptr){
        this->cancelAllButton = new QPushButton(QStringLiteral("取消所有下载"));
        this->cancelAllButton->setObjectName("widgetButton");
        this->cancelAllButton->setEnabled(false);
    }
    if( this->ClearLogButton == nullptr){
        this->ClearLogButton = new QPushButton(QStringLiteral("清除机载日志"));
        this->ClearLogButton->setObjectName("widgetButton");
//        this->ClearLogButton->setEnabled(false);
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->fileListView == nullptr){
        this->fileListView = new QTableView();
        this->fileListView->setObjectName("widgetTableView");

//        //设置表头颜色
//        QString qssTV = "QTableWidget::item:hover{background-color:rgb(92,188,227,200)}"
//                            "QTableWidget::item:selected{background-color:#1B89A1}"
//                            "QHeaderView::section,QTableCornerButton:section{ \
//                            padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
//                    border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
//                background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252); }"
//                "QTableWidget{background-color:white;border:none;}";
//        this->fileListView->horizontalHeader()->setStyleSheet(qssTV);
////        //设置相邻行颜色交替显示
//        this->fileListView->setAlternatingRowColors(true);
////        //垂直表头不显示
//////        this->fileListView->verticalHeader()->setVisible(false);

    }

    this->widgetLayout->addWidget(this->fileListView,0,0,10,10);
    this->widgetLayout->addWidget(this->seleceAllCheckBox,0,10,1,1);
    this->widgetLayout->addWidget(this->getFileListButton,5,10,1,1);
    this->widgetLayout->addWidget(this->downLoadButton,6,10,1,1);
    this->widgetLayout->addWidget(this->cancelButton,7,10,1,1);
    this->widgetLayout->addWidget(this->cancelAllButton,8,10,1,1);
    this->widgetLayout->addWidget(this->ClearLogButton,9,10,1,1);


    this->setLayout(this->widgetLayout);


    if(this->planeLogModel == nullptr){
        this->planeLogModel = new PlaneLogDownLoadModel;
        this->fileListView->setModel(this->planeLogModel);

    }

    if(this->checkBoxDelegate == nullptr){
        this->checkBoxDelegate = new CheckBoxDelegate();
        checkBoxDelegate->setColumn(0);
        this->fileListView->setItemDelegateForColumn(0,this->checkBoxDelegate);
    }
    if(this->progressBarDelegate == nullptr){
        this->progressBarDelegate = new ProgressBarDelegate();
        progressBarDelegate->setColumn(7,0,100);
        this->fileListView->setItemDelegateForColumn(7,this->progressBarDelegate);
    }
//        // 设置列宽
    this->fileListView->setColumnWidth(0, 60);
    this->fileListView->setColumnWidth(1, 60);
    this->fileListView->setColumnWidth(2, 120);
    this->fileListView->setColumnWidth(3, 160);
    this->fileListView->setColumnWidth(4, 120);
    this->fileListView->setColumnWidth(5, 120);
    this->fileListView->setColumnWidth(6, 80);
    this->fileListView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
}

void PlaneLogDownLoadWidget::connectSignalAndSlot()
{
    connect(this->seleceAllCheckBox, &QCheckBox::stateChanged, this, &PlaneLogDownLoadWidget::seleceAllCheckBoxChangedSlot);
    connect(this->getFileListButton, &QPushButton::pressed, this, &PlaneLogDownLoadWidget::getFileListButtonPressedSlot);
    connect(this->downLoadButton, &QPushButton::pressed, this, &PlaneLogDownLoadWidget::downloadButtonPressedSlot);
    connect(this->cancelButton, &QPushButton::pressed, this, &PlaneLogDownLoadWidget::cancelButtonPressedSlot);
    connect(this->cancelAllButton, &QPushButton::pressed, this, &PlaneLogDownLoadWidget::cancelAllButtonPresssedSlot);
    connect(this->ClearLogButton, &QPushButton::pressed, this, &PlaneLogDownLoadWidget::ClearLogButtonPresssedSlot);

    connect(this->planeLogModel,&PlaneLogDownLoadModel::selectFileChangedSignal,this,&PlaneLogDownLoadWidget::selectFileChangedSlot);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&PlaneLogDownLoadWidget::handle_DMMM_event);
}

void PlaneLogDownLoadWidget::seleceAllCheckBoxChangedSlot(int status)
{
    this->planeLogModel->selectAllFile((status == 0) ? false : true);
    selectFileChangedSlot();
}

void PlaneLogDownLoadWidget::getFileListButtonPressedSlot()
{
    this->planeLogModel->clearPlaneLogMap();
    if(this->seleceAllCheckBox->isEnabled() == true){                      //当数据列中没有数据时，全选按钮失能
        this->seleceAllCheckBox->setEnabled(false);
    }
    if(this->downLoadButton->isEnabled() == true){
        this->downLoadButton->setEnabled(false);
    }
    //获取文件列表相关操作
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->log_list_start();
    }
}

void PlaneLogDownLoadWidget::downloadButtonPressedSlot()
{
    QList<int> downloadFileList = this->planeLogModel->getSelectedFileId();                                                                     //获取所有被选中的文件列表ID
    this->planeLogModel->setDownloadFileList(downloadFileList);

    //获取文件列表相关操作
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){

        for(int i = 0; i < downloadFileList.count();i++){
            link->addDownloadIdToList(downloadFileList.at(i));
        }
        link->log_download_start();
    }
}

void PlaneLogDownLoadWidget::cancelButtonPressedSlot()
{
    QList<int> dowloadingFileList = this->planeLogModel->getDownloadingFileID();                                                        //获取当前正在下载中的文件列表
    //添加取消下载操作
    this->planeLogModel->setCancelDownloadFileList(dowloadingFileList);
    //清除界面下载信息

    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->log_download_cancel_current();
    }
}

void PlaneLogDownLoadWidget::cancelAllButtonPresssedSlot()
{
    QList<int> notCompletedDownloadFileList = this->planeLogModel->getNotCompletedDownloadFileID();                 //获取等待下载或正在下载的文件列表
    //添加取消下载操作

    this->planeLogModel->setCancelDownloadFileList(notCompletedDownloadFileList);                                                   //清除界面下载信息
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->log_download_cancel_all();
    }
}

void PlaneLogDownLoadWidget::ClearLogButtonPresssedSlot()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->send_log_clearAll();
    }
}

void PlaneLogDownLoadWidget::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    QList<FlyLink::log_info_t> loginfo{};
    if(link==nullptr){
        return;
    }
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_log_reqlist_failed:break;
        case Q_DMMM::DMMM_GCSEvent_log_getLogInfo:

        case Q_DMMM::DMMM_GCSEvent_log_getLogList:
            loginfo = link->getLog_info();

            // 清除model
            for(int i = 0; i < loginfo.count();i++){
                addPlaneLogFileListSlot(loginfo.at(i).id, QStringLiteral("日志 ")+QString::number(loginfo.at(i).id),QDateTime::fromTime_t(loginfo[i].time_utc), loginfo.at(i).size);

            }
            break;
        case Q_DMMM::DMMM_GCSEvent_log_reqdata_failed:break;
        case Q_DMMM::DMMM_GCSEvent_log_getLogData:
            {
                uint16_t index = 0xffff;
                uint32_t size = 0;
                link->log_download_current_state(index,size);
                if(index != 0xffff){
                    updatePlaneLogFileLoadSizeSlot(index,size);
                }
            }
            break;
        case Q_DMMM::DMMM_GCSEvent_log_getLogFile:break;
        case Q_DMMM::DMMM_GCSEvent_log_getLogAll:break;
        break;

        default:break;
    }
}

void PlaneLogDownLoadWidget::addPlaneLogFileListSlot(int id, QString fileName, QDateTime time, int size)
{
    this->planeLogModel->addPlaneLogFileList(id,fileName,time,size);

    if(this->seleceAllCheckBox->isEnabled() == false){                      //当数据列中有数据时，全选按钮使能
        this->seleceAllCheckBox->setEnabled(true);
    }
}

void PlaneLogDownLoadWidget::updatePlaneLogFileLoadSizeSlot(int id, int loadSize)
{
    this->planeLogModel->updatePlaneLogFileLoadSize(id,loadSize);
}

void PlaneLogDownLoadWidget::selectFileChangedSlot()
{
    QList<int> downloadFileList = this->planeLogModel->getSelectedFileId();                 //获取所有被选中的文件列表ID
    if(downloadFileList.count() > 0){
        if(this->downLoadButton->isEnabled() == false){
            this->downLoadButton->setEnabled(true);
        }
        if(this->cancelButton->isEnabled() == false){
            this->cancelButton->setEnabled(true);
        }
        if(this->cancelAllButton->isEnabled() == false){
            this->cancelAllButton->setEnabled(true);
        }
    }else{
        if(this->downLoadButton->isEnabled() == true){
            this->downLoadButton->setEnabled(false);
        }
        if(this->cancelButton->isEnabled() == true){
            this->cancelButton->setEnabled(false);
        }
        if(this->cancelAllButton->isEnabled() == true){
            this->cancelAllButton->setEnabled(false);
        }
    }
}














PlaneLogDownLoadModel::PlaneLogDownLoadModel()
{
//    this->planeLogMap.insert(1,new PlaneLogInfo());
//    this->mapIndexList.append(1);

}

QVariant PlaneLogDownLoadModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        if(role == Qt::DisplayRole){
            QHash<int, QByteArray> roles = headerNames();
            return QVariant(roles[section + Qt::UserRole + 1]);
        }else {
            return QVariant();
        }
    }
    return QVariant();
}

QModelIndex PlaneLogDownLoadModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex PlaneLogDownLoadModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int PlaneLogDownLoadModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->planeLogMap.count();
}

int PlaneLogDownLoadModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 8;
}

QVariant PlaneLogDownLoadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return false;
    }
    int row = index.row();
    int column = index.column();
    if(row < 0 || row > this->planeLogMap.count() || row > this->mapIndexList.count()){
        return QVariant();
    }
    int key = this->mapIndexList[row];

    if(this->planeLogMap.find(key) == this->planeLogMap.end()){
        return QVariant();
    }
    PlaneLogInfo *info = this->planeLogMap.find(key).value();
    switch(role){
    case Qt::DisplayRole:{
        switch(column + 1 + Qt::UserRole){
        case PlaneLogInfoRoles::PlaneLogCheck:{
            return info->logCheck;
        }case PlaneLogInfoRoles::PlaneLogID:{
            return info->logID;
        }case PlaneLogInfoRoles::PlaneLogName:{
            return info->logName;
        }case PlaneLogInfoRoles::PlaneLogTime:{
            return info->logTme.toString("yyyy-MM-dd hh:mm:ss");
        }case PlaneLogInfoRoles::PlaneLogSize:{
            return Q_DMMM::GetSuitableUnits_Bytes(info->logSize);
        }case PlaneLogInfoRoles::PlaneLogDownloadSize:{
            return Q_DMMM::GetSuitableUnits_Bytes(info->loadSize);
        }case PlaneLogInfoRoles::PlaneLogStatus:{
            QHash<int,QByteArray> status = this->statusNames();
            return status.find(info->status) != status.end() ? status.find(info->status).value() : QVariant();
        }case PlaneLogInfoRoles::PlaneLogLoadSize:{
            return static_cast<float>(info->loadSize * 100) / static_cast<float>(info->logSize) ;
        }
        }
    }

    }
    return QVariant();
}

bool PlaneLogDownLoadModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()){
        return false;
    }
    int row = index.row();
    int column = index.column();

    if(row >= this->planeLogMap.count() || row < 0 || column >= this->columnCount() || column < 0){
        return false;
    }
    int key = this->mapIndexList[row];

    if(this->planeLogMap.find(key) == this->planeLogMap.end()){
        return false;
    }
    PlaneLogInfo *info = this->planeLogMap.find(key).value();
    switch(role){
    case Qt::EditRole:{
        switch(column + 1 + Qt::UserRole){
        case PlaneLogInfoRoles::PlaneLogCheck:{
            this->beginResetModel();
            info->logCheck = (value.toInt() == 0 ? false  : true);
            this->endResetModel();
            emit selectFileChangedSignal();
            return true;
        }
        }
    }
    }
    return false;
}

QHash<int, QByteArray> PlaneLogDownLoadModel::roleNames() const
{
    QHash<int, QByteArray> roleName;
    roleName[PlaneLogCheck] = "PlaneLogCheck";
    roleName[PlaneLogID] = "PlaneLogID";
    roleName[PlaneLogName] = "PlaneLogName";
    roleName[PlaneLogTime] = "PlaneLogTime";
    roleName[PlaneLogSize] = "PlaneLogSize";
    roleName[PlaneLogDownloadSize] = "PlaneLogDownloadSize";
    roleName[PlaneLogStatus] = "PlaneLogStatus";
    roleName[PlaneLogLoadSize] = "PlaneLogLoadSize";
    return roleName;
}

QHash<int, QByteArray> PlaneLogDownLoadModel::headerNames() const
{
    QHash<int, QByteArray> headerName;
    headerName[PlaneLogCheck] = QStringLiteral("勾选").toUtf8();
    headerName[PlaneLogID] = QStringLiteral("序号").toUtf8();
    headerName[PlaneLogName] = QStringLiteral("名称").toUtf8();
    headerName[PlaneLogTime] = QStringLiteral("时间").toUtf8();
    headerName[PlaneLogSize] = QStringLiteral("日志大小").toUtf8();
    headerName[PlaneLogDownloadSize] = QStringLiteral("已下载大小").toUtf8();
    headerName[PlaneLogStatus] = QStringLiteral("状态").toUtf8();
    headerName[PlaneLogLoadSize] = QStringLiteral("进度").toUtf8();
      return headerName;
}

QHash<int, QByteArray> PlaneLogDownLoadModel::statusNames() const
{
    QHash<int, QByteArray> statusName;
//    0:未下载          1:等待下载    2:正在下载      3:下载完成      -1:下载失败
    statusName.insert(0,QStringLiteral("未下载").toUtf8());
    statusName.insert(1,QStringLiteral("等待下载").toUtf8());
    statusName.insert(2,QStringLiteral("正在下载").toUtf8());
    statusName.insert(3,QStringLiteral("下载完成").toUtf8());
    statusName.insert(-1,QStringLiteral("下载失败").toUtf8());

    return statusName;
}

Qt::ItemFlags PlaneLogDownLoadModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags =QAbstractItemModel::flags(index);

    switch(index.column() + 1 + Qt::UserRole){
    case PlaneLogInfoRoles::PlaneLogCheck:{
        flags |=  Qt::ItemIsEditable;
        break;
    }
    }

    return flags;
}

void PlaneLogDownLoadModel::clearPlaneLogMap()
{
    this->beginResetModel();
    this->mapIndexList.clear();
    QMap<int,PlaneLogInfo *>::Iterator iter = this->planeLogMap.begin();
    while(iter != this->planeLogMap.end()){
        if(iter.value() != nullptr){
            delete iter.value();
        }
        iter++;
    }
    this->planeLogMap.clear();
    this->endResetModel();
}

void PlaneLogDownLoadModel::addPlaneLogFileList(int id, QString fileName, QDateTime time, int size)
{
    this->beginResetModel();
    if(this->mapIndexList.indexOf(id) == -1){
        this->mapIndexList.append(id);
        PlaneLogInfo *info = new PlaneLogInfo;
        info->logCheck = false;
        info->logID = id;
        info->logName = fileName;
        info->logTme = time;
        info->logSize = size;
        info->loadSize = 0;
        info->status = 0;
        this->planeLogMap.insert(id,info);
    }else{
        if(this->planeLogMap.find(id) == this->planeLogMap.end()){
            PlaneLogInfo *info = new PlaneLogInfo;
            info->logCheck = false;
            info->logID = id;
            info->logName = fileName;
            info->logTme = time;
            info->logSize = size;
            info->loadSize = 0;
            info->status = 0;
            this->planeLogMap.insert(id,info);
        }else{
            PlaneLogInfo *info = this->planeLogMap.find(id).value();
            if(info != nullptr){
                info->logCheck = false;
                info->logID = id;
                info->logName = fileName;
                info->logTme = time;
                info->logSize = size;
                info->loadSize = 0;
                info->status = 0;
            }else{
                PlaneLogInfo *info = new PlaneLogInfo;
                info->logCheck = false;
                info->logID = id;
                info->logName = fileName;
                info->logTme = time;
                info->logSize = size;
                info->loadSize = 0;
                info->status = 0;
                this->planeLogMap[id] = info;
            }
        }
    }

    this->endResetModel();
}

void PlaneLogDownLoadModel::updatePlaneLogFileLoadSize(int id, int loadSize)
{
    if(this->mapIndexList.indexOf(id) == -1){
        return;
    }
    if(this->planeLogMap.find(id) == this->planeLogMap.end()){
        return;
    }
    PlaneLogInfo *info = this->planeLogMap.find(id).value();
    if(info == nullptr){
        return;
    }
    this->beginResetModel();
    info->loadSize = loadSize;
    if(info->loadSize > 0 && info->loadSize < info->logSize){
        info->status = 2;                   //将当前状态置为正在下载状态
    }else{
        if(info->loadSize == info->logSize){
            info->status = 3;               //将当前状态置为下载完成状态
        }
    }
    this->endResetModel();
}

void PlaneLogDownLoadModel::selectAllFile(bool status)
{
    this->beginResetModel();
    QMap<int,PlaneLogInfo *>::Iterator iter = this->planeLogMap.begin();
    while(iter != this->planeLogMap.end()){
        if(iter.value() != nullptr){
            iter.value()->logCheck = status;
        }
        iter++;
    }
    this->endResetModel();
}

QList<int> PlaneLogDownLoadModel::getSelectedFileId()
{
    QList<int> retList = {};
    QMap<int,PlaneLogInfo *>::Iterator iter = this->planeLogMap.begin();
    while(iter != this->planeLogMap.end()){
        if(iter.value() != nullptr){
            if(iter.value()->logCheck == true){
                retList.append(iter.value()->logID);
            }
        }
        iter++;
    }
    return retList;
}

QList<int> PlaneLogDownLoadModel::getDownloadingFileID()
{
    QList<int> retList = {};
    QMap<int,PlaneLogInfo *>::Iterator iter = this->planeLogMap.begin();
    while(iter != this->planeLogMap.end()){
        if(iter.value() != nullptr){
            if(iter.value()->status == 2){
                retList.append(iter.value()->logID);
            }
        }
        iter++;
    }
    return retList;
}

QList<int> PlaneLogDownLoadModel::getNotCompletedDownloadFileID()
{
    QList<int> retList = {};
    QMap<int,PlaneLogInfo *>::Iterator iter = this->planeLogMap.begin();
    while(iter != this->planeLogMap.end()){
        if(iter.value() != nullptr){
            if(iter.value()->status == 2 || iter.value()->status == 1){
                retList.append(iter.value()->logID);
            }
        }
        iter++;
    }
    return retList;
}

void PlaneLogDownLoadModel::setDownloadFileList(QList<int> list)
{
    for(int i = 0; i < list.count(); i++){
        if(this->mapIndexList.indexOf(list.at(i)) == -1){
            continue;
        }
        if(this->planeLogMap.find(list.at(i)) == this->planeLogMap.end()){
            continue;
        }
        PlaneLogInfo *info = this->planeLogMap.find(list.at(i)).value();
        if(info == nullptr){
            return;
        }
        this->beginResetModel();
        info->status = 1;                                                           //将当前状态设置为等待下载状态

        this->endResetModel();
    }
}

void PlaneLogDownLoadModel::setCancelDownloadFileList(QList<int> list)
{
    for(int i = 0; i < list.count(); i++){
        if(this->mapIndexList.indexOf(list.at(i)) == -1){
            continue;
        }
        if(this->planeLogMap.find(list.at(i)) == this->planeLogMap.end()){
            continue;
        }
        PlaneLogInfo *info = this->planeLogMap.find(list.at(i)).value();
        if(info == nullptr){
            return;
        }
        this->beginResetModel();
        info->status = 0;                                                           //将当前状态设置为等待下载状态
        info->loadSize = 0;
        this->endResetModel();
    }
}



static QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)/*const*/
{
    //绘制按钮所需要的参数
    QStyleOptionButton checkBoxStyleOption;
    //按照给定的风格参数 返回元素子区域
    QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    //返回QCheckBox坐标
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);
    //返回QCheckBox几何形状
    return QRect(checkBoxPoint, checkBoxRect.size());
}

CheckBoxDelegate::CheckBoxDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

void CheckBoxDelegate::setColumn(int col)
{
    column = col;
}

// 绘制复选框
void CheckBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();

    if(index.column() == column){
        QStyleOptionButton checkBoxStyleOption;
        checkBoxStyleOption.state |= QStyle::State_Enabled;
        checkBoxStyleOption.state |= checked? QStyle::State_On : QStyle::State_Off;
        checkBoxStyleOption.rect = CheckBoxRect(option);

        QApplication::style()->drawControl(QStyle::CE_CheckBox,&checkBoxStyleOption,painter);
    }else{
        QStyledItemDelegate::paint(painter, option, index);
    }
}

// 响应鼠标事件，更新数据
bool CheckBoxDelegate::editorEvent(QEvent *event,
                                QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) {
    if(index.column() == column){
    if((event->type() == QEvent::MouseButtonRelease) || (event->type() == QEvent::MouseButtonDblClick)|| (event->type() == QEvent::MouseButtonPress)){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() != Qt::LeftButton || !CheckBoxRect(option).contains(mouseEvent->pos())){
            return true;
        }
        if(event->type() == QEvent::MouseButtonDblClick){
            return true;
        }
    }else if(event->type() == QEvent::KeyPress){
        if(static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
                static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select){
            return false;
        }
    }else{
        return false;
    }

    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
    int data = checked ? 0 : 1;     //互逆
    return model->setData(index, data, Qt::EditRole);
    }else{
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }
}


/****************************************************
* ProgressBarDelegate
****************************************************/

ProgressBarDelegate::ProgressBarDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void ProgressBarDelegate::setColumn(int col, int min, int max)
{
    column = col;
    maxValue = max;
    minValue = min;
}

// 绘制进度条
void ProgressBarDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
    if (index.column() == column) {
        QStyleOptionProgressBar bar;
        bar.rect = option.rect;
        bar.progress = index.data().toInt();
        bar.maximum = maxValue;
        bar.minimum = minValue;
        bar.text = QString("%1%").arg(bar.progress);
        bar.textAlignment = Qt::AlignCenter;
        bar.textVisible = true;

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &bar, painter);
    }
    else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}


ReplayWidget::ReplayWidget()
{
//    if(this->loggerRelpayWidget == nullptr){
//        this->loggerRelpayWidget = new LoggerReplay();
//    }


}

void ReplayWidget::showEvent(QShowEvent *e)
{
//    if(this->loggerRelpayWidget != nullptr){
//        this->setCentralWidget(this->loggerRelpayWidget->getWidget());
//    }
}
