/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_param_failsafe.h"
#include "DMMM.h"
#include <qmath.h>

CFG_ParamFailsafe::CFG_ParamFailsafe(QWidget *parent):
    QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
}


void CFG_ParamFailsafe::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamFailsafe::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamfailsafe();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamFailsafe::upload_param);
    connect(PB_Calcu   , &QPushButton::released,this,[=]{calc_values();});


//    connect(PB_Stop        , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MotorTest_stop();}});
//    connect(PB_OrderStart  , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MotorTest(1,motor_count,SP_MotorTime->value(),SP_MotorPCT->value());}});
//    connect(PB_SimpleMagCali    , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagSimpleCaliStart(this->SP_FixedYaw->value());}});
//    connect(PB_InFlightMagCaliCancel, &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagInFlightCaliCancel();}});
}

void CFG_ParamFailsafe::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("故障保护"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    if(LB_Info_Icon == nullptr){
        LB_Info_Icon = new QLabel();
        LB_Info_Icon->setPixmap(QPixmap(":/img/status/text_woring.png"));
        LB_Info_Icon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("请谨慎设置故障响应条件及动作            "));
        LB_Info->setObjectName(QString::fromUtf8("warningLabel"));
        LB_Info->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
    if(LB_Layout == nullptr){
        LB_Layout = new QHBoxLayout();
        LB_Layout->addWidget(LB_Info_Icon);
        LB_Layout->addWidget(LB_Info);
        LB_Layout->setAlignment(Qt::AlignCenter);
    }
    if(LB_Crash == nullptr){
        LB_Crash = new QLabel(QStringLiteral("飞行坠毁保护:"));
        LB_Crash->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Crash->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_Crash->setToolTip(QStringLiteral("触发条件：倾斜角大于15°,角度差值大于30°,\r\n"
                                      "速度低于10m/s,以上持续2s以上"));
    }

    if(LB_Vibe == nullptr){
        LB_Vibe = new QLabel(QStringLiteral("飞行震动补偿:"));
        LB_Vibe->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_Vibe->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_Vibe->setToolTip(QStringLiteral("当飞控系统检测到震动过大时将开启震动补偿,\r\n"
                                           "将会牺牲高度控制精度来会降低震动带来的影响，\r\n"
                                           "为避免出现震动故障,请务必在飞行前进行震动测试。"));
    }

    if(LB_EKF == nullptr){
        LB_EKF = new QLabel(QStringLiteral("EKF 故障保护:"));
        LB_EKF->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_EKF->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_EKF->setToolTip(QStringLiteral("飞控EKF系统将实时监测当前状态,当出现速度、位置\r\n"
                                          "高度、磁力计、空速计等方差过大时,触发保护。常见\r\n"
                                          "原因如卫星失锁等。\r\n"
                                          "过程中，EKF尝试自动修复(如重置罗盘、切换传感器等)。\r\n\r\n"
                                          "如果切换\"高度保持模式\"失败，则会切换\"降落模式\"，\r\n"
                                          "降落时会先悬停固定时间（默认10s）然后开始降落。"));
        LB_Vibe->setToolTipDuration(60000);
    }

    if(LB_RC == nullptr){
        LB_RC = new QLabel(QStringLiteral("遥控故障保护:"));
        LB_RC->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_RC->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_RC->setToolTip(QStringLiteral("遥控故障仅在辅助模式下触发保护。\r\n"
                                         "辅助模式指需要遥控器参与的飞行模式，如\"自稳模式\"、\r\n"
                                         "\"定高模式\"、\"悬停模式\"等。"));
    }

    if(LB_GCS == nullptr){
        LB_GCS = new QLabel(QStringLiteral("通信故障保护:"));
        LB_GCS->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_GCS->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_GCS->setToolTip(QStringLiteral("遥控故障仅在非辅助模式下触发保护。\r\n"
                                         "非辅助辅助模式指需要不用遥控器参与的飞行模式，如\"自主任务\"、\r\n"
                                         "\"指点模式\"等。"));
    }

    if(LB_BatL1 == nullptr){
        LB_BatL1 = new QLabel(QStringLiteral("低电 1 级保护:"));
        LB_BatL1->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_BatL1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_BatL1->setToolTip(QStringLiteral("低电保护系统会优先检测2级保护电压,未检测到触发2级保护电压\r\n"
                                            "才会检测1级保护电压。\r\n\r\n"
                                            "触发条件:持续10秒电压低于保护电压。"));
    }
    if(LB_BatL2 == nullptr){
        LB_BatL2 = new QLabel(QStringLiteral("低电 2 级保护:"));
        LB_BatL2->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_BatL2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_BatL2->setToolTip(QStringLiteral("低电保护系统会优先检测2级保护电压,未检测到触发2级保护电压\r\n"
                                            "才会检测1级保护电压。\r\n\r\n"
                                            "触发条件:持续10秒电压低于保护电压。"));
    }

    if(LB_BatArm == nullptr){
        LB_BatArm = new QLabel(QStringLiteral("解锁最低电压:"));
        LB_BatArm->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_BatArm->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_BatArm->setToolTip(QStringLiteral("低于此电压将拒绝解锁。"));
    }

    if( LB_BatMax == nullptr){
        LB_BatMax = new QLabel(QStringLiteral("电源最大电压:"));
        LB_BatMax->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_BatMax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_BatMax->setToolTip(QStringLiteral("电源最大电压用于飞控系统进行电源补偿计算，应设置为电池的满电电压。"));
    }
    if( LB_BatMin == nullptr){
        LB_BatMin = new QLabel(QStringLiteral("电源最小电压:"));
        LB_BatMin->setObjectName(QString::fromUtf8("widgetNameLabel"));
        LB_BatMin->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_BatMin->setToolTip(QStringLiteral("电源最小电压用于飞控系统进行电源补偿计算，\r\n"
                                             "应设置为电池能正常放电的最小电压（！！！非电压保护！！！）。"));
    }

    if(this->crashEnableCheckBox == nullptr){
        this->crashEnableCheckBox = new QCheckBox(QStringLiteral("开启保护"));
        this->crashEnableCheckBox->setToolTip(QStringLiteral("触发条件：倾斜角大于15°,角度差值大于30°,\r\n"
                                              "速度低于10m/s,以上持续2s以上"));
        this->crashEnableCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->crashDisEnableCheckBox == nullptr){
        this->crashDisEnableCheckBox = new QCheckBox(QStringLiteral("关闭保护"));
        this->crashDisEnableCheckBox->setToolTip(QStringLiteral("触发条件：倾斜角大于15°,角度差值大于30°,\r\n"
                                              "速度低于10m/s,以上持续2s以上"));
        this->crashDisEnableCheckBox->setObjectName("widgetCheckBox");
    }

    if(this->crashButtonGroup == nullptr){
        this->crashButtonGroup = new QButtonGroup();
        this->crashButtonGroup->addButton(this->crashEnableCheckBox);
        this->crashButtonGroup->addButton(this->crashDisEnableCheckBox);
    }


    if(this->vibeEnableCheckBox == nullptr){
        this->vibeEnableCheckBox = new QCheckBox(QStringLiteral("开启补偿"));
        this->vibeEnableCheckBox->setToolTip(QStringLiteral("当飞控系统检测到震动过大时将开启震动补偿,\r\n"
                         "将会牺牲高度控制精度来会降低震动带来的影响，\r\n"
                         "为避免出现震动故障,请务必在飞行前进行震动测试。"));
        this->vibeEnableCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->vibeDisEnableCheckBox == nullptr){
        this->vibeDisEnableCheckBox = new QCheckBox(QStringLiteral("关闭补偿"));
        this->vibeDisEnableCheckBox->setToolTip(QStringLiteral("当飞控系统检测到震动过大时将开启震动补偿,\r\n"
                       "将会牺牲高度控制精度来会降低震动带来的影响，\r\n"
                       "为避免出现震动故障,请务必在飞行前进行震动测试。"));
        this->vibeDisEnableCheckBox->setObjectName("widgetCheckBox");
    }

    if(this->vibeButtonGroup == nullptr){
        this->vibeButtonGroup = new QButtonGroup();
        this->vibeButtonGroup->addButton(this->vibeEnableCheckBox);
        this->vibeButtonGroup->addButton(this->vibeDisEnableCheckBox);
    }

    //    0:关闭
    //    1:降落
    //    2:定高模式
    //    3:强制降落(任何模式都降落)
    if(CB_EKF == nullptr){
        CB_EKF = new UComboBox();
        CB_EKF->setEditable(false);
        CB_EKF->addItem(QStringLiteral("关闭保护"),0);
        CB_EKF->addItem(QStringLiteral("降落模式"),1);
        CB_EKF->addItem(QStringLiteral("定高模式"),2);
        CB_EKF->addItem(QStringLiteral("强制降落"),3);
        CB_EKF->setToolTip(QStringLiteral("非辅助模式下，请保持遥控器油门处于中立位。\r\n"
                                          "定高模式-飞行过程中将会检测遥控器,如果遥控器异常，将会切换\"降落模式\"。\r\n"
                                          "降落模式-降落时会先悬停固定时间（默认10s）然后,开始降落。\r\n"
                                          "强制降落-当触发保护,即使在自稳模式下,仍然会执行降落模式。"));
        CB_EKF->setToolTipDuration(60000);
        CB_EKF->setChanged(false);
    }

    //    0:关闭
    //    1,2:返航
    //    3:降落
    //    4:智能返航
    //    5:智能返航（返航失败直接降落）

    if(CB_RC == nullptr){
        CB_RC = new UComboBox();
        CB_RC->setEditable(false);
        CB_RC->addItem(QStringLiteral("关闭保护"),0);
        CB_RC->addItem(QStringLiteral("返航模式"),1);
        CB_RC->addItem(QStringLiteral("降落模式"),3);
        CB_RC->addItem(QStringLiteral("智能返航1"),4);
        CB_RC->addItem(QStringLiteral("智能返航2"),5);
        CB_RC->setChanged(false);
        CB_RC->setToolTip(QStringLiteral("遥控故障仅在辅助模式下触发保护。\r\n"
                                         "辅助模式指需要遥控器参与的飞行模式，如\"自稳模式\"、\r\n"
                                         "\"定高模式\"、\"悬停模式\"等。"));
    }

    if(CB_GCS == nullptr){
        CB_GCS = new UComboBox();
        CB_GCS->setEditable(false);
        CB_GCS->addItem(QStringLiteral("关闭保护"),0);
        CB_GCS->addItem(QStringLiteral("返航模式"),1);
        CB_GCS->addItem(QStringLiteral("降落模式"),3);
        CB_GCS->addItem(QStringLiteral("智能返航1"),4);
        CB_GCS->addItem(QStringLiteral("智能返航2"),5);
        CB_GCS->setChanged(false);
        CB_GCS->setToolTip(QStringLiteral("遥控故障仅在非辅助模式下触发保护。\r\n"
                                         "非辅助辅助模式指需要不用遥控器参与的飞行模式，如\"自主任务\"、\r\n\"指点模式\"等。\r\n\r\n"
                                          "智能返航1-若切换智能返航失败,则会切换返航模式。\r\n"
                                          "智能返航2-若切换智能返航失败,则会切换降落模式"));
    }
    //    0:关闭
    //    1:降落
    //    2:返航
    //    3:智能返航
    //    4:智能返航（返航失败直接降落）

    if( CB_BatL1 == nullptr){
        CB_BatL1 = new UComboBox();
        CB_BatL1->setEditable(false);
        CB_BatL1->addItem(QStringLiteral("关闭保护"),0);
        CB_BatL1->addItem(QStringLiteral("返航模式"),2);
        CB_BatL1->addItem(QStringLiteral("降落模式"),1);
        CB_BatL1->addItem(QStringLiteral("智能返航1"),3);
        CB_BatL1->addItem(QStringLiteral("智能返航2"),4);
        CB_BatL1->setChanged(false);
        CB_BatL1->setToolTip(QStringLiteral("遥控故障仅在非辅助模式下触发保护。\r\n"
                                         "非辅助辅助模式指需要不用遥控器参与的飞行模式，如\"自主任务\"、\r\n\"指点模式\"等。\r\n\r\n"
                                          "智能返航1-若切换智能返航失败,则会切换返航模式。\r\n"
                                          "智能返航2-若切换智能返航失败,则会切换降落模式"));
    }

    if( CB_BatL2 == nullptr){
        CB_BatL2 = new UComboBox();
        CB_BatL2->setEditable(false);
        CB_BatL2->addItem(QStringLiteral("关闭保护"),0);
        CB_BatL2->addItem(QStringLiteral("返航模式"),2);
        CB_BatL2->addItem(QStringLiteral("降落模式"),1);
        CB_BatL2->addItem(QStringLiteral("智能返航1"),3);
        CB_BatL2->addItem(QStringLiteral("智能返航2"),4);
        CB_BatL2->setChanged(false);
        CB_BatL2->setToolTip(QStringLiteral("遥控故障仅在非辅助模式下触发保护。\r\n"
                                         "非辅助辅助模式指需要不用遥控器参与的飞行模式，如\"自主任务\"、\r\n\"指点模式\"等。\r\n\r\n"
                                          "智能返航1-若切换智能返航失败,则会切换返航模式。\r\n"
                                          "智能返航2-若切换智能返航失败,则会切换降落模式"));
    }

    if(QB_GCSTime == nullptr){
        QB_GCSTime = new USpinBox();
        QB_GCSTime->setRange(5,200);
        QB_GCSTime->setValue(5);
        QB_GCSTime->setAlignment(Qt::AlignCenter);
        QB_GCSTime->setSuffix(QStringLiteral(" 秒"));
        QB_GCSTime->setChanged(false);
        QB_GCSTime->setToolTip(QStringLiteral("通信超时时间,通信持续丢失超过此时间,将触发保护。"));
    }

    if(QB_BatL1Val == nullptr){
        QB_BatL1Val = new UDoubleSpinBox();
        QB_BatL1Val->setRange(0,2000);
        QB_BatL1Val->setValue(0);
        QB_BatL1Val->setAlignment(Qt::AlignCenter);
        QB_BatL1Val->setSuffix(QStringLiteral(" V"));
        QB_BatL1Val->setToolTip(QStringLiteral("保护电压,当电压持续低于设定值10秒以上,将触发保护。"));
        QB_BatL1Val->setDecimals(1);
        QB_BatL1Val->setChanged(false);

    }
    if(QB_BatL2Val == nullptr){
        QB_BatL2Val = new UDoubleSpinBox();
        QB_BatL2Val->setRange(0,2000);
        QB_BatL2Val->setValue(0);
        QB_BatL2Val->setAlignment(Qt::AlignCenter);
        QB_BatL2Val->setSuffix(QStringLiteral(" V"));
        QB_BatL2Val->setDecimals(1);
        QB_BatL2Val->setToolTip(QStringLiteral("保护电压,当电压持续低于设定值10秒以上,将触发保护。"));
        QB_BatL2Val->setChanged(false);
    }

    if( QB_BatArm == nullptr){
        QB_BatArm = new UDoubleSpinBox();
        QB_BatArm->setRange(0,2000);
        QB_BatArm->setValue(0);
        QB_BatArm->setAlignment(Qt::AlignCenter);
        QB_BatArm->setSuffix(QStringLiteral(" V"));
        QB_BatArm->setDecimals(1);
        QB_BatArm->setToolTip(QStringLiteral("低于此电压将拒绝解锁。"));
        QB_BatArm->setChanged(false);
    }
    if( QB_BatMax == nullptr){
        QB_BatMax = new UDoubleSpinBox();
        QB_BatMax->setRange(0,2000);
        QB_BatMax->setValue(0);
        QB_BatMax->setAlignment(Qt::AlignCenter);
        QB_BatMax->setSuffix(QStringLiteral(" V"));
        QB_BatMax->setDecimals(1);
        QB_BatMax->setToolTip(QStringLiteral("电源最大电压用于飞控系统进行电源补偿计算，应设置为电池的满电电压。"));
        QB_BatMax->setChanged(false);
    }
    if( QB_BatMin == nullptr){
        QB_BatMin = new UDoubleSpinBox();
        QB_BatMin->setRange(0,2000);
        QB_BatMin->setValue(0);
        QB_BatMin->setAlignment(Qt::AlignCenter);
        QB_BatMin->setSuffix(QStringLiteral(" V"));
        QB_BatMin->setDecimals(1);
        QB_BatMin->setToolTip(QStringLiteral("电源最小电压用于飞控系统进行电源补偿计算，\r\n"
                                             "应设置为电池能正常放电的最小电压（！！！非电压保护！！！）。"));
        QB_BatMin->setChanged(false);
    }

    if( DS_batt_cells == nullptr){
        DS_batt_cells = new QSpinBox();
        DS_batt_cells->setRange(1,200);
        DS_batt_cells->setValue(6);
        DS_batt_cells->setAlignment(Qt::AlignCenter);
        DS_batt_cells->setSuffix(QStringLiteral(" S"));
        DS_batt_cells->setToolTip(QStringLiteral("电池节数。"));
    }

    if(this->battTypeCheckBox == nullptr){
        this->battTypeCheckBox = new QCheckBox(QStringLiteral("普通版"));
        this->battTypeCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->battTypeHVCheckBox == nullptr){
        this->battTypeHVCheckBox = new QCheckBox(QStringLiteral("高压版"));
        this->battTypeHVCheckBox->setObjectName("widgetCheckBox");
    }

    if(this->battTypeGroup == nullptr){
        this->battTypeGroup = new QButtonGroup();
        this->battTypeGroup->addButton(this->battTypeCheckBox);
        this->battTypeGroup->addButton(this->battTypeHVCheckBox);
    }
    if( PB_Calcu == nullptr){
        PB_Calcu = new QPushButton(QStringLiteral("计算电压"));
        PB_Calcu->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_Calcu->setToolTip(QStringLiteral(""));
    }

    if(LB_BattInfo == nullptr){
        LB_BattInfo = new QLabel(QStringLiteral("左侧电压可以依据电池\r\n"
                                                                        "节数和电池类型自动计算"));
        LB_BattInfo->setObjectName(QString::fromUtf8("CFGLabelWarning"));
        LB_BattInfo->setAlignment(Qt::AlignCenter);
    }


    if(Group_Calcu == nullptr){
        Group_Calcu = new QGroupBox(QStringLiteral("计算参数"));
        Group_Calcu->setObjectName("widgetGroupBox");
        Group_Calcu->setAlignment(Qt::AlignCenter);
    }
    if(Layout_Batt == nullptr){
        Layout_Batt = new QGridLayout(Group_Calcu);
        Layout_Batt->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    Layout_Batt->addWidget(LB_BattInfo,0,0,2,2);
    Layout_Batt->addWidget(battTypeCheckBox,2,0,1,1);
    Layout_Batt->addWidget(battTypeHVCheckBox,2,1,1,1);
    Layout_Batt->addWidget(DS_batt_cells,3,0,1,1);
    Layout_Batt->addWidget(PB_Calcu,3,1,1,1);
    Layout_Batt->setAlignment(Qt::AlignCenter);

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
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    QGridLayout *subLayout_Batt = new QGridLayout();
    subLayout_Batt->addWidget(Group_Calcu,0,0,1,1);
    subLayout_Batt->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding),0,1,1,1);

    QLabel * spaceLabel = new QLabel();
    spaceLabel->setObjectName("widgetSpaceLabel");

    this->widgetLayout->addWidget(this->titleLabel,0,0,2,8);
    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding),2,0,13,1);
    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding),2,7,13,1);

    widgetLayout->addWidget(LB_Crash,   2 ,1,1 ,1 );
    widgetLayout->addWidget(crashEnableCheckBox,   2 ,2,1 ,2 );
    widgetLayout->addWidget(crashDisEnableCheckBox,   2 ,4,1 ,2 );

    widgetLayout->addWidget(LB_Vibe,   3 ,1,1 ,1 );
    widgetLayout->addWidget(vibeEnableCheckBox,   3 ,2,1 ,2 );
    widgetLayout->addWidget(vibeDisEnableCheckBox,   3 ,4,1 ,2 );

    widgetLayout->addWidget(LB_EKF,     4 ,1 ,1 ,1 );
    widgetLayout->addWidget(CB_EKF,     4,2,1 ,2 );
    widgetLayout->addWidget(LB_RC,     5 ,1 ,1 ,1 );
    widgetLayout->addWidget(CB_RC,     5,2,1 ,2 );

    widgetLayout->addWidget(LB_GCS,     6 ,1 ,1 ,1 );
    widgetLayout->addWidget(CB_GCS,     6 ,2,1 ,2 );
    widgetLayout->addWidget(QB_GCSTime, 6 ,4,1 ,2 );

    widgetLayout->addWidget(spaceLabel,   7 ,1,1 ,6 );

    widgetLayout->addWidget(LB_BatL1,   8 ,1,1 ,1 );
    widgetLayout->addWidget(CB_BatL1,   8 ,2,1 ,2 );
    widgetLayout->addWidget(QB_BatL1Val,8 ,4,1 ,2 );

    widgetLayout->addWidget(LB_BatL2,   9,1 ,1 ,1 );
    widgetLayout->addWidget(CB_BatL2,   9 ,2,1 ,2 );
    widgetLayout->addWidget(QB_BatL2Val,9 ,4,1 ,2 );

    widgetLayout->addWidget(LB_BatArm,   10 ,1 ,1 ,1 );
    widgetLayout->addWidget(QB_BatArm,   10 ,2,1 ,1 );

    widgetLayout->addWidget(LB_BatMax,   11,1,1 ,1 );
    widgetLayout->addWidget(QB_BatMax,   11 ,2,1 ,1 );

    widgetLayout->addWidget(LB_BatMin,   12,1,1 ,1 );
    widgetLayout->addWidget(QB_BatMin,   12,2,1 ,1 );

    widgetLayout->addWidget(PB_download,   13,1,1 ,1 );
    widgetLayout->addWidget(PB_upload,   13,5,1 ,1 );

    widgetLayout->addLayout(subLayout_Batt,7,7,4,1);

    widgetLayout->addItem(LB_Layout,   14 ,1 ,1 ,5);

    this->widgetLayout->setColumnStretch(0,1);
    this->widgetLayout->setColumnStretch(8,1);


    this->widgetLayout->addItem(new QSpacerItem(40,10,QSizePolicy::Expanding,QSizePolicy::Expanding),15,2,1,1);

    this->setLayout(this->widgetLayout);
    this->setObjectName("widgetGroupBox_no_border");
}

