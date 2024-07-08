/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_param_initcfg.h"
#include "DMMM.h"
#include <qmath.h>

CFG_InitCfg::CFG_InitCfg(QWidget *parent):
    QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();

    this->setObjectName(QString::fromUtf8("stackedSubWidget"));
}

QGridLayout *CFG_InitCfg::getWidgetLayout() const
{
    return widgetLayout;
}

void CFG_InitCfg::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_InitCfg::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamInitCtrlCfg();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_InitCfg::upload_param);
    connect(PB_Calculate   , &QPushButton::released,this,&CFG_InitCfg::calc_values);

    connect(this->DS_atc_rat_pit_fltd,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_pit_fltd,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_pit_flte,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_pit_fltt,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_rll_fltd,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_rll_flte,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_rll_fltt,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_yaw_fltd,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_yaw_flte,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_atc_rat_yaw_fltt,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_ins_accel_filter,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});
    connect(this->DS_ins_gyro_filter ,QOverload<double>::of(&UDoubleSpinBox::valueChanged),[=](double value){this->SD_atc_rat_pit_fltd->setValue(static_cast<int>(value * 10));});

    connect(this->SD_atc_rat_pit_fltd,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_pit_fltd,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_pit_flte,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_pit_fltt,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_rll_fltd,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_rll_flte,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_rll_fltt,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_yaw_fltd,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_yaw_flte,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_atc_rat_yaw_fltt,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_ins_accel_filter,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
    connect(this->SD_ins_gyro_filter ,QOverload<int>::of(&QSlider::valueChanged),          [=](int value){this->DS_atc_rat_pit_fltd->setValue(static_cast<double>(static_cast<double>(value) / 10.0f));});
}

