#include "P_PreAction.h"
#include "DMMM.h"

WidgetPreAction::WidgetPreAction()
{
    widgetInit();
    connectSignalAndSlot();
}

void WidgetPreAction::widgetInit()
{

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if( this->Action_GyroCaliZero == nullptr){
        this->Action_GyroCaliZero = new QPushButton(QStringLiteral("陀螺清零"));
        this->Action_GyroCaliZero->setObjectName("WidgetCMD_Action");
        connect(this->Action_GyroCaliZero,&QPushButton::pressed,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();
                                                                         if(link){
                                                                             link->do_GyroCaliStart();
                                                                         }});
    }

    if( this->Action_BaroCaliZero == nullptr){
        this->Action_BaroCaliZero = new QPushButton(QStringLiteral("气压清零"));
        this->Action_BaroCaliZero->setObjectName("WidgetCMD_Action");
        connect(this->Action_BaroCaliZero,&QPushButton::pressed,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();
                                                                         if(link){
                                                                             link->do_BaroCaliStart();
                                                                         }});
    }

    if( this->Action_AirspeedCaliZero == nullptr){
        this->Action_AirspeedCaliZero = new QPushButton(QStringLiteral("空速清零"));
        this->Action_AirspeedCaliZero->setObjectName("WidgetCMD_Action");
        connect(this->Action_AirspeedCaliZero,&QPushButton::pressed,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();
                                                                         if(link){
                                                                             link->do_AirspeedCaliStart();
                                                                         }});
    }

    this->widgetLayout->addWidget(this->Action_GyroCaliZero                     ,0,0,1,1);
    this->widgetLayout->addWidget(this->Action_BaroCaliZero                     ,0,1,1,1);
    this->widgetLayout->addWidget(this->Action_AirspeedCaliZero                 ,0,2,1,1);
    this->widgetLayout->setSpacing(2);
    this->widgetLayout->setContentsMargins(10,20,10,5);
    this->setLayout(this->widgetLayout);
}

void WidgetPreAction::connectSignalAndSlot()
{

}
