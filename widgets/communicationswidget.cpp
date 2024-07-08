#include "communicationswidget.h"
#include "DMMM.h"




CommunicationsWidget::CommunicationsWidget(QWidget *parent)
    : QWidget(parent)
{
    if(main_tablewidget == nullptr){
        main_tablewidget = new QTabWidget();
        main_tablewidget->setObjectName("CommunicationsWidget");
    }
    parameterMapInit();
    basicConfigWidgetInit();
    photoelectricConfigInit();

    widgetInit();
    connectSignalAndSlot();
}

void CommunicationsWidget::widgetInit()
{
    main_tablewidget->addTab(this->basicConfigWidget,QStringLiteral("基础连接"));
//    main_tablewidget->addTab(this->photoelectricConfigWidget,QStringLiteral("光电连接"));

    this->setWindowTitle(QStringLiteral("通讯连接"));
    this->setObjectName("CommunicationsWidget");


    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("通信连接"));
        w_title->setMaximumHeight(40);
    }
    if(this->WidgetLayout == nullptr){
        this->WidgetLayout = new QGridLayout;
        this->WidgetLayout->setMargin(0);
        this->WidgetLayout->setSpacing(0);
    }

    this->WidgetLayout->addWidget(this->main_tablewidget,0,0,1,1);
    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->WidgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);

    this->setWindowFlags(this->windowFlags() |Qt::Dialog|Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
    QFile file(QString(":/style/communiicationswidget.qss"));

    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }

    this->resize(600,400);
}

void CommunicationsWidget::basicConfigWidgetInit()
{
    if(this->basicConfigWidget == nullptr){
        this->basicConfigWidget = new QGroupBox;
        this->basicConfigWidget->setObjectName("CommunicationsWidget");
    }

    if(this->basicConfigWidgetLayout == nullptr){
        this->basicConfigWidgetLayout = new QGridLayout;
    }

    if(this->basicConfigModel == nullptr){
        this->basicConfigModel = new BasicConfigWidgetTableModel();
    }

    if(this->deviceItemDelegate == nullptr){
        this->deviceItemDelegate = new BasicConfigWidgetDeviceItemDelegate();
    }

    if(this->buttonDelegate == nullptr){
        this->buttonDelegate = new BasicConfigWidgetButtonDelegate();
    }


    if(this->basicConfigTableView == nullptr){
        this->basicConfigTableView = new QTableView();
        this->basicConfigTableView->setModel(this->basicConfigModel);
        this->basicConfigTableView->setObjectName("basicConfigTableView");
        this->basicConfigTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        this->basicConfigTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        this->basicConfigTableView->horizontalHeader()->setStretchLastSection(true);
        this->basicConfigTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->basicConfigTableView->setAttribute(Qt::WA_StyledBackground,true);
        this->basicConfigTableView->setItemDelegateForColumn(0,this->deviceItemDelegate);
        this->basicConfigTableView->setItemDelegateForColumn(1,this->deviceItemDelegate);
        this->basicConfigTableView->setItemDelegateForColumn(2,this->deviceItemDelegate);
        this->basicConfigTableView->setItemDelegateForColumn(3,this->deviceItemDelegate);
        this->basicConfigTableView->setItemDelegateForColumn(4,this->buttonDelegate);
    }

    if(this->addButton == nullptr){
        this->addButton = new QPushButton("+");
        this->addButton->setObjectName("Basic_Button");
        this->addButton->setFixedSize(90,35);


    }
    if(this->subButton == nullptr){
        this->subButton = new QPushButton("-");
        this->subButton->setObjectName("Basic_Button");
        this->subButton->setFixedSize(90,35);

    }
    if(this->buttonLayout == nullptr){
        this->buttonLayout = new QHBoxLayout();
    }
    this->buttonLayout->addWidget(this->addButton);
    this->buttonLayout->addWidget(this->subButton);
    this->buttonLayout->setSpacing(10);
    this->buttonLayout->setMargin(5);

    this->basicConfigWidgetLayout->addWidget(this->basicConfigTableView,0,0,9,5);
    this->basicConfigWidgetLayout->addItem(this->buttonLayout,9,4,1,1);
    this->basicConfigWidget->setLayout(this->basicConfigWidgetLayout);
    this->basicConfigWidgetLayout->setMargin(0);
}