void CFG_InitCfg::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
    }

    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("初始参数配置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral(""));
        LB_Info->setObjectName(QString::fromUtf8("CFGLabelWarning"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    if(LB_prop_size == nullptr){
        LB_prop_size = new QLabel(QStringLiteral("螺旋桨尺寸(英寸):"));
        LB_prop_size->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_prop_size->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_prop_size->setToolTip(QStringLiteral(""));
    }

    if( LB_acro_yaw_p == nullptr){
        LB_acro_yaw_p = new QLabel(QStringLiteral("航向控制因子(手动模式):"));
        LB_acro_yaw_p->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_acro_yaw_p->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_acro_yaw_p->setToolTip(QStringLiteral("此参数用于将航向摇杆输入转换为目标角速度，值越大意味着旋转越快。"));
    }

    if( LB_atc_accel_p_max == nullptr){
        LB_atc_accel_p_max = new QLabel(QStringLiteral("Pitch轴最大加速度:"));
        LB_atc_accel_p_max->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_accel_p_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_accel_p_max->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_accel_r_max == nullptr){
        LB_atc_accel_r_max = new QLabel(QStringLiteral("Roll轴最大加速度:"));
        LB_atc_accel_r_max->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_accel_r_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_accel_r_max->setToolTip(QStringLiteral(""));
    }

    if( LB_atc_accel_y_max == nullptr){
        LB_atc_accel_y_max = new QLabel(QStringLiteral("Yaw轴最大加速度:"));
        LB_atc_accel_y_max->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_accel_y_max->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_accel_y_max->setToolTip(QStringLiteral(""));
    }

    if( LB_atc_rat_pit_fltd == nullptr){
        LB_atc_rat_pit_fltd = new QLabel(QStringLiteral("Pitch速率控制D项:"));
        LB_atc_rat_pit_fltd->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_pit_fltd->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_pit_fltd->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_rat_pit_flte == nullptr){
        LB_atc_rat_pit_flte = new QLabel(QStringLiteral("Pitch速率控制E差:"));
        LB_atc_rat_pit_flte->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_pit_flte->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_pit_flte->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_rat_pit_fltt == nullptr){
        LB_atc_rat_pit_fltt = new QLabel(QStringLiteral("Pitch速率控制目标:"));
        LB_atc_rat_pit_fltt->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_pit_fltt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_pit_fltt->setToolTip(QStringLiteral(""));
    }

    if( LB_atc_rat_rll_fltd == nullptr){
        LB_atc_rat_rll_fltd = new QLabel(QStringLiteral("Roll速率控制D项:"));
        LB_atc_rat_rll_fltd->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_rll_fltd->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_rll_fltd->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_rat_rll_flte == nullptr){
        LB_atc_rat_rll_flte = new QLabel(QStringLiteral("Roll速率控制E差:"));
        LB_atc_rat_rll_flte->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_rll_flte->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_rll_flte->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_rat_rll_fltt == nullptr){
        LB_atc_rat_rll_fltt = new QLabel(QStringLiteral("Roll速率控制目标:"));
        LB_atc_rat_rll_fltt->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_rll_fltt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_rll_fltt->setToolTip(QStringLiteral(""));
    }

    if( LB_atc_rat_yaw_fltd == nullptr){
        LB_atc_rat_yaw_fltd = new QLabel(QStringLiteral("Yaw速率控制D项:"));
        LB_atc_rat_yaw_fltd->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_yaw_fltd->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_yaw_fltd->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_rat_yaw_flte == nullptr){
        LB_atc_rat_yaw_flte = new QLabel(QStringLiteral("Yaw速率控制E差:"));
        LB_atc_rat_yaw_flte->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_yaw_flte->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_yaw_flte->setToolTip(QStringLiteral(""));
    }
    if( LB_atc_rat_yaw_fltt == nullptr){
        LB_atc_rat_yaw_fltt = new QLabel(QStringLiteral("Yaw速率控制目标:"));
        LB_atc_rat_yaw_fltt->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_rat_yaw_fltt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_rat_yaw_fltt->setToolTip(QStringLiteral(""));
    }

    if( LB_atc_thr_mix_man == nullptr){
        LB_atc_thr_mix_man = new QLabel(QStringLiteral("辅助模式油门优先级:"));
        LB_atc_thr_mix_man->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_atc_thr_mix_man->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_atc_thr_mix_man->setToolTip(QStringLiteral(""));
    }
    if( LB_ins_accel_filter == nullptr){
        LB_ins_accel_filter = new QLabel(QStringLiteral("加速度计:"));
        LB_ins_accel_filter->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_ins_accel_filter->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_ins_accel_filter->setToolTip(QStringLiteral(""));
    }

    if( LB_ins_gyro_filter == nullptr){
        LB_ins_gyro_filter = new QLabel(QStringLiteral("陀螺仪:"));
        LB_ins_gyro_filter->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_ins_gyro_filter->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_ins_gyro_filter->setToolTip(QStringLiteral(""));
    }

    if( LB_mot_thst_expo == nullptr){
        LB_mot_thst_expo = new QLabel(QStringLiteral("电机推力曲线指数:"));
        LB_mot_thst_expo->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_mot_thst_expo->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_mot_thst_expo->setToolTip(QStringLiteral(""));
    }

    if( DS_acro_yaw_p == nullptr){
        DS_acro_yaw_p = new UDoubleSpinBox();
        DS_acro_yaw_p->setRange(1,10);
        DS_acro_yaw_p->setValue(4.5);
        DS_acro_yaw_p->setAlignment(Qt::AlignCenter);
//        DS_acro_yaw_p->setSuffix(QStringLiteral(""));
        DS_acro_yaw_p->setToolTip(QStringLiteral("此参数用于将航向摇杆输入转换为目标角速度，值越大意味着旋转越快。1代表45°/s"));
        DS_acro_yaw_p->setDecimals(2);
        DS_acro_yaw_p->setChanged(false);
    }

    if( DS_atc_accel_p_max == nullptr){
        DS_atc_accel_p_max = new UDoubleSpinBox();
        DS_atc_accel_p_max->setRange(0,1800);
        DS_atc_accel_p_max->setValue(1100);
        DS_atc_accel_p_max->setAlignment(Qt::AlignCenter);
        DS_atc_accel_p_max->setSuffix(QStringLiteral(" °/ss"));
        DS_atc_accel_p_max->setToolTip(QStringLiteral("Pitch轴最大加速度,值为0则代表不做限制。"));
        DS_atc_accel_p_max->setDecimals(1);
        DS_atc_accel_p_max->setChanged(false);
    }
    if( DS_atc_accel_r_max == nullptr){
        DS_atc_accel_r_max = new UDoubleSpinBox();
        DS_atc_accel_r_max->setRange(0,1800);
        DS_atc_accel_r_max->setValue(1100);
        DS_atc_accel_r_max->setAlignment(Qt::AlignCenter);
        DS_atc_accel_r_max->setSuffix(QStringLiteral(" °/ss"));
        DS_atc_accel_r_max->setToolTip(QStringLiteral("Roll轴最大加速度,值为0则代表不做限制。"));
        DS_atc_accel_r_max->setDecimals(1);
        DS_atc_accel_r_max->setChanged(false);
    }
    if( DS_atc_accel_y_max == nullptr){
        DS_atc_accel_y_max = new UDoubleSpinBox();
        DS_atc_accel_y_max->setRange(0,1800);
        DS_atc_accel_y_max->setValue(1100);
        DS_atc_accel_y_max->setAlignment(Qt::AlignCenter);
        DS_atc_accel_y_max->setSuffix(QStringLiteral(" °/ss"));
        DS_atc_accel_y_max->setToolTip(QStringLiteral("Yaw轴最大加速度,值为0则代表不做限制。"));
        DS_atc_accel_y_max->setDecimals(1);
        DS_atc_accel_y_max->setChanged(false);
    }
    if( DS_atc_rat_pit_fltd == nullptr){
        DS_atc_rat_pit_fltd = new UDoubleSpinBox();
        DS_atc_rat_pit_fltd->setRange(0,1000);
        DS_atc_rat_pit_fltd->setValue(0);
        DS_atc_rat_pit_fltd->setAlignment(Qt::AlignCenter);
        DS_atc_rat_pit_fltd->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_pit_fltd->setToolTip(QStringLiteral("Pitch速率控制D项滤波器截止频率。"));
        DS_atc_rat_pit_fltd->setDecimals(1);
        DS_atc_rat_pit_fltd->setChanged(false);
    }
    if( DS_atc_rat_pit_flte == nullptr){
        DS_atc_rat_pit_flte = new UDoubleSpinBox();
        DS_atc_rat_pit_flte->setRange(0,1000);
        DS_atc_rat_pit_flte->setValue(0);
        DS_atc_rat_pit_flte->setAlignment(Qt::AlignCenter);
        DS_atc_rat_pit_flte->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_pit_flte->setToolTip(QStringLiteral("Pitch速率控制E差值滤波器截止频率。"));
        DS_atc_rat_pit_flte->setDecimals(1);
        DS_atc_rat_pit_flte->setChanged(false);
    }
    if( DS_atc_rat_pit_fltt == nullptr){
        DS_atc_rat_pit_fltt = new UDoubleSpinBox();
        DS_atc_rat_pit_fltt->setRange(0,1000);
        DS_atc_rat_pit_fltt->setValue(0);
        DS_atc_rat_pit_fltt->setAlignment(Qt::AlignCenter);
        DS_atc_rat_pit_fltt->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_pit_fltt->setToolTip(QStringLiteral("Pitch速率控制目标项滤波器截止频率。"));
        DS_atc_rat_pit_fltt->setDecimals(1);
        DS_atc_rat_pit_fltt->setChanged(false);
    }

    if( DS_atc_rat_rll_fltd == nullptr){
        DS_atc_rat_rll_fltd = new UDoubleSpinBox();
        DS_atc_rat_rll_fltd->setRange(0,1000);
        DS_atc_rat_rll_fltd->setValue(0);
        DS_atc_rat_rll_fltd->setAlignment(Qt::AlignCenter);
        DS_atc_rat_rll_fltd->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_rll_fltd->setToolTip(QStringLiteral("Roll速率控制D项滤波器截止频率。"));
        DS_atc_rat_rll_fltd->setDecimals(1);
        DS_atc_rat_rll_fltd->setChanged(false);
    }
    if( DS_atc_rat_rll_flte == nullptr){
        DS_atc_rat_rll_flte = new UDoubleSpinBox();
        DS_atc_rat_rll_flte->setRange(0,1000);
        DS_atc_rat_rll_flte->setValue(0);
        DS_atc_rat_rll_flte->setAlignment(Qt::AlignCenter);
        DS_atc_rat_rll_flte->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_rll_flte->setToolTip(QStringLiteral("Roll速率控制E差值滤波器截止频率。"));
        DS_atc_rat_rll_flte->setDecimals(1);
        DS_atc_rat_rll_flte->setChanged(false);
    }
    if( DS_atc_rat_rll_fltt == nullptr){
        DS_atc_rat_rll_fltt = new UDoubleSpinBox();
        DS_atc_rat_rll_fltt->setRange(0,1000);
        DS_atc_rat_rll_fltt->setValue(0);
        DS_atc_rat_rll_fltt->setAlignment(Qt::AlignCenter);
        DS_atc_rat_rll_fltt->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_rll_fltt->setToolTip(QStringLiteral("Roll速率控制目标项滤波器截止频率。"));
        DS_atc_rat_rll_fltt->setDecimals(1);
        DS_atc_rat_rll_fltt->setChanged(false);
    }

    if( DS_atc_rat_yaw_fltd == nullptr){
        DS_atc_rat_yaw_fltd = new UDoubleSpinBox();
        DS_atc_rat_yaw_fltd->setRange(0,1000);
        DS_atc_rat_yaw_fltd->setValue(0);
        DS_atc_rat_yaw_fltd->setAlignment(Qt::AlignCenter);
        DS_atc_rat_yaw_fltd->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_yaw_fltd->setToolTip(QStringLiteral("Yaw速率控制D项滤波器截止频率。"));
        DS_atc_rat_yaw_fltd->setDecimals(1);
        DS_atc_rat_yaw_fltd->setChanged(false);
    }
    if( DS_atc_rat_yaw_flte == nullptr){
        DS_atc_rat_yaw_flte = new UDoubleSpinBox();
        DS_atc_rat_yaw_flte->setRange(0,1000);
        DS_atc_rat_yaw_flte->setValue(0);
        DS_atc_rat_yaw_flte->setAlignment(Qt::AlignCenter);
        DS_atc_rat_yaw_flte->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_yaw_flte->setToolTip(QStringLiteral("Yaw速率控制E差值滤波器截止频率。"));
        DS_atc_rat_yaw_flte->setDecimals(1);
        DS_atc_rat_yaw_flte->setChanged(false);
    }
    if( DS_atc_rat_yaw_fltt == nullptr){
        DS_atc_rat_yaw_fltt = new UDoubleSpinBox();
        DS_atc_rat_yaw_fltt->setRange(0,1000);
        DS_atc_rat_yaw_fltt->setValue(0);
        DS_atc_rat_yaw_fltt->setAlignment(Qt::AlignCenter);
        DS_atc_rat_yaw_fltt->setSuffix(QStringLiteral(" Hz"));
        DS_atc_rat_yaw_fltt->setToolTip(QStringLiteral("Yaw速率控制目标项滤波器截止频率。"));
        DS_atc_rat_yaw_fltt->setDecimals(1);
        DS_atc_rat_yaw_fltt->setChanged(false);
    }
    if( DS_atc_thr_mix_man == nullptr){
        DS_atc_thr_mix_man = new UDoubleSpinBox();
        DS_atc_thr_mix_man->setRange(0.1,0.9);
        DS_atc_thr_mix_man->setValue(0.1);
        DS_atc_thr_mix_man->setAlignment(Qt::AlignCenter);
//        DS_atc_thr_mix_man->setSuffix(QStringLiteral(" "));
        DS_atc_thr_mix_man->setToolTip(QStringLiteral("手动飞行期间使用的油门与姿态控制优先级,更高的值意味着\r\n"
                                                      "我们优先考虑姿态控制（而不是油门）"));
        DS_atc_thr_mix_man->setDecimals(2);
        DS_atc_thr_mix_man->setChanged(false);
    }

    if( DS_ins_accel_filter == nullptr){
        DS_ins_accel_filter = new UDoubleSpinBox();
        DS_ins_accel_filter->setRange(0,256);
        DS_ins_accel_filter->setValue(20);
        DS_ins_accel_filter->setAlignment(Qt::AlignCenter);
        DS_ins_accel_filter->setSuffix(QStringLiteral(" Hz"));
        DS_ins_accel_filter->setToolTip(QStringLiteral("加速度计的滤波器截止频率。这可以设置为一个较低的值，\r\n"
                                                       "以尝试应对飞机中非常高的振动水平。值为零表示没有过滤（不推荐！）"));
        DS_ins_accel_filter->setDecimals(1);
        DS_ins_accel_filter->setChanged(false);
    }
    if( DS_ins_gyro_filter == nullptr){
        DS_ins_gyro_filter = new UDoubleSpinBox();
        DS_ins_gyro_filter->setRange(0,256);
        DS_ins_gyro_filter->setValue(20);
        DS_ins_gyro_filter->setAlignment(Qt::AlignCenter);
        DS_ins_gyro_filter->setSuffix(QStringLiteral(" Hz"));
        DS_ins_gyro_filter->setToolTip(QStringLiteral("陀螺仪的滤波器截止频率。这可以设置为一个较低的值，\r\n"
                                                      "以尝试应对飞机中非常高的振动水平。值为零表示没有过滤（不推荐！）"));
        DS_ins_gyro_filter->setDecimals(1);
        DS_ins_gyro_filter->setChanged(false);
    }

    if( DS_mot_thst_expo == nullptr){
        DS_mot_thst_expo = new UDoubleSpinBox();
        DS_mot_thst_expo->setRange(0,1);
        DS_mot_thst_expo->setValue(0);
        DS_mot_thst_expo->setAlignment(Qt::AlignCenter);
//        DS_mot_thst_expo->setSuffix(QStringLiteral(" Hz"));
        DS_mot_thst_expo->setToolTip(QStringLiteral("电机推力曲线指数（线性曲线为0.0，二阶曲线为1.0）"));
        DS_mot_thst_expo->setDecimals(2);
        DS_mot_thst_expo->setChanged(false);
    }


    if( DS_prop_size == nullptr){
        DS_prop_size = new QDoubleSpinBox();
        DS_prop_size->setRange(0.1,500);
        DS_prop_size->setValue(prop_size);
        DS_prop_size->setSingleStep(1);
        DS_prop_size->setDecimals(2);
        DS_prop_size->setAlignment(Qt::AlignCenter);
        DS_prop_size->setSuffix(QStringLiteral(""));
        DS_prop_size->setToolTip(QStringLiteral(""));
    }

    if( PB_Calculate == nullptr){
        PB_Calculate = new QPushButton(QStringLiteral("计算"));
        PB_Calculate->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_Calculate->setToolTip(QStringLiteral("WidgetCMD_Action"));
    }
    if(Group_Calcu == nullptr){
        Group_Calcu = new QGroupBox(QStringLiteral("计算参数"));
        Group_Calcu->setObjectName("widgetGroupBox");
        Group_Calcu->setAlignment(Qt::AlignCenter);
    }
    if(widgetLayout_calcu == nullptr){
        widgetLayout_calcu = new QVBoxLayout(Group_Calcu);
        widgetLayout_calcu->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    widgetLayout_calcu->addStretch(5);
    widgetLayout_calcu->addWidget(LB_prop_size,1);
    widgetLayout_calcu->addWidget(DS_prop_size,1);
    widgetLayout_calcu->addWidget(PB_Calculate,1);
    widgetLayout_calcu->addStretch(5);
    widgetLayout_calcu->setAlignment(Qt::AlignCenter);



    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_download->setToolTip(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_upload->setToolTip(QStringLiteral(""));
    }
    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
    }


    if( SD_atc_rat_pit_fltd == nullptr){
        SD_atc_rat_pit_fltd = new QSlider();
        SD_atc_rat_pit_fltd->setRange(0,1000);
        SD_atc_rat_pit_fltd->setValue(0);
        SD_atc_rat_pit_fltd->setOrientation(Qt::Horizontal);
        SD_atc_rat_pit_fltd->setObjectName("widgetSlider");
        SD_atc_rat_pit_fltd->setToolTip(QStringLiteral("Pitch速率控制D项滤波器截止频率。"));
    }


    if( SD_atc_rat_pit_flte == nullptr){
        SD_atc_rat_pit_flte = new QSlider();
        SD_atc_rat_pit_flte->setRange(0,1000);
        SD_atc_rat_pit_flte->setValue(0);
        SD_atc_rat_pit_flte->setOrientation(Qt::Horizontal);
        SD_atc_rat_pit_flte->setObjectName("widgetSlider");
        SD_atc_rat_pit_flte->setToolTip(QStringLiteral("Pitch速率控制E差值滤波器截止频率。"));
    }

    if( SD_atc_rat_pit_fltt == nullptr){
        SD_atc_rat_pit_fltt = new QSlider();
        SD_atc_rat_pit_fltt->setRange(0,1000);
        SD_atc_rat_pit_fltt->setValue(0);
        SD_atc_rat_pit_fltt->setOrientation(Qt::Horizontal);
        SD_atc_rat_pit_fltt->setObjectName("widgetSlider");
        SD_atc_rat_pit_fltt->setToolTip(QStringLiteral("Pitch速率控制目标项滤波器截止频率。"));
    }

    if( SD_atc_rat_rll_fltd == nullptr){
        SD_atc_rat_rll_fltd = new QSlider();
        SD_atc_rat_rll_fltd->setRange(0,1000);
        SD_atc_rat_rll_fltd->setValue(0);
        SD_atc_rat_rll_fltd->setOrientation(Qt::Horizontal);
        SD_atc_rat_rll_fltd->setObjectName("widgetSlider");
        SD_atc_rat_rll_fltd->setToolTip(QStringLiteral("Roll速率控制D项滤波器截止频率。"));
    }

    if( SD_atc_rat_rll_flte == nullptr){
        SD_atc_rat_rll_flte = new QSlider();
        SD_atc_rat_rll_flte->setRange(0,1000);
        SD_atc_rat_rll_flte->setValue(0);
        SD_atc_rat_rll_flte->setOrientation(Qt::Horizontal);
        SD_atc_rat_rll_flte->setObjectName("widgetSlider");
        SD_atc_rat_rll_flte->setToolTip(QStringLiteral("Roll速率控制E差值滤波器截止频率。"));

    }

    if( SD_atc_rat_rll_fltt == nullptr){
        SD_atc_rat_rll_fltt = new QSlider();
        SD_atc_rat_rll_fltt->setRange(0,1000);
        SD_atc_rat_rll_fltt->setValue(0);
        SD_atc_rat_rll_fltt->setOrientation(Qt::Horizontal);
        SD_atc_rat_rll_fltt->setObjectName("widgetSlider");
        SD_atc_rat_rll_fltt->setToolTip(QStringLiteral("Roll速率控制目标项滤波器截止频率。"));
    }

    if( SD_atc_rat_yaw_fltd == nullptr){
        SD_atc_rat_yaw_fltd = new QSlider();
        SD_atc_rat_yaw_fltd->setRange(0,1000);
        SD_atc_rat_yaw_fltd->setValue(0);
        SD_atc_rat_yaw_fltd->setOrientation(Qt::Horizontal);
        SD_atc_rat_yaw_fltd->setObjectName("widgetSlider");
        SD_atc_rat_yaw_fltd->setToolTip(QStringLiteral("Yaw速率控制D项滤波器截止频率。"));
    }

    if( SD_atc_rat_yaw_flte == nullptr){
        SD_atc_rat_yaw_flte = new QSlider();
        SD_atc_rat_yaw_flte->setRange(0,1000);
        SD_atc_rat_yaw_flte->setValue(0);
        SD_atc_rat_yaw_flte->setOrientation(Qt::Horizontal);
        SD_atc_rat_yaw_flte->setObjectName("widgetSlider");

        SD_atc_rat_yaw_flte->setToolTip(QStringLiteral("Yaw速率控制E差值滤波器截止频率。"));

    }

    if( SD_atc_rat_yaw_fltt == nullptr){
        SD_atc_rat_yaw_fltt = new QSlider();
        SD_atc_rat_yaw_fltt->setRange(0,1000);
        SD_atc_rat_yaw_fltt->setValue(0);
        SD_atc_rat_yaw_fltt->setOrientation(Qt::Horizontal);
        SD_atc_rat_yaw_fltt->setObjectName("widgetSlider");
        SD_atc_rat_yaw_fltt->setToolTip(QStringLiteral("Yaw速率控制目标项滤波器截止频率。"));
    }
    if( SD_ins_accel_filter == nullptr){
        SD_ins_accel_filter = new QSlider();
        SD_ins_accel_filter->setRange(0,256);
        SD_ins_accel_filter->setValue(20);
        SD_ins_accel_filter->setOrientation(Qt::Horizontal);
        SD_ins_accel_filter->setObjectName("widgetSlider");

        SD_ins_accel_filter->setToolTip(QStringLiteral("加速度计的滤波器截止频率。这可以设置为一个较低的值，\r\n"
                                                     "以尝试应对飞机中非常高的振动水平。值为零表示没有过滤（不推荐！）"));

    }

    if( SD_ins_gyro_filter == nullptr){
        SD_ins_gyro_filter = new QSlider();
        SD_ins_gyro_filter->setRange(0,256);
        SD_ins_gyro_filter->setValue(20);
        SD_ins_gyro_filter->setOrientation(Qt::Horizontal);
        SD_ins_gyro_filter->setObjectName("widgetSlider");
        SD_ins_gyro_filter->setToolTip(QStringLiteral("陀螺仪的滤波器截止频率。这可以设置为一个较低的值，\r\n"
                                                    "以尝试应对飞机中非常高的振动水平。值为零表示没有过滤（不推荐！）"));
    }


    widgetLayout_pb->addStretch(5);
    widgetLayout_pb->addWidget(PB_download,1);
    widgetLayout_pb->addWidget(PB_upload,1);
    widgetLayout_pb->addStretch(5);


    QGridLayout *subWidgetLayout_calcu = new QGridLayout();
    subWidgetLayout_calcu->addWidget(this->Group_Calcu,0,0,1,1);
    subWidgetLayout_calcu->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),0,1,1,1);
    subWidgetLayout_calcu->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,0,1,1);


    QLabel *groupLabel_1 = new QLabel(QStringLiteral("滤波器截止频率"));
    groupLabel_1->setObjectName("widgetSpaceLabel_Bottom_Text");
    groupLabel_1->setAlignment(Qt::AlignHCenter);




    this->widgetLayout->addWidget(this->titleLabel,0,0,2,5);
    this->widgetLayout->addWidget(groupLabel_1,2,1,1,3);

    this->widgetLayout->addWidget(LB_atc_rat_pit_fltd,3,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_pit_flte,4,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_pit_fltt,5,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_rll_fltd,6,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_rll_flte,7,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_rll_fltt,8,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_yaw_fltd,9,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_yaw_flte,10,1,1,1);
    this->widgetLayout->addWidget(LB_atc_rat_yaw_fltt,11,1,1,1);
    this->widgetLayout->addWidget(LB_ins_accel_filter,12,1,1,1);
    this->widgetLayout->addWidget(LB_ins_gyro_filter,13,1,1,1);

   this->widgetLayout->addWidget(DS_atc_rat_pit_fltd,3,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_pit_flte,4,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_pit_fltt,5,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_rll_fltd,6,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_rll_flte,7,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_rll_fltt,8,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_yaw_fltd,9,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_yaw_flte,10,2,1,1);
   this->widgetLayout->addWidget(DS_atc_rat_yaw_fltt,11,2,1,1);
   this->widgetLayout->addWidget(DS_ins_accel_filter,12,2,1,1);
   this->widgetLayout->addWidget(DS_ins_gyro_filter,13,2,1,1);

   this->widgetLayout->addWidget(SD_atc_rat_pit_fltd,3,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_pit_flte,4,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_pit_fltt,5,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_rll_fltd,6,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_rll_flte,7,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_rll_fltt,8,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_yaw_fltd,9,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_yaw_flte,10,3,1,1);
   this->widgetLayout->addWidget(SD_atc_rat_yaw_fltt,11,3,1,1);
   this->widgetLayout->addWidget(SD_ins_accel_filter,12,3,1,1);
   this->widgetLayout->addWidget(SD_ins_gyro_filter,13,3,1,1);


    QLabel *groupLabel_2 = new QLabel(QStringLiteral("其他"));
    groupLabel_2->setObjectName("widgetSpaceLabel_Bottom_Text");
    groupLabel_2->setAlignment(Qt::AlignHCenter);


    this->widgetLayout->addWidget(groupLabel_2,14,1,1,3);
    this->widgetLayout->addWidget(LB_acro_yaw_p  , 15, 1, 1, 1);
    this->widgetLayout->addWidget(LB_atc_accel_p_max  , 16, 1, 1, 1);
    this->widgetLayout->addWidget(LB_atc_accel_r_max  , 17, 1, 1, 1);
    this->widgetLayout->addWidget(LB_atc_accel_y_max  , 18, 1, 1, 1);
    this->widgetLayout->addWidget(LB_atc_thr_mix_man  , 19, 1, 1, 1);
    this->widgetLayout->addWidget(LB_mot_thst_expo  , 20, 1, 1, 1);

    this->widgetLayout->addWidget(DS_acro_yaw_p  , 15,2, 1, 2);
    this->widgetLayout->addWidget(DS_atc_accel_p_max  , 16,2, 1, 2);
    this->widgetLayout->addWidget(DS_atc_accel_r_max  , 17,2, 1, 2);
    this->widgetLayout->addWidget(DS_atc_accel_y_max  , 18,2, 1, 2);
    this->widgetLayout->addWidget(DS_atc_thr_mix_man  , 19,2, 1, 2);
    this->widgetLayout->addWidget(DS_mot_thst_expo  , 20,2, 1, 2);

    this->widgetLayout->addLayout(widgetLayout_pb,21,1,1,3);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Expanding),2,0,1,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Expanding),2,4,1,1);

    this->widgetLayout->addLayout(subWidgetLayout_calcu,2,4,5,1);

    this->widgetLayout->setColumnStretch(0,1);
    this->widgetLayout->setColumnStretch(4,1);

    this->widgetLayout->setSpacing(2);

    this->setLayout(this->widgetLayout);


}

