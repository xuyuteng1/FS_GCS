#include "routeswidget.h"
#include "DMMM.h"




RoutesWidget::RoutesWidget(QWidget *parent)
    : QWidget(parent)
{
    if(this->models == nullptr){
        this->models = new GIS_Models;
    }
    if(this->routesModel == nullptr){
        this->routesModel = this->models->getRoutesModel();
    }
    widgetInit();
    if(Qt::DMMM()!=nullptr){
        get_route_from_datapool(Qt::DMMM()->getMain_link_id());
    }


    this->routesListView->setModel(this->routesModel);

    if(this->cmdDelegate == nullptr){
        this->cmdDelegate = new GIS_AirRoutesPointCMDDelegate();
        this->routesPointView->setItemDelegateForColumn(1,this->cmdDelegate);
    }

    if(this->alititudeTypeDelegate == nullptr){
        this->alititudeTypeDelegate = new GIS_AirRoutesPointAlititudeTypeDelegate;
        this->routesPointView->setItemDelegateForColumn(5,this->alititudeTypeDelegate);
    }

    if(this->lngDelegate == nullptr){
        this->lngDelegate = new GIS_AirRoutesPointCoordinatesDelegate;
        this->routesPointView->setItemDelegateForColumn(2,this->lngDelegate);
    }
    if(this->latDelegate == nullptr){
        this->latDelegate = new GIS_AirRoutesPointCoordinatesDelegate;
        this->routesPointView->setItemDelegateForColumn(3,this->latDelegate);
    }

    if(this->parameter1Delegate == nullptr){
        this->parameter1Delegate = new GIS_AirRoutesPointParameter1Delegate;
        this->routesPointView->setItemDelegateForColumn(6,this->parameter1Delegate);
    }

    if(this->parameter2Delegate == nullptr){
        this->parameter2Delegate = new GIS_AirRoutesPointParameter2Delegate;
        this->routesPointView->setItemDelegateForColumn(7,this->parameter2Delegate);
    }

    if(this->parameter3Delegate == nullptr){
        this->parameter3Delegate = new GIS_AirRoutesPointParameter3Delegate;
        this->routesPointView->setItemDelegateForColumn(8,this->parameter3Delegate);
    }

    if(this->parameter4Delegate == nullptr){
        this->parameter4Delegate = new GIS_AirRoutesPointParameter4Delegate;
        this->routesPointView->setItemDelegateForColumn(9,this->parameter4Delegate);
    }


    connectSignalAndSlot();


    this->setObjectName("systemWidget");
    this->setWindowTitle(QStringLiteral("航线规划"));

    this->resize(1000,600);
    this->setWindowOpacity(0.95);
    this->setAttribute(Qt::WA_StyledBackground,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
//    QFile file(QString(":/style/routesWidget.qss"));

//    if(file.open(QIODevice::ReadOnly)){
//        this->setStyleSheet(file.readAll());
//        file.close();
//    }
}

void RoutesWidget::widgetInit()
{

    if(this->routesListView == nullptr){
        this->routesListView = new QListView(this);
        this->routesListView->setAlternatingRowColors(false);                               //每间隔一行颜色不一样，当有qss时该属性无效
        this->routesListView->setFocusPolicy(Qt::NoFocus);                                  //去掉鼠标移到单元格上时的虚线框
        this->routesListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);     //滚动模式，按像素滚动
        this->routesListView->setAttribute(Qt::WA_StyledBackground,true);
        this->routesListView->setObjectName("widgetListView");
    }

    if(this->routesPointView == nullptr){
        this->routesPointView = new QTableView(this);
        this->routesPointView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        this->routesPointView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->routesPointView->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->routesPointView->setAttribute(Qt::WA_StyledBackground,true);
        this->routesPointView->setObjectName("widgetTableView");
        this->routesPointView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    if(this->widgetSplitter == nullptr){
        this->widgetSplitter = new QSplitter(this);
        this->widgetSplitter->setOrientation(Qt::Horizontal);
        this->widgetSplitter->setSizes(QList<int>()<<50<<200);
        this->widgetSplitter->setObjectName("widgetSplitter");
        this->widgetSplitter->addWidget(this->routesListView);
        this->widgetSplitter->addWidget(this->routesPointView);
        this->widgetSplitter->setStretchFactor(0,1);
        this->widgetSplitter->setStretchFactor(1,10);
    }

    if(this->addRoutesButton == nullptr){
        this->addRoutesButton = new QPushButton(QIcon(":/img/rotues/add.png"),QStringLiteral("添加"));
        this->addRoutesButton->setObjectName("widgetButton");
    }
    if(this->removeRoutesButton == nullptr){
        this->removeRoutesButton = new QPushButton(QIcon(":/img/rotues/remove.png"),QStringLiteral("删除"));
        this->removeRoutesButton->setObjectName("widgetButton");
    }
    if(this->loadLoacationRouteButton == nullptr){
        this->loadLoacationRouteButton = new QPushButton(QIcon(":/img/rotues/goto.png"),QStringLiteral("加载"));
        this->loadLoacationRouteButton->setObjectName("widgetButton");
    }

    if(this->saveAsButton == nullptr){
        this->saveAsButton = new QPushButton(QIcon(":/img/rotues/sqveass.png"),QStringLiteral("保存"));
        this->saveAsButton->setObjectName("widgetButton");
    }
    if(this->uploadRouteButton == nullptr){
        this->uploadRouteButton = new QPushButton(QIcon(":/img/rotues/upload.png"),QStringLiteral("上传"));
        this->uploadRouteButton->setObjectName("widgetButton");
    }
    if(this->downloadRouteButton == nullptr){
        this->downloadRouteButton = new QPushButton(QIcon(":/img/rotues/download.png"),QStringLiteral("下载"));
        this->downloadRouteButton->setObjectName("widgetButton");
    }

    if(this->routesButtonsLayout == nullptr){
        this->routesButtonsLayout = new QGridLayout();

        this->routesButtonsLayout->addWidget(this->addRoutesButton,0,0,1,1);
        this->routesButtonsLayout->addWidget(this->loadLoacationRouteButton,0,1,1,1);
        this->routesButtonsLayout->addWidget(this->uploadRouteButton,0,2,1,1);

        this->routesButtonsLayout->addWidget(this->removeRoutesButton,1,0,1,1);
        this->routesButtonsLayout->addWidget(this->saveAsButton,1,1,1,1);
        this->routesButtonsLayout->addWidget(this->downloadRouteButton,1,2,1,1);


        this->routesButtonsLayout->setMargin(0);
        this->routesButtonsLayout->setSpacing(9);
    }


    if(this->insertPointButton == nullptr){
        this->insertPointButton = new QPushButton(QIcon(":/img/rotues/insertTop.png"),QStringLiteral("添加航点-首行"));
        this->insertPointButton->setObjectName("widgetButton");
    }
    if(this->apppendPointButton == nullptr){
        this->apppendPointButton = new QPushButton(QIcon(":/img/rotues/insertBottom.png"),QStringLiteral("添加航点-尾行"));
        this->apppendPointButton->setObjectName("widgetButton");
    }

    if(this->insertPointBelowIndexButton == nullptr){
        this->insertPointBelowIndexButton = new QPushButton(QIcon(":/img/rotues/caretBottom.png"),QStringLiteral("添加航点-行后"));
        this->insertPointBelowIndexButton->setObjectName("widgetButton");
    }

    if(this->insertPointAboveIndexButton == nullptr){
        this->insertPointAboveIndexButton = new QPushButton(QIcon(":/img/rotues/caretTop.png"),QStringLiteral("添加航点-行前"));
        this->insertPointAboveIndexButton->setObjectName("widgetButton");
    }

    if(this->moveUpPointButton == nullptr){
        this->moveUpPointButton = new QPushButton(QIcon(":/img/rotues/moveUp.png"),QStringLiteral("航点上移"));
        this->moveUpPointButton->setObjectName("widgetButton");
    }
    if(this->moveDownPointButton == nullptr){
        this->moveDownPointButton = new QPushButton(QIcon(":/img/rotues/moveDown.png"),QStringLiteral("航点下移"));
        this->moveDownPointButton->setObjectName("widgetButton");
    }

    if(this->removePointButton == nullptr){
        this->removePointButton = new QPushButton(QIcon(":/img/rotues/delete.png"),QStringLiteral("删除航点"));
        this->removePointButton->setObjectName("widgetButton");
    }

    if(this->removeAllPointsButton == nullptr){
        this->removeAllPointsButton = new QPushButton(QIcon(":/img/rotues/deleteAll.png"),QStringLiteral("删除所有航点"));
        this->removeAllPointsButton->setObjectName("widgetButton");
    }

    if(this->signPointButton == nullptr){
        this->signPointButton = new QPushButton(QIcon(":/img/rotues/add.png"),QStringLiteral("标定航点"));
        this->signPointButton->setObjectName("widgetButton");
    }

    if(this->appendPointForMouseButton == nullptr){
        this->appendPointForMouseButton = new QPushButton(QIcon(":/img/rotues/addPoint.png"),QStringLiteral("鼠标点选"));
        this->appendPointForMouseButton->setObjectName("widgetButton");
        this->appendPointForMouseButton->setCheckable(true);
    }


    if(this->pointButtonsLayout == nullptr){
        this->pointButtonsLayout = new QGridLayout();
        this->pointButtonsLayout->addWidget(this->insertPointButton,0,0,1,1);
        this->pointButtonsLayout->addWidget(this->apppendPointButton,1,0,1,1);
        this->pointButtonsLayout->addWidget(this->insertPointAboveIndexButton,0,1,1,1);
        this->pointButtonsLayout->addWidget(this->insertPointBelowIndexButton,1,1,1,1);
        this->pointButtonsLayout->addWidget(this->moveUpPointButton,0,2,1,1);
        this->pointButtonsLayout->addWidget(this->moveDownPointButton,1,2,1,1);
        this->pointButtonsLayout->addWidget(this->removePointButton,0,3,1,1);
        this->pointButtonsLayout->addWidget(this->removeAllPointsButton,1,3,1,1);
//        this->pointButtonsLayout->addWidget(this->signPointButton,0,4,1,1);
        this->pointButtonsLayout->addWidget(this->appendPointForMouseButton,1,4,1,1);

        this->pointButtonsLayout->setSpacing(0);
        this->pointButtonsLayout->setMargin(0);
    }

    if(this->WidgetLayout == nullptr){
        this->WidgetLayout = new QGridLayout;
        this->WidgetLayout->setMargin(0);
        this->WidgetLayout->setSpacing(1);
    }

    this->WidgetLayout->addWidget(this->widgetSplitter,0,0,4,32);
    this->WidgetLayout->addItem(this->routesButtonsLayout,4,0,1,2);
    this->WidgetLayout->addItem(this->pointButtonsLayout,4,12,1,20);

    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("航线编辑"));
        w_title->setMaximumHeight(40);
    }
    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->WidgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);
}

