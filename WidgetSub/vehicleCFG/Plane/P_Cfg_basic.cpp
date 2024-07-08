/**=================================================================**
 * @brief       : FixWing Basic Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-10     Jerry.xl     the first version
 **==================================================================**/
#include "P_Cfg_basic.h"
#include "DMMM.h"
#include <qmath.h>

P_CFG_Basic::P_CFG_Basic(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("基础配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void P_CFG_Basic::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&P_CFG_Basic::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{update_value(true);});
    connect(PB_upload   , &QPushButton::released,this,&P_CFG_Basic::Upload_Parameters);
}

void P_CFG_Basic::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("基础配置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    Init_ParametersBasic();

    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));

    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
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

    /* widget title label */
    widgetLayout->addWidget(titleLabel,      0, 0, 1, 3);
    /* SpacerItem for automatic spacing adjustment */
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 1);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 2, 1, 1);
    /* parachute parameters group */
    widgetLayout->addWidget(Group_basic,1,1,1,1);

    /* general parameters setting  group */
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 0, 1, 1);
    widgetLayout->addLayout(widgetLayout_pb , 5, 0, 1, 3);
    this->setLayout(widgetLayout);
}

void P_CFG_Basic::Init_ParametersBasic()
{
    /* rc&throttle failsafe parameters group*/
    if( Group_basic == nullptr){
        Group_basic = new QGroupBox(QStringLiteral("基础参数"));
        Group_basic->setObjectName("widgetGroupBox");
        Group_basic->setAlignment(Qt::AlignCenter);
    }

    if( Layout_basic == nullptr){
        Layout_basic = new QGridLayout(Group_basic);
        Layout_basic->setObjectName(QString::fromUtf8("widgetLayout"));
    }


    if( CRASH_DETECT == nullptr){
        CRASH_DETECT = new UCheckBox();
        CRASH_DETECT->setText(QStringLiteral("开启坠毁检测"));
        CRASH_DETECT->setToolTip(QStringLiteral("坠毁检测使能开关"));
    }
    if( STALL_PREVENTION == nullptr){
        STALL_PREVENTION = new UCheckBox();
        STALL_PREVENTION->setText(QStringLiteral("开启失速保护"));
        STALL_PREVENTION->setToolTip(QStringLiteral("失速保护使能开关"));
    }

    if( lb_THR_MIN == nullptr){
        lb_THR_MIN = new QLabel(QStringLiteral("最小油门(%):"));
        lb_THR_MIN->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_THR_MIN->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_THR_MIN->setToolTip(QStringLiteral("正常飞行中最小油门值"));
    }
    if( THR_MIN == nullptr){
        THR_MIN = new UDoubleSpinBox();
        THR_MIN->setRange(-100,100);
        THR_MIN->setValue(0);
        THR_MIN->setAlignment(Qt::AlignCenter);
        THR_MIN->setSingleStep(1);
        THR_MIN->setDecimals(0);
        THR_MIN->setToolTip(QStringLiteral("正常飞行中最小油门值"));
    }

    if( lb_THR_MAX == nullptr){
        lb_THR_MAX = new QLabel(QStringLiteral("最大油门(%):"));
        lb_THR_MAX->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_THR_MAX->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_THR_MAX->setToolTip(QStringLiteral("正常飞行中最大油门值,负值代表反推油门"));
    }

    if( THR_MAX == nullptr){
        THR_MAX = new UDoubleSpinBox();
        THR_MAX->setRange(0,100);
        THR_MAX->setValue(0);
        THR_MAX->setAlignment(Qt::AlignCenter);
        THR_MAX->setSingleStep(1);
        THR_MAX->setDecimals(0);
        THR_MAX->setToolTip(QStringLiteral("正常飞行中最大油门值"));
    }
    if( lb_TRIM_THROTTLE == nullptr){
        lb_TRIM_THROTTLE = new QLabel(QStringLiteral("巡航油门(%):"));
        lb_TRIM_THROTTLE->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_TRIM_THROTTLE->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_TRIM_THROTTLE->setToolTip(QStringLiteral("保持正常巡航空速的巡航油门值"));
    }

    if( TRIM_THROTTLE == nullptr){
        TRIM_THROTTLE = new UDoubleSpinBox();
        TRIM_THROTTLE->setRange(0,100);
        TRIM_THROTTLE->setValue(0);
        TRIM_THROTTLE->setAlignment(Qt::AlignCenter);
        TRIM_THROTTLE->setSingleStep(1);
        TRIM_THROTTLE->setDecimals(0);
        TRIM_THROTTLE->setToolTip(QStringLiteral("保持正常巡航空速的巡航油门值"));
    }

    if( lb_THR_SLEWRATE == nullptr){
        lb_THR_SLEWRATE = new QLabel(QStringLiteral("油门变化率(%/s):"));
        lb_THR_SLEWRATE->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_THR_SLEWRATE->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_THR_SLEWRATE->setToolTip(QStringLiteral("油门变化率"));
    }

    if( THR_SLEWRATE == nullptr){
        THR_SLEWRATE = new UDoubleSpinBox();
        THR_SLEWRATE->setRange(0,127);
        THR_SLEWRATE->setValue(0);
        THR_SLEWRATE->setAlignment(Qt::AlignCenter);
        THR_SLEWRATE->setSingleStep(1);
        THR_SLEWRATE->setDecimals(0);
        THR_SLEWRATE->setToolTip(QStringLiteral("油门变化率"));
    }

    if( lb_ARSPD_FBW_MIN == nullptr){
        lb_ARSPD_FBW_MIN = new QLabel(QStringLiteral("最小空速(m/s):"));
        lb_ARSPD_FBW_MIN->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_ARSPD_FBW_MIN->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_ARSPD_FBW_MIN->setToolTip(QStringLiteral("最小空速"));
    }

    if( ARSPD_FBW_MIN == nullptr){
        ARSPD_FBW_MIN = new UDoubleSpinBox();
        ARSPD_FBW_MIN->setRange(3,200);
        ARSPD_FBW_MIN->setValue(0);
        ARSPD_FBW_MIN->setAlignment(Qt::AlignCenter);
        ARSPD_FBW_MIN->setSingleStep(1);
        ARSPD_FBW_MIN->setDecimals(0);
        ARSPD_FBW_MIN->setToolTip(QStringLiteral("最小空速"));
    }
    if( lb_ARSPD_FBW_MAX == nullptr){
        lb_ARSPD_FBW_MAX = new QLabel(QStringLiteral("最大空速(m/s):"));
        lb_ARSPD_FBW_MAX->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_ARSPD_FBW_MAX->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_ARSPD_FBW_MAX->setToolTip(QStringLiteral("最大空速"));
    }

    if( ARSPD_FBW_MAX == nullptr){
        ARSPD_FBW_MAX = new UDoubleSpinBox();
        ARSPD_FBW_MAX->setRange(3,200);
        ARSPD_FBW_MAX->setValue(0);
        ARSPD_FBW_MAX->setAlignment(Qt::AlignCenter);
        ARSPD_FBW_MAX->setSingleStep(1);
        ARSPD_FBW_MAX->setDecimals(0);
        ARSPD_FBW_MAX->setToolTip(QStringLiteral("最大空速"));
    }

    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_TRIM_ARSPD_CM, TRIM_ARSPD_CM,
                                 QStringLiteral("目标空速(m/s):"),
                                 QStringLiteral("目标空速"),
                                 3,
                                 200,
                                 1,
                                 1);

    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_SCALING_SPEED, SCALING_SPEED,
                                 QStringLiteral("缩放速度(m/s):"),
                                 QStringLiteral("用于speed scaling计算"),
                                 3,
                                 200,
                                 1,
                                 1);

    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_MIN_GNDSPD_CM, MIN_GNDSPD_CM,
                                 QStringLiteral("最小地速(m/s):"),
                                 QStringLiteral("Minimum ground speed in cm/s when under airspeed control"),
                                 0,
                                 200,
                                 1,
                                 1);

    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_LIM_ROLL_CD, LIM_ROLL_CD,
                                 QStringLiteral("最大滚转角(°):"),
                                 QStringLiteral("姿态控制最大滚转角"),
                                 0,
                                 90,
                                 1,
                                 1);
    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_LIM_PITCH_MAX, LIM_PITCH_MAX,
                                 QStringLiteral("最大俯仰角(°):"),
                                 QStringLiteral("姿态控制最大俯仰角"),
                                 0,
                                 90,
                                 1,
                                 1);
    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_LIM_PITCH_MIN, LIM_PITCH_MIN,
                                 QStringLiteral("最小俯仰角(°):"),
                                 QStringLiteral("姿态控制最小俯仰角"),
                                 -90,
                                 0,
                                 1,
                                 1);

    G_CFG_Template::ParamCFGInit_DoubleSpinBox(lb_WP_RADIUS, WP_RADIUS,
                                 QStringLiteral("航点半径(m):"),
                                 QStringLiteral("航点半径"),
                                 -32767,
                                 32767,
                                 1,
                                 1);
    Layout_basic->addWidget(CRASH_DETECT,           0, 0, 1, 2);
    Layout_basic->addWidget(STALL_PREVENTION,       1, 0, 1, 2);

    Layout_basic->addWidget(lb_THR_MIN                 , 2, 0, 1, 1);
    Layout_basic->addWidget(lb_THR_MAX                 , 3, 0, 1, 1);
    Layout_basic->addWidget(lb_THR_SLEWRATE            , 4, 0, 1, 1);
    Layout_basic->addWidget(lb_TRIM_THROTTLE           , 5, 0, 1, 1);
    Layout_basic->addWidget(lb_ARSPD_FBW_MIN           , 6, 0, 1, 1);
    Layout_basic->addWidget(lb_ARSPD_FBW_MAX           , 7, 0, 1, 1);
    Layout_basic->addWidget(lb_TRIM_ARSPD_CM           , 8, 0, 1, 1);
    Layout_basic->addWidget(lb_SCALING_SPEED           , 9, 0, 1, 1);
    Layout_basic->addWidget(lb_MIN_GNDSPD_CM           ,10, 0, 1, 1);
    Layout_basic->addWidget(lb_LIM_ROLL_CD             ,11, 0, 1, 1);
    Layout_basic->addWidget(lb_LIM_PITCH_MAX           ,12, 0, 1, 1);
    Layout_basic->addWidget(lb_LIM_PITCH_MIN           ,13, 0, 1, 1);
    Layout_basic->addWidget(lb_WP_RADIUS           ,14, 0, 1, 1);

    Layout_basic->addWidget(THR_MIN                 , 2, 1, 1, 1);
    Layout_basic->addWidget(THR_MAX                 , 3, 1, 1, 1);
    Layout_basic->addWidget(THR_SLEWRATE            , 4, 1, 1, 1);
    Layout_basic->addWidget(TRIM_THROTTLE           , 5, 1, 1, 1);
    Layout_basic->addWidget(ARSPD_FBW_MIN           , 6, 1, 1, 1);
    Layout_basic->addWidget(ARSPD_FBW_MAX           , 7, 1, 1, 1);
    Layout_basic->addWidget(TRIM_ARSPD_CM           , 8, 1, 1, 1);
    Layout_basic->addWidget(SCALING_SPEED           , 9, 1, 1, 1);
    Layout_basic->addWidget(MIN_GNDSPD_CM           ,10, 1, 1, 1);
    Layout_basic->addWidget(LIM_ROLL_CD             ,11, 1, 1, 1);
    Layout_basic->addWidget(LIM_PITCH_MAX           ,12, 1, 1, 1);
    Layout_basic->addWidget(LIM_PITCH_MIN           ,13, 1, 1, 1);
    Layout_basic->addWidget(WP_RADIUS           ,14, 1, 1, 1);

}

