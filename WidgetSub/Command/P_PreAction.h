#ifndef PreACTION_HHHH___
#define PreACTION_HHHH___

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


class WidgetPreAction : public QWidget{
    Q_OBJECT
public:
    WidgetPreAction();
private:
    QPushButton *Action_GyroCaliZero = nullptr;
    QPushButton *Action_BaroCaliZero = nullptr;
    QPushButton *Action_AirspeedCaliZero = nullptr;

    QGridLayout *widgetLayout = nullptr;



private:
    void widgetInit();
    void connectSignalAndSlot();


private slots:

};
#endif
