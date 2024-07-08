/**=================================================================**
 * @brief       : FixWing Takeoff Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-08     Jerry.xl     the first version
 **==================================================================**/
#include "P_Cfg_Failsafe.h"
#include "DMMM.h"
#include <qmath.h>

P_CFG_Failsafe::P_CFG_Failsafe(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("故障保护配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
//    this->setMinimumSize(400,300);
}

void P_CFG_Failsafe::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&P_CFG_Failsafe::handle_DMMM_event);
//    connect(this, &P_CFG_Failsafe::show,this,&P_CFG_Failsafe::update_value);

    connect(PB_download   , &QPushButton::released,this,[=]{update_value(true);});
    connect(PB_upload   , &QPushButton::released,this,&P_CFG_Failsafe::Upload_Parameters);
}

void P_CFG_Failsafe::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("故障保护"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }



    /* rc&throttle failsafe parameters group*/
    if( Group_rc == nullptr){
        Group_rc = new QGroupBox(QStringLiteral("遥控故障"));
        Group_rc->setObjectName("widgetGroupBox");
        Group_rc->setAlignment(Qt::AlignCenter);
    }

    if( Layout_rc == nullptr){
        Layout_rc = new QGridLayout(Group_rc);
        Layout_rc->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if( lb_THR_FAILSAFE == nullptr){
        lb_THR_FAILSAFE = new QLabel(QStringLiteral("遥控丢失故障:"));
        lb_THR_FAILSAFE->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_THR_FAILSAFE->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_THR_FAILSAFE->setToolTip(QStringLiteral("油门或RC故障保护使能"));
    }
    if( THR_FAILSAFE == nullptr){
        THR_FAILSAFE = new UComboBox();
        THR_FAILSAFE->setEditable(false);
        THR_FAILSAFE->addItem(QStringLiteral("关闭保护"),0);
        THR_FAILSAFE->addItem(QStringLiteral("开启保护"),1);
//        THR_FAILSAFE->addItem(QStringLiteral("仅检测"),2);
        THR_FAILSAFE->setToolTip(QStringLiteral("油门或RC故障保护使能"));
        THR_FAILSAFE->setToolTipDuration(60000);
    }
    if( lb_THR_FS_VALUE == nullptr){
        lb_THR_FS_VALUE = new QLabel(QStringLiteral("油门故障值:"));
        lb_THR_FS_VALUE->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_THR_FS_VALUE->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_THR_FS_VALUE->setToolTip(QStringLiteral("RC油门低于此值将触发保护,用于PPM等协议,S.Bus则通过协议中状态标志判断"));
    }
    if( THR_FS_VALUE == nullptr){
        THR_FS_VALUE = new UDoubleSpinBox();
        THR_FS_VALUE->setRange(600,1200);
        THR_FS_VALUE->setValue(0);
        THR_FS_VALUE->setAlignment(Qt::AlignCenter);
        THR_FS_VALUE->setSingleStep(1);
        THR_FS_VALUE->setDecimals(0);
        THR_FS_VALUE->setToolTip(QStringLiteral("RC油门低于此值将触发保护,用于PPM等协议,S.Bus则通过协议中状态标志判断"));
    }

    if( lb_THR_FAILSAFE == nullptr){
        lb_THR_FAILSAFE = new QLabel(QStringLiteral("遥控丢失检测:"));
        lb_THR_FAILSAFE->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_THR_FAILSAFE->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_THR_FAILSAFE->setToolTip(QStringLiteral("油门或RC故障保护使能"));
    }
    if( THR_FAILSAFE == nullptr){
        THR_FAILSAFE = new UComboBox();
        THR_FAILSAFE->setEditable(false);
        THR_FAILSAFE->addItem(QStringLiteral("关闭"),0);
        THR_FAILSAFE->addItem(QStringLiteral("关闭(仅提示)"),2);
        THR_FAILSAFE->addItem(QStringLiteral("开启"),1);
        THR_FAILSAFE->setToolTip(QStringLiteral("RC数据健康状态检测"));
        THR_FAILSAFE->setToolTipDuration(60000);
    }
    if( lb_FS_GCS_ENABL == nullptr){
        lb_FS_GCS_ENABL = new QLabel(QStringLiteral("通信丢失检测:"));
        lb_FS_GCS_ENABL->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_FS_GCS_ENABL->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_FS_GCS_ENABL->setToolTip(QStringLiteral("地面站与飞控通信连接状态检测"));
    }
    if( FS_GCS_ENABL == nullptr){
        FS_GCS_ENABL = new UComboBox();
        FS_GCS_ENABL->setEditable(false);
        FS_GCS_ENABL->addItem(QStringLiteral("关闭"),0);
        FS_GCS_ENABL->addItem(QStringLiteral("开启"),1);
        FS_GCS_ENABL->setToolTip(QStringLiteral("地面站与飞控通信连接状态检测"));
        FS_GCS_ENABL->setToolTipDuration(60000);
    }

    /* rc&throttle failsafe  label & Udoublespinbox*/
    Layout_rc->addWidget(lb_THR_FAILSAFE,      0, 0, 1, 1);
    Layout_rc->addWidget(THR_FAILSAFE,         0, 1, 1, 1);
    Layout_rc->addWidget(lb_THR_FS_VALUE,      0, 2, 1, 1);
    Layout_rc->addWidget(THR_FS_VALUE,         0, 3, 1, 1);
    Layout_rc->addWidget(lb_FS_GCS_ENABL,      1, 0, 1, 1);
    Layout_rc->addWidget(FS_GCS_ENABL,         1, 1, 1, 1);

    /* short and long failsafe Triger Action parameters setting */
    if( Group_action == nullptr){
        Group_action = new QGroupBox(QStringLiteral("故障处理"));
        Group_action->setObjectName("widgetGroupBox");
        Group_action->setAlignment(Qt::AlignCenter);
    }

    if( Layout_action == nullptr){
        Layout_action = new QGridLayout(Group_action);
        Layout_action->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if( lb_FS_SHORT_ACTN == nullptr){
        lb_FS_SHORT_ACTN = new QLabel(QStringLiteral("短故障处理:"));
        lb_FS_SHORT_ACTN->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_FS_SHORT_ACTN->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_FS_SHORT_ACTN->setToolTip(QStringLiteral("RC/GCS通信故障均会触发短时故障。"));
    }
    if( FS_SHORT_ACTN == nullptr){
        FS_SHORT_ACTN = new UComboBox();
        FS_SHORT_ACTN->setEditable(false);
        FS_SHORT_ACTN->addItem(QStringLiteral("无动作"),3);
        FS_SHORT_ACTN->addItem(QStringLiteral("原地绕圈"),1);
        FS_SHORT_ACTN->addItem(QStringLiteral("原地绕圈(仅辅助模式)"),0);
        FS_SHORT_ACTN->addItem(QStringLiteral("辅助模式(AS)"),4);
        FS_SHORT_ACTN->addItem(QStringLiteral("自稳模式(油门为零)"),2);
        FS_SHORT_ACTN->setToolTip(QStringLiteral("RC/GCS通信故障均会触发短时故障。"));
        FS_SHORT_ACTN->setToolTipDuration(60000);
    }
    if( lb_FS_SHORT_TIMEOUT == nullptr){
        lb_FS_SHORT_TIMEOUT = new QLabel(QStringLiteral("超时时间:"));
        lb_FS_SHORT_TIMEOUT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_FS_SHORT_TIMEOUT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_FS_SHORT_TIMEOUT->setToolTip(QStringLiteral("///"));
    }
    if( FS_SHORT_TIMEOUT == nullptr){
        FS_SHORT_TIMEOUT = new UDoubleSpinBox();
        FS_SHORT_TIMEOUT->setRange(0.5,100);
        FS_SHORT_TIMEOUT->setValue(0);
        FS_SHORT_TIMEOUT->setAlignment(Qt::AlignCenter);
        FS_SHORT_TIMEOUT->setSingleStep(0.5);
        FS_SHORT_TIMEOUT->setDecimals(1);
        FS_SHORT_TIMEOUT->setToolTip(QStringLiteral("///"));
    }

    if( lb_FS_LONG_ACTN == nullptr){
        lb_FS_LONG_ACTN = new QLabel(QStringLiteral("长故障处理:"));
        lb_FS_LONG_ACTN->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_FS_LONG_ACTN->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_FS_LONG_ACTN->setToolTip(QStringLiteral("RC/GCS故障触发时间超过设定时间，触发长故障"));
    }

    if( FS_LONG_ACTN == nullptr){
        FS_LONG_ACTN = new UComboBox();
        FS_LONG_ACTN->setEditable(false);
        FS_LONG_ACTN->addItem(QStringLiteral("返航(仅辅助模式)"),0);
        FS_LONG_ACTN->addItem(QStringLiteral("返航"),1);
        FS_LONG_ACTN->addItem(QStringLiteral("自稳模式"),2);
        FS_LONG_ACTN->addItem(QStringLiteral("开伞"),3);
        FS_LONG_ACTN->setToolTip(QStringLiteral("RC/GCS故障触发时间超过设定时间，触发长故障。"));
        FS_LONG_ACTN->setToolTipDuration(60000);
    }

    if( lb_FS_LONG_TIMEOUT == nullptr){
        lb_FS_LONG_TIMEOUT = new QLabel(QStringLiteral("超时时间:"));
        lb_FS_LONG_TIMEOUT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_FS_LONG_TIMEOUT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_FS_LONG_TIMEOUT->setToolTip(QStringLiteral("///"));
    }

    if( FS_LONG_TIMEOUT == nullptr){
        FS_LONG_TIMEOUT = new UDoubleSpinBox();
        FS_LONG_TIMEOUT->setRange(0.5,600);
        FS_LONG_TIMEOUT->setValue(0);
        FS_LONG_TIMEOUT->setAlignment(Qt::AlignCenter);
        FS_LONG_TIMEOUT->setSingleStep(0.5);
        FS_LONG_TIMEOUT->setDecimals(1);
        FS_LONG_TIMEOUT->setToolTip(QStringLiteral("///"));
    }

    Layout_action->addWidget(lb_FS_SHORT_ACTN,          0, 0, 1, 1);
    Layout_action->addWidget(FS_SHORT_ACTN,             0, 1, 1, 1);
    Layout_action->addWidget(lb_FS_SHORT_TIMEOUT,       0, 3, 1, 1);
    Layout_action->addWidget(FS_SHORT_TIMEOUT,          0, 4, 1, 1);
    Layout_action->addWidget(lb_FS_LONG_ACTN,           1, 0, 1, 1);
    Layout_action->addWidget(FS_LONG_ACTN,              1, 1, 1, 1);
    Layout_action->addWidget(lb_FS_LONG_TIMEOUT,        1, 3, 1, 1);
    Layout_action->addWidget(FS_LONG_TIMEOUT,           1, 4, 1, 1);

    /* short and long failsafe Triger Action parameters setting */
    if( Group_batt == nullptr){
        Group_batt = new QGroupBox(QStringLiteral("供电保护"));
        Group_batt->setObjectName("widgetGroupBox");
        Group_batt->setAlignment(Qt::AlignCenter);
    }

    if( Layout_batt == nullptr){
        Layout_batt = new QGridLayout(Group_batt);
        Layout_batt->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if( lb_BATT_LOW_VOLT == nullptr){
        lb_BATT_LOW_VOLT = new QLabel(QStringLiteral("1级保护电压:"));
        lb_BATT_LOW_VOLT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_BATT_LOW_VOLT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_BATT_LOW_VOLT->setToolTip(QStringLiteral("供电1级保护电压。"));
    }
    if( BATT_LOW_VOLT == nullptr){
        BATT_LOW_VOLT = new UDoubleSpinBox();
        BATT_LOW_VOLT->setRange(0,600);
        BATT_LOW_VOLT->setValue(0);
        BATT_LOW_VOLT->setAlignment(Qt::AlignCenter);
        BATT_LOW_VOLT->setSingleStep(0.5);
        BATT_LOW_VOLT->setDecimals(1);
        BATT_LOW_VOLT->setToolTip(QStringLiteral("供电1级保护电压"));
    }
    if( lb_BATT_CRT_VOLT == nullptr){
        lb_BATT_CRT_VOLT = new QLabel(QStringLiteral("2级保护电压:"));
        lb_BATT_CRT_VOLT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_BATT_CRT_VOLT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_BATT_CRT_VOLT->setToolTip(QStringLiteral("供电2级保护电压。"));
    }
    if( BATT_CRT_VOLT == nullptr){
        BATT_CRT_VOLT = new UDoubleSpinBox();
        BATT_CRT_VOLT->setRange(0,600);
        BATT_CRT_VOLT->setValue(0);
        BATT_CRT_VOLT->setAlignment(Qt::AlignCenter);
        BATT_CRT_VOLT->setSingleStep(0.5);
        BATT_CRT_VOLT->setDecimals(1);
        BATT_CRT_VOLT->setToolTip(QStringLiteral("供电2级保护电压"));
    }
    if( lb_BATT_ARM_VOLT == nullptr){
        lb_BATT_ARM_VOLT = new QLabel(QStringLiteral("解锁阈值电压:"));
        lb_BATT_ARM_VOLT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_BATT_ARM_VOLT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_BATT_ARM_VOLT->setToolTip(QStringLiteral("解锁阈值电压"));
    }
    if( BATT_ARM_VOLT == nullptr){
        BATT_ARM_VOLT = new UDoubleSpinBox();
        BATT_ARM_VOLT->setRange(0,600);
        BATT_ARM_VOLT->setValue(0);
        BATT_ARM_VOLT->setAlignment(Qt::AlignCenter);
        BATT_ARM_VOLT->setSingleStep(0.5);
        BATT_ARM_VOLT->setDecimals(1);
        BATT_ARM_VOLT->setToolTip(QStringLiteral("解锁阈值电压"));
    }
    if( lb_BATT_LOW_TIMER == nullptr){
        lb_BATT_LOW_TIMER = new QLabel(QStringLiteral("低电超时:"));
        lb_BATT_LOW_TIMER->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_BATT_LOW_TIMER->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_BATT_LOW_TIMER->setToolTip(QStringLiteral("当电压持续“低电超时”时间低于阈值，触发保护"));
    }
    if( BATT_LOW_TIMER == nullptr){
        BATT_LOW_TIMER = new UDoubleSpinBox();
        BATT_LOW_TIMER->setRange(0,120);
        BATT_LOW_TIMER->setValue(0);
        BATT_LOW_TIMER->setAlignment(Qt::AlignCenter);
        BATT_LOW_TIMER->setSingleStep(1);
        BATT_LOW_TIMER->setDecimals(0);
        BATT_LOW_TIMER->setToolTip(QStringLiteral("当电压持续“低电超时”时间低于阈值，触发保护"));
    }

    if( lb_BATT_FS_LOW_ACT == nullptr){
        lb_BATT_FS_LOW_ACT = new QLabel(QStringLiteral("故障处理:"));
        lb_BATT_FS_LOW_ACT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_BATT_FS_LOW_ACT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_BATT_FS_LOW_ACT->setToolTip(QStringLiteral("故障处理"));
    }

    if( BATT_FS_LOW_ACT == nullptr){
        BATT_FS_LOW_ACT = new UComboBox();
        BATT_FS_LOW_ACT->setEditable(false);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("无动作"),0);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("返航"),1);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("降落"),2);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("自毁"),3);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("降落(混合翼)"),4);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("开伞"),5);
        BATT_FS_LOW_ACT->addItem(QStringLiteral("Q-Alt降落模式"),6);
        BATT_FS_LOW_ACT->setToolTip(QStringLiteral("故障处理"));
        BATT_FS_LOW_ACT->setToolTipDuration(60000);
    }
    if( lb_BATT_FS_CRT_ACT == nullptr){
        lb_BATT_FS_CRT_ACT = new QLabel(QStringLiteral("故障处理:"));
        lb_BATT_FS_CRT_ACT->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_BATT_FS_CRT_ACT->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_BATT_FS_CRT_ACT->setToolTip(QStringLiteral("故障处理"));
    }

    if( BATT_FS_CRT_ACT == nullptr){
        BATT_FS_CRT_ACT = new UComboBox();
        BATT_FS_CRT_ACT->setEditable(false);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("无动作"),0);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("返航"),1);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("降落"),2);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("自毁"),3);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("降落(混合翼)"),4);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("开伞"),5);
        BATT_FS_CRT_ACT->addItem(QStringLiteral("Q-Alt降落模式"),6);
        BATT_FS_CRT_ACT->setToolTip(QStringLiteral("故障处理"));
        BATT_FS_CRT_ACT->setToolTipDuration(60000);
    }

    Layout_batt->addWidget(lb_BATT_LOW_VOLT,          0, 0, 1, 1);
    Layout_batt->addWidget(lb_BATT_FS_LOW_ACT,        0, 2, 1, 1);
    Layout_batt->addWidget(lb_BATT_CRT_VOLT,          1, 0, 1, 1);
    Layout_batt->addWidget(lb_BATT_FS_CRT_ACT,        1, 2, 1, 1);
    Layout_batt->addWidget(lb_BATT_ARM_VOLT,          2, 0, 1, 1);
    Layout_batt->addWidget(lb_BATT_LOW_TIMER,         2, 2, 1, 1);

    Layout_batt->addWidget(BATT_LOW_VOLT,          0, 1, 1, 1);
    Layout_batt->addWidget(BATT_FS_LOW_ACT,        0, 3, 1, 1);
    Layout_batt->addWidget(BATT_CRT_VOLT,          1, 1, 1, 1);
    Layout_batt->addWidget(BATT_FS_CRT_ACT,        1, 3, 1, 1);
    Layout_batt->addWidget(BATT_ARM_VOLT,          2, 1, 1, 1);
    Layout_batt->addWidget(BATT_LOW_TIMER,         2, 3, 1, 1);


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
    /* rc throttle failsafe group */
    widgetLayout->addWidget(Group_rc,1,1,1,1);
    /* short long failsafe action  group */
    widgetLayout->addWidget(Group_action,2,1,1,1);
    /* battery failsafe action  group */
    widgetLayout->addWidget(Group_batt,3,1,1,1);

    /* general parameters setting  group */
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 0, 1, 1);
    widgetLayout->addLayout(widgetLayout_pb , 5, 0, 1, 3);
    this->setLayout(widgetLayout);
}

