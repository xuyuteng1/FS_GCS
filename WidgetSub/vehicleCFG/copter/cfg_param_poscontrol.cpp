/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_param_poscontrol.h"
#include "DMMM.h"
#include <qmath.h>

CFG_ParamPosZControl::CFG_ParamPosZControl(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("stackedSubWidget");
}



void CFG_ParamPosZControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamPosZControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamPosZCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamPosZControl::upload_param);
}

void CFG_ParamPosZControl::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("高度控制参数"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    // 标签
    if( LB_shaping_jerk == nullptr){
        LB_shaping_jerk = new QLabel(QStringLiteral("目标加速度变化率:"));
        LB_shaping_jerk->setToolTip(QStringLiteral("目标加速度变化率(m/sss)"));
        LB_shaping_jerk->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_shaping_jerk->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_pos_p == nullptr){
        LB_pos_p = new QLabel(QStringLiteral("P:"));
        LB_pos_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_pos_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_p == nullptr){
        LB_vel_p = new QLabel(QStringLiteral("P:"));
        LB_vel_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_i == nullptr){
        LB_vel_i = new QLabel(QStringLiteral("I:"));
        LB_vel_i->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_i->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_d == nullptr){
        LB_vel_d = new QLabel(QStringLiteral("D:"));
        LB_vel_d->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_d->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_ff == nullptr){
        LB_vel_ff = new QLabel(QStringLiteral("FF:"));
        LB_vel_ff->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_ff->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_imax == nullptr){
        LB_vel_imax = new QLabel(QStringLiteral("Imax:"));
        LB_vel_imax->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_imax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_acc_p == nullptr){
        LB_acc_p = new QLabel(QStringLiteral("P:"));
        LB_acc_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_acc_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_acc_i == nullptr){
        LB_acc_i = new QLabel(QStringLiteral("I:"));
        LB_acc_i->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_acc_i->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_acc_d == nullptr){
        LB_acc_d = new QLabel(QStringLiteral("D:"));
        LB_acc_d->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_acc_d->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_acc_ff == nullptr){
        LB_acc_ff = new QLabel(QStringLiteral("FF:"));
        LB_acc_ff->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_acc_ff->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_acc_imax == nullptr){
        LB_acc_imax = new QLabel(QStringLiteral("Imax:"));
        LB_acc_imax->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_acc_imax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_acc_slew_rate_max == nullptr){
        LB_acc_slew_rate_max = new QLabel(QStringLiteral("Limit:"));
        LB_acc_slew_rate_max->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_acc_slew_rate_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }



    if( QB_shaping_jerk == nullptr){
        QB_shaping_jerk = new UDoubleSpinBox();
        QB_shaping_jerk->setRange(5,50);
        QB_shaping_jerk->setSingleStep(1);
        QB_shaping_jerk->setValue(0);
        QB_shaping_jerk->setAlignment(Qt::AlignCenter);
        QB_shaping_jerk->setDecimals(0);
        QB_shaping_jerk->setToolTip(QStringLiteral("垂直方向目标加速度变化率限制"));
        QB_shaping_jerk->setChanged(false);
    }
    if( QB_pos_p == nullptr){
        QB_pos_p = new UDoubleSpinBox();
        QB_pos_p->setRange(1,3);
        QB_pos_p->setSingleStep(0.05);
        QB_pos_p->setValue(0);
        QB_pos_p->setAlignment(Qt::AlignCenter);
        QB_pos_p->setDecimals(3);
        QB_pos_p->setToolTip(QStringLiteral("垂直位置P项"));
        QB_pos_p->setChanged(false);
    }
    if( QB_vel_p == nullptr){
        QB_vel_p = new UDoubleSpinBox();
        QB_vel_p->setRange(1,8);
        QB_vel_p->setSingleStep(0.05);
        QB_vel_p->setValue(0);
        QB_vel_p->setAlignment(Qt::AlignCenter);
        QB_vel_p->setDecimals(3);
        QB_vel_p->setToolTip(QStringLiteral("垂直速度P项"));
        QB_vel_p->setChanged(false);
    }
    if( QB_vel_i == nullptr){
        QB_vel_i = new UDoubleSpinBox();
        QB_vel_i->setRange(0.02,1);
        QB_vel_i->setSingleStep(0.01);
        QB_vel_i->setValue(0);
        QB_vel_i->setAlignment(Qt::AlignCenter);
        QB_vel_i->setDecimals(3);
        QB_vel_i->setToolTip(QStringLiteral("垂直速度I项"));
        QB_vel_i->setChanged(false);
    }
    if( QB_vel_d == nullptr){
        QB_vel_d = new UDoubleSpinBox();
        QB_vel_d->setRange(0,1);
        QB_vel_d->setSingleStep(0.001);
        QB_vel_d->setValue(0);
        QB_vel_d->setAlignment(Qt::AlignCenter);
        QB_vel_d->setDecimals(3);
        QB_vel_d->setToolTip(QStringLiteral("垂直速度D项"));
        QB_vel_d->setChanged(false);
    }
    if( QB_vel_ff == nullptr){
        QB_vel_ff = new UDoubleSpinBox();
        QB_vel_ff->setRange(0,1);
        QB_vel_ff->setSingleStep(0.01);
        QB_vel_ff->setValue(0);
        QB_vel_ff->setAlignment(Qt::AlignCenter);
        QB_vel_ff->setDecimals(3);
        QB_vel_ff->setToolTip(QStringLiteral("垂直速度FF项"));
        QB_vel_ff->setChanged(false);
    }
    if( QB_vel_imax == nullptr){
        QB_vel_imax = new UDoubleSpinBox();
        QB_vel_imax->setRange(1,8);
        QB_vel_imax->setSingleStep(0.05);
        QB_vel_imax->setValue(0);
        QB_vel_imax->setAlignment(Qt::AlignCenter);
        QB_vel_imax->setDecimals(3);
        QB_vel_imax->setToolTip(QStringLiteral("垂直速度积分限幅"));
        QB_vel_imax->setChanged(false);
    }
    if( QB_acc_p == nullptr){
        QB_acc_p = new UDoubleSpinBox();
        QB_acc_p->setRange(0.2,1.5);
        QB_acc_p->setSingleStep(0.05);
        QB_acc_p->setValue(0);
        QB_acc_p->setAlignment(Qt::AlignCenter);
        QB_acc_p->setDecimals(3);
        QB_acc_p->setToolTip(QStringLiteral("垂直加速度P项"));
        QB_acc_p->setChanged(false);
    }
    if( QB_acc_i == nullptr){
        QB_acc_i = new UDoubleSpinBox();
        QB_acc_i->setRange(0,3);
        QB_acc_i->setSingleStep(0.05);
        QB_acc_i->setValue(0);
        QB_acc_i->setAlignment(Qt::AlignCenter);
        QB_acc_i->setDecimals(3);
        QB_acc_i->setToolTip(QStringLiteral("垂直加速度I项"));
        QB_acc_i->setChanged(false);
    }
    if( QB_acc_d == nullptr){
        QB_acc_d = new UDoubleSpinBox();
        QB_acc_d->setRange(0,0.4);
        QB_acc_d->setSingleStep(0.001);
        QB_acc_d->setValue(0);
        QB_acc_d->setAlignment(Qt::AlignCenter);
        QB_acc_d->setDecimals(3);
        QB_acc_d->setToolTip(QStringLiteral("垂直加速度D项"));
        QB_acc_d->setChanged(false);
    }
    if( QB_acc_ff == nullptr){
        QB_acc_ff = new UDoubleSpinBox();
        QB_acc_ff->setRange(0,0.5);
        QB_acc_ff->setSingleStep(0.001);
        QB_acc_ff->setValue(0);
        QB_acc_ff->setAlignment(Qt::AlignCenter);
        QB_acc_ff->setDecimals(3);
        QB_acc_ff->setToolTip(QStringLiteral("垂直加速度FF项"));
        QB_acc_ff->setChanged(false);
    }
    if( QB_acc_imax == nullptr){
        QB_acc_imax = new UDoubleSpinBox();
        QB_acc_imax->setRange(0,1000);
        QB_acc_imax->setSingleStep(1);
        QB_acc_imax->setValue(0);
        QB_acc_imax->setAlignment(Qt::AlignCenter);
        QB_acc_imax->setDecimals(0);
        QB_acc_imax->setToolTip(QStringLiteral("垂直加速度积分限幅"));
        QB_acc_imax->setChanged(false);
    }
    if( QB_acc_slew_rate_max == nullptr){
        QB_acc_slew_rate_max = new UDoubleSpinBox();
        QB_acc_slew_rate_max->setRange(0,200);
        QB_acc_slew_rate_max->setSingleStep(0.5);
        QB_acc_slew_rate_max->setValue(0);
        QB_acc_slew_rate_max->setAlignment(Qt::AlignCenter);
        QB_acc_slew_rate_max->setDecimals(1);
        QB_acc_slew_rate_max->setToolTip(QStringLiteral("输出加速度变化限幅"));
        QB_acc_slew_rate_max->setChanged(false);
    }

    if( LB_Limit == nullptr){
        LB_Limit = new QLabel(QStringLiteral("限定参数"));
        LB_Limit->setObjectName("widgetNameLabel");
    }
    if( LB_Pos == nullptr){
        LB_Pos = new QLabel(QStringLiteral("位置控制"));
        LB_Pos->setObjectName("widgetNameLabel");
    }
    if( LB_Vel == nullptr){
        LB_Vel = new QLabel(QStringLiteral("速度控制"));
        LB_Vel->setObjectName("widgetNameLabel");
    }
    if( LB_Acc == nullptr){
        LB_Acc = new QLabel(QStringLiteral("加速度控制"));
        LB_Acc->setObjectName("widgetNameLabel");
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


    QLabel *LB_space_1 = new QLabel();
    QLabel *LB_space_2 = new QLabel();
    QLabel *LB_space_3 = new QLabel();
    LB_space_1->setObjectName("widgetSpaceLabel");
    LB_space_2->setObjectName("widgetSpaceLabel");
    LB_space_3->setObjectName("widgetSpaceLabel");

    this->widgetLayout->addWidget(this->titleLabel,0,0,1,7);

    this->widgetLayout->addWidget(this->LB_Limit,1,1,1,1);
    this->widgetLayout->addWidget(this->LB_shaping_jerk,1,2,1,2);
    this->widgetLayout->addWidget(this->QB_shaping_jerk,1,4,1,2);

    this->widgetLayout->addWidget(LB_space_1,2,1,1,5);

    this->widgetLayout->addWidget(this->LB_Pos,3,1,1,1);
    this->widgetLayout->addWidget(this->LB_pos_p,3,2,1,2);
    this->widgetLayout->addWidget(this->QB_pos_p,3,4,1,2);

    this->widgetLayout->addWidget(LB_space_2,4,1,1,5);

    this->widgetLayout->addWidget(LB_Vel,5,1,3,1);
    this->widgetLayout->addWidget(LB_vel_p   ,            5, 2, 1, 1);
    this->widgetLayout->addWidget(LB_vel_i   ,            6, 2, 1, 1);
    this->widgetLayout->addWidget(LB_vel_d   ,            7, 2, 1, 1);
    this->widgetLayout->addWidget(LB_vel_ff  ,            5, 4, 1, 1);
    this->widgetLayout->addWidget(LB_vel_imax,            6, 4, 1, 1);
    this->widgetLayout->addWidget(QB_vel_p   ,            5, 3, 1, 1);
    this->widgetLayout->addWidget(QB_vel_i   ,            6, 3, 1, 1);
    this->widgetLayout->addWidget(QB_vel_d   ,            7, 3, 1, 1);
    this->widgetLayout->addWidget(QB_vel_ff  ,            5, 5, 1, 1);
    this->widgetLayout->addWidget(QB_vel_imax,            6, 5, 1, 1);

    this->widgetLayout->addWidget(LB_space_3,8,1,1,5);

    this->widgetLayout->addWidget(LB_Acc,9,1,3,1);
    this->widgetLayout->addWidget(LB_acc_p            ,            9, 2, 1, 1);
    this->widgetLayout->addWidget(LB_acc_i            ,            10, 2, 1, 1);
    this->widgetLayout->addWidget(LB_acc_d            ,            11,2 , 1, 1);
    this->widgetLayout->addWidget(LB_acc_ff           ,            9, 4, 1, 1);
    this->widgetLayout->addWidget(LB_acc_imax         ,            10, 4, 1, 1);
    this->widgetLayout->addWidget(LB_acc_slew_rate_max,            11, 4, 1, 1);
    this->widgetLayout->addWidget(QB_acc_p            ,            9, 3, 1, 1);
    this->widgetLayout->addWidget(QB_acc_i            ,            10, 3, 1, 1);
    this->widgetLayout->addWidget(QB_acc_d            ,            11, 3, 1, 1);
    this->widgetLayout->addWidget(QB_acc_ff           ,            9, 5, 1, 1);
    this->widgetLayout->addWidget(QB_acc_imax         ,            10, 5, 1, 1);
    this->widgetLayout->addWidget(QB_acc_slew_rate_max,            11, 5, 1, 1);

    widgetLayout->addLayout(widgetLayout_pb         ,12, 1, 1, 5);


    this->widgetLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,0,11,1);
    this->widgetLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,6,11,1);
    this->widgetLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),13,3,1,1);


    this->widgetLayout->setColumnStretch(0,1);
    this->widgetLayout->setColumnStretch(6,1);

}