void CommunicationsWidget::photoelectricConfigInit()
{

    if(this->photoelectricConfigWidget == nullptr){
        this->photoelectricConfigWidget = new QGroupBox;
        this->photoelectricConfigWidget->setObjectName("basicConfigWidget");
    }

    if(this->photoelectricConfigWidgetLayout == nullptr){
        this->photoelectricConfigWidgetLayout = new QGridLayout;
    }

    if(this->rtspBaseBox == nullptr){
        this->rtspBaseBox = new QGroupBox(QStringLiteral("基础设置"));
         this->rtspBaseBox->setObjectName("photoelectricConfigBox");
    }
    if(this->rtspAdvancedBox == nullptr){
        this->rtspAdvancedBox = new QGroupBox(QStringLiteral("高级设置"));
        this->rtspAdvancedBox->setObjectName("photoelectricConfigBox");
    }

    if(this->rtspBaseLayout == nullptr){
        this->rtspBaseLayout = new QGridLayout();
    }
    if(this->rtspAddressLabel == nullptr){
        this->rtspAddressLabel = new QLabel(QStringLiteral("Rtsp地址:"));
        this->rtspAddressLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
         this->rtspAdvancedBox->setObjectName("photoelectricConfigLabel");
    }
    if(this->rtspAddressComboBox == nullptr){
        this->rtspAddressComboBox = new QComboBox();
        this->rtspAddressComboBox->setEditable(true);
    }
    if(this->linkButton == nullptr){
        this->linkButton = new QPushButton(QStringLiteral("连接"));
    }

     this->rtspBaseLayout->addWidget(this->rtspAddressLabel,0,0,1,1);
    this->rtspBaseLayout->addWidget(this->rtspAddressComboBox,0,1,1,3);
    this->rtspBaseLayout->addWidget(this->linkButton,0,4,1,1);
    this->rtspBaseLayout->setContentsMargins(5,20,15,10);
    this->rtspBaseLayout->setSpacing(2);
    this->rtspBaseBox->setLayout(this->rtspBaseLayout);


    if(this->rtspAdvancedLayout == nullptr){
        this->rtspAdvancedLayout = new QGridLayout();
    }
    if(this->linkMode == nullptr){
        this->linkMode = new QLabel(QStringLiteral("连接方式:"));
        this->linkMode->setObjectName("photoelectricConfigLabel");
    }
    if(this->linkModeComboBox == nullptr){
        this->linkModeComboBox = new QComboBox();
        this->linkModeComboBox->addItems(QStringList()<<"udp"<<"tcp"<<"rtp");
         this->linkModeComboBox->setCurrentText("udp");
    }
    if(this->codecMode == nullptr){
        this->codecMode = new QLabel(QStringLiteral("解码速度:"));
        this->codecMode->setObjectName("photoelectricConfigLabel");
    }
    if(this->codecModeComboBox == nullptr){
        this->codecModeComboBox = new QComboBox();
        this->codecModeComboBox->addItems(QStringList()<<"ultrafast"<<"superfast"<<"veryfast"<<"faster"<<"fast"<<"medium"<<"slow"<<"slower"<<"veryslow"<<"placebo");
         this->codecModeComboBox->setCurrentText("fast");
    }
    if(this->bufferSize == nullptr){
        this->bufferSize = new QLabel(QStringLiteral("缓冲区大小"));
        this->bufferSize->setObjectName("photoelectricConfigLabel");
    }
    if(this->bufferSizeEdit == nullptr){
        this->bufferSizeEdit = new QLineEdit("1024000");
    }
    if(this->maxDelay == nullptr){
        this->maxDelay = new QLabel(QStringLiteral("延时约束:"));
        this->maxDelay->setObjectName("photoelectricConfigLabel");
    }
    if(this->maxDelayEdit == nullptr){
        this->maxDelayEdit = new QLineEdit("5000");
    }
    if(this->cfrLabel == nullptr){
        this->cfrLabel = new QLabel(QStringLiteral("视频质量:"));
        this->cfrLabel->setObjectName("photoelectricConfigLabel");
    }
    if(this->cfrComboBox == nullptr){
        this->cfrComboBox = new QComboBox();
        QStringList list;
        for(int i = 0; i < 51; i++){
            list<<QString::number(i);
        }
        this->cfrComboBox->addItems(list);
        this->cfrComboBox->setCurrentText("23");
    }
    if(this->stimeoutLabel == nullptr){
        this->stimeoutLabel = new QLabel(QStringLiteral("连接超时:"));
        this->stimeoutLabel->setObjectName("photoelectricConfigLabel");
    }
    if(this->stimeoutEdit == nullptr){
        this->stimeoutEdit = new QLineEdit("1000000");
    }
    if(this->fpsLabel == nullptr){
        this->fpsLabel = new QLabel(QStringLiteral("fps:"));
        this->fpsLabel->setObjectName("photoelectricConfigLabel");
    }
    if(this->fpsComboBox == nullptr){
        this->fpsComboBox = new QComboBox();

        this->fpsComboBox->addItems(QStringList()<<"5"<<"10"<<"15"<<"20"<<"25"<<"30"<<"35"<<"40"<<"45"<<"50"<<"55"<<"60");
        this->fpsComboBox->setCurrentText("25");
    }


    rtspAdvancedLayout->addWidget(this->linkMode,0,0,1,1);
    rtspAdvancedLayout->addWidget(this->linkModeComboBox,0,1,1,1);
    rtspAdvancedLayout->addWidget(this->bufferSize,0,2,1,1);
    rtspAdvancedLayout->addWidget(this->bufferSizeEdit,0,3,1,1);
    rtspAdvancedLayout->addWidget(this->codecMode,1,0,1,1);
    rtspAdvancedLayout->addWidget(this->codecModeComboBox,1,1,1,1);
    rtspAdvancedLayout->addWidget(this->maxDelay,1,2,1,1);
    rtspAdvancedLayout->addWidget(this->maxDelayEdit,1,3,1,1);
    rtspAdvancedLayout->addWidget(this->cfrLabel,2,0,1,1);
    rtspAdvancedLayout->addWidget(this->cfrComboBox,2,1,1,1);
    rtspAdvancedLayout->addWidget(this->stimeoutLabel,2,2,1,1);
    rtspAdvancedLayout->addWidget(this->stimeoutEdit,2,3,1,1);
    rtspAdvancedLayout->addWidget(this->fpsLabel,3,0,1,1);
    rtspAdvancedLayout->addWidget(this->fpsComboBox,3,1,1,1);


    this->rtspAdvancedLayout->setContentsMargins(5,20,15,10);
    this->rtspAdvancedLayout->setSpacing(2);

    this->rtspAdvancedBox->setLayout(this->rtspAdvancedLayout);

    this->photoelectricConfigWidgetLayout->addWidget(this->rtspBaseBox,0,0,1,5);
    this->photoelectricConfigWidgetLayout->addWidget(this->rtspAdvancedBox,1,0,5,5);

    this->photoelectricConfigWidgetLayout->setSpacing(10);
    this->photoelectricConfigWidget->setLayout(this->photoelectricConfigWidgetLayout);

}

