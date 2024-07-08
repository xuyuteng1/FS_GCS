#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include <QListView>
#include <QListWidgetItem>
#include <QListWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
//#include <QHash>
#include "sidebar_flightinfo.h "
#include "sidebar_missioninfo.h "
#include "sidebar_pminfo.h "
#include "sidebar_sensorinfo.h"
#include "sidebar_monitor.h"
#include "sidebar_moveinfo.h"
#include "sidebar_sys_status.h"
#include "sidebar_wind.h"
#include "sidebar_guidance.h"

#include <QDesktopWidget>

class SystemInfoWidget : public QListWidget
{
    Q_OBJECT
public:
    SystemInfoWidget(QWidget *parent = nullptr);

private:
    QMap<QListWidgetItem *,QGroupBox *> widgetMap{};
    QMap<QAction *,QListWidgetItem *>   actionMap{};
    QMap<QString,QListWidgetItem *>     widgetNameMap{};

    QMenu *menu = nullptr;
    SideBarSensorInfo           * statewidget = nullptr;
    SideBarPMInfo               * pm_designer = nullptr;
    SideBarFlightInfo           * flight_designer = nullptr;
    SideBarMissionInfo          * AutoInfo = nullptr;
    SideBarMonitor              * ExtMonitor = nullptr;
    SideBarMoveInfo             * MoveInfo = nullptr;
    SideBarSysStatus            * SysStatus = nullptr;
    SideBarWindInfo             * WindInfo = nullptr;
    SideBarGuidance             * Guidance = nullptr;
    QPushButton                 *miniButton = nullptr;

    bool isShow = true;
private:
    void widgetInit();
    void connectSignalAndSlot();

    void addGroupBoxToListWidget(QListWidgetItem* item,QGroupBox *box);
    void update_pm_widget();
    void update_flight_widget();
    void update_autoinfo_widget();
    void update_ExtMonitor_widget();
    void update_MoveInfo_widget();
    void update_Guidance_widget();
public:
    bool addNewWidgetForListWidget(QString widgetName,QGridLayout *widgetLayout,bool isShow = false);               //初始化时使用
    bool getIsShow() const;
    void setIsShow(bool newIsShow);

    QPushButton *getMiniButton() const;

private slots:
    void mouseRightButtonPressedSlot(const QPoint &pos);
    void menuActionTargetSlot(QAction *action);

    void miniButtonPressedSlot();

public slots:
    void update_sysinfo();


};

#endif // SYSTEMINFOWIDGET_H


