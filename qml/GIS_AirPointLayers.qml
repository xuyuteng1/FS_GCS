import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15


MapItemView {
    id:airPositionView
    add:Transition {}
    remove:Transition {}
    model:AirPointModel

    delegate:MapItemGroup{
        visible: pointIsShow

        MapQuickItem{
            id:airPointItem
            /*缩放等级默认0固定大小，否则会和缩放等级一起放大缩小*/
            zoomLevel: 0
            coordinate:pointCoor
            property point pressedPoint: Qt.point(0,0)
            property bool  isSelect: false


            anchorPoint: Qt.point(point.width/2,point.height)
            sourceItem:Rectangle{
                id:pointRect
                color: Qt.rgba(0,0,0,0)
                width:50
                height:50
                Image {
                    id: point
                    source: "qrc:/img/point/wp_green.png"
                    sourceSize: Qt.size(36, 36)
                    visible: pointIsShow
                }
                Text {
                    id:coorLat
                    text:"临时航点"
                    color: "red"
                    font.pixelSize: 15
                    font.family: "微软雅黑"
                    font.bold: true
    //                anchors.verticalCenter:point.verticalCenter
                    anchors.top: point.bottom
                    anchors.horizontalCenter: point.horizontalCenter
                    visible: pointIsShow
                }

                MouseArea{
                    anchors.fill: airPointItem
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
        MapCircle {
            id: circle
            center: pointCoor
            radius: pointRadius
            border.width: 3
            border.color:"lightblue"//Qt.rgba(255,105,180,0.75)//"#ef5767"
            color:Qt.rgba(0,255,0,0.1)
            opacity: 0.85
            visible: CircleIsShow
        }
    }
}