void CommunicationsWidget::parameterMapInit()
{
    parameterMap.clear();

    parameterMap.insert("rtsp_transport","udp");
    parameterMap.insert("preset","fast");
    parameterMap.insert("buffer_size","1024000");
    parameterMap.insert("max_delay","5000");
    parameterMap.insert("cfr","23");
    parameterMap.insert("stimeout","1000000");
    parameterMap.insert("fps","25");
    parameterMap.insert("fflags","nobuffer");
    parameterMap.insert("probsize","4096");
    parameterMap.insert("packet-bufferin","0");
}

void CommunicationsWidget::connectSignalAndSlot()
{
    connect(this->addButton,&QPushButton::released,this,&CommunicationsWidget::basicConfigWidgetAddButtonReleaseSlot);
    connect(this->subButton,&QPushButton::released,this,&CommunicationsWidget::basicConfigWidgetRemoveButtonReleaseSlot);

    connect(this->basicConfigModel,&BasicConfigWidgetTableModel::connectButtonReleaseSignal,this,&CommunicationsWidget::connectButtonReleaseSlot);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();});

    connect(this->linkButton,&QPushButton::released,this,&CommunicationsWidget::photoelectricLinkButtonClickedSlot);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CommunicationsWidget::handle_DMMM_event);
}

void CommunicationsWidget::basicConfigWidgetAddButtonReleaseSlot()
{
    if(this->basicConfigModel != nullptr){
        this->basicConfigModel->addNewConnect();
    }
}

void CommunicationsWidget::basicConfigWidgetRemoveButtonReleaseSlot()
{

}

