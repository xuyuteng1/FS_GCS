
/**=================================================================**
 * @brief       : parachute Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-24     Jerry.xl     the first version
 **==================================================================**/
#include "P_Cfg_parachute.h"
#include "DMMM.h"

void P_Cfg_Parachute::connectSignalAndSlot()
{

}

P_Cfg_Parachute::P_Cfg_Parachute(QWidget *parent, QString title):
    G_CFG_Template(parent,title)
{
    f_WidgetInit();
    f_connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(_widgetTitle);
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void P_Cfg_Parachute::WidgetInit()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    /* Parachute Init */
    Init_ParametersParachute();

    /* widget title label */
    widgetLayout->addWidget(titleLabel,      0, 0, 1, 3);
    /* SpacerItem for automatic spacing adjustment */
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 0, 1, 1);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 2, 1, 1);
    /* parachute parameters group */
    widgetLayout->addWidget(Group_parachute,2,1,1,1);
    widgetLayout->addLayout(widgetLayout_pb , 5, 0, 1, 3);

    this->setLayout(widgetLayout);
}

void P_Cfg_Parachute::Upload_Parameters()
{
    upload_ParametersParachute();
}

void P_Cfg_Parachute::update_value(bool getfromflight)
{
    update_ParametersParachute(getfromflight);
}

