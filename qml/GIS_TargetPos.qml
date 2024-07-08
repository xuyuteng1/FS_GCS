import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15


MapItemView {
    id:airPositionView
    add:Transition {}
    remove:Transition {}
    model:ModelTargetPos

    delegate:MapQuickItem{
        id:airPointItem
        /*缩放等级默认0固定大小，否则会和缩放等级一起放大缩小*/
        zoomLevel: 0
        coordinate:pointCoor
        property point pressedPoint: Qt.point(0,0)
        property bool  isSelect: false

        sourceItem:Rectangle{
            id:pointRect
            width: 45
            height: 45
            color: Qt.rgba(255,255,0,0.8)
            radius: width
            visible: pointIsShow
            anchors.verticalCenter:airPointItem.verticalCenter
            anchors.horizontalCenter: airPointItem.horizontalCenter
//            state:"dd";
            ColorAnimation on color {
                from: Qt.rgba(255,255,0,0.1)
                to:Qt.rgba(255,255,0,0.7)
                duration:1000;
                loops:Animation.Infinite
            }
            Text {
                id:coorLat
                text:"T"
                color: "lightyellow"
                font.pixelSize: 15
                font.family: "微软雅黑"
                font.bold: true
                anchors.centerIn: parent
                visible: pointIsShow
            }
        }

    }

}
