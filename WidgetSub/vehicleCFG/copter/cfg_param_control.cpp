/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_param_control.h"
#include "DMMM.h"
#include <qmath.h>

CFG_ParamControl::CFG_ParamControl(QWidget *parent):
    QWidget(parent)
{
    widget_init();
}


void CFG_ParamControl::widget_init()
{

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(pilotctrl == nullptr){
        pilotctrl = new CFG_ParamPilotControl();
//        pilotctrl->setTitle(QStringLiteral("辅助控制参数"));
    }

    if(autoctrl == nullptr){
        autoctrl = new CFG_ParamAutoControl();
//        autoctrl->setTitle(QStringLiteral("自动控制参数"));
    }

    widgetLayout->addItem(pilotctrl,1,0,1,1);
    widgetLayout->addItem(autoctrl,1,1,1,1);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding),3,0,1,1);

    this->widgetLayout->setRowStretch(3,1);

    this->setLayout(widgetLayout);

}

CFG_ParamPilotControl::CFG_ParamPilotControl(QWidget *parent):
    QGridLayout(parent)
{
    widget_init();
    connectSignalAndSlot();
//    this->setObjectName("stackedSubWidget");
}

void CFG_ParamPilotControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamPilotControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamPilotCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamPilotControl::upload_param);

    connect(this->QB_angle_max_cd,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_angle_max_cd->setValue(static_cast<int>(value * 10));});
    connect(this->SD_angle_max_cd,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_angle_max_cd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_pilot_speed_up_cms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_pilot_speed_up_cms->setValue(static_cast<int>(value * 10));});
    connect(this->SD_pilot_speed_up_cms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_pilot_speed_up_cms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_pilot_speed_dn_cms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_pilot_speed_dn_cms->setValue(static_cast<int>(value * 10));});
    connect(this->SD_pilot_speed_dn_cms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_pilot_speed_dn_cms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_pilot_accel_z_cmms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_pilot_accel_z_cmms->setValue(static_cast<int>(value * 10));});
    connect(this->SD_pilot_accel_z_cmms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_pilot_accel_z_cmms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_speed_cms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_speed_cms->setValue(static_cast<int>(value * 10));});
    connect(this->SD_speed_cms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_speed_cms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_accel_cmss,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_accel_cmss->setValue(static_cast<int>(value * 10));});
    connect(this->SD_accel_cmss,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_accel_cmss->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_brake_accel_cmss,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_brake_accel_cmss->setValue(static_cast<int>(value * 10));});
    connect(this->SD_brake_accel_cmss,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_brake_accel_cmss->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_brake_jerk_max_cmsss,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_brake_jerk_max_cmsss->setValue(static_cast<int>(value * 10));});
    connect(this->SD_brake_jerk_max_cmsss,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_brake_jerk_max_cmsss->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_brake_delay_ms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_brake_delay_ms->setValue(static_cast<int>(value * 1000));});
    connect(this->SD_brake_delay_ms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_brake_delay_ms->setValue(static_cast<double>(static_cast<double>(value) / 1000.0f));});
}

