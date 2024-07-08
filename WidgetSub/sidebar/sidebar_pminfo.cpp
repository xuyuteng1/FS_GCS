#include "sidebar_pminfo.h"
#include <QGraphicsView>
SideBarPMInfo::SideBarPMInfo()
{
    initPowerDesigner();
}

QGridLayout *SideBarPMInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarPMInfo::initPowerDesigner()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }

    if(this->battry == nullptr){
        this->battry = new Battery();
        this->battry->setFixedSize(50,30);
        this->battry->setAlarmValue(25);
        this->battry->setValue(this->battry->getAlarmValue());
        this->battry->setToolTip(QStringLiteral("飞行器供电状态及预估百分比值"));
    }

    if(this->lb_voltage == nullptr){
        this->lb_voltage = new QLabel(QStringLiteral("0.0V"));
        this->lb_voltage->setObjectName("SideBarPMInfoLabel");
        this->lb_voltage->setAlignment(Qt::AlignCenter);
        this->lb_voltage->setToolTip(QStringLiteral("飞行器当前电压"));
    }
    if(this->lb_cureent == nullptr){
        this->lb_cureent = new QLabel(QStringLiteral("0.0A"));
        this->lb_cureent->setObjectName("SideBarPMInfoLabel");
        this->lb_cureent->setAlignment(Qt::AlignCenter);
        this->lb_cureent->setToolTip(QStringLiteral("飞行器当前电流"));
    }

    this->widgetLayout->addWidget(this->battry,0,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_voltage,0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_cureent,0,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget(this->lb_throttle,0,3,1,1);
    this->widgetLayout->setMargin(6);
    this->widgetLayout->setColumnStretch(0,5);
    this->widgetLayout->setColumnStretch(1,5);
    this->widgetLayout->setColumnStretch(2,5);
    this->widgetLayout->setRowMinimumHeight(0,40);
}

void SideBarPMInfo::update_val(bool state, float vol, float cureent,bool bat_usepercent,uint8_t per)
{
    if(!bat_usepercent){
        if(state){
            this->battry->setValue(this->battry->getMaxValue());
        }
        else{
            this->battry->setValue(this->battry->getAlarmValue());
        }
    }
    else{
        this->battry->setValue(per);
    }

    this->lb_voltage->setText(QString::asprintf("%.2fV",vol));
    this->lb_cureent->setText(QString::asprintf("%.2fA",cureent));
}
