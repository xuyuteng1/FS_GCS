#include "gis_mapview.h"
#include "DMMM.h"
#include <QDesktopWidget>

GIS_MapView *GIS_MapView::singleton;
namespace Qt {
    GIS_MapView *GISMap() {
        return GIS_MapView::get_singleton();
    };
};

GIS_MapView::GIS_MapView(QWidget *parent)
    : QQuickWidget(parent)
{
    if (singleton != nullptr) {
        qDebug()<<("GIS_MapView must be singleton");
        return;
    }
    singleton = this;
    if(this->models == nullptr){
        this->models = new GIS_Models;
    }
    if(this->airPositionModel == nullptr){
        this->airPositionModel = this->models->getPositionModel();
        this->rootContext()->setContextProperty("AirModel",this->airPositionModel);
    }

    if(this->airRoutesModel == nullptr){
        this->airRoutesModel = this->models->getRoutesModel();
        this->rootContext()->setContextProperty("AirRoutesModel",this->airRoutesModel);
    }

    if(this->mapToolModel == nullptr){
        this->mapToolModel = this->models->getMapToolsModel();
        this->rootContext()->setContextProperty("AirMapToolModel",this->mapToolModel);
    }

    if(this->pointModel == nullptr){
        this->pointModel = this->models->getPointModel();
        this->rootContext()->setContextProperty("AirPointModel",this->pointModel);
    }
    if(this->Model_TargetPos == nullptr){
        this->Model_TargetPos = this->models->getModel_Target();
        this->rootContext()->setContextProperty("ModelTargetPos",this->Model_TargetPos);
    }
    if(this->Model_RTLWaypoint == nullptr){
        this->Model_RTLWaypoint = this->models->getModel_RTLWaypoint();
        this->rootContext()->setContextProperty("ModelRTLWaypoint",this->Model_RTLWaypoint);
    }

    widgetInit();

    connectSignalAndSlot();
    mapInit();

//    this->setFixedSize(QApplication::desktop()->screen()->size());
//    emit mapPluginSetSignal("googlemaps","Satellite");
}

int GIS_MapView::getMapMode() const
{
    return this->mapModeNum;
}

void GIS_MapView::setMapMode(int value)
{
    if(value != this->mapModeNum){
        this->mapModeNum = value;
        this->models->setMapModel(value);
        emit mapModeChanged(QVariant(this->mapModeNum));
    }
}

void GIS_MapView::widgetInit()
{
    this->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->setSource(QUrl("qrc:/qml/GIS_Map.qml"));
}

void GIS_MapView::connectSignalAndSlot()
{
    connect(static_cast<QObject *>(this->rootObject()),SIGNAL( mouseEventSignal(QVariant,QVariant)),this,SLOT(mouseEventSlot(QVariant,QVariant)));
    connect(static_cast<QObject *>(this->rootObject()),SIGNAL( coordinatChangedSignal(QVariant,QVariant)),this,SLOT(screenCoordinateSlot(QVariant,QVariant)));
    connect(this,SIGNAL(resizeSignal(QVariant,QVariant)),static_cast<QObject *>(this->rootObject()),SLOT( resizeEvent(QVariant,QVariant)));
    connect(this,SIGNAL(setCenterCoordinateSiganl(QVariant)),static_cast<QObject *>(this->rootObject()),SLOT( setCenterCoordinate(QVariant)));

    connect(this,SIGNAL(mapModeChanged(QVariant)),static_cast<QObject *>(this->rootObject()),SLOT(onMapModeChangedFunction(QVariant)));

    connect(this,SIGNAL(mapPluginSetSignal(QVariant,QVariant)),static_cast<QObject*>(this->rootObject()),SLOT(onMapPluginTypeSetSlot(QVariant,QVariant)));
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&GIS_MapView::handle_DMMM_event);
}

void GIS_MapView::mapInit()
{
    emit mapPluginSetSignal(mapData->getMapNameStr(),mapData->getMapTypeStr());
}

GIS_RTLWaypointModel *GIS_MapView::getModel_RTLWaypoint() const
{
    return Model_RTLWaypoint;
}

GIS_AirPointModel *GIS_MapView::getPointModel() const
{
    return pointModel;
}

bool GIS_MapView::getCenterAirFlag() const
{
    return centerAirFlag;
}

void GIS_MapView::setCenterAirFlag(bool newCenterAirFlag)
{
    centerAirFlag = newCenterAirFlag;
}


