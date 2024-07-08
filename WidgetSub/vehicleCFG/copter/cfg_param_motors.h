/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_MOTORS_H_
#define CFG_PARAM_MOTORS_H_

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

class CFG_ParamMotors:public QObject
{
    Q_OBJECT
public:
    CFG_ParamMotors();

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout*    widgetLayout        = nullptr;
    QLabel*         LB_Info             = nullptr;

    QLabel*         LB_SpinMin          = nullptr;
    QLabel*         LB_SpinMax          = nullptr;
    QLabel*         LB_SpinArm          = nullptr;
    QLabel*         LB_PWMMin           = nullptr;
    QLabel*         LB_PWMMax           = nullptr;
    QLabel*         LB_Throttle_hover   = nullptr;
    QLabel*         LB_hover_learn      = nullptr;


    USpinBox*       SB_SpinMin          = nullptr;
    USpinBox*       SB_SpinMax          = nullptr;
    USpinBox*       SB_SpinArm          = nullptr;
    USpinBox*       SB_PWMMin           = nullptr;
    USpinBox*       SB_PWMMax           = nullptr;
    USpinBox*       SB_Throttle_hover   = nullptr;
    UComboBox*      CB_hover_learn      = nullptr;



    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
private:
    void connectSignalAndSlot();
    void widget_init();
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};



#endif // CFG_PREARM_CALI__
