import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15
/*航线规划图层*/
MapItemView {
    id:mapRoutesView
    add:Transition {}
    remove:Transition {}

    model:AirRoutesModel

    delegate:MapItemGroup{

        MapPolyline{
            id:routePath
            line.width: 3
            line.color: "#2D9F8F"
            path:Air_RoutePath
        }

//        MapItemView{

//            model:Air_RouteModel
//            delegate: MapCircle {
//                id: circle
//                center: QtPositioning.coordinate(point_lat,point_lng)
//                radius: 50
//                border.width: 2
//                border.color:"lightgreen"
//                color:Qt.rgba(0,255,0,0.2)
//                opacity: 0.85
////                //鼠标按住后可移动
////                MouseArea {
////                    anchors.fill: parent
////                    drag.target: parent
////                }
//            }
//        }
        MapItemView{
            id:mapRouteView
            add:Transition {}
            remove:Transition {}

            model:Air_RouteModel
            delegate: MapQuickItem{
                id:airRoutePointItem
                property point pressedPoint: Qt.point(0,0)
                property bool  isSelect: false

                zoomLevel: 0
                coordinate{
                    latitude: point_lat
                    longitude: point_lng
                }

                anchorPoint: Qt.point(airRoutePointItem.width/2,airRoutePointItem.height - 5)
                sourceItem:Rectangle{
                    id:pointRect
                    color: Qt.rgba(0,0,0,0)
                    width:50
                    height:50

                    Image{
                        id:point
                        width:50
                        height:50
                        x:pointRect.x
                        y:pointRect.y
                        source: "qrc:/img/point/point_red.png"
                    }

//                    Rectangle {
//                        width: 23
//                        height: 23
//                        anchors.centerIn: parent
//                        color: "lightblue"
//                        radius: width
//                        ColorAnimation on color {
//                            from: Qt.rgba(0,255,0,0)
//                            to:Qt.rgba(0,255,0,255)
//                            duration:1000;
//                            loops:Animation.Infinite
//                        }

//                    }

                    Text {
                        id: pointText
                        text: point_id
                        width:parent.width
                        height:parent.height
                        anchors.fill: point
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 12
                        font.family: "SimSun"
                        font.weight: Font.DemiBold
                        color: "yellow"
                    }



                    MouseArea{
                        anchors.fill: pointRect
//                        acceptedButtons: Qt.AllButtons
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        preventStealing:true                //此属性保存是否从此MouseArea中窃取鼠标事件。
                        onPressed: {
                            if(airRoutePointItem.isSelect === false){
                                pressedPoint = Qt.point(mouse.x - airRoutePointItem.width/2,mouse.y + (airRoutePointItem.height - 5) / 2)
                                if(mouse.button == Qt.RightButton){
                                    point.source = "qrc:/img/point/point_yellow.png"
                                }
                                else{
                                    point.source = "qrc:/img/point/point_green.png"
                                }

                                airRoutePointItem.isSelect = true;
                            }
                        }

                        onReleased: {
                            if(airRoutePointItem.isSelect){
                                pressedPoint = Qt.point(0,0)
                                point_Coor = airRoutePointItem.coordinate
                                point.source = "qrc:/img/point/point_red.png"
                                airRoutePointItem.isSelect = false;
                            }
                        }
                        onCanceled: {
                            if(airRoutePointItem.isSelect){
                                pressedPoint = Qt.point(0,0)
                                point_Coor = airRoutePointItem.coordinate
                                point.source = "qrc:/img/point/point_red.png"
                                airRoutePointItem.isSelect = false;
                            }
                        }

                        onPositionChanged: {
                            if(airRoutePointItem.isSelect){
                                airRoutePointItem.coordinate = gis_basemap.toCoordinate(Qt.point(mapToGlobal(mouse.x,mouse.y).x - pressedPoint.x,mapToGlobal(mouse.x,mouse.y).y - pressedPoint.y));
                            }
                        }
                    }
                }
            }
        }
    }
}