void CFG_ParamFailsafe::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamFailsafe:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_failsafe_t pkt = link->getTVehicleParam().failsafe;
                if(pkt.crash_enable){
                    crashEnableCheckBox->setChecked(true);
                    crashDisEnableCheckBox->setChecked(false);
                }else{
                    crashEnableCheckBox->setChecked(false);
                    crashDisEnableCheckBox->setChecked(true);
                }

                if(pkt.vibration_enable){
                    vibeEnableCheckBox->setChecked(true);
                    vibeDisEnableCheckBox->setChecked(false);
                }else{
                    vibeEnableCheckBox->setChecked(false);
                    vibeDisEnableCheckBox->setChecked(true);
                }

//                CB_Crash->setCurrentIndex(CB_Crash->findData(QVariant(pkt.crash_enable)));
//                CB_Vibe->setCurrentIndex(CB_Vibe->findData(QVariant(pkt.vibration_enable)));
                CB_EKF->setCurrentIndex(CB_EKF->findData(QVariant(pkt.Ekf)));
                CB_RC->setCurrentIndex(CB_RC->findData(QVariant(pkt.RC)));
                CB_GCS->setCurrentIndex(CB_GCS->findData(QVariant(pkt.GCS)));
                CB_BatL1->setCurrentIndex(CB_BatL1->findData(QVariant(pkt.battery_level1)));
                CB_BatL2->setCurrentIndex(CB_BatL2->findData(QVariant(pkt.battery_level2)));

                QB_GCSTime->setValue(pkt.GCS_timeout);
                QB_BatL1Val->setValue(pkt.battery_level1_voltage*0.1f);
                QB_BatL2Val->setValue(pkt.battery_level2_voltage*0.1f);

                QB_BatArm->setValue(pkt.batt_arm_volt*0.1f);
                QB_BatMax->setValue(pkt._batt_voltage_max*0.1f);
                QB_BatMin->setValue(pkt._batt_voltage_min*0.1f);

