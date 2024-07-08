#include "gis_model.h"

GIS_AirPositionModel *GIS_Models::positionModel = nullptr;
GIS_AirRoutesModel   *GIS_Models::routesModel = nullptr;
GIS_AirNoFlyZoneModel *GIS_Models::noFlyZoneModel = nullptr;
GIS_AirMapToolModel *GIS_Models::mapToolsModel = nullptr;
GIS_AirPointModel   *GIS_Models::pointModel = nullptr;
GIS_ModelTarget       *GIS_Models::ModelTargetPos = nullptr;
GIS_RTLWaypointModel       *GIS_Models::ModelRTLWaypoint = nullptr;

GIS_Models::GIS_Models()
{
    if(positionModel == nullptr){
        positionModel = new GIS_AirPositionModel();
    }

    if(routesModel == nullptr){
        routesModel = new GIS_AirRoutesModel;
    }

    if(noFlyZoneModel == nullptr){
        noFlyZoneModel = new GIS_AirNoFlyZoneModel();
    }


    if(mapToolsModel == nullptr){
        mapToolsModel = new GIS_AirMapToolModel();
    }

    if(pointModel == nullptr){
        pointModel = new GIS_AirPointModel();
    }
    if(ModelTargetPos == nullptr){
        ModelTargetPos = new GIS_ModelTarget();
    }
    if(ModelRTLWaypoint == nullptr){
        ModelRTLWaypoint = new GIS_RTLWaypointModel();
    }

}

GIS_AirPositionModel *GIS_Models::getPositionModel() const
{
    return positionModel;
}

GIS_AirRoutesModel *GIS_Models::getRoutesModel() const
{
    return routesModel;
}

GIS_AirNoFlyZoneModel *GIS_Models::getNoFlyZoneModel() const
{
    return noFlyZoneModel;
}

//int GIS_Models::getRoutesIDByRoutesPlanningModel() const
//{
//    return routesIDByRoutesPlanningModel;
//}

//void GIS_Models::setRoutesIDByRoutesPlanningModel(int newRoutesIDByRoutesPlanningModel)
//{
//    routesIDByRoutesPlanningModel = newRoutesIDByRoutesPlanningModel;
//}

int GIS_Models::getMapModel() const
{
    return mapModel;
}

void GIS_Models::setMapModel(int newMapModel)
{
    mapModel = newMapModel;
    this->getMapToolsModel()->setData(this->getMapToolsModel()->index(0,0),mapModel,GIS_AirMapToolModel::AirMapToolRoles::ToolModel);
}

GIS_AirPointModel *GIS_Models::getPointModel() const
{
    return pointModel;
}

GIS_ModelTarget *GIS_Models::getModel_Target() const
{
    return ModelTargetPos;
}

GIS_RTLWaypointModel *GIS_Models::getModel_RTLWaypoint() const
{
    return ModelRTLWaypoint;
}

GIS_AirMapToolModel *GIS_Models::getMapToolsModel() const
{
    return mapToolsModel;
}