void P_CFG_Basic::upload_ParametersBasic()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr)return;
    if(this->CRASH_DETECT->IsChanged()){
        link->ParamSetToFlight_ByName("CRASH_DETECT",this->CRASH_DETECT->checkState()?1:0);
    }
    if(this->STALL_PREVENTION->IsChanged()){
        link->ParamSetToFlight_ByName("STALL_PREVENTION",this->STALL_PREVENTION->checkState()?1:0);
    }

    if(this->THR_MIN->IsChanged()){
        link->ParamSetToFlight_ByName("THR_MIN",this->THR_MIN->value());
    }
    if(this->THR_MAX->IsChanged()){
        link->ParamSetToFlight_ByName("THR_MAX",this->THR_MAX->value());
    }
    if(this->THR_SLEWRATE->IsChanged()){
        link->ParamSetToFlight_ByName("THR_SLEWRATE",this->THR_SLEWRATE->value());
    }
    if(this->TRIM_THROTTLE->IsChanged()){
        link->ParamSetToFlight_ByName("TRIM_THROTTLE",this->TRIM_THROTTLE->value());
    }
    if(this->ARSPD_FBW_MIN->IsChanged()){
        link->ParamSetToFlight_ByName("ARSPD_FBW_MIN",this->ARSPD_FBW_MIN->value());
    }
    if(this->ARSPD_FBW_MAX->IsChanged()){
        link->ParamSetToFlight_ByName("ARSPD_FBW_MAX",this->ARSPD_FBW_MAX->value());
    }
    if(this->TRIM_ARSPD_CM->IsChanged()){
        link->ParamSetToFlight_ByName("TRIM_ARSPD_CM",this->TRIM_ARSPD_CM->value()*100);
    }
    if(this->SCALING_SPEED->IsChanged()){
        link->ParamSetToFlight_ByName("SCALING_SPEED",this->SCALING_SPEED->value());
    }
    if(this->MIN_GNDSPD_CM->IsChanged()){
        link->ParamSetToFlight_ByName("MIN_GNDSPD_CM",this->MIN_GNDSPD_CM->value()*100);
    }
    if(this->LIM_ROLL_CD->IsChanged()){
        link->ParamSetToFlight_ByName("LIM_ROLL_CD",this->LIM_ROLL_CD->value()*100);
    }
    if(this->LIM_PITCH_MAX->IsChanged()){
        link->ParamSetToFlight_ByName("LIM_PITCH_MAX",this->LIM_PITCH_MAX->value()*100);
    }
    if(this->LIM_PITCH_MIN->IsChanged()){
        link->ParamSetToFlight_ByName("LIM_PITCH_MIN",this->LIM_PITCH_MIN->value()*100);
    }
    if(this->WP_RADIUS->IsChanged()){
        link->ParamSetToFlight_ByName("WP_RADIUS",this->WP_RADIUS->value());
    }
}