void CFG_ParamPilotControl::widget_init()
{
    // 提示
    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("辅助控制参数设置"));
        LB_Info->setObjectName(QString::fromUtf8("CfgWIdgetTitle"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    // 标签
    if( LB_angle_max_cd == nullptr){
        LB_angle_max_cd = new QLabel(QStringLiteral("最大倾斜角:"));
        LB_angle_max_cd->setToolTip(QStringLiteral("最大倾斜角(°)"));
        LB_angle_max_cd->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_angle_max_cd->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_angle_max_cd->setToolTip(QStringLiteral("所有模式下，最大允许的倾斜角"));
    }

    if( LB_pilot_speed_up_cms == nullptr){
        LB_pilot_speed_up_cms = new QLabel(QStringLiteral("最大上升速度:"));
        LB_pilot_speed_up_cms->setToolTip(QStringLiteral("最大上升速度(m/s)"));
        LB_pilot_speed_up_cms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_pilot_speed_up_cms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_pilot_speed_dn_cms == nullptr){
        LB_pilot_speed_dn_cms = new QLabel(QStringLiteral("最大下降速度:"));
        LB_pilot_speed_dn_cms->setToolTip(QStringLiteral("最大下降速度(m/s)"));
        LB_pilot_speed_dn_cms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_pilot_speed_dn_cms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_pilot_accel_z_cmms == nullptr){
        LB_pilot_accel_z_cmms = new QLabel(QStringLiteral("垂直加速度:"));
        LB_pilot_accel_z_cmms->setToolTip(QStringLiteral("垂直加速度(m/ss)"));
        LB_pilot_accel_z_cmms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_pilot_accel_z_cmms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_speed_cms == nullptr){
        LB_speed_cms = new QLabel(QStringLiteral("悬停最大速度:"));
        LB_speed_cms->setToolTip(QStringLiteral("悬停最大速度(m/s)"));
        LB_speed_cms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_speed_cms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_accel_cmss == nullptr){
        LB_accel_cmss = new QLabel(QStringLiteral("水平加速度:"));
        LB_accel_cmss->setToolTip(QStringLiteral("水平加速度(m/ss)"));
        LB_accel_cmss->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_accel_cmss->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_brake_accel_cmss == nullptr){
        LB_brake_accel_cmss = new QLabel(QStringLiteral("刹车最大加速度:"));
        LB_brake_accel_cmss->setToolTip(QStringLiteral("刹车最大加速度(m/ss)"));
        LB_brake_accel_cmss->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_brake_accel_cmss->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_brake_jerk_max_cmsss == nullptr){
        LB_brake_jerk_max_cmsss = new QLabel(QStringLiteral("退刹响应加速度:"));
        LB_brake_jerk_max_cmsss->setToolTip(QStringLiteral("退刹响应加速度(m/ss)"));
        LB_brake_jerk_max_cmsss->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_brake_jerk_max_cmsss->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_brake_delay_ms == nullptr){
        LB_brake_delay_ms = new QLabel(QStringLiteral("刹车延时:"));
        LB_brake_delay_ms->setToolTip(QStringLiteral("刹车延时(s)"));
        LB_brake_delay_ms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_brake_delay_ms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( QB_angle_max_cd == nullptr){
        QB_angle_max_cd = new UDoubleSpinBox();
        QB_angle_max_cd->setRange(10,85);
        QB_angle_max_cd->setSingleStep(0.5f);
        QB_angle_max_cd->setValue(0);
        QB_angle_max_cd->setAlignment(Qt::AlignCenter);
        QB_angle_max_cd->setDecimals(1);
        QB_angle_max_cd->setToolTip(QStringLiteral("所有模式下，最大允许的倾斜角。"));
        QB_angle_max_cd->setChanged(false);
    }
    if( QB_pilot_speed_up_cms == nullptr){
        QB_pilot_speed_up_cms = new UDoubleSpinBox();
        QB_pilot_speed_up_cms->setRange(0.2f,20.0f);
        QB_pilot_speed_up_cms->setSingleStep(0.5f);
        QB_pilot_speed_up_cms->setValue(0);
        QB_pilot_speed_up_cms->setAlignment(Qt::AlignCenter);
        QB_pilot_speed_up_cms->setDecimals(2);
        QB_pilot_speed_up_cms->setToolTip(QStringLiteral("辅助模式下最大上升速度"));
        QB_pilot_speed_up_cms->setChanged(false);
    }
    if( QB_pilot_speed_dn_cms == nullptr){
        QB_pilot_speed_dn_cms = new UDoubleSpinBox();
        QB_pilot_speed_dn_cms->setRange(0.2f,20.0f);
        QB_pilot_speed_dn_cms->setSingleStep(0.5f);
        QB_pilot_speed_dn_cms->setValue(0);
        QB_pilot_speed_dn_cms->setAlignment(Qt::AlignCenter);
        QB_pilot_speed_dn_cms->setDecimals(2);
        QB_pilot_speed_dn_cms->setToolTip(QStringLiteral("辅助模式下最大下降"));
        QB_pilot_speed_dn_cms->setChanged(false);
    }
    if( QB_pilot_accel_z_cmms == nullptr){
        QB_pilot_accel_z_cmms = new UDoubleSpinBox();
        QB_pilot_accel_z_cmms->setRange(0.2f,20.0f);
        QB_pilot_accel_z_cmms->setSingleStep(0.5f);
        QB_pilot_accel_z_cmms->setValue(0);
        QB_pilot_accel_z_cmms->setAlignment(Qt::AlignCenter);
        QB_pilot_accel_z_cmms->setDecimals(2);
        QB_pilot_accel_z_cmms->setToolTip(QStringLiteral("辅助模式下最大垂直加速度"));
        QB_pilot_accel_z_cmms->setChanged(false);
    }
    if( QB_speed_cms == nullptr){
        QB_speed_cms = new UDoubleSpinBox();
        QB_speed_cms->setRange(0.2f,50.0f);
        QB_speed_cms->setSingleStep(0.5f);
        QB_speed_cms->setValue(0);
        QB_speed_cms->setAlignment(Qt::AlignCenter);
        QB_speed_cms->setDecimals(2);
        QB_speed_cms->setToolTip(QStringLiteral("悬停模式下最大水平速度"));
        QB_speed_cms->setChanged(false);
    }
    if( QB_accel_cmss == nullptr){
        QB_accel_cmss = new UDoubleSpinBox();
        QB_accel_cmss->setRange(0.5f,30.0f);
        QB_accel_cmss->setSingleStep(0.5f);
        QB_accel_cmss->setValue(0);
        QB_accel_cmss->setAlignment(Qt::AlignCenter);
        QB_accel_cmss->setDecimals(2);
        QB_accel_cmss->setToolTip(QStringLiteral("悬停模式下最大水平加速度"));
        QB_accel_cmss->setChanged(false);
    }
    if( QB_brake_accel_cmss == nullptr){
        QB_brake_accel_cmss = new UDoubleSpinBox();
        QB_brake_accel_cmss->setRange(0.1f,5.0f);
        QB_brake_accel_cmss->setSingleStep(0.5f);
        QB_brake_accel_cmss->setValue(0);
        QB_brake_accel_cmss->setAlignment(Qt::AlignCenter);
        QB_brake_accel_cmss->setDecimals(2);
        QB_brake_accel_cmss->setToolTip(QStringLiteral("刹车加速度,值越大,刹车速度越快。"));
        QB_brake_accel_cmss->setChanged(false);
    }

    if( QB_brake_jerk_max_cmsss == nullptr){
        QB_brake_jerk_max_cmsss = new UDoubleSpinBox();
        QB_brake_jerk_max_cmsss->setRange(1.0f,50.0f);
        QB_brake_jerk_max_cmsss->setSingleStep(0.5f);
        QB_brake_jerk_max_cmsss->setValue(0);
        QB_brake_jerk_max_cmsss->setAlignment(Qt::AlignCenter);
        QB_brake_jerk_max_cmsss->setDecimals(2);
        QB_brake_jerk_max_cmsss->setToolTip(QStringLiteral("退出刹车加速度大小,值越大,当拨动控制摇杆时退出刹车的速度越快。"));
        QB_brake_jerk_max_cmsss->setChanged(false);
    }
    if( QB_brake_delay_ms == nullptr){
        QB_brake_delay_ms = new UDoubleSpinBox();
        QB_brake_delay_ms->setRange(0,2.5f);
        QB_brake_delay_ms->setSingleStep(0.1f);
        QB_brake_delay_ms->setValue(0);
        QB_brake_delay_ms->setAlignment(Qt::AlignCenter);
        QB_brake_delay_ms->setDecimals(2);
        QB_brake_delay_ms->setToolTip(QStringLiteral("刹车延时:当控制摇杆回中后,将执行延时后进行刹车"));
        QB_brake_delay_ms->setChanged(false);
    }

    if( SD_angle_max_cd == nullptr){
        SD_angle_max_cd = new QSlider();
        SD_angle_max_cd->setRange(100,850);
        SD_angle_max_cd->setSingleStep(1);
        SD_angle_max_cd->setValue(100);
        SD_angle_max_cd->setOrientation(Qt::Horizontal);
        SD_angle_max_cd->setObjectName("widgetSlider");
        SD_angle_max_cd->setToolTip(QStringLiteral("所有模式下，最大允许的倾斜角。"));
    }
    if( SD_pilot_speed_up_cms == nullptr){
        SD_pilot_speed_up_cms = new QSlider();
        SD_pilot_speed_up_cms->setRange(2,200);
        SD_pilot_speed_up_cms->setSingleStep(5);
        SD_pilot_speed_up_cms->setValue(2);
        SD_pilot_speed_up_cms->setOrientation(Qt::Horizontal);
        SD_pilot_speed_up_cms->setObjectName("widgetSlider");
        SD_pilot_speed_up_cms->setToolTip(QStringLiteral("辅助模式下最大上升速度"));
    }
    if( SD_pilot_speed_dn_cms == nullptr){
        SD_pilot_speed_dn_cms = new QSlider();
        SD_pilot_speed_dn_cms->setRange(2,200);
        SD_pilot_speed_dn_cms->setSingleStep(5);
        SD_pilot_speed_dn_cms->setValue(2);
        SD_pilot_speed_dn_cms->setOrientation(Qt::Horizontal);
        SD_pilot_speed_dn_cms->setObjectName("widgetSlider");
        SD_pilot_speed_dn_cms->setToolTip(QStringLiteral("辅助模式下最大下降"));
    }
    if( SD_pilot_accel_z_cmms == nullptr){
        SD_pilot_accel_z_cmms = new QSlider();
        SD_pilot_accel_z_cmms->setRange(2,200);
        SD_pilot_accel_z_cmms->setSingleStep(5);
        SD_pilot_accel_z_cmms->setValue(2);
        SD_pilot_accel_z_cmms->setOrientation(Qt::Horizontal);
        SD_pilot_accel_z_cmms->setObjectName("widgetSlider");
        SD_pilot_accel_z_cmms->setToolTip(QStringLiteral("辅助模式下最大垂直加速度"));
    }
    if( SD_speed_cms == nullptr){
        SD_speed_cms = new QSlider();
        SD_speed_cms->setRange(2,500);
        SD_speed_cms->setSingleStep(5);
        SD_speed_cms->setValue(2);
        SD_speed_cms->setOrientation(Qt::Horizontal);
        SD_speed_cms->setObjectName("widgetSlider");
        SD_speed_cms->setToolTip(QStringLiteral("悬停模式下最大水平速度"));
    }
    if( SD_accel_cmss == nullptr){
        SD_accel_cmss = new QSlider();
        SD_accel_cmss->setRange(5,300);
        SD_accel_cmss->setSingleStep(5);
        SD_accel_cmss->setValue(5);
        SD_accel_cmss->setOrientation(Qt::Horizontal);
        SD_accel_cmss->setObjectName("widgetSlider");
        SD_accel_cmss->setToolTip(QStringLiteral("悬停模式下最大水平加速度"));
    }
    if( SD_brake_accel_cmss == nullptr){
        SD_brake_accel_cmss = new QSlider();
        SD_brake_accel_cmss->setRange(1,50);
        SD_brake_accel_cmss->setSingleStep(5);
        SD_brake_accel_cmss->setValue(1);
        SD_brake_accel_cmss->setOrientation(Qt::Horizontal);
        SD_brake_accel_cmss->setObjectName("widgetSlider");
        SD_brake_accel_cmss->setToolTip(QStringLiteral("刹车加速度,值越大,刹车速度越快。"));
    }

    if( SD_brake_jerk_max_cmsss == nullptr){
        SD_brake_jerk_max_cmsss = new QSlider();
        SD_brake_jerk_max_cmsss->setRange(10,500);
        SD_brake_jerk_max_cmsss->setSingleStep(5);
        SD_brake_jerk_max_cmsss->setValue(10);
        SD_brake_jerk_max_cmsss->setOrientation(Qt::Horizontal);
        SD_brake_jerk_max_cmsss->setObjectName("widgetSlider");
        SD_brake_jerk_max_cmsss->setToolTip(QStringLiteral("退出刹车加速度大小,值越大,当拨动控制摇杆时退出刹车的速度越快。"));
    }
    if( SD_brake_delay_ms == nullptr){
        SD_brake_delay_ms = new QSlider();
        SD_brake_delay_ms->setRange(0,2500);
        SD_brake_delay_ms->setSingleStep(1);
        SD_brake_delay_ms->setValue(0);
        SD_brake_delay_ms->setOrientation(Qt::Horizontal);
        SD_brake_delay_ms->setObjectName("widgetSlider");
        SD_brake_delay_ms->setToolTip(QStringLiteral("刹车延时:当控制摇杆回中后,将执行延时后进行刹车"));
    }

    // 按键
    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_download->setToolTip(QStringLiteral(""));
    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_upload->setToolTip(QStringLiteral(""));
    }
    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
        widgetLayout_pb->setObjectName(QString::fromUtf8("widgetLayout"));
    }


    widgetLayout_pb->addStretch(10);
    widgetLayout_pb->addWidget(PB_download,2);
    widgetLayout_pb->addStretch(1);
    widgetLayout_pb->addWidget(PB_upload,2);
    widgetLayout_pb->addStretch(10);
    widgetLayout_pb->setSpacing(2);
    widgetLayout_pb->setContentsMargins(0,15,0,0);

    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,0,12,1);

    this->addWidget(LB_Info                , 0, 0, 1, 5);
    this->addWidget(LB_angle_max_cd        , 1, 1, 1, 1);
    this->addWidget(LB_pilot_speed_up_cms  , 2, 1, 1, 1);
    this->addWidget(LB_pilot_speed_dn_cms  , 3, 1, 1, 1);
    this->addWidget(LB_pilot_accel_z_cmms  , 4, 1, 1, 1);
    this->addWidget(LB_speed_cms           , 5, 1, 1, 1);
    this->addWidget(LB_accel_cmss          , 6, 1, 1, 1);
    this->addWidget(LB_brake_accel_cmss    , 7, 1, 1, 1);
    this->addWidget(LB_brake_jerk_max_cmsss, 8, 1, 1, 1);
    this->addWidget(LB_brake_delay_ms      ,9, 1, 1, 1);

    this->addWidget(QB_angle_max_cd         , 1, 2, 1, 1);
    this->addWidget(QB_pilot_speed_up_cms   , 2, 2, 1, 1);
    this->addWidget(QB_pilot_speed_dn_cms   , 3, 2, 1, 1);
    this->addWidget(QB_pilot_accel_z_cmms   , 4, 2, 1, 1);
    this->addWidget(QB_speed_cms            , 5, 2, 1, 1);
    this->addWidget(QB_accel_cmss           , 6, 2, 1, 1);
    this->addWidget(QB_brake_accel_cmss     , 7, 2, 1, 1);
    this->addWidget(QB_brake_jerk_max_cmsss , 8, 2, 1, 1);
    this->addWidget(QB_brake_delay_ms       ,9, 2, 1, 1);


    this->addWidget(SD_angle_max_cd         , 1, 3, 1, 1);
    this->addWidget(SD_pilot_speed_up_cms   , 2, 3, 1, 1);
    this->addWidget(SD_pilot_speed_dn_cms   , 3, 3, 1, 1);
    this->addWidget(SD_pilot_accel_z_cmms   , 4, 3, 1, 1);
    this->addWidget(SD_speed_cms            , 5, 3, 1, 1);
    this->addWidget(SD_accel_cmss           , 6, 3, 1, 1);
    this->addWidget(SD_brake_accel_cmss     , 7, 3, 1, 1);
    this->addWidget(SD_brake_jerk_max_cmsss , 8, 3, 1, 1);
    this->addWidget(SD_brake_delay_ms       ,9, 3, 1, 1);

    this->addLayout(widgetLayout_pb         ,11, 1, 1, 3);
     this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,4,12,1);

    this->setVerticalSpacing(2);
    this->setColumnStretch(0,1);
    this->setColumnStretch(4,1);

}

