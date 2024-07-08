#ifndef SYSTEMCOMMONDWIDGET_H
#define SYSTEMCOMMONDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QStyle>
#include <QObject>
#include <QDebug>
#include <QObject>
#include <QStackedWidget>
#include <QToolButton>
#include "globalObserver.h"
#include <QMenu>
#include <QWidgetAction>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "DMMM.h"
#include <QtLocation>
#include <QMessageBox>
#include <QDockWidget>

#include <QGraphicsView>
#include <QGraphicsScene>

#include "svggraphicswidgetitem.h"
#include "svgbuttonitem.h"
#include "svgborderitem.h"

#include "C_MotorWidget.h"
#include "C_TakeoffWidget.h"
#include "C_LandWidget.h"
#include "C_WaypointWidget.h"
#include "C_RoutesButtonWidget.h"
#include "C_SetModeWidget.h"
#include "P_SetModeWidget.h"
#include "P_PreAction.h"
#include "P_RTL.h"
#include "P_Takeoff.h"
#include "P_Waypoint.h"
#include "P_LandWidget.h"


//菜单栏指令界面容器
class SystemCommondWidgetContainer : public QStackedWidget{
    Q_OBJECT
public:
    SystemCommondWidgetContainer(QWidget *parent = nullptr);
    void addCommondWidget(QString name,QWidget *widget);
    void ClearCommondWidget();

    bool widgetIsExist(QString name);

private:
    QMap<QString,QWidget *> widgetMap;

public slots:
    void chooseWidgetChangeSlot(QString widgetName);

};


//菜单栏按键容器
class SystemMenuButtonContainer : public QWidget{
    Q_OBJECT
public:
    SystemMenuButtonContainer(QWidget *parent = nullptr);

    void addMenuButton(QString name,QString buttnText,QIcon &ico,QString buttonObjectName = "SystemMenuButtonContainer");                                                          //默认clicked信号触发后发出buttonPressedSignal信号
    void addMenuButton(QString name,QString buttnText,QString signalName,QIcon& ico,QString buttonObjectName = "SystemMenuButtonContainer");                                       //默认clicked信号触发后发出buttonPressedSignal信号
    void ClearMenuButton();

    bool buttonIsExist(QString name);

private:
    QHBoxLayout *widgetLayout = nullptr;

    QMap<QString,QToolButton *>buttonMap;
private:
    void initWidget();


public:
signals:
    void buttonPressedSignal(QString name);

};


class SystemMenuWidget : public QWidget{
    Q_OBJECT
public:
    SystemMenuWidget(QWidget *parent = nullptr);

    void addSystemMenu(QString buttonName,QString buttonText,QWidget *widget,QIcon ico);                                          //添加一个按钮，绑定一个界面
    void addSystemMenu(QString buttonName,QString buttonText,QString signalName,QIcon ico);                                     //添加一个按钮，绑定一个信号

private:
    SystemMenuButtonContainer *buttonContainer = nullptr;                                                   //按键容器
    SystemCommondWidgetContainer *commondContainer = nullptr;                                     //指令界面容器

    QGraphicsScene *comondScene  = nullptr;
    QGraphicsView   *commondView = nullptr;

    QGraphicsScene *buttonScene = nullptr;
    QGraphicsView   *buttonView = nullptr;

    SvgButtonItem  *buttonViewButton = nullptr;
    SvgButtonItem  *commondViewButton = nullptr;

    SvgBorderItem  *buttonViewBorder = nullptr;
    SvgBorderItem  *commondViewBorder = nullptr;

    SvgGraphicsWidgetItem *buttonViewWidget = nullptr;
    SvgGraphicsWidgetItem *commondViewWidget = nullptr;

    QGridLayout *widgetLayout = nullptr;

    // 多旋翼
    C_MotorUnlockWidget     *C_Widget_motorUnlock   = nullptr;
    C_TakeoffMenuWidget     *C_Widget_takeoffMenu   = nullptr;
    C_LandWidget            *C_Widget_Land          = nullptr;
    C_WaypointWidget        *C_Widget_waypoint      = nullptr;
    C_RoutesButtonWidget    *C_Widget_routesButton  = nullptr;
    C_SetModeWidget         *C_Widget_SetModeWidget = nullptr;
    // 固定翼
    P_SetModeWidget         *P_Widget_SetModeWidget = nullptr;
    WidgetPreAction         *P_Widget_preaction     = nullptr;
    P_CMD_RTL               *P_Widget_RTL           = nullptr;
    P_CMD_Takeoff           *P_Widget_Takeoff       = nullptr;
    P_CMD_Waypoint          *P_Widget_Waypoint      = nullptr;
    P_LandWidget            *P_Widget_Land          = nullptr;
private:
    void widgetInit();
    void connectSignalAnsSlot();
    void AddCopterWidget();
    void AddPlaneWidget();

private slots:
    void buttonPressedSlot(QString name);
    void handle_DMMM_event(int ev, int linkid);
};



#endif // SYSTEMCOMMONDWIDGET_H