void P_CFG_Basic::update_ParametersBasic(bool getfromflight)
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        float val = 0;
        if(link->ParamGetValue_ByName("CRASH_DETECT",val,getfromflight)){
            int state = val;
            this->CRASH_DETECT->setNewChecked(state?true:false);
        }
        if(link->ParamGetValue_ByName("STALL_PREVENTION",val,getfromflight)){
            int state = val;
            this->STALL_PREVENTION->setNewChecked(state?true:false);
        }


        if(link->ParamGetValue_ByName("THR_MIN",val,getfromflight)){
            this->THR_MIN->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("THR_MAX",val,getfromflight)){
            this->THR_MAX->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("THR_SLEWRATE",val,getfromflight)){
            this->THR_SLEWRATE->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TRIM_THROTTLE",val,getfromflight)){
            this->TRIM_THROTTLE->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("ARSPD_FBW_MIN",val,getfromflight)){
            this->ARSPD_FBW_MIN->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("ARSPD_FBW_MAX",val,getfromflight)){
            this->ARSPD_FBW_MAX->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("TRIM_ARSPD_CM",val,getfromflight)){
            this->TRIM_ARSPD_CM->SetNewValue(val*0.01);
        }
        if(link->ParamGetValue_ByName("SCALING_SPEED",val,getfromflight)){
            this->SCALING_SPEED->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("MIN_GNDSPD_CM",val,getfromflight)){
            this->MIN_GNDSPD_CM->SetNewValue(val*0.01);
        }
        if(link->ParamGetValue_ByName("LIM_ROLL_CD",val,getfromflight)){
            this->LIM_ROLL_CD->SetNewValue(val*0.01);
        }
        if(link->ParamGetValue_ByName("LIM_PITCH_MAX",val,getfromflight)){
            this->LIM_PITCH_MAX->SetNewValue(val*0.01);
        }
        if(link->ParamGetValue_ByName("LIM_PITCH_MIN",val,getfromflight)){
            this->LIM_PITCH_MIN->SetNewValue(val*0.01);
        }
        if(link->ParamGetValue_ByName("WP_RADIUS",val,getfromflight)){
            this->WP_RADIUS->SetNewValue(val);
        }

    }
}





void P_CFG_Basic::showEvent(QShowEvent *event)
{
    update_value();
    QWidget::showEvent(event);
}

void P_CFG_Basic::handle_DMMM_event(int ev, int linkid)
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

void P_CFG_Basic::update_value(bool getfromflight)
{
    update_ParametersBasic(getfromflight);
}

void P_CFG_Basic::Upload_Parameters()
{
    upload_ParametersBasic();
}