void RoutesWidget::connectSignalAndSlot()
{
    connect(this->routesListView,&QListView::clicked,this,&RoutesWidget::indexClickedSlot);
    connect(this->addRoutesButton,&QPushButton::clicked,this,&RoutesWidget::addRoutesButtonClickedSlot);
    connect(this->removeRoutesButton,&QPushButton::clicked,this,&RoutesWidget::removeRoutesButtonClickedSlot);
    connect(this->loadLoacationRouteButton,&QPushButton::clicked,this,&RoutesWidget::loadLoacationRouteButtonClickedSlot);
    connect(this->saveAsButton,&QPushButton::clicked,this,&RoutesWidget::saveAsButtonClickedSlot);
    connect(this->uploadRouteButton,&QPushButton::clicked,this,&RoutesWidget::uploadRouteButtonClickedSlot);
    connect(this->downloadRouteButton,&QPushButton::clicked,this,&RoutesWidget::downloadRouteButtonClickedSlot);

    connect(this->apppendPointButton,&QPushButton::pressed,this,&RoutesWidget::apppendPointButtonPressedSlot);
    connect(this->insertPointButton,&QPushButton::pressed,this,&RoutesWidget::insertPointButtonPressedSlot);
    connect(this->insertPointBelowIndexButton,&QPushButton::pressed,this,&RoutesWidget::insertPointBelowIndexButtonPressedSlot);
    connect(this->insertPointAboveIndexButton,&QPushButton::pressed,this,&RoutesWidget::insertPointAboveIndexButtonPressedSlot);
    connect(this->moveUpPointButton,&QPushButton::pressed,this,&RoutesWidget::moveUpPointButtonPressedSlot);
    connect(this->moveDownPointButton,&QPushButton::pressed,this,&RoutesWidget::moveDownPointButtonPressedSlot);
    connect(this->removePointButton,&QPushButton::pressed,this,&RoutesWidget::removePointButtonPressedSlot);
    connect(this->removeAllPointsButton,&QPushButton::pressed,this,&RoutesWidget::removeAllPointsButtonPressedSlot);
    connect(this->signPointButton,&QPushButton::pressed,this,&RoutesWidget::signPointButtonPressedSlot);
    connect(this->appendPointForMouseButton,&QPushButton::pressed,this,&RoutesWidget::appendPointForMouseButtonPressedSlot);

    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&RoutesWidget::handle_DMMM_event);
    connect(this->routesModel,&GIS_AirRoutesModel::currentRoutesChangedSignal,this,&RoutesWidget::currentRoutesChangedSlot);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
}

