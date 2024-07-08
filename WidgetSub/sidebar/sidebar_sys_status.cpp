#include "sidebar_sys_status.h"
#include "DMMM.h"
SideBarSysStatus::SideBarSysStatus(QObject *parent)
    : QObject{parent}
{
    widget_init();
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&SideBarSysStatus::handle_DMMM_event);
    this->update_state(0xffffffff,\
                       0xffffffff,\
                       0);
}

QGridLayout *SideBarSysStatus::getWidgetLayout() const
{
    return widgetLayout;
}

void SideBarSysStatus::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件

    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
    {
        update();
    }break;
    default:break;
    }
}

void SideBarSysStatus::widget_init()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if( this->lb_name_SENSOR_3D_GYRO == nullptr){
        this->lb_name_SENSOR_3D_GYRO = new QLabel(QStringLiteral("陀螺"));
        this->lb_name_SENSOR_3D_GYRO->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_3D_GYRO->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_3D_ACCEL == nullptr){
        this->lb_name_SENSOR_3D_ACCEL = new QLabel(QStringLiteral("加计"));
        this->lb_name_SENSOR_3D_ACCEL->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_3D_ACCEL->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_3D_MAG == nullptr){
        this->lb_name_SENSOR_3D_MAG = new QLabel(QStringLiteral("罗盘"));
        this->lb_name_SENSOR_3D_MAG->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_3D_MAG->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_ABSOLUTE_PRESSURE == nullptr){
        this->lb_name_SENSOR_ABSOLUTE_PRESSURE = new QLabel(QStringLiteral("气压"));
        this->lb_name_SENSOR_ABSOLUTE_PRESSURE->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_ABSOLUTE_PRESSURE->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_DIFFERENTIAL_PRESSURE == nullptr){
        this->lb_name_SENSOR_DIFFERENTIAL_PRESSURE = new QLabel(QStringLiteral("空速"));
        this->lb_name_SENSOR_DIFFERENTIAL_PRESSURE->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_DIFFERENTIAL_PRESSURE->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_GPS == nullptr){
        this->lb_name_SENSOR_GPS = new QLabel(QStringLiteral("卫星"));
        this->lb_name_SENSOR_GPS->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_GPS->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_VISION_POSITION == nullptr){
        this->lb_name_SENSOR_VISION_POSITION = new QLabel(QStringLiteral("视觉定位"));
        this->lb_name_SENSOR_VISION_POSITION->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_VISION_POSITION->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_LASER_POSITION == nullptr){
        this->lb_name_SENSOR_LASER_POSITION = new QLabel(QStringLiteral("激光定位"));
        this->lb_name_SENSOR_LASER_POSITION->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_LASER_POSITION->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_EXTERNAL_GROUND_TRUTH == nullptr){
        this->lb_name_SENSOR_EXTERNAL_GROUND_TRUTH = new QLabel(QStringLiteral("外部训练集"));
        this->lb_name_SENSOR_EXTERNAL_GROUND_TRUTH->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_EXTERNAL_GROUND_TRUTH->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_ANGULAR_RATE_CONTROL == nullptr){
        this->lb_name_SENSOR_ANGULAR_RATE_CONTROL = new QLabel(QStringLiteral("角速率控制"));
        this->lb_name_SENSOR_ANGULAR_RATE_CONTROL->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_ANGULAR_RATE_CONTROL->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_ATTITUDE_STABILIZATION == nullptr){
        this->lb_name_SENSOR_ATTITUDE_STABILIZATION = new QLabel(QStringLiteral("姿态控制"));
        this->lb_name_SENSOR_ATTITUDE_STABILIZATION->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_ATTITUDE_STABILIZATION->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_YAW_POSITION == nullptr){
        this->lb_name_SENSOR_YAW_POSITION = new QLabel(QStringLiteral("航向控制"));
        this->lb_name_SENSOR_YAW_POSITION->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_YAW_POSITION->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_Z_ALTITUDE_CONTROL == nullptr){
        this->lb_name_SENSOR_Z_ALTITUDE_CONTROL = new QLabel(QStringLiteral("高度控制"));
        this->lb_name_SENSOR_Z_ALTITUDE_CONTROL->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_Z_ALTITUDE_CONTROL->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_XY_POSITION_CONTROL == nullptr){
        this->lb_name_SENSOR_XY_POSITION_CONTROL = new QLabel(QStringLiteral("水平位置控制"));
        this->lb_name_SENSOR_XY_POSITION_CONTROL->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_XY_POSITION_CONTROL->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_MOTOR_OUTPUTS == nullptr){
        this->lb_name_SENSOR_MOTOR_OUTPUTS = new QLabel(QStringLiteral("输出"));
        this->lb_name_SENSOR_MOTOR_OUTPUTS->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_MOTOR_OUTPUTS->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_RC_RECEIVER == nullptr){
        this->lb_name_SENSOR_RC_RECEIVER = new QLabel(QStringLiteral("遥控"));
        this->lb_name_SENSOR_RC_RECEIVER->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_RC_RECEIVER->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_3D_GYRO2 == nullptr){
        this->lb_name_SENSOR_3D_GYRO2 = new QLabel(QStringLiteral("陀螺2"));
        this->lb_name_SENSOR_3D_GYRO2->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_3D_GYRO2->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_3D_ACCEL2 == nullptr){
        this->lb_name_SENSOR_3D_ACCEL2 = new QLabel(QStringLiteral("加计2"));
        this->lb_name_SENSOR_3D_ACCEL2->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_3D_ACCEL2->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_3D_MAG2 == nullptr){
        this->lb_name_SENSOR_3D_MAG2 = new QLabel(QStringLiteral("罗盘2"));
        this->lb_name_SENSOR_3D_MAG2->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_3D_MAG2->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_GEOFENCE == nullptr){
        this->lb_name_GEOFENCE = new QLabel(QStringLiteral("电子围栏"));
        this->lb_name_GEOFENCE->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_GEOFENCE->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_AHRS == nullptr){
        this->lb_name_AHRS = new QLabel(QStringLiteral("航姿"));
        this->lb_name_AHRS->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_AHRS->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_TERRAIN == nullptr){
        this->lb_name_TERRAIN = new QLabel(QStringLiteral("地形"));
        this->lb_name_TERRAIN->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_TERRAIN->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_REVERSE_MOTOR == nullptr){
        this->lb_name_REVERSE_MOTOR = new QLabel(QStringLiteral("电机反向"));
        this->lb_name_REVERSE_MOTOR->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_REVERSE_MOTOR->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_LOGGING == nullptr){
        this->lb_name_LOGGING = new QLabel(QStringLiteral("日志"));
        this->lb_name_LOGGING->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_LOGGING->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_OPTICAL_FLOW == nullptr){
        this->lb_name_SENSOR_OPTICAL_FLOW = new QLabel(QStringLiteral("光流"));
        this->lb_name_SENSOR_OPTICAL_FLOW->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_OPTICAL_FLOW->setAlignment(Qt::AlignCenter);
    }

    if( this->lb_name_SENSOR_BATTERY == nullptr){
        this->lb_name_SENSOR_BATTERY = new QLabel(QStringLiteral("电池"));
        this->lb_name_SENSOR_BATTERY->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_BATTERY->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_PROXIMITY == nullptr){
        this->lb_name_SENSOR_PROXIMITY = new QLabel(QStringLiteral("距离传感器"));
        this->lb_name_SENSOR_PROXIMITY->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_PROXIMITY->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_SATCOM == nullptr){
        this->lb_name_SENSOR_SATCOM = new QLabel(QStringLiteral("卫星通信"));
        this->lb_name_SENSOR_SATCOM->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_SATCOM->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_PREARM_CHECK == nullptr){
        this->lb_name_PREARM_CHECK = new QLabel(QStringLiteral("检查"));
        this->lb_name_PREARM_CHECK->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_PREARM_CHECK->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_OBSTACLE_AVOIDANCE == nullptr){
        this->lb_name_OBSTACLE_AVOIDANCE = new QLabel(QStringLiteral("避障"));
        this->lb_name_OBSTACLE_AVOIDANCE->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_OBSTACLE_AVOIDANCE->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_SENSOR_PROPULSION == nullptr){
        this->lb_name_SENSOR_PROPULSION = new QLabel(QStringLiteral("推进器"));
        this->lb_name_SENSOR_PROPULSION->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_SENSOR_PROPULSION->setAlignment(Qt::AlignCenter);
    }
    if( this->Icon_SENSOR_3D_GYRO              == nullptr){
        this->Icon_SENSOR_3D_GYRO = new LightButton();
        this->Icon_SENSOR_3D_GYRO->setFixedSize(25,25);
    }

    if( this->Icon_SENSOR_3D_ACCEL            == nullptr){
        this->Icon_SENSOR_3D_ACCEL = new LightButton();
        this->Icon_SENSOR_3D_ACCEL->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_3D_MAG              == nullptr){
        this->Icon_SENSOR_3D_MAG = new LightButton();
        this->Icon_SENSOR_3D_MAG->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_ABSOLUTE_PRESSURE == nullptr){
        this->Icon_SENSOR_ABSOLUTE_PRESSURE = new LightButton();
        this->Icon_SENSOR_ABSOLUTE_PRESSURE->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_DIFFERENTIAL_PRESSURE == nullptr){
        this->Icon_SENSOR_DIFFERENTIAL_PRESSURE = new LightButton();
        this->Icon_SENSOR_DIFFERENTIAL_PRESSURE->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_GPS == nullptr){
        this->Icon_SENSOR_GPS = new LightButton();
        this->Icon_SENSOR_GPS->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_OPTICAL_FLOW == nullptr){
        this->Icon_SENSOR_OPTICAL_FLOW = new LightButton();
        this->Icon_SENSOR_OPTICAL_FLOW->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_VISION_POSITION == nullptr){
        this->Icon_SENSOR_VISION_POSITION = new LightButton();
        this->Icon_SENSOR_VISION_POSITION->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_LASER_POSITION == nullptr){
        this->Icon_SENSOR_LASER_POSITION = new LightButton();
        this->Icon_SENSOR_LASER_POSITION->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_EXTERNAL_GROUND_TRUTH == nullptr){
        this->Icon_SENSOR_EXTERNAL_GROUND_TRUTH = new LightButton();
        this->Icon_SENSOR_EXTERNAL_GROUND_TRUTH->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_ANGULAR_RATE_CONTROL == nullptr){
        this->Icon_SENSOR_ANGULAR_RATE_CONTROL = new LightButton();
        this->Icon_SENSOR_ANGULAR_RATE_CONTROL->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_ATTITUDE_STABILIZATION == nullptr){
        this->Icon_SENSOR_ATTITUDE_STABILIZATION = new LightButton();
        this->Icon_SENSOR_ATTITUDE_STABILIZATION->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_YAW_POSITION == nullptr){
        this->Icon_SENSOR_YAW_POSITION = new LightButton();
        this->Icon_SENSOR_YAW_POSITION->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_Z_ALTITUDE_CONTROL == nullptr){
        this->Icon_SENSOR_Z_ALTITUDE_CONTROL = new LightButton();
        this->Icon_SENSOR_Z_ALTITUDE_CONTROL->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_XY_POSITION_CONTROL == nullptr){
        this->Icon_SENSOR_XY_POSITION_CONTROL = new LightButton();
        this->Icon_SENSOR_XY_POSITION_CONTROL->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_MOTOR_OUTPUTS == nullptr){
        this->Icon_SENSOR_MOTOR_OUTPUTS = new LightButton();
        this->Icon_SENSOR_MOTOR_OUTPUTS->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_RC_RECEIVER == nullptr){
        this->Icon_SENSOR_RC_RECEIVER = new LightButton();
        this->Icon_SENSOR_RC_RECEIVER->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_3D_GYRO2 == nullptr){
        this->Icon_SENSOR_3D_GYRO2 = new LightButton();
        this->Icon_SENSOR_3D_GYRO2->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_3D_ACCEL2 == nullptr){
        this->Icon_SENSOR_3D_ACCEL2 = new LightButton();
        this->Icon_SENSOR_3D_ACCEL2->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_3D_MAG2 == nullptr){
        this->Icon_SENSOR_3D_MAG2 = new LightButton();
        this->Icon_SENSOR_3D_MAG2->setFixedSize(25,25);
    }
    if( this->Icon_GEOFENCE == nullptr){
        this->Icon_GEOFENCE = new LightButton();
        this->Icon_GEOFENCE->setFixedSize(25,25);
    }
    if( this->Icon_AHRS == nullptr){
        this->Icon_AHRS = new LightButton();
        this->Icon_AHRS->setFixedSize(25,25);
    }
    if( this->Icon_TERRAIN == nullptr){
        this->Icon_TERRAIN = new LightButton();
        this->Icon_TERRAIN->setFixedSize(25,25);
    }
    if( this->Icon_REVERSE_MOTOR == nullptr){
        this->Icon_REVERSE_MOTOR = new LightButton();
        this->Icon_REVERSE_MOTOR->setFixedSize(25,25);
    }
    if( this->Icon_LOGGING == nullptr){
        this->Icon_LOGGING = new LightButton();
        this->Icon_LOGGING->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_BATTERY == nullptr){
        this->Icon_SENSOR_BATTERY = new LightButton();
        this->Icon_SENSOR_BATTERY->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_PROXIMITY == nullptr){
        this->Icon_SENSOR_PROXIMITY = new LightButton();
        this->Icon_SENSOR_PROXIMITY->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_SATCOM == nullptr){
        this->Icon_SENSOR_SATCOM = new LightButton();
        this->Icon_SENSOR_SATCOM->setFixedSize(25,25);
    }
    if( this->Icon_PREARM_CHECK == nullptr){
        this->Icon_PREARM_CHECK = new LightButton();
        this->Icon_PREARM_CHECK->setFixedSize(45,45);
    }
    if( this->Icon_OBSTACLE_AVOIDANCE == nullptr){
        this->Icon_OBSTACLE_AVOIDANCE = new LightButton();
        this->Icon_OBSTACLE_AVOIDANCE->setFixedSize(25,25);
    }
    if( this->Icon_SENSOR_PROPULSION == nullptr){
        this->Icon_SENSOR_PROPULSION = new LightButton();
        this->Icon_SENSOR_PROPULSION->setFixedSize(25,25);
    }


