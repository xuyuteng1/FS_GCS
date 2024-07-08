#ifndef pSetModeWidget_H____
#define pSetModeWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QMessageBox>

#include <QtLocation>
#include <QGroupBox>


class P_SetModeWidget : public QWidget{
    Q_OBJECT
public:
    P_SetModeWidget();

private:
    QPushButton *Action_MANUAL = nullptr;
    QPushButton *Action_CIRCLE = nullptr;
    QPushButton *Action_STABILIZE = nullptr;
    QPushButton *Action_TRAINING = nullptr;
    QPushButton *Action_ACRO = nullptr;
    QPushButton *Action_FLY_BY_WIRE_A = nullptr;
    QPushButton *Action_FLY_BY_WIRE_B = nullptr;
    QPushButton *Action_CRUISE = nullptr;
    QPushButton *Action_AUTOTUNE = nullptr;
    QPushButton *Action_AUTO = nullptr;
    QPushButton *Action_RTL = nullptr;
    QPushButton *Action_LOITER = nullptr;
    QPushButton *Action_TAKEOFF = nullptr;
    QPushButton *Action_GUIDED = nullptr;

    QGridLayout *widgetLayout = nullptr;
    QGridLayout *Layout_Box_Assi = nullptr;
    QGridLayout *Layout_Box_Auto = nullptr;
    QGroupBox   *Box_Assi = nullptr;
    QGroupBox   *Box_Auto = nullptr;



private:
    void widgetInit();
    void connectSignalAndSlot();

    void set_mode(uint8_t mode_number);

private slots:

};
#endif
