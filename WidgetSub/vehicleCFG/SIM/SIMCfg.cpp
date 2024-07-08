/**=================================================================**
 * @brief       : SITL Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-03     Jerry.xl     the first version
 **==================================================================**/
#include "SIMCfg.h"
#include "DMMM.h"
#include <qmath.h>

SIM_CFG::SIM_CFG(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("仿真配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
    this->setMinimumSize(400,300);
}

void SIM_CFG::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&SIM_CFG::handle_DMMM_event);
    connect(this->OpenSIM, &QPushButton::released,this,&SIM_CFG::handle_OpenSIM);
//    connect(this, &SIM_CFG::show,this,&SIM_CFG::update_value);

    connect(PB_download   , &QPushButton::released,this,[=]{update_value(true);});
    connect(PB_upload   , &QPushButton::released,this,&SIM_CFG::Upload_Parameters);
}

void SIM_CFG::widget_init()
{
    if(this->flightgear == nullptr){
        flightgear = new FlightGear_Link(this,true);
    }
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("仿真配置"));
        this->titleLabel->setObjectName("CfgWIdgetTitle");
        this->titleLabel->setAlignment(Qt::AlignCenter);
    }
    if( this->OpenSIM == nullptr){
        this->OpenSIM = new QPushButton(QStringLiteral("开启仿真"));
        this->OpenSIM->setObjectName("widgetButton");
        this->OpenSIM->setToolTip(QStringLiteral("开启或关闭仿真通信"));
    }
    /* init postion */
    if( lb_Pos_Alt == nullptr){
        lb_Pos_Alt = new QLabel(QStringLiteral("高度:"));
        lb_Pos_Alt->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Pos_Alt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Pos_Alt->setToolTip(QStringLiteral("仿真启动时的高度,单位米,海拔高度"));
    }
    if( lb_Pos_Lat == nullptr){
        lb_Pos_Lat = new QLabel(QStringLiteral("纬度:"));
        lb_Pos_Lat->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Pos_Lat->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Pos_Lat->setToolTip(QStringLiteral("仿真启动时的纬度"));
    }
    if( lb_Pos_Lng == nullptr){
        lb_Pos_Lng = new QLabel(QStringLiteral("经度:"));
        lb_Pos_Lng->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Pos_Lng->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Pos_Lng->setToolTip(QStringLiteral("仿真启动时的经度"));
    }
    if( lb_Pos_Heading == nullptr){
        lb_Pos_Heading = new QLabel(QStringLiteral("航向:"));
        lb_Pos_Heading->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Pos_Heading->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Pos_Heading->setToolTip(QStringLiteral("仿真启动时的航向,单位°"));
    }
    if( ds_Pos_Alt == nullptr){
        ds_Pos_Alt = new UDoubleSpinBox();
        ds_Pos_Alt->setRange(-5000,5000);
        ds_Pos_Alt->setValue(0);
        ds_Pos_Alt->setAlignment(Qt::AlignCenter);
        ds_Pos_Alt->setSuffix(QStringLiteral(" m"));
        ds_Pos_Alt->setDecimals(1);
        ds_Pos_Alt->setToolTip(QStringLiteral("仿真启动时的高度,单位米,海拔高度。"));
        ds_Pos_Alt->setChanged(true);
    }
    if( ds_Pos_Lat == nullptr){
        ds_Pos_Lat = new UDoubleSpinBox();
        ds_Pos_Lat->setRange(-90,90);
        ds_Pos_Lat->setValue(0);
        ds_Pos_Lat->setAlignment(Qt::AlignCenter);
        ds_Pos_Lat->setSuffix(QStringLiteral(" °"));
        ds_Pos_Lat->setDecimals(7);
        ds_Pos_Lat->setToolTip(QStringLiteral("仿真启动时的纬度"));
        ds_Pos_Lat->setChanged(true);
    }
    if( ds_Pos_Lng == nullptr){
        ds_Pos_Lng = new UDoubleSpinBox();
        ds_Pos_Lng->setRange(-180,180);
        ds_Pos_Lng->setValue(0);
        ds_Pos_Lng->setAlignment(Qt::AlignCenter);
        ds_Pos_Lng->setSuffix(QStringLiteral(" °"));
        ds_Pos_Lng->setDecimals(7);
        ds_Pos_Lng->setToolTip(QStringLiteral("仿真启动时的经度"));
        ds_Pos_Lng->setChanged(true);
    }
    if( ds_Pos_Heading == nullptr){
        ds_Pos_Heading = new UDoubleSpinBox();
        ds_Pos_Heading->setRange(0,360);
        ds_Pos_Heading->setValue(0);
        ds_Pos_Heading->setAlignment(Qt::AlignCenter);
        ds_Pos_Heading->setSuffix(QStringLiteral(" °"));
        ds_Pos_Heading->setDecimals(1);
        ds_Pos_Heading->setToolTip(QStringLiteral("仿真启动时的航向"));
        ds_Pos_Heading->setChanged(true);
    }
    if( Group_Postion == nullptr){
        Group_Postion = new QGroupBox(QStringLiteral("初始位置"));
        Group_Postion->setObjectName("widgetGroupBox");
        Group_Postion->setAlignment(Qt::AlignCenter);
    }

    if( Layout_Postion == nullptr){
        Layout_Postion = new QGridLayout(Group_Postion);
        Layout_Postion->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    Layout_Postion->addWidget(lb_Pos_Lat,0,0,1,1,Qt::AlignRight|Qt::AlignVCenter);
    Layout_Postion->addWidget(lb_Pos_Lng,1,0,1,1,Qt::AlignRight|Qt::AlignVCenter);
    Layout_Postion->addWidget(lb_Pos_Alt,2,0,1,1,Qt::AlignRight|Qt::AlignVCenter);
    Layout_Postion->addWidget(lb_Pos_Heading,3,0,1,1,Qt::AlignRight|Qt::AlignVCenter);


    Layout_Postion->addWidget(ds_Pos_Lat,0,1,1,1);//,Qt::AlignLeft|Qt::AlignVCenter);
    Layout_Postion->addWidget(ds_Pos_Lng,1,1,1,1);//,Qt::AlignLeft|Qt::AlignVCenter);
    Layout_Postion->addWidget(ds_Pos_Alt,2,1,1,1);//,Qt::AlignLeft|Qt::AlignVCenter);
    Layout_Postion->addWidget(ds_Pos_Heading,3,1,1,1);//,Qt::AlignLeft|Qt::AlignVCenter);

    /* Wind Parameter */
    if( lb_WindDir == nullptr){
        lb_WindDir = new QLabel(QStringLiteral("风向:"));
        lb_WindDir->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_WindDir->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_WindDir->setToolTip(QStringLiteral("模拟风向"));
    }
    if( lb_Wind_Spd == nullptr){
        lb_Wind_Spd = new QLabel(QStringLiteral("风速:"));
        lb_Wind_Spd->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Wind_Spd->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Wind_Spd->setToolTip(QStringLiteral("模拟风速"));
    }
    if( lb_Wind_Alt == nullptr){
        lb_Wind_Alt = new QLabel(QStringLiteral("高度:"));
        lb_Wind_Alt->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Wind_Alt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Wind_Alt->setToolTip(QStringLiteral("模拟风场高度，高于此高度则与风速一直，低于此高度则逐渐减小"));
    }
    if( lb_Wind_Turb == nullptr){
        lb_Wind_Turb = new QLabel(QStringLiteral("风扰动:"));
        lb_Wind_Turb->setObjectName(QString::fromUtf8("widgetNameLabel"));
        lb_Wind_Turb->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lb_Wind_Turb->setToolTip(QStringLiteral("模拟随机风速"));
    }
    if( ds_WindDir == nullptr){
        ds_WindDir = new UDoubleSpinBox();
        ds_WindDir->setRange(0,360);
        ds_WindDir->setValue(0);
        ds_WindDir->setAlignment(Qt::AlignCenter);
        ds_WindDir->setSuffix(QStringLiteral(" °"));
        ds_WindDir->setDecimals(1);
        ds_WindDir->setToolTip(QStringLiteral("模拟风向。"));
        ds_WindDir->setChanged(true);
    }
    if( ds_Wind_Spd == nullptr){
        ds_Wind_Spd = new UDoubleSpinBox();
        ds_Wind_Spd->setRange(0,360);
        ds_Wind_Spd->setValue(0);
        ds_Wind_Spd->setAlignment(Qt::AlignCenter);
        ds_Wind_Spd->setSuffix(QStringLiteral(" m/s"));
        ds_Wind_Spd->setDecimals(1);
        ds_Wind_Spd->setToolTip(QStringLiteral("模拟风速"));
        ds_Wind_Spd->setChanged(true);
    }
    if( ds_Wind_Alt == nullptr){
        ds_Wind_Alt = new UDoubleSpinBox();
        ds_Wind_Alt->setRange(0,10000);
        ds_Wind_Alt->setValue(0);
        ds_Wind_Alt->setAlignment(Qt::AlignCenter);
        ds_Wind_Alt->setSuffix(QStringLiteral(" m"));
        ds_Wind_Alt->setDecimals(1);
        ds_Wind_Alt->setToolTip(QStringLiteral("模拟风场高度，高于此高度则与风速一直，低于此高度则逐渐减小"));
        ds_Wind_Alt->setChanged(true);
    }
    if( ds_Wind_Turb == nullptr){
        ds_Wind_Turb = new UDoubleSpinBox();
        ds_Wind_Turb->setRange(0,4);
        ds_Wind_Turb->setValue(0);
        ds_Wind_Turb->setAlignment(Qt::AlignCenter);
        ds_Wind_Turb->setSuffix(QStringLiteral(" "));
        ds_Wind_Turb->setDecimals(1);
        ds_Wind_Turb->setToolTip(QStringLiteral("模拟随机风"));
        ds_Wind_Turb->setChanged(true);
    }

    if( Group_Wind == nullptr){
        Group_Wind = new QGroupBox(QStringLiteral("模拟风场"));
        Group_Wind->setObjectName("widgetGroupBox");
        Group_Wind->setAlignment(Qt::AlignCenter);
    }

    if( Layout_Wind == nullptr){
        Layout_Wind = new QGridLayout(Group_Wind);
        Layout_Wind->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    Layout_Wind->addWidget(lb_WindDir,0,0,1,1,Qt::AlignRight|Qt::AlignVCenter);
    Layout_Wind->addWidget(lb_Wind_Spd,1,0,1,1,Qt::AlignRight|Qt::AlignVCenter);
    Layout_Wind->addWidget(lb_Wind_Turb,2,0,1,1,Qt::AlignRight|Qt::AlignVCenter);
    Layout_Wind->addWidget(lb_Wind_Alt,3,0,1,1,Qt::AlignRight|Qt::AlignVCenter);

    Layout_Wind->addWidget(ds_WindDir,0,1,1,1);//Qt::AlignRight|Qt::AlignVCenter);
    Layout_Wind->addWidget(ds_Wind_Spd,1,1,1,1);//Qt::AlignRight|Qt::AlignVCenter);
    Layout_Wind->addWidget(ds_Wind_Turb,2,1,1,1);//Qt::AlignRight|Qt::AlignVCenter);
    Layout_Wind->addWidget(ds_Wind_Alt,3,1,1,1);//Qt::AlignRight|Qt::AlignVCenter);

    /* GPS RC Failsafe Simulation */
    if( Group_fail == nullptr){
        Group_fail = new QGroupBox(QStringLiteral("故障模拟"));
        Group_fail->setObjectName("widgetGroupBox");
        Group_fail->setAlignment(Qt::AlignCenter);
    }

    if( Layout_fail == nullptr){
        Layout_fail = new QGridLayout(Group_fail);
        Layout_fail->setObjectName(QString::fromUtf8("widgetLayout"));
    }
    if( ds_GPSDisable == nullptr){
        ds_GPSDisable = new UCheckBox();
        ds_GPSDisable->setText(QStringLiteral("GPS故障模拟"));
        ds_GPSDisable->setToolTip(QStringLiteral("GPS故障模拟。"));
    }
    if( SIM_RC_FAIL == nullptr){
        SIM_RC_FAIL = new UCheckBox();
        SIM_RC_FAIL->setText(QStringLiteral("RC故障模拟"));
        SIM_RC_FAIL->setToolTip(QStringLiteral("RC故障模拟。"));
    }

    Layout_fail->addWidget(ds_GPSDisable,0,1,1,1);//Qt::AlignRight|Qt::AlignVCenter);
    Layout_fail->addWidget(SIM_RC_FAIL,1,1,1,1);//Qt::AlignRight|Qt::AlignVCenter);

    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("widgetButton"));
        PB_download->setToolTip(QStringLiteral(""));
    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("widgetButton"));
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

    widgetLayout->addWidget(titleLabel , 0, 0, 1, 10);
    widgetLayout->addWidget(OpenSIM , 0, 9, 1, 1,Qt::AlignCenter);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 1);
    widgetLayout->addWidget(Group_Postion , 2, 0, 1, 1);
    widgetLayout->addWidget(Group_Wind , 2, 1, 1, 1);
    widgetLayout->addWidget(Group_fail , 2, 2, 1, 1);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 3, 0, 1, 1);
    widgetLayout->addLayout(widgetLayout_pb , 4, 0, 1, 10);
    for(int i = 0 ; i < 10;i++){
        this->widgetLayout->setColumnStretch(i,1);
    }
    this->setLayout(widgetLayout);
}

