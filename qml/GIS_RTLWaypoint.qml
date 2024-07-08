import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15


MapItemView {
    id:airRTLWaypoint
    add:Transition {}
    remove:Transition {}
    model:ModelRTLWaypoint

    delegate:MapItemGroup{
        visible: pointIsShow
        MapCircle {
            id: circle
            center: pointCoor
            radius: pointRadius
            border.width: 3
            border.color:"lightblue"//Qt.rgba(255,105,180,0.75)//"#ef5767"
            color:Qt.rgba(0,255,0,0.1)
            opacity: 0.85
        }
        MapQuickItem{
                id:airPointItem
                /*缩放等级默认0固定大小，否则会和缩放等级一起放大缩小*/
                zoomLevel: 0
                coordinate:pointCoor
                anchorPoint: Qt.point(point.width/2,point.height)
                sourceItem:Rectangle{
                    id:pointRect
                    color: Qt.rgba(0,0,0,0)
                    width:50
                    height:50
                    Image {
                        id: point
                        source: "qrc:/img/point/wp_red.png"
                        visible: pointIsShow
                        sourceSize: Qt.size(36, 36)

                    }
                    Text {
                        id:coorLat
                        text:"返航"
                        color: "red"
                        font.pixelSize: 15
                        font.family: "微软雅黑"
                        font.bold: true
        //                anchors.verticalCenter:point.verticalCenter
                        anchors.top: point.bottom
                        anchors.horizontalCenter: point.horizontalCenter
                        visible: pointIsShow
                    }
            }
        }
    }
}