void P_CFG_Failsafe::showEvent(QShowEvent *event)
{
    update_value();
    QWidget::showEvent(event);
}

void P_CFG_Failsafe::handle_DMMM_event(int ev, int linkid)
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

void P_CFG_Failsafe::update_value(bool getfromflight)
{
    qDebug()<<"update_value"<<getfromflight;
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        float val = 0;
        if(link->ParamGetValue_ByName("THR_FAILSAFE",val,getfromflight)){
            this->THR_FAILSAFE->setNewCurrentIndex(THR_FAILSAFE->findData(QVariant((int)val)));
        }
        if(link->ParamGetValue_ByName("THR_FS_VALUE",val,getfromflight)){
            this->THR_FS_VALUE->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("FS_SHORT_ACTN",val,getfromflight)){
            this->FS_SHORT_ACTN->setNewCurrentIndex(FS_SHORT_ACTN->findData(QVariant((int)val)));
        }
        if(link->ParamGetValue_ByName("FS_SHORT_TIMEOUT",val,getfromflight)){
            this->FS_SHORT_TIMEOUT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("FS_LONG_ACTN",val,getfromflight)){
            this->FS_LONG_ACTN->setNewCurrentIndex(FS_LONG_ACTN->findData(QVariant((int)val)));
        }
        if(link->ParamGetValue_ByName("BATT_LOW_VOLT",val,getfromflight)){
            this->BATT_LOW_VOLT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("FS_LONG_TIMEOUT",val,getfromflight)){
            this->FS_LONG_TIMEOUT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("BATT_CRT_VOLT",val,getfromflight)){
            this->BATT_CRT_VOLT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("BATT_FS_LOW_ACT",val,getfromflight)){
            this->BATT_FS_LOW_ACT->setNewCurrentIndex(BATT_FS_LOW_ACT->findData(QVariant((int)val)));
        }
        if(link->ParamGetValue_ByName("BATT_FS_CRT_ACT",val,getfromflight)){
            this->BATT_FS_CRT_ACT->setNewCurrentIndex(BATT_FS_CRT_ACT->findData(QVariant((int)val)));
        }
        if(link->ParamGetValue_ByName("BATT_LOW_TIMER",val,getfromflight)){
            this->BATT_LOW_TIMER->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("BATT_ARM_VOLT",val,getfromflight)){
            this->BATT_ARM_VOLT->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("FS_GCS_ENABL",val,getfromflight)){
            this->FS_GCS_ENABL->setNewCurrentIndex(FS_GCS_ENABL->findData(QVariant((int)val)));
        }


    }
}

