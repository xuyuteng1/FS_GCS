import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15

MapItemView {
    id:mapRoutesView
    add:Transition {}
    remove:Transition {}

//    model:AirRoutesModel


    delegate:MapItemGroup{
        MapItemView{
            add:Transition {}
            remove:Transition {}
            model:AirRoutesModel
            delegate: MapCircle {
                id: circle
                center: QtPositioning.coordinate(34.23,108.87)
                radius: 20000
                border.width: 3
                color:Qt.rgba(0,200,0,0.1)
                //鼠标按住后可移动
                MouseArea {
                    anchors.fill: parent
                    drag.target: parent
                }
            }
        }

        MapItemView{
            add:Transition {}
            remove:Transition {}

            model:AirRoutesModel
            delegate: MapPolygon
            {
                id:polygon
                border.width: 3
                color:Qt.rgba(0,200,0,0.1)
                path: [QtPositioning.coordinate(34.23,108.87)
                    ,QtPositioning.coordinate(34.23,108.97)
                    ,QtPositioning.coordinate(34.63,108.67)
                    ,QtPositioning.coordinate(34.33,108.87)]

                //鼠标按住后可移动
                MouseArea {
                    visible: false
                    anchors.fill: parent
                    drag.target: parent
                }
            }
        }

    }

}

