#ifndef SYS_STATUS_SIDEBAR_H__
#define SYS_STATUS_SIDEBAR_H__

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <ledlabel.h>
#include <QDebug>
#include "lightbutton.h"

class SideBarSysStatus : public QObject
{
    Q_OBJECT
public:
    explicit SideBarSysStatus(QObject *parent = nullptr);
signals:

private:
    QGridLayout *widgetLayout = nullptr;

    QLabel* lb_name_SENSOR_3D_GYRO                   = nullptr;
    QLabel* lb_name_SENSOR_3D_ACCEL                  = nullptr;
    QLabel* lb_name_SENSOR_3D_MAG                    = nullptr;
    QLabel* lb_name_SENSOR_ABSOLUTE_PRESSURE         = nullptr;
    QLabel* lb_name_SENSOR_DIFFERENTIAL_PRESSURE     = nullptr;
    QLabel* lb_name_SENSOR_GPS                       = nullptr;
    QLabel* lb_name_SENSOR_OPTICAL_FLOW              = nullptr;
    QLabel* lb_name_SENSOR_VISION_POSITION           = nullptr;
    QLabel* lb_name_SENSOR_LASER_POSITION            = nullptr;
    QLabel* lb_name_SENSOR_EXTERNAL_GROUND_TRUTH     = nullptr;
    QLabel* lb_name_SENSOR_ANGULAR_RATE_CONTROL      = nullptr;
    QLabel* lb_name_SENSOR_ATTITUDE_STABILIZATION    = nullptr;
    QLabel* lb_name_SENSOR_YAW_POSITION              = nullptr;
    QLabel* lb_name_SENSOR_Z_ALTITUDE_CONTROL        = nullptr;
    QLabel* lb_name_SENSOR_XY_POSITION_CONTROL       = nullptr;
    QLabel* lb_name_SENSOR_MOTOR_OUTPUTS             = nullptr;
    QLabel* lb_name_SENSOR_RC_RECEIVER               = nullptr;
    QLabel* lb_name_SENSOR_3D_GYRO2                  = nullptr;
    QLabel* lb_name_SENSOR_3D_ACCEL2                 = nullptr;
    QLabel* lb_name_SENSOR_3D_MAG2                   = nullptr;
    QLabel* lb_name_GEOFENCE                         = nullptr;
    QLabel* lb_name_AHRS                             = nullptr;
    QLabel* lb_name_TERRAIN                          = nullptr;
    QLabel* lb_name_REVERSE_MOTOR                    = nullptr;
    QLabel* lb_name_LOGGING                          = nullptr;
    QLabel* lb_name_SENSOR_BATTERY                   = nullptr;
    QLabel* lb_name_SENSOR_PROXIMITY                 = nullptr;
    QLabel* lb_name_SENSOR_SATCOM                    = nullptr;
    QLabel* lb_name_PREARM_CHECK                     = nullptr;
    QLabel* lb_name_OBSTACLE_AVOIDANCE               = nullptr;
    QLabel* lb_name_SENSOR_PROPULSION                = nullptr;


    LightButton* Icon_SENSOR_3D_GYRO                   = nullptr;
    LightButton* Icon_SENSOR_3D_ACCEL                  = nullptr;
    LightButton* Icon_SENSOR_3D_MAG                    = nullptr;
    LightButton* Icon_SENSOR_ABSOLUTE_PRESSURE         = nullptr;
    LightButton* Icon_SENSOR_DIFFERENTIAL_PRESSURE     = nullptr;
    LightButton* Icon_SENSOR_GPS                       = nullptr;
    LightButton* Icon_SENSOR_MOTOR_OUTPUTS             = nullptr;
    LightButton* Icon_SENSOR_BATTERY                   = nullptr;


    LightButton* Icon_SENSOR_RC_RECEIVER               = nullptr;
    LightButton* Icon_AHRS                             = nullptr;
    LightButton* Icon_LOGGING                          = nullptr;


    LightButton* Icon_SENSOR_OPTICAL_FLOW              = nullptr;
    LightButton* Icon_SENSOR_VISION_POSITION           = nullptr;
    LightButton* Icon_SENSOR_LASER_POSITION            = nullptr;
    LightButton* Icon_SENSOR_EXTERNAL_GROUND_TRUTH     = nullptr;

    LightButton* Icon_PREARM_CHECK                     = nullptr;
    LightButton* Icon_SENSOR_ANGULAR_RATE_CONTROL      = nullptr;
    LightButton* Icon_SENSOR_ATTITUDE_STABILIZATION    = nullptr;
    LightButton* Icon_SENSOR_YAW_POSITION              = nullptr;
    LightButton* Icon_SENSOR_Z_ALTITUDE_CONTROL        = nullptr;
    LightButton* Icon_SENSOR_XY_POSITION_CONTROL       = nullptr;
    LightButton* Icon_SENSOR_3D_GYRO2                  = nullptr;
    LightButton* Icon_SENSOR_3D_ACCEL2                 = nullptr;
    LightButton* Icon_SENSOR_3D_MAG2                   = nullptr;
    LightButton* Icon_GEOFENCE                         = nullptr;
    LightButton* Icon_TERRAIN                          = nullptr;
    LightButton* Icon_REVERSE_MOTOR                    = nullptr;
    LightButton* Icon_SENSOR_PROXIMITY                 = nullptr;
    LightButton* Icon_SENSOR_SATCOM                    = nullptr;
    LightButton* Icon_OBSTACLE_AVOIDANCE               = nullptr;
    LightButton* Icon_SENSOR_PROPULSION                = nullptr;



    LightButton* Icon_Link                      = nullptr;
    QLabel* lb_name_Link                        = nullptr;

    LightButton* Icon_vibration                      = nullptr;
    QLabel* lb_name_vibration                        = nullptr;

    void widget_init();

    void update_state(uint32_t present,uint32_t enable,uint32_t health);
    void update();

    static void update_statebyflags(LightButton* lg,uint32_t present,uint32_t enable,uint32_t health,uint32_t flags);
    static void update_health(uint32_t &health, bool healthstate, uint32_t flags);
public:
    QGridLayout *getWidgetLayout() const;

private slots:
    void handle_DMMM_event(int ev, int linkid);
};

#endif // POWERDESIGNER_H