//    this->widgetLayout->addWidget( Icon_SENSOR_3D_GYRO                   ,0,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_3D_ACCEL                  ,0,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_3D_MAG                    ,0,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_ABSOLUTE_PRESSURE         ,0,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_DIFFERENTIAL_PRESSURE     ,0,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_GPS                       ,0,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_MOTOR_OUTPUTS             ,2,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_BATTERY                   ,2,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_RC_RECEIVER               ,2,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_AHRS                             ,2,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_LOGGING                          ,2,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_OPTICAL_FLOW              ,2,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_VISION_POSITION           ,4,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_LASER_POSITION            ,4,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_EXTERNAL_GROUND_TRUTH     ,4,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_PREARM_CHECK                     ,4,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_ANGULAR_RATE_CONTROL      ,4,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_ATTITUDE_STABILIZATION    ,4,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_YAW_POSITION              ,6,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_Z_ALTITUDE_CONTROL        ,6,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_XY_POSITION_CONTROL       ,6,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_3D_GYRO2                  ,6,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_3D_ACCEL2                 ,6,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_3D_MAG2                   ,6,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_GEOFENCE                         ,8,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_TERRAIN                          ,8,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_REVERSE_MOTOR                    ,8,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_PROXIMITY                 ,8,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_SATCOM                    ,8,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_OBSTACLE_AVOIDANCE               ,8,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( Icon_SENSOR_PROPULSION                ,10,1,1,1,Qt::AlignCenter);

