#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gis_mapview.h"
#include <QGridLayout>
#include "titlewidget.h"

#include <QMessageBox>
#include "systemcommondwidget.h"
#include "systemtoolbar.h"
#include "routeswidget.h"
#include "communicationswidget.h"
#include "rangingtoolbarwidget.h"
#include "dataview.h"
#include "hudopenglview.h"
#include "DMMM.h"
#include "promptwidget.h"
#include "command_widget.h"
#include "chatwidget.h"
#include "systeminfowidget.h"
#include <QThread>
#include <QScreen>
#include "systemconfigwidget.h"
#include "chartwidget.h"
#include "EnumDef.h"
#include "loggerwidget.h"
#include "loggermanagement.h"
#include "parameterconfigwidget.h"
#include "applicatinconfigure.h"
#include "hudwidget.h"
#include "pluginmanager.h"
#include "pluginmanagermodel.h"
#include "videowidget.h"
#include "FCBoardInfo.h"
#include "FunDbg.h"
using namespace Log;


class MainWindow : public QWidget

{
    Q_OBJECT
    Q_ENUMS(WidgetModel)
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum WidgetModel{
        NormolModel = 0,                /*正常模式*/
        RoutesPlanningModel,            /*航线规划模式*/
        RangingModel,                   /*测距模式*/
        AreaModel,                      /*面积测量模式*/
        PointModel,                     /*点信息模式*/
        GetMapPositionModel,            /*获取地图经纬度信息*/
        GetMapRTLModel,                 /*获取返航经纬度信息*/
    };

private:
    TitleWidget     *titleWidget = nullptr;             /*标题栏*/

    GIS_MapView     *mapView = nullptr;                 /*地图视图，底层界面*/
    VideoWidget        *videoWidget = nullptr;


    SystemMenuWidget *systemMenuWidget = nullptr;
    SystemToolBar   *toolBar = nullptr;
    RoutesWidget    *routesWidget = nullptr;
    RangingToolBarWidget *rangingToolBarWidget = nullptr;
    CommunicationsWidget *communicationWidget = nullptr;
    DataView        *dataView = nullptr;
    PromptWidget    *promptWidget = nullptr;
    HUDWidget          *hudOpenGLView = nullptr;
    SystemInfoWidget *systemInfoWidget = nullptr;       /*右侧信息面板*/
    QPushButton     *systemInfominsizeButton = nullptr;
    QGridLayout     *widgetLayout = nullptr;
    QThread         *datapoolThread = nullptr;

    QTimer          *maintimer_10Hz = nullptr;
    CommandWidget   *widget_command = nullptr;
    ChatWidget      *chatWidget = nullptr;
    SystemConfigWidget* widget_CFG = nullptr;
    ChartWidget *chartWidget = nullptr;
    LoggerWidget *logwidget = nullptr;
    ParameterConfigWidget *parameterWidget = nullptr;
    ApplicatinConfigure *appConfigWidget = nullptr;
    PluginManagerWidget           *pluginWidget = nullptr;                          //插件管理
    FCBoardINFO         *FCBoardInfoptr = nullptr;
    PluginManager *plugin = nullptr;
#ifdef GCS_DEBUG_ENABLE
    FunDebug*       w_fundbg = nullptr;
#endif

private:
    bool            videoWidgetIsMin = true;

    int             interfaceWidgetWidth = 0;
    int             interfaceWidgetHeight = 0;

//    int             currentAirID = 0;           //当前飞行器ID

private:
    QGridLayout *mapBaseLayout = nullptr;
    QWidget         *mapBaseWidget = nullptr;

    QGridLayout *cmdBaseLayout= nullptr;

    QGridLayout     *systemInfoBaseLayout = nullptr;

    QMdiArea         *baseConfigWidget = nullptr;


private:
    void systemInit();
    void connectSignalAndSlot();

    void widgetBaseInit();                                  //初始化界面
    void initMapBaseWidget();                          //初始化地图显示界面层            使用QQuickView
    void initCommondBaseWidget();               //初始化指令控件界面层            使用DackWidget
    void initSystemInfoBaseWidget();            //初始化系统信息界面层            使用QWidget
    void initSystemConfigBaseWidget();      //初始化系统配置界面层             使用MDI widget
private:


protected:
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);


private slots:
    void closeButtonPressedSlot();
    void minimizeButtonPressedSlot();
    void selectButtonPressedSlot();
    void connectionButtonPressedSlot();

    /*左侧工具栏*/
    void ToolBar_RangingButtonPressedSlot(bool buttontStatus);
    void ToolBar_RoutePlanningButtonPressedSlot(bool buttontStatus);
    void ToolBar_ElectronicFenceButtonPressedSlot(bool buttontStatus);
    void ToolBar_WaypointMarkerButtonPressedSlot(bool buttontStatus);
    void ToolBar_ToggleActionChangedSlot(bool);


    void routesWidgetCloseSlot();
    /*地图工具栏*/
    void rangingButtonPressedSlot(bool);
    void areaButtonPressedSlot(bool);
    void pointButtonPressedSlot(bool);
    void perspectiveFollowButtonPresssedSlot(bool);
    void seekAirButtonPressedSlot();
    void clearAirPathButtonPressedSlot();


    void appendPointForMousePressedSlot(bool checked,int id);

    /*dataview 响应槽函数*/
    void updateFor100HZTimerSlot();

    void update_gis();

    void update_promptwidget();

    void newConnectGcsIDSlot(bool isopen,int id);

    /*widget_command界面鼠标点选获取经纬度信息 */
    void mousePressedForMapSlot(int type,QGeoCoordinate coor);
    void event_edit_guidedPointModelSlot(QGeoCoordinate coor);

    void req_gis_loc_Slot();

    void handle_DMMM_event(int ev, int linkid);

    void promptWidgetLeftButtonPressedSlot();
    void promptWidgetRightButtonPressedSlot();

    void updateHUDData();                   //更新hud数据

    void basicConfigActionTriggeredSlot();
    void systemConfigActionTriggeredSlot();
    void parameterConfigAcitonTriggeredSlot();
    void communicationConfigActionTriggeredSlot();
    void loggerManagerActionTriggeredSlot();
    void realTimeDataActionTriggeredSlot();
    void panelDataActionTriggeredSlot();
    void pluginManagerActionTriggeredSlot();
    void FCBoardInfoActionActionTriggeredSlot();
    void FunDbgPortActionActionTriggeredSlot();
    void videoWidgetCreateSlot(QWidget *);
    void videoWidgetRemoveSlot(QWidget *wid);

public:
signals:
    void rangingButtonStatusChangedSignal(bool status);
    void routePlanningButtonStatusChangedSignal(bool status);
    void electronicFenceButtonStatusChangedSignal(bool status);
    void waypointMarkerButtonStatusChangedSignal(bool status);


};
#endif // MAINWINDOW_H