void CommunicationsWidget::connectButtonReleaseSlot(const QModelIndex &index)
{

    BasicConfigWidgetTableModel::BasicModelData modelData;
    modelData.linkID = index.data(BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_linkID).toInt();
    modelData.Device = index.data(BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).toInt();
    modelData.address = index.data(BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss).toString();
    modelData.channel = index.data(BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel).toString();
    modelData.isOpen = index.data(BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_isOpen).toBool();

    FlyLink::DeviceType_e device = FlyLink::DeviceType_None;
    if(modelData.Device == FlyLink::DeviceType_None){
        return;
    }else if(modelData.Device == FlyLink::DeviceType_SerialPort){
        device = FlyLink::DeviceType_SerialPort;
    }else if(modelData.Device == FlyLink::DeviceType_NetUDP){
        device = FlyLink::DeviceType_NetUDP;
    }

    if(Qt::DMMM()== nullptr)return;

    if(modelData.isOpen){              //打开
        QMap<QString,QVariant>openMap{};
        // 依据类型传入参数
        switch(device){
        case FlyLink::DeviceType_SerialPort:
            openMap[STR_SerialPort] = QVariant::fromValue(modelData.address);
            openMap[STR_SerialPort_baudRate] = QVariant::fromValue(modelData.channel.toInt());

            break;
        case FlyLink::DeviceType_NetUDP:
            openMap[STR_SocketUDP] = QVariant::fromValue(QHostAddress(modelData.address));
            openMap[STR_SocketUDP_Port] = QVariant::fromValue(modelData.channel.toUShort());
            break;
        default:
            return;
        }
        Qt::DMMM()->open(openMap,modelData.linkID);
        emit newConnectGcsIDSignal(true,modelData.linkID);
//        this->basicConfigModel->setData(index,QVariant(true),Qt::EditRole);
        SystemData::getCommunicationsData()->setLastCommunicationType(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).toInt());
        switch(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).toInt()){
            case BasicConfigWidgetTableModel::DeviceType::Device_SerialPort:{
                SystemData::getCommunicationsData()->setLastSerialConnectName(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss).toString());
                SystemData::getCommunicationsData()->setLastSerialConnectBaud(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel).toString());
                break;
            }case BasicConfigWidgetTableModel::DeviceType::Device_NetTCP:{
                SystemData::getCommunicationsData()->setLastTcpConnectAddress(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss).toString());
                SystemData::getCommunicationsData()->setLastTcpConnectPort(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel).toString());
                break;
            }case BasicConfigWidgetTableModel::DeviceType::Device_NetUDP:{
                SystemData::getCommunicationsData()->setLastUdpConnectAddress(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss).toString());
                SystemData::getCommunicationsData()->setLastUdpConnectPort(this->basicConfigModel->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel).toString());
                break;
            }
        }
    }else{                              //关闭
        Qt::DMMM()->close(modelData.linkID);
        this->basicConfigModel->setData(index,QVariant(false),Qt::EditRole);
        emit newConnectGcsIDSignal(false,modelData.linkID);
    }

}

void CommunicationsWidget::photoelectricLinkButtonClickedSlot()
{
    if(this->linkButton->text().compare(QStringLiteral("连接")) == 0){

        QUrl url = QUrl(this->rtspAddressComboBox->currentText());
        parameterMap["rtsp_transport"] = this->linkModeComboBox->currentText();
        parameterMap["preset"] = this->codecModeComboBox->currentText();
        parameterMap["buffer_size"] = this->bufferSizeEdit->text();
        parameterMap["max_delay"] = this->maxDelayEdit->text();
        parameterMap["cfr"] = this->cfrComboBox->currentText();
        parameterMap["stimeout"] = this->stimeoutEdit->text();
        parameterMap["fps"] = this->fpsComboBox->currentText();

        emit photoelectricStartSignal(url,parameterMap);
    }else{
        emit photoelectricStopSignal();
        this->linkButton->setText(QStringLiteral("连接"));
        this->rtspAddressComboBox->setEnabled(true);
    }

}

void CommunicationsWidget::handle_DMMM_event(int ev, int linkid)
{
        Q_UNUSED(linkid);

        // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_ComDeviceErr:
        case Q_DMMM::DMMM_GCSEvent_DeviceOpenFailed:
        qDebug()<<"CommunicationsWidget-------------- "<< ev;
        changedLinkStartForLinkID(linkid,false,false);
        break;
        case Q_DMMM::DMMM_GCSEvent_DeviceOpenSucceed:
        qDebug()<<"CommunicationsWidget "<< ev;
        changedLinkStartForLinkID(linkid,true,false);
        break;

        default:break;
    }
}

void CommunicationsWidget::changedLinkStartForLinkID(int linkid, bool status, bool islinked)
{
    if(islinked){
        this->basicConfigModel->setData(this->basicConfigModel->index(linkid,4),status,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_isOpen);
    }else{
        this->basicConfigModel->setData(this->basicConfigModel->index(linkid,4),status,Qt::DisplayRole);
    }
}