void RoutesWidget::get_route_from_datapool(int linkid)
{
    FlyLink::mission_local_t routesList;
    Qt::DMMM()->getLocal_mission(routesList,linkid);

    if(routesList.mission.count() <= 0){
        qDebug()<<QStringLiteral("未读取到航线数据");
        return;
    }
    qDebug()<<QStringLiteral("收到航线数据");
    this->routesModel->removeRouteForID(linkid);
    this->routesModel->createNewRoute(linkid);

    for(int i = 0; i < routesList.mission.count(); i++){
        this->routesModel->addRouteItemPoint(linkid,\
                                             static_cast<double>(routesList.mission.at(i).y) / static_cast<double>(1e7),\
                                             static_cast<double>(routesList.mission.at(i).x) / static_cast<double>(1e7),\
                                             routesList.mission.at(i).z,\
                                             routesList.mission.at(i).frame,\
                                             routesList.mission.at(i).command,\
                                             routesList.mission.at(i).param1,\
                                             routesList.mission.at(i).param2,\
                                             routesList.mission.at(i).param3,\
                                             routesList.mission.at(i).param4);
    }

    this->routesModel->setData(QModelIndex(),QVariant(linkid),GIS_AirRoutesModel::AirRoutesData::DATA_CurrentRouteID);
}

