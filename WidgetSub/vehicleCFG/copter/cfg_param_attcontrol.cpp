/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_param_attcontrol.h"
#include "DMMM.h"
#include <qmath.h>

CFG_ParamRollControl::CFG_ParamRollControl(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("stackedSubWidget_no_border");
}


void CFG_ParamRollControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamRollControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamRollCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamRollControl::upload_param);
}

void CFG_ParamRollControl::widget_init()
{

    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("滚转控制参数"));
        this->titleLabel->setObjectName("CfgWIdgetTitle");
        this->titleLabel->setAlignment(Qt::AlignCenter);
    }

    // 标签
    if( LB__ang_vel_max == nullptr){
        LB__ang_vel_max = new QLabel(QStringLiteral("最大角速度:"));
        LB__ang_vel_max->setToolTip(QStringLiteral("最大角速度(deg/s)"));
        LB__ang_vel_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__ang_vel_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__accel_max == nullptr){
        LB__accel_max = new QLabel(QStringLiteral("最大加速度:"));
        LB__accel_max->setToolTip(QStringLiteral("最大加速度(deg/ss)"));
        LB__accel_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__accel_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_angle_p == nullptr){
        LB_angle_p = new QLabel(QStringLiteral("P:"));
        LB_angle_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_angle_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_p == nullptr){
        LB_rate_p = new QLabel(QStringLiteral("P:"));
        LB_rate_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_i == nullptr){
        LB_rate_i = new QLabel(QStringLiteral("I:"));
        LB_rate_i->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_i->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_d == nullptr){
        LB_rate_d = new QLabel(QStringLiteral("D:"));
        LB_rate_d->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_d->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_ff == nullptr){
        LB_rate_ff = new QLabel(QStringLiteral("FF:"));
        LB_rate_ff->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_ff->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_imax == nullptr){
        LB_rate_imax = new QLabel(QStringLiteral("Imax:"));
        LB_rate_imax->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_imax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_slew_rate_max == nullptr){
        LB_rate_slew_rate_max = new QLabel(QStringLiteral("Limit:"));
        LB_rate_slew_rate_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_slew_rate_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_Limit == nullptr){
        LB_Limit = new QLabel(QStringLiteral("限定参数"));
        LB_Limit->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Limit->setAlignment(Qt::AlignCenter);
    }
    if( LB_Angle == nullptr){
        LB_Angle = new QLabel(QStringLiteral("角度控制"));
        LB_Angle->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Angle->setAlignment(Qt::AlignCenter);
    }
    if( LB_Rate == nullptr){
        LB_Rate = new QLabel(QStringLiteral("速率控制"));
        LB_Rate->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Rate->setAlignment(Qt::AlignCenter);
    }

    if( QB__accel_max == nullptr){
        QB__accel_max = new UDoubleSpinBox();
        QB__accel_max->setRange(0,1800);
        QB__accel_max->setSingleStep(1);
        QB__accel_max->setValue(0);
        QB__accel_max->setAlignment(Qt::AlignCenter);
        QB__accel_max->setDecimals(1);
        QB__accel_max->setToolTip(QStringLiteral("Roll轴的最大加速度"));
        QB__accel_max->setChanged(false);
    }

    if( QB__ang_vel_max == nullptr){
        QB__ang_vel_max = new UDoubleSpinBox();
        QB__ang_vel_max->setRange(0,1200.0f);
        QB__ang_vel_max->setSingleStep(1);
        QB__ang_vel_max->setValue(0);
        QB__ang_vel_max->setAlignment(Qt::AlignCenter);
        QB__ang_vel_max->setDecimals(1);
        QB__ang_vel_max->setToolTip(QStringLiteral("Roll轴的最大角速度"));
        QB__ang_vel_max->setChanged(false);
    }

    if( QB_angle_p == nullptr){
        QB_angle_p = new UDoubleSpinBox();
        QB_angle_p->setRange(2.5f,12.0f);
        QB_angle_p->setSingleStep(0.1f);
        QB_angle_p->setValue(0);
        QB_angle_p->setAlignment(Qt::AlignCenter);
        QB_angle_p->setDecimals(2);
        QB_angle_p->setToolTip(QStringLiteral("Roll角度环路P项，将角度差值转换为期望角速度"));
        QB_angle_p->setChanged(false);
    }

    if( QB_rate_p == nullptr){
        QB_rate_p = new UDoubleSpinBox();
        QB_rate_p->setRange(0.005f,0.55);
        QB_rate_p->setSingleStep(0.005);
        QB_rate_p->setValue(0);
        QB_rate_p->setAlignment(Qt::AlignCenter);
        QB_rate_p->setDecimals(3);
        QB_rate_p->setToolTip(QStringLiteral("Roll角速度环路P值"));
        QB_rate_p->setChanged(false);
    }

    if( QB_rate_i == nullptr){
        QB_rate_i = new UDoubleSpinBox();
        QB_rate_i->setRange(0.01f,2.0);
        QB_rate_i->setSingleStep(0.005);
        QB_rate_i->setValue(0);
        QB_rate_i->setAlignment(Qt::AlignCenter);
        QB_rate_i->setDecimals(3);
        QB_rate_i->setToolTip(QStringLiteral("Roll角速度环路I值"));
        QB_rate_i->setChanged(false);
    }

    if( QB_rate_imax == nullptr){
        QB_rate_imax = new UDoubleSpinBox();
        QB_rate_imax->setRange(0,1);
        QB_rate_imax->setSingleStep(0.01f);
        QB_rate_imax->setValue(0);
        QB_rate_imax->setAlignment(Qt::AlignCenter);
        QB_rate_imax->setDecimals(2);
        QB_rate_imax->setToolTip(QStringLiteral("Roll角速度环路I值限幅"));
        QB_rate_imax->setChanged(false);
    }
    if( QB_rate_d == nullptr){
        QB_rate_d = new UDoubleSpinBox();
        QB_rate_d->setRange(0,0.1);
        QB_rate_d->setSingleStep(0.001);
        QB_rate_d->setValue(0);
        QB_rate_d->setAlignment(Qt::AlignCenter);
        QB_rate_d->setDecimals(3);
        QB_rate_d->setToolTip(QStringLiteral("Roll角速度环路D值"));
        QB_rate_d->setChanged(false);
    }
    if( QB_rate_ff == nullptr){
        QB_rate_ff = new UDoubleSpinBox();
        QB_rate_ff->setRange(0,0.5);
        QB_rate_ff->setSingleStep(0.001);
        QB_rate_ff->setValue(0);
        QB_rate_ff->setAlignment(Qt::AlignCenter);
        QB_rate_ff->setDecimals(3);
        QB_rate_ff->setToolTip(QStringLiteral("Roll角速度环路feed forward值"));
        QB_rate_ff->setChanged(false);
    }

    if( QB_rate_slew_rate_max == nullptr){
        QB_rate_slew_rate_max = new UDoubleSpinBox();
        QB_rate_slew_rate_max->setRange(0,200);
        QB_rate_slew_rate_max->setSingleStep(0.5);
        QB_rate_slew_rate_max->setValue(0);
        QB_rate_slew_rate_max->setAlignment(Qt::AlignCenter);
        QB_rate_slew_rate_max->setDecimals(1);
        QB_rate_slew_rate_max->setToolTip(QStringLiteral("Roll角速度环转换速率限制:用于限制由P和D增益产生的压摆率上限。"
                                                         "如果速率反馈产生的控制动作幅度超过该值，则D+P增益会降低以遵守限制。"
                                                         "这限制了由过度增益引起的高频振荡的幅度。"
                                                         "零值将禁用此功能。"));
        QB_rate_slew_rate_max->setChanged(false);
    }

    // 按键
    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_download->setToolTip(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_upload->setToolTip(QStringLiteral("WidgetCMD_Action"));
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

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    QLabel *label_space_1 = new QLabel();
    QLabel *label_space_2 = new QLabel();
    label_space_1->setObjectName("widgetSpaceLabel");
    label_space_2->setObjectName("widgetSpaceLabel");

    widgetLayout->addWidget(titleLabel                    , 0, 0, 1, 7);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 1, 0, 11, 1);
    widgetLayout->addWidget(LB_Limit                    , 1, 1, 2, 1);
    widgetLayout->addWidget(LB__accel_max        , 1, 2, 1, 2);
    widgetLayout->addWidget(QB__accel_max        , 1, 4, 1, 2);
    widgetLayout->addWidget(LB__ang_vel_max      , 2, 2, 1, 2);
    widgetLayout->addWidget(QB__ang_vel_max      , 2, 4, 1, 2);


    widgetLayout->addWidget(label_space_1,          3,1,1,5);
    widgetLayout->addWidget(LB_Angle,                 4,1,1,1);
    widgetLayout->addWidget(LB_angle_p,            4, 2, 1, 2);
    widgetLayout->addWidget(QB_angle_p,            4, 4, 1, 2);


    widgetLayout->addWidget(label_space_2,        5,1,1,5);
    widgetLayout->addWidget(LB_Rate   ,            6, 1, 3, 1);

    widgetLayout->addWidget(LB_rate_p   ,            6, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_i   ,            7, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_d   ,            8, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_ff  ,            6, 4, 1, 1);
    widgetLayout->addWidget(LB_rate_imax,         7, 4, 1, 1);
    widgetLayout->addWidget(LB_rate_slew_rate_max,   8, 4, 1, 1);
    widgetLayout->addWidget(QB_rate_p   ,            6, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_i   ,            7, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_d   ,            8, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_ff  ,            6, 5, 1, 1);
    widgetLayout->addWidget(QB_rate_imax,            7, 5, 1, 1);
    widgetLayout->addWidget(QB_rate_slew_rate_max,   8, 5, 1, 1);

    widgetLayout->addLayout(widgetLayout_pb         ,10, 1, 1, 5);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 1, 6, 11, 1);

    widgetLayout->setColumnStretch(0,1);
    widgetLayout->setColumnStretch(6,1);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 11, 4, 1, 1);
}

