#ifndef SYSTEMTOOLBAR_H
#define SYSTEMTOOLBAR_H

#include <QWidget>
#include <QFile>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QToolButton>
#include <QDebug>
#include <QToolBar>
class SystemToolBar : public QToolBar
{
    Q_OBJECT
public:
    SystemToolBar(QWidget *parent = nullptr);

private:
    QAction *rangingButton = nullptr;                   //测距
    QAction *routePlanningButton = nullptr;         //航线规划
    QAction *electronicFenceButton = nullptr;       //电子围栏
    QAction *waypointMarkerButton = nullptr;        //航点标记


private:
    void initWidget();
    void connectSignalAndSlot();

signals:
    void ToolBar_RangingButtonPressedSignal(bool buttontStatus);
    void ToolBar_RoutePlanningButtonPressedSignal(bool buttontStatus);
    void ToolBar_ElectronicFenceButtonPressedSignal(bool buttontStatus);
    void ToolBar_WaypointMarkerButtonPressedSignal(bool buttontStatus);

private slots:
    void rangingButtonPressedSlot();
    void routePlanningButtonPressedSlot();
    void electronicFenceButtonPressedSlot();
    void waypointMarkerButtonPressedSlot();

    void toggleViewActionSlot(bool );

public slots:
    void rangingButtonStatusChangedSlot(bool status);
    void routePlanningButtonStatusChangedSlot(bool status);
    void electronicFenceButtonStatusChangedSlot(bool status);
    void waypointMarkerButtonStatusChangedSlot(bool status);
};



#endif // SYSTEMTOOLBAR_H