void SIM_CFG::showEvent(QShowEvent *event)
{
//    update_value();
    QWidget::showEvent(event);
}

void SIM_CFG::handle_DMMM_event(int ev, int linkid)
{
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetCommonParameter:
        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        case Q_DMMM::DMMM_GCSEvent_NewVehicleType:
        {
            if(this->isVisible()){
                update_value();
            }
        }break;
        case Q_DMMM::DMMM_GCSEvent_DeviceOpenFailed:
        {
            if(linkid == FlightGearLinkID){
                flightgear->Close();
                this->OpenSIM->setText(QStringLiteral("开启仿真"));
            }
        }break;

        default:break;
    }
}

void SIM_CFG::handle_OpenSIM()
{
    if(flightgear!=nullptr){
        if(flightgear->getE_DeviceState() != DeviceCommunication::DeviceState_Connect){
            flightgear->Open();
            this->OpenSIM->setText(QStringLiteral("关闭仿真"));
        }else{
            flightgear->Close();
            this->OpenSIM->setText(QStringLiteral("开启仿真"));
        }
    }
}

void SIM_CFG::update_value(bool getfromflight)
{
    qDebug()<<"update_value"<<getfromflight;
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        float val = 0;
        /* Init Postion */
        // Alt;

        if(link->ParamGetValue_ByName("SIM_OPOS_ALT",val,getfromflight)){
            this->ds_Pos_Alt->SetNewValue(val);
        }

        // lat;
        if(link->ParamGetValue_ByName("SIM_OPOS_LAT",val,getfromflight)){
            this->ds_Pos_Lat->SetNewValue(val);
        }
        // lng;
        if(link->ParamGetValue_ByName("SIM_OPOS_LNG",val,getfromflight)){
            this->ds_Pos_Lng->SetNewValue(val);
        }

        if(link->ParamGetValue_ByName("SIM_OPOS_HDG",val,getfromflight)){
            this->ds_Pos_Heading->SetNewValue(val);
        }

        /* Wind Parameters */
        if(link->ParamGetValue_ByName("SIM_WIND_DIR",val,getfromflight)){
            this->ds_WindDir->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("SIM_WIND_SPD",val,getfromflight)){
            this->ds_Wind_Spd->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("SIM_WIND_TURB",val,getfromflight)){
            this->ds_Wind_Turb->SetNewValue(val);
        }
        if(link->ParamGetValue_ByName("SIM_WIND_T_ALT",val,getfromflight)){
            this->ds_Wind_Alt->SetNewValue(val);
        }
        /* gps rc failsafe simulation */
        if(link->ParamGetValue_ByName("SIM_GPS_DISABLE",val,getfromflight)){
            int state = val;
            this->ds_GPSDisable->setNewChecked(state?true:false);
        }

        if(link->ParamGetValue_ByName("SIM_RC_FAIL",val,getfromflight)){
            int state = val;
            this->SIM_RC_FAIL->setNewChecked(state?true:false);
        }
    }
}

