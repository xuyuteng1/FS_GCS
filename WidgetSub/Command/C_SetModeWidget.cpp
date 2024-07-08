#include "C_SetModeWidget.h"
#include "DMMM.h"



C_SetModeWidget::C_SetModeWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void C_SetModeWidget::widgetInit()
{
    if(this->stabilizeAction == nullptr){
        this->stabilizeAction = new QPushButton(QStringLiteral("自稳模式"));
        this->stabilizeAction->setObjectName("WidgetCMD_Action");
    }
    if(this->altHoldAction == nullptr){
        this->altHoldAction = new QPushButton(QStringLiteral("定高模式"));
        this->altHoldAction->setObjectName("WidgetCMD_Action");
    }
    if(this->loiterAction == nullptr){
        this->loiterAction = new QPushButton(QStringLiteral("悬停模式"));
        this->loiterAction->setObjectName("WidgetCMD_Action");
    }
    if(this->posHoldAction == nullptr){
        this->posHoldAction = new QPushButton(QStringLiteral("位置模式"));
        this->posHoldAction->setObjectName("WidgetCMD_Action");
    }
    if(this->guidedAction == nullptr){
        this->guidedAction = new QPushButton(QStringLiteral("引导模式"));
        this->guidedAction->setObjectName("WidgetCMD_Action");
    }
    if(this->breakAction == nullptr){
        this->breakAction = new QPushButton(QStringLiteral("刹车模式"));
        this->breakAction->setObjectName("WidgetCMD_Action");
    }
    if(this->autoAction == nullptr){
        this->autoAction = new QPushButton(QStringLiteral("任务模式"));
        this->autoAction->setObjectName("WidgetCMD_Action");
    }
    if(this->circleAction == nullptr){
        this->circleAction = new QPushButton(QStringLiteral("绕圈模式"));
        this->circleAction->setObjectName("WidgetCMD_Action");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,1,1);
    this->widgetLayout->addWidget(this->stabilizeAction             ,0,1,1,1);
    this->widgetLayout->addWidget(this->altHoldAction               ,0,2,1,1);
    this->widgetLayout->addWidget(this->loiterAction                  ,0,3,1,1);
    this->widgetLayout->addWidget(this->posHoldAction              ,0,4,1,1);
    this->widgetLayout->addWidget(this->guidedAction                ,1,1,1,1);
    this->widgetLayout->addWidget(this->breakAction                  ,1,2,1,1);
    this->widgetLayout->addWidget(this->autoAction                    ,1,3,1,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,5,1,1);
//    this->addWidget(this->circleAction                   ,0,7,1,1);

    this->widgetLayout->setSpacing(2);
    this->widgetLayout->setContentsMargins(10,30,10,20);
    this->setLayout(this->widgetLayout);
}

void C_SetModeWidget::connectSignalAndSlot()
{
    connect(this->stabilizeAction,&QPushButton::pressed,this,&C_SetModeWidget::stabilizeActionTargetSlot);
    connect(this->altHoldAction,&QPushButton::pressed,this,&C_SetModeWidget::altHoldActionTargetSlot);
    connect(this->loiterAction,&QPushButton::pressed,this,&C_SetModeWidget::loiterActionTargetSlot);
    connect(this->posHoldAction,&QPushButton::pressed,this,&C_SetModeWidget::posHoldActionTargetSlot);
    connect(this->guidedAction,&QPushButton::pressed,this,&C_SetModeWidget::guidedActionTargetSlot);
    connect(this->breakAction,&QPushButton::pressed,this,&C_SetModeWidget::breakActionTargetSlot);
    connect(this->autoAction,&QPushButton::pressed,this,&C_SetModeWidget::autoActionTargetSlot);
}


void C_SetModeWidget::stabilizeActionTargetSlot()
{
    set_mode(FlyLink::STABILIZE);
}

void C_SetModeWidget::altHoldActionTargetSlot()
{
    set_mode(FlyLink::ALT_HOLD);
}

void C_SetModeWidget::loiterActionTargetSlot()
{
    set_mode(FlyLink::LOITER);
}

void C_SetModeWidget::posHoldActionTargetSlot()
{
    set_mode(FlyLink::POSHOLD);
}

void C_SetModeWidget::guidedActionTargetSlot()
{
    set_mode(FlyLink::GUIDED);
}

void C_SetModeWidget::breakActionTargetSlot()
{
    set_mode(FlyLink::BRAKE);
}

void C_SetModeWidget::autoActionTargetSlot()
{
    set_mode(FlyLink::AUTO);
}

void C_SetModeWidget::circleActionTargetSlot()
{
    set_mode(FlyLink::CIRCLE);
}

void C_SetModeWidget::set_mode(uint8_t mode_number)
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->set_mode(mode_number);
        }
    }
}