void RoutesWidget::indexClickedSlot(const QModelIndex &index)
{
    int id = this->routesModel->data(index,GIS_AirRoutesModel::AirRoutesData::DATA_RoutesID).toInt();
    this->routesModel->setData(index,QVariant(id),GIS_AirRoutesModel::AirRoutesData::DATA_CurrentRouteID);
    qDebug()<<"indexClickedSlot id = "<<id;
}


//添加航线
void RoutesWidget::addRoutesButtonClickedSlot()
{
    this->routesModel->createNewRoute(Qt::DMMM()->getMain_link_id());
}


//删除航线
void RoutesWidget::removeRoutesButtonClickedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    this->models->routesModel->removeRoute(routesRow);
}


//加载航线
void RoutesWidget::loadLoacationRouteButtonClickedSlot()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,QStringLiteral("加载航线"),QCoreApplication::applicationDirPath(),"*.waypoints");
    QFile file(filePath);
    if(!file.open(QIODevice::ReadWrite)){
        qDebug()<<"航线加载错误，文件无法打开。\r\nPATH:" + filePath;
        return;
    }

    QFileInfo info(filePath);
    int id = info.fileName().remove(".waypoints").toInt();
    this->routesModel->createNewRoute(id);
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        QStringList strList(str.remove("\r\n").remove(" ").split("\t"));
        qDebug()<<strList;
        if(strList.count() == 12){
            this->routesModel->addRouteItemPoint(id,strList.at(8).toDouble(),strList.at(9).toDouble(),strList.at(10).toDouble(),strList.at(2).toInt(),strList.at(3).toInt(),strList.at(4).toInt(),strList.at(5).toInt(),strList.at(6).toInt(),strList.at(7).toInt());
        }
    }
}


