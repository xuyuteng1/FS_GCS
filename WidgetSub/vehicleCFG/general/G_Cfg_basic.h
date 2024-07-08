/**=================================================================**
 * @brief       : FixWing Basic Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-10     Jerry.xl     the first version
 **==================================================================**/
#ifndef g_CFG_BASIC_H
#define g_CFG_BASIC_H

/**==================================================================**/
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
#include "uComboBox.h"
#include "uCheckBox.h"
#include "uDoubleSpinBox.h"
class G_CFG_Basic:public QWidget
{
    Q_OBJECT
public:
    G_CFG_Basic(QWidget *parent = nullptr);
private:
    void connectSignalAndSlot();
    void widget_init();
private:
    QGridLayout*    widgetLayout = nullptr;
    QLabel          *titleLabel = nullptr;

    /* Update Parameters */
    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
    /**-----------------------------------------------------------------**/

    UCheckBox*         LOG_DISARMED = nullptr;

protected:
    void showEvent(QShowEvent *event)override;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void Upload_Parameters();
public slots:
    void update_value(bool getfromflight = false);
};


#endif // CFG_PREARM_CALI__