void P_Cfg_Parachute::Init_ParametersParachute()
{
    /* rc&throttle failsafe parameters group*/
    if( Group_parachute == nullptr){
        Group_parachute = new QGroupBox(QStringLiteral("降落伞"));
        Group_parachute->setObjectName("widgetGroupBox");
        Group_parachute->setAlignment(Qt::AlignCenter);
    }

    if( Layout_parachute == nullptr){
        Layout_parachute = new QGridLayout(Group_parachute);
        Layout_parachute->setObjectName(QString::fromUtf8("widgetLayout"));
    }


    if( CHUTE_ENABLED == nullptr){
        CHUTE_ENABLED = new UCheckBox();
        CHUTE_ENABLED->setText(QStringLiteral("开启降落伞功能"));
        CHUTE_ENABLED->setToolTip(QStringLiteral("降落伞使能开关"));
    }
    if( lb_CHUTE_TYPE == nullptr){
        lb_CHUTE_TYPE = new QLabel(QStringLiteral("伞控类型:"));
        lb_CHUTE_TYPE->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_CHUTE_TYPE->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_CHUTE_TYPE->setToolTip(QStringLiteral("降落伞控制类型的选择"));
    }
    if( CHUTE_TYPE == nullptr){
        CHUTE_TYPE = new UComboBox();
        CHUTE_TYPE->setEditable(false);
        CHUTE_TYPE->addItem(QStringLiteral("继电器1"),0);
        CHUTE_TYPE->addItem(QStringLiteral("继电器2"),1);
        CHUTE_TYPE->addItem(QStringLiteral("继电器3"),2);
        CHUTE_TYPE->addItem(QStringLiteral("继电器4"),3);
        CHUTE_TYPE->addItem(QStringLiteral("舵  机"),10);
        CHUTE_TYPE->setToolTip(QStringLiteral("降落伞控制类型的选择"));
        CHUTE_TYPE->setToolTipDuration(60000);
    }

    if( lb_CHUTE_SERVO_ON == nullptr){
        lb_CHUTE_SERVO_ON = new QLabel(QStringLiteral("PWM值(开伞):"));
        lb_CHUTE_SERVO_ON->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_CHUTE_SERVO_ON->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_CHUTE_SERVO_ON->setToolTip(QStringLiteral("开伞时舵机输出的PWM值"));
    }
    if( CHUTE_SERVO_ON == nullptr){
        CHUTE_SERVO_ON = new UDoubleSpinBox();
        CHUTE_SERVO_ON->setRange(1000,2000);
        CHUTE_SERVO_ON->setValue(0);
        CHUTE_SERVO_ON->setAlignment(Qt::AlignCenter);
        CHUTE_SERVO_ON->setSingleStep(1);
        CHUTE_SERVO_ON->setDecimals(0);
        CHUTE_SERVO_ON->setToolTip(QStringLiteral("开伞时舵机输出的PWM值"));
    }
    if( lb_CHUTE_SERVO_OFF == nullptr){
        lb_CHUTE_SERVO_OFF = new QLabel(QStringLiteral("PWM值(关伞):"));
        lb_CHUTE_SERVO_OFF->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_CHUTE_SERVO_OFF->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_CHUTE_SERVO_OFF->setToolTip(QStringLiteral("关伞时舵机输出的PWM值"));
    }
    if( CHUTE_SERVO_OFF == nullptr){
        CHUTE_SERVO_OFF = new UDoubleSpinBox();
        CHUTE_SERVO_OFF->setRange(1000,2000);
        CHUTE_SERVO_OFF->setValue(0);
        CHUTE_SERVO_OFF->setAlignment(Qt::AlignCenter);
        CHUTE_SERVO_OFF->setSingleStep(1);
        CHUTE_SERVO_OFF->setDecimals(0);
        CHUTE_SERVO_OFF->setToolTip(QStringLiteral("关伞时舵机输出的PWM值"));
    }

    if( lb_CHUTE_ALT_MIN == nullptr){
        lb_CHUTE_ALT_MIN = new QLabel(QStringLiteral("开伞最低高度(m):"));
        lb_CHUTE_ALT_MIN->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_CHUTE_ALT_MIN->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_CHUTE_ALT_MIN->setToolTip(QStringLiteral("相对高度低于此值将不执行开伞,0则不进行高度检查"));
    }
    if( CHUTE_ALT_MIN == nullptr){
        CHUTE_ALT_MIN = new UDoubleSpinBox();
        CHUTE_ALT_MIN->setRange(0,32000);
        CHUTE_ALT_MIN->setValue(0);
        CHUTE_ALT_MIN->setAlignment(Qt::AlignCenter);
        CHUTE_ALT_MIN->setSingleStep(1);
        CHUTE_ALT_MIN->setDecimals(0);
        CHUTE_ALT_MIN->setToolTip(QStringLiteral("相对高度低于此值将不执行开伞,0则不进行高度检查"));
    }

    if( lb_CHUTE_DELAY_MS == nullptr){
        lb_CHUTE_DELAY_MS = new QLabel(QStringLiteral("开伞延迟(ms):"));
        lb_CHUTE_DELAY_MS->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_CHUTE_DELAY_MS->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_CHUTE_DELAY_MS->setToolTip(QStringLiteral("电机停止及实际开伞的延迟时间"));
    }
    if( CHUTE_DELAY_MS == nullptr){
        CHUTE_DELAY_MS = new UDoubleSpinBox();
        CHUTE_DELAY_MS->setRange(0,6000);
        CHUTE_DELAY_MS->setValue(0);
        CHUTE_DELAY_MS->setAlignment(Qt::AlignCenter);
        CHUTE_DELAY_MS->setSingleStep(1);
        CHUTE_DELAY_MS->setDecimals(0);
        CHUTE_DELAY_MS->setToolTip(QStringLiteral("电机停止及实际开伞的延迟时间"));
    }

    if( lb_CHUTE_CRT_SINK == nullptr){
        lb_CHUTE_CRT_SINK = new QLabel(QStringLiteral("坠毁速度(m/s):"));
        lb_CHUTE_CRT_SINK->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_CHUTE_CRT_SINK->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_CHUTE_CRT_SINK->setToolTip(QStringLiteral("下降速度超过此值，将会触发开伞，值为0则不检测"));
    }
    if( CHUTE_CRT_SINK == nullptr){
        CHUTE_CRT_SINK = new UDoubleSpinBox();
        CHUTE_CRT_SINK->setRange(0,20);
        CHUTE_CRT_SINK->setValue(0);
        CHUTE_CRT_SINK->setAlignment(Qt::AlignCenter);
        CHUTE_CRT_SINK->setSingleStep(0.1);
        CHUTE_CRT_SINK->setDecimals(1);
        CHUTE_CRT_SINK->setToolTip(QStringLiteral("下降速度超过此值，将会触发开伞，值为0则不检测"));
    }


    if( CHUTE_OPTIONS == nullptr){
        CHUTE_OPTIONS = new UCheckBox();
        CHUTE_OPTIONS->setText(QStringLiteral("伞仓位置保持"));
        CHUTE_OPTIONS->setToolTip(QStringLiteral("使能后，开伞后会保持开伞状态，否则开伞仅执行开伞动作，执行后舵机会回到关闭状态"));
    }

    Layout_parachute->addWidget(CHUTE_ENABLED,      0, 0, 1, 2);
    Layout_parachute->addWidget(CHUTE_OPTIONS,      1, 0, 1, 2);

    Layout_parachute->addWidget(lb_CHUTE_TYPE,      2, 0, 1, 1);
    Layout_parachute->addWidget(lb_CHUTE_SERVO_ON,  3, 0, 1, 1);
    Layout_parachute->addWidget(lb_CHUTE_SERVO_OFF, 4, 0, 1, 1);
    Layout_parachute->addWidget(lb_CHUTE_DELAY_MS,  5, 0, 1, 1);
    Layout_parachute->addWidget(lb_CHUTE_ALT_MIN,   6, 0, 1, 1);
    Layout_parachute->addWidget(lb_CHUTE_CRT_SINK,  7, 0, 1, 1);

    Layout_parachute->addWidget(CHUTE_TYPE,         2, 1, 1, 1);
    Layout_parachute->addWidget(CHUTE_SERVO_ON,     3, 1, 1, 1);
    Layout_parachute->addWidget(CHUTE_SERVO_OFF,    4, 1, 1, 1);
    Layout_parachute->addWidget(CHUTE_ALT_MIN,      5, 1, 1, 1);
    Layout_parachute->addWidget(CHUTE_DELAY_MS,     6, 1, 1, 1);
    Layout_parachute->addWidget(CHUTE_CRT_SINK,     7, 1, 1, 1);
}

