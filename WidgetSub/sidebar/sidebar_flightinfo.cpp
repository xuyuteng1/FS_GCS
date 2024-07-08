#include "sidebar_flightinfo.h"
#include <QVariant>
SideBarFlightInfo::SideBarFlightInfo()
{
    initDesigner();
}

QGridLayout *SideBarFlightInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarFlightInfo::initDesigner()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }
    if(this->disLayout == nullptr){
        this->disLayout = new QHBoxLayout();
        this->disLayout->setSpacing(0);
        this->disLayout->setMargin(0);
    }

    if(this->timeLayout == nullptr){
        this->timeLayout = new QHBoxLayout();
        this->timeLayout->setSpacing(0);
        this->timeLayout->setMargin(0);
    }
    if(this->throttle == nullptr){
        this->throttle = new GaugeRange();
        this->throttle->setObjectName(QString::fromUtf8("gaugeRange1"));
        this->throttle->setProperty("usedColor", QVariant(QColor(15, 185, 112)));
        this->throttle->setProperty("freeColor", QVariant(QColor(200, 200, 200)));
        this->throttle->setProperty("textColor", QVariant(QColor(255, 255, 255)));
        this->throttle->setProperty("rangeTextColor", QVariant(QColor(0, 255, 255)));
        this->throttle->setRange(0,100);
        this->throttle->setLeftValue(0);
        this->throttle->setRightValue(0);
        this->throttle->setUnit("%");
        this->throttle->setToolTip(QStringLiteral("当前油门输出值"));
    }

    if(this->lb_temperature == nullptr){
        this->lb_temperature = new QLabel(QStringLiteral("0℃"));
        this->lb_temperature->setObjectName("SystemInfoWidgetLabel");
        this->lb_temperature->setAlignment(Qt::AlignCenter);
        this->lb_temperature->setToolTip(QStringLiteral("飞控温度"));

    }
    if(this->lb_flytime == nullptr){
        this->lb_flytime = new QLabel(QStringLiteral("00:00:00"));
        this->lb_flytime->setObjectName("SystemInfoWidgetLabel");
        this->lb_flytime->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
        this->lb_flytime->setToolTip(QStringLiteral("本次飞行时间"));
    }
    if(this->lb_flydis == nullptr){
        this->lb_flydis = new QLabel(QStringLiteral("0 km"));
        this->lb_flydis->setObjectName("SystemInfoWidgetLabel");
        this->lb_flydis->setAlignment(Qt::AlignLeft| Qt::AlignVCenter);
        this->lb_flydis->setToolTip(QStringLiteral("本次飞行距离"));
    }
    if(this->lb_flytime_icon == nullptr){
        this->lb_flytime_icon = new QLabel();
        this->lb_flytime_icon->setObjectName("SystemInfoWidgetLabel");
        this->lb_flytime_icon->setFixedSize(22,30);
        this->lb_flytime_icon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        QPixmap pix(":/img/png/flighttime.png");
        pix = pix.scaled(this->lb_flytime_icon->width(),this->lb_flytime_icon->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

        this->lb_flytime_icon->setPixmap(pix);
        this->lb_flytime_icon->setToolTip(QStringLiteral("本次飞行时间"));
    }

    if(this->lb_flydis_icon == nullptr){
        this->lb_flydis_icon = new QLabel();
        this->lb_flydis_icon->setObjectName("SystemInfoWidgetLabel");
        this->lb_flydis_icon->setFixedSize(22,30);
        this->lb_flydis_icon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        QPixmap pix(":/img/png/mileage.png");
        pix = pix.scaled(this->lb_flydis_icon->width(),this->lb_flydis_icon->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb_flydis_icon->setPixmap(pix);
        this->lb_flydis_icon->setToolTip(QStringLiteral("本次飞行距离"));
    }


    if(this->lb_state == nullptr){
        this->lb_state = new QLabel(QStringLiteral("地面"));
        this->lb_state->setObjectName("SystemInfoWidgetLabel");
        this->lb_state->setAlignment(Qt::AlignCenter);
        this->lb_state->setToolTip(QStringLiteral("飞行器电机解锁状态"));
    }

    this->timeLayout->addWidget(this->lb_flytime_icon,Qt::AlignCenter);
    this->timeLayout->addWidget(this->lb_flytime,Qt::AlignCenter);


    this->disLayout->addWidget(this->lb_flydis_icon,Qt::AlignCenter);
    this->disLayout->addWidget(this->lb_flydis,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->throttle,0,0,2,1);
    this->widgetLayout->addWidget(this->lb_state,0,1,2,1);
    this->widgetLayout->addWidget(this->lb_temperature,0,2,2,1);
    this->widgetLayout->addLayout(this->timeLayout,0,3,1,2);
    this->widgetLayout->addLayout(this->disLayout,1,3,1,2);



    this->widgetLayout->setMargin(6);
    this->widgetLayout->setColumnStretch(0,5);
    this->widgetLayout->setColumnStretch(1,3);
    this->widgetLayout->setColumnStretch(2,3);
    this->widgetLayout->setColumnStretch(3,5);
}

void SideBarFlightInfo::update_val(int thr, float temp, qint64 flytime, qint64 flydis, bool arm, bool fly)
{
    this->throttle->setRightValue(qMin(thr,100));
    this->throttle->setCurrentValue(qMin(thr,100));
    if(arm && fly){
        this->lb_state->setText(QStringLiteral("飞行"));
    }else if(arm && !fly){
        this->lb_state->setText(QStringLiteral("地面"));
    }else{
        this->lb_state->setText(QStringLiteral("锁定"));
    }

    this->lb_temperature->setText(QString::number(temp,'f',1)+QStringLiteral("℃"));
    this->lb_flydis->setText(QString::number(flydis/1000.0f,'f',2)+QStringLiteral(" km"));
    this->lb_flytime->setText(QString::asprintf("%02d:%02d:%02d",flytime/3600,flytime%3600/60,flytime%60));
}


