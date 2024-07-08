/**=================================================================**
 * @brief       : SITL Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-03     Jerry.xl     the first version
 **==================================================================**/
#ifndef SIMCFG_H
#define SIMCFG_H

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
#include "uCheckBox.h"
#include "flightgear.h"
class SIM_CFG:public QWidget
{
    Q_OBJECT
public:
    SIM_CFG(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    FlightGear_Link* flightgear = nullptr;
    QGridLayout*    widgetLayout = nullptr;
    QLabel *        titleLabel = nullptr;
    /* Communication Switch */
    QPushButton*    OpenSIM = nullptr;

    /* Init Postion */
    QGroupBox*      Group_Postion = nullptr;
    QGridLayout*    Layout_Postion = nullptr;
    QLabel*         lb_Pos_Alt = nullptr;
    QLabel*         lb_Pos_Lat = nullptr;
    QLabel*         lb_Pos_Lng = nullptr;
    QLabel*         lb_Pos_Heading = nullptr;
    UDoubleSpinBox* ds_Pos_Alt = nullptr;
    UDoubleSpinBox* ds_Pos_Lat = nullptr;
    UDoubleSpinBox* ds_Pos_Lng = nullptr;
    UDoubleSpinBox* ds_Pos_Heading = nullptr;

    /* Wind Parameter */
    QGroupBox*      Group_Wind = nullptr;
    QGridLayout*    Layout_Wind = nullptr;
    QLabel*         lb_WindDir = nullptr;
    QLabel*         lb_Wind_Spd = nullptr;
    QLabel*         lb_Wind_Alt = nullptr;
    QLabel*         lb_Wind_Turb = nullptr;
    UDoubleSpinBox* ds_WindDir = nullptr;
    UDoubleSpinBox* ds_Wind_Spd = nullptr;
    UDoubleSpinBox* ds_Wind_Alt = nullptr;
    UDoubleSpinBox* ds_Wind_Turb = nullptr;

    /* GPS RC Failsafe Simulation */
    QGroupBox*      Group_fail = nullptr;
    QGridLayout*    Layout_fail = nullptr;
    UCheckBox*      ds_GPSDisable = nullptr;
    UCheckBox*      SIM_RC_FAIL = nullptr;

    /* Update Parameters */
    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
protected:
    void showEvent(QShowEvent *event)override;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void handle_OpenSIM();
    void Upload_Parameters();
public slots:
    void update_value(bool getfromflight = false);
};


#endif // CFG_PREARM_CALI__