void P_Cfg_Parachute::upload_ParametersParachute()
{

    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr)return;
    if(this->CHUTE_ENABLED->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_ENABLED",this->CHUTE_ENABLED->checkState()?1:0);
    }
    /* CHUTE_OPTIONS 指示的是bit位，当前仅使用的1位，所以此用法没问题，但后续得留意 */
    if(this->CHUTE_OPTIONS->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_OPTIONS",this->CHUTE_OPTIONS->checkState()?1:0);
    }
    if(this->CHUTE_TYPE->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_TYPE",this->CHUTE_TYPE->currentData().toInt());
    }
    if(this->CHUTE_SERVO_ON->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_SERVO_ON",this->CHUTE_SERVO_ON->value());
    }
    if(this->CHUTE_SERVO_OFF->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_SERVO_OFF",this->CHUTE_SERVO_OFF->value());
    }
    if(this->CHUTE_ALT_MIN->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_ALT_MIN",this->CHUTE_ALT_MIN->value());
    }
    if(this->CHUTE_DELAY_MS->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_DELAY_MS",this->CHUTE_DELAY_MS->value());
    }
    if(this->CHUTE_CRT_SINK->IsChanged()){
        link->ParamSetToFlight_ByName("CHUTE_CRT_SINK",this->CHUTE_CRT_SINK->value());
    }
}

void P_Cfg_Parachute::update_ParametersParachute(bool getfromflight)
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        float val = 0;
        if(link->ParamGetValue_ByName("CHUTE_ENABLED",val,getfromflight)){
            int state = val;
            this->CHUTE_ENABLED->setNewChecked(state?true:false);
        }
        if(link->ParamGetValue_ByName("CHUTE_OPTIONS",val,getfromflight)){
            int state = val;
            this->CHUTE_OPTIONS->setNewChecked((state&0x01)?true:false);
        }
        if(link->ParamGetValue_ByName("CHUTE_TYPE",val,getfromflight)){
            this->CHUTE_TYPE->setNewCurrentIndex(this->CHUTE_TYPE->findData(QVariant((int)val)));
        }
        if(link->ParamGetValue_ByName("CHUTE_SERVO_ON",val,getfromflight)){
            this->CHUTE_SERVO_ON->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("CHUTE_SERVO_OFF",val,getfromflight)){
            this->CHUTE_SERVO_OFF->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("CHUTE_ALT_MIN",val,getfromflight)){
            this->CHUTE_ALT_MIN->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("CHUTE_DELAY_MS",val,getfromflight)){
            this->CHUTE_DELAY_MS->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("CHUTE_CRT_SINK",val,getfromflight)){
            this->CHUTE_CRT_SINK->SetNewValue(val);
        }
    }
}
