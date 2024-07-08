/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_esc_cali.h"
#include "DMMM.h"
#include <qmath.h>

CFG_ESCCalibration::CFG_ESCCalibration()
{
    widget_init();
    connectSignalAndSlot();
}

QGridLayout *CFG_ESCCalibration::getWidgetLayout() const
{
    return widgetLayout;
}

void CFG_ESCCalibration::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ESCCalibration::handle_DMMM_event);
    connect(PB_Start       , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main(); if(link){link->do_ESCcali_start();}});
    connect(PB_Stop        , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main(); if(link){link->do_ESCcali_stop();}});
    connect(PB_Shift  , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();      if(link){link->do_ESCcali_toggle();}});
//    connect(PB_SimpleMagCali    , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagSimpleCaliStart(this->SP_FixedYaw->value());}});
//    connect(PB_InFlightMagCaliCancel, &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagInFlightCaliCancel();}});
}

void CFG_ESCCalibration::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("     电调校准前,一定要将螺旋桨拆下,防止不可预见的危险。 请单独给飞控及数据链系统供电,待飞控启动后,执行校准,此时飞控输出的为最大值,此时给电机上电,当听到电机\"滴滴滴\"时,切换电平,此时飞控输出最小值，完成校准。"));
        LB_Info->setWordWrap(true);
        LB_Info->setObjectName(QString::fromUtf8("warningLabel"));
    }

    if(PB_Start == nullptr){
        PB_Start = new QPushButton(QStringLiteral("校准开始"));
        PB_Start->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_Stop == nullptr){
        PB_Stop = new QPushButton(QStringLiteral("停止校准"));
        PB_Stop->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_Shift == nullptr){
        PB_Shift = new QPushButton(QStringLiteral("切换电平"));
        PB_Shift->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    widgetLayout->addItem(new QSpacerItem(40,160,QSizePolicy::Expanding,QSizePolicy::Maximum),0,0,9,1);
     widgetLayout->addItem(new QSpacerItem(40,160,QSizePolicy::Expanding,QSizePolicy::Maximum),0,11,9,1);
    widgetLayout->addWidget(LB_Info,0,1,8,10);
    widgetLayout->addWidget(PB_Start,8,2,1,1);
    widgetLayout->addWidget(PB_Shift,8,5,1,1);
    widgetLayout->addWidget(PB_Stop,8,7,1,1);

    widgetLayout->setContentsMargins(5,20,5,5);
}

void CFG_ESCCalibration::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_frameChanged:
        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        case Q_DMMM::DMMM_GCSEvent_Protocol_lost:
        case Q_DMMM::DMMM_GCSEvent_MagCountChanged:
        break;

        default:break;
    }
}
