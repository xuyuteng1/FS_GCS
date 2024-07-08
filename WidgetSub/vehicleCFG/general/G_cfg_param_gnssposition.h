/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_GNSS_POSITION_H_
#define CFG_GNSS_POSITION_H_

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
class G_CFG_AntennaPos:public QWidget
{
    Q_OBJECT
public:
    G_CFG_AntennaPos(QWidget *parent = nullptr);
    QGridLayout *getWidgetLayout() const;
private:
    QLabel          *titleLabel         = nullptr;
    QGridLayout*    widgetLayout        = nullptr;
    QLabel*         LB_Info             = nullptr;

    QLabel*         LB_Posx             = nullptr;
    QLabel*         LB_Posy             = nullptr;
    QLabel*         LB_Posz             = nullptr;

    QLabel*         LB_GNSS1             = nullptr;
    QLabel*         LB_GNSS2             = nullptr;


    UDoubleSpinBox* SB_GNSS1_POS[3]     = {};
    UDoubleSpinBox* SB_GNSS2_POS[3]     = {};

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