void CommunicationsWidget::videoStartSlot(bool status)
{
    if(status){
        this->linkButton->setText(QStringLiteral("断开"));
        this->rtspAddressComboBox->setEnabled(false);
    }else{
        this->linkButton->setText(QStringLiteral("连接"));
        this->rtspAddressComboBox->setEnabled(true);
    }
}





BasicConfigWidgetTableModel::BasicConfigWidgetTableModel()
{
    initDeviceTypeNames();
    initDeviceSerialBaudMap();
    addNewConnect();
}

QVariant BasicConfigWidgetTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        switch(role){
            case Qt::DisplayRole:{
                QHash<int, QString> name = headerNames();
                return QVariant(name[section + Qt::UserRole + 1]);
            }case Qt::TextAlignmentRole:{
                return Qt::AlignCenter;
            }case Qt::FontRole:{
                return QFont("SimHei",10);
            }
        }
    }
    return QVariant();
}

QModelIndex BasicConfigWidgetTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex BasicConfigWidgetTableModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int BasicConfigWidgetTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->BasicData.count();
}

int BasicConfigWidgetTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 5;
}

QVariant BasicConfigWidgetTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();

    if(row < 0 || row >= this->BasicData.count() || row > this->BasicIDList.count()){
        return QVariant();
    }

    int column = index.column();
    int lindID = this->BasicIDList.at(row);
    switch(role){
    case Qt::DisplayRole:
        return this->getModelDataFromIDAndColumn(lindID,column);
    case BasicDataRoutes::BasicData_linkID:
        return this->BasicData.find(this->BasicIDList.at(row)) != this->BasicData.end() ? this->BasicData.find(this->BasicIDList.at(row)).value().linkID : QVariant();
    case BasicDataRoutes::BasicData_Device:
        return this->BasicData.find(this->BasicIDList.at(row)) != this->BasicData.end() ? this->BasicData.find(this->BasicIDList.at(row)).value().Device : QVariant();
    case BasicDataRoutes::BasicData_addresss:
        return this->BasicData.find(this->BasicIDList.at(row)) != this->BasicData.end() ? this->BasicData.find(this->BasicIDList.at(row)).value().address : QVariant();
    case BasicDataRoutes::BasicData_channel:
        return this->BasicData.find(this->BasicIDList.at(row)) != this->BasicData.end() ? this->BasicData.find(this->BasicIDList.at(row)).value().channel : QVariant();
    case BasicDataRoutes::BasicData_isOpen:
        return this->BasicData.find(this->BasicIDList.at(row)) != this->BasicData.end() ? this->BasicData.find(this->BasicIDList.at(row)).value().isOpen : QVariant();
    case BasicDataRoutes::BasicData_DeviceTyppeNameList:
        return getDeviceTypeNameList();
    case BasicDataRoutes::BasicData_DeviceSerialComList:
        return getDeviceSerialCom();
    case BasicDataRoutes::BasicData_DeviceSerialBaudList:
        return getDeviceBaud();
    case Qt::EditRole:
        return this->getModelDataFromIDAndColumn(lindID,column);
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    default:
        return QVariant();
    }
}

bool BasicConfigWidgetTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()){
        return false;
    }
    int row = index.row();
    int column = index.column();

    if(row < 0 || row >= this->BasicData.count() || row > this->BasicIDList.count()){
        return false;
    }

    bool ret = false;

    switch(role){
    case Qt::DisplayRole:{
        ret = upModelData(row,column,value);
        break;
    }case Qt::EditRole:{
        ret = upModelData(row,column,value);
        break;
    }case BasicDataRoutes::BasicData_isOpen:{
        ret = upModelData(row,column,value);
        emit connectButtonReleaseSignal(index);
        break;
    }case BasicDataRoutes::BasicData_linkID:{
        ret = upModelData(row,0,value);
        break;
    }
    }

    return ret;
}

QHash<int, QByteArray> BasicConfigWidgetTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[BasicData_linkID] = "BasicData_linkID";
    roles[BasicData_isOpen] = "BasicData_isOpen";
    roles[BasicData_Device] = "BasicData_Device";
    roles[BasicData_addresss] = "BasicData_addresss";
    roles[BasicData_channel] = "BasicData_channel";

    return roles;
}