void CFG_ParamRollControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamRollCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_att_roll_control_t pkt = link->getTVehicleParam().RollCtrl;
                QB__accel_max        ->setValue(pkt._accel_max);
                QB__ang_vel_max      ->setValue(pkt._ang_vel_max      );
                QB_angle_p           ->setValue(pkt.angle_p           );
                QB_rate_p            ->setValue(pkt.rate_p            );
                QB_rate_i            ->setValue(pkt.rate_i            );
                QB_rate_d            ->setValue(pkt.rate_d            );
                QB_rate_ff           ->setValue(pkt.rate_ff           );
                QB_rate_imax         ->setValue(pkt.rate_imax         );
                QB_rate_slew_rate_max->setValue(pkt.rate_slew_rate_max);

                QB__accel_max        ->setChanged(false);
                QB__ang_vel_max      ->setChanged(false);
                QB_angle_p           ->setChanged(false);
                QB_rate_p            ->setChanged(false);
                QB_rate_i            ->setChanged(false);
                QB_rate_d            ->setChanged(false);
                QB_rate_ff           ->setChanged(false);
                QB_rate_imax         ->setChanged(false);
                QB_rate_slew_rate_max->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamRollControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_att_roll_control_t pkt{};
        pkt.is_set = 1;
        pkt._accel_max         = QB__accel_max         ->value();
        pkt._ang_vel_max       = QB__ang_vel_max       ->value();
        pkt.angle_p            = QB_angle_p            ->value();
        pkt.rate_p             = QB_rate_p             ->value();
        pkt.rate_i             = QB_rate_i             ->value();
        pkt.rate_d             = QB_rate_d             ->value();
        pkt.rate_ff            = QB_rate_ff            ->value();
        pkt.rate_imax          = QB_rate_imax          ->value();
        pkt.rate_slew_rate_max = QB_rate_slew_rate_max ->value();
        link->do_setParamRollCtrl(pkt);
    }
}

