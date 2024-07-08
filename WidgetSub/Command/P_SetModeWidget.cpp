#include "P_SetModeWidget.h"
#include "DMMM.h"



P_SetModeWidget::P_SetModeWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void P_SetModeWidget::widgetInit()
{





    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if( this->Action_MANUAL == nullptr){
        this->Action_MANUAL = new QPushButton(QStringLiteral("P手动模式"));
        this->Action_MANUAL->setObjectName("WidgetCMD_Action");
        connect(this->Action_MANUAL,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_MANUAL);});
    }


    if( this->Action_STABILIZE == nullptr){
        this->Action_STABILIZE = new QPushButton(QStringLiteral("P自动平飞"));
        this->Action_STABILIZE->setObjectName("WidgetCMD_Action");
        connect(this->Action_STABILIZE,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_STABILIZE);});
    }


    if( this->Action_ACRO == nullptr){
        this->Action_ACRO = new QPushButton(QStringLiteral("P竞技模式"));
        this->Action_ACRO->setObjectName("WidgetCMD_Action");
        connect(this->Action_ACRO,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_ACRO);});
    }

    if( this->Action_TRAINING == nullptr){
        this->Action_TRAINING = new QPushButton(QStringLiteral("P训练模式"));
        this->Action_TRAINING->setObjectName("WidgetCMD_Action");
        connect(this->Action_TRAINING,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_TRAINING);});
    }
    if( this->Action_FLY_BY_WIRE_A == nullptr){
        this->Action_FLY_BY_WIRE_A = new QPushButton(QStringLiteral("P自稳模式"));
        this->Action_FLY_BY_WIRE_A->setObjectName("WidgetCMD_Action");
        connect(this->Action_FLY_BY_WIRE_A,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_FLY_BY_WIRE_A);});
    }

    if( this->Action_FLY_BY_WIRE_B == nullptr){
        this->Action_FLY_BY_WIRE_B = new QPushButton(QStringLiteral("P辅助(AS)"));
        this->Action_FLY_BY_WIRE_B->setObjectName("WidgetCMD_Action");
        connect(this->Action_FLY_BY_WIRE_B,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_FLY_BY_WIRE_B);});
    }
    if( this->Action_CRUISE == nullptr){
        this->Action_CRUISE = new QPushButton(QStringLiteral("P辅助(ASY)"));
        this->Action_CRUISE->setObjectName("WidgetCMD_Action");
        connect(this->Action_CRUISE,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_CRUISE);});
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    if( this->Action_CIRCLE == nullptr){
        this->Action_CIRCLE = new QPushButton(QStringLiteral("P绕圈模式"));
        this->Action_CIRCLE->setObjectName("WidgetCMD_Action");
        connect(this->Action_CIRCLE,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_CIRCLE);});
    }
    if( this->Action_AUTOTUNE == nullptr){
        this->Action_AUTOTUNE = new QPushButton(QStringLiteral("P自动调参"));
        this->Action_AUTOTUNE->setObjectName("WidgetCMD_Action");
        connect(this->Action_AUTOTUNE,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_AUTOTUNE);});
    }
    if( this->Action_AUTO == nullptr){
        this->Action_AUTO = new QPushButton(QStringLiteral("P任务模式"));
        this->Action_AUTO->setObjectName("WidgetCMD_Action");
        connect(this->Action_AUTO,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_AUTO);});
    }
    if( this->Action_RTL == nullptr){
        this->Action_RTL = new QPushButton(QStringLiteral("P返航模式"));
        this->Action_RTL->setObjectName("WidgetCMD_Action");
        connect(this->Action_RTL,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_RTL);});
    }
    if( this->Action_LOITER == nullptr){
        this->Action_LOITER = new QPushButton(QStringLiteral("P绕点模式"));
        this->Action_LOITER->setObjectName("WidgetCMD_Action");
        connect(this->Action_LOITER,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_LOITER);});
    }
    if( this->Action_TAKEOFF == nullptr){
        this->Action_TAKEOFF = new QPushButton(QStringLiteral("P自主起飞"));
        this->Action_TAKEOFF->setObjectName("WidgetCMD_Action");
        connect(this->Action_TAKEOFF,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_TAKEOFF);});
    }
    if( this->Action_GUIDED == nullptr){
        this->Action_GUIDED = new QPushButton(QStringLiteral("P引导模式"));
        this->Action_GUIDED->setObjectName("WidgetCMD_Action");
        connect(this->Action_GUIDED,&QPushButton::pressed,this,[=]{set_mode(FlyLink::PLANE_GUIDED);});
    }

    if(this->Layout_Box_Assi == nullptr){
        this->Layout_Box_Assi = new QGridLayout();
    }
    if(this->Layout_Box_Auto == nullptr){
        this->Layout_Box_Auto = new QGridLayout();
    }


    // 辅助模式
    this->Layout_Box_Assi->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,1,1);
    this->Layout_Box_Assi->addWidget(this->Action_FLY_BY_WIRE_A            ,0,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addWidget(this->Action_FLY_BY_WIRE_B            ,1,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addWidget(this->Action_CRUISE                   ,2,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addWidget(this->Action_TRAINING                 ,3,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,2,1,1);
    this->Layout_Box_Assi->addWidget(this->Action_MANUAL                   ,0,3,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addWidget(this->Action_STABILIZE                ,1,3,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addWidget(this->Action_ACRO                     ,2,3,1,1,Qt::AlignCenter);
    this->Layout_Box_Assi->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,4,1,1);
    this->Layout_Box_Assi->setSpacing(2);
    this->Layout_Box_Assi->setContentsMargins(10,5,10,5);

    // 自动模式
    this->Layout_Box_Auto->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,1,2);
    this->Layout_Box_Auto->addWidget(this->Action_AUTO                     ,0,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addWidget(this->Action_RTL                      ,1,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addWidget(this->Action_TAKEOFF                  ,2,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addWidget(this->Action_GUIDED                   ,3,1,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,2,1,1);
    this->Layout_Box_Auto->addWidget(this->Action_LOITER                   ,0,3,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addWidget(this->Action_CIRCLE                   ,1,3,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addWidget(this->Action_AUTOTUNE                 ,2,3,1,1,Qt::AlignCenter);
    this->Layout_Box_Auto->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,4,1,1);
    this->Layout_Box_Auto->setSpacing(2);
    this->Layout_Box_Auto->setContentsMargins(10,5,10,5);

    if(this->Box_Assi == nullptr){
        this->Box_Assi = new QGroupBox();
    }
    if(this->Box_Auto == nullptr){
        this->Box_Auto = new QGroupBox();
    }
    Box_Assi->setLayout(Layout_Box_Assi);
    Box_Auto->setLayout(Layout_Box_Auto);


    this->widgetLayout->addWidget(this->Box_Assi                     ,0,0,1,1);
    this->widgetLayout->addWidget(this->Box_Auto                     ,0,1,1,1);
    this->widgetLayout->setSpacing(2);
    this->widgetLayout->setContentsMargins(10,20,10,5);
    this->setLayout(this->widgetLayout);
}

void P_SetModeWidget::connectSignalAndSlot()
{

}


void P_SetModeWidget::set_mode(uint8_t mode_number)
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->set_mode(mode_number);
        }
    }
}