void GIS_MapView::updateMapView()
{
    if(centerAirFlag == false || Qt::DMMM()->getMain_link_id() == -1){
        return;
    }
    double lat = this->airPositionModel->dataForID(Qt::DMMM()->getMain_link_id(),GIS_AirPositionModel::AirPositionDataRoles::DATA_AirLat).toDouble();
    double lng = this->airPositionModel->dataForID(Qt::DMMM()->getMain_link_id(),GIS_AirPositionModel::AirPositionDataRoles::DATA_AirLng).toDouble();

    QGeoCoordinate nowCoor = QGeoCoordinate(lat,lng);

    QGeoCoordinate rightTopCoor = QGeoCoordinate(this->minCoordinate.latitude(),this->maxCoordinate.longitude());
    int distancelng = this->minCoordinate.distanceTo(rightTopCoor) * 0.95f;
    int disranceLat = this->maxCoordinate.distanceTo(rightTopCoor) * 0.95f;

    QGeoCoordinate latMinCoor(lat,this->minCoordinate.longitude());
    QGeoCoordinate latMaxCoor(lat,this->maxCoordinate.longitude());

    QGeoCoordinate lngMinCoor(this->minCoordinate.latitude(),lng);
    QGeoCoordinate lngMaxCoor(this->maxCoordinate.latitude(),lng);

    int distanceMinLat = nowCoor.distanceTo(latMinCoor);
    int distanceMaxLat = nowCoor.distanceTo(latMaxCoor);


    int distanceMinLng = nowCoor.distanceTo(lngMinCoor);
    int distanceMaxLng = nowCoor.distanceTo(lngMaxCoor);

    if(distanceMinLat > distancelng || distanceMaxLat > distancelng || distanceMinLng > disranceLat || distanceMaxLng > disranceLat)
    {
        QGeoCoordinate coor(lat,lng);
        emit setCenterCoordinateSiganl(QVariant::fromValue<QGeoCoordinate>(coor));

    }
}

bool GIS_MapView::getWidgetMiniSize() const
{
    return widgetMiniSize;
}

void GIS_MapView::setWidgetMiniSize(bool newWidgetMiniSize)
{
    widgetMiniSize = newWidgetMiniSize;
}

void GIS_MapView::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
//    if(parent()!=nullptr){
//        this->setFixedSize(parentWidget()->size());
//    }

    static bool resizeFlag = true;
    if(resizeFlag){
        emit resizeSignal(QVariant(this->width()),QVariant(this->height()));
        resizeFlag = false;
    }

    this->update();
}


void GIS_MapView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(widgetMiniSize){
            emit gisViewPressedSignal();
        }
    }
    return QQuickWidget::mousePressEvent(event);

}



void GIS_MapView::mouseEventSlot(QVariant mode,QVariant point)
{

    switch(mode.toInt()){
    case 0:{

        break;
    }case 1:{                       //航线规划模式
        QGeoCoordinate coorPoint = point.value<QGeoCoordinate>();
        if(this->models->getMapModel() == mode){
            this->models->routesModel->addRouteItemPoint(this->models->routesModel->getCurrentRouteID(),coorPoint.longitude(),coorPoint.latitude());
        }
        break;
    }case 2:{
        QGeoCoordinate coorPoint = point.value<QGeoCoordinate>();
        this->models->getMapToolsModel()->setData(this->models->getMapToolsModel()->index(0,0),QVariant::fromValue<QGeoCoordinate>(coorPoint),GIS_AirMapToolModel::AirMapToolRoles::ToolMouseClickedPoint);
        break;
    }
    case 3:{
        QGeoCoordinate coorPoint = point.value<QGeoCoordinate>();
        this->models->getMapToolsModel()->setData(this->models->getMapToolsModel()->index(0,0),QVariant::fromValue<QGeoCoordinate>(coorPoint),GIS_AirMapToolModel::AirMapToolRoles::ToolMouseClickedPoint);
        break;
    }case 5:{
        QGeoCoordinate coorPoint = point.value<QGeoCoordinate>();

        this->pointModel->setData(this->models->getMapToolsModel()->index(0,0),QVariant(true),GIS_AirPointModel::DATA_PointIsShow);
        this->pointModel->setData(this->models->getMapToolsModel()->index(0,0),QVariant::fromValue<QGeoCoordinate>(coorPoint),GIS_AirPointModel::DATA_PointCoor);
        emit mousePressedForMapSignal(5,coorPoint);
        break;
    }
    case 6:{
            QGeoCoordinate coorPoint = point.value<QGeoCoordinate>();
            this->getModel_RTLWaypoint()->setData(this->models->getModel_RTLWaypoint()->index(0,0),QVariant::fromValue<QGeoCoordinate>(coorPoint),GIS_AirPointModel::DATA_PointCoor);
            this->setMapMode(0);
            break;
    }default:
        break;
    }

}

/*获取屏幕坐标点 type == 0 屏幕左上角经纬度，type == 1 屏幕右下角经纬度*/
void GIS_MapView::screenCoordinateSlot(QVariant type, QVariant coor)
{
    if(type.toInt() == 0){
        this->minCoordinate = coor.value<QGeoCoordinate>();
    }else if(type.toInt() == 1){
        this->maxCoordinate = coor.value<QGeoCoordinate>();
    }
}

void GIS_MapView::handle_DMMM_event(int ev, int linkid)
{
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
        {
            if(this->Model_TargetPos!=nullptr){
                FlyLink* link = Qt::DMMM()->getFlyLink_main();
                if(link != nullptr){
                    Q_DMMM::DataPool_t data = Qt::DMMM()->getData_main();
                    int lat = data.flylink.tTarget.TargetLat;
                    int lng = data.flylink.tTarget.TargetLng;
                    bool visable = true;
                    if(lat == 0 && lng == 0){
                        visable = false;
                    }
//                    QGeoCoordinate coor = QGeoCoordinate((double)lat*1e-7,(double)lng*1e-7);
                    this->Model_TargetPos->update_target((double)lat*1e-7,(double)lng*1e-7,visable);

                }
            }
        }
        break;



        default:break;
    }
}

void GIS_MapView::updateGcsOnTimerSlot()
{

}

void GIS_MapView::mapSourcesChangedSlot()
{
    emit mapPluginSetSignal(mapData->getMapNameStr(),mapData->getMapTypeStr());
}