CFG_ParamPitchControl::CFG_ParamPitchControl(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("widgetGroupBox_no_border");
}


void CFG_ParamPitchControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamPitchControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamPitchCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamPitchControl::upload_param);
}

void CFG_ParamPitchControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamPitchCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_att_pitch_control_t pkt = link->getTVehicleParam().PitchCtrl;
                QB__accel_max        ->setValue(pkt._accel_max);
                QB__ang_vel_max      ->setValue(pkt._ang_vel_max      );
                QB_angle_p           ->setValue(pkt.angle_p           );
                QB_rate_p            ->setValue(pkt.rate_p            );
                QB_rate_i            ->setValue(pkt.rate_i            );
                QB_rate_d            ->setValue(pkt.rate_d            );
                QB_rate_ff           ->setValue(pkt.rate_ff           );
                QB_rate_imax         ->setValue(pkt.rate_imax         );
                QB_rate_slew_rate_max->setValue(pkt.rate_slew_rate_max);

                QB__accel_max        ->setChanged(false);
                QB__ang_vel_max      ->setChanged(false);
                QB_angle_p           ->setChanged(false);
                QB_rate_p            ->setChanged(false);
                QB_rate_i            ->setChanged(false);
                QB_rate_d            ->setChanged(false);
                QB_rate_ff           ->setChanged(false);
                QB_rate_imax         ->setChanged(false);
                QB_rate_slew_rate_max->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamPitchControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_att_pitch_control_t pkt{};
        pkt.is_set = 1;
        pkt._accel_max         = QB__accel_max         ->value();
        pkt._ang_vel_max       = QB__ang_vel_max       ->value();
        pkt.angle_p            = QB_angle_p            ->value();
        pkt.rate_p             = QB_rate_p             ->value();
        pkt.rate_i             = QB_rate_i             ->value();
        pkt.rate_d             = QB_rate_d             ->value();
        pkt.rate_ff            = QB_rate_ff            ->value();
        pkt.rate_imax          = QB_rate_imax          ->value();
        pkt.rate_slew_rate_max = QB_rate_slew_rate_max ->value();
        link->do_setParamPitchCtrl(pkt);
    }
}

