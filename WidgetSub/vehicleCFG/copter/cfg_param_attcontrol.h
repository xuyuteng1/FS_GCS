/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_ATT_CONTROL___H_
#define CFG_PARAM_ATT_CONTROL___H_

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
#include "uDoubleSpinBox.h"
class CFG_ParamRollControl:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamRollControl(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:

    QGridLayout*    widgetLayout            = nullptr;

    QLabel*         LB__accel_max           = nullptr;
    QLabel*         LB__ang_vel_max         = nullptr;
    QLabel*         LB_angle_p              = nullptr;
    QLabel*         LB_rate_p               = nullptr;
    QLabel*         LB_rate_i               = nullptr;
    QLabel*         LB_rate_d               = nullptr;
    QLabel*         LB_rate_ff              = nullptr;
    QLabel*         LB_rate_imax            = nullptr;
    QLabel*         LB_rate_slew_rate_max   = nullptr;

    QLabel *        titleLabel              = nullptr;

    QLabel*         LB_Limit                = nullptr;
    QLabel*         LB_Angle                = nullptr;
    QLabel*         LB_Rate                 = nullptr;

    UDoubleSpinBox* QB__accel_max           = nullptr;
    UDoubleSpinBox* QB__ang_vel_max         = nullptr;
    UDoubleSpinBox* QB_angle_p              = nullptr;
    UDoubleSpinBox* QB_rate_p               = nullptr;
    UDoubleSpinBox* QB_rate_i               = nullptr;
    UDoubleSpinBox* QB_rate_d               = nullptr;
    UDoubleSpinBox* QB_rate_ff              = nullptr;
    UDoubleSpinBox* QB_rate_imax            = nullptr;
    UDoubleSpinBox* QB_rate_slew_rate_max   = nullptr;


    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};

class CFG_ParamPitchControl:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamPitchControl(QWidget *parent = nullptr);
    CFG_ParamPitchControl(const QString &title, QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:

    QLabel  *titleLabel = nullptr;

    QGridLayout*    widgetLayout            = nullptr;

    QLabel*         LB__accel_max           = nullptr;
    QLabel*         LB__ang_vel_max         = nullptr;
    QLabel*         LB_angle_p              = nullptr;
    QLabel*         LB_rate_p               = nullptr;
    QLabel*         LB_rate_i               = nullptr;
    QLabel*         LB_rate_d               = nullptr;
    QLabel*         LB_rate_ff              = nullptr;
    QLabel*         LB_rate_imax            = nullptr;
    QLabel*         LB_rate_slew_rate_max   = nullptr;

    QLabel*         LB_Limit                = nullptr;
    QLabel*         LB_Angle                = nullptr;
    QLabel*         LB_Rate                 = nullptr;

    UDoubleSpinBox* QB__accel_max           = nullptr;
    UDoubleSpinBox* QB__ang_vel_max         = nullptr;
    UDoubleSpinBox* QB_angle_p              = nullptr;
    UDoubleSpinBox* QB_rate_p               = nullptr;
    UDoubleSpinBox* QB_rate_i               = nullptr;
    UDoubleSpinBox* QB_rate_d               = nullptr;
    UDoubleSpinBox* QB_rate_ff              = nullptr;
    UDoubleSpinBox* QB_rate_imax            = nullptr;
    UDoubleSpinBox* QB_rate_slew_rate_max   = nullptr;


    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};

class CFG_ParamYawControl:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamYawControl(QWidget *parent = nullptr);
    CFG_ParamYawControl(const QString &title, QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    QLabel  *titleLabel = nullptr;

    QGridLayout*    widgetLayout            = nullptr;

    QLabel*         LB__accel_max           = nullptr;
    QLabel*         LB__ang_vel_max         = nullptr;
    QLabel*         LB_angle_p              = nullptr;
    QLabel*         LB_rate_p               = nullptr;
    QLabel*         LB_rate_i               = nullptr;
    QLabel*         LB_rate_d               = nullptr;
    QLabel*         LB_rate_ff              = nullptr;
    QLabel*         LB_rate_imax            = nullptr;
    QLabel*         LB_rate_slew_rate_max   = nullptr;
    QLabel*         LB__slew_yaw            = nullptr;

    QLabel*         LB_Limit                = nullptr;
    QLabel*         LB_Angle                = nullptr;
    QLabel*         LB_Rate                 = nullptr;

    UDoubleSpinBox* QB__accel_max           = nullptr;
    UDoubleSpinBox* QB__ang_vel_max         = nullptr;
    UDoubleSpinBox* QB_angle_p              = nullptr;
    UDoubleSpinBox* QB_rate_p               = nullptr;
    UDoubleSpinBox* QB_rate_i               = nullptr;
    UDoubleSpinBox* QB_rate_d               = nullptr;
    UDoubleSpinBox* QB_rate_ff              = nullptr;
    UDoubleSpinBox* QB_rate_imax            = nullptr;
    UDoubleSpinBox* QB_rate_slew_rate_max   = nullptr;
    UDoubleSpinBox* QB__slew_yaw            = nullptr;

    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};




#endif // CFG_PREARM_CALI__
