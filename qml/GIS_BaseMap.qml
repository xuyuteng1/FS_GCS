import QtQuick 2.0
import QtLocation 5.15
import QtPositioning 5.15


Rectangle {
    width: parent.width
    height: parent.height
    id:map_base


    property var mousePressPoint: QtPositioning.coordinate(0,0,0)
    property var mouseReleasePoint: QtPositioning.coordinate(0,0,0)
    property int mapMode: 0

    Plugin {
        id: mapPlugin
        name: "bingmaps"//"bingmaps"//TiMap"//"TiMap"//"bingmaps"//"googlemaps"//"amap" //"esri"// "osm"//"esri"//"esri" // "mapboxgl", "esri", ...
    }

    Map {
        id:gis_basemap
        anchors.fill: map_base
        plugin: mapPlugin
        center: QtPositioning.coordinate(34.0180205, 108.7045348)
        zoomLevel: 19
        scale:1
        layer.enabled: true
        layer.samples: 8
        Component.onCompleted: {
            updateActiveMapType(this,"Bing Satellite Map");
//            updateActiveMapType(this,"Satellite"); //qml: Road Map  qml: Satellite qml: Terrain qml: Hybrid
        }

        Map {
            anchors.fill: parent
            plugin: Plugin {
                name: "TiMap"
//                name:"bingmaps"
                PluginParameter {
                    name: "mapProvider"
                    value: "tiandituImg"
                }
                PluginParameter {
                    name: "format"
                    value: "png"
                }
                //弃用,缓存已使用数据库,代码内默认了数据库存放于程序运行当前目录
            }

            gesture.enabled: false
            center: parent.center
            color: 'transparent' // Necessary to make this map transparent
            minimumFieldOfView: parent.minimumFieldOfView
            maximumFieldOfView: parent.maximumFieldOfView
            minimumTilt: parent.minimumTilt
            maximumTilt: parent.maximumTilt
            minimumZoomLevel: parent.minimumZoomLevel
            maximumZoomLevel: parent.maximumZoomLevel
            zoomLevel: parent.zoomLevel
            tilt: parent.tilt;
            bearing: parent.bearing
            fieldOfView: parent.fieldOfView
            z: parent.z + 0;
            Component.onCompleted: {
                updateActiveMapType(this,"Tianditu Street");
            }

        }

        MouseArea{
            anchors.fill:parent
            onClicked: {
                var coorPoint = gis_basemap.toCoordinate(Qt.point(mouse.x,mouse.y),0);
                gis_map.mouseEventSignal(mapMode,coorPoint);
            }
        }
        /* DisPlay Flight TargetPos */
        GIS_TargetPos{
            id:targetpos
        }
        /*路径规划层*/
        GIS_RoutesLayers{
            id:airRoutes
        }

        GIS_NoFlyZoneLayers{
            id:airNoFlyZone
        }

        GIS_MapToolLayers{
            id:airMapTool
        }

        GIS_AirPointLayers{
            id:airPoint
        }

        /* DisPlay RTL Waypoint */
        GIS_RTLWaypoint{
            id:rtlWP
        }

        /*飞行器显示图层*/
        GIS_AirPositionLayers{
            id:airPosition
        }

        onCenterChanged: {
            gis_map.coordinatChangedSignal(0,gis_basemap.toCoordinate(Qt.point(0,0),0));
            gis_map.coordinatChangedSignal(1,gis_basemap.toCoordinate(Qt.point(width,height),0));

        }
    }

    function addNewAirPointToMap(id ,coor){
        return airPosition.addAirPosition(id,coor);
    }
    function setCenterCoordinate(coor){
        gis_basemap.center = coor;
    }
    //更新地图显示类型
    function updateActiveMapType(control,para) {
        for (var i = 0; i < control.supportedMapTypes.length; i++) {
            console.log(control.supportedMapTypes[i].name);
            if (para === control.supportedMapTypes[i].name) {
                control.activeMapType = control.supportedMapTypes[i]
                return
            }
        }
    }

    function onMapPluginTypeSetSlot(name,type){
            if(name!=="googlemaps" && name!=="bingmaps" && name!=="TiMap" && name!=="esri"){
                mapPlugin.name = "bingmaps";
                type = "Bing Satellite Map";
            }
            else{
                mapPlugin.name = name;
            }
            updateActiveMapType(gis_basemap,type);

        }

}
