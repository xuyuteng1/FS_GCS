#include "sidebar_sensorinfo.h"
#include "DMMM.h"
SideBarSensorInfo::SideBarSensorInfo(QObject *parent)
    : QObject{parent}
{
    widget_init();
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&SideBarSensorInfo::handle_DMMM_event);
}

QGridLayout *SideBarSensorInfo::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarSensorInfo::widget_init()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->lb_name_check_ok == nullptr){
        this->lb_name_check_ok = new QLabel(QStringLiteral("安全"));
        this->lb_name_check_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_check_ok->setAlignment(Qt::AlignCenter);
    }

    if(this->lb_name_gnss_ok == nullptr){
        this->lb_name_gnss_ok = new QLabel(QStringLiteral("卫星"));
        this->lb_name_gnss_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_gnss_ok->setAlignment(Qt::AlignCenter);
    }

    if(this->lb_name_link_ok == nullptr){
        this->lb_name_link_ok = new QLabel(QStringLiteral("通讯"));
        this->lb_name_link_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_link_ok->setAlignment(Qt::AlignCenter);
    }
    if(this->lb_name_compass_ok == nullptr){
        this->lb_name_compass_ok = new QLabel(QStringLiteral("罗盘"));
        this->lb_name_compass_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_compass_ok->setAlignment(Qt::AlignCenter);
    }
    if(this->lb_name_rc_ok == nullptr){
        this->lb_name_rc_ok = new QLabel(QStringLiteral("遥控"));
        this->lb_name_rc_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_rc_ok->setAlignment(Qt::AlignCenter);
    }
    if(this->lb_name_vibration_ok == nullptr){
        this->lb_name_vibration_ok = new QLabel(QStringLiteral("震动"));
        this->lb_name_vibration_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_vibration_ok->setAlignment(Qt::AlignCenter);
    }
    if(this->lb_name_ahrs_ok == nullptr){
        this->lb_name_ahrs_ok = new QLabel(QStringLiteral("航姿"));
        this->lb_name_ahrs_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_ahrs_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_acc_ok == nullptr){
        this->lb_name_acc_ok = new QLabel(QStringLiteral("加计"));
        this->lb_name_acc_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_acc_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_gyro_ok == nullptr){
        this->lb_name_gyro_ok = new QLabel(QStringLiteral("陀螺"));
        this->lb_name_gyro_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_gyro_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_baro_ok == nullptr){
        this->lb_name_baro_ok = new QLabel(QStringLiteral("气压"));
        this->lb_name_baro_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_baro_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_airspeed_ok == nullptr){
        this->lb_name_airspeed_ok = new QLabel(QStringLiteral("空速"));
        this->lb_name_airspeed_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_airspeed_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_motor_ok == nullptr){
        this->lb_name_motor_ok = new QLabel(QStringLiteral("输出"));
        this->lb_name_motor_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_motor_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_datalog_ok == nullptr){
        this->lb_name_datalog_ok = new QLabel(QStringLiteral("日志"));
        this->lb_name_datalog_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_datalog_ok->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_power_ok == nullptr){
        this->lb_name_power_ok = new QLabel(QStringLiteral("供电"));
        this->lb_name_power_ok->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_power_ok->setAlignment(Qt::AlignCenter);
    }


    if( this->lb_ico_acc_ok == nullptr){
        this->lb_ico_acc_ok = new LightButton();
        this->lb_ico_acc_ok->setFixedSize(25,25);
    }
    if( this->lb_ico_gyro_ok == nullptr){
        this->lb_ico_gyro_ok = new LightButton();
        this->lb_ico_gyro_ok->setFixedSize(25,25);
    }
    if( this->lb_ico_baro_ok == nullptr){
        this->lb_ico_baro_ok = new LightButton();
        this->lb_ico_baro_ok->setFixedSize(25,25);
    }
    if( this->lb_ico_airspeed_ok == nullptr){
        this->lb_ico_airspeed_ok = new LightButton();
        this->lb_ico_airspeed_ok->setFixedSize(25,25);
    }
    if( this->lb_ico_motor_ok == nullptr){
        this->lb_ico_motor_ok = new LightButton();
        this->lb_ico_motor_ok->setFixedSize(25,25);
    }
    if( this->lb_ico_datalog_ok == nullptr){
        this->lb_ico_datalog_ok = new LightButton();
        this->lb_ico_datalog_ok->setFixedSize(25,25);
    }
    if( this->lb_ico_power_ok == nullptr){
        this->lb_ico_power_ok = new LightButton();
        this->lb_ico_power_ok->setFixedSize(25,25);
    }


    if(this->lb_ico_check_ok == nullptr){
        this->lb_ico_check_ok = new LightButton();
        this->lb_ico_check_ok->setFixedSize(45,45);
        this->lb_ico_check_ok->setToolTip(QStringLiteral("解锁条件满足指示"));
    }

    if(this->lb_ico_gnss_ok == nullptr){
        this->lb_ico_gnss_ok = new LightButton();
        this->lb_ico_gnss_ok->setFixedSize(25,25);
    }


    if(this->lb_ico_link_ok == nullptr){
        this->lb_ico_link_ok = new LightButton();
        this->lb_ico_link_ok->setFixedSize(25,25);
    }


    if(this->lb_ico_compass_ok == nullptr){
        this->lb_ico_compass_ok = new LightButton();
        this->lb_ico_compass_ok->setFixedSize(25,25);
    }

    if(this->lb_ico_rc_ok == nullptr){
        this->lb_ico_rc_ok = new LightButton();
        this->lb_ico_rc_ok->setFixedSize(25,25);
    }

    if(this->lb_ico_vibration_ok == nullptr){
        this->lb_ico_vibration_ok = new LightButton();
        this->lb_ico_vibration_ok->setFixedSize(25,25);
    }

    if(this->lb_ico_ahrs_ok == nullptr){
        this->lb_ico_ahrs_ok = new LightButton();
        this->lb_ico_ahrs_ok->setFixedSize(25,25);
    }


    this->widgetLayout->addWidget(lb_ico_check_ok,0,0,4,1,Qt::AlignCenter);

    this->widgetLayout->addWidget(lb_ico_gnss_ok        ,0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_link_ok        ,0,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_rc_ok          ,0,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_vibration_ok   ,0,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_ahrs_ok        ,0,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_motor_ok       ,0,6,1,1,Qt::AlignCenter);

    this->widgetLayout->addWidget(lb_ico_acc_ok     ,2,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_gyro_ok    ,2,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_compass_ok ,2,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_baro_ok    ,2,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_airspeed_ok,2,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_ico_datalog_ok ,2,6,1,1,Qt::AlignCenter);

    this->widgetLayout->addWidget(lb_name_gnss_ok        ,1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_link_ok        ,1,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_rc_ok          ,1,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_vibration_ok   ,1,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_ahrs_ok        ,1,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_motor_ok       ,1,6,1,1,Qt::AlignCenter);

    this->widgetLayout->addWidget(lb_name_acc_ok     ,3,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_gyro_ok    ,3,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_compass_ok ,3,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_baro_ok    ,3,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_airspeed_ok,3,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget(lb_name_datalog_ok ,3,6,1,1,Qt::AlignCenter);

    this->widgetLayout->setMargin(3);
    this->widgetLayout->setColumnStretch(0,5);
    this->widgetLayout->setColumnStretch(1,5);
    this->widgetLayout->setColumnStretch(2,5);
    this->widgetLayout->setColumnStretch(3,5);
    this->widgetLayout->setColumnStretch(4,5);
    this->widgetLayout->setColumnStretch(5,5);
    this->widgetLayout->setColumnStretch(6,5);

}

