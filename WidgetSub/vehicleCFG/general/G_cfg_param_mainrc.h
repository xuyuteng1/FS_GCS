/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_MAINRC_H_
#define CFG_PARAM_MAINRC_H_

#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <QProgressBar>
#include <QStringList>
#include <QMap>
#include "uComboBox.h"
#include "progressbarpercent.h"
#include "uComboBox.h"
#include "uSpinBox.h"
#include "uDoubleSpinBox.h"

class G_CFG_RC:public QWidget
{
    Q_OBJECT
public:
    G_CFG_RC(QWidget *parent = nullptr);
    QGridLayout *getWidgetLayout() const;
private:

    QLabel          *titleLabel         = nullptr;
    QGridLayout*    widgetLayout        = nullptr;
    QLabel*         LB_Info             = nullptr;

    QLabel*         LB_RC[4]            = {};
    USpinBox*       QB_RC_Min[4]        = {};
    USpinBox*       QB_RC_Max[4]        = {};
    USpinBox*       QB_RC_Trim[4]       = {};
    USpinBox*       QB_RC_DZ[4]         = {};

    QLabel*         LB_RC_Min_Name      = nullptr;
    QLabel*         LB_RC_Max_Name      = nullptr;
    QLabel*         LB_RC_Trim_Name     = nullptr;
    QLabel*         LB_RC_DZ_Name       = nullptr;


    QProgressBar*   PR_pwm[8]           = {};
    QLabel*         LB_pwm[8]           = {};

    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;


    QLabel*         FLT_Select_Name     = nullptr;
    UComboBox*      FLT_Select          = nullptr;
    QMap<QString,int>  Flight_mode_names;

    QLabel*         FLT_Modes_Names[3]  = {};
    UComboBox*      FLT_Modes[3]        = {};
    QMap<QString,int>  Flight_modes;

    QLabel*         RC_OPT_Names[4]     = {};
    UComboBox*      RC_OPT[4]           = {};
    QMap<QString,int>  RC_options;
    QGridLayout*    sublayout           = nullptr;

    QHBoxLayout*    widgetLayout_pb2     = nullptr;
    QPushButton*    PB_download2         = nullptr;
    QPushButton*    PB_upload2           = nullptr;


private:
    void connectSignalAndSlot();
    void widget_init();
    void initial();
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
    void upload_param_aux();
};



#endif // CFG_PREARM_CALI__
