#include "sidebar_missioninfo.h"
#include <QVariant>
SideBarMissionInfo::SideBarMissionInfo()
{
    initDesigner();
}

QGridLayout *SideBarMissionInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarMissionInfo::initDesigner()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }
    if(this->vBoxHome == nullptr){
        this->vBoxHome= new QVBoxLayout();
        this->vBoxHome->setSpacing(0);
        this->vBoxHome->setMargin(0);
    }
    if(this->vBoxTarget == nullptr){
        this->vBoxTarget= new QVBoxLayout();
        this->vBoxTarget->setSpacing(0);
        this->vBoxTarget->setMargin(0);
    }

    if(this->vBoxXtarckErr == nullptr){
        this->vBoxXtarckErr= new QVBoxLayout();
        this->vBoxXtarckErr->setSpacing(0);
        this->vBoxXtarckErr->setMargin(0);
    }

    if(this->lb_home_dis == nullptr){
        this->lb_home_dis = new QLabel(QStringLiteral("0 米"));
        this->lb_home_dis->setObjectName("SystemInfoWidgetLabel");
        this->lb_home_dis->setAlignment(Qt::AlignCenter);
        this->lb_home_dis->setMinimumWidth(60);
        this->lb_home_dis->setToolTip(QStringLiteral("离家距离"));
    }
    if(this->lb_target_dis == nullptr){
        this->lb_target_dis = new QLabel(QStringLiteral("0 米"));
        this->lb_target_dis->setObjectName("SystemInfoWidgetLabel");
        this->lb_target_dis->setAlignment(Qt::AlignCenter);
        this->lb_target_dis->setMinimumWidth(60);
        this->lb_target_dis->setToolTip(QStringLiteral("目标距离"));
    }
    if(this->lb_xtrack_err == nullptr){
        this->lb_xtrack_err = new QLabel(QStringLiteral("0 米"));
        this->lb_xtrack_err->setObjectName("SystemInfoWidgetLabel");
        this->lb_xtrack_err->setAlignment(Qt::AlignCenter);
        this->lb_xtrack_err->setMinimumWidth(60);

        this->lb_xtrack_err->setToolTip(QStringLiteral("偏航距离"));
    }

    if(this->lb_home_dis_icon == nullptr){
        this->lb_home_dis_icon = new QLabel();
        this->lb_home_dis_icon->setObjectName("SystemInfoWidgetLabel");
        this->lb_home_dis_icon->setFixedSize(22,30);
        this->lb_home_dis_icon->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/home.png");

        pix = pix.scaled(this->lb_home_dis_icon->width(),this->lb_home_dis_icon->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb_home_dis_icon->setPixmap(pix);

        this->lb_home_dis_icon->setToolTip(QStringLiteral("离家距离"));
    }

    if(this->lb_target_dis_icon == nullptr){
        this->lb_target_dis_icon = new QLabel();
        this->lb_target_dis_icon->setFixedSize(22,30);
        this->lb_target_dis_icon->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/target.png");

        pix = pix.scaled(this->lb_target_dis_icon->width(),this->lb_target_dis_icon->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb_target_dis_icon->setPixmap(pix);
        this->lb_target_dis_icon->setToolTip(QStringLiteral("目标距离"));
    }

    if(this->lb_xtrack_err_icon == nullptr){
        this->lb_xtrack_err_icon = new QLabel();
        this->lb_xtrack_err_icon->setFixedSize(22,30);
        this->lb_xtrack_err_icon->setAlignment(Qt::AlignCenter);
        QPixmap pix(":/img/png/Route.png");

        pix = pix.scaled(this->lb_xtrack_err_icon->width(),this->lb_xtrack_err_icon->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        this->lb_xtrack_err_icon->setPixmap(pix);
        this->lb_xtrack_err_icon->setToolTip(QStringLiteral("偏航距离"));
    }

//    this->vBoxHome->setAlignment(Qt::AlignCenter);
//    this->vBoxHome->addWidget(this->lb_home_dis_icon);
//    this->vBoxHome->addWidget(this->lb_home_dis);

//    this->vBoxTarget->addWidget(this->lb_target_dis_icon);
//    this->vBoxTarget->addWidget(this->lb_target_dis);
//    this->vBoxTarget->setAlignment(Qt::AlignCenter);

//    this->vBoxXtarckErr->addWidget(this->lb_xtrack_err_icon);
//    this->vBoxXtarckErr->addWidget(this->lb_xtrack_err);
//    this->vBoxXtarckErr->setAlignment(Qt::AlignCenter);


    this->widgetLayout->addWidget(this->lb_home_dis_icon,0,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_home_dis,1,0,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_target_dis_icon,0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_target_dis,1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_xtrack_err_icon,0,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(this->lb_xtrack_err,1,2,1,1,Qt::AlignCenter);

    this->widgetLayout->setMargin(6);
//    this->widgetLayout->setVerticalSpacing(6);

//    this->widgetLayout->setRowMinimumHeight(0,23);
//    this->widgetLayout->setRowMinimumHeight(1,30);

    this->widgetLayout->setColumnStretch(0,5);
    this->widgetLayout->setColumnStretch(1,5);
    this->widgetLayout->setColumnStretch(2,5);
}

void SideBarMissionInfo::update_val(float home_dis, float target_dis, float xtackErr)
{
    this->lb_home_dis->setText(QString::number(home_dis,'f',0)+QStringLiteral(" 米"));
    this->lb_target_dis->setText(QString::number(target_dis,'f',0)+QStringLiteral(" 米"));
    this->lb_xtrack_err->setText(QString::number(xtackErr,'f',1)+QStringLiteral(" 米"));
}



