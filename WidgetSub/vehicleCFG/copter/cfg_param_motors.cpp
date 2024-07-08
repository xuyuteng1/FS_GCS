/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_param_motors.h"
#include "DMMM.h"
#include <qmath.h>

CFG_ParamMotors::CFG_ParamMotors()
{
    widget_init();
    connectSignalAndSlot();
}

QGridLayout *CFG_ParamMotors::getWidgetLayout() const
{
    return widgetLayout;
}

void CFG_ParamMotors::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_ParamMotors::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamMotors();}});
    connect(PB_upload   , &QPushButton::released,this,&CFG_ParamMotors::upload_param);
}

void CFG_ParamMotors::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("请按照说明,谨慎设置电机相关参数。"));
        LB_Info->setObjectName(QString::fromUtf8("warningLabel"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    if(LB_SpinMin == nullptr){
        LB_SpinMin = new QLabel(QStringLiteral("电机最小值:"));
        LB_SpinMin->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_SpinMin->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_SpinMin->setToolTip(QStringLiteral(""));
    }
    if(LB_SpinMax == nullptr){
        LB_SpinMax = new QLabel(QStringLiteral("电机最大值:"));
        LB_SpinMax->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_SpinMax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_SpinMax->setToolTip(QStringLiteral(""));
    }
    if(LB_SpinArm == nullptr){
        LB_SpinArm = new QLabel(QStringLiteral("电机解锁值:"));
        LB_SpinArm->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_SpinArm->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_SpinArm->setToolTip(QStringLiteral(""));
    }
    if(LB_PWMMin == nullptr){
        LB_PWMMin = new QLabel(QStringLiteral("PWM最小值:"));
        LB_PWMMin->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_PWMMin->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_PWMMin->setToolTip(QStringLiteral(""));
    }
    if(LB_PWMMax == nullptr){
        LB_PWMMax = new QLabel(QStringLiteral("PWM最大值:"));
        LB_PWMMax->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_PWMMax->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_PWMMax->setToolTip(QStringLiteral(""));
    }
    if(LB_Throttle_hover == nullptr){
        LB_Throttle_hover = new QLabel(QStringLiteral("悬停油门值:"));
        LB_Throttle_hover->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_Throttle_hover->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_Throttle_hover->setToolTip(QStringLiteral(""));
    }
    if(LB_hover_learn == nullptr){
        LB_hover_learn = new QLabel(QStringLiteral("悬停油门学习:"));
        LB_hover_learn->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_hover_learn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_hover_learn->setToolTip(QStringLiteral(""));
    }

    if(CB_hover_learn == nullptr){
        CB_hover_learn = new UComboBox();
        CB_hover_learn->setEditable(false);
        CB_hover_learn->addItem(QStringLiteral("关闭学习"),0);
        CB_hover_learn->addItem(QStringLiteral("开启学习"),1);
        CB_hover_learn->addItem(QStringLiteral("学习并保存"),2);
        CB_hover_learn->setChanged(false);
        CB_hover_learn->setToolTip(QStringLiteral("悬停油门学习开关,在定高或悬停等有高度保持的模式下,\r\n"
                                                  "若开启学习,飞控将自动学习悬停油门。"));
        CB_hover_learn->setObjectName("widgetComboBox");
    }
    if(SB_SpinMin == nullptr){
        SB_SpinMin = new USpinBox();
        SB_SpinMin->setRange(0,30);
        SB_SpinMin->setValue(0);
        SB_SpinMin->setSingleStep(1);
        SB_SpinMin->setAlignment(Qt::AlignCenter);
        SB_SpinMin->setSuffix(QStringLiteral(" %"));
        SB_SpinMin->setChanged(false);
        SB_SpinMin->setObjectName("widgetSpinBox");
        SB_SpinMin->setToolTip(QStringLiteral("电机最小值:解锁后整个飞行过程中,电机的输出值将始终大于此值。"));
    }
    if(SB_SpinMax == nullptr){
        SB_SpinMax = new USpinBox();
        SB_SpinMax->setRange(70,100);
        SB_SpinMax->setValue(100);
        SB_SpinMax->setSingleStep(1);
        SB_SpinMax->setAlignment(Qt::AlignCenter);
        SB_SpinMax->setSuffix(QStringLiteral(" %"));
        SB_SpinMax->setChanged(false);
        SB_SpinMax->setObjectName("widgetSpinBox");
        SB_SpinMax->setToolTip(QStringLiteral("电机最大值:解锁后整个飞行过程中,电机的输出值将始终小于此值。"));
    }
    if(SB_SpinArm == nullptr){
        SB_SpinArm = new USpinBox();
        SB_SpinArm->setRange(0,30);
        SB_SpinArm->setValue(0);
        SB_SpinArm->setSingleStep(1);
        SB_SpinArm->setAlignment(Qt::AlignCenter);
        SB_SpinArm->setSuffix(QStringLiteral(" %"));
        SB_SpinArm->setChanged(false);
        SB_SpinArm->setObjectName("widgetSpinBox");
        SB_SpinArm->setToolTip(QStringLiteral("电机解锁值:解锁后,电机的预旋油门。"));
    }

    if(SB_Throttle_hover == nullptr){
        SB_Throttle_hover = new USpinBox();
        SB_Throttle_hover->setRange(0,100);
        SB_Throttle_hover->setValue(0);
        SB_Throttle_hover->setSingleStep(1);
        SB_Throttle_hover->setAlignment(Qt::AlignCenter);
        SB_Throttle_hover->setSuffix(QStringLiteral(" %"));
        SB_Throttle_hover->setChanged(false);
        SB_Throttle_hover->setObjectName("widgetSpinBox");
        SB_Throttle_hover->setToolTip(QStringLiteral("悬停油门值。"));
    }

    if(SB_PWMMin == nullptr){
        SB_PWMMin = new USpinBox();
        SB_PWMMin->setRange(0,1500);
        SB_PWMMin->setValue(0);
        SB_PWMMin->setSingleStep(1);
        SB_PWMMin->setAlignment(Qt::AlignCenter);
        SB_PWMMin->setSuffix(QStringLiteral(" us"));
        SB_PWMMin->setChanged(false);
        SB_PWMMin->setObjectName("widgetSpinBox");
        SB_PWMMin->setToolTip(QStringLiteral("PWM最小值:电机的PWM范围的最小值,若值为0，则以每个电机通道的PWM值为准。"));
    }
    if(SB_PWMMax == nullptr){
        SB_PWMMax = new USpinBox();
        SB_PWMMax->setRange(0,2200);
        SB_PWMMax->setValue(0);
        SB_PWMMax->setSingleStep(1);
        SB_PWMMax->setAlignment(Qt::AlignCenter);
        SB_PWMMax->setSuffix(QStringLiteral(" us"));
        SB_PWMMax->setChanged(false);
        SB_PWMMax->setObjectName("widgetSpinBox");
        SB_PWMMax->setToolTip(QStringLiteral("PWM最大值:电机的PWM范围的最大值,若值为0，则以每个电机通道的PWM值为准。"));
    }

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
    }

    widgetLayout->addWidget(LB_Info,            0 ,0 ,1 ,20);
    widgetLayout->addWidget(LB_Throttle_hover,  1 ,9 ,1 ,1 );
    widgetLayout->addWidget(LB_SpinArm,         2 ,9 ,1 ,1 );
    widgetLayout->addWidget(LB_SpinMin,         3 ,9 ,1 ,1 );
    widgetLayout->addWidget(LB_SpinMax,         4 ,9 ,1 ,1 );
    widgetLayout->addWidget(LB_PWMMin,          5 ,9 ,1 ,1 );
    widgetLayout->addWidget(LB_PWMMax,          6 ,9 ,1 ,1 );

    widgetLayout->addWidget(SB_Throttle_hover,  1 ,10,1 ,1 );
    widgetLayout->addWidget(CB_hover_learn,     1 ,11,1 ,1 );
    widgetLayout->addWidget(SB_SpinArm,         2 ,10,1 ,1 );
    widgetLayout->addWidget(SB_SpinMin,         3 ,10,1 ,1 );
    widgetLayout->addWidget(SB_SpinMax,         4 ,10,1 ,1 );
    widgetLayout->addWidget(SB_PWMMin,          5 ,10,1 ,1 );
    widgetLayout->addWidget(SB_PWMMax,          6 ,10,1 ,1 );


    widgetLayout_pb->addStretch(5);
    widgetLayout_pb->addWidget(PB_download,1);
    widgetLayout_pb->addWidget(PB_upload,1);
    widgetLayout_pb->addStretch(5);
//    widgetLayout_pb->addWidget(PB_upload,  0 ,10,1 ,1 );
//    widgetLayout_pb->setRowMinimumHeight(0,30);

    widgetLayout->addLayout(widgetLayout_pb,8,0,1,20);

//    widgetLayout->setVerticalSpacing(10);
    widgetLayout->setContentsMargins(5,20,5,10);
    widgetLayout->setRowMinimumHeight(0,60);
    widgetLayout->setRowMinimumHeight(1,30);
    widgetLayout->setRowMinimumHeight(2,30);
    widgetLayout->setRowMinimumHeight(3,30);
    widgetLayout->setRowMinimumHeight(4,30);
    widgetLayout->setRowMinimumHeight(5,30);
    widgetLayout->setRowMinimumHeight(6,30);
    widgetLayout->setRowMinimumHeight(7,20);
    widgetLayout->setRowMinimumHeight(8,30);
}

