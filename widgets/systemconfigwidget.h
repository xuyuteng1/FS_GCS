#ifndef SYSTEMCONFIGWIDGET_H
#define SYSTEMCONFIGWIDGET_H

#include <QListWidget>
#include <QWidget>
#include <QGridLayout>
#include <QAction>
#include <QAction>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QDebug>
#include "widgetitle.h"
#include <QCloseEvent>
#include <QMouseEvent>
#include <QFile>
#include "cfg_motortest.h"
#include "cfg_esc_cali.h"
#include "cfg_param_motors.h"
#include "cfg_copter_frame.h"
#include <QScroller>
#include <QScrollBar>
class ConfigTestLayout{
public:
    ConfigTestLayout();

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;

private:
    void configTestLayoutInit();

};

class SystemConfigWidget : public QWidget
{
    Q_OBJECT
public:
    SystemConfigWidget(QWidget *parent = nullptr);
    ~SystemConfigWidget();

    void addNewConfigWidget(QString,QGridLayout *layout);
private:
    QMap<QString,QListWidgetItem *> configWidgetMap;
    QMap<QString,QListWidgetItem *> actionWidgetMap;

private:
    QListWidget *actionWidget = nullptr;
    QListWidget *configWidget = nullptr;
    QGridLayout *configWidgetLayout = nullptr;

    WidgetTitle *w_title = nullptr;
    QGridLayout *mainLayout = nullptr;
//    QGridLayout *WidgetLayout = nullptr;

    CFG_CopterFrame   *         CFGwidget_Frame = nullptr;
    CFG_MotorTest*              CFGwidget_MotorTest = nullptr;
    CFG_ESCCalibration*         CFGwidget_ESCCali = nullptr;
    CFG_ParamMotors*            CFGwidget_ParamMotors = nullptr;


private:
    void widgetInit();
    void connectSignalAndSlot();



private slots:
    void actionWidgetItemPressedSlot(QString text);
    void configWidgetItemPressedSlot(QString text);
protected:
//    /**========= 窗口支持鼠标拖动 =========**/
//    QPoint dragPosition;
//    void mousePressEvent(QMouseEvent *event)
//    {
//        if (event->button() == Qt::LeftButton) {
//           dragPosition = event->globalPos() - frameGeometry().topLeft();
//            event->accept();
//        }
//    };

//    void mouseMoveEvent(QMouseEvent *event)
//    {
//        if (event->buttons() & Qt::LeftButton) {
//            move(event->globalPos() - dragPosition);
//            event->accept();
//        }
//    };
public:
signals:
    void signalCloseEvent();
};

#endif // SYSTEMCONFIGWIDGET_H
