#include "sidebar_moveinfo.h"
#include <QGraphicsView>
#include <QVariant>
SideBarMoveInfo::SideBarMoveInfo()
{
    init();
}

QGridLayout *SideBarMoveInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarMoveInfo::init()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }

    if( this->lb_val[0] == nullptr){
        this->lb_val[0] = new QLabel(QStringLiteral("0 m/s"));
        this->lb_val[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[0]->setAlignment(Qt::AlignCenter);
        this->lb_val[0]->setToolTip(QStringLiteral("指示空速"));
    }
    if( this->lb_val[1] == nullptr){
        this->lb_val[1] = new QLabel(QStringLiteral("0 m/s"));
        this->lb_val[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[1]->setAlignment(Qt::AlignCenter);
        this->lb_val[1]->setToolTip(QStringLiteral("爬升速度"));
    }
    if( this->lb_val[2] == nullptr){
        this->lb_val[2] = new QLabel(QStringLiteral("0 米"));
        this->lb_val[2]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[2]->setAlignment(Qt::AlignCenter);
        this->lb_val[2]->setToolTip(QStringLiteral("相对高度"));
    }

    if( this->lb[0] == nullptr){
        this->lb[0] = new QLabel();
        this->lb[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb[0]->setFixedSize(22,30);
        this->lb[0]->setAlignment(Qt::AlignCenter);
        this->lb[0]->setToolTip(QStringLiteral("指示空速"));
        QPixmap pix(":/img/png/airspeed.png");

        pix = pix.scaled(lb[0]->width(),lb[0]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[0]->setPixmap(pix);
    }
    if( this->lb[1] == nullptr){
        this->lb[1] = new QLabel();
        this->lb[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb[1]->setFixedSize(22,30);
        this->lb[1]->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/up.png");

        this->lb[1]->setToolTip(QStringLiteral("爬升速度"));
        pix = pix.scaled(lb[1]->width(),lb[1]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[1]->setPixmap(pix);
    }
    if( this->lb[2] == nullptr){
        this->lb[2] = new QLabel();
        this->lb[2]->setObjectName("SystemInfoWidgetLabel");
        this->lb[2]->setFixedSize(22,30);
        this->lb[2]->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/relalt.png");

        this->lb[2]->setToolTip(QStringLiteral("相对高度"));
        pix = pix.scaled(lb[2]->width(),lb[2]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[2]->setPixmap(pix);
    }

    if(this->speed == nullptr){
        this->speed = new GaugeRange();
        this->speed->setObjectName(QString::fromUtf8("gaugeRange1"));
        this->speed->setProperty("usedColor", QVariant(QColor(15, 185, 112)));
        this->speed->setProperty("freeColor", QVariant(QColor(200, 200, 200)));
        this->speed->setProperty("textColor", QVariant(QColor(255, 255, 255)));
        this->speed->setProperty("rangeTextColor", QVariant(QColor(0, 255, 255)));
        this->speed->setRange(0,80);
        this->speed->setLeftValue(0);
        this->speed->setRightValue(0);
        this->speed->setUnit("");
        this->speed->setToolTip(QStringLiteral("水平移动速度:单位m/s"));
    }


    this->widgetLayout->addWidget(this->speed,0,0,2,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget(this->speedarc,0,0,2,1);
    this->widgetLayout->addWidget(this->lb[0],0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb[1],0,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb[2],0,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_val[0],1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_val[1],1,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_val[2],1,3,1,1,Qt::AlignCenter);


    this->widgetLayout->setMargin(6);
    this->widgetLayout->setColumnStretch(0,1);
    this->widgetLayout->setColumnStretch(1,1);
    this->widgetLayout->setColumnStretch(2,1);
    this->widgetLayout->setColumnStretch(3,1);
}

void SideBarMoveInfo::update_val(float val1, float val2 ,float val3 ,float val4)
{
    this->lb_val[0]->setText(QString::number(val4,'f',1)+QStringLiteral(" m/s"));

    this->lb_val[1]->setText(QString::number(val2,'f',1)+QStringLiteral(" m/s"));

    this->lb_val[2]->setText(QString::number(val3,'f',1)+QStringLiteral(" 米"));
    this->speed->setRightValue(qMin((int)val1,100));
    this->speed->setCurrentValue(qMin((int)val1,100));
//    this->speedarc->setValue(val1);
}
