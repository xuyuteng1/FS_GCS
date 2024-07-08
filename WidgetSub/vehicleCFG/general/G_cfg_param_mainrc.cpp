/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "G_cfg_param_mainrc.h"
#include "DMMM.h"
#include <qmath.h>

G_CFG_RC::G_CFG_RC(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    initial();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("遥控配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}
QGridLayout *G_CFG_RC::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_RC::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_RC::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamMainRC();}});
    connect(PB_upload   , &QPushButton::released,this,&G_CFG_RC::upload_param);
    connect(PB_download2   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamAuxRC();}});
    connect(PB_upload2   , &QPushButton::released,this,&G_CFG_RC::upload_param_aux);
}

void G_CFG_RC::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    if(sublayout == nullptr){
        sublayout = new QGridLayout();
        sublayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("请优先调整遥控器上的微调，尽量保证各通道值与RC的参数一致。"));
        LB_Info->setObjectName(QString::fromUtf8("textLabel"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    FLT_Select_Name = new QLabel(QStringLiteral("飞行模式通道 "));
    FLT_Select_Name->setObjectName(QString::fromUtf8("CFGLabelState"));
    FLT_Select_Name->setAlignment(Qt::AlignCenter);
    FLT_Select_Name->setToolTip(QStringLiteral(""));

    if(this->FLT_Select == nullptr){
        this->FLT_Select = new UComboBox();
//        this->FLT_Select->setChanged(false);
        this->FLT_Select->setObjectName("RCComboBox");
    }

    for(int i = 0;i<3;i++){
        if(FLT_Modes_Names[i] == nullptr){
            FLT_Modes_Names[i] = new QLabel(QStringLiteral("飞行模式 ")+QString::number(i+1));
            FLT_Modes_Names[i]->setObjectName(QString::fromUtf8("CFGLabelState"));
            FLT_Modes_Names[i]->setAlignment(Qt::AlignCenter);
            FLT_Modes_Names[i]->setToolTip(QStringLiteral(""));
        }
        if(FLT_Modes[i] == nullptr){
            FLT_Modes[i] = new UComboBox();
            FLT_Modes[i]->setObjectName("RCComboBox");
        }
    }

    for(int i = 0;i<4;i++){
        if(LB_RC[i] == nullptr){
            LB_RC[i] = new QLabel(QStringLiteral("通道 ")+QString::number(i+1));
            LB_RC[i]->setObjectName(QString::fromUtf8("CFGLabelState"));
            LB_RC[i]->setAlignment(Qt::AlignCenter);
            LB_RC[i]->setToolTip(QStringLiteral(""));
        }
        if(QB_RC_Min[i] == nullptr){
            QB_RC_Min[i] = new USpinBox();
            QB_RC_Min[i]->setRange(800,2200);
            QB_RC_Min[i]->setValue(1100);
            QB_RC_Min[i]->setAlignment(Qt::AlignCenter);
            QB_RC_Min[i]->setSuffix(QStringLiteral(""));
            QB_RC_Min[i]->setChanged(false);
            QB_RC_Min[i]->setToolTip(QStringLiteral("RC通道最小值。"));
            QB_RC_Min[i]->setObjectName("widgetSpinBox");
        }
        if(RC_OPT_Names[i] == nullptr){
            RC_OPT_Names[i] = new QLabel(QStringLiteral("RC ")+QString::number(i+6)+ QStringLiteral(" OPT"));
            RC_OPT_Names[i]->setObjectName(QString::fromUtf8("CFGLabelState"));
            RC_OPT_Names[i]->setAlignment(Qt::AlignCenter);
            RC_OPT_Names[i]->setToolTip(QStringLiteral(""));
        }
        if(RC_OPT[i] == nullptr){
            RC_OPT[i] = new UComboBox();
            RC_OPT[i]->setObjectName("RCComboBox");
        }

        if( QB_RC_Max[i] == nullptr){
            QB_RC_Max[i] = new USpinBox();
            QB_RC_Max[i]->setRange(800,2200);
            QB_RC_Max[i]->setValue(1940);
            QB_RC_Max[i]->setAlignment(Qt::AlignCenter);
            QB_RC_Max[i]->setSuffix(QStringLiteral(""));
            QB_RC_Max[i]->setChanged(false);
            QB_RC_Max[i]->setToolTip(QStringLiteral("RC通道最大值。"));
            QB_RC_Max[i]->setObjectName("widgetSpinBox");
        }

        if( QB_RC_Trim[i] == nullptr){
            QB_RC_Trim[i] = new USpinBox();
            QB_RC_Trim[i]->setRange(800,2200);
            QB_RC_Trim[i]->setValue(1520);
            QB_RC_Trim[i]->setAlignment(Qt::AlignCenter);
            QB_RC_Trim[i]->setSuffix(QStringLiteral(""));
            QB_RC_Trim[i]->setChanged(false);
            QB_RC_Trim[i]->setToolTip(QStringLiteral("RC通道中间值。"));
            QB_RC_Trim[i]->setObjectName("widgetSpinBox");
        }
        if( QB_RC_DZ[i] == nullptr){
            QB_RC_DZ[i] = new USpinBox();
            QB_RC_DZ[i]->setRange(0,200);
            QB_RC_DZ[i]->setValue(40);
            QB_RC_DZ[i]->setAlignment(Qt::AlignCenter);
            QB_RC_DZ[i]->setSuffix(QStringLiteral(""));
            QB_RC_DZ[i]->setChanged(false);
            QB_RC_DZ[i]->setToolTip(QStringLiteral("RC通道死区范围。"));
            QB_RC_DZ[i]->setObjectName("widgetSpinBox");
        }

    }

    if(LB_RC_Min_Name == nullptr){
        LB_RC_Min_Name = new QLabel(QStringLiteral("最小值"));
        LB_RC_Min_Name->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_RC_Min_Name->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        LB_RC_Min_Name->setToolTip(QStringLiteral(""));
    }

    if(LB_RC_Min_Name == nullptr){
        LB_RC_Min_Name = new QLabel(QStringLiteral("最小值"));
        LB_RC_Min_Name->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_RC_Min_Name->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        LB_RC_Min_Name->setToolTip(QStringLiteral(""));
    }

    if( LB_RC_Max_Name == nullptr){
        LB_RC_Max_Name = new QLabel(QStringLiteral("最大值"));
        LB_RC_Max_Name->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_RC_Max_Name->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        LB_RC_Max_Name->setToolTip(QStringLiteral(""));
    }

    if( LB_RC_Trim_Name == nullptr){
        LB_RC_Trim_Name = new QLabel(QStringLiteral("中立值"));
        LB_RC_Trim_Name->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_RC_Trim_Name->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        LB_RC_Trim_Name->setToolTip(QStringLiteral(""));
    }
    if( LB_RC_DZ_Name == nullptr){
        LB_RC_DZ_Name = new QLabel(QStringLiteral("死区值"));
        LB_RC_DZ_Name->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_RC_DZ_Name->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        LB_RC_DZ_Name->setToolTip(QStringLiteral(""));
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
    if(PB_download2 == nullptr){
        PB_download2 = new QPushButton(QStringLiteral("查询"));
        PB_download2->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_download2->setToolTip(QStringLiteral(""));
    }
    if(PB_upload2 == nullptr){
        PB_upload2 = new QPushButton(QStringLiteral("设置"));
        PB_upload2->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_upload2->setToolTip(QStringLiteral(""));
    }
    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
    }
    if(widgetLayout_pb2 == nullptr){
        widgetLayout_pb2 = new QHBoxLayout();
    }
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    for(int i = 0 ;i < 8; i++){
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
    }
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("遥控配置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    widgetLayout->addWidget(titleLabel,            0 ,0 ,1 ,20);
    widgetLayout->addWidget(LB_Info,            1 ,0 ,1 ,20);

    for(int i = 0;i < 4 ; i++){
        widgetLayout->addWidget(LB_RC[i],       2 ,4+i,1 ,1 );
        widgetLayout->addWidget(QB_RC_Max[i],   3 ,4+i,1 ,1 );
        widgetLayout->addWidget(QB_RC_Trim[i],  4 ,4+i,1 ,1 );
        widgetLayout->addWidget(QB_RC_Min[i],   5 ,4+i,1 ,1 );
        widgetLayout->addWidget(QB_RC_DZ[i],    6 ,4+i,1 ,1 );
    }
    widgetLayout->addWidget(LB_RC_Max_Name,     3 ,3 ,1 ,1 );
    widgetLayout->addWidget(LB_RC_Trim_Name,    4 ,3 ,1 ,1 );
    widgetLayout->addWidget(LB_RC_Min_Name,     5 ,3 ,1 ,1 );
    widgetLayout->addWidget(LB_RC_DZ_Name,      6 ,3 ,1 ,1 );

    for(int i = 0 ;i < 8;i++){
        widgetLayout->addWidget(PR_pwm[i],      3 ,10+i ,3 ,1 );
        widgetLayout->addWidget(LB_pwm[i],      6 ,10+i ,1 ,1 );
    }

    widgetLayout_pb->addStretch(5);
    widgetLayout_pb->addWidget(PB_download,1);
    widgetLayout_pb->addWidget(PB_upload,1);
    widgetLayout_pb->addStretch(5);

    widgetLayout_pb2->addStretch(5);
    widgetLayout_pb2->addWidget(PB_download2,1);
    widgetLayout_pb2->addWidget(PB_upload2,1);
    widgetLayout_pb2->addStretch(5);

    widgetLayout->addLayout(widgetLayout_pb,7,0,1,20);

//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 15, 0, 1, 20);


    sublayout->addWidget(FLT_Select_Name, 1,5,1,1);
    sublayout->addWidget(FLT_Select, 1,6,1,1);

    for(int i = 0;i < 3 ; i++){
        sublayout->addWidget(FLT_Modes_Names[i],       2+i ,5,1 ,1 );
        sublayout->addWidget(FLT_Modes[i],   2+i ,6,1 ,1 );
    }
    for(int i = 0;i < 4 ; i++){
        sublayout->addWidget(RC_OPT_Names[i],       1+i ,12,1 ,1 );
        sublayout->addWidget(RC_OPT[i],   1+i ,13,1 ,1 );
    }
    sublayout->addLayout(widgetLayout_pb2,5,0,1,20,Qt::AlignCenter);

    widgetLayout->addLayout(sublayout,9,1,1,20);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 10, 0, 1, 20);
    this->widgetLayout->setContentsMargins(10,20,10,20);
    widgetLayout->setRowMinimumHeight(1,30);
    widgetLayout->setRowMinimumHeight(2,30);
    widgetLayout->setRowMinimumHeight(3,30);
    widgetLayout->setRowMinimumHeight(4,30);
    widgetLayout->setRowMinimumHeight(5,30);
    widgetLayout->setRowMinimumHeight(6,30);
    this->setLayout(widgetLayout);
}

void G_CFG_RC::initial()
{
    Flight_mode_names.insert(QStringLiteral("CH5"),5);
    Flight_mode_names.insert(QStringLiteral("CH6"),6);
    Flight_mode_names.insert(QStringLiteral("CH7"),7);
    Flight_mode_names.insert(QStringLiteral("CH8"),8);
    Flight_mode_names.insert(QStringLiteral("CH9"),9);

    for (auto it = Flight_mode_names.begin(); it != Flight_mode_names.end(); ++it) {
        FLT_Select->addItem(it.key(),it.value());
    }

    Flight_modes.insert(QStringLiteral("Stabilize"),0);
    Flight_modes.insert(QStringLiteral("Acro"),1);
    Flight_modes.insert(QStringLiteral("AltHold"),2);
    Flight_modes.insert(QStringLiteral("Auto"),3);
    Flight_modes.insert(QStringLiteral("Guided"),4);
    Flight_modes.insert(QStringLiteral("Loiter"),5);
    Flight_modes.insert(QStringLiteral("RTL"),6);
    Flight_modes.insert(QStringLiteral("Circle"),7);
    Flight_modes.insert(QStringLiteral("Land"),9);
    Flight_modes.insert(QStringLiteral("Drift"),11);
    Flight_modes.insert(QStringLiteral("Sport"),13);
    Flight_modes.insert(QStringLiteral("Flip"),14);
    Flight_modes.insert(QStringLiteral("AutoTune"),15);
    Flight_modes.insert(QStringLiteral("PosHold"),16);
    Flight_modes.insert(QStringLiteral("Brake"),17);
    Flight_modes.insert(QStringLiteral("Throw"),18);
    Flight_modes.insert(QStringLiteral("Avoid_ADSB"),19);
    Flight_modes.insert(QStringLiteral("Guided_NoGPS"),20);
    Flight_modes.insert(QStringLiteral("Smart_RTL"),21);
    Flight_modes.insert(QStringLiteral("FlowHold"),22);
    Flight_modes.insert(QStringLiteral("Follow"),23);
    Flight_modes.insert(QStringLiteral("ZigZag"),24);
    Flight_modes.insert(QStringLiteral("SystemID"),25);
    Flight_modes.insert(QStringLiteral("Heli_Autorotate"),26);
    Flight_modes.insert(QStringLiteral("Auto_RTL"),27);
    for(int i = 0;i<3;i++)
    {
        for (auto it = Flight_modes.begin(); it != Flight_modes.end(); ++it) {
            FLT_Modes[i]->addItem(it.key(),it.value());
        }
    }
    RC_options.insert(QStringLiteral("DO_NOTHING"),0);
    RC_options.insert(QStringLiteral("MOTOR_ESTOP"),31);
    RC_options.insert(QStringLiteral("AUTOTUNE"),17);

    for(int i = 0;i<4;i++)
    {
        for (auto it = RC_options.begin(); it != RC_options.end(); ++it) {
            RC_OPT[i]->addItem(it.key(),it.value());
        }
    }
}

void G_CFG_RC::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetParamMainRC:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_MianRC pkt = link->getTVehicleParam().MainRC;

                for(int i = 0; i <4 ;i++){
                    QB_RC_Min[i]->setValue(pkt.val[i].radio_min);
                    QB_RC_Trim[i]->setValue(pkt.val[i].radio_trim);
                    QB_RC_Max[i]->setValue(pkt.val[i].radio_max);
                    QB_RC_DZ[i]->setValue(pkt.val[i].dead_zone);
                    QB_RC_Min[i]->setChanged(false);
                    QB_RC_Trim[i]->setChanged(false);
                    QB_RC_Max[i]->setChanged(false);
                    QB_RC_DZ[i]->setChanged(false);
                }
            }
        }break;
        case Q_DMMM::DMMM_GCSEvent_GetParamAuxRC:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                FlyLink::param_AuxRC pkt = link->getTVehicleParam().AuxRC;
                FLT_Select->setCurrentIndex(FLT_Select->findData(QVariant(pkt.flight_modes_ch)));
                FLT_Modes[0]->setCurrentIndex(FLT_Modes[0]->findData(QVariant(pkt.flight_mode1)));
                FLT_Modes[1]->setCurrentIndex(FLT_Modes[1]->findData(QVariant(pkt.flight_mode4)));
                FLT_Modes[2]->setCurrentIndex(FLT_Modes[2]->findData(QVariant(pkt.flight_mode6)));
                RC_OPT[0]->setCurrentIndex(RC_OPT[0]->findData(QVariant(pkt.ch6_aux_fun)));
                RC_OPT[1]->setCurrentIndex(RC_OPT[1]->findData(QVariant(pkt.ch7_aux_fun)));
                RC_OPT[2]->setCurrentIndex(RC_OPT[2]->findData(QVariant(pkt.ch8_aux_fun)));
                RC_OPT[3]->setCurrentIndex(RC_OPT[3]->findData(QVariant(pkt.ch9_aux_fun)));
            }
        }break;

        case Q_DMMM::DMMM_GCSEvent_GetMotorVal:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            for(int i = 0;i < 8 ;i++){
                if(link != nullptr){
                    PR_pwm[i]->setValue(link->getTDataPort().tRC_OUT.rc[i]);
                }
            }
            int ch = FLT_Select->currentData().toInt();
            uint16_t pwm = link->getTDataPort().tRC_OUT.rc[ch-1];
            if( pwm > 0 && pwm <= 1230)
            {
                FLT_Modes[0]->setStyleSheet("background-color: green;");
                FLT_Modes[1]->setStyleSheet("background-color: #708090;");
                FLT_Modes[2]->setStyleSheet("background-color: #708090;");
            }
            else if(pwm > 1491 && pwm <= 1620)
            {
                FLT_Modes[1]->setStyleSheet("background-color: green;");
                FLT_Modes[0]->setStyleSheet("background-color: #708090;");
                FLT_Modes[2]->setStyleSheet("background-color: #708090;");
            }
            else if(pwm > 1750)
            {
                FLT_Modes[2]->setStyleSheet("background-color: green;");
                FLT_Modes[0]->setStyleSheet("background-color: #708090;");
                FLT_Modes[1]->setStyleSheet("background-color: #708090;");
            }
            else
            {
                FLT_Modes[2]->setStyleSheet("background-color: #708090;");
                FLT_Modes[0]->setStyleSheet("background-color: #708090;");
                FLT_Modes[1]->setStyleSheet("background-color: #708090;");
            }
        }break;

        default:break;
    }
}