//航线保存本地
void RoutesWidget::saveAsButtonClickedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    int routesRowCount = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>()->rowCount();
    QString filePath = QFileDialog::getSaveFileName(this, QStringLiteral("保存航线"), ".", tr("*.waypoints"));
    QFile file(filePath);
    QFileInfo info(file);
    if(info.isFile()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QStringLiteral("保存航线"));
        msgBox.setText(QStringLiteral("航线文件存在，是否替换"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Yes:
            file.remove();
            break;
        default:
            return;
        }
    }

    if(file.open(QIODevice::ReadWrite)){
        int row = 0;
        while(routesRowCount --){
            GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();

            QString str;
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointID).toInt()),16,QLatin1Char(' ')));      //ID
            str.append(QString("%1\t").arg(QString::number(0),16,QLatin1Char(' ')));                  //
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointAlititudeModel).toInt()),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointCommondID).toInt()),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter1).toDouble(),'f',4),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter2).toDouble(),'f',4),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter3).toDouble(),'f',4),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter4).toDouble(),'f',4),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointLng).toDouble(),'f',7),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointLat).toDouble(),'f',7),16,QLatin1Char(' ')));
            str.append(QString("%1\t").arg(QString::number(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointAlititude).toDouble(),'f',4),16,QLatin1Char(' ')));
            str.append(QString("%1\r\n").arg(QString::number(1),16,QLatin1Char(' ')));                  //
            QByteArray  strBytes=str.toUtf8();//转换为字节数组
            file.write(strBytes,strBytes.length());  //写入文件
            row ++;
        }

        file.close();
    }else{
        QMessageBox::warning(nullptr,QStringLiteral("警告"),QStringLiteral("航线保存失败，文件无法打开。"));
        return;
    }

}


//航线上传
void RoutesWidget::uploadRouteButtonClickedSlot()
{
    FlyLink::mission_local_t routesList{};
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }
    int routesRowCount = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>()->rowCount();

    int row = 0;
    while(routesRowCount --){
        GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();
        FlyLink::mission_item_t missionItem{};
        missionItem.seq = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointID).toInt() & 0xFFFF;
        missionItem.command = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointCommondID).toInt() & 0xFFFF;
        missionItem.param1 = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter1).toFloat();
        missionItem.param2 = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter2).toFloat();
        missionItem.param3 = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter3).toFloat();
        missionItem.param4 = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointParameter4).toFloat();
        missionItem.y = static_cast<int>(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointLng).toDouble() * 10000000);
        missionItem.x= static_cast<int>(item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointLat).toDouble() * 10000000);
        missionItem.z = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointAlititude).toFloat();
        missionItem.frame = item->data(this->routesModel->index(row,0),GIS_AirRouteItemModel::AirRouteItem::DATA_PointAlititudeModel).toInt();
        routesList.mission.append(missionItem);
        row ++;
    }

    Qt::DMMM()->setLocal_mission(routesList,Qt::DMMM()->getMain_link_id());
    Qt::DMMM()->mission_upload_start(Qt::DMMM()->getMain_link_id());
}


//航线下载
void RoutesWidget::downloadRouteButtonClickedSlot()
{
    Qt::DMMM()->mission_download_start(Qt::DMMM()->getMain_link_id());


}

void RoutesWidget::apppendPointButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();

    if(item != nullptr){
        item->createItemPoint(100,33);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(item->rowCount() - 1,0));
    }

}

void RoutesWidget::insertPointButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();

    if(item != nullptr){
        item->insertItemPointToHead(108,34);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(0,0));
    }
}

void RoutesWidget::insertPointBelowIndexButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    int routeRow = this->routesPointView->currentIndex().row();
    if(routeRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择插入航点位置，请先选中需要插入航点的位置。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();
    if(item != nullptr){
        item->insertItemPointBelowIndex(routeRow,108,34);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(routeRow < item->rowCount() ? routeRow + 1 : routeRow,0));
    }
}

