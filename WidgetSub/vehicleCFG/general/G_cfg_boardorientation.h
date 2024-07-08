/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#ifndef CFG_PARAM_BOARD_ORIENTATION_H__
#define CFG_PARAM_BOARD_ORIENTATION_H__

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

class G_CFG_BoardOrientation:public QWidget
{
    Q_OBJECT
public:
    G_CFG_BoardOrientation(QWidget *parent = nullptr);

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout*    widgetLayout        = nullptr;
    QLabel*         LB_Info             = nullptr;

    QLabel          *titleLabel = nullptr;
    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;

    UComboBox*      CB_boardorientation = nullptr;
private:
    void connectSignalAndSlot();
    void widget_init();
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void upload_param();
};



#endif // CFG_PREARM_CALI__
