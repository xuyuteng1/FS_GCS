#include "toolwidget.h"

ToolWidget::ToolWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void ToolWidget::widgetInit()
{
    if(this->switchViewButton == nullptr){
        this->switchViewButton = new QPushButton();
        this->switchViewButton->setIconSize(QSize(32,32));
        this->switchViewButton->setToolTip(QStringLiteral("切换视场"));
        this->switchViewButton->setIcon(QIcon(":/img/switchView.png"));
        this->switchViewButton->setObjectName("ToolButton");
    }
    if(this->overlayVideoButton == nullptr){
        this->overlayVideoButton = new QPushButton();
        this->overlayVideoButton->setIconSize(QSize(32,32));
        this->overlayVideoButton->setToolTip(QStringLiteral("画中画"));
        this->overlayVideoButton->setIcon(QIcon(":/img/overlayVideo.png"));
        this->overlayVideoButton->setObjectName("ToolButton");
    }
    if(this->lockButton == nullptr){
        this->lockButton = new QPushButton();
        this->lockButton->setIconSize(QSize(32,32));
        this->lockButton->setToolTip(QStringLiteral("锁定"));
        this->lockButton->setIcon(QIcon(":/img/lock.png"));
        this->lockButton->setObjectName("ToolButton");
//        this->lockButton->setCheckable(true);
    }
    if(this->swicthSensor == nullptr){
        this->swicthSensor = new QPushButton();
        this->swicthSensor->setIconSize(QSize(32,32));
        this->swicthSensor->setToolTip(QStringLiteral("切換传感器"));
        this->swicthSensor->setIcon(QIcon(":/img/swicthSensor.png"));
        this->swicthSensor->setObjectName("ToolButton");
    }
    if(this->target_Cross == nullptr){
        this->target_Cross = new QPushButton();
        this->target_Cross->setIconSize(QSize(32,32));
        this->target_Cross->setToolTip(QStringLiteral("靶型选择(十字靶标)"));
        this->target_Cross->setIcon(QIcon(":/img/target_Cross.png"));
        this->target_Cross->setObjectName("ToolButton");
        this->target_Cross->setCheckable(true);
    }
    if(this->target_General == nullptr){
        this->target_General = new QPushButton();
        this->target_General->setIconSize(QSize(32,32));
        this->target_General->setToolTip(QStringLiteral("靶型选择(通用目标)"));
        this->target_General->setIcon(QIcon(":/img/target_General.png"));
        this->target_General->setObjectName("ToolButton");
        this->target_General->setCheckable(true);
    }
    if(this->target_Car == nullptr){
        this->target_Car = new QPushButton();
        this->target_Car->setIconSize(QSize(32,32));
        this->target_Car->setToolTip(QStringLiteral("靶型选择(车辆)"));
        this->target_Car->setIcon(QIcon(":/img/target_Car.png"));
        this->target_Car->setObjectName("ToolButton");
        this->target_Car->setCheckable(true);
    }

    if( this->SerialPortOpen == nullptr){
        this->SerialPortOpen = new QPushButton();
        this->SerialPortOpen->setIconSize(QSize(32,32));
        this->SerialPortOpen->setToolTip(QStringLiteral("串口通信测试"));
        this->SerialPortOpen->setIcon(QIcon(":/img/serialport.png"));
        this->SerialPortOpen->setObjectName("ToolButton");
//        this->SerialPortOpen->setCheckable(true);
    }
    if( this->SocketUDPOpen == nullptr){
        this->SocketUDPOpen = new QPushButton();
        this->SocketUDPOpen->setIconSize(QSize(32,32));
        this->SocketUDPOpen->setToolTip(QStringLiteral("UDP组播通信测试"));
        this->SocketUDPOpen->setIcon(QIcon(":/img/network.png"));
        this->SocketUDPOpen->setObjectName("ToolButton");
//        this->SocketUDPOpen->setCheckable(true);
    }


    if(this->targetButtonGroup == nullptr){
        this->targetButtonGroup = new QButtonGroup(this);
    }

    this->targetButtonGroup->addButton(this->target_Cross);
    this->targetButtonGroup->addButton(this->target_General);
    this->targetButtonGroup->addButton(this->target_Car);

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addWidget(this->switchViewButton,0,0,1,1);
    this->widgetLayout->addWidget(this->overlayVideoButton,1,0,1,1);
    this->widgetLayout->addWidget(this->swicthSensor,2,0,1,1);
    this->widgetLayout->addWidget(this->lockButton,3,0,1,1);
    this->widgetLayout->addWidget(this->target_Cross,4,0,1,1);
    this->widgetLayout->addWidget(this->target_General,5,0,1,1);
    this->widgetLayout->addWidget(this->target_Car,6,0,1,1);
    this->widgetLayout->addWidget(this->SerialPortOpen,7,0,1,1);
    this->widgetLayout->addWidget(this->SocketUDPOpen,8,0,1,1);

    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum),0,1,1,1);

    this->setLayout(this->widgetLayout);

    this->widgetLayout->setSpacing(1);
    this->widgetLayout->setMargin(0);

    this->setMaximumWidth(200);
}

void ToolWidget::connectSignalAndSlot()
{
    connect(this->switchViewButton,&QPushButton::pressed,this,&ToolWidget::switchViewButtonPressedSignal);
    connect(this->overlayVideoButton,&QPushButton::pressed,this,&ToolWidget::overlayVideoButtonPressedSignal);
    connect(this->lockButton,&QPushButton::pressed,this,&ToolWidget::lockButtonPressedSignal);
    connect(this->swicthSensor,&QPushButton::pressed,this,&ToolWidget::swicthSensorPressedSignal);
    connect(this->target_Cross,&QPushButton::pressed,this,&ToolWidget::target_CrossPressedSignal);
    connect(this->target_General,&QPushButton::pressed,this,&ToolWidget::target_GeneralPressedSignal);
    connect(this->target_Car,&QPushButton::pressed,this,&ToolWidget::target_CarPressedSignal);
    connect(this->SerialPortOpen,&QPushButton::pressed,this,&ToolWidget::SerialPortOpenPressedSignal);
    connect(this->SocketUDPOpen,&QPushButton::pressed,this,&ToolWidget::SocketUDPOpenPressedSignal);


    connect(this->lockButton,&QPushButton::pressed,[=]{
        this->lockButton->setIcon(this->lockButton->isChecked() ? QIcon(":/img/lock.png"):QIcon(":/img/unlock.png"));
    });
}

void ToolWidget::lockedStatusChangedSlot(bool status)
{
    this->lockButton->setChecked(status);
}
