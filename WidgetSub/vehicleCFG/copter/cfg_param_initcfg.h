/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_INIT_CFG____
#define CFG_INIT_CFG____

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

class CFG_InitCfg:public QWidget
{
    Q_OBJECT
public:
    CFG_InitCfg(QWidget *parent = nullptr);

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout*    widgetLayout                = nullptr;
    QLabel*         LB_Info                     = nullptr;
    QLabel          *titleLabel                         = nullptr;

    QLabel*         LB_prop_size                = nullptr;
    QDoubleSpinBox* DS_prop_size                = nullptr;
    QPushButton*    PB_Calculate                = nullptr;

    QVBoxLayout*    widgetLayout_calcu          = nullptr;
    QGroupBox*      Group_Calcu                 = nullptr;
    QHBoxLayout*    widgetLayout_pb             = nullptr;
    QPushButton*    PB_download                 = nullptr;
    QPushButton*    PB_upload                   = nullptr;

    QLabel* LB_acro_yaw_p                       = nullptr;
    QLabel* LB_atc_accel_p_max                  = nullptr;
    QLabel* LB_atc_accel_r_max                  = nullptr;
    QLabel* LB_atc_accel_y_max                  = nullptr;
    QLabel* LB_atc_rat_pit_fltd                 = nullptr;
    QLabel* LB_atc_rat_pit_flte                 = nullptr;
    QLabel* LB_atc_rat_pit_fltt                 = nullptr;
    QLabel* LB_atc_rat_rll_fltd                 = nullptr;
    QLabel* LB_atc_rat_rll_flte                 = nullptr;
    QLabel* LB_atc_rat_rll_fltt                 = nullptr;
    QLabel* LB_atc_rat_yaw_fltd                 = nullptr;
    QLabel* LB_atc_rat_yaw_flte                 = nullptr;
    QLabel* LB_atc_rat_yaw_fltt                 = nullptr;
    QLabel* LB_atc_thr_mix_man                  = nullptr;
    QLabel* LB_ins_accel_filter                 = nullptr;
    QLabel* LB_ins_gyro_filter                  = nullptr;
    QLabel* LB_mot_thst_expo                    = nullptr;

    UDoubleSpinBox* DS_acro_yaw_p               = nullptr;
    UDoubleSpinBox* DS_atc_accel_p_max          = nullptr;
    UDoubleSpinBox* DS_atc_accel_r_max          = nullptr;
    UDoubleSpinBox* DS_atc_accel_y_max          = nullptr;
    UDoubleSpinBox* DS_atc_rat_pit_fltd         = nullptr;
    UDoubleSpinBox* DS_atc_rat_pit_flte         = nullptr;
    UDoubleSpinBox* DS_atc_rat_pit_fltt         = nullptr;
    UDoubleSpinBox* DS_atc_rat_rll_fltd         = nullptr;
    UDoubleSpinBox* DS_atc_rat_rll_flte         = nullptr;
    UDoubleSpinBox* DS_atc_rat_rll_fltt         = nullptr;
    UDoubleSpinBox* DS_atc_rat_yaw_fltd         = nullptr;
    UDoubleSpinBox* DS_atc_rat_yaw_flte         = nullptr;
    UDoubleSpinBox* DS_atc_rat_yaw_fltt         = nullptr;
    UDoubleSpinBox* DS_atc_thr_mix_man          = nullptr;
    UDoubleSpinBox* DS_ins_accel_filter         = nullptr;
    UDoubleSpinBox* DS_ins_gyro_filter          = nullptr;
    UDoubleSpinBox* DS_mot_thst_expo            = nullptr;

    QSlider *SD_atc_rat_pit_fltd                        = nullptr;
    QSlider *SD_atc_rat_pit_flte                        = nullptr;
    QSlider *SD_atc_rat_pit_fltt                        = nullptr;
    QSlider *SD_atc_rat_rll_fltd                        = nullptr;
    QSlider *SD_atc_rat_rll_flte                        = nullptr;
    QSlider *SD_atc_rat_rll_fltt                        = nullptr;
    QSlider *SD_atc_rat_yaw_fltd                        = nullptr;
    QSlider *SD_atc_rat_yaw_flte                        = nullptr;
    QSlider *SD_atc_rat_yaw_fltt                        = nullptr;
    QSlider *SD_ins_accel_filter                        = nullptr;
    QSlider *SD_ins_gyro_filter                        = nullptr;


    double prop_size = 9.0f;
    double acro_yaw_p;
    double atc_accel_p_max;
    double atc_accel_r_max;
    double atc_accel_y_max;
    double atc_rat_pit_fltd;
    double atc_rat_pit_flte;
    double atc_rat_pit_fltt;
    double atc_rat_rll_fltd;
    double atc_rat_rll_flte;
    double atc_rat_rll_fltt;
    double atc_rat_yaw_fltd;
    double atc_rat_yaw_flte;
    double atc_rat_yaw_fltt;
    double atc_thr_mix_man;
    double ins_accel_filter;
    double ins_gyro_filter;
    double mot_thst_expo;

private:
    void connectSignalAndSlot();
    void widget_init();
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();

    void calc_values();
};



#endif // CFG_PREARM_CALI__
