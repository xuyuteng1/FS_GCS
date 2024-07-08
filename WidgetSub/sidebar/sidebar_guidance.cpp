#include "sidebar_guidance.h"
#include <QVariant>
SideBarGuidance::SideBarGuidance()
{
    initDesigner();
}

QGridLayout *SideBarGuidance::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarGuidance::initDesigner()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }
    if( this->LED_GuidanceDevice            == nullptr){
        this->LED_GuidanceDevice = new LightButton();
        this->LED_GuidanceDevice->setFixedSize(45,45);
        this->LED_GuidanceDevice->setGray();
    }
    if( this->lb_State == nullptr){
        this->lb_State = new QLabel(QStringLiteral("未知状态"));
        this->lb_State->setObjectName("SystemInfoWidgetLabel");
        this->lb_State->setAlignment(Qt::AlignCenter);
        this->lb_State->setToolTip(QStringLiteral("导引设备状态"));
    }
    if( this->lb_PitchErr == nullptr){
        this->lb_PitchErr = new QLabel(QStringLiteral("0°"));
        this->lb_PitchErr->setObjectName("SystemInfoWidgetLabel");
        this->lb_PitchErr->setAlignment(Qt::AlignCenter);
        this->lb_PitchErr->setToolTip(QStringLiteral("俯仰偏差"));
    }
    if( this->lb_YawErr == nullptr){
        this->lb_YawErr = new QLabel(QStringLiteral("0°"));
        this->lb_YawErr->setObjectName("SystemInfoWidgetLabel");
        this->lb_YawErr->setAlignment(Qt::AlignCenter);
        this->lb_YawErr->setToolTip(QStringLiteral("航向偏差"));
    }
    if( this->lb_TrackingResponsivity == nullptr){
        this->lb_TrackingResponsivity = new QLabel(QStringLiteral("10"));
        this->lb_TrackingResponsivity->setObjectName("SystemInfoWidgetLabel");
        this->lb_TrackingResponsivity->setAlignment(Qt::AlignCenter);
        this->lb_TrackingResponsivity->setToolTip(QStringLiteral("跟踪响应度"));
    }
    this->widgetLayout->addWidget(this->LED_GuidanceDevice,0,0,2,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_State,0,1,1,3,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_PitchErr,1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_YawErr,1,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_TrackingResponsivity,1,3,1,1,Qt::AlignCenter);

    this->widgetLayout->setMargin(3);
//    this->widgetLayout->setColumnStretch(0,5);
//    this->widgetLayout->setColumnStretch(1,3);
//    this->widgetLayout->setColumnStretch(2,3);
//    this->widgetLayout->setColumnStretch(3,3);
    this->widgetLayout->setRowMinimumHeight(0,30);
    this->widgetLayout->setRowMinimumHeight(1,30);
}

void SideBarGuidance::update_val(bool is_health, float pitch, float yaw, float TrackRes, QString state)
{
    if(is_health){
        this->LED_GuidanceDevice->setGreen();
    }else{
        this->LED_GuidanceDevice->setGray();
    }
    this->lb_State->setText(state);
    this->lb_PitchErr->setText("P:"+QString::number(pitch,10,0)+QStringLiteral("°"));
    this->lb_YawErr->setText("Y:"+QString::number(yaw,10,0)+QStringLiteral("°"));
    this->lb_TrackingResponsivity->setText(QString::number(TrackRes,10,0));
}