//    this->widgetLayout->addWidget( lb_name_SENSOR_3D_GYRO                   ,0+1,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_3D_ACCEL                  ,0+1,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_3D_MAG                    ,0+1,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_ABSOLUTE_PRESSURE         ,0+1,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_DIFFERENTIAL_PRESSURE     ,0+1,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_GPS                       ,0+1,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_MOTOR_OUTPUTS             ,2+1,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_BATTERY                   ,2+1,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_RC_RECEIVER               ,2+1,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_AHRS                             ,2+1,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_LOGGING                          ,2+1,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_OPTICAL_FLOW              ,2+1,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_VISION_POSITION           ,4+1,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_LASER_POSITION            ,4+1,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_EXTERNAL_GROUND_TRUTH     ,4+1,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_PREARM_CHECK                     ,4+1,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_ANGULAR_RATE_CONTROL      ,4+1,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_ATTITUDE_STABILIZATION    ,4+1,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_YAW_POSITION              ,6+1,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_Z_ALTITUDE_CONTROL        ,6+1,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_XY_POSITION_CONTROL       ,6+1,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_3D_GYRO2                  ,6+1,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_3D_ACCEL2                 ,6+1,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_3D_MAG2                   ,6+1,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_GEOFENCE                         ,8+1,1,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_TERRAIN                          ,8+1,2,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_REVERSE_MOTOR                    ,8+1,3,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_PROXIMITY                 ,8+1,4,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_SATCOM                    ,8+1,5,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_OBSTACLE_AVOIDANCE               ,8+1,6,1,1,Qt::AlignCenter);
//    this->widgetLayout->addWidget( lb_name_SENSOR_PROPULSION                ,10+1,1,1,1,Qt::AlignCenter);


    if( this->lb_name_Link == nullptr){
        this->lb_name_Link = new QLabel(QStringLiteral("通讯"));
        this->lb_name_Link->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_Link->setAlignment(Qt::AlignCenter);
    }
    if( this->lb_name_vibration == nullptr){
        this->lb_name_vibration = new QLabel(QStringLiteral("震动"));
        this->lb_name_vibration->setObjectName("SideBarSensorInfoLabel");
        this->lb_name_vibration->setAlignment(Qt::AlignCenter);
    }
    if( this->Icon_Link              == nullptr){
        this->Icon_Link = new LightButton();
        this->Icon_Link->setFixedSize(25,25);
    }
    if( this->Icon_vibration              == nullptr){
        this->Icon_vibration = new LightButton();
        this->Icon_vibration->setFixedSize(25,25);
    }


    this->widgetLayout->addWidget( Icon_PREARM_CHECK                    ,0,0,4,1,Qt::AlignCenter);

    this->widgetLayout->addWidget( Icon_Link                            ,0,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_vibration                       ,0,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_GPS                      ,0,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_RC_RECEIVER              ,0,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_AHRS                            ,0,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_MOTOR_OUTPUTS            ,0,6,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_3D_ACCEL                 ,2,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_3D_GYRO                  ,2,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_3D_MAG                   ,2,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_ABSOLUTE_PRESSURE        ,2,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_SENSOR_DIFFERENTIAL_PRESSURE    ,2,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( Icon_LOGGING                         ,2,6,1,1,Qt::AlignCenter);


    this->widgetLayout->addWidget( lb_name_Link                            ,1,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_vibration                       ,1,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_GPS                      ,1,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_RC_RECEIVER              ,1,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_AHRS                            ,1,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_MOTOR_OUTPUTS            ,1,6,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_3D_ACCEL                 ,3,1,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_3D_GYRO                  ,3,2,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_3D_MAG                   ,3,3,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_ABSOLUTE_PRESSURE        ,3,4,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_SENSOR_DIFFERENTIAL_PRESSURE    ,3,5,1,1,Qt::AlignCenter);
    this->widgetLayout->addWidget( lb_name_LOGGING                         ,3,6,1,1,Qt::AlignCenter);

    this->widgetLayout->setMargin(3);
    this->widgetLayout->setColumnStretch(0,5);
    this->widgetLayout->setColumnStretch(1,5);
    this->widgetLayout->setColumnStretch(2,5);
    this->widgetLayout->setColumnStretch(3,5);
    this->widgetLayout->setColumnStretch(4,5);
    this->widgetLayout->setColumnStretch(5,5);
    this->widgetLayout->setColumnStretch(6,5);
//    this->widgetLayout->setRowMinimumHeight(0,25);
//    this->widgetLayout->setRowMinimumHeight(1,25);
//    this->widgetLayout->setRowMinimumHeight(2,25);
//    this->widgetLayout->setRowMinimumHeight(3,25);

}