void CFG_ParamPilotControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamPilotCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_pilot_control_t pkt = link->getTVehicleParam().PilotCtrl;
                QB_angle_max_cd         ->setValue(pkt.angle_max_cd          *0.01f);
                QB_pilot_speed_up_cms   ->setValue(pkt.pilot_speed_up_cms    *0.01f);
                QB_pilot_speed_dn_cms   ->setValue(pkt.pilot_speed_dn_cms    *0.01f);
                QB_pilot_accel_z_cmms   ->setValue(pkt.pilot_accel_z_cmms    *0.01f);
                QB_speed_cms            ->setValue(pkt._speed_cms            *0.01f);
                QB_accel_cmss           ->setValue(pkt._accel_cmss           *0.01f);
                QB_brake_accel_cmss     ->setValue(pkt._brake_accel_cmss     *0.01f);
                QB_brake_jerk_max_cmsss ->setValue(pkt._brake_jerk_max_cmsss *0.01f);
                QB_brake_delay_ms       ->setValue(pkt._brake_delay_ms       *0.001f);

                QB_angle_max_cd        ->setChanged(false);
                QB_pilot_speed_up_cms  ->setChanged(false);
                QB_pilot_speed_dn_cms  ->setChanged(false);
                QB_pilot_accel_z_cmms  ->setChanged(false);
                QB_speed_cms           ->setChanged(false);
                QB_accel_cmss          ->setChanged(false);
                QB_brake_accel_cmss    ->setChanged(false);
                QB_brake_jerk_max_cmsss->setChanged(false);
                QB_brake_delay_ms      ->setChanged(false);

            }
        }break;
        default:break;
    }
}

