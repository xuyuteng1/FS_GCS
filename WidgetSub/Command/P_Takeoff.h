#ifndef P_TAKEOFF_CMD_H__
#define P_TAKEOFF_CMD_H__

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QTimer>
#include <QMessageBox>


class P_CMD_Takeoff :  public QWidget{
    Q_OBJECT
public:
    P_CMD_Takeoff();

private:
    QLabel          *lb_TakeoffAction = nullptr;
    QComboBox       *cb_TakeoffAction = nullptr;

    QPushButton     *btn_Takeoff = nullptr;
    QGridLayout     *widgetLayout   = nullptr;
private:
    void widgetInit();
    void connectSignalAndSlot();
private slots:

    void handle_Takeoff();
public:
signals:
};


#endif
