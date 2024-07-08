/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "cfg_motortest.h"
#include "DMMM.h"
#include <qmath.h>

CFG_MotorTest::CFG_MotorTest()
{
    widget_init();
    connectSignalAndSlot();
}

QGridLayout *CFG_MotorTest::getWidgetLayout() const
{
    return widgetLayout;
}

void CFG_MotorTest::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_MotorTest::handle_DMMM_event);
    connect(PB_Start       , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MotorTest(this->SP_MotorID->value(),1,SP_MotorTime->value(),SP_MotorPCT->value());}});
    connect(PB_Stop        , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MotorTest_stop();}});
    connect(PB_OrderStart  , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MotorTest(1,motor_count,SP_MotorTime->value(),SP_MotorPCT->value());}});
//    connect(PB_SimpleMagCali    , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagSimpleCaliStart(this->SP_FixedYaw->value());}});
//    connect(PB_InFlightMagCaliCancel, &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagInFlightCaliCancel();}});
}

void CFG_MotorTest::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("电机测试时,一定要将螺旋桨拆下,防止不可预见的危险。"));
        LB_Info->setObjectName(QString::fromUtf8("warningLabel"));
        LB_Info->setAlignment(Qt::AlignHCenter);
    }

    if(LB_MotorID == nullptr){
        LB_MotorID = new QLabel(QStringLiteral("电机序号"));
        LB_MotorID->setObjectName(QString::fromUtf8("SystemInfoWidgetLabel"));
        LB_MotorID->setAlignment(Qt::AlignRight);
    }
    if(LB_MotorPCT == nullptr){
        LB_MotorPCT = new QLabel(QStringLiteral("电机油门"));
        LB_MotorPCT->setObjectName(QString::fromUtf8("SystemInfoWidgetLabel"));

        LB_MotorPCT->setAlignment(Qt::AlignRight);
    }

    if(LB_MotorTime == nullptr){
        LB_MotorTime = new QLabel(QStringLiteral("运行时间"));
        LB_MotorTime->setObjectName(QString::fromUtf8("SystemInfoWidgetLabel"));
        LB_MotorTime->setAlignment(Qt::AlignRight);
    }

    if(SP_MotorID == nullptr){
        SP_MotorID = new QSpinBox();
        SP_MotorID->setRange(1,motor_count);
        SP_MotorID->setAlignment(Qt::AlignCenter);
        SP_MotorID->setObjectName("widgetSpinBox");
        SP_MotorID->setValue(1);
    }

    if(SP_MotorPCT == nullptr){
        SP_MotorPCT = new QSpinBox();
        SP_MotorPCT->setRange(0,100);
        SP_MotorPCT->setValue(5);
        SP_MotorPCT->setSuffix("%");
        SP_MotorPCT->setObjectName("widgetSpinBox");
        SP_MotorPCT->setAlignment(Qt::AlignCenter);
    }
    if(SP_MotorTime == nullptr){
        SP_MotorTime = new QSpinBox();
        SP_MotorTime->setRange(0,255);
        SP_MotorTime->setValue(2);
        SP_MotorTime->setObjectName("widgetSpinBox");
        SP_MotorTime->setAlignment(Qt::AlignCenter);
    }

    if(PB_Start == nullptr){
        PB_Start = new QPushButton(QStringLiteral("开始测试"));
        PB_Start->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_Start->setToolTip(QStringLiteral("电机测试时,一定要将螺旋桨拆下,防止不可预见的危险。\r\n"));

    }
    if(PB_Stop == nullptr){
        PB_Stop = new QPushButton(QStringLiteral("停止测试"));
        PB_Stop->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_OrderStart == nullptr){
        PB_OrderStart = new QPushButton(QStringLiteral("顺序执行"));
        PB_OrderStart->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);

    for(int i = 0 ;i < 16; i++){
        if(PR_pwm[i] == nullptr){
            PR_pwm[i] = new QProgressBar();
            PR_pwm[i]->setRange(1000,2000);
            PR_pwm[i]->setValue(1100);
            sizePolicy2.setHeightForWidth(PR_pwm[i]->sizePolicy().hasHeightForWidth());
            PR_pwm[i]->setSizePolicy(sizePolicy2);
            PR_pwm[i]->setAlignment(Qt::AlignCenter);
            PR_pwm[i]->setTextVisible(true);
            PR_pwm[i]->setOrientation(Qt::Vertical);
            PR_pwm[i]->setTextDirection(QProgressBar::TopToBottom);
            PR_pwm[i]->setFormat(QCoreApplication::translate("Motor", "%v", nullptr));
            PR_pwm[i]->setObjectName("SystemConfigProgressBar");
        }

        if(LB_pwm[i]== nullptr){
            LB_pwm[i] = new QLabel(QString::number(i+1));
            LB_pwm[i]->setObjectName(QString::fromUtf8("CFGLabelState"));
            LB_pwm[i]->setAlignment(Qt::AlignCenter);
        }

        if(i >= 4){
            PR_pwm[i]->setVisible(false);
            LB_pwm[i]->setVisible(false);
        }
    }

    if(Group_motortest == nullptr){
        Group_motortest = new QGroupBox(QStringLiteral(""));
        Group_motortest->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_motortest->setAlignment(Qt::AlignCenter);
    }
    if(Group_motorval == nullptr){
        Group_motorval = new QGroupBox(QStringLiteral(""));
        Group_motorval->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_motorval->setAlignment(Qt::AlignCenter);
    }

    if(LayoutMotorVal == nullptr){
        LayoutMotorVal = new QGridLayout(Group_motorval);
        LayoutMotorVal->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    if(LayoutMotorTest == nullptr){
        LayoutMotorTest = new QGridLayout(Group_motortest);
        LayoutMotorTest->setObjectName(QString::fromUtf8("widgetLayout"));
    }


    // 常规校准布局
    LayoutMotorTest->addWidget(LB_Info,        0,0,1,20);
    LayoutMotorTest->addWidget(LB_MotorID,     1,9,1,1);
    LayoutMotorTest->addWidget(SP_MotorID,     1,10,1,1);
    LayoutMotorTest->addWidget(LB_MotorPCT,    2,9,1,1);
    LayoutMotorTest->addWidget(SP_MotorPCT,    2,10,1,1);
    LayoutMotorTest->addWidget(LB_MotorTime,   3,9,1,1);
    LayoutMotorTest->addWidget(SP_MotorTime,   3,10,1,1);

    LayoutMotorTest->addWidget(PB_Start,5,7,1,2);
    LayoutMotorTest->addWidget(PB_Stop,5,9,1,2);
    LayoutMotorTest->addWidget(PB_OrderStart,5,11,1,2);
    LayoutMotorTest->setVerticalSpacing(10);
    LayoutMotorTest->setContentsMargins(10,20,10,10);
    LayoutMotorTest->setRowMinimumHeight(0,60);

    for(int i = 0;i < 16;i++){
        LayoutMotorVal->addWidget(PR_pwm[i],0,i,6,1);
        LayoutMotorVal->addWidget(LB_pwm[i],6,i,1,1);
    }

    LayoutMotorVal->setVerticalSpacing(10);
    LayoutMotorVal->setContentsMargins(10,20,10,10);

    widgetLayout->addWidget(Group_motortest,0,0,1,1);
    widgetLayout->addWidget(Group_motorval,0,1,1,1);
    this->widgetLayout->setContentsMargins(0,20,0,0);
    widgetLayout->setSpacing(2);
}

void CFG_MotorTest::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_frameChanged:
        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        case Q_DMMM::DMMM_GCSEvent_Protocol_lost:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link != nullptr){
                motor_count = link->get_frame_output_count();
                SP_MotorID->setRange(1,motor_count);
                for(int i = 0 ;i < 16;i++){
                    if(i < motor_count){
                        PR_pwm[i]->setVisible(true);
                        LB_pwm[i]->setVisible(true);
                    }else{
                        PR_pwm[i]->setVisible(false);
                        LB_pwm[i]->setVisible(false);
                    }
                }

            }
        }break;

    case Q_DMMM::DMMM_GCSEvent_GetMotorVal:
        for(int i = 0;i < 16 ;i++){
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link != nullptr){
                PR_pwm[i]->setValue(link->getTDataPort().tRC_OUT.out[i]);
            }

        }

        default:break;
    }
}