void CFG_ParamPilotControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_pilot_control_t pkt{};
        pkt.is_set = 1;

        pkt.angle_max_cd              = QB_angle_max_cd             ->value()*100;
        pkt.pilot_speed_up_cms    = QB_pilot_speed_up_cms   ->value()*100;
        pkt.pilot_speed_dn_cms    = QB_pilot_speed_dn_cms   ->value()*100;
        pkt.pilot_accel_z_cmms     = QB_pilot_accel_z_cmms   ->value()*100;
        pkt._speed_cms                 = QB_speed_cms                 ->value()*100;
        pkt._accel_cmss                 = QB_accel_cmss                 ->value()*100;
        pkt._brake_accel_cmss      = QB_brake_accel_cmss      ->value()*100;
        pkt._brake_jerk_max_cmsss = QB_brake_jerk_max_cmsss ->value()*100;
        pkt._brake_delay_ms       = QB_brake_delay_ms         ->value()*1000;

        link->do_setParamPilotCtrl(pkt);
    }
}

CFG_ParamAutoControl::CFG_ParamAutoControl(QWidget *parent)
{
    widget_init();
    connectSignalAndSlot();
}

void CFG_ParamAutoControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamAutoControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamAutoCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamAutoControl::upload_param);

    connect(this->QB__wp_speed_cms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD__wp_speed_cms->setValue(static_cast<int>(value * 10));});
    connect(this->SD__wp_speed_cms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB__wp_speed_cms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB__wp_speed_up_cms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD__wp_speed_up_cms->setValue(static_cast<int>(value * 10));});
    connect(this->SD__wp_speed_up_cms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB__wp_speed_up_cms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB__wp_speed_down_cms,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD__wp_speed_down_cms->setValue(static_cast<int>(value * 10));});
    connect(this->SD__wp_speed_down_cms,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB__wp_speed_down_cms->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB__wp_radius_cm,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD__wp_radius_cm->setValue(static_cast<int>(value * 100));});
    connect(this->SD__wp_radius_cm,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB__wp_radius_cm->setValue(static_cast<double>(static_cast<double>(value) / 100.0f));});

    connect(this->QB__wp_accel_cmss,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD__wp_accel_cmss->setValue(static_cast<int>(value * 10));});
    connect(this->SD__wp_accel_cmss,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB__wp_accel_cmss->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB__wp_accel_z_cmss,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD__wp_accel_z_cmss->setValue(static_cast<int>(value * 10));});
    connect(this->SD__wp_accel_z_cmss,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB__wp_accel_z_cmss->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_land_speed,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_land_speed->setValue(static_cast<int>(value * 10));});
    connect(this->SD_land_speed,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_land_speed->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

    connect(this->QB_land_alt_low,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_land_alt_low->setValue(static_cast<int>(value ));});
    connect(this->SD_land_alt_low,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_land_alt_low->setValue(static_cast<double>(static_cast<double>(value)));});

    connect(this->QB_rtl_altitude,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_rtl_altitude->setValue(static_cast<int>(value * 10));});
    connect(this->SD_rtl_altitude,QOverload<int>::of(&QSlider::valueChanged),[=](int value){this->QB_rtl_altitude->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});

}