void CFG_ParamPitchControl::widget_init()
{

    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("俯仰控制参数"));
        this->titleLabel->setObjectName("CfgWIdgetTitle");
        this->titleLabel->setAlignment(Qt::AlignCenter);
    }
    // 标签
    if( LB__ang_vel_max == nullptr){
        LB__ang_vel_max = new QLabel(QStringLiteral("最大角速度:"));
        LB__ang_vel_max->setToolTip(QStringLiteral("最大角速度(deg/s)"));
        LB__ang_vel_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__ang_vel_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__accel_max == nullptr){
        LB__accel_max = new QLabel(QStringLiteral("最大加速度:"));
        LB__accel_max->setToolTip(QStringLiteral("最大加速度(deg/ss)"));
        LB__accel_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__accel_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_angle_p == nullptr){
        LB_angle_p = new QLabel(QStringLiteral("P:"));
        LB_angle_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_angle_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_p == nullptr){
        LB_rate_p = new QLabel(QStringLiteral("P:"));
        LB_rate_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_i == nullptr){
        LB_rate_i = new QLabel(QStringLiteral("I:"));
        LB_rate_i->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_i->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_d == nullptr){
        LB_rate_d = new QLabel(QStringLiteral("D:"));
        LB_rate_d->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_d->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_ff == nullptr){
        LB_rate_ff = new QLabel(QStringLiteral("FF:"));
        LB_rate_ff->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_ff->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_imax == nullptr){
        LB_rate_imax = new QLabel(QStringLiteral("Imax:"));
        LB_rate_imax->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_imax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_slew_rate_max == nullptr){
        LB_rate_slew_rate_max = new QLabel(QStringLiteral("Limit:"));
        LB_rate_slew_rate_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_slew_rate_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_Limit == nullptr){
        LB_Limit = new QLabel(QStringLiteral("限定参数"));
        LB_Limit->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Limit->setAlignment(Qt::AlignCenter);
    }
    if( LB_Angle == nullptr){
        LB_Angle = new QLabel(QStringLiteral("角度控制"));
        LB_Angle->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Angle->setAlignment(Qt::AlignCenter);
    }
    if( LB_Rate == nullptr){
        LB_Rate = new QLabel(QStringLiteral("速率控制"));
        LB_Rate->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Rate->setAlignment(Qt::AlignCenter);
    }

    if( QB__accel_max == nullptr){
        QB__accel_max = new UDoubleSpinBox();
        QB__accel_max->setRange(0,1800);
        QB__accel_max->setSingleStep(1);
        QB__accel_max->setValue(0);
        QB__accel_max->setAlignment(Qt::AlignCenter);
        QB__accel_max->setDecimals(1);
        QB__accel_max->setToolTip(QStringLiteral("Pitch轴的最大加速度"));
        QB__accel_max->setChanged(false);
    }

    if( QB__ang_vel_max == nullptr){
        QB__ang_vel_max = new UDoubleSpinBox();
        QB__ang_vel_max->setRange(0,1200.0f);
        QB__ang_vel_max->setSingleStep(1);
        QB__ang_vel_max->setValue(0);
        QB__ang_vel_max->setAlignment(Qt::AlignCenter);
        QB__ang_vel_max->setDecimals(1);
        QB__ang_vel_max->setToolTip(QStringLiteral("Pitch轴的最大角速度"));
        QB__ang_vel_max->setChanged(false);
    }

    if( QB_angle_p == nullptr){
        QB_angle_p = new UDoubleSpinBox();
        QB_angle_p->setRange(2.5f,12.0f);
        QB_angle_p->setSingleStep(0.1f);
        QB_angle_p->setValue(0);
        QB_angle_p->setAlignment(Qt::AlignCenter);
        QB_angle_p->setDecimals(2);
        QB_angle_p->setToolTip(QStringLiteral("Pitch角度环路P项，将角度差值转换为期望角速度"));
        QB_angle_p->setChanged(false);
    }

    if( QB_rate_p == nullptr){
        QB_rate_p = new UDoubleSpinBox();
        QB_rate_p->setRange(0.005f,0.55);
        QB_rate_p->setSingleStep(0.005);
        QB_rate_p->setValue(0);
        QB_rate_p->setAlignment(Qt::AlignCenter);
        QB_rate_p->setDecimals(3);
        QB_rate_p->setToolTip(QStringLiteral("Pitch角速度环路P值"));
        QB_rate_p->setChanged(false);
    }

    if( QB_rate_i == nullptr){
        QB_rate_i = new UDoubleSpinBox();
        QB_rate_i->setRange(0.01f,2.0);
        QB_rate_i->setSingleStep(0.005);
        QB_rate_i->setValue(0);
        QB_rate_i->setAlignment(Qt::AlignCenter);
        QB_rate_i->setDecimals(3);
        QB_rate_i->setToolTip(QStringLiteral("Pitch角速度环路I值"));
        QB_rate_i->setChanged(false);
    }

    if( QB_rate_imax == nullptr){
        QB_rate_imax = new UDoubleSpinBox();
        QB_rate_imax->setRange(0,1);
        QB_rate_imax->setSingleStep(0.01f);
        QB_rate_imax->setValue(0);
        QB_rate_imax->setAlignment(Qt::AlignCenter);
        QB_rate_imax->setDecimals(2);
        QB_rate_imax->setToolTip(QStringLiteral("Pitch角速度环路I值限幅"));
        QB_rate_imax->setChanged(false);
    }
    if( QB_rate_d == nullptr){
        QB_rate_d = new UDoubleSpinBox();
        QB_rate_d->setRange(0,0.1);
        QB_rate_d->setSingleStep(0.001);
        QB_rate_d->setValue(0);
        QB_rate_d->setAlignment(Qt::AlignCenter);
        QB_rate_d->setDecimals(3);
        QB_rate_d->setToolTip(QStringLiteral("Pitch角速度环路D值"));
        QB_rate_d->setChanged(false);
    }
    if( QB_rate_ff == nullptr){
        QB_rate_ff = new UDoubleSpinBox();
        QB_rate_ff->setRange(0,0.5);
        QB_rate_ff->setSingleStep(0.001);
        QB_rate_ff->setValue(0);
        QB_rate_ff->setAlignment(Qt::AlignCenter);
        QB_rate_ff->setDecimals(3);
        QB_rate_ff->setToolTip(QStringLiteral("Pitch角速度环路feed forward值"));
        QB_rate_ff->setChanged(false);
    }

    if( QB_rate_slew_rate_max == nullptr){
        QB_rate_slew_rate_max = new UDoubleSpinBox();
        QB_rate_slew_rate_max->setRange(0,200);
        QB_rate_slew_rate_max->setSingleStep(0.5);
        QB_rate_slew_rate_max->setValue(0);
        QB_rate_slew_rate_max->setAlignment(Qt::AlignCenter);
        QB_rate_slew_rate_max->setDecimals(1);
        QB_rate_slew_rate_max->setToolTip(QStringLiteral("Pitch角速度环转换速率限制:用于限制由P和D增益产生的压摆率上限。"
                                                         "如果速率反馈产生的控制动作幅度超过该值，则D+P增益会降低以遵守限制。"
                                                         "这限制了由过度增益引起的高频振荡的幅度。"
                                                         "零值将禁用此功能。"));
        QB_rate_slew_rate_max->setChanged(false);
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

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }


    QLabel *label_space_1 = new QLabel();
    QLabel *label_space_2 = new QLabel();
    label_space_1->setObjectName("widgetSpaceLabel");
    label_space_2->setObjectName("widgetSpaceLabel");

    widgetLayout->addWidget(titleLabel                    , 0, 0, 1, 7);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 1, 0, 11, 1);
    widgetLayout->addWidget(LB_Limit                    , 1, 1, 2, 1);
    widgetLayout->addWidget(LB__accel_max        , 1, 2, 1, 2);
    widgetLayout->addWidget(QB__accel_max        , 1, 4, 1, 2);
    widgetLayout->addWidget(LB__ang_vel_max      , 2, 2, 1, 2);
    widgetLayout->addWidget(QB__ang_vel_max      , 2, 4, 1, 2);


    widgetLayout->addWidget(label_space_1,          3,1,1,5);
    widgetLayout->addWidget(LB_Angle,                 4,1,1,1);
    widgetLayout->addWidget(LB_angle_p,            4, 2, 1, 2);
    widgetLayout->addWidget(QB_angle_p,            4, 4, 1, 2);


    widgetLayout->addWidget(label_space_2,        5,1,1,5);
    widgetLayout->addWidget(LB_Rate   ,            6, 1, 3, 1);

    widgetLayout->addWidget(LB_rate_p   ,            6, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_i   ,            7, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_d   ,            8, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_ff  ,            6, 4, 1, 1);
    widgetLayout->addWidget(LB_rate_imax,         7, 4, 1, 1);
    widgetLayout->addWidget(LB_rate_slew_rate_max,   8, 4, 1, 1);
    widgetLayout->addWidget(QB_rate_p   ,            6, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_i   ,            7, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_d   ,            8, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_ff  ,            6, 5, 1, 1);
    widgetLayout->addWidget(QB_rate_imax,            7, 5, 1, 1);
    widgetLayout->addWidget(QB_rate_slew_rate_max,   8, 5, 1, 1);

    widgetLayout->addLayout(widgetLayout_pb         ,10, 1, 1, 5);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 1, 6, 11, 1);

    widgetLayout->setColumnStretch(0,1);
    widgetLayout->setColumnStretch(6,1);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 11, 4, 1, 1);

}

