/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_ESC_CAL_H_
#define CFG_ESC_CAL_H_

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

class CFG_ESCCalibration:public QObject
{
    Q_OBJECT
public:
    CFG_ESCCalibration();

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout*    widgetLayout        = nullptr;
    QLabel*         LB_Info             = nullptr;
    QPushButton*    PB_Start            = nullptr;
    QPushButton*    PB_Stop             = nullptr;
    QPushButton*    PB_Shift            = nullptr;

private:
    void connectSignalAndSlot();
    void widget_init();
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
};



#endif // CFG_PREARM_CALI__
