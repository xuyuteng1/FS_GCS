#include "C_LandWidget.h"
#include "DMMM.h"

C_LandWidget::C_LandWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void C_LandWidget::widgetInit()
{
    if(this->rtlAction == nullptr){
        this->rtlAction = new QPushButton(QStringLiteral("返航模式"));
        this->rtlAction->setObjectName("WidgetCMD_Action");
    }

    if(this->smartRtlAction == nullptr){
        this->smartRtlAction = new QPushButton(QStringLiteral("智能返航"));
        this->smartRtlAction->setObjectName("WidgetCMD_Action");
    }

    if(this->landAction == nullptr){
        this->landAction = new QPushButton(QStringLiteral("降落模式"));
        this->landAction->setObjectName("WidgetCMD_Action");
    }


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,1,1);
    this->widgetLayout->addWidget(this->rtlAction,0,1,1,1);
    this->widgetLayout->addWidget(this->smartRtlAction,0,2,1,1);
    this->widgetLayout->addWidget(this->landAction,0,3,1,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,4,1,1);

    this->setLayout(this->widgetLayout);

}

void C_LandWidget::rtlActionTargetSlot()
{
    set_mode(FlyLink::RTL);
}

void C_LandWidget::smartRtlActionTargetSlot()
{
    set_mode(FlyLink::SMART_RTL);
}

void C_LandWidget::landActionTargetSlot()
{
    set_mode(FlyLink::LAND);
}



void C_LandWidget::connectSignalAndSlot()
{
    connect(this->rtlAction,&QPushButton::pressed,this,&C_LandWidget::rtlActionTargetSlot);
    connect(this->smartRtlAction,&QPushButton::pressed,this,&C_LandWidget::smartRtlActionTargetSlot);
    connect(this->landAction,&QPushButton::pressed,this,&C_LandWidget::landActionTargetSlot);
}

void C_LandWidget::set_mode(uint8_t mode_number)
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->set_mode(mode_number);
        }
    }
}
