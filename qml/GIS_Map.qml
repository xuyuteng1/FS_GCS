import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtLocation 5.15
import QtPositioning 5.15
import QtQuick.Window 2.15

Rectangle {
    visible: true
    id:gis_map
    width:0
    height:0
    anchors.margins: 0
    /*signal*/
    signal mouseEventSignal(var mode,var coor);
    signal coordinatChangedSignal(var type,var coor);
    property int mapMode: 0
    property int keyPressedMode: 0


    GIS_BaseMap{
        id:gis_baseMap
        anchors.left: gis_map.left
        anchors.right: gis_map.right
        anchors.top: gis_map.top
        anchors.bottom: gis_map.bottom

    }


/*slot*/




/*funciton*/
    /*界面大小变化时*/
    function resizeEvent(width,height){
        gis_map.width = width;
        gis_map.height = height;
        gis_baseMap.width = width;
        gis_baseMap.height = height;
//        console.log(gis_map.width,gis_map.height,gis_baseMap.width,gis_baseMap.height)
    }

    /*添加新的飞行器到地图中*/
    function addNewAirPointToMap(id ,coor){
        var ret = gis_baseMap.addNewAirPointToMap(id,coor);
    }

    function onMapModeChangedFunction(mode){
//        console.log(mode);
        mapMode = mode;
        gis_baseMap.mapMode = mode;
    }

    function setCenterCoordinate(coor){
        gis_baseMap.setCenterCoordinate(coor);
    }

    function onMapPluginTypeSetSlot(name,type){
        gis_baseMap.onMapPluginTypeSetSlot(name,type);
    }
}
