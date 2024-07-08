/**=================================================================**
 * @brief       : FixWing Basic Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-10     Jerry.xl     the first version
 **==================================================================**/
#ifndef P_CFG_BASIC_H
#define P_CFG_BASIC_H

/**==================================================================**/
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
#include "uComboBox.h"
#include "uCheckBox.h"
#include "uDoubleSpinBox.h"
#include "G_cfg_template.h"
class P_CFG_Basic:public QWidget
{
    Q_OBJECT
public:
    P_CFG_Basic(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    QGridLayout*    widgetLayout = nullptr;
    QLabel          *titleLabel = nullptr;

    /* Update Parameters */
    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
    /**-----------------------------------------------------------------**/

    /* basic parameters setting */
    QGroupBox*          Group_basic = nullptr;
    QGridLayout*        Layout_basic = nullptr;
    QLabel*             lb_THR_MIN = nullptr;
    QLabel*             lb_THR_MAX = nullptr;
    QLabel*             lb_THR_SLEWRATE = nullptr;
    QLabel*             lb_TRIM_THROTTLE = nullptr;
    QLabel*             lb_ARSPD_FBW_MIN = nullptr;
    QLabel*             lb_ARSPD_FBW_MAX = nullptr;
    QLabel*             lb_SCALING_SPEED = nullptr;
    QLabel*             lb_TRIM_ARSPD_CM = nullptr;
    QLabel*             lb_MIN_GNDSPD_CM = nullptr;
    QLabel*             lb_LIM_ROLL_CD = nullptr;
    QLabel*             lb_LIM_PITCH_MAX = nullptr;
    QLabel*             lb_LIM_PITCH_MIN = nullptr;
    QLabel*             lb_WP_RADIUS = nullptr;

    UDoubleSpinBox*     THR_MIN = nullptr;
    UDoubleSpinBox*     THR_MAX = nullptr;
    UDoubleSpinBox*     THR_SLEWRATE = nullptr;
    UDoubleSpinBox*     TRIM_THROTTLE = nullptr;
    UDoubleSpinBox*     ARSPD_FBW_MIN = nullptr;
    UDoubleSpinBox*     ARSPD_FBW_MAX = nullptr;
    UDoubleSpinBox*     TRIM_ARSPD_CM = nullptr;
    UDoubleSpinBox*     SCALING_SPEED = nullptr;
    UDoubleSpinBox*     MIN_GNDSPD_CM = nullptr;
    UDoubleSpinBox*     LIM_ROLL_CD = nullptr;
    UDoubleSpinBox*     LIM_PITCH_MAX = nullptr;
    UDoubleSpinBox*     LIM_PITCH_MIN = nullptr;
    UDoubleSpinBox*     WP_RADIUS = nullptr;
    UCheckBox*          CRASH_DETECT = nullptr;
    UCheckBox*          STALL_PREVENTION = nullptr;
    void Init_ParametersBasic();
    void upload_ParametersBasic();
    void update_ParametersBasic(bool getfromflight = false);

protected:
    void showEvent(QShowEvent *event)override;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void Upload_Parameters();
public slots:
    void update_value(bool getfromflight = false);
};


#endif // CFG_PREARM_CALI__