void CFG_InitCfg::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamInitCtrlCfg:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_initCFGparam_t param = link->getTVehicleParam().initCtrlCFG;
                DS_acro_yaw_p        ->setValue(param.acro_yaw_p   );
                DS_atc_accel_p_max   ->setValue(param.atc_accel_p_max*0.01f);
                DS_atc_accel_r_max   ->setValue(param.atc_accel_r_max*0.01f);
                DS_atc_accel_y_max   ->setValue(param.atc_accel_y_max*0.01f);
                DS_atc_rat_pit_fltd  ->setValue(param.atc_rat_pit_fltd);
                DS_atc_rat_pit_flte  ->setValue(param.atc_rat_pit_flte);
                DS_atc_rat_pit_fltt  ->setValue(param.atc_rat_pit_fltt);
                DS_atc_rat_rll_fltd  ->setValue(param.atc_rat_rll_fltd);
                DS_atc_rat_rll_flte  ->setValue(param.atc_rat_rll_flte);
                DS_atc_rat_rll_fltt  ->setValue(param.atc_rat_rll_fltt);
                DS_atc_rat_yaw_fltd  ->setValue(param.atc_rat_yaw_fltd);
                DS_atc_rat_yaw_flte  ->setValue(param.atc_rat_yaw_flte);
                DS_atc_rat_yaw_fltt  ->setValue(param.atc_rat_yaw_fltt);
                DS_atc_thr_mix_man   ->setValue(param.atc_thr_mix_man);
                DS_ins_accel_filter  ->setValue(param.ins_accel_filter);
                DS_ins_gyro_filter   ->setValue(param.ins_gyro_filter);
                DS_mot_thst_expo     ->setValue(param.mot_thst_expo);

                DS_acro_yaw_p        ->setChanged(false);
                DS_atc_accel_p_max   ->setChanged(false);
                DS_atc_accel_r_max   ->setChanged(false);
                DS_atc_accel_y_max   ->setChanged(false);
                DS_atc_rat_pit_fltd  ->setChanged(false);
                DS_atc_rat_pit_flte  ->setChanged(false);
                DS_atc_rat_pit_fltt  ->setChanged(false);
                DS_atc_rat_rll_fltd  ->setChanged(false);
                DS_atc_rat_rll_flte  ->setChanged(false);
                DS_atc_rat_rll_fltt  ->setChanged(false);
                DS_atc_rat_yaw_fltd  ->setChanged(false);
                DS_atc_rat_yaw_flte  ->setChanged(false);
                DS_atc_rat_yaw_fltt  ->setChanged(false);
                DS_atc_thr_mix_man   ->setChanged(false);
                DS_ins_accel_filter  ->setChanged(false);
                DS_ins_gyro_filter   ->setChanged(false);
                DS_mot_thst_expo     ->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_InitCfg::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_initCFGparam_t pkt{};

        pkt.is_set = 1;
        pkt.acro_yaw_p        = DS_acro_yaw_p        ->value();
        pkt.atc_accel_p_max   = DS_atc_accel_p_max   ->value()*100;
        pkt.atc_accel_r_max   = DS_atc_accel_r_max   ->value()*100;
        pkt.atc_accel_y_max   = DS_atc_accel_y_max   ->value()*100;
        pkt.atc_rat_pit_fltd  = DS_atc_rat_pit_fltd  ->value();
        pkt.atc_rat_pit_flte  = DS_atc_rat_pit_flte  ->value();
        pkt.atc_rat_pit_fltt  = DS_atc_rat_pit_fltt  ->value();
        pkt.atc_rat_rll_fltd  = DS_atc_rat_rll_fltd  ->value();
        pkt.atc_rat_rll_flte  = DS_atc_rat_rll_flte  ->value();
        pkt.atc_rat_rll_fltt  = DS_atc_rat_rll_fltt  ->value();
        pkt.atc_rat_yaw_fltd  = DS_atc_rat_yaw_fltd  ->value();
        pkt.atc_rat_yaw_flte  = DS_atc_rat_yaw_flte  ->value();
        pkt.atc_rat_yaw_fltt  = DS_atc_rat_yaw_fltt  ->value();
        pkt.atc_thr_mix_man   = DS_atc_thr_mix_man   ->value();
        pkt.ins_accel_filter  = DS_ins_accel_filter  ->value();
        pkt.ins_gyro_filter   = DS_ins_gyro_filter   ->value();
        pkt.mot_thst_expo     = DS_mot_thst_expo     ->value();
        link->do_setParamInitCtrlCfg(pkt);
    }
}