void CFG_ParamPosZControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamPosZCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_posz_control_t pkt = link->getTVehicleParam().PosZCtrl;
                QB_shaping_jerk     ->setValue(pkt.shaping_jerk     );
                QB_pos_p            ->setValue(pkt.pos_p            );
                QB_vel_p            ->setValue(pkt.vel_p            );
                QB_vel_i            ->setValue(pkt.vel_i            );
                QB_vel_d            ->setValue(pkt.vel_d            );
                QB_vel_ff           ->setValue(pkt.vel_ff           );
                QB_vel_imax         ->setValue(pkt.vel_imax         );
                QB_acc_p            ->setValue(pkt.acc_p            );
                QB_acc_i            ->setValue(pkt.acc_i            );
                QB_acc_d            ->setValue(pkt.acc_d            );
                QB_acc_ff           ->setValue(pkt.acc_ff           );
                QB_acc_imax         ->setValue(pkt.acc_imax         );
                QB_acc_slew_rate_max->setValue(pkt.acc_slew_rate_max);

                QB_shaping_jerk     ->setChanged(false);
                QB_pos_p            ->setChanged(false);
                QB_vel_p            ->setChanged(false);
                QB_vel_i            ->setChanged(false);
                QB_vel_d            ->setChanged(false);
                QB_vel_ff           ->setChanged(false);
                QB_vel_imax         ->setChanged(false);
                QB_acc_p            ->setChanged(false);
                QB_acc_i            ->setChanged(false);
                QB_acc_d            ->setChanged(false);
                QB_acc_ff           ->setChanged(false);
                QB_acc_imax         ->setChanged(false);
                QB_acc_slew_rate_max->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamPosZControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_posz_control_t pkt{};
        pkt.is_set = 1;
        pkt.shaping_jerk      = QB_shaping_jerk              ->value();
        pkt.pos_p             = QB_pos_p                     ->value();
        pkt.vel_p             = QB_vel_p                     ->value();
        pkt.vel_i             = QB_vel_i                     ->value();
        pkt.vel_d             = QB_vel_d                     ->value();
        pkt.vel_ff            = QB_vel_ff                    ->value();
        pkt.vel_imax          = QB_vel_imax                  ->value();
        pkt.acc_p             = QB_acc_p                     ->value();
        pkt.acc_i             = QB_acc_i                     ->value();
        pkt.acc_d             = QB_acc_d                     ->value();
        pkt.acc_ff            = QB_acc_ff                    ->value();
        pkt.acc_imax          = QB_acc_imax                  ->value();
        pkt.acc_slew_rate_max = QB_acc_slew_rate_max         ->value();

        link->do_setParamPosZCtrl(pkt);
    }
}

