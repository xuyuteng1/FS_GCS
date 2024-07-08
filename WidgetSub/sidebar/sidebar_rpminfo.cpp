#include "sidebar_rpminfo.h"
#include <QGraphicsView>
SideBarRPMInfo::SideBarRPMInfo()
{
    init();
}

QGridLayout *SideBarRPMInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarRPMInfo::init()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }

    if( this->lb_val[0] == nullptr){
        this->lb_val[0] = new QLabel(QStringLiteral("0 RPM"));
        this->lb_val[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[0]->setAlignment(Qt::AlignCenter);
        this->lb_val[0]->setToolTip(QStringLiteral("转速监测1"));
    }
    if( this->lb_val[1] == nullptr){
        this->lb_val[1] = new QLabel(QStringLiteral("0 RPM"));
        this->lb_val[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb_val[1]->setAlignment(Qt::AlignCenter);
        this->lb_val[1]->setToolTip(QStringLiteral("转速监测2"));
    }

    if( this->lb[0] == nullptr){
        this->lb[0] = new QLabel();
        this->lb[0]->setObjectName("SystemInfoWidgetLabel");
        this->lb[0]->setFixedHeight(22);
        this->lb[0]->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        this->lb[0]->setToolTip(QStringLiteral("转速监测1"));
        QPixmap pix(":/img/png/rpm.png");

        pix = pix.scaled(lb[0]->width(),lb[0]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[0]->setPixmap(pix);

    }
    if( this->lb[1] == nullptr){
        this->lb[1] = new QLabel();
        this->lb[1]->setObjectName("SystemInfoWidgetLabel");
        this->lb[1]->setFixedHeight(22);
        this->lb[1]->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        QPixmap pix(":/img/png/rpm.png");

        this->lb[1]->setToolTip(QStringLiteral("转速监测2"));
        pix = pix.scaled(lb[1]->width(),lb[1]->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb[1]->setPixmap(pix);
    }

    this->widgetLayout->addWidget(this->lb[0],0,0,1,1);
    this->widgetLayout->addWidget(this->lb[1],0,1,1,1);
    this->widgetLayout->addWidget(this->lb_val[0],1,0,1,1);
    this->widgetLayout->addWidget(this->lb_val[1],1,1,1,1);

    this->widgetLayout->setMargin(6);

    this->widgetLayout->setAlignment(Qt::AlignCenter);
    this->widgetLayout->setRowMinimumHeight(0,30);
    this->widgetLayout->setRowMinimumHeight(1,30);
}

void SideBarRPMInfo::update_val(float val1, float val2)
{
    this->lb_val[0]->setText(QString::number(val1,'f',0)+QStringLiteral(" RPM"));
    this->lb_val[1]->setText(QString::number(val2,'f',0)+QStringLiteral(" RPM"));
}
