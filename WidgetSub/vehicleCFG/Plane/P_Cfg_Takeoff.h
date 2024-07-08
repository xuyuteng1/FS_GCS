/**=================================================================**
 * @brief       : FixWing Takeoff Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-08     Jerry.xl     the first version
 **==================================================================**/
#ifndef P_CFG_TAKEOFF_H
#define P_CFG_TAKEOFF_H

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
class P_CFG_Takeoff:public QWidget
{
    Q_OBJECT
public:
    P_CFG_Takeoff(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    QGridLayout*    widgetLayout = nullptr;
    QLabel          *titleLabel = nullptr;

    /* Trigger condition parameters */
    QGroupBox*      Group_Trigger = nullptr;
    QGridLayout*    Layout_Trigger = nullptr;

    QLabel*         lb_TKOFF_ACCEL_CNT = nullptr;
    QLabel*         lb_TKOFF_THR_MINACC = nullptr;
    QLabel*         lb_TKOFF_THR_MINSPD = nullptr;
    UDoubleSpinBox* TKOFF_ACCEL_CNT = nullptr;
    UDoubleSpinBox* TKOFF_THR_MINACC = nullptr;
    UDoubleSpinBox* TKOFF_THR_MINSPD = nullptr;

    /* takeoff target parameters setting */
    QGroupBox*      Group_Target = nullptr;
    QGridLayout*    Layout_Target = nullptr;

    QLabel*         lb_TKOFF_ALT = nullptr;
    QLabel*         lb_TKOFF_DIST = nullptr;
    QLabel*         lb_TKOFF_LVL_ALT = nullptr;
    QLabel*         lb_TKOFF_LVL_PITCH = nullptr;
    UDoubleSpinBox* TKOFF_ALT = nullptr;
    UDoubleSpinBox* TKOFF_DIST = nullptr;
    UDoubleSpinBox* TKOFF_LVL_ALT = nullptr;
    UDoubleSpinBox* TKOFF_LVL_PITCH = nullptr;


    /* Runway takeoff parameters setting */
    QGroupBox*      Group_runway = nullptr;
    QGridLayout*    Layout_runway = nullptr;

    QLabel*         lb_TKOFF_ROTATE_SPD = nullptr;
    QLabel*         lb_TKOFF_TDRAG_ELEV = nullptr;
    QLabel*         lb_TKOFF_TDRAG_SPD1 = nullptr;

    UDoubleSpinBox* TKOFF_ROTATE_SPD = nullptr;
    UDoubleSpinBox* TKOFF_TDRAG_ELEV = nullptr;
    UDoubleSpinBox* TKOFF_TDRAG_SPD1 = nullptr;

    /* general parameters setting */
    QGroupBox*      Group_general = nullptr;
    QGridLayout*    Layout_general = nullptr;
    QLabel*         lb_TKOFF_THR_SLEW = nullptr;
    QLabel*         lb_TKOFF_PLIM_SEC = nullptr;
    QLabel*         lb_TKOFF_THR_MAX = nullptr;
    QLabel*         lb_TKOFF_TIMEOUT = nullptr;
    QLabel*         lb_TKOFF_FLAP_PCNT = nullptr;
    QLabel*         lb_GROUND_STEER_ALT = nullptr;
    QLabel*         lb_TKOFF_THR_DELAY = nullptr;

    UDoubleSpinBox* TKOFF_THR_SLEW = nullptr;
    UDoubleSpinBox* TKOFF_PLIM_SEC = nullptr;
    UDoubleSpinBox* TKOFF_THR_MAX = nullptr;
    UDoubleSpinBox* TKOFF_TIMEOUT = nullptr;
    UDoubleSpinBox* TKOFF_FLAP_PCNT = nullptr;
    UDoubleSpinBox* GROUND_STEER_ALT = nullptr;
    UDoubleSpinBox* TKOFF_THR_DELAY = nullptr;

    /* Update Parameters */
    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
protected:
    void showEvent(QShowEvent *event)override;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void Upload_Parameters();
public slots:
    void update_value(bool getfromflight = false);
};


#endif // CFG_PREARM_CALI__