CFG_ParamPosXYControl::CFG_ParamPosXYControl(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("CFGMainGroup");
}



void CFG_ParamPosXYControl::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamPosXYControl::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamPosXYCtrl();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamPosXYControl::upload_param);
}

void CFG_ParamPosXYControl::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("水平位置参数"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    // 标签
    if( LB_shaping_jerk == nullptr){
        LB_shaping_jerk = new QLabel(QStringLiteral("目标加速度变化率:"));
        LB_shaping_jerk->setToolTip(QStringLiteral("目标加速度变化率(m/sss)"));
        LB_shaping_jerk->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_shaping_jerk->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_pos_p == nullptr){
        LB_pos_p = new QLabel(QStringLiteral("P:"));
        LB_pos_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_pos_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_p == nullptr){
        LB_vel_p = new QLabel(QStringLiteral("P:"));
        LB_vel_p->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_i == nullptr){
        LB_vel_i = new QLabel(QStringLiteral("I:"));
        LB_vel_i->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_i->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_d == nullptr){
        LB_vel_d = new QLabel(QStringLiteral("D:"));
        LB_vel_d->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_d->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_ff == nullptr){
        LB_vel_ff = new QLabel(QStringLiteral("FF:"));
        LB_vel_ff->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_ff->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
    if( LB_vel_imax == nullptr){
        LB_vel_imax = new QLabel(QStringLiteral("Imax:"));
        LB_vel_imax->setObjectName(QString::fromUtf8("widgetSubNameLabel"));
        LB_vel_imax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }


    if( QB_shaping_jerk == nullptr){
        QB_shaping_jerk = new UDoubleSpinBox();
        QB_shaping_jerk->setRange(1,20);
        QB_shaping_jerk->setSingleStep(1);
        QB_shaping_jerk->setValue(0);
        QB_shaping_jerk->setAlignment(Qt::AlignCenter);
        QB_shaping_jerk->setDecimals(0);
        QB_shaping_jerk->setToolTip(QStringLiteral("水平方向目标加速度变化率限制"));
        QB_shaping_jerk->setChanged(false);
    }
    if( QB_pos_p == nullptr){
        QB_pos_p = new UDoubleSpinBox();
        QB_pos_p->setRange(0.5,2.0);
        QB_pos_p->setSingleStep(0.05);
        QB_pos_p->setValue(0);
        QB_pos_p->setAlignment(Qt::AlignCenter);
        QB_pos_p->setDecimals(3);
        QB_pos_p->setToolTip(QStringLiteral("水平位置P项"));
        QB_pos_p->setChanged(false);
    }
    if( QB_vel_p == nullptr){
        QB_vel_p = new UDoubleSpinBox();
        QB_vel_p->setRange(0.1,6);
        QB_vel_p->setSingleStep(0.05);
        QB_vel_p->setValue(0);
        QB_vel_p->setAlignment(Qt::AlignCenter);
        QB_vel_p->setDecimals(3);
        QB_vel_p->setToolTip(QStringLiteral("水平速度P项"));
        QB_vel_p->setChanged(false);
    }
    if( QB_vel_i == nullptr){
        QB_vel_i = new UDoubleSpinBox();
        QB_vel_i->setRange(0.02,1);
        QB_vel_i->setSingleStep(0.01);
        QB_vel_i->setValue(0);
        QB_vel_i->setAlignment(Qt::AlignCenter);
        QB_vel_i->setDecimals(3);
        QB_vel_i->setToolTip(QStringLiteral("水平速度I项"));
        QB_vel_i->setChanged(false);
    }
    if( QB_vel_d == nullptr){
        QB_vel_d = new UDoubleSpinBox();
        QB_vel_d->setRange(0,1);
        QB_vel_d->setSingleStep(0.001);
        QB_vel_d->setValue(0);
        QB_vel_d->setAlignment(Qt::AlignCenter);
        QB_vel_d->setDecimals(3);
        QB_vel_d->setToolTip(QStringLiteral("水平速度D项"));
        QB_vel_d->setChanged(false);
    }
    if( QB_vel_ff == nullptr){
        QB_vel_ff = new UDoubleSpinBox();
        QB_vel_ff->setRange(0,6);
        QB_vel_ff->setSingleStep(0.01);
        QB_vel_ff->setValue(0);
        QB_vel_ff->setAlignment(Qt::AlignCenter);
        QB_vel_ff->setDecimals(3);
        QB_vel_ff->setToolTip(QStringLiteral("水平速度FF项"));
        QB_vel_ff->setChanged(false);
    }
    if( QB_vel_imax == nullptr){
        QB_vel_imax = new UDoubleSpinBox();
        QB_vel_imax->setRange(0,4500);
        QB_vel_imax->setSingleStep(10);
        QB_vel_imax->setValue(0);
        QB_vel_imax->setAlignment(Qt::AlignCenter);
        QB_vel_imax->setDecimals(0);
        QB_vel_imax->setToolTip(QStringLiteral("水平速度积分限幅"));
        QB_vel_imax->setChanged(false);
    }

    if( LB_Limit == nullptr){
        LB_Limit = new QLabel(QStringLiteral("限定参数"));
        LB_Limit->setObjectName("widgetNameLabel");
    }
    if( LB_Pos == nullptr){
        LB_Pos = new QLabel(QStringLiteral("位置控制"));
        LB_Pos->setObjectName("widgetNameLabel");
    }
    if( LB_Vel == nullptr){
        LB_Vel = new QLabel(QStringLiteral("速度控制"));
        LB_Vel->setObjectName("widgetNameLabel");
    }



//    if( LY_Limit == nullptr){
//        LY_Limit = new QGridLayout(GR_Limit);
//        LY_Limit->setObjectName(QString::fromUtf8("widgetLayout"));
//    }
//    if( LY_Pos == nullptr){
//        LY_Pos = new QGridLayout(GR_Pos);
//        LY_Pos->setObjectName(QString::fromUtf8("widgetLayout"));
//    }
//    if( LY_Vel == nullptr){
//        LY_Vel = new QGridLayout(GR_Vel);
//        LY_Vel->setObjectName(QString::fromUtf8("widgetLayout"));
//    }



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



    QLabel *LB_space_1 = new QLabel();
    QLabel *LB_space_2 = new QLabel();

    LB_space_1->setObjectName("widgetSpaceLabel");
    LB_space_2->setObjectName("widgetSpaceLabel");

    this->widgetLayout->addWidget(this->titleLabel,0,0,1,7);

    this->widgetLayout->addWidget(this->LB_Limit,1,1,1,1);
    this->widgetLayout->addWidget(this->LB_shaping_jerk,1,2,1,2);
    this->widgetLayout->addWidget(this->QB_shaping_jerk,1,4,1,2);

    this->widgetLayout->addWidget(LB_space_1,2,1,1,5);

    this->widgetLayout->addWidget(this->LB_Pos,3,1,1,1);
    this->widgetLayout->addWidget(this->LB_pos_p,3,2,1,2);
    this->widgetLayout->addWidget(this->QB_pos_p,3,4,1,2);

    this->widgetLayout->addWidget(LB_space_2,4,1,1,5);

    this->widgetLayout->addWidget(LB_Vel,5,1,3,1);
    this->widgetLayout->addWidget(LB_vel_p   ,            5, 2, 1, 1);
    this->widgetLayout->addWidget(LB_vel_i   ,            6, 2, 1, 1);
    this->widgetLayout->addWidget(LB_vel_d   ,            7, 2, 1, 1);
    this->widgetLayout->addWidget(LB_vel_ff  ,            5, 4, 1, 1);
    this->widgetLayout->addWidget(LB_vel_imax,            6, 4, 1, 1);
    this->widgetLayout->addWidget(QB_vel_p   ,            5, 3, 1, 1);
    this->widgetLayout->addWidget(QB_vel_i   ,            6, 3, 1, 1);
    this->widgetLayout->addWidget(QB_vel_d   ,            7, 3, 1, 1);
    this->widgetLayout->addWidget(QB_vel_ff  ,            5, 5, 1, 1);
    this->widgetLayout->addWidget(QB_vel_imax,            6, 5, 1, 1);


    widgetLayout->addLayout(widgetLayout_pb         ,8, 1, 1, 5);


    this->widgetLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,0,11,1);
    this->widgetLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,6,11,1);
    this->widgetLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),9,3,1,1);


    this->widgetLayout->setColumnStretch(0,1);
    this->widgetLayout->setColumnStretch(6,1);


    widgetLayout->addLayout(widgetLayout_pb         ,4, 0, 1, 1);


}

