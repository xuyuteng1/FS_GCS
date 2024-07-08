/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_MOTOR_TEST_H_
#define CFG_MOTOR_TEST_H_

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

class CFG_MotorTest:public QObject
{
    Q_OBJECT
public:
    CFG_MotorTest();

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout*    widgetLayout        = nullptr;
    QGridLayout*    LayoutMotorVal      = nullptr;
    QGridLayout*    LayoutMotorTest     = nullptr;
    QLabel*         LB_Info             = nullptr;

    QSpinBox*       SP_MotorID          = nullptr;
    QSpinBox*       SP_MotorPCT         = nullptr;
    QSpinBox*       SP_MotorTime        = nullptr;

    QLabel*         LB_MotorID          = nullptr;
    QLabel*         LB_MotorPCT         = nullptr;
    QLabel*         LB_MotorTime        = nullptr;

    QPushButton*    PB_Start            = nullptr;
    QPushButton*    PB_Stop             = nullptr;
    QPushButton*    PB_OrderStart       = nullptr;

    QProgressBar*   PR_pwm[16]          = {};
    QLabel*         LB_pwm[16]          = {};


    QGroupBox*      Group_motorval   = nullptr;
    QGroupBox*      Group_motortest      = nullptr;

private:
    void connectSignalAndSlot();
    void widget_init();
    uint8_t         motor_count = 4;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
};



#endif // CFG_PREARM_CALI__
