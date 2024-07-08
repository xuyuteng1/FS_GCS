#pragma once
/**=================================================================**
 * @brief       : Parameter Config Widget Template
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-23     Jerry.xl     the first version
 **==================================================================**/
#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "uDoubleSpinBox.h"


class G_CFG_Template:public QWidget
{
    Q_OBJECT
public:
    G_CFG_Template(QWidget *parent = nullptr,QString title = "");
    QGridLayout *getWidgetLayout() const;
    static void ParamCFGInit_DoubleSpinBox(QLabel *&label, UDoubleSpinBox *&box, QString name, QString Tooltip, double range_min, double range_max, double single_step, int prec);
protected:
    QLabel*         titleLabel          = nullptr;
    QGridLayout*    widgetLayout        = nullptr;

    /* Update Parameters */
    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
    QString         _widgetTitle{};
protected:
    virtual void WidgetInit(){};
    virtual void connectSignalAndSlot(){};
    void showEvent(QShowEvent *event) override;
    void f_WidgetInit();
    void f_connectSignalAndSlot();
protected slots:
    /* 用于处理datapool_event */
    virtual void handle_DMMM_event(int ev,int linkid = 0);
    virtual void update_value(bool getfromflight = false){};
    virtual void Upload_Parameters(){};

private:

};