void RoutesWidget::insertPointAboveIndexButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    int routeRow = this->routesPointView->currentIndex().row();
    if(routeRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择插入航点位置，请先选中需要插入航点的位置。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();
    if(item != nullptr){
        item->insertItemPointAboveIndex(routeRow,108,34);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(routeRow,0));
    }
}

void RoutesWidget::moveUpPointButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    int routeRow = this->routesPointView->currentIndex().row();
    if(routeRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择移动航点，请先选中需要移动的航点。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();
    if(item != nullptr){
        item->pointIndexMoveUp(routeRow);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(routeRow > 0 ? routeRow - 1 : 0,0));

    }
}

void RoutesWidget::moveDownPointButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    int routeRow = this->routesPointView->currentIndex().row();
    if(routeRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择移动航点，请先选中需要移动的航点。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();
    if(item != nullptr){
        item->pointIndexMoveDown(routeRow);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(routeRow < item->rowCount() - 1  ? routeRow + 1 : routeRow,0));
    }
}

void RoutesWidget::removePointButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    int routeRow = this->routesPointView->currentIndex().row();
    if(routeRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择移动航点，请先选中需要移动的航点。"));
        return;
    }
    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();
    if(item != nullptr){
        item->removePointForIndex(routeRow);
//        this->routesListView->setCurrentIndex(this->routesModel->index(routesRow,0));
        this->routesPointView->setCurrentIndex(item->index(routeRow > 0 ? routeRow - 1 : 0,0));
    }
}

void RoutesWidget::removeAllPointsButtonPressedSlot()
{
//    int routesRow = this->routesListView->currentIndex().row();
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    GIS_AirRouteItemModel *item = this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RouteModel).value<GIS_AirRouteItemModel *>();

    if(item != nullptr){
        item->removeAllPoint();
    }
}

void RoutesWidget::signPointButtonPressedSlot()
{

}

void RoutesWidget::appendPointForMouseButtonPressedSlot()
{
    int routesRow = this->routesModel->getRoutesIndexForRoutesID(this->routesModel->getCurrentRouteID());
    if(routesRow < 0){
        QMessageBox::warning(this,QStringLiteral("错误操作"),QStringLiteral("未选择操作的航线，请先选中需要操作的航线。"));
        return;
    }

    emit appendPointForMousePressedSignal(!this->appendPointForMouseButton->isChecked(),this->routesModel->data(this->routesModel->index(routesRow,0),GIS_AirRoutesModel::AirRoutesData::DATA_RoutesID).toInt());
}

void RoutesWidget::handle_DMMM_event(int ev, int linkid)
{
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_Mission_download_Succeed:{
            get_route_from_datapool(linkid);
        }
        break;
    }
}

void RoutesWidget::currentRoutesChangedSlot()
{
    qDebug()<<"currentRoutesChangedSlot";
//    int id = this->routesModel->data(,GIS_AirRoutesModel::AirRoutesData::DATA_CurrentRouteID).toInt();
    int id = this->routesModel->getCurrentRouteID();
    GIS_AirRouteItemModel *model = this->routesModel->getAirRoutesItemModelForRoutesID(id);
    if(model != this->currentItemModel && model != nullptr){
        this->currentItemModel = model;
        this->routesPointView->setModel(this->currentItemModel);
        this->routesPointView->update();
    }
    qDebug()<<id;
    this->routesListView->setCurrentIndex(this->routesModel->index(this->routesModel->getRoutesIndexForRoutesID(id),0));
//    this->routesListView->setCurrentIndex(index.row(),0));
    //    this->routesListView->setCurrentIndex()
}

void RoutesWidget::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e)
    this->appendPointForMouseButton->setChecked(false);
    emit this->routesWidgetCloseSignal();
}

void RoutesWidget::changeEvent(QEvent *event)
{
    if(event->type() != QEvent::WindowStateChange){
        return;
    }
    if(this->windowState()==Qt::WindowMinimized){
        this->appendPointForMouseButton->setChecked(false);
        emit this->routesWidgetCloseSignal();
    }

}
