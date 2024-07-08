#include "G_cfg_communicationinterface.h"
#include "DMMM.h"

G_CFG_SerialManager::G_CFG_SerialManager(QWidget *parent):
  QWidget(parent)
{
    initWidget();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("串口配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void G_CFG_SerialManager::initWidget()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("串口配置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
    }
    if(this->serialConfigWidget == nullptr){
        this->serialConfigWidget = new SerialConfigWidget();
        this->serialConfigWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 禁用滚动
    }

    if(this->upDateButton == nullptr){
        this->upDateButton = new QPushButton(QStringLiteral("查询"));
        this->upDateButton->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(this->selectButton == nullptr){
        this->selectButton = new QPushButton(QStringLiteral("设置"));
        this->selectButton->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }


    QHBoxLayout*    widgetLayout_pb = new QHBoxLayout();


    widgetLayout_pb->addStretch(5);
    widgetLayout_pb->addWidget(upDateButton,1);
    widgetLayout_pb->addWidget(selectButton,1);
    widgetLayout_pb->addStretch(5);

    this->widgetLayout->addWidget(this->titleLabel,0,0,1,5);
//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 1);
    this->widgetLayout->addWidget(this->serialConfigWidget,2,0,1,5);
    this->widgetLayout->addLayout(widgetLayout_pb,3,0,1,5);
//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 4, 1, 1);



    this->widgetLayout->setContentsMargins(0,20,0,30);
    this->setLayout(widgetLayout);


}

void G_CFG_SerialManager::connectSignalAndSlot()
{
    connect(this->upDateButton, &QPushButton::pressed,this,&G_CFG_SerialManager::upDateButtonPressedSlot);
    connect(this->selectButton, &QPushButton::pressed,this,&G_CFG_SerialManager::selectButtonPressedSlot);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_SerialManager::handle_DMMM_event);
}

void G_CFG_SerialManager::upDateButtonPressedSlot()
{
    //请求数据
    if(Qt::DMMM()->getFlyLink_main() != nullptr){
        Qt::DMMM()->getFlyLink_main()->req_ParamSerialPort();
    }

}

void G_CFG_SerialManager::selectButtonPressedSlot()
{
    if(Qt::DMMM()->getFlyLink_main() != nullptr){
        FlyLink::param_SerialPort_t serial{};
        serial.is_set = true;
        serial.count = this->serialConfigWidget->getItemWidgeCount();
        for(int i = 0 ; i < qMin((uint8_t)8,serial.count);i++){
            this->serialConfigWidget->getItemWidgetInfo(QStringLiteral("飞控串口")+QString::number(i),serial.param[i].baud,serial.param[i].protocol);
        }
        Qt::DMMM()->getFlyLink_main()->do_setParamSerialPort(serial);
    }
}

void G_CFG_SerialManager::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamSerialPortOption:
            if(Qt::DMMM()->getFlyLink_main() != nullptr){
                this->serialConfigWidget->clearSerialConfigWidget();
                FlyLink::param_SerialPort_t serial  = Qt::DMMM()->getFlyLink_main()->getTVehicleParam().SerialPortOption;
                for(int i = 0 ; i < serial.count;i++){
//                    qDebug()<<serial.param[i].baud<<serial.param[i].protocol;
                    this->serialConfigWidget->addItemWidget(QStringLiteral("飞控串口")+QString::number(i), \
                                                            serial.param[i].baud,\
                                                            serial.param[i].protocol);
                }
            }
        break;

        default:break;
    }
}



SerialConfigWidget::SerialConfigWidgetItem::SerialConfigWidgetItem(QString str, uint32_t baud, int8_t protocol):
    serialNameStr(str),
    _baud(baud),
    _protocol(protocol)
{
    widgetInit();

    setCurrentBaud(baud);
    setCurrentProtocol(protocol);
}

void SerialConfigWidget::SerialConfigWidgetItem::setCurrentBaud(uint32_t baud)
{
    _baud = FlyLink::map_baudrate(baud);
    qDebug()<<"setCurrentBaud"<<baud<<_baud;
    int index = this->baudComboBox->findData(QVariant(_baud));
    if(index < 0){
        this->baudComboBox->addItem(QString::number(_baud),_baud);

    }
    this->baudComboBox->setCurrentIndex(this->baudComboBox->findData(QVariant(_baud)));
    this->baudComboBox->setChanged(false);
}