CFG_ParamYawControl::CFG_ParamYawControl(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("widgetGroupBox_no_border");
}


void CFG_ParamYawControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamYawControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamYawCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamYawControl::upload_param);
}

void CFG_ParamYawControl::widget_init()
{

    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("航向控制参数"));
        this->titleLabel->setObjectName("CfgWIdgetTitle");
        this->titleLabel->setAlignment(Qt::AlignCenter);
    }
    // 标签
    if( LB__ang_vel_max == nullptr){
        LB__ang_vel_max = new QLabel(QStringLiteral("最大角速度"));
        LB__ang_vel_max->setToolTip(QStringLiteral("最大角速度(deg/s)"));
        LB__ang_vel_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__ang_vel_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__accel_max == nullptr){
        LB__accel_max = new QLabel(QStringLiteral("最大加速度:"));
        LB__accel_max->setToolTip(QStringLiteral("最大加速度(deg/ss)"));
        LB__accel_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__accel_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB__slew_yaw == nullptr){
        LB__slew_yaw = new QLabel(QStringLiteral("最大目标角速度:"));
        LB__slew_yaw->setToolTip(QStringLiteral("最大目标角速度(deg/s)"));
        LB__slew_yaw->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB__slew_yaw->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_angle_p == nullptr){
        LB_angle_p = new QLabel(QStringLiteral("P:"));
        LB_angle_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_angle_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_p == nullptr){
        LB_rate_p = new QLabel(QStringLiteral("P:"));
        LB_rate_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_i == nullptr){
        LB_rate_i = new QLabel(QStringLiteral("I:"));
        LB_rate_i->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_i->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_d == nullptr){
        LB_rate_d = new QLabel(QStringLiteral("D:"));
        LB_rate_d->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_d->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_ff == nullptr){
        LB_rate_ff = new QLabel(QStringLiteral("FF:"));
        LB_rate_ff->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_ff->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_imax == nullptr){
        LB_rate_imax = new QLabel(QStringLiteral("Imax:"));
        LB_rate_imax->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_imax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    if( LB_rate_slew_rate_max == nullptr){
        LB_rate_slew_rate_max = new QLabel(QStringLiteral("Limit:"));
        LB_rate_slew_rate_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_rate_slew_rate_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_Limit == nullptr){
        LB_Limit = new QLabel(QStringLiteral("限定参数"));
        LB_Limit->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Limit->setAlignment(Qt::AlignCenter);
    }
    if( LB_Angle == nullptr){
        LB_Angle = new QLabel(QStringLiteral("角度控制"));
        LB_Angle->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Angle->setAlignment(Qt::AlignCenter);
    }
    if( LB_Rate == nullptr){
        LB_Rate = new QLabel(QStringLiteral("速率控制"));
        LB_Rate->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Rate->setAlignment(Qt::AlignCenter);
    }

    if( QB__accel_max == nullptr){
        QB__accel_max = new UDoubleSpinBox();
        QB__accel_max->setRange(0,1800);
        QB__accel_max->setSingleStep(1);
        QB__accel_max->setValue(0);
        QB__accel_max->setAlignment(Qt::AlignCenter);
        QB__accel_max->setDecimals(1);
        QB__accel_max->setToolTip(QStringLiteral("Yaw轴的最大加速度"));
        QB__accel_max->setChanged(false);
    }

    if( QB__ang_vel_max == nullptr){
        QB__ang_vel_max = new UDoubleSpinBox();
        QB__ang_vel_max->setRange(0,1200.0f);
        QB__ang_vel_max->setSingleStep(1);
        QB__ang_vel_max->setValue(0);
        QB__ang_vel_max->setAlignment(Qt::AlignCenter);
        QB__ang_vel_max->setDecimals(1);
        QB__ang_vel_max->setToolTip(QStringLiteral("Yaw轴的最大角速度"));
        QB__ang_vel_max->setChanged(false);
    }

    if( QB_angle_p == nullptr){
        QB_angle_p = new UDoubleSpinBox();
        QB_angle_p->setRange(2.5f,12.0f);
        QB_angle_p->setSingleStep(0.1f);
        QB_angle_p->setValue(0);
        QB_angle_p->setAlignment(Qt::AlignCenter);
        QB_angle_p->setDecimals(2);
        QB_angle_p->setToolTip(QStringLiteral("Yaw角度环路P项，将角度差值转换为期望角速度"));
        QB_angle_p->setChanged(false);
    }

    if( QB_rate_p == nullptr){
        QB_rate_p = new UDoubleSpinBox();
        QB_rate_p->setRange(0.005f,0.55);
        QB_rate_p->setSingleStep(0.005);
        QB_rate_p->setValue(0);
        QB_rate_p->setAlignment(Qt::AlignCenter);
        QB_rate_p->setDecimals(3);
        QB_rate_p->setToolTip(QStringLiteral("Yaw角速度环路P值"));
        QB_rate_p->setChanged(false);
    }

    if( QB_rate_i == nullptr){
        QB_rate_i = new UDoubleSpinBox();
        QB_rate_i->setRange(0.01f,2.0);
        QB_rate_i->setSingleStep(0.005);
        QB_rate_i->setValue(0);
        QB_rate_i->setAlignment(Qt::AlignCenter);
        QB_rate_i->setDecimals(3);
        QB_rate_i->setToolTip(QStringLiteral("Yaw角速度环路I值"));
        QB_rate_i->setChanged(false);
    }

    if( QB_rate_imax == nullptr){
        QB_rate_imax = new UDoubleSpinBox();
        QB_rate_imax->setRange(0,1);
        QB_rate_imax->setSingleStep(0.01f);
        QB_rate_imax->setValue(0);
        QB_rate_imax->setAlignment(Qt::AlignCenter);
        QB_rate_imax->setDecimals(2);
        QB_rate_imax->setToolTip(QStringLiteral("Yaw角速度环路I值限幅"));
        QB_rate_imax->setChanged(false);
    }
    if( QB_rate_d == nullptr){
        QB_rate_d = new UDoubleSpinBox();
        QB_rate_d->setRange(0,0.1);
        QB_rate_d->setSingleStep(0.001);
        QB_rate_d->setValue(0);
        QB_rate_d->setAlignment(Qt::AlignCenter);
        QB_rate_d->setDecimals(3);
        QB_rate_d->setToolTip(QStringLiteral("Yaw角速度环路D值"));
        QB_rate_d->setChanged(false);
    }
    if( QB_rate_ff == nullptr){
        QB_rate_ff = new UDoubleSpinBox();
        QB_rate_ff->setRange(0,0.5);
        QB_rate_ff->setSingleStep(0.001);
        QB_rate_ff->setValue(0);
        QB_rate_ff->setAlignment(Qt::AlignCenter);
        QB_rate_ff->setDecimals(3);
        QB_rate_ff->setToolTip(QStringLiteral("Yaw角速度环路feed forward值"));
        QB_rate_ff->setChanged(false);
    }

    if( QB_rate_slew_rate_max == nullptr){
        QB_rate_slew_rate_max = new UDoubleSpinBox();
        QB_rate_slew_rate_max->setRange(0,200);
        QB_rate_slew_rate_max->setSingleStep(0.5);
        QB_rate_slew_rate_max->setValue(0);
        QB_rate_slew_rate_max->setAlignment(Qt::AlignCenter);
        QB_rate_slew_rate_max->setDecimals(1);
        QB_rate_slew_rate_max->setToolTip(QStringLiteral("Yaw角速度环转换速率限制:用于限制由P和D增益产生的压摆率上限。"
                                                         "如果速率反馈产生的控制动作幅度超过该值，则D+P增益会降低以遵守限制。"
                                                         "这限制了由过度增益引起的高频振荡的幅度。"
                                                         "零值将禁用此功能。"));
        QB_rate_slew_rate_max->setChanged(false);
    }
    if( QB__slew_yaw == nullptr){
        QB__slew_yaw = new UDoubleSpinBox();
        QB__slew_yaw->setRange(5,180);
        QB__slew_yaw->setSingleStep(1);
        QB__slew_yaw->setValue(0);
        QB__slew_yaw->setAlignment(Qt::AlignCenter);
        QB__slew_yaw->setDecimals(1);
        QB__slew_yaw->setToolTip(QStringLiteral("Yaw轴最大的目标角速度"));
        QB__slew_yaw->setChanged(false);
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

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }


    QLabel *label_space_1 = new QLabel();
    QLabel *label_space_2 = new QLabel();
    label_space_1->setObjectName("widgetSpaceLabel");
    label_space_2->setObjectName("widgetSpaceLabel");

    widgetLayout->addWidget(titleLabel                    , 0, 0, 1, 7);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 1, 0, 11, 1);
    widgetLayout->addWidget(LB_Limit                    , 1, 1, 3, 1);
    widgetLayout->addWidget(LB__accel_max        , 1, 2, 1, 2);
    widgetLayout->addWidget(QB__accel_max        , 1, 4, 1, 2);
    widgetLayout->addWidget(LB__ang_vel_max      , 2, 2, 1, 2);
    widgetLayout->addWidget(QB__ang_vel_max      , 2, 4, 1, 2);
    widgetLayout->addWidget(LB__slew_yaw      , 3, 2, 1, 2);
    widgetLayout->addWidget(QB__slew_yaw      , 3, 4, 1, 2);


    widgetLayout->addWidget(label_space_1,          4,1,1,5);
    widgetLayout->addWidget(LB_Angle,                 5,1,1,1);
    widgetLayout->addWidget(LB_angle_p,            5, 2, 1, 2);
    widgetLayout->addWidget(QB_angle_p,            5, 4, 1, 2);


    widgetLayout->addWidget(label_space_2,        6,1,1,5);
    widgetLayout->addWidget(LB_Rate   ,            7, 1, 3, 1);

    widgetLayout->addWidget(LB_rate_p   ,            7, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_i   ,            8, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_d   ,            9, 2, 1, 1);
    widgetLayout->addWidget(LB_rate_ff  ,            7, 4, 1, 1);
    widgetLayout->addWidget(LB_rate_imax,         8, 4, 1, 1);
    widgetLayout->addWidget(LB_rate_slew_rate_max,   9, 4, 1, 1);
    widgetLayout->addWidget(QB_rate_p   ,            7, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_i   ,            8, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_d   ,            9, 3, 1, 1);
    widgetLayout->addWidget(QB_rate_ff  ,            7, 5, 1, 1);
    widgetLayout->addWidget(QB_rate_imax,            8, 5, 1, 1);
    widgetLayout->addWidget(QB_rate_slew_rate_max,   9, 5, 1, 1);

    widgetLayout->addLayout(widgetLayout_pb         ,10, 1, 1, 5);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 1, 6, 11, 1);

    widgetLayout->setColumnStretch(0,1);
    widgetLayout->setColumnStretch(6,1);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding)                    , 11, 4, 1, 1);


}