void P_CFG_Failsafe::Upload_Parameters()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr)return;

    if(this->THR_FAILSAFE->IsChanged()){
        link->ParamSetToFlight_ByName("THR_FAILSAFE",this->THR_FAILSAFE->currentData().toInt());
    }
    if(this->THR_FS_VALUE->IsChanged()){
        link->ParamSetToFlight_ByName("THR_FS_VALUE",this->THR_FS_VALUE->value());
    }
    if(this->FS_SHORT_ACTN->IsChanged()){
        link->ParamSetToFlight_ByName("FS_SHORT_ACTN",this->FS_SHORT_ACTN->currentData().toInt());
    }
    if(this->FS_SHORT_TIMEOUT->IsChanged()){
        link->ParamSetToFlight_ByName("FS_SHORT_TIMEOUT",this->FS_SHORT_TIMEOUT->value());
    }
    if(this->FS_LONG_ACTN->IsChanged()){
        link->ParamSetToFlight_ByName("FS_LONG_ACTN",this->FS_LONG_ACTN->currentData().toInt());
    }
    if(this->FS_LONG_TIMEOUT->IsChanged()){
        link->ParamSetToFlight_ByName("FS_LONG_TIMEOUT",this->FS_LONG_TIMEOUT->value());
    }
    if(this->BATT_LOW_VOLT->IsChanged()){
        link->ParamSetToFlight_ByName("BATT_LOW_VOLT",this->BATT_LOW_VOLT->value());
    }
    if(this->BATT_CRT_VOLT->IsChanged()){
        link->ParamSetToFlight_ByName("BATT_CRT_VOLT",this->BATT_CRT_VOLT->value());
    }
    if(this->BATT_FS_LOW_ACT->IsChanged()){
        link->ParamSetToFlight_ByName("BATT_FS_LOW_ACT",this->BATT_FS_LOW_ACT->currentData().toInt());
    }
    if(this->BATT_FS_CRT_ACT->IsChanged()){
        link->ParamSetToFlight_ByName("BATT_FS_CRT_ACT",this->BATT_FS_CRT_ACT->currentData().toInt());
    }
    if(this->BATT_LOW_TIMER->IsChanged()){
        link->ParamSetToFlight_ByName("BATT_LOW_TIMER",this->BATT_LOW_TIMER->value());
    }
    if(this->BATT_ARM_VOLT->IsChanged()){
        link->ParamSetToFlight_ByName("BATT_ARM_VOLT",this->BATT_ARM_VOLT->value());
    }
    if(this->FS_GCS_ENABL->IsChanged()){
        link->ParamSetToFlight_ByName("FS_GCS_ENABL",this->FS_GCS_ENABL->currentData().toInt());
    }
}