void SerialConfigWidget::SerialConfigWidgetItem::setCurrentProtocol(int8_t protocol)
{
    int index = this->protocalComboBox->findData(QVariant(protocol));
    qDebug()<<"setCurrentProtocol"<<index<<protocol;
    if(index < 0){
        this->protocalComboBox->setCurrentIndex(0);
    }
    else{
        this->protocalComboBox->setCurrentIndex(index);
    }
    this->protocalComboBox->setChanged(false);
}

uint32_t SerialConfigWidget::SerialConfigWidgetItem::getCurrentBaud()
{
    return this->baudComboBox->currentData().toUInt();
}

int8_t SerialConfigWidget::SerialConfigWidgetItem::getCurrentProtocol()
{
    return this->protocalComboBox->currentData().toInt();
}
void SerialConfigWidget::SerialConfigWidgetItem::widgetInit()
{
    if(this->nameLabel == nullptr){
        this->nameLabel = new QLabel(QStringLiteral("名称:"));
        this->nameLabel->setObjectName(QString::fromUtf8("CFGLabelPre"));
    }

    if(this->serialName == nullptr){
        this->serialName = new QLabel(this->serialNameStr);
        this->serialName->setObjectName(QString::fromUtf8("CFGLabelPre"));
    }

    QHBoxLayout *nameLayout = new QHBoxLayout;
//    nameLayout->addWidget(this->nameLabel);
    nameLayout->addWidget(this->serialName);
    nameLayout->setSpacing(2);
    nameLayout->setContentsMargins(10,2,20,2);

    if(this->baudNameLabel == nullptr){
        this->baudNameLabel = new QLabel(QStringLiteral("波特率:"));

        this->baudNameLabel->setObjectName(QString::fromUtf8("CFGLabelPre"));
    }

    if(this->baudComboBox == nullptr){
        this->baudComboBox = new UComboBox();
        this->baudComboBox->addItem("115200",115200);
        this->baudComboBox->addItem("57600",57600);
        this->baudComboBox->addItem("38400",38400);
        this->baudComboBox->addItem("9600",9600);
        this->baudComboBox->addItem("230400",230400);
        this->baudComboBox->setMinimumWidth(120);
        this->baudComboBox->setEditable(true);
    }

    QHBoxLayout *baudLayout = new QHBoxLayout;
    baudLayout->addWidget(this->baudNameLabel);
    baudLayout->addWidget(this->baudComboBox);
    baudLayout->setSpacing(2);
    baudLayout->setContentsMargins(10,2,10,2);

    if(this->protocalNameLabel == nullptr){
        this->protocalNameLabel = new QLabel(QStringLiteral("协议类型:"));

        this->protocalNameLabel->setObjectName(QString::fromUtf8("CFGLabelPre"));
    }

    if(this->protocalComboBox == nullptr){
        this->protocalComboBox = new UComboBox();
        this->protocalComboBox->setMinimumWidth(120);
        this->protocalComboBox->setEditable(false);
        //==================================
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_None),QVariant(FlyLink::SerialProtocol_None));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_FlyLink),QVariant(FlyLink::SerialProtocol_FlyLink));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_GPS),QVariant(FlyLink::SerialProtocol_GPS));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_GPS2),QVariant(FlyLink::SerialProtocol_GPS2));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_YJYSeeker),QVariant(FlyLink::SerialProtocol_YJYSeeker));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Console),QVariant(FlyLink::SerialProtocol_Console));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_MAVLink),QVariant(FlyLink::SerialProtocol_MAVLink));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_MAVLink2),QVariant(FlyLink::SerialProtocol_MAVLink2));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_FrSky_D),QVariant(FlyLink::SerialProtocol_FrSky_D));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_FrSky_SPort),QVariant(FlyLink::SerialProtocol_FrSky_SPort));

        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_AlexMos),QVariant(FlyLink::SerialProtocol_AlexMos));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_SToRM32),QVariant(FlyLink::SerialProtocol_SToRM32));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Rangefinder),QVariant(FlyLink::SerialProtocol_Rangefinder));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_FrSky_SPort_Passthrough),QVariant(FlyLink::SerialProtocol_FrSky_SPort_Passthrough));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Lidar360),QVariant(FlyLink::SerialProtocol_Lidar360));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Aerotenna_uLanding),QVariant(FlyLink::SerialProtocol_Aerotenna_uLanding));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Beacon),QVariant(FlyLink::SerialProtocol_Beacon));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Volz),QVariant(FlyLink::SerialProtocol_Volz));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Sbus1),QVariant(FlyLink::SerialProtocol_Sbus1));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_ESCTelemetry),QVariant(FlyLink::SerialProtocol_ESCTelemetry));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Devo_Telem),QVariant(FlyLink::SerialProtocol_Devo_Telem));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_OpticalFlow),QVariant(FlyLink::SerialProtocol_OpticalFlow));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Robotis),QVariant(FlyLink::SerialProtocol_Robotis));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_NMEAOutput),QVariant(FlyLink::SerialProtocol_NMEAOutput));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_WindVane),QVariant(FlyLink::SerialProtocol_WindVane));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_SLCAN),QVariant(FlyLink::SerialProtocol_SLCAN));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_RCIN),QVariant(FlyLink::SerialProtocol_RCIN));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_EFI_MS),QVariant(FlyLink::SerialProtocol_EFI_MS));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_LTM_Telem),QVariant(FlyLink::SerialProtocol_LTM_Telem));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_RunCam),QVariant(FlyLink::SerialProtocol_RunCam));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Hott),QVariant(FlyLink::SerialProtocol_Hott));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Scripting),QVariant(FlyLink::SerialProtocol_Scripting));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_CRSF),QVariant(FlyLink::SerialProtocol_CRSF));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Generator),QVariant(FlyLink::SerialProtocol_Generator));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_Winch),QVariant(FlyLink::SerialProtocol_Winch));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_MSP),QVariant(FlyLink::SerialProtocol_MSP));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_DJI_FPV),QVariant(FlyLink::SerialProtocol_DJI_FPV));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_AirSpeed),QVariant(FlyLink::SerialProtocol_AirSpeed));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_ADSB),QVariant(FlyLink::SerialProtocol_ADSB));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_AHRS),QVariant(FlyLink::SerialProtocol_AHRS));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_SmartAudio),QVariant(FlyLink::SerialProtocol_SmartAudio));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_FETtecOneWire),QVariant(FlyLink::SerialProtocol_FETtecOneWire));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_INS_Telem),QVariant(FlyLink::SerialProtocol_INS_Telem));
        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_NumProtocols),QVariant(FlyLink::SerialProtocol_NumProtocols));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_XYFly),QVariant(FlyLink::SerialProtocol_XYFly));
