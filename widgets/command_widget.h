#ifndef COMMAND_WIDGET_H
#define COMMAND_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QFile>
#include <QPushButton>
#include <QGroupBox>
#include "DMMM.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
class MissionWidget:public QWidget
{
    Q_OBJECT
public:
    MissionWidget(QWidget *parent = nullptr);
private:
    /* 电机解锁 */
    QGridLayout* mainlayout = nullptr;
    QGroupBox*   group = nullptr;
    QGridLayout *gridLayout = nullptr;

    QPushButton* pb_start_mission = nullptr;
    QPushButton* pb_restart_mission = nullptr;
    QPushButton* pb_change_mission_item = nullptr;

    QSpinBox* item_id = nullptr;


    void connectSignalAndSlot();
    void widget_init();

private slots:
    void do_start_mission();
    void do_restart_mission();
    void do_change_mission_item();
};


class GuidedNavWidget:public QWidget
{
    Q_OBJECT
public:
    GuidedNavWidget(QWidget *parent = nullptr);
public:signals:
    void req_gis_loc();
private:
    /* 电机解锁 */
    QGridLayout* mainlayout = nullptr;
    QGroupBox*   group = nullptr;
    QGridLayout *gridLayout = nullptr;

    QPushButton* pb_set_wp = nullptr;
    QPushButton* pb_get_current_loc = nullptr;
    QPushButton* pb_get_fromgis = nullptr;
    QLabel*         lb_lat = nullptr;;
    QLabel*         lb_lng = nullptr;;
    QDoubleSpinBox* val_alt_m = nullptr;
    QDoubleSpinBox* val_lat = nullptr;
    QDoubleSpinBox* val_lng = nullptr;
    QComboBox*      cb_alt_frame = nullptr;

    void connectSignalAndSlot();
    void widget_init();

private slots:
    void set_guided_nav();
    void get_cureent_loc();
    void request_from_gis();
public slots:
    void get_gis_loc(const double &lat,const double &lng);
};

class SetWidget:public QWidget
{
    Q_OBJECT
public:
    SetWidget(QWidget *parent = nullptr);
private slots:
    void do_setAlt();
    void do_setHeading();
private:
    /* 电机解锁 */
    QGridLayout* mainlayout = nullptr;
    QPushButton* pb_setAlt=nullptr;
    QDoubleSpinBox* val_alt_m = nullptr;
    QPushButton* pb_setheading=nullptr;
    QDoubleSpinBox* val_heading = nullptr;
    QGroupBox*   group = nullptr;
    QGridLayout *gridLayout = nullptr;

    void connectSignalAndSlot();
    void widget_init();
};

class SysOptionWidget:public QWidget
{
    Q_OBJECT
public:
    SysOptionWidget(QWidget *parent = nullptr);
private slots:
    void do_factory();
    void do_reboot();
private:
    /* 电机解锁 */
    QGridLayout* mainlayout = nullptr;
    QPushButton* pb_setfactory=nullptr;
    QPushButton* pb_setreboot=nullptr;
    QGroupBox*   group = nullptr;
    QGridLayout *gridLayout = nullptr;

    void connectSignalAndSlot();
    void widget_init();
};

class TakeoffWidget:public QWidget
{
    Q_OBJECT

public:
    TakeoffWidget(QWidget *parent = nullptr);
private slots:
    void do_takeoff();
private:
    /* 设置高度 */
    QGridLayout* mainlayout = nullptr;
    QPushButton* pb_takeoff=nullptr;
    QDoubleSpinBox* val_alt_m = nullptr;
    QGroupBox*   group = nullptr;
    QGridLayout *gridLayout = nullptr;

    void connectSignalAndSlot();
    void widget_init();
};

class MotorsArmWidget:public QWidget
{
    Q_OBJECT

public:
    MotorsArmWidget(QWidget *parent = nullptr);
private slots:
    void set_motors_arm(){set_motors(FlyLink::ARM_MOTERS);}
    void set_motors_force_arm(){set_motors(FlyLink::ARM_MOTERS_FORCE);}
    void set_motors_disarm(){set_motors(FlyLink::DISARM_MOTORS);}
    void set_motors_force_disarm(){set_motors(FlyLink::DISARM_MOTORS_FORCE);}
private:
    /* 电机解锁 */
    QGridLayout* mainlayout = nullptr;
    QPushButton* pb_arm=nullptr;
    QPushButton* pb_force_arm=nullptr;
    QPushButton* pb_disarm=nullptr;
    QPushButton* pb_force_disarm=nullptr;
    QGroupBox*   group_arm = nullptr;
    QGridLayout *gridLayout = nullptr;

    void set_motors(uint8_t mode);
    void connectSignalAndSlot();
    void widget_init();
};

class SetMode_Widget : public QWidget
{
    Q_OBJECT

public :
    SetMode_Widget(QWidget *parent = nullptr);
public slots:
    void slot_set_mode_stabilize(){set_mode(FlyLink::STABILIZE);}
    void slot_set_mode_alt_hold()    {set_mode(FlyLink::ALT_HOLD);}
    void slot_set_mode_loiter(){set_mode(FlyLink::LOITER);}
    void slot_set_mode_poshold(){set_mode(FlyLink::POSHOLD);}
//    void slot_set_mode_guided(){set_mode(FlyLink::GUIDED);}
    void slot_set_mode_rtl(){set_mode(FlyLink::RTL);}
    void slot_set_mode_smart_rtl(){set_mode(FlyLink::SMART_RTL);}
    void slot_set_mode_land(){set_mode(FlyLink::LAND);}
//    void slot_set_mode_auto(){set_mode(FlyLink::AUTO);}
    void slot_set_mode_break(){set_mode(FlyLink::BRAKE);}
    void slot_set_mode_circle(){set_mode(FlyLink::CIRCLE);}

private:
    /* 模式设置 */

    QGridLayout* mainlayout = nullptr;
    QPushButton* pb_stabilize=nullptr;
    QPushButton* pb_alt_hold=nullptr;
    QPushButton* pb_loiter=nullptr;
    QPushButton* pb_poshold=nullptr;
//    QPushButton* pb_guided=nullptr;
    QPushButton* pb_rtl=nullptr;
    QPushButton* pb_smart_rtl=nullptr;
    QPushButton* pb_land=nullptr;
//    QPushButton* pb_auto=nullptr;
    QPushButton* pb_break=nullptr;
    QPushButton* pb_circle=nullptr;
    QGroupBox*   group_setmode = nullptr;
    QGridLayout *gridLayout = nullptr;


    void connectSignalAndSlot();
    void widget_init();
    void set_mode(uint8_t mode_number);
};

class CommandWidget : public QWidget
{
    Q_OBJECT

public:
    CommandWidget(QWidget *parent = nullptr);
    GuidedNavWidget *getGuided_nav() const;

private:
    QGridLayout* mainlayout = nullptr;
    MotorsArmWidget* arm_widget = nullptr;
    SetMode_Widget* setmode_widget = nullptr;
    TakeoffWidget* takoeff_widget = nullptr;
    SetWidget*  set_widget = nullptr;
    SysOptionWidget* sysoption_widget = nullptr;
    GuidedNavWidget* guided_nav = nullptr;
    MissionWidget*   mission_widget = nullptr;
    void connectSignalAndSlot();
    void widget_init();
};


#endif // MASKWIDGET_H