void SideBarSysStatus::update_state(uint32_t present, uint32_t enable, uint32_t health)
{
    update_statebyflags( Icon_SENSOR_3D_GYRO               ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_3D_GYRO               );
    update_statebyflags( Icon_SENSOR_3D_ACCEL              ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_3D_ACCEL              );
    update_statebyflags( Icon_SENSOR_3D_MAG                ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_3D_MAG                );
    update_statebyflags( Icon_SENSOR_ABSOLUTE_PRESSURE     ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE     );
    update_statebyflags( Icon_SENSOR_DIFFERENTIAL_PRESSURE ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE );
    update_statebyflags( Icon_SENSOR_GPS                   ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_GPS                   );
    update_statebyflags( Icon_SENSOR_MOTOR_OUTPUTS         ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS         );
    update_statebyflags( Icon_SENSOR_BATTERY               ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_BATTERY               );
    update_statebyflags( Icon_SENSOR_RC_RECEIVER           ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_RC_RECEIVER           );
    update_statebyflags( Icon_AHRS                         ,present,enable,health,FlyLink::MAV_SYS_STATUS_AHRS                         );
    update_statebyflags( Icon_LOGGING                      ,present,enable,health,FlyLink::MAV_SYS_STATUS_LOGGING                      );
    update_statebyflags( Icon_SENSOR_OPTICAL_FLOW          ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW          );
    update_statebyflags( Icon_SENSOR_VISION_POSITION       ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_VISION_POSITION       );
    update_statebyflags( Icon_SENSOR_LASER_POSITION        ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_LASER_POSITION        );
    update_statebyflags( Icon_SENSOR_EXTERNAL_GROUND_TRUTH ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH );
    update_statebyflags( Icon_PREARM_CHECK                 ,present,enable,health,FlyLink::MAV_SYS_STATUS_PREARM_CHECK                 );
    update_statebyflags( Icon_SENSOR_ANGULAR_RATE_CONTROL  ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL  );
    update_statebyflags( Icon_SENSOR_ATTITUDE_STABILIZATION,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION);
    update_statebyflags( Icon_SENSOR_YAW_POSITION          ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_YAW_POSITION          );
    update_statebyflags( Icon_SENSOR_Z_ALTITUDE_CONTROL    ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL    );
    update_statebyflags( Icon_SENSOR_XY_POSITION_CONTROL   ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL   );
    update_statebyflags( Icon_SENSOR_3D_GYRO2              ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_3D_GYRO2              );
    update_statebyflags( Icon_SENSOR_3D_ACCEL2             ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_3D_ACCEL2             );
    update_statebyflags( Icon_SENSOR_3D_MAG2               ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_3D_MAG2               );
    update_statebyflags( Icon_GEOFENCE                     ,present,enable,health,FlyLink::MAV_SYS_STATUS_GEOFENCE                     );
    update_statebyflags( Icon_TERRAIN                      ,present,enable,health,FlyLink::MAV_SYS_STATUS_TERRAIN                      );
    update_statebyflags( Icon_REVERSE_MOTOR                ,present,enable,health,FlyLink::MAV_SYS_STATUS_REVERSE_MOTOR                );
    update_statebyflags( Icon_SENSOR_PROXIMITY             ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_PROXIMITY             );
    update_statebyflags( Icon_SENSOR_SATCOM                ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_SATCOM                );
    update_statebyflags( Icon_OBSTACLE_AVOIDANCE           ,present,enable,health,FlyLink::MAV_SYS_STATUS_OBSTACLE_AVOIDANCE           );
    update_statebyflags( Icon_SENSOR_PROPULSION            ,present,enable,health,FlyLink::MAV_SYS_STATUS_SENSOR_PROPULSION            );

}

