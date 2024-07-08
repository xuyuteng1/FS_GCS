#include "P_Takeoff.h"
#include "DMMM.h"
P_CMD_Takeoff::P_CMD_Takeoff()
{
    widgetInit();
    connectSignalAndSlot();
}

void P_CMD_Takeoff::widgetInit()
{
    if( this->lb_TakeoffAction == nullptr){
        this->lb_TakeoffAction = new QLabel(QStringLiteral("起飞完成:"));
        this->lb_TakeoffAction->setAlignment(Qt::AlignCenter);
        this->lb_TakeoffAction->setObjectName("WidgetCMD");
    }

    if( this->cb_TakeoffAction == nullptr){
        this->cb_TakeoffAction = new QComboBox();
        this->cb_TakeoffAction->setEditable(false);
        this->cb_TakeoffAction->setObjectName("WidgetCMD");
        this->cb_TakeoffAction->addItem(QStringLiteral("无动作"),FlyLink::TAKEOFF_ACTION_NONE);
        this->cb_TakeoffAction->addItem(QStringLiteral("执行返航"),FlyLink::TAKEOFF_ACTION_RTL);
        this->cb_TakeoffAction->addItem(QStringLiteral("执行航线"),FlyLink::TAKEOFF_ACTION_MISSION);
    }



    if( this->btn_Takeoff == nullptr){
        this->btn_Takeoff = new QPushButton(QStringLiteral("立即起飞"));
        this->btn_Takeoff->setObjectName("WidgetCMD_Action");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addWidget(lb_TakeoffAction    ,1,0,1,1);
    this->widgetLayout->addWidget(cb_TakeoffAction    ,1,1,1,1);
    this->widgetLayout->addWidget(btn_Takeoff    ,2,0,1,2);



    this->widgetLayout->setSpacing(5);
    this->widgetLayout->setContentsMargins(120,30,120,30);
    this->setLayout(this->widgetLayout);

}

void P_CMD_Takeoff::connectSignalAndSlot()
{
    connect(this->btn_Takeoff,&QPushButton::released,this,&P_CMD_Takeoff::handle_Takeoff);
}

void P_CMD_Takeoff::handle_Takeoff()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->do_PlaneTakeoff(cb_TakeoffAction->currentData().toInt());
    }
}
