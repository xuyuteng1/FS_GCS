/**=================================================================**
 * @brief       : FixWing Takeoff Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-08     Jerry.xl     the first version
 **==================================================================**/
#include "P_Cfg_Takeoff.h"
#include "DMMM.h"
#include <qmath.h>

P_CFG_Takeoff::P_CFG_Takeoff(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("起飞配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
//    this->setMinimumSize(400,300);
}

void P_CFG_Takeoff::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&P_CFG_Takeoff::handle_DMMM_event);
//    connect(this, &P_CFG_Takeoff::show,this,&P_CFG_Takeoff::update_value);

    connect(PB_download   , &QPushButton::released,this,[=]{update_value(true);});
    connect(PB_upload   , &QPushButton::released,this,&P_CFG_Takeoff::Upload_Parameters);
}

void P_CFG_Takeoff::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("起飞配置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    if( lb_TKOFF_ACCEL_CNT == nullptr){
        lb_TKOFF_ACCEL_CNT = new QLabel(QStringLiteral("加速度检测计数:"));
        lb_TKOFF_ACCEL_CNT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_ACCEL_CNT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_ACCEL_CNT->setToolTip(QStringLiteral("起飞条件判断时，需要检测到的加计超过设定值次数"));
    }

    if( TKOFF_ACCEL_CNT == nullptr){
        TKOFF_ACCEL_CNT = new UDoubleSpinBox();
        TKOFF_ACCEL_CNT->setRange(0,20);
        TKOFF_ACCEL_CNT->setValue(0);
        TKOFF_ACCEL_CNT->setAlignment(Qt::AlignCenter);
        TKOFF_ACCEL_CNT->setDecimals(0);
        TKOFF_ACCEL_CNT->setToolTip(QStringLiteral("起飞条件判断时，需要检测到的加计超过设定值次数"));
        TKOFF_ACCEL_CNT->setChanged(true);
    }

    if( lb_TKOFF_ALT == nullptr){
        lb_TKOFF_ALT = new QLabel(QStringLiteral("目标高度(m):"));
        lb_TKOFF_ALT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_ALT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_ALT->setToolTip(QStringLiteral("自动起飞的目标高度"));
    }
    if( TKOFF_ALT == nullptr){
        TKOFF_ALT = new UDoubleSpinBox();
        TKOFF_ALT->setRange(0,300);
        TKOFF_ALT->setValue(0);
        TKOFF_ALT->setAlignment(Qt::AlignCenter);
        TKOFF_ALT->setDecimals(0);
        TKOFF_ALT->setToolTip(QStringLiteral("自动起飞的目标高度"));
        TKOFF_ALT->setChanged(true);
    }

    if( lb_TKOFF_DIST == nullptr){
        lb_TKOFF_DIST = new QLabel(QStringLiteral("目标距离(m):"));
        lb_TKOFF_DIST->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_DIST->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_DIST->setToolTip(QStringLiteral("自动起飞模式下悬停点的距离,起飞完成后将以此距离起飞点和起飞时航向的对应距离作为悬停点"));
    }
    if( TKOFF_DIST == nullptr){
        TKOFF_DIST = new UDoubleSpinBox();
        TKOFF_DIST->setRange(0,2000);
        TKOFF_DIST->setValue(0);
        TKOFF_DIST->setAlignment(Qt::AlignCenter);
        TKOFF_DIST->setDecimals(0);
        TKOFF_DIST->setToolTip(QStringLiteral("自动起飞模式下悬停点的距离,起飞完成后将以此距离起飞点和起飞时航向的对应距离作为悬停点"));
        TKOFF_DIST->setChanged(true);
    }

    if( lb_TKOFF_FLAP_PCNT == nullptr){
        lb_TKOFF_FLAP_PCNT = new QLabel(QStringLiteral("襟翼输出(%):"));
        lb_TKOFF_FLAP_PCNT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_FLAP_PCNT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_FLAP_PCNT->setToolTip(QStringLiteral("起飞过程中襟翼输出百分比"));
    }
    if( TKOFF_FLAP_PCNT == nullptr){
        TKOFF_FLAP_PCNT = new UDoubleSpinBox();
        TKOFF_FLAP_PCNT->setRange(0,100);
        TKOFF_FLAP_PCNT->setValue(0);
        TKOFF_FLAP_PCNT->setAlignment(Qt::AlignCenter);
        TKOFF_FLAP_PCNT->setDecimals(0);
        TKOFF_FLAP_PCNT->setToolTip(QStringLiteral("起飞过程中襟翼输出百分比"));
        TKOFF_FLAP_PCNT->setChanged(true);
    }


    if( lb_TKOFF_LVL_ALT == nullptr){
        lb_TKOFF_LVL_ALT = new QLabel(QStringLiteral("爬升高度(m):"));
        lb_TKOFF_LVL_ALT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_LVL_ALT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_LVL_ALT->setToolTip(QStringLiteral("起飞过程中，低于此高度，飞行器将保持滚转为0°"));
    }

    if( TKOFF_LVL_ALT == nullptr){
        TKOFF_LVL_ALT = new UDoubleSpinBox();
        TKOFF_LVL_ALT->setRange(0,200);
        TKOFF_LVL_ALT->setValue(0);
        TKOFF_LVL_ALT->setAlignment(Qt::AlignCenter);
        TKOFF_LVL_ALT->setDecimals(0);
        TKOFF_LVL_ALT->setToolTip(QStringLiteral("起飞过程中，低于此高度，飞行器将保持滚转为0°"));
        TKOFF_LVL_ALT->setChanged(true);
    }

    if( lb_TKOFF_LVL_PITCH == nullptr){
        lb_TKOFF_LVL_PITCH = new QLabel(QStringLiteral("爬升俯仰( ° ):"));
        lb_TKOFF_LVL_PITCH->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_LVL_PITCH->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_LVL_PITCH->setToolTip(QStringLiteral("起飞初始阶段，设定的目标俯仰值"));
    }
    if( TKOFF_LVL_PITCH == nullptr){
        TKOFF_LVL_PITCH = new UDoubleSpinBox();
        TKOFF_LVL_PITCH->setRange(0,45);
        TKOFF_LVL_PITCH->setValue(0);
        TKOFF_LVL_PITCH->setAlignment(Qt::AlignCenter);
        TKOFF_LVL_PITCH->setDecimals(0);
        TKOFF_LVL_PITCH->setToolTip(QStringLiteral("起飞初始阶段，设定的目标俯仰值"));
        TKOFF_LVL_PITCH->setChanged(true);
    }

    if( lb_TKOFF_PLIM_SEC == nullptr){
        lb_TKOFF_PLIM_SEC = new QLabel(QStringLiteral("俯仰预降时间(s):"));
        lb_TKOFF_PLIM_SEC->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_PLIM_SEC->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_PLIM_SEC->setToolTip(QStringLiteral("该参数在自动起飞到达目标高度前几秒降低了最小俯仰限制。"));
    }
    if( TKOFF_PLIM_SEC == nullptr){
        TKOFF_PLIM_SEC = new UDoubleSpinBox();
        TKOFF_PLIM_SEC->setRange(0,15);
        TKOFF_PLIM_SEC->setValue(0);
        TKOFF_PLIM_SEC->setAlignment(Qt::AlignCenter);
        TKOFF_PLIM_SEC->setDecimals(1);
        TKOFF_PLIM_SEC->setToolTip(QStringLiteral("该参数在自动起飞到达目标高度前几秒降低了最小俯仰限制。"));
        TKOFF_PLIM_SEC->setChanged(true);
    }



    if( lb_TKOFF_TDRAG_SPD1 == nullptr){
        lb_TKOFF_TDRAG_SPD1 = new QLabel(QStringLiteral("速度阈值1(滑跑)(m/s):"));
        lb_TKOFF_TDRAG_SPD1->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_TDRAG_SPD1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_TDRAG_SPD1->setToolTip(QStringLiteral("速度低于此阈值,升降舵面输出为固定值。"));
    }
    if( TKOFF_TDRAG_SPD1 == nullptr){
        TKOFF_TDRAG_SPD1 = new UDoubleSpinBox();
        TKOFF_TDRAG_SPD1->setRange(0,50);
        TKOFF_TDRAG_SPD1->setValue(0);
        TKOFF_TDRAG_SPD1->setAlignment(Qt::AlignCenter);
        TKOFF_TDRAG_SPD1->setDecimals(1);
        TKOFF_TDRAG_SPD1->setToolTip(QStringLiteral("速度低于此阈值,升降舵面输出为固定值°"));
        TKOFF_TDRAG_SPD1->setChanged(true);
    }
    if( lb_TKOFF_ROTATE_SPD == nullptr){
        lb_TKOFF_ROTATE_SPD = new QLabel(QStringLiteral("速度阈值2(离地)(m/s):"));
        lb_TKOFF_ROTATE_SPD->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_ROTATE_SPD->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_ROTATE_SPD->setToolTip(QStringLiteral("速度低于此阈值,目标俯仰将保持5°,用于离地。"
                                                       "\r\n！！！筒射、弹射、手抛等起飞时此值需设置为0"));
    }
    if( TKOFF_ROTATE_SPD == nullptr){
        TKOFF_ROTATE_SPD = new UDoubleSpinBox();
        TKOFF_ROTATE_SPD->setRange(0,100);
        TKOFF_ROTATE_SPD->setValue(0);
        TKOFF_ROTATE_SPD->setAlignment(Qt::AlignCenter);
        TKOFF_ROTATE_SPD->setDecimals(1);
        TKOFF_ROTATE_SPD->setToolTip(QStringLiteral("速度低于此阈值,目标俯仰将保持5°,用于离地。"
                                                    "\r\n！！！筒射、弹射、手抛等起飞时此值需设置为0"));
        TKOFF_ROTATE_SPD->setChanged(true);
    }

    if( lb_TKOFF_TDRAG_ELEV == nullptr){
        lb_TKOFF_TDRAG_ELEV = new QLabel(QStringLiteral("升降舵固定输出(%):"));
        lb_TKOFF_TDRAG_ELEV->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_TDRAG_ELEV->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_TDRAG_ELEV->setToolTip(QStringLiteral("低于速度阈值1，升降舵输出值。"));
    }
    if( TKOFF_TDRAG_ELEV == nullptr){
        TKOFF_TDRAG_ELEV = new UDoubleSpinBox();
        TKOFF_TDRAG_ELEV->setRange(-100,100);
        TKOFF_TDRAG_ELEV->setValue(0);
        TKOFF_TDRAG_ELEV->setAlignment(Qt::AlignCenter);
        TKOFF_TDRAG_ELEV->setDecimals(0);
        TKOFF_TDRAG_ELEV->setToolTip(QStringLiteral("低于速度阈值1，升降舵输出值。"));
        TKOFF_TDRAG_ELEV->setChanged(true);
    }


    if( lb_TKOFF_THR_DELAY == nullptr){
        lb_TKOFF_THR_DELAY = new QLabel(QStringLiteral("油门输出延时(s):"));
        lb_TKOFF_THR_DELAY->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_THR_DELAY->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_THR_DELAY->setToolTip(QStringLiteral("检测到起飞条件后的油门输出延时"));
    }
    if( TKOFF_THR_DELAY == nullptr){
        TKOFF_THR_DELAY = new UDoubleSpinBox();
        TKOFF_THR_DELAY->setRange(0,12.7);
        TKOFF_THR_DELAY->setValue(0);
        TKOFF_THR_DELAY->setAlignment(Qt::AlignCenter);
        TKOFF_THR_DELAY->setDecimals(1);
        TKOFF_THR_DELAY->setToolTip(QStringLiteral("检测到起飞条件后的油门输出延时"));
        TKOFF_THR_DELAY->setChanged(true);
    }


    if( lb_TKOFF_THR_MAX == nullptr){
        lb_TKOFF_THR_MAX = new QLabel(QStringLiteral("最大油门(%):"));
        lb_TKOFF_THR_MAX->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_THR_MAX->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_THR_MAX->setToolTip(QStringLiteral("起飞过程中的最大油门,如果为0，则使用系统设定的最大油门。"));
    }
    if( TKOFF_THR_MAX == nullptr){
        TKOFF_THR_MAX = new UDoubleSpinBox();
        TKOFF_THR_MAX->setRange(0,100);
        TKOFF_THR_MAX->setValue(0);
        TKOFF_THR_MAX->setAlignment(Qt::AlignCenter);
        TKOFF_THR_MAX->setDecimals(0);
        TKOFF_THR_MAX->setToolTip(QStringLiteral("起飞过程中的最大油门,如果为0，则使用系统设定的最大油门。"));
        TKOFF_THR_MAX->setChanged(true);
    }

    if( lb_TKOFF_THR_MINACC == nullptr){
        lb_TKOFF_THR_MINACC = new QLabel(QStringLiteral("加速度(m/ss):"));
        lb_TKOFF_THR_MINACC->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_THR_MINACC->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_THR_MINACC->setToolTip(QStringLiteral("在自动起飞中启用地面速度检查之前，检测的最小前向加速度"));
    }
    if( TKOFF_THR_MINACC == nullptr){
        TKOFF_THR_MINACC = new UDoubleSpinBox();
        TKOFF_THR_MINACC->setRange(0,90);
        TKOFF_THR_MINACC->setValue(0);
        TKOFF_THR_MINACC->setAlignment(Qt::AlignCenter);
        TKOFF_THR_MINACC->setDecimals(1);
        TKOFF_THR_MINACC->setToolTip(QStringLiteral("在自动起飞中启用地面速度检查之前，检测的最小前向加速度"));
        TKOFF_THR_MINACC->setChanged(true);
    }

    if( lb_TKOFF_THR_MINSPD == nullptr){
        lb_TKOFF_THR_MINSPD = new QLabel(QStringLiteral("速度(m/s):"));
        lb_TKOFF_THR_MINSPD->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_THR_MINSPD->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_THR_MINSPD->setToolTip(QStringLiteral("起飞检测的速度条件"));
    }
    if( TKOFF_THR_MINSPD == nullptr){
        TKOFF_THR_MINSPD = new UDoubleSpinBox();
        TKOFF_THR_MINSPD->setRange(0,45);
        TKOFF_THR_MINSPD->setValue(0);
        TKOFF_THR_MINSPD->setAlignment(Qt::AlignCenter);
        TKOFF_THR_MINSPD->setDecimals(1);
        TKOFF_THR_MINSPD->setToolTip(QStringLiteral("起飞检测的速度条件"));
        TKOFF_THR_MINSPD->setChanged(true);
    }

    if( lb_TKOFF_THR_SLEW == nullptr){
        lb_TKOFF_THR_SLEW = new QLabel(QStringLiteral("油门变化率(%/s):"));
        lb_TKOFF_THR_SLEW->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_THR_SLEW->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_THR_SLEW->setToolTip(QStringLiteral("起飞过程油门输出的变化速度"));
    }
    if( TKOFF_THR_SLEW == nullptr){
        TKOFF_THR_SLEW = new UDoubleSpinBox();
        TKOFF_THR_SLEW->setRange(-1,127);
        TKOFF_THR_SLEW->setValue(0);
        TKOFF_THR_SLEW->setAlignment(Qt::AlignCenter);
        TKOFF_THR_SLEW->setDecimals(0);
        TKOFF_THR_SLEW->setToolTip(QStringLiteral("起飞过程油门输出的变化速度"));
        TKOFF_THR_SLEW->setChanged(true);
    }

    if( lb_TKOFF_TIMEOUT == nullptr){
        lb_TKOFF_TIMEOUT = new QLabel(QStringLiteral("起飞超时时间(s):"));
        lb_TKOFF_TIMEOUT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TKOFF_TIMEOUT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TKOFF_TIMEOUT->setToolTip(QStringLiteral("开始起飞后，超过此时间仍未达到起飞判断条件，则中止起飞"));
    }
    if( TKOFF_TIMEOUT == nullptr){
        TKOFF_TIMEOUT = new UDoubleSpinBox();
        TKOFF_TIMEOUT->setRange(0,20);
        TKOFF_TIMEOUT->setValue(0);
        TKOFF_TIMEOUT->setAlignment(Qt::AlignCenter);
        TKOFF_TIMEOUT->setDecimals(1);
        TKOFF_TIMEOUT->setToolTip(QStringLiteral("开始起飞后，超过此时间仍未达到起飞判断条件，则中止起飞"));
        TKOFF_TIMEOUT->setChanged(true);
    }

    if( lb_GROUND_STEER_ALT == nullptr){
        lb_GROUND_STEER_ALT = new QLabel(QStringLiteral("转向轮控制高度(m):"));
        lb_GROUND_STEER_ALT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_GROUND_STEER_ALT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_GROUND_STEER_ALT->setToolTip(QStringLiteral("跑道起飞时低于此高度，航向由转向轮控制"));
    }
    if( GROUND_STEER_ALT == nullptr){
        GROUND_STEER_ALT = new UDoubleSpinBox();
        GROUND_STEER_ALT->setRange(-100,100);
        GROUND_STEER_ALT->setValue(0);
        GROUND_STEER_ALT->setAlignment(Qt::AlignCenter);
        GROUND_STEER_ALT->setSingleStep(0.1);
        GROUND_STEER_ALT->setDecimals(1);
        GROUND_STEER_ALT->setToolTip(QStringLiteral("跑道起飞时低于此高度，航向由转向轮控制"));
        GROUND_STEER_ALT->setChanged(true);
    }

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
        widgetLayout_pb->addStretch(5);
        widgetLayout_pb->addWidget(PB_download,1);
        widgetLayout_pb->addWidget(PB_upload,1);
        widgetLayout_pb->addStretch(5);
    }

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    /* Trigger Condition  parameters*/
    if( Group_Trigger == nullptr){
        Group_Trigger = new QGroupBox(QStringLiteral("起飞条件"));
        Group_Trigger->setObjectName("widgetGroupBox");
        Group_Trigger->setAlignment(Qt::AlignCenter);
    }

    if( Layout_Trigger == nullptr){
        Layout_Trigger = new QGridLayout(Group_Trigger);
        Layout_Trigger->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    /* Trigger Condition  label & Udoublespinbox*/
    Layout_Trigger->addWidget(lb_TKOFF_ACCEL_CNT,      2, 0, 1, 1);
    Layout_Trigger->addWidget(lb_TKOFF_THR_MINACC,     1, 0, 1, 1);
    Layout_Trigger->addWidget(lb_TKOFF_THR_MINSPD,     0, 0, 1, 1);

    Layout_Trigger->addWidget(TKOFF_ACCEL_CNT,         2, 1, 1, 1);
    Layout_Trigger->addWidget(TKOFF_THR_MINACC,        1, 1, 1, 1);
    Layout_Trigger->addWidget(TKOFF_THR_MINSPD,        0, 1, 1, 1);

    /* takeoff target parameters setting*/
    if( Group_Target == nullptr){
        Group_Target = new QGroupBox(QStringLiteral("目标设定"));
        Group_Target->setObjectName("widgetGroupBox");
        Group_Target->setAlignment(Qt::AlignCenter);
    }

    if( Layout_Target == nullptr){
        Layout_Target = new QGridLayout(Group_Target);
        Layout_Target->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    /* takeoff target parameters setting  label & Udoublespinbox*/
    Layout_Target->addWidget(lb_TKOFF_LVL_ALT,      1, 0, 1, 1);
    Layout_Target->addWidget(lb_TKOFF_LVL_PITCH,    0, 0, 1, 1);
    Layout_Target->addWidget(lb_TKOFF_ALT,          2, 0, 1, 1);
    Layout_Target->addWidget(lb_TKOFF_DIST,         3, 0, 1, 1);

    Layout_Target->addWidget(TKOFF_LVL_ALT,         1, 1, 1, 1);
    Layout_Target->addWidget(TKOFF_LVL_PITCH,       0, 1, 1, 1);
    Layout_Target->addWidget(TKOFF_ALT,             2, 1, 1, 1);
    Layout_Target->addWidget(TKOFF_DIST,            3, 1, 1, 1);

    /* runway takeoff parameters setting*/
    if( Group_runway == nullptr){
        Group_runway = new QGroupBox(QStringLiteral("速度阈值"));
        Group_runway->setObjectName("widgetGroupBox");
        Group_runway->setAlignment(Qt::AlignCenter);
    }

    if( Layout_runway == nullptr){
        Layout_runway = new QGridLayout(Group_runway);
        Layout_runway->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    /* runway takeoff parameters setting  label & Udoublespinbox*/
    Layout_runway->addWidget(lb_TKOFF_TDRAG_SPD1,      0, 0, 1, 1);
    Layout_runway->addWidget(lb_TKOFF_ROTATE_SPD,      2, 0, 1, 1);

    Layout_runway->addWidget(TKOFF_TDRAG_SPD1,        0, 1, 1, 1);
    Layout_runway->addWidget(TKOFF_ROTATE_SPD,        2, 1, 1, 1);

    /* runway takeoff parameters setting*/
    if( Group_general == nullptr){
        Group_general = new QGroupBox(QStringLiteral("通用参数"));
        Group_general->setObjectName("widgetGroupBox");
        Group_general->setAlignment(Qt::AlignCenter);
    }

    if( Layout_general == nullptr){
        Layout_general = new QGridLayout(Group_general);
        Layout_general->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    Layout_general->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 0, 0, 4, 1);
    Layout_general->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 0, 3, 4, 1);
    Layout_general->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 0, 6, 4, 1);

    Layout_general->addWidget(lb_TKOFF_PLIM_SEC,       0, 1, 1, 1);
    Layout_general->addWidget(lb_GROUND_STEER_ALT,     1, 1, 1, 1);
    Layout_general->addWidget(lb_TKOFF_FLAP_PCNT,      2, 1, 1, 1);
    Layout_general->addWidget(lb_TKOFF_TDRAG_ELEV,     3, 1, 1, 1);

    Layout_general->addWidget(lb_TKOFF_THR_MAX,        0, 4, 1, 1);
    Layout_general->addWidget(lb_TKOFF_THR_SLEW,       1, 4, 1, 1);
    Layout_general->addWidget(lb_TKOFF_THR_DELAY,      2, 4, 1, 1);
    Layout_general->addWidget(lb_TKOFF_TIMEOUT,        3, 4, 1, 1);


    Layout_general->addWidget(TKOFF_PLIM_SEC,       0, 2, 1, 1);
    Layout_general->addWidget(GROUND_STEER_ALT,     1, 2, 1, 1);
    Layout_general->addWidget(TKOFF_FLAP_PCNT,      2, 2, 1, 1);
    Layout_general->addWidget(TKOFF_TDRAG_ELEV,     3, 2, 1, 1);

    Layout_general->addWidget(TKOFF_THR_MAX,        0, 5, 1, 1);
    Layout_general->addWidget(TKOFF_THR_SLEW,       1, 5, 1, 1);
    Layout_general->addWidget(TKOFF_THR_DELAY,      2, 5, 1, 1);
    Layout_general->addWidget(TKOFF_TIMEOUT,        3, 5, 1, 1);


    /* widget title label */
    widgetLayout->addWidget(titleLabel,      0, 0, 1, 7);
    /* SpacerItem for automatic spacing adjustment */
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 1);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 2, 1, 1);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 4, 1, 1);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 6, 1, 1);
    /* Trigger Condition  group */
    widgetLayout->addWidget(Group_Trigger,1,1,1,1);
    /* takeoff target parameters setting  group */
    widgetLayout->addWidget(Group_Target,1,3,1,1);
    /* runway takeoff parameters setting  group */
    widgetLayout->addWidget(Group_runway,1,5,1,1);
    /* general parameters setting  group */
    widgetLayout->addWidget(Group_general,2,1,1,5);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 3, 0, 1, 1);
    widgetLayout->addLayout(widgetLayout_pb , 4, 0, 1, 7);
    this->setLayout(widgetLayout);
}

