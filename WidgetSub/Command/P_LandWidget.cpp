#include "P_LandWidget.h"
#include "DMMM.h"

P_LandWidget::P_LandWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void P_LandWidget::widgetInit()
{

    if(this->landAction == nullptr){
        this->landAction = new QPushButton(QStringLiteral("立即降落"));
        this->landAction->setObjectName("WidgetCMD_Action");
    }
    if(this->goAround_Action == nullptr){
        this->goAround_Action = new QPushButton(QStringLiteral("立即复飞"));
        this->goAround_Action->setObjectName("WidgetCMD_ActionWarning");
    }

    if( this->goAroundAlt == nullptr){
        this->goAroundAlt = new QDoubleSpinBox;
        this->goAroundAlt->setDecimals(0);
        this->goAroundAlt->setMinimum(20);
        this->goAroundAlt->setMaximum(500);
        this->goAroundAlt->setValue(100);
        this->goAroundAlt->setObjectName("WidgetCMD");
    }
    if(this->goAroundAlt_name == nullptr){
        this->goAroundAlt_name = new QLabel(QStringLiteral("复飞高度"));
        this->goAroundAlt_name->setObjectName("WidgetCMD");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,2,1);
    this->widgetLayout->addWidget(this->landAction,0,1,1,3);
    this->widgetLayout->addWidget(this->goAroundAlt_name,   1,1,1,1);
    this->widgetLayout->addWidget(this->goAroundAlt,        1,2,1,1);
    this->widgetLayout->addWidget(this->goAround_Action,    1,3,1,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,4,2,1);

    this->setLayout(this->widgetLayout);

}

void P_LandWidget::landActionTargetSlot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_PlaneLand();
        }
    }
}


void P_LandWidget::goAroundActionTargetSlot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            float alt = goAroundAlt->value();
            link->do_PlaneGoAround(alt);
        }
    }
}



void P_LandWidget::connectSignalAndSlot()
{
    connect(this->goAround_Action,&QPushButton::pressed,this,&P_LandWidget::goAroundActionTargetSlot);
    connect(this->landAction,&QPushButton::pressed,this,&P_LandWidget::landActionTargetSlot);
}