void CFG_ParamAutoControl::widget_init()
{
    // 提示
    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("自动控制参数设置"));
        LB_Info->setObjectName(QString::fromUtf8("CfgWIdgetTitle"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    // 标签
    if( LB__wp_speed_cms == nullptr){
        LB__wp_speed_cms = new QLabel(QStringLiteral("水平速度:"));
        LB__wp_speed_cms->setToolTip(QStringLiteral("水平速度(m/s)"));
        LB__wp_speed_cms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__wp_speed_cms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__wp_speed_up_cms == nullptr){
        LB__wp_speed_up_cms = new QLabel(QStringLiteral("上升速度:"));
        LB__wp_speed_up_cms->setToolTip(QStringLiteral("上升速度(m/s)"));
        LB__wp_speed_up_cms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__wp_speed_up_cms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__wp_speed_down_cms == nullptr){
        LB__wp_speed_down_cms = new QLabel(QStringLiteral("下降速度:"));
        LB__wp_speed_down_cms->setToolTip(QStringLiteral("下降速度(m/s)"));
        LB__wp_speed_down_cms->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__wp_speed_down_cms->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__wp_radius_cm == nullptr){
        LB__wp_radius_cm = new QLabel(QStringLiteral("航点半径:"));
        LB__wp_radius_cm->setToolTip(QStringLiteral("航点半径(m)"));
        LB__wp_radius_cm->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__wp_radius_cm->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__wp_accel_cmss == nullptr){
        LB__wp_accel_cmss = new QLabel(QStringLiteral("水平加速度:"));
        LB__wp_accel_cmss->setToolTip(QStringLiteral("水平加速度(m/ss)"));
        LB__wp_accel_cmss->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__wp_accel_cmss->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__wp_accel_z_cmss == nullptr){
        LB__wp_accel_z_cmss = new QLabel(QStringLiteral("垂直加速度:"));
        LB__wp_accel_z_cmss->setToolTip(QStringLiteral("垂直加速度(m/ss)"));
        LB__wp_accel_z_cmss->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__wp_accel_z_cmss->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_land_speed == nullptr){
        LB_land_speed = new QLabel(QStringLiteral("降落速度:"));
        LB_land_speed->setToolTip(QStringLiteral("降落速度(m/s)"));
        LB_land_speed->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_land_speed->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_land_alt_low == nullptr){
        LB_land_alt_low = new QLabel(QStringLiteral("降落高度:"));
        LB_land_alt_low->setToolTip(QStringLiteral("降落高度(m)"));
        LB_land_alt_low->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_land_alt_low->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_rtl_altitude == nullptr){
        LB_rtl_altitude = new QLabel(QStringLiteral("返航高度:"));
        LB_rtl_altitude->setToolTip(QStringLiteral("返航高度(m)"));
        LB_rtl_altitude->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rtl_altitude->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }


    if( QB__wp_speed_cms == nullptr){
        QB__wp_speed_cms = new UDoubleSpinBox();
        QB__wp_speed_cms->setRange(0.2f,100);
        QB__wp_speed_cms->setSingleStep(1);
        QB__wp_speed_cms->setValue(0);
        QB__wp_speed_cms->setAlignment(Qt::AlignCenter);
        QB__wp_speed_cms->setDecimals(1);
        QB__wp_speed_cms->setToolTip(QStringLiteral("水平速度:自主模式下,飞行器将尝试以此速度飞行"));
        QB__wp_speed_cms->setChanged(false);
    }
    if( QB__wp_speed_up_cms == nullptr){
        QB__wp_speed_up_cms = new UDoubleSpinBox();
        QB__wp_speed_up_cms->setRange(0.2f,20);
        QB__wp_speed_up_cms->setSingleStep(0.5f);
        QB__wp_speed_up_cms->setValue(0);
        QB__wp_speed_up_cms->setAlignment(Qt::AlignCenter);
        QB__wp_speed_up_cms->setDecimals(1);
        QB__wp_speed_up_cms->setToolTip(QStringLiteral("上升速度:自主模式下,飞行器将尝试以此速度飞行"));
        QB__wp_speed_up_cms->setChanged(false);
    }
    if( QB__wp_speed_down_cms == nullptr){
        QB__wp_speed_down_cms = new UDoubleSpinBox();
        QB__wp_speed_down_cms->setRange(0.2f,10.0f);
        QB__wp_speed_down_cms->setSingleStep(0.5f);
        QB__wp_speed_down_cms->setValue(0);
        QB__wp_speed_down_cms->setAlignment(Qt::AlignCenter);
        QB__wp_speed_down_cms->setDecimals(1);
        QB__wp_speed_down_cms->setToolTip(QStringLiteral("上升速度:自主模式下,飞行器将尝试以此速度下降"));
        QB__wp_speed_down_cms->setChanged(false);
    }
    if( QB__wp_radius_cm == nullptr){
        QB__wp_radius_cm = new UDoubleSpinBox();
        QB__wp_radius_cm->setRange(0.05,300);
        QB__wp_radius_cm->setSingleStep(0.5f);
        QB__wp_radius_cm->setValue(0);
        QB__wp_radius_cm->setAlignment(Qt::AlignCenter);
        QB__wp_radius_cm->setDecimals(1);
        QB__wp_radius_cm->setToolTip(QStringLiteral("航点半径:到达目标的半径内则认定到达目标."));
        QB__wp_radius_cm->setChanged(false);
    }
    if( QB__wp_accel_cmss == nullptr){
        QB__wp_accel_cmss = new UDoubleSpinBox();
        QB__wp_accel_cmss->setRange(0.2f,20.0f);
        QB__wp_accel_cmss->setSingleStep(0.5f);
        QB__wp_accel_cmss->setValue(0);
        QB__wp_accel_cmss->setAlignment(Qt::AlignCenter);
        QB__wp_accel_cmss->setDecimals(1);
        QB__wp_accel_cmss->setToolTip(QStringLiteral("水平加速度:自主模式下水平加速度大小."));
        QB__wp_accel_cmss->setChanged(false);
    }
    if( QB__wp_accel_z_cmss == nullptr){
        QB__wp_accel_z_cmss = new UDoubleSpinBox();
        QB__wp_accel_z_cmss->setRange(0.2f,20.0f);
        QB__wp_accel_z_cmss->setSingleStep(0.5f);
        QB__wp_accel_z_cmss->setValue(0);
        QB__wp_accel_z_cmss->setAlignment(Qt::AlignCenter);
        QB__wp_accel_z_cmss->setDecimals(1);
        QB__wp_accel_z_cmss->setToolTip(QStringLiteral("垂直加速度:自主模式下垂直加速度大小."));
        QB__wp_accel_z_cmss->setChanged(false);
    }
    if( QB_land_speed == nullptr){
        QB_land_speed = new UDoubleSpinBox();
        QB_land_speed->setRange(0.2f,2.5f);
        QB_land_speed->setSingleStep(0.1f);
        QB_land_speed->setValue(0);
        QB_land_speed->setAlignment(Qt::AlignCenter);
        QB_land_speed->setDecimals(1);
        QB_land_speed->setToolTip(QStringLiteral("降落速度:自主模式下,最后的降落阶段的速度"));
        QB_land_speed->setChanged(false);
    }
    if( QB_land_alt_low == nullptr){
        QB_land_alt_low = new UDoubleSpinBox();
        QB_land_alt_low->setRange(1,100);
        QB_land_alt_low->setSingleStep(1);
        QB_land_alt_low->setValue(0);
        QB_land_alt_low->setAlignment(Qt::AlignCenter);
        QB_land_alt_low->setDecimals(1);
        QB_land_alt_low->setToolTip(QStringLiteral("落地高度:低于此高度，将速度设定为降落速度。"));
        QB_land_alt_low->setChanged(false);
    }
    if( QB_rtl_altitude == nullptr){
        QB_rtl_altitude = new UDoubleSpinBox();
        QB_rtl_altitude->setRange(2,100);
        QB_rtl_altitude->setSingleStep(0.1f);
        QB_rtl_altitude->setValue(0);
        QB_rtl_altitude->setAlignment(Qt::AlignCenter);
        QB_rtl_altitude->setDecimals(1);
        QB_rtl_altitude->setToolTip(QStringLiteral("返航高度:当返航时当前高度低于此高度，将会升高至此高度，然后执行返航动作."));
        QB_rtl_altitude->setChanged(false);
    }


    if( SD__wp_speed_cms == nullptr){
        SD__wp_speed_cms = new QSlider();
        SD__wp_speed_cms->setRange(2,1000);
        SD__wp_speed_cms->setSingleStep(10);
        SD__wp_speed_cms->setValue(2);
        SD__wp_speed_cms->setOrientation(Qt::Horizontal);
        SD__wp_speed_cms->setObjectName("widgetSlider");
        SD__wp_speed_cms->setToolTip(QStringLiteral("水平速度:自主模式下,飞行器将尝试以此速度飞行"));
    }
    if( SD__wp_speed_up_cms == nullptr){
        SD__wp_speed_up_cms = new QSlider();
        SD__wp_speed_up_cms->setRange(2,200);
        SD__wp_speed_up_cms->setSingleStep(5);
        SD__wp_speed_up_cms->setValue(2);
        SD__wp_speed_up_cms->setOrientation(Qt::Horizontal);
        SD__wp_speed_up_cms->setObjectName("widgetSlider");
        SD__wp_speed_up_cms->setToolTip(QStringLiteral("上升速度:自主模式下,飞行器将尝试以此速度飞行"));
    }
    if( SD__wp_speed_down_cms == nullptr){
        SD__wp_speed_down_cms = new QSlider();
        SD__wp_speed_down_cms->setRange(2,100);
        SD__wp_speed_down_cms->setSingleStep(5);
        SD__wp_speed_down_cms->setValue(2);
        SD__wp_speed_down_cms->setOrientation(Qt::Horizontal);
        SD__wp_speed_down_cms->setObjectName("widgetSlider");
        SD__wp_speed_down_cms->setToolTip(QStringLiteral("上升速度:自主模式下,飞行器将尝试以此速度下降"));
    }
    if( SD__wp_radius_cm == nullptr){
        SD__wp_radius_cm = new QSlider();
        SD__wp_radius_cm->setRange(5,30000);
        SD__wp_radius_cm->setSingleStep(50);
        SD__wp_radius_cm->setValue(5);
        SD__wp_radius_cm->setOrientation(Qt::Horizontal);
        SD__wp_radius_cm->setObjectName("widgetSlider");
        SD__wp_radius_cm->setToolTip(QStringLiteral("航点半径:到达目标的半径内则认定到达目标."));
    }
    if( SD__wp_accel_cmss == nullptr){
        SD__wp_accel_cmss = new QSlider();
        SD__wp_accel_cmss->setRange(2,200);
        SD__wp_accel_cmss->setSingleStep(5);
        SD__wp_accel_cmss->setValue(2);
        SD__wp_accel_cmss->setOrientation(Qt::Horizontal);
        SD__wp_accel_cmss->setObjectName("widgetSlider");
        SD__wp_accel_cmss->setToolTip(QStringLiteral("水平加速度:自主模式下水平加速度大小."));
    }
    if( SD__wp_accel_z_cmss == nullptr){
        SD__wp_accel_z_cmss = new QSlider();
        SD__wp_accel_z_cmss->setRange(2,200);
        SD__wp_accel_z_cmss->setSingleStep(5);
        SD__wp_accel_z_cmss->setValue(2);
        SD__wp_accel_z_cmss->setOrientation(Qt::Horizontal);
        SD__wp_accel_z_cmss->setObjectName("widgetSlider");
        SD__wp_accel_z_cmss->setToolTip(QStringLiteral("垂直加速度:自主模式下垂直加速度大小."));
    }
    if( SD_land_speed == nullptr){
        SD_land_speed = new QSlider();
        SD_land_speed->setRange(2,25);
        SD_land_speed->setSingleStep(1);
        SD_land_speed->setValue(2);
        SD_land_speed->setOrientation(Qt::Horizontal);
        SD_land_speed->setObjectName("widgetSlider");
        SD_land_speed->setToolTip(QStringLiteral("降落速度:自主模式下,最后的降落阶段的速度"));
    }
    if( SD_land_alt_low == nullptr){
        SD_land_alt_low = new QSlider();
        SD_land_alt_low->setRange(1,100);
        SD_land_alt_low->setSingleStep(1);
        SD_land_alt_low->setValue(0);
        SD_land_alt_low->setOrientation(Qt::Horizontal);
        SD_land_alt_low->setObjectName("widgetSlider");
        SD_land_alt_low->setToolTip(QStringLiteral("落地高度:低于此高度，将速度设定为降落速度。"));
    }
    if( SD_rtl_altitude == nullptr){
        SD_rtl_altitude = new QSlider();
        SD_rtl_altitude->setRange(20,1000);
        SD_rtl_altitude->setSingleStep(1);
        SD_rtl_altitude->setValue(20);
        SD_rtl_altitude->setOrientation(Qt::Horizontal);
        SD_rtl_altitude->setObjectName("widgetSlider");
        SD_rtl_altitude->setToolTip(QStringLiteral("返航高度:当返航时当前高度低于此高度，将会升高至此高度，然后执行返航动作."));
    }


    // 按键
    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_download->setToolTip(QStringLiteral(""));
    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_upload->setToolTip(QStringLiteral(""));
    }
    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
        widgetLayout_pb->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    widgetLayout_pb->addStretch(10);
    widgetLayout_pb->addWidget(PB_download,2);
    widgetLayout_pb->addStretch(1);
    widgetLayout_pb->addWidget(PB_upload,2);
    widgetLayout_pb->addStretch(10);
    widgetLayout_pb->setSpacing(2);
    widgetLayout_pb->setContentsMargins(0,15,0,0);

    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,0,12,1);
    this->addWidget(LB_Info                , 0, 0, 1, 5);
    this->addWidget(LB__wp_speed_cms     , 1, 1, 1, 1);
    this->addWidget(LB__wp_speed_up_cms  , 2, 1, 1, 1);
    this->addWidget(LB__wp_speed_down_cms, 3, 1, 1, 1);
    this->addWidget(LB__wp_radius_cm     , 4, 1, 1, 1);
    this->addWidget(LB__wp_accel_cmss    , 5, 1, 1, 1);
    this->addWidget(LB__wp_accel_z_cmss  , 6, 1, 1, 1);
    this->addWidget(LB_land_speed        , 7, 1, 1, 1);
    this->addWidget(LB_land_alt_low      , 8, 1, 1, 1);
    this->addWidget(LB_rtl_altitude      ,9, 1, 1, 1);

    this->addWidget(QB__wp_speed_cms     , 1, 2, 1, 1);
    this->addWidget(QB__wp_speed_up_cms  , 2, 2, 1, 1);
    this->addWidget(QB__wp_speed_down_cms, 3, 2, 1, 1);
    this->addWidget(QB__wp_radius_cm     , 4, 2, 1, 1);
    this->addWidget(QB__wp_accel_cmss    , 5, 2, 1, 1);
    this->addWidget(QB__wp_accel_z_cmss  , 6, 2, 1, 1);
    this->addWidget(QB_land_speed        , 7, 2, 1, 1);
    this->addWidget(QB_land_alt_low      , 8, 2, 1, 1);
    this->addWidget(QB_rtl_altitude      ,9, 2, 1, 1);

    this->addWidget(SD__wp_speed_cms     , 1, 3, 1, 1);
    this->addWidget(SD__wp_speed_up_cms  , 2, 3, 1, 1);
    this->addWidget(SD__wp_speed_down_cms, 3, 3, 1, 1);
    this->addWidget(SD__wp_radius_cm     ,4 , 3, 1, 1);
    this->addWidget(SD__wp_accel_cmss    , 5, 3, 1, 1);
    this->addWidget(SD__wp_accel_z_cmss  , 6, 3, 1, 1);
    this->addWidget(SD_land_speed        , 7, 3, 1, 1);
    this->addWidget(SD_land_alt_low      , 8, 3, 1, 1);
    this->addWidget(SD_rtl_altitude      ,9, 3, 1, 1);

    this->addLayout(widgetLayout_pb         ,11, 1, 1, 3);

    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,4,12,1);

    this->setVerticalSpacing(2);
    this->setColumnStretch(0,1);
    this->setColumnStretch(4,1);

}