void CFG_ParamPosXYControl::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamPosXYCtrl:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_posxy_control_t pkt = link->getTVehicleParam().PosXYCtrl;
                QB_shaping_jerk     ->setValue(pkt.shaping_jerk     );
                QB_pos_p            ->setValue(pkt.pos_p            );
                QB_vel_p            ->setValue(pkt.vel_p            );
                QB_vel_i            ->setValue(pkt.vel_i            );
                QB_vel_d            ->setValue(pkt.vel_d            );
                QB_vel_ff           ->setValue(pkt.vel_ff           );
                QB_vel_imax         ->setValue(pkt.vel_imax         );

                QB_shaping_jerk     ->setChanged(false);
                QB_pos_p            ->setChanged(false);
                QB_vel_p            ->setChanged(false);
                QB_vel_i            ->setChanged(false);
                QB_vel_d            ->setChanged(false);
                QB_vel_ff           ->setChanged(false);
                QB_vel_imax         ->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamPosXYControl::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_posxy_control_t pkt{};
        pkt.is_set = 1;
        pkt.shaping_jerk      = QB_shaping_jerk              ->value();
        pkt.pos_p             = QB_pos_p                     ->value();
        pkt.vel_p             = QB_vel_p                     ->value();
        pkt.vel_i             = QB_vel_i                     ->value();
        pkt.vel_d             = QB_vel_d                     ->value();
        pkt.vel_ff            = QB_vel_ff                    ->value();
        pkt.vel_imax          = QB_vel_imax                  ->value();

        link->do_setParamPosXYCtrl(pkt);
    }
}