void CFG_ParamYawControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamYawCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_att_yaw_control_t pkt = link->getTVehicleParam().YawCtrl;
                QB__accel_max        ->setValue(pkt._accel_max);
                QB__ang_vel_max      ->setValue(pkt._ang_vel_max      );
                QB_angle_p           ->setValue(pkt.angle_p           );
                QB_rate_p            ->setValue(pkt.rate_p            );
                QB_rate_i            ->setValue(pkt.rate_i            );
                QB_rate_d            ->setValue(pkt.rate_d            );
                QB_rate_ff           ->setValue(pkt.rate_ff           );
                QB_rate_imax         ->setValue(pkt.rate_imax         );
                QB_rate_slew_rate_max->setValue(pkt.rate_slew_rate_max);
                QB__slew_yaw->setValue(pkt._slew_yaw*0.01);

                QB__accel_max        ->setChanged(false);
                QB__ang_vel_max      ->setChanged(false);
                QB_angle_p           ->setChanged(false);
                QB_rate_p            ->setChanged(false);
                QB_rate_i            ->setChanged(false);
                QB_rate_d            ->setChanged(false);
                QB_rate_ff           ->setChanged(false);
                QB_rate_imax         ->setChanged(false);
                QB_rate_slew_rate_max->setChanged(false);
                QB__slew_yaw->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamYawControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_att_yaw_control_t pkt{};
        pkt.is_set = 1;
        pkt._accel_max         = QB__accel_max         ->value();
        pkt._ang_vel_max       = QB__ang_vel_max       ->value();
        pkt.angle_p            = QB_angle_p            ->value();
        pkt.rate_p             = QB_rate_p             ->value();
        pkt.rate_i             = QB_rate_i             ->value();
        pkt.rate_d             = QB_rate_d             ->value();
        pkt.rate_ff            = QB_rate_ff            ->value();
        pkt.rate_imax          = QB_rate_imax          ->value();
        pkt.rate_slew_rate_max = QB_rate_slew_rate_max ->value();
        pkt._slew_yaw          = QB__slew_yaw ->value()*100;
        link->do_setParamYawCtrl(pkt);
    }
}

