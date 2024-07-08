#ifndef C_RoutesButtonWidget_H____
#define C_RoutesButtonWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QMessageBox>

#include <QtLocation>


class C_RoutesButtonWidget:  public QWidget{
    Q_OBJECT
public:
    C_RoutesButtonWidget();

private:
    QSpinBox    *changedCurrentRoutePointSpinBox = nullptr;
    QPushButton *changedCurrentRoutePointButton = nullptr;
    QPushButton *beginRoutesTaskButton = nullptr;
    QPushButton *reloadRoutesTaskButton = nullptr;

    QGridLayout *widgetLayout = nullptr;

private:
    void widgetInit();

    void connectSignalAndSlot();

private slots:
    void changedCurrentRoutePointButtonPressedSlot();
    void beginRoutesTaskButtonPressedSlot();
    void reloadRoutesTaskButtonPressedSlot();

};


#endif
