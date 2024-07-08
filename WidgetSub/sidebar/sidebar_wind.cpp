#include "sidebar_wind.h"
#include <QVariant>
#include "DMMM.h"
SideBarWindInfo::SideBarWindInfo()
{
    initDesigner();
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&SideBarWindInfo::handle_DMMM_event);
}

QGridLayout *SideBarWindInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarWindInfo::initDesigner()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }

    if( this->lb_wind_dir == nullptr){
        this->lb_wind_dir = new QLabel(QStringLiteral("0°"));
        this->lb_wind_dir->setObjectName("SystemInfoWidgetLabel");
        this->lb_wind_dir->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
        this->lb_wind_dir->setToolTip(QStringLiteral("风向信息"));
    }
    if( this->lb_wind_speed == nullptr){
        this->lb_wind_speed = new QLabel(QStringLiteral("0 m/s"));
        this->lb_wind_speed->setObjectName("SystemInfoWidgetLabel");
        this->lb_wind_speed->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
        this->lb_wind_speed->setToolTip(QStringLiteral("风速"));
    }
    if( this->lb_wind_speed_z == nullptr){
        this->lb_wind_speed_z = new QLabel(QStringLiteral("0 m/s"));
        this->lb_wind_speed_z->setObjectName("SystemInfoWidgetLabel");
        this->lb_wind_speed_z->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
        this->lb_wind_speed_z->setToolTip(QStringLiteral("垂直风速"));
    }

    if( this->lb_icon_wind_dir == nullptr){
        this->lb_icon_wind_dir = new QLabel();
        this->lb_icon_wind_dir->setObjectName("SystemInfoWidgetLabel");
        this->lb_icon_wind_dir->setFixedSize(22,30);
        this->lb_icon_wind_dir->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        QPixmap pix(":/img/png/wind/dir.png");
        pix = pix.scaled(this->lb_icon_wind_dir->width(),this->lb_icon_wind_dir->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

        this->lb_icon_wind_dir->setPixmap(pix);
        this->lb_icon_wind_dir->setToolTip(QStringLiteral("风向"));
    }
    if( this->lb_icon_wind_speed == nullptr){
        this->lb_icon_wind_speed = new QLabel();
        this->lb_icon_wind_speed->setObjectName("SystemInfoWidgetLabel");
        this->lb_icon_wind_speed->setFixedSize(22,30);
        this->lb_icon_wind_speed->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        QPixmap pix(":/img/png/wind/speed.png");
        pix = pix.scaled(this->lb_icon_wind_speed->width(),this->lb_icon_wind_speed->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

        this->lb_icon_wind_speed->setPixmap(pix);
        this->lb_icon_wind_speed->setToolTip(QStringLiteral("风速"));
    }

    if( this->lb_icon_wind_speed_z == nullptr){
        this->lb_icon_wind_speed_z = new QLabel();
        this->lb_icon_wind_speed_z->setObjectName("SystemInfoWidgetLabel");
        this->lb_icon_wind_speed_z->setFixedSize(22,30);
        this->lb_icon_wind_speed_z->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        QPixmap pix(":/img/png/wind/speed_z.png");
        pix = pix.scaled(this->lb_icon_wind_speed_z->width(),this->lb_icon_wind_speed_z->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

        this->lb_icon_wind_speed_z->setPixmap(pix);
        this->lb_icon_wind_speed_z->setToolTip(QStringLiteral("垂直风速"));
    }
    this->widgetLayout->addWidget(this->lb_wind_dir ,               1,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_wind_speed ,             1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_wind_speed_z ,           1,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_icon_wind_dir ,          0,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_icon_wind_speed ,        0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_icon_wind_speed_z ,      0,2,1,1,Qt::AlignCenter);

    this->widgetLayout->setMargin(6);
}

void SideBarWindInfo::update_val(float wind_dir, float wind_speed, float wind_speed_z)
{
    this->lb_wind_dir->setText(QString::number(wind_dir,'f',0)+QStringLiteral(" °"));
    this->lb_wind_speed->setText(QString::number(wind_speed,'f',1)+QStringLiteral(" m/s"));
    this->lb_wind_speed_z->setText(QString::number(wind_speed_z,'f',1)+QStringLiteral(" m/s"));
}

void SideBarWindInfo::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件

    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
    {
        Q_DMMM::DataPool_t data = Qt::DMMM()->getData_main();
        update_val(data.flylink.tVehicle.wind_dir,data.flylink.tVehicle.wind_spd*0.01f,data.flylink.tVehicle.wind_spd_z*0.01f);
    }break;
    default:break;
    }
}