void G_CFG_RC::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_MianRC pkt{};
        pkt.is_set = 1;
        for(int i = 0;i<4;i++){
            pkt.val[i].radio_min  = QB_RC_Min[i]->value();
            pkt.val[i].radio_trim = QB_RC_Trim[i]->value();
            pkt.val[i].radio_max  = QB_RC_Max[i]->value();
            pkt.val[i].dead_zone  = QB_RC_DZ[i]->value();
        }
        link->do_setParamMainRC(pkt);
    }
}

void G_CFG_RC::upload_param_aux()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_AuxRC pkt{};
        pkt.is_set = 1;
        pkt.flight_modes_ch = FLT_Select->currentData().toInt();
        pkt.flight_mode1 = FLT_Modes[0]->currentData().toInt();
        pkt.flight_mode4 = FLT_Modes[1]->currentData().toInt();
        pkt.flight_mode6 = FLT_Modes[2]->currentData().toInt();
        pkt.ch6_aux_fun = RC_OPT[0]->currentData().toInt();
        pkt.ch7_aux_fun = RC_OPT[1]->currentData().toInt();
        pkt.ch8_aux_fun = RC_OPT[2]->currentData().toInt();
        pkt.ch9_aux_fun = RC_OPT[3]->currentData().toInt();
        link->do_setParamAuxRC(pkt);
    }
}
