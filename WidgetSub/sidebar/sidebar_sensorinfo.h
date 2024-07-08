#ifndef STATE_DESIGNER_H
#define STATE_DESIGNER_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <ledlabel.h>
#include <QDebug>
#include "lightbutton.h"

class SideBarSensorInfo : public QObject
{
    Q_OBJECT
public:
    explicit SideBarSensorInfo(QObject *parent = nullptr);
signals:

private:
    QGridLayout *widgetLayout = nullptr;

    QLabel* lb_name_check_ok = nullptr;
    QLabel* lb_name_gnss_ok = nullptr;
    QLabel* lb_name_link_ok = nullptr;
    QLabel* lb_name_compass_ok = nullptr;
    QLabel* lb_name_rc_ok = nullptr;
    QLabel* lb_name_vibration_ok = nullptr;
    QLabel* lb_name_ahrs_ok = nullptr;

    QLabel* lb_name_acc_ok = nullptr;
    QLabel* lb_name_gyro_ok = nullptr;
    QLabel* lb_name_baro_ok = nullptr;
    QLabel* lb_name_airspeed_ok = nullptr;
    QLabel* lb_name_motor_ok = nullptr;
    QLabel* lb_name_datalog_ok = nullptr;
    QLabel* lb_name_power_ok = nullptr;

    LightButton* lb_ico_acc_ok = nullptr;
    LightButton* lb_ico_gyro_ok = nullptr;
    LightButton* lb_ico_baro_ok = nullptr;
    LightButton* lb_ico_airspeed_ok = nullptr;
    LightButton* lb_ico_motor_ok = nullptr;
    LightButton* lb_ico_datalog_ok = nullptr;
    LightButton* lb_ico_power_ok = nullptr;
    LightButton* lb_ico_check_ok = nullptr;
    LightButton* lb_ico_gnss_ok = nullptr;
    LightButton* lb_ico_link_ok = nullptr;
    LightButton* lb_ico_compass_ok = nullptr;
    LightButton* lb_ico_rc_ok = nullptr;
    LightButton* lb_ico_vibration_ok = nullptr;
    LightButton* lb_ico_ahrs_ok = nullptr;


    void widget_init();
    void update_state();
public:
    void update_state1(bool chk = false,
                      bool gnss = false,
                      bool link = false,
                      bool compass = false,
                      bool rc = false,
                      bool vibration = false,
                      bool ahrs = false,
                      bool acc = false,
                      bool gyro = false,
                      bool airspeed = false,
                      bool baro = false,
                      bool motor = false,
                      bool datalog = false);
    QGridLayout *getWidgetLayout() const;
private slots:
    void handle_DMMM_event(int ev, int linkid);
};

#endif // POWERDESIGNER_H