QHash<int, QString> BasicConfigWidgetTableModel::headerNames() const
{
    QHash<int, QString> headerName;
    headerName[BasicData_linkID] = QStringLiteral("通讯ID");
    headerName[BasicData_isOpen] = QStringLiteral("操作");
    headerName[BasicData_Device] = QStringLiteral("设备类型");
    headerName[BasicData_addresss] = QStringLiteral("IP/串口号");
    headerName[BasicData_channel] = QStringLiteral("端口/波特率");
    return headerName;
}



void BasicConfigWidgetTableModel::addNewConnect()
{
    BasicModelData data;

    data.linkID = this->BasicData.count();
    data.Device = SystemData::getCommunicationsData()->getLastCommunicationType();
    switch (data.Device) {
    case DeviceType::Device_SerialPort:{
        data.address = SystemData::getCommunicationsData()->getLastSerialConnectName();
        data.channel = SystemData::getCommunicationsData()->getLastSerialConnectBaud();
        break;
    }case DeviceType::Device_NetUDP:{
        data.address = SystemData::getCommunicationsData()->getLastUdpConnectAddress();
        data.channel = SystemData::getCommunicationsData()->getLastUdpConnectPort();
        break;
    }case DeviceType::Device_NetTCP:{
        data.address = SystemData::getCommunicationsData()->getLastTcpConnectAddress();
        data.channel = SystemData::getCommunicationsData()->getLastTcpConnectPort();
        break;
    }
    default:
        data.Device = FlyLink::DeviceType_NetUDP;
        data.address = QStringLiteral("127.0.0.1");
        data.channel = QString::number(8235);
        break;
    }

    data.isOpen = false;
    this->beginResetModel();
    this->BasicIDList.append(data.linkID);
    this->BasicData.insert(data.linkID,data);
    this->endResetModel();
}

void BasicConfigWidgetTableModel::initDeviceTypeNames()
{
    deviceTypeNamesMap.insert(DeviceType::Device_None,QStringLiteral("未选择"));
    deviceTypeNamesMap.insert(DeviceType::Device_SerialPort,QStringLiteral("串口"));
    deviceTypeNamesMap.insert(DeviceType::Device_NetUDP,QStringLiteral("UDP"));
    deviceTypeNamesMap.insert(DeviceType::Device_NetTCP,QStringLiteral("TCP"));
    deviceTypeNamesMap.insert(DeviceType::Device_end,QStringLiteral("未选择"));
}



void BasicConfigWidgetTableModel::initDeviceSerialBaudMap()
{
    this->BasicBaudMap.insert(1200,QSerialPort::BaudRate::Baud1200);
    this->BasicBaudMap.insert(2400,QSerialPort::BaudRate::Baud2400);
    this->BasicBaudMap.insert(4800,QSerialPort::BaudRate::Baud4800);
    this->BasicBaudMap.insert(9600,QSerialPort::BaudRate::Baud9600);
    this->BasicBaudMap.insert(19200,QSerialPort::BaudRate::Baud19200);
    this->BasicBaudMap.insert(38400,QSerialPort::BaudRate::Baud38400);
    this->BasicBaudMap.insert(57600,QSerialPort::BaudRate::Baud57600);
    this->BasicBaudMap.insert(115200,QSerialPort::BaudRate::Baud115200);
    this->BasicBaudMap.insert(230400,230400);
}

const QString BasicConfigWidgetTableModel::getDeviceTypeNameFromDeviceType(int type) const
{
    if(this->deviceTypeNamesMap.find(type) != this->deviceTypeNamesMap.end()){
        return this->deviceTypeNamesMap.find(type).value();
    }else{
        return QStringLiteral("未选择");
    }
}

const int BasicConfigWidgetTableModel::getDeviceTypeFromDeviceTypeName(QString name) const
{
    QMap<int,QString>::const_iterator iter = this->deviceTypeNamesMap.begin();
    while(iter != this->deviceTypeNamesMap.end()){
        if(iter.value().compare(name) == 0){
            return iter.key();
        }
        iter ++;
    }
    return DeviceType::Device_None;
}

QStringList BasicConfigWidgetTableModel::getDeviceTypeNameList() const
{
    QList<QString> deviceNameList;
    QMap<int,QString>::const_iterator iter = this->deviceTypeNamesMap.begin();
    while(iter != this->deviceTypeNamesMap.end()){
        if(deviceNameList.indexOf(iter.value()) == -1){
            deviceNameList.append(iter.value());
        }

        iter ++;
    }
    return deviceNameList;
}

