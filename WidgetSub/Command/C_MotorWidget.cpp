#include "C_MotorWidget.h"
#include "DMMM.h"

C_MotorUnlockWidget::C_MotorUnlockWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void C_MotorUnlockWidget::widgetInit()
{
    if(this->motorUnlockAction == nullptr){
        this->motorUnlockAction = new QPushButton(QStringLiteral("电机解锁"));
        this->motorUnlockAction->setObjectName("WidgetCMD_Action");
    }

    if(this->motorLockAction == nullptr){
        this->motorLockAction = new QPushButton(QStringLiteral("电机锁定"));
        this->motorLockAction->setObjectName("WidgetCMD_Action");
    }

    if(this->motorUnlockForceAction == nullptr){
        this->motorUnlockForceAction = new QPushButton(QStringLiteral("强制解锁"));
        this->motorUnlockForceAction->setObjectName("WidgetCMD_ActionWarning");
    }

    if(this->motorLockForceAction == nullptr){
        this->motorLockForceAction = new QPushButton(QStringLiteral("强制锁定"));
        this->motorLockForceAction->setObjectName("WidgetCMD_ActionWarning");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,1,1);
    this->widgetLayout->addWidget(this->motorUnlockAction,0,1,1,1);
    this->widgetLayout->addWidget(this->motorLockAction,1,1,1,1);
    this->widgetLayout->addWidget(this->motorUnlockForceAction,0,2,1,1);
    this->widgetLayout->addWidget(this->motorLockForceAction,1,2,1,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,3,1,1);
    this->widgetLayout->setContentsMargins(10,30,10,20);

    this->setLayout(this->widgetLayout);

}

void C_MotorUnlockWidget::connectSignalAndSlot()
{
    connect(this->motorUnlockAction,&QPushButton::pressed,this,&C_MotorUnlockWidget::motorUnlockActionTargetSlot);
    connect(this->motorLockAction,&QPushButton::pressed,this,&C_MotorUnlockWidget::motorLockActionTargetSlot);
    connect(this->motorUnlockForceAction,&QPushButton::pressed,this,&C_MotorUnlockWidget::motorUnlockForceActionTargetSlot);
    connect(this->motorLockForceAction,&QPushButton::pressed,this,&C_MotorUnlockWidget::motorLockForceActionTargetSlot);
}


void C_MotorUnlockWidget::motorUnlockActionTargetSlot()
{
    set_motors(FlyLink::ARM_MOTERS);
}

void C_MotorUnlockWidget::motorLockActionTargetSlot()
{
    set_motors(FlyLink::DISARM_MOTORS);
}

void C_MotorUnlockWidget::motorUnlockForceActionTargetSlot()
{
    set_motors(FlyLink::ARM_MOTERS_FORCE);
}

void C_MotorUnlockWidget::motorLockForceActionTargetSlot()
{
    set_motors(FlyLink::DISARM_MOTORS_FORCE);
}
void C_MotorUnlockWidget::set_motors(uint8_t mode)
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        switch(mode){
        case FlyLink::ARM_MOTERS:
            link->set_motors_arm();
            break;
        case FlyLink::DISARM_MOTORS:
            link->set_motors_disarm();
            break;
        case FlyLink::ARM_MOTERS_FORCE:
            link->set_motors_force_arm();
            break;

        case FlyLink::DISARM_MOTORS_FORCE:
            link->set_motors_force_disarm();
            break;
        }
    }
}