//        this->protocalComboBox->addItem(FlyLink::getSerialProtocolString(FlyLink::SerialProtocol_OpenLink),QVariant(FlyLink::SerialProtocol_OpenLink));

    }

    QHBoxLayout *protocalLayout = new QHBoxLayout;
    protocalLayout->addWidget(this->protocalNameLabel);
    protocalLayout->addWidget(this->protocalComboBox);
    protocalLayout->setSpacing(2);
    protocalLayout->setContentsMargins(10,2,20,2);


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QHBoxLayout();
    }
    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding));
    this->widgetLayout->addLayout(nameLayout);
    this->widgetLayout->addLayout(baudLayout);
    this->widgetLayout->addLayout(protocalLayout);
    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding));

    this->widgetLayout->setContentsMargins(10,20,10,20);
    this->setLayout(this->widgetLayout);

}

SerialConfigWidget::SerialConfigWidget()
{
    this->setObjectName(QString::fromUtf8("actionWidget"));
}

void SerialConfigWidget::clearSerialConfigWidget()
{
    this->clear();
    QMap<QString,SerialConfigWidgetItem *>::Iterator iter = this->serialConfigItemMap.begin();
    while(iter != this->serialConfigItemMap.end()){
        if(iter.value() != nullptr){
            iter.value()->deleteLater();
        }
        iter ++;
    }

    this->serialConfigItemMap.clear();

}


void SerialConfigWidget::connectSignalAndSlot()
{

}

void SerialConfigWidget::addItemWidget(QString name, uint32_t baud, int8_t protocol)
{
    if(serialConfigItemMap.contains(name)){
        SerialConfigWidgetItem *widget = serialConfigItemMap.find(name).value();
        widget->setCurrentBaud(baud);
        widget->setCurrentProtocol(protocol);
        return;
    }

    SerialConfigWidgetItem *widget = new SerialConfigWidgetItem(name,baud,protocol);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(widget->sizeHint());
    this->addItem(item);
    this->setItemWidget(item,widget);
    this->serialConfigItemMap.insert(name,widget);
}

bool SerialConfigWidget::getItemWidgetInfo(QString name, uint32_t &baud, int8_t &protocol)
{
    if(serialConfigItemMap.isEmpty()){
        return false;
    }
    if(!serialConfigItemMap.contains(name)){
        return false;
    }
    SerialConfigWidgetItem* widget = serialConfigItemMap.find(name).value();
    baud = widget->getCurrentBaud();
    protocol = widget->getCurrentProtocol();
    return true;
}

int SerialConfigWidget::getItemWidgeCount()
{
    return serialConfigItemMap.count();
}

