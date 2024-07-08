#ifndef GIS_MODEL_H
#define GIS_MODEL_H
#include "gis_airpositionmodel.h"
#include "gis_airroutesmodel.h"
#include "gis_airnoflyzonemodel.h"
#include "gis_airmaptoolmodel.h"
#include "gis_airpointmodel.h"
#include "gis_model_target.h"
#include "gis_RTLmodel.h"
/* GIS相关model */
class GIS_Models{
public:
    GIS_Models();
    GIS_AirPositionModel *getPositionModel() const;

    GIS_AirRoutesModel *getRoutesModel() const;

    GIS_AirNoFlyZoneModel *getNoFlyZoneModel() const;

    GIS_AirMapToolModel *getMapToolsModel() const;

    GIS_AirPointModel *getPointModel() const;
    GIS_ModelTarget *getModel_Target() const;
    GIS_RTLWaypointModel *getModel_RTLWaypoint() const;
//    int getRoutesIDByRoutesPlanningModel() const;
//    void setRoutesIDByRoutesPlanningModel(int newRoutesIDByRoutesPlanningModel);

    int getMapModel() const;
    void setMapModel(int newMapModel);

public:
    static GIS_AirPositionModel *positionModel;
    static GIS_AirRoutesModel *routesModel;
    static GIS_AirNoFlyZoneModel *noFlyZoneModel;
    static GIS_AirMapToolModel   *mapToolsModel;
    static GIS_AirPointModel     *pointModel;
    static GIS_ModelTarget       *ModelTargetPos;
    static GIS_RTLWaypointModel       *ModelRTLWaypoint;




private:
//    int      routesIDByRoutesPlanningModel = 0;
    int      mapModel = 0;



};

#endif // GIS_MODEL_H
