import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15


MapItemView {
    id:airPositionView
    add:Transition {}
    remove:Transition {}
    model:ModelRTLWaypoint
    delegate:MapQuickItem{
        id:airPointItem
        /*缩放等级默认0固定大小，否则会和缩放等级一起放大缩小*/
        zoomLevel: 0
        coordinate:pointCoor
        property point pressedPoint: Qt.point(0,0)
        property bool  isSelect: false
        anchorPoint: Qt.point(point.width/2,point.height)
                MapItemView{

                    model:ModelRTLWaypoint
                    delegate: MapCircle {
                        id: circle
                        center: QtPositioning.coordinate(34,108)
                        radius: 50
                        border.width: 2
                        border.color:"lightgreen"
                        color:Qt.rgba(0,255,0,0.2)
                        opacity: 0.85
        //                //鼠标按住后可移动
        //                MouseArea {
        //                    anchors.fill: parent
        //                    drag.target: parent
        //                }
                    }
                }
        sourceItem:Rectangle{
            id:pointRect
            color: Qt.rgba(0,0,0,0)
            width:50
            height:50
            visible: pointIsShow
            Image {
                id: point
                source: "qrc:/img/point/point_green.png"
            }
            Text {
                id:coorLat
                text:"返航点"
                color: "#f3d751"
                font.pixelSize: 15
                font.family: "幼圆"
                font.bold: true
//                anchors.verticalCenter:point.verticalCenter
                anchors.top: point.bottom
                anchors.horizontalCenter: point.horizontalCenter
            }

            MouseArea{
                anchors.fill: pointRect
                acceptedButtons: Qt.AllButtons
                preventStealing:true                //此属性保存是否从此MouseArea中窃取鼠标事件。
                onPressed: {
                    if(airPointItem.isSelect === false){
                        console.log(point.source.toString())
                        pressedPoint = Qt.point(mouse.x - airPointItem.width/2,mouse.y + (airPointItem.height - 5) / 2)
                        point.source = "qrc:/img/point/point_yellow.png"
                        airPointItem.isSelect = true;
                        console.log(point.source.toString())
                    }
                }

                onReleased: {
                    if(airPointItem.isSelect){
                        pressedPoint = Qt.point(0,0)
                        pointCoor = airPointItem.coordinate
                        point.source = "qrc:/img/point/point_red.png"
                        airPointItem.isSelect = false;
                        console.log(point.source.toString())
                    }
                }

                onCanceled: {
                    if(airPointItem.isSelect){
                        pressedPoint = Qt.point(0,0)
                        pointCoor = airPointItem.coordinate
                        point.source = "qrc:/img/point/point_red.png"
                        airPointItem.isSelect = false;
                        console.log(point.source.toString())
                    }
                }

                onPositionChanged: {
                    if(airPointItem.isSelect){
                        console.log(mouse.x,mouse.y,Qt.point(mapToGlobal(mouse.x,mouse.y).x - pressedPoint.x,mapToGlobal(mouse.x,mouse.y).y - pressedPoint.y))
                        airPointItem.coordinate = gis_basemap.toCoordinate(Qt.point(mapToGlobal(mouse.x,mouse.y).x - pressedPoint.x,mapToGlobal(mouse.x,mouse.y).y - pressedPoint.y),false);
                        console.log(airPointItem.coordinate)
                    }
                }
            }
        }
    }
}