Qt::ItemFlags BasicConfigWidgetTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    bool status = index.data(BasicDataRoutes::BasicData_isOpen).toBool();
    int column = index.column();
    switch(column + Qt::UserRole + 1){
        case BasicDataRoutes::BasicData_linkID:
        case BasicDataRoutes::BasicData_Device:
        case BasicDataRoutes::BasicData_addresss:
        case BasicDataRoutes::BasicData_channel:{
            if(status == false){
                flags |= Qt::ItemFlag::ItemIsEditable;
            }
            break;
        }case BasicDataRoutes::BasicData_isOpen:{
            break;
        }
        default:{
            flags = Qt::ItemFlag::NoItemFlags;
            break;
        }
    }
    return flags;
}

const QVariant BasicConfigWidgetTableModel::getModelDataFromIDAndColumn(int id, int column) const
{
    if(this->BasicData.find(id) != this->BasicData.end()){
        BasicModelData modelData = this->BasicData.find(id).value();
        switch(column + Qt::UserRole + 1){
        case BasicDataRoutes::BasicData_linkID:{
            return QString::number(modelData.linkID);
        }case BasicDataRoutes::BasicData_Device:{
            return getDeviceTypeNameFromDeviceType(modelData.Device);
        }case BasicDataRoutes::BasicData_addresss:{
            return modelData.address;
        }case BasicDataRoutes::BasicData_channel:{
            return modelData.channel;
        }case BasicDataRoutes::BasicData_isOpen:{
            return modelData.isOpen ? QStringLiteral("打开"):QStringLiteral("关闭");
        }
        }
    }
    return QVariant();
}

bool BasicConfigWidgetTableModel::upModelData(int row, int column, QVariant data)
{
    bool ret = false;
    if(this->BasicData.find(this->BasicIDList.at(row)) != this->BasicData.end()){
        this->beginResetModel();
        switch(column + Qt::UserRole + 1){
        case BasicDataRoutes::BasicData_linkID:{
            this->BasicData[this->BasicIDList.at(row)].linkID = data.toInt();
            ret = true;
            break;
        }case BasicDataRoutes::BasicData_Device:{
            this->BasicData[this->BasicIDList.at(row)].Device = this->getDeviceTypeFromDeviceTypeName(data.toString());
            ret = true;
            break;
        }case BasicDataRoutes::BasicData_addresss:{
            this->BasicData[this->BasicIDList.at(row)].address = data.toString();
            ret = true;
            break;
        }case BasicDataRoutes::BasicData_channel:{
            this->BasicData[this->BasicIDList.at(row)].channel = data.toString();
            ret = true;
            break;
        }case BasicDataRoutes::BasicData_isOpen:{
            this->BasicData[this->BasicIDList.at(row)].isOpen = data.toBool();
            ret = true;
            break;
        }default:{
            ret = false;
            break;
        }
        }

        this->endResetModel();
    }

    return ret;
}

const QStringList BasicConfigWidgetTableModel::getDeviceSerialCom() const
{
    QList<QString> serialportinfo;
    foreach(QSerialPortInfo info,QSerialPortInfo::availablePorts())
    {
        serialportinfo<<info.portName();
    }
    return serialportinfo;
}

const QStringList BasicConfigWidgetTableModel::getDeviceBaud() const
{
//    return this->BasicBaudMap.keys();
    QList<QString> ret;
    QMap<int,int>::const_iterator iter = this->BasicBaudMap.begin();
    while(iter != this->BasicBaudMap.end()){
        ret.append(QString::number(iter.key()));
        iter++;
    }
    return ret;
}




BasicConfigWidgetDeviceItemDelegate::BasicConfigWidgetDeviceItemDelegate(QObject *parent): QItemDelegate(parent)
{

}




QWidget *BasicConfigWidgetDeviceItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    switch(index.column() + Qt::UserRole + 1){
    case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_linkID:{
        QLineEdit *edit = new QLineEdit(parent);
        return edit;
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device:{
        QStringList deviceNameList = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_DeviceTyppeNameList).value<QStringList>();
        QComboBox *combobox = new QComboBox(parent);
        combobox->addItems(deviceNameList);
        return combobox;
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss:{
        int deviceType = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).value<int>();
        switch(deviceType){
        case BasicConfigWidgetTableModel::DeviceType::Device_NetTCP:
        case BasicConfigWidgetTableModel::DeviceType::Device_NetUDP:{
            QLineEdit *edit = new QLineEdit(parent);
            return edit;
        }
        case BasicConfigWidgetTableModel::DeviceType::Device_SerialPort:{
            QComboBox *combobox = new QComboBox(parent);
            QStringList deviceComList = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_DeviceSerialComList).value<QStringList>();
            combobox->addItems(deviceComList);
            return combobox;
        }default:
            QLineEdit *edit = new QLineEdit(parent);
            return edit;
        }
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel:{
        int deviceType = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).value<int>();
        switch(deviceType){
        case BasicConfigWidgetTableModel::DeviceType::Device_NetTCP:
        case BasicConfigWidgetTableModel::DeviceType::Device_NetUDP:{
            QLineEdit *edit = new QLineEdit(parent);
            return edit;
        }
        case BasicConfigWidgetTableModel::DeviceType::Device_SerialPort:{
            QComboBox *combobox = new QComboBox(parent);
            QStringList deviceComList = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_DeviceSerialBaudList).value<QStringList>();
            combobox->addItems(deviceComList);
            return combobox;
        }default:
            QLineEdit *edit = new QLineEdit(parent);
            return edit;
        }
    }
    }

    return new QLineEdit();

}

void BasicConfigWidgetDeviceItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column() + Qt::UserRole + 1){
    case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_linkID:{
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QLineEdit *edit = static_cast<QLineEdit *>(editor);
        edit->setText(value);
        break;
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device:{
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *edit = static_cast<QComboBox *>(editor);
        edit->setCurrentText(value);
        break;
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss:
     case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel:{
        int deviceType = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).value<int>();
        switch(deviceType){
        case BasicConfigWidgetTableModel::DeviceType::Device_NetTCP:
        case BasicConfigWidgetTableModel::DeviceType::Device_NetUDP:{
            QString value = index.model()->data(index, Qt::DisplayRole).toString();
            QLineEdit *edit = static_cast<QLineEdit *>(editor);
            edit->setText(value);
            break;
        }case BasicConfigWidgetTableModel::DeviceType::Device_SerialPort:{
            QString value = index.model()->data(index, Qt::DisplayRole).toString();
            QComboBox *edit = static_cast<QComboBox *>(editor);
            edit->setCurrentText(value);
            break;
        }
        }
        break;
    }

    }

}

void BasicConfigWidgetDeviceItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column() + Qt::UserRole + 1){
    case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_linkID:{
        QString str = static_cast<QLineEdit *>(editor)->text();
        model->setData(index, str, Qt::EditRole);
        break;
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device:{
        QString str = static_cast<QComboBox *>(editor)->currentText();
        model->setData(index, str, Qt::EditRole);
        break;
    }case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_addresss:
    case BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_channel:{
        int deviceType = index.model()->data(index,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_Device).value<int>();
        switch(deviceType){
        case BasicConfigWidgetTableModel::DeviceType::Device_NetTCP:
        case BasicConfigWidgetTableModel::DeviceType::Device_NetUDP:{
            QString str = static_cast<QLineEdit *>(editor)->text();
            model->setData(index, str, Qt::EditRole);
            break;
        }case BasicConfigWidgetTableModel::DeviceType::Device_SerialPort:{
            QString str = static_cast<QComboBox *>(editor)->currentText();
            model->setData(index, str, Qt::EditRole);
            break;
        }

        }
        break;
    }
    }

}

void BasicConfigWidgetDeviceItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect.x(),option.rect.y(),option.rect.width() ,option.rect.height());


}


BasicConfigWidgetButtonDelegate::BasicConfigWidgetButtonDelegate()
{

}

void BasicConfigWidgetButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     bool status = index.model()->data(index, BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_isOpen).toBool();
     QStyleOptionButton btnStyle;
     btnStyle.text = status ? QStringLiteral("关闭") : QStringLiteral("打开");             //设置按钮文本
     btnStyle.rect = option.rect;            //设置按钮区域为当前item的rect
     btnStyle.state = QStyle::State_Enabled; //设置按钮状态

     QPushButton btn;
     btn.setObjectName("Basic_Button");
     QFile file(QString(":/style/communiicationswidget.qss"));
     if(file.open(QIODevice::ReadOnly)){
         btn.setStyleSheet(file.readAll());
         file.close();
     }
     btn.style()->drawControl(QStyle::CE_PushButton, &btnStyle, painter,&btn);   //将按钮绘制出来
}

bool BasicConfigWidgetButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model);
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    bool status = index.model()->data(index, BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_isOpen).toBool();
    if(option.rect.contains(mouseEvent->pos()))
    {
        if(event->type() == QEvent::MouseButtonRelease){
            model->setData(index,!status,BasicConfigWidgetTableModel::BasicDataRoutes::BasicData_isOpen);
            return true;
        }
    }

    return false;
}
