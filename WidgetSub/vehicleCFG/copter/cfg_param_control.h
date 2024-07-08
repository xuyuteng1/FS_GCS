/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_CONTROL___H_
#define CFG_PARAM_CONTROL___H_

#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QProgressBar>
#include "progressbarpercent.h"
#include "uComboBox.h"
#include "uSpinBox.h"
#include "uDoubleSpinBox.h"
class CFG_ParamPilotControl:public QGridLayout
{
    Q_OBJECT
public:
    CFG_ParamPilotControl(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:

    QLabel*         LB_Info                 = nullptr;
    QLabel*         LB_angle_max_cd         = nullptr;
    QLabel*         LB_pilot_speed_up_cms   = nullptr;
    QLabel*         LB_pilot_speed_dn_cms   = nullptr;
    QLabel*         LB_pilot_accel_z_cmms   = nullptr;
    QLabel*         LB_speed_cms            = nullptr;
    QLabel*         LB_accel_cmss           = nullptr;
    QLabel*         LB_brake_accel_cmss     = nullptr;
    QLabel*         LB_brake_jerk_max_cmsss = nullptr;
    QLabel*         LB_brake_delay_ms       = nullptr;

    UDoubleSpinBox* QB_angle_max_cd         = nullptr;
    UDoubleSpinBox* QB_pilot_speed_up_cms   = nullptr;
    UDoubleSpinBox* QB_pilot_speed_dn_cms   = nullptr;
    UDoubleSpinBox* QB_pilot_accel_z_cmms   = nullptr;
    UDoubleSpinBox* QB_speed_cms            = nullptr;
    UDoubleSpinBox* QB_accel_cmss           = nullptr;
    UDoubleSpinBox* QB_brake_accel_cmss     = nullptr;
    UDoubleSpinBox* QB_brake_jerk_max_cmsss = nullptr;
    UDoubleSpinBox* QB_brake_delay_ms       = nullptr;

    QSlider* SD_angle_max_cd         = nullptr;
    QSlider* SD_pilot_speed_up_cms   = nullptr;
    QSlider* SD_pilot_speed_dn_cms   = nullptr;
    QSlider* SD_pilot_accel_z_cmms   = nullptr;
    QSlider* SD_speed_cms            = nullptr;
    QSlider* SD_accel_cmss           = nullptr;
    QSlider* SD_brake_accel_cmss     = nullptr;
    QSlider* SD_brake_jerk_max_cmsss = nullptr;
    QSlider* SD_brake_delay_ms       = nullptr;

    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};


class CFG_ParamAutoControl:public QGridLayout
{
    Q_OBJECT
public:
    CFG_ParamAutoControl(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    QLabel*         LB_Info                 = nullptr;

    QLabel* LB__wp_speed_cms                = nullptr;
    QLabel* LB__wp_speed_up_cms             = nullptr;
    QLabel* LB__wp_speed_down_cms           = nullptr;
    QLabel* LB__wp_radius_cm                = nullptr;
    QLabel* LB__wp_accel_cmss               = nullptr;
    QLabel* LB__wp_accel_z_cmss             = nullptr;
    QLabel* LB_land_speed                   = nullptr;
    QLabel* LB_land_alt_low                 = nullptr;
    QLabel* LB_rtl_altitude                 = nullptr;


    UDoubleSpinBox* QB__wp_speed_cms        = nullptr;
    UDoubleSpinBox* QB__wp_speed_up_cms     = nullptr;
    UDoubleSpinBox* QB__wp_speed_down_cms   = nullptr;
    UDoubleSpinBox* QB__wp_radius_cm        = nullptr;
    UDoubleSpinBox* QB__wp_accel_cmss       = nullptr;
    UDoubleSpinBox* QB__wp_accel_z_cmss     = nullptr;
    UDoubleSpinBox* QB_land_speed           = nullptr;
    UDoubleSpinBox* QB_land_alt_low         = nullptr;
    UDoubleSpinBox* QB_rtl_altitude         = nullptr;

    QSlider* SD__wp_speed_cms        = nullptr;
    QSlider* SD__wp_speed_up_cms     = nullptr;
    QSlider* SD__wp_speed_down_cms   = nullptr;
    QSlider* SD__wp_radius_cm        = nullptr;
    QSlider* SD__wp_accel_cmss       = nullptr;
    QSlider* SD__wp_accel_z_cmss     = nullptr;
    QSlider* SD_land_speed           = nullptr;
    QSlider* SD_land_alt_low         = nullptr;
    QSlider* SD_rtl_altitude         = nullptr;

    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};

class CFG_ParamControl:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamControl(QWidget *parent = nullptr);

private:
    QGridLayout*    widgetLayout            = nullptr;
    CFG_ParamPilotControl * pilotctrl      = nullptr;
    CFG_ParamAutoControl* autoctrl          = nullptr;
private:
    void widget_init();
private slots:

};



#endif // CFG_PREARM_CALI__