void P_CFG_Takeoff::showEvent(QShowEvent *event)
{
    update_value();
    QWidget::showEvent(event);
}

void P_CFG_Takeoff::handle_DMMM_event(int ev, int linkid)
{
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_GetCommonParameter:
    {
        update_value();
    }break;
    case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
    case Q_DMMM::DMMM_GCSEvent_NewVehicleType:
    {
        update_value(true);
    }break;
        default:break;
    }
}

void P_CFG_Takeoff::update_value(bool getfromflight)
{
    qDebug()<<"update_value"<<getfromflight;
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        float val = 0;
        /* Init Postion */
        // Alt;
        if(link->ParamGetValue_ByName("TKOFF_ACCEL_CNT",val,getfromflight)){
            this->TKOFF_ACCEL_CNT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_ALT",val,getfromflight)){
            this->TKOFF_ALT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_DIST",val,getfromflight)){
            this->TKOFF_DIST->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_FLAP_PCNT",val,getfromflight)){
            this->TKOFF_FLAP_PCNT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_LVL_ALT",val,getfromflight)){
            this->TKOFF_LVL_ALT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_LVL_PITCH",val,getfromflight)){
            this->TKOFF_LVL_PITCH->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_PLIM_SEC",val,getfromflight)){
            this->TKOFF_PLIM_SEC->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_ROTATE_SPD",val,getfromflight)){
            this->TKOFF_ROTATE_SPD->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_TDRAG_ELEV",val,getfromflight)){
            this->TKOFF_TDRAG_ELEV->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_TDRAG_SPD1",val,getfromflight)){
            this->TKOFF_TDRAG_SPD1->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_THR_DELAY",val,getfromflight)){
            this->TKOFF_THR_DELAY->SetNewValue(val*0.1);
        }
        if(link->ParamGetValue_ByName("TKOFF_THR_MAX",val,getfromflight)){
            this->TKOFF_THR_MAX->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_THR_MINACC",val,getfromflight)){
            this->TKOFF_THR_MINACC->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_THR_MINSPD",val,getfromflight)){
            this->TKOFF_THR_MINSPD->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_THR_SLEW",val,getfromflight)){
            this->TKOFF_THR_SLEW->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TKOFF_TIMEOUT",val,getfromflight)){
            this->TKOFF_TIMEOUT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("GROUND_STEER_ALT",val,getfromflight)){
            this->GROUND_STEER_ALT->SetNewValue(val);
        }
    }
}