//                CB_Crash->setChanged(false);
//                CB_Vibe->setChanged(false);
                CB_EKF->setChanged(false);
                CB_RC->setChanged(false);
                CB_GCS->setChanged(false);
                CB_BatL1->setChanged(false);
                CB_BatL2->setChanged(false);
                QB_GCSTime->setChanged(false);
                QB_BatL1Val->setChanged(false);
                QB_BatL2Val->setChanged(false);
                QB_BatArm->setChanged(false);
                QB_BatMax->setChanged(false);
                QB_BatMin->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamFailsafe::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_failsafe_t pkt{};
        pkt.is_set = 1;
//        pkt.crash_enable = CB_Crash->currentData().toInt();
//        pkt.vibration_enable = CB_Vibe->currentData().toInt();
        pkt.crash_enable = crashEnableCheckBox->isChecked() ? 1 : 0;
        pkt.vibration_enable = vibeEnableCheckBox->isChecked() ? 1 : 0;
        pkt.Ekf = CB_EKF->currentData().toInt();
        pkt.RC = CB_RC->currentData().toInt();
        pkt.GCS = CB_GCS->currentData().toInt();
        pkt.GCS_timeout = QB_GCSTime->value();                /*<  单位为S >*/
        pkt.battery_level1 = CB_BatL1->currentData().toInt();
        pkt.battery_level2 = CB_BatL2->currentData().toInt();
        pkt.battery_level1_voltage = QB_BatL1Val->value()*10;      /*<  单位为V*10 >*/
        pkt.battery_level2_voltage = QB_BatL2Val->value()*10;      /*<  单位为V*10 >*/

        pkt.batt_arm_volt = QB_BatArm->value()*10;      /*<  单位为V*10 >*/
        pkt._batt_voltage_max = QB_BatMax->value()*10;      /*<  单位为V*10 >*/
        pkt._batt_voltage_min = QB_BatMin->value()*10;      /*<  单位为V*10 >*/

        link->do_setParamfailsafe(pkt);
    }
}

void CFG_ParamFailsafe::calc_values()
{

    int batt_cells = this->DS_batt_cells->value();

    float batt_cell_max_voltage   = 4.2f;
    // 高压版
    if(this->battTypeHVCheckBox->isChecked() ){
        batt_cell_max_voltage = 4.35f;
    }

    float batt_cell_min_voltage   = 3.3f;

    float batt_arm_volt = (batt_cells - 1) * 0.1 + (batt_cell_min_voltage+0.4) * batt_cells;
    float batt_crt_volt = (batt_cell_min_voltage + 0.3) * batt_cells;
    float batt_low_volt = (batt_cell_min_voltage + 0.4) * batt_cells;
    float mot_bat_volt_max = batt_cell_max_voltage * batt_cells;
    float mot_bat_volt_min = batt_cell_min_voltage * batt_cells;

    this->QB_BatArm->setValue(batt_arm_volt);
    this->QB_BatMax->setValue(mot_bat_volt_max);
    this->QB_BatMin->setValue(mot_bat_volt_min);
    this->QB_BatL1Val->setValue(batt_low_volt);
    this->QB_BatL2Val->setValue(batt_crt_volt);
}
