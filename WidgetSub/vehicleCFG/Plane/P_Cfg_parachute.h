/**=================================================================**
 * @brief       : parachute Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-24     Jerry.xl     the first version
 **==================================================================**/
#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include "UCheckBox.h"
#include "UComboBox.h"
#include "G_cfg_template.h"

class P_Cfg_Parachute:public G_CFG_Template
{
    Q_OBJECT
public:
    P_Cfg_Parachute(QWidget *parent = nullptr,QString title = "");

protected:
    void WidgetInit()override;
    void connectSignalAndSlot()override;
protected slots:
    void Upload_Parameters()override;
    void update_value(bool getfromflight = false)override;
private:
    /* parachute parameters setting */
    QGroupBox*      Group_parachute = nullptr;
    QGridLayout*    Layout_parachute = nullptr;
    QLabel*         lb_CHUTE_TYPE = nullptr;
    QLabel*         lb_CHUTE_SERVO_ON = nullptr;
    QLabel*         lb_CHUTE_SERVO_OFF = nullptr;
    QLabel*         lb_CHUTE_ALT_MIN = nullptr;
    QLabel*         lb_CHUTE_DELAY_MS = nullptr;
    QLabel*         lb_CHUTE_CRT_SINK = nullptr;

    UCheckBox*         CHUTE_ENABLED = nullptr;
    UComboBox*         CHUTE_TYPE = nullptr;
    UDoubleSpinBox*    CHUTE_SERVO_ON = nullptr;
    UDoubleSpinBox*    CHUTE_SERVO_OFF = nullptr;
    UDoubleSpinBox*    CHUTE_ALT_MIN = nullptr;
    UDoubleSpinBox*    CHUTE_DELAY_MS = nullptr;
    UDoubleSpinBox*    CHUTE_CRT_SINK = nullptr;
    UCheckBox*         CHUTE_OPTIONS = nullptr;

    void Init_ParametersParachute();
    void upload_ParametersParachute();
    void update_ParametersParachute(bool getfromflight = false);
};

