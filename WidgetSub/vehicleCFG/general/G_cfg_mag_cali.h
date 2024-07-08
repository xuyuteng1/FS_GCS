/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_MAG_CALI_H_
#define CFG_MAG_CALI_H_

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


class G_CFG_MagCali:public QWidget
{
    Q_OBJECT
public:
    G_CFG_MagCali(QWidget *parent = nullptr);
    QGridLayout *getWidgetLayout() const;
private:
    QLabel          *titleLabel         = nullptr;

private:
    QGridLayout*    widgetLayout        = nullptr;
    QLabel*         LB_MagInfo          = nullptr;
    QLabel*         LB_MagState[3]      = {};
    QLabel*         LB_InFlightMagInfo  = nullptr;
    QLabel*         LB_SimpleMagInfo    = nullptr;
    ProgressBarPercent* progress[3]     = {};
    QPushButton*    PB_MagCali          = nullptr;
    QPushButton*    PB_MagCaliStop          = nullptr;
    QPushButton*    PB_InFlightMagCali  = nullptr;
    QPushButton*    PB_InFlightMagCaliCancel  = nullptr;
    QPushButton*    PB_SimpleMagCali    = nullptr;

    QGroupBox*      Group_MagCali       = nullptr;
    QGroupBox*      Group_InFlightMagCali= nullptr;
    QGroupBox*      Group_SimpleMagCali = nullptr;

    QGridLayout*    LayoutMagCali       = nullptr;
    QGridLayout*    LayoutInFlightMagCali= nullptr;
    QGridLayout*    LayoutSimpleMagCali = nullptr;

    QGridLayout*    LayoutProgress      = nullptr;

    QSpinBox*       SP_FixedYaw         = nullptr;
    uint8_t         mag_count           = 0;
private:
    void connectSignalAndSlot();
    void widget_init();
    void reset_state();

    static QString getCaliState(uint8_t state);
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
};



#endif // CFG_PREARM_CALI__
