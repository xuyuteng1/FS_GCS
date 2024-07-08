import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15


MapItemView {
    id:airPositionView
    add:Transition {}
    remove:Transition {}
    model:AirModel

    delegate:MapItemGroup{
        MapPolyline{
            id:trackPath
            line.width: 5
            line.color: 'red'
            path:AirTrackPath

        }

        MapQuickItem{
            id:airPositionItem
            /*缩放等级默认0固定大小，否则会和缩放等级一起放大缩小*/
            zoomLevel: 0
            coordinate{
                latitude: AirLat
                longitude: AirLng
            }


            anchorPoint: Qt.point(air.width/2,air.height/2)

            rotation: AirCourse % 360

            sourceItem:Image {
                id: air
                source: AirImage
                visible: AirVisible
            }


            MouseArea{
                anchors.fill:parent
                acceptedButtons: Qt.AllButtons
                onClicked: {
//                    console.log("clicked");
                }
            }
        }
        Text {
            id:airNameID
            text:MAVID
            color: "yellow"
            font.pixelSize: 20
            font.family: "幼圆"
            font.bold: true
//                anchors.centerIn: parent.centerIn
            anchors.verticalCenter:airPositionItem.verticalCenter
            anchors.horizontalCenter: airPositionItem.horizontalCenter
        }

        // 飞行高度显示
        Rectangle{
            id:airInfo_height
            width:80
            height: 42
            color:"#161929"
            anchors.bottom: airPositionItem.top
            anchors.bottomMargin: 2

            anchors.right: airPositionItem.horizontalCenter
            opacity: 0.75
            visible: AirTextVisible

            border.color:"#1677ff"
            radius: 4
                Text {
                    id:airRelHigNameText
                    text: "高度(m)"
                    color: "white"
                    font.bold: true
                    font.pixelSize: 12
                    anchors.horizontalCenter:  parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    font.family: "Microsoft YaHei"
                }
                Text {
                    id:airRelHigText
                    text: AirRelativeAlititude.toFixed(1)
                    color: "yellow"
                    font.pixelSize: 14
                    font.bold: true
                    font.family: "Microsoft YaHei"

                    anchors.horizontalCenter:  parent.horizontalCenter
                    anchors.top: airRelHigNameText.bottom
                    anchors.topMargin: 0
                }
        }
        // 飞行速度显示
        Rectangle{
            id:airInfo_speed
            width:80
            height: 42
            color:"#161929"
            anchors.bottom: airPositionItem.top
            anchors.bottomMargin: 2

            anchors.left: airPositionItem.horizontalCenter
            opacity: 0.75
            visible: AirTextVisible
            radius: 4
            border.color:"#1677ff"


            Text {
                id:airSpeedNameText
                text: "空速"
                color: "white"
                font.bold: true
                font.pixelSize: 12
                font.family: "Microsoft YaHei"
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.horizontalCenterOffset: -airInfo_speed.width/4
                anchors.top: parent.top
                anchors.topMargin: 2

            }
            Text {
                id:gndSpeedNameText
                text: "地速"
                color: "white"
                font.bold: true
                font.pixelSize: 12
                font.family: "Microsoft YaHei"
                anchors.horizontalCenter:  parent.horizontalCenter
                anchors.horizontalCenterOffset: airInfo_speed.width/4
                anchors.top: parent.top
                anchors.topMargin: 2

            }


            /* gndspeed display */
            Rectangle{
                id:airInfo_AIRspeed
                width:airInfo_speed.width/2-1
                height: airInfo_speed.height/2
                color:"#1677ff"
                anchors.bottom: airInfo_speed.bottom
                anchors.bottomMargin: 0

                anchors.right: airInfo_speed.right
                anchors.rightMargin:0
                opacity: 0
                visible: AirTextVisible
                radius: 2

            }
            Text {
                id:airInfo_gndspeedtext
                text: GndSpeed.toFixed(1)
                color: "lightgreen"
                font.pixelSize: 14
                font.family: "Microsoft YaHei"
                font.bold: true
                anchors.centerIn: parent.Center
                anchors.horizontalCenter:  airInfo_AIRspeed.horizontalCenter
                anchors.verticalCenter:   airInfo_AIRspeed.verticalCenter
                anchors.verticalCenterOffset: -2
            }

            /* airspeed display */
            Rectangle{
                id:airInfo_Gndspeed
                width:airInfo_speed.width/2-1
                height: airInfo_speed.height/2
                color:"#1677ff"
                anchors.bottom: airInfo_speed.bottom
                anchors.bottomMargin: 0

                anchors.left: airInfo_speed.left
                anchors.leftMargin:0
                opacity: 0
                visible: AirTextVisible
                radius: 2
            }
            Text {
                id:airInfo_airspeedtext
                text: AirSpeed.toFixed(1)
                color: "yellow"
                font.pixelSize: 14
                font.family: "Microsoft YaHei"
                font.bold: true
                anchors.centerIn: airInfo_Gndspeed.Center
                anchors.horizontalCenter:  airInfo_Gndspeed.horizontalCenter
                anchors.verticalCenter:   airInfo_Gndspeed.verticalCenter
                anchors.verticalCenterOffset: -2
            }
        }

        // 飞行状态显示
        Rectangle{
            id:airMode_dis
            width:160
            height: 28
            color: "#1677ff"
            anchors.bottom: airInfo_height.top
            anchors.bottomMargin: 0
            anchors.horizontalCenter: airInfo_height.right
            opacity: 0.9
            visible: AirTextVisible
            Text {
                id:airState_name
                text:AirState+"-"+AirMode
                color: "white"
                font.pixelSize: 16
                font.family: "Microsoft YaHei"
                font.bold: true
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}


