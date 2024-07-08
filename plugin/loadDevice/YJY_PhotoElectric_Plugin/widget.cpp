#include "widget.h"
#include "DMMM.h"
VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("YJY视频显示"));
    widgetInit();
    connectSignalAndSlot();

    qDebug()<<"VideoWidget::VideoWidget";
}

VideoWidget::~VideoWidget()
{
    this->player->videoStop();
}

void VideoWidget::widgetInit()
{

    if(this->player == nullptr){
        this->player = new VideoCodec();
//        this->player->photoelectricRunSlot();
    }

    if(this->statusWidget == nullptr){
        this->statusWidget = new StatusWidget();

    }

    if(this->toolWidget == nullptr){
        this->toolWidget = new ToolWidget();

    }

    if(this->handleWidget == nullptr){
        this->handleWidget = new HandleWidget();

    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();

    }

    this->widgetLayout->addWidget(this->videoWidget ,0,0,11,11);
    this->widgetLayout->addWidget(this->statusWidget ,0,0,2,2);
    this->widgetLayout->addWidget(this->toolWidget ,4,0,3,1);
    this->widgetLayout->addWidget(this->handleWidget ,8,9,3,2);

    this->widgetLayout->setMargin(0);
    this->widgetLayout->setSpacing(0);

    this->setLayout(this->widgetLayout);

    QFile file(QString(":/style/applicationStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void VideoWidget::connectSignalAndSlot()
{
    connect(this->toolWidget,&ToolWidget::switchViewButtonPressedSignal,this,&VideoWidget::switchViewButtonPressedSlot);
    connect(this->toolWidget,&ToolWidget::overlayVideoButtonPressedSignal,this,&VideoWidget::overlayVideoButtonPressedSlot);
    connect(this->toolWidget,&ToolWidget::lockButtonPressedSignal,this,&VideoWidget::lockButtonPressedSlot);
    connect(this->toolWidget,&ToolWidget::swicthSensorPressedSignal,this,&VideoWidget::swicthSensorPressedSlot);
    connect(this->toolWidget,&ToolWidget::target_CrossPressedSignal,this,&VideoWidget::target_CrossPressedSlot);
    connect(this->toolWidget,&ToolWidget::target_GeneralPressedSignal,this,&VideoWidget::target_GeneralPressedSlot);
    connect(this->toolWidget,&ToolWidget::target_CarPressedSignal,this,&VideoWidget::target_CarPressedSlot);
    connect(this->handleWidget,&HandleWidget::handleProcessValueChangedSignal,this,&VideoWidget::handleProcessValueChangedSlot);
    connect(this->toolWidget,&ToolWidget::SerialPortOpenPressedSignal,this,&VideoWidget::Slot_SerialPortOpenPressedSlot);
    connect(this->toolWidget,&ToolWidget::SocketUDPOpenPressedSignal,this,&VideoWidget::Slot_SocketUDPOpenPressedSlot);

//    connect(this->player,&VideoPlayer::mousePressedEventSignal,this,&VideoWidget::videoWidgetMousePressedSlot);
}

void VideoWidget::switchViewButtonPressedSlot()
{
//    Qt::DMMM()->getYJYPtl()->SendCMD_FieldViewSwitch();
}

void VideoWidget::overlayVideoButtonPressedSlot()
{
//    Qt::DMMM()->getYJYPtl()->SendCMD_P_in_PSwitch();
}

void VideoWidget::lockButtonPressedSlot()
{
    Qt::DMMM()->getYJYPtl()->SendCMD_LockTarget();
}

void VideoWidget::swicthSensorPressedSlot()
{
    Qt::DMMM()->getYJYPtl()->SendCMD_SensorSwitch();
}

void VideoWidget::target_CrossPressedSlot()
{
    Qt::DMMM()->getYJYPtl()->SendCMD_TargetTypePlus();
}

void VideoWidget::target_GeneralPressedSlot()
{
    Qt::DMMM()->getYJYPtl()->SendCMD_TargetTypeGeneral();
}

void VideoWidget::target_CarPressedSlot()
{

    Qt::DMMM()->getYJYPtl()->SendCMD_TargetTypeCar();
}

void VideoWidget::Slot_SerialPortOpenPressedSlot()
{
    emit Qt::DMMM()->getYJYPtl()->CloseProtocolDevice();
//    if(Qt::DMMM()->getYJYPtl()->getE_DeviceState() != YJYProtocol::DeviceState_Connect){
    QMap<QString,QVariant> param;
    param.clear();
    param[STR_SerialPort] = QVariant::fromValue(QString("COM3"));
    param[STR_SerialPort_baudRate] = QVariant::fromValue(qint32(230400));
    Qt::DMMM()->getYJYPtl()->OpenProtocolDevice(param);
//    }
//    else{
//        emit Qt::DMMM()->getYJYPtl()->CloseProtocolDevice();
//    }
}

void VideoWidget::Slot_SocketUDPOpenPressedSlot()
{
//    if(Qt::DMMM()->getYJYPtl()->getE_DeviceState() != YJYProtocol::DeviceState_Connect){
    emit Qt::DMMM()->getYJYPtl()->CloseProtocolDevice();
    QMap<QString,QVariant> param;
    param.clear();
    param[STR_SocketUDP] = QVariant::fromValue(QHostAddress("226.0.0.25"));
    param[STR_SocketUDP_Port] = QVariant::fromValue(6001);
    param[STR_SocketUDP_TargetIP] = QVariant::fromValue(QHostAddress("226.0.0.25"));
    param[STR_SocketUDP_TargetPort] = QVariant::fromValue(6000);
    emit Qt::DMMM()->getYJYPtl()->OpenProtocolDevice(param);
//    }
//    else{
//        emit Qt::DMMM()->getYJYPtl()->CloseProtocolDevice();
//    }
}

void VideoWidget::handleProcessValueChangedSlot(bool status, int x, int y)
{
    if(status){                             //微调模式
        Qt::DMMM()->getYJYPtl()->SendCMD_TrackPointRepair(x,y);
    }else{                                  //正常速度
        Qt::DMMM()->getYJYPtl()->SendCMD_GateWaveIncrement(x,y);
    }
}

void VideoWidget::videoWidgetMousePressedSlot(int x, int y)
{
    Qt::DMMM()->getYJYPtl()->SendCMD_GateWaveMovePos(x,y);
    qDebug()<<"videoWidgetMousePressedSlot:"<<x<<y;
}


