/**=================================================================**
 * @brief       : FixWing Takeoff Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-08     Jerry.xl     the first version
 **==================================================================**/
#ifndef P_CFG_FAILSAFE_H
#define P_CFG_FAILSAFE_H

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
#include "uDoubleSpinBox.h"
class P_CFG_Failsafe:public QWidget
{
    Q_OBJECT
public:
    P_CFG_Failsafe(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    QGridLayout*    widgetLayout = nullptr;
    QLabel          *titleLabel = nullptr;

    /* rc&throttle failsafe parameters setting */
    QGroupBox*      Group_rc = nullptr;
    QGridLayout*    Layout_rc = nullptr;
    QLabel*         lb_THR_FAILSAFE = nullptr;
    UComboBox*      THR_FAILSAFE = nullptr;
    QLabel*         lb_THR_FS_VALUE = nullptr;
    UDoubleSpinBox* THR_FS_VALUE = nullptr;
    QLabel*         lb_FS_GCS_ENABL = nullptr;
    UComboBox*      FS_GCS_ENABL = nullptr;

    /* short and long failsafe Triger Action parameters setting */
    QGroupBox*      Group_action = nullptr;
    QGridLayout*    Layout_action = nullptr;

    QLabel*         lb_FS_SHORT_ACTN = nullptr;
    UComboBox*      FS_SHORT_ACTN = nullptr;
    QLabel*         lb_FS_SHORT_TIMEOUT = nullptr;
    UDoubleSpinBox* FS_SHORT_TIMEOUT = nullptr;

    QLabel*         lb_FS_LONG_ACTN = nullptr;
    UComboBox*      FS_LONG_ACTN = nullptr;
    QLabel*         lb_FS_LONG_TIMEOUT = nullptr;
    UDoubleSpinBox* FS_LONG_TIMEOUT = nullptr;

    /* battery failsafe Triger Action parameters setting */
    QGroupBox*      Group_batt = nullptr;
    QGridLayout*    Layout_batt = nullptr;

    QLabel*         lb_BATT_LOW_VOLT = nullptr;
    QLabel*         lb_BATT_CRT_VOLT = nullptr;
    QLabel*         lb_BATT_FS_LOW_ACT = nullptr;
    QLabel*         lb_BATT_FS_CRT_ACT = nullptr;
    QLabel*         lb_BATT_LOW_TIMER = nullptr;
    QLabel*         lb_BATT_ARM_VOLT = nullptr;

    UDoubleSpinBox* BATT_LOW_VOLT = nullptr;
    UDoubleSpinBox* BATT_CRT_VOLT = nullptr;
    UComboBox*      BATT_FS_LOW_ACT = nullptr;
    UComboBox*      BATT_FS_CRT_ACT = nullptr;
    UDoubleSpinBox* BATT_LOW_TIMER = nullptr;
    UDoubleSpinBox* BATT_ARM_VOLT = nullptr;

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
