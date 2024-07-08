/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_POS_CONTROL___H_
#define CFG_PARAM_POS_CONTROL___H_

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
class CFG_ParamPosZControl:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamPosZControl(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:

    QGridLayout*    widgetLayout            = nullptr;
    QLabel*         LB_shaping_jerk         = nullptr;
    QLabel*         LB_pos_p                = nullptr;
    QLabel*         LB_vel_p                = nullptr;
    QLabel*         LB_vel_i                = nullptr;
    QLabel*         LB_vel_d                = nullptr;
    QLabel*         LB_vel_ff               = nullptr;
    QLabel*         LB_vel_imax             = nullptr;
    QLabel*         LB_acc_p                = nullptr;
    QLabel*         LB_acc_i                = nullptr;
    QLabel*         LB_acc_d                = nullptr;
    QLabel*         LB_acc_ff               = nullptr;
    QLabel*         LB_acc_imax             = nullptr;
    QLabel*         LB_acc_slew_rate_max    = nullptr;

    UDoubleSpinBox* QB_shaping_jerk         = nullptr;
    UDoubleSpinBox* QB_pos_p                = nullptr;
    UDoubleSpinBox* QB_vel_p                = nullptr;
    UDoubleSpinBox* QB_vel_i                = nullptr;
    UDoubleSpinBox* QB_vel_d                = nullptr;
    UDoubleSpinBox* QB_vel_ff               = nullptr;
    UDoubleSpinBox* QB_vel_imax             = nullptr;
    UDoubleSpinBox* QB_acc_p                = nullptr;
    UDoubleSpinBox* QB_acc_i                = nullptr;
    UDoubleSpinBox* QB_acc_d                = nullptr;
    UDoubleSpinBox* QB_acc_ff               = nullptr;
    UDoubleSpinBox* QB_acc_imax             = nullptr;
    UDoubleSpinBox* QB_acc_slew_rate_max    = nullptr;

    QLabel *titleLabel = nullptr;

    QLabel*      LB_Limit                = nullptr;
    QLabel*      LB_Pos                  = nullptr;
    QLabel*      LB_Vel                  = nullptr;
    QLabel*      LB_Acc                  = nullptr;

//    QGridLayout*    LY_Limit                = nullptr;
//    QGridLayout*    LY_Pos                  = nullptr;
//    QGridLayout*    LY_Vel                  = nullptr;
//    QGridLayout*    LY_Acc                  = nullptr;

    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};

class CFG_ParamPosXYControl:public QWidget
{
    Q_OBJECT
public:
    CFG_ParamPosXYControl(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:

    QGridLayout*    widgetLayout            = nullptr;
    QLabel*         LB_shaping_jerk         = nullptr;
    QLabel*         LB_pos_p                = nullptr;
    QLabel*         LB_vel_p                = nullptr;
    QLabel*         LB_vel_i                = nullptr;
    QLabel*         LB_vel_d                = nullptr;
    QLabel*         LB_vel_ff               = nullptr;
    QLabel*         LB_vel_imax             = nullptr;
    QLabel *        titleLabel              = nullptr;

    UDoubleSpinBox* QB_shaping_jerk         = nullptr;
    UDoubleSpinBox* QB_pos_p                = nullptr;
    UDoubleSpinBox* QB_vel_p                = nullptr;
    UDoubleSpinBox* QB_vel_i                = nullptr;
    UDoubleSpinBox* QB_vel_d                = nullptr;
    UDoubleSpinBox* QB_vel_ff               = nullptr;
    UDoubleSpinBox* QB_vel_imax             = nullptr;

    QLabel*      LB_Limit                = nullptr;
    QLabel*      LB_Pos                  = nullptr;
    QLabel*      LB_Vel                  = nullptr;

//    QGridLayout*    LY_Limit                = nullptr;
//    QGridLayout*    LY_Pos                  = nullptr;
//    QGridLayout*    LY_Vel                  = nullptr;

    QHBoxLayout*    widgetLayout_pb         = nullptr;
    QPushButton*    PB_download             = nullptr;
    QPushButton*    PB_upload               = nullptr;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};




#endif // CFG_PREARM_CALI__