void SideBarSysStatus::update()
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

        // 震动状态更新
        (data.flylink.tSysInfo.sensor_state.state.vibration)?this->Icon_vibration->setGreen():this->Icon_vibration->setRed();
        // 通信状态更新
        this->Icon_Link->setGreen();

        uint32_t present = data.flylink.tSysInfo.control_sensors_present;
        uint32_t enabled = data.flylink.tSysInfo.control_sensors_enabled;
        uint32_t health = data.flylink.tSysInfo.control_sensors_health;


        update_health(health, data.flylink.tSysInfo.sensor_state.state.GNSS ,       FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_GPS);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.RC,          FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_RC_RECEIVER);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.AHRS,        FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_AHRS);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.acc,         FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_3D_ACCEL);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.gyro,        FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_3D_GYRO);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.airspeed,    FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.baro,        FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.motor,       FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.datalog,     FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_LOGGING);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.mag,         FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_3D_MAG);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.power,       FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_BATTERY);
        update_health(health, data.flylink.tSysInfo.sensor_state.state.motor,       FlyLink::MAV_SYS_STATUS_SENSOR::MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS);
        this->update_state(present,enabled,health);
    }
    else{
        this->Icon_Link->setRed();
        this->Icon_vibration->setRed();
        this->update_state(0xffffffff,\
                           0xffffffff,\
                           0);
    }
}

void SideBarSysStatus::update_statebyflags(LightButton *lg, uint32_t present, uint32_t enable, uint32_t health, uint32_t flags)
{
    if(lg == nullptr) {
        return;
    }
    if( !(present & flags)){
        lg->setGray();
        return;
    }

    if(!(enable & flags)){
        lg->setYellow();
        return;
    }

    if(health & flags){
        lg->setGreen();
    }
    else{
        lg->setRed();
    }

}

void SideBarSysStatus::update_health(uint32_t &health, bool healthstate , uint32_t flags)
{
    if(healthstate){
        health |= flags;
    }else{
        health &= ~flags;
    }
}