void CFG_ParamAutoControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamAutoCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_auto_control_t pkt = link->getTVehicleParam().AutoCtrl;
                QB__wp_speed_cms     ->setValue(pkt._wp_speed_cms     *0.01f);
                QB__wp_speed_up_cms  ->setValue(pkt._wp_speed_up_cms  *0.01f);
                QB__wp_speed_down_cms->setValue(pkt._wp_speed_down_cms*0.01f);
                QB__wp_radius_cm     ->setValue(pkt._wp_radius_cm     *0.01f);
                QB__wp_accel_cmss    ->setValue(pkt._wp_accel_cmss    *0.01f);
                QB__wp_accel_z_cmss  ->setValue(pkt._wp_accel_z_cmss  *0.01f);
                QB_land_speed        ->setValue(pkt.land_speed        *0.01f);
                QB_land_alt_low      ->setValue(pkt.land_alt_low      *0.01f);
                QB_rtl_altitude      ->setValue(pkt.rtl_altitude      *0.01f);

                QB_rtl_altitude      ->setChanged(false);
                QB_land_alt_low      ->setChanged(false);
                QB_land_speed        ->setChanged(false);
                QB__wp_accel_z_cmss  ->setChanged(false);
                QB__wp_accel_cmss    ->setChanged(false);
                QB__wp_radius_cm     ->setChanged(false);
                QB__wp_speed_down_cms->setChanged(false);
                QB__wp_speed_up_cms  ->setChanged(false);
                QB__wp_speed_cms     ->setChanged(false);

            }
        }break;
        default:break;
    }
}

void CFG_ParamAutoControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_auto_control_t pkt{};
        pkt.is_set = 1;

        pkt._wp_speed_cms      = QB__wp_speed_cms     ->value()*100;
        pkt._wp_speed_up_cms   = QB__wp_speed_up_cms  ->value()*100;
        pkt._wp_speed_down_cms = QB__wp_speed_down_cms->value()*100;
        pkt._wp_radius_cm      = QB__wp_radius_cm     ->value()*100;
        pkt._wp_accel_cmss     = QB__wp_accel_cmss    ->value()*100;
        pkt._wp_accel_z_cmss   = QB__wp_accel_z_cmss  ->value()*100;
        pkt.land_speed         = QB_land_speed        ->value()*100;
        pkt.land_alt_low       = QB_land_alt_low      ->value()*100;
        pkt.rtl_altitude       = QB_rtl_altitude      ->value()*100;

        link->do_setParamAutoCtrl(pkt);
    }
}
