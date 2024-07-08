#ifndef GIS_MAPVIEW_H
#define GIS_MAPVIEW_H

#include <QQuickView>
#include <QQuickWidget>
#include <QResizeEvent>
#include <QQmlContext>
#include <QGridLayout>
#include <QKeyEvent>
#include <QQuickItem>
#include <QGeoCoordinate>
#include <QMouseEvent>
#include <QTableView>
#include <QModelIndex>
//#include "gis_airpositionmodel.h"
#include "systemdata.h"
#include "gis_model.h"
#include <QTimer>
#include <QMessageBox>

class GIS_MapView : public QQuickWidget
{
    Q_OBJECT
public:
    GIS_MapView(QWidget *parent = nullptr);


    GIS_MapView(const GIS_MapView &other) = delete;
    GIS_MapView &operator=(const GIS_MapView&) = delete;
    static GIS_MapView* get_singleton(void) {
            return singleton;
    }

    int getMapMode() const;
    void setMapMode(int value);

    bool getWidgetMiniSize() const;
    void setWidgetMiniSize(bool newWidgetMiniSize);

    void updateMapView();

    bool getCenterAirFlag() const;
    void setCenterAirFlag(bool newCenterAirFlag);

    GIS_AirPointModel *getPointModel() const;

    GIS_RTLWaypointModel *getModel_RTLWaypoint() const;

private:
    void widgetInit();
    void connectSignalAndSlot();
    void mapInit();

private:
    QQuickView *gismapView = nullptr;
    QGridLayout *widgetLayout = nullptr;
    GIS_AirPositionModel    *airPositionModel = nullptr;         /*飞行器位置信息model*/
    GIS_AirRoutesModel      *airRoutesModel = nullptr;
    GIS_AirMapToolModel     *mapToolModel = nullptr;
    GIS_AirPointModel       *pointModel = nullptr;
    GIS_ModelTarget       *Model_TargetPos = nullptr;
    GIS_RTLWaypointModel       *Model_RTLWaypoint = nullptr;
    QTimer *airPositionTestTimer = nullptr;
    GIS_Models *models = nullptr;
private:
    int                     mapModeNum = 0;
//    int                     currentRoutesID = 0;
    bool                    widgetMiniSize = false;

    bool                    centerAirFlag = false;
    int                     centerAirID = -1;

    QGeoCoordinate          minCoordinate;                      //屏幕左上角经纬度
    QGeoCoordinate          maxCoordinate;                      //屏幕右下角经纬度

    MapData                      *mapData = SystemData::getMapData();
    static GIS_MapView *singleton;
protected:
    void resizeEvent(QResizeEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *event);
    QTableView *viewTest = nullptr;

signals:
    void resizeSignal(QVariant width,QVariant height);
    void setCenterCoordinateSiganl(QVariant coor);
    void mapModeChanged(QVariant model);
    void gisViewPressedSignal();

    void mousePressedForMapSignal(int, QGeoCoordinate);

    void mapPluginSetSignal(QVariant,QVariant);

private slots:
    void mouseEventSlot(QVariant,QVariant);
    void screenCoordinateSlot(QVariant type,QVariant coor);

    void handle_DMMM_event(int ev,int linkid = 0);
public slots:
    void updateGcsOnTimerSlot();
    void mapSourcesChangedSlot();

};

namespace Qt {
    GIS_MapView *GISMap();
};
#endif // GIS_MAPVIEW_H