void CFG_ParamMotors::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamMotors:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_Motors pkt = link->getTVehicleParam().Motors;


                SB_SpinMin->setValue(pkt._spin_min);                                    // throttle out ratio which produces the minimum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
                SB_SpinMax->setValue(pkt._spin_max);                                    // throttle out ratio which produces the maximum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
                SB_SpinArm->setValue(pkt._spin_arm);                                    // throttle out ratio which produces the armed spin rate.  (i.e. 0 ~ 1 ) of the full throttle range
                SB_PWMMin->setValue(pkt._pwm_min);                                      // minimum PWM value that will ever be output to the motors (if 0, vehicle's throttle input channel's min pwm used)
                SB_PWMMax->setValue(pkt._pwm_max);                                      // maximum PWM value that will ever be output to the motors (if 0, vehicle's throttle input channel's max pwm used)
                SB_Throttle_hover->setValue(pkt._throttle_hover);                       // estimated throttle required to hover throttle in the range 0 ~ 1
                CB_hover_learn->setCurrentIndex(CB_hover_learn->findData(QVariant(pkt._throttle_hover_learn)));


                SB_SpinMin->setChanged(false);
                SB_SpinMax->setChanged(false);
                SB_SpinArm->setChanged(false);
                SB_PWMMin->setChanged(false);
                SB_PWMMax->setChanged(false);
                SB_Throttle_hover->setChanged(false);
                CB_hover_learn->setChanged(false);
            }
        }break;
        default:break;
    }
}

void CFG_ParamMotors::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_Motors pkt{};

        pkt.is_set = 1;
        pkt._spin_min = SB_SpinMin->value();                                    // throttle out ratio which produces the minimum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
        pkt._spin_max = SB_SpinMax->value();                                    // throttle out ratio which produces the maximum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
        pkt._spin_arm = SB_SpinArm->value();                                    // throttle out ratio which produces the armed spin rate.  (i.e. 0 ~ 1 ) of the full throttle range
        pkt._pwm_min = SB_PWMMin->value();                                      // minimum PWM value that will ever be output to the motors (if 0, vehicle's throttle input channel's min pwm used)
        pkt._pwm_max = SB_PWMMax->value();                                      // maximum PWM value that will ever be output to the motors (if 0, vehicle's throttle input channel's max pwm used)
        pkt._throttle_hover = SB_Throttle_hover->value();                       // estimated throttle required to hover throttle in the range 0 ~ 1
        pkt._throttle_hover_learn = CB_hover_learn->currentData().toInt();      // enable/disabled hover thrust learning

        link->do_setParamMotors(pkt);
    }
}
