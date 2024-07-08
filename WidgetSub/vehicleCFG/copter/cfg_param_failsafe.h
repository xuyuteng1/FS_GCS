/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_FAILSAFE_H_
#define CFG_PARAM_FAILSAFE_H_

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
#include <QCheckBox>
#include <QButtonGroup>
#include <QPixmap>

#if 1
class CFG_ParamFailsafe:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamFailsafe(QWidget *parent = nullptr);

private:
    QGridLayout*    widgetLayout        = nullptr;

    QLabel          *titleLabel = nullptr;
    QLabel*         LB_Info_Icon    = nullptr;
    QLabel*         LB_Info             = nullptr;
    QHBoxLayout * LB_Layout = nullptr;

    QLabel*         LB_Crash            = nullptr;
    QLabel*         LB_Vibe             = nullptr;
    QLabel*         LB_EKF              = nullptr;
    QLabel*         LB_RC               = nullptr;
    QLabel*         LB_GCS              = nullptr;
    QLabel*         LB_BatL1            = nullptr;
    QLabel*         LB_BatL2            = nullptr;
    QLabel*         LB_BatArm           = nullptr;
    QLabel*         LB_BatMax           = nullptr;
    QLabel*         LB_BatMin           = nullptr;

    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;

    QCheckBox       *crashEnableCheckBox = nullptr;
    QCheckBox       *crashDisEnableCheckBox = nullptr;
    QButtonGroup *crashButtonGroup = nullptr;

    QCheckBox       *vibeEnableCheckBox = nullptr;
    QCheckBox       *vibeDisEnableCheckBox = nullptr;
    QButtonGroup *vibeButtonGroup = nullptr;

    UComboBox*      CB_EKF              = nullptr;
    UComboBox*      CB_RC               = nullptr;
    USpinBox*       QB_GCSTime          = nullptr;
    UComboBox*      CB_GCS              = nullptr;
    UComboBox*      CB_BatL1            = nullptr;
    UComboBox*      CB_BatL2            = nullptr;
    UDoubleSpinBox* QB_BatL1Val         = nullptr;
    UDoubleSpinBox* QB_BatL2Val         = nullptr;
    UDoubleSpinBox* QB_BatArm           = nullptr;
    UDoubleSpinBox* QB_BatMax           = nullptr;
    UDoubleSpinBox* QB_BatMin           = nullptr;

    QLabel*         LB_BattInfo         = nullptr;
    QSpinBox*       DS_batt_cells       = nullptr;
    QCheckBox *     battTypeCheckBox = nullptr;
    QCheckBox *     battTypeHVCheckBox = nullptr;
    QButtonGroup * battTypeGroup = nullptr;
//    QComboBox*      QC_battType         = nullptr;
    QPushButton*    PB_Calcu            = nullptr;
    QGridLayout*    Layout_Batt         = nullptr;
    QGroupBox*      Group_Calcu                 = nullptr;
private:
    void connectSignalAndSlot();
    void widget_init();
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
    void calc_values();
};
#endif


#endif // CFG_PREARM_CALI__