void P_CFG_Takeoff::Upload_Parameters()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr)return;
    /* Init Postion */
    if(this->TKOFF_ACCEL_CNT->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_ACCEL_CNT",this->TKOFF_ACCEL_CNT->value());
    }
    if(this->TKOFF_ALT->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_ALT",this->TKOFF_ALT->value());
    }
    if(this->TKOFF_DIST->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_DIST",this->TKOFF_DIST->value());
    }
    if(this->TKOFF_FLAP_PCNT->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_FLAP_PCNT",this->TKOFF_FLAP_PCNT->value());
    }
    if(this->TKOFF_LVL_ALT->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_LVL_ALT",this->TKOFF_LVL_ALT->value());
    }
    if(this->TKOFF_LVL_PITCH->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_LVL_PITCH",this->TKOFF_LVL_PITCH->value());
    }
    if(this->TKOFF_PLIM_SEC->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_PLIM_SEC",this->TKOFF_PLIM_SEC->value());
    }
    if(this->TKOFF_ROTATE_SPD->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_ROTATE_SPD",this->TKOFF_ROTATE_SPD->value());
    }
    if(this->TKOFF_TDRAG_ELEV->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_TDRAG_ELEV",this->TKOFF_TDRAG_ELEV->value());
    }
    if(this->TKOFF_TDRAG_SPD1->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_TDRAG_SPD1",this->TKOFF_TDRAG_SPD1->value());
    }
    if(this->TKOFF_THR_DELAY->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_THR_DELAY",this->TKOFF_THR_DELAY->value()*10);
    }
    if(this->TKOFF_THR_MAX->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_THR_MAX",this->TKOFF_THR_MAX->value());
    }
    if(this->TKOFF_THR_MINACC->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_THR_MINACC",this->TKOFF_THR_MINACC->value());
    }
    if(this->TKOFF_THR_MINSPD->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_THR_MINSPD",this->TKOFF_THR_MINSPD->value());
    }
    if(this->TKOFF_THR_SLEW->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_THR_SLEW",this->TKOFF_THR_SLEW->value());
    }
    if(this->TKOFF_TIMEOUT->IsChanged()){
        link->ParamSetToFlight_ByName("TKOFF_TIMEOUT",this->TKOFF_TIMEOUT->value());
    }
    if(this->GROUND_STEER_ALT->IsChanged()){
        link->ParamSetToFlight_ByName("GROUND_STEER_ALT",this->GROUND_STEER_ALT->value());
    }

}
