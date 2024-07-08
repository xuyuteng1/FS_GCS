#include "sidebar_monitor.h"
#include <QGraphicsView>
SideBarMonitor::SideBarMonitor()
{
    init();
}

QGridLayout *SideBarMonitor::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarMonitor::init()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }

    if( this->lb_voltage_val[0] == nullptr){
        this->lb_voltage_val[0] = new QLabel(QStringLiteral("0.00V"));
        this->lb_voltage_val[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb_voltage_val[0]->setAlignment(Qt::AlignCenter);
        this->lb_voltage_val[0]->setToolTip(QStringLiteral("外置电压检测口1电压值"));
    }
    if( this->lb_voltage_val[1] == nullptr){
        this->lb_voltage_val[1] = new QLabel(QStringLiteral("0.00V"));
        this->lb_voltage_val[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb_voltage_val[1]->setAlignment(Qt::AlignCenter);
        this->lb_voltage_val[1]->setToolTip(QStringLiteral("外置电压检测口2电压值"));
    }

    if( this->lb_voltage[0] == nullptr){
        this->lb_voltage[0] = new QLabel();
        this->lb_voltage[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb_voltage[0]->setFixedSize(22,30);
        this->lb_voltage[0]->setAlignment(Qt::AlignCenter);
        this->lb_voltage[0]->setToolTip(QStringLiteral("外置电压检测口1电压值"));
        QPixmap pix(":/img/png/extvol.png");

        pix = pix.scaled(lb_voltage[0]->width(),lb_voltage[0]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb_voltage[0]->setPixmap(pix);
    }
    if( this->lb_voltage[1] == nullptr){
        this->lb_voltage[1] = new QLabel();
        this->lb_voltage[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb_voltage[1]->setFixedSize(22,30);
        this->lb_voltage[1]->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/extvol.png");

        this->lb_voltage[1]->setToolTip(QStringLiteral("外置电压检测口2电压值"));
        pix = pix.scaled(lb_voltage[1]->width(),lb_voltage[1]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb_voltage[1]->setPixmap(pix);
    }
    if( this->lb_val[0] == nullptr){
        this->lb_val[0] = new QLabel(QStringLiteral("0"));
        this->lb_val[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[0]->setAlignment(Qt::AlignCenter);
        this->lb_val[0]->setToolTip(QStringLiteral("转速监测1,单位RPM"));
    }
    if( this->lb_val[1] == nullptr){
        this->lb_val[1] = new QLabel(QStringLiteral("0"));
        this->lb_val[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[1]->setAlignment(Qt::AlignCenter);
        this->lb_val[1]->setToolTip(QStringLiteral("转速监测2,单位RPM"));
    }

    if( this->lb[0] == nullptr){
        this->lb[0] = new QLabel();
        this->lb[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb[0]->setFixedSize(22,30);
        this->lb[0]->setAlignment(Qt::AlignCenter);
        this->lb[0]->setToolTip(QStringLiteral("转速监测1,单位RPM"));
        QPixmap pix(":/img/png/rpm.png");

        pix = pix.scaled(lb[0]->width(),lb[0]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[0]->setPixmap(pix);
    }
    if( this->lb[1] == nullptr){
        this->lb[1] = new QLabel();
        this->lb[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb[1]->setFixedSize(22,30);
        this->lb[1]->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/rpm.png");

        this->lb[1]->setToolTip(QStringLiteral("转速监测2,单位RPM"));
        pix = pix.scaled(lb[1]->width(),lb[1]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[1]->setPixmap(pix);
    }
    this->widgetLayout->addWidget(this->lb_voltage[0],0,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_voltage[1],0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_voltage_val[0],1,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_voltage_val[1],1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb[0],0,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb[1],0,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_val[0],1,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_val[1],1,3,1,1,Qt::AlignCenter);

    this->widgetLayout->setMargin(6);
    this->widgetLayout->setColumnStretch(0,5);
    this->widgetLayout->setColumnStretch(1,5);
    this->widgetLayout->setColumnStretch(2,5);
    this->widgetLayout->setColumnStretch(3,5);
}

void SideBarMonitor::update_val(float val1, float val2,float rpm1,float rpm2)
{
    this->lb_voltage_val[0]->setText(QString::number(val1,'f',2)+QStringLiteral("V"));
    this->lb_voltage_val[1]->setText(QString::number(val2,'f',2)+QStringLiteral("V"));
    this->lb_val[0]->setText(QString::number(rpm1,'f',0));//+QStringLiteral(" RPM"));
    this->lb_val[1]->setText(QString::number(rpm2,'f',0));//+QStringLiteral(" RPM"));
}