void SideBarSensorInfo::update_state1(bool chk,
                                     bool gnss,
                                     bool link,
                                     bool compass,
                                     bool rc,
                                     bool vibration,
                                     bool ahrs ,
                                     bool acc,
                                     bool gyro,
                                     bool airspeed ,
                                     bool baro ,
                                     bool motor,
                                     bool datalog)
{
    chk?this->lb_ico_check_ok->setGreen():this->lb_ico_check_ok->setRed();
    gnss?this->lb_ico_gnss_ok->setGreen():this->lb_ico_gnss_ok->setRed();
    link?this->lb_ico_link_ok->setGreen():this->lb_ico_link_ok->setRed();
    compass?this->lb_ico_compass_ok->setGreen():this->lb_ico_compass_ok->setRed();
    rc?this->lb_ico_rc_ok->setGreen():this->lb_ico_rc_ok->setRed();
    ahrs?this->lb_ico_ahrs_ok->setGreen():this->lb_ico_ahrs_ok->setRed();
    vibration?this->lb_ico_vibration_ok->setGreen():this->lb_ico_vibration_ok->setRed();
    acc?this->lb_ico_acc_ok->setGreen():this->lb_ico_acc_ok->setRed();
    gyro?this->lb_ico_gyro_ok->setGreen():this->lb_ico_gyro_ok->setRed();



    airspeed?this->lb_ico_airspeed_ok->setGreen():this->lb_ico_airspeed_ok->setRed();
    baro?this->lb_ico_baro_ok->setGreen():this->lb_ico_baro_ok->setRed();
    motor?this->lb_ico_motor_ok->setGreen():this->lb_ico_motor_ok->setRed();
    datalog?this->lb_ico_datalog_ok->setGreen():this->lb_ico_datalog_ok->setRed();
}


void SideBarSensorInfo::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
    {
        update_state();
    }break;
    default:break;
    }
}


void SideBarSensorInfo::update_state()
{
    Q_DMMM* flight = Qt::DMMM();
    if(flight == nullptr){
        return;
    }

    Q_DMMM::DataPool_t data = flight->getData_main();
    bool link_ok = false;
    if(flight->getFlyLink_main() != nullptr){
        link_ok = flight->getFlyLink_main()->getIs_active();
    }


    if(link_ok){
        this->update_state1(data.flylink.tSysInfo.sensor_state.state.arm_check,
                                    data.flylink.tSysInfo.sensor_state.state.GNSS,
                                    link_ok,
                                    data.flylink.tSysInfo.sensor_state.state.mag,
                                    data.flylink.tSysInfo.sensor_state.state.RC,
                                    data.flylink.tSysInfo.sensor_state.state.vibration,
                                    data.flylink.tSysInfo.sensor_state.state.AHRS,
                                    data.flylink.tSysInfo.sensor_state.state.acc,
                                    data.flylink.tSysInfo.sensor_state.state.gyro,
                                    data.flylink.tSysInfo.sensor_state.state.airspeed,
                                    data.flylink.tSysInfo.sensor_state.state.baro,
                                    data.flylink.tSysInfo.sensor_state.state.motor,
                                    data.flylink.tSysInfo.sensor_state.state.datalog
                                    );
    }
    else{
        this->update_state1(
                                    false,
                                    false,
                                    false,
                                    false,
                                    false,
                                    false,
                                    false
                                    );
    }
}