void SIM_CFG::Upload_Parameters()
{

    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr)return;
    /* Init Postion */
    if(this->ds_Pos_Alt->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_OPOS_ALT",this->ds_Pos_Alt->value());
    }
    if(this->ds_Pos_Lat->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_OPOS_LAT",this->ds_Pos_Lat->value());
    }
    if(this->ds_Pos_Lng->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_OPOS_LNG",this->ds_Pos_Lng->value());
    }
    if(this->ds_Pos_Heading->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_OPOS_HDG",this->ds_Pos_Heading->value());
    }
    /* Wind Parameters */
    if(this->ds_WindDir->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_WIND_DIR",this->ds_WindDir->value());
    }
    if(this->ds_Wind_Spd->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_WIND_SPD",this->ds_Wind_Spd->value());
    }
    if(this->ds_Wind_Turb->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_WIND_TURB",this->ds_Wind_Turb->value());
    }
    if(this->ds_Wind_Alt->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_WIND_T_ALT",this->ds_Wind_Alt->value());
    }
    /* gps rc failsafe simulation */
    if(this->ds_GPSDisable->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_GPS_DISABLE",this->ds_GPSDisable->checkState()?1:0);
    }
    if(this->SIM_RC_FAIL->IsChanged()){
        link->ParamSetToFlight_ByName("SIM_RC_FAIL",this->SIM_RC_FAIL->checkState()?1:0);
    }
}