void CFG_InitCfg::calc_values()
{
    prop_size               = DS_prop_size->value();
    atc_accel_y_max = qMax((double)8000,(double)(-900 * prop_size + 36000));
    acro_yaw_p = 0.5f * atc_accel_y_max / 4500;
    atc_accel_p_max = qMax((double)10000, -2.613267 * qPow(prop_size, 3) + 343.39216 * qPow(prop_size, 2) - 15083.7121 * prop_size + 235771);
    atc_accel_r_max = atc_accel_p_max;
    ins_gyro_filter = qMax((double)20, (289.22 * qPow(prop_size, -0.838)));

    atc_rat_pit_fltd = qMax((double)10, ins_gyro_filter / 2);
    atc_rat_pit_flte = 0;
    atc_rat_pit_fltt = qMax((double)10, ins_gyro_filter / 2);
    atc_rat_rll_fltd = qMax((double)10, ins_gyro_filter / 2);
    atc_rat_rll_flte = 0;
    atc_rat_rll_fltt = qMax((double)10, ins_gyro_filter / 2);
    atc_rat_yaw_fltd = 0;
    atc_rat_yaw_flte = 2;
    atc_rat_yaw_fltt = qMax((double)10, ins_gyro_filter / 2);

    atc_thr_mix_man = 0.1;
    ins_accel_filter = 20;
    mot_thst_expo = 0.1405 * qLn(prop_size) + 0.3254;

    DS_acro_yaw_p        ->setValue(acro_yaw_p );
    DS_atc_accel_p_max   ->setValue(atc_accel_p_max*0.01f);
    DS_atc_accel_r_max   ->setValue(atc_accel_r_max*0.01f);
    DS_atc_accel_y_max   ->setValue(atc_accel_y_max*0.01f);
    DS_atc_rat_pit_fltd  ->setValue(atc_rat_pit_fltd);
    DS_atc_rat_pit_flte  ->setValue(atc_rat_pit_flte);
    DS_atc_rat_pit_fltt  ->setValue(atc_rat_pit_fltt);
    DS_atc_rat_rll_fltd  ->setValue(atc_rat_rll_fltd);
    DS_atc_rat_rll_flte  ->setValue(atc_rat_rll_flte);
    DS_atc_rat_rll_fltt  ->setValue(atc_rat_rll_fltt);
    DS_atc_rat_yaw_fltd  ->setValue(atc_rat_yaw_fltd);
    DS_atc_rat_yaw_flte  ->setValue(atc_rat_yaw_flte);
    DS_atc_rat_yaw_fltt  ->setValue(atc_rat_yaw_fltt);
    DS_atc_thr_mix_man   ->setValue(atc_thr_mix_man);
    DS_ins_accel_filter  ->setValue(ins_accel_filter);
    DS_ins_gyro_filter   ->setValue(ins_gyro_filter);
    DS_mot_thst_expo     ->setValue(mot_thst_expo);

}
