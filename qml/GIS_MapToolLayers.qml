import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import QtGraphicalEffects 1.15



MapItemView {
    id:mapRoutesView
    add:Transition {}
    remove:Transition {}
    visible: true
    model:AirMapToolModel




    delegate:MapItemGroup{
        MapPolyline{
            id:mapTool_ranging
            visible: true;
            line.width: 3
            line.color:  "yellow"
            path:ToolGeoCoorList

            function getDistanceCount(){
                var distance_count=0;
                for(var i=1;i<pathLength();i++){
                    distance_count+=mapTool_ranging.coordinateAt(i).distanceTo(mapTool_ranging.coordinateAt(i-1));
                }
                return Math.round(distance_count);
            }
        }



        MapItemView{
            add:Transition {}
            remove:Transition {}

            model:AirMapToolModel
            delegate: MapQuickItem{
                id:airRangingPointItem
                zoomLevel: 0
                coordinate:ToolGeoCoorPoint
                anchorPoint: Qt.point(airRangingPointItem.width/2,airRangingPointItem.height - 5)

                sourceItem:Rectangle{
                    id:airRangingPoint
                    width:14
                    height:14
                    radius: 7
                    color:"red"

                    Text {
                        id:pointID
                        text: "ID:" + (index + 1)
                        anchors.left: airRangingPoint.left
                        anchors.top:airRangingPoint.bottom
                        color: "red"
                        font.pixelSize: 15
                    }
                    Text {
                        id:pointLng
                        text: "纬度:" + airRangingPointItem.coordinate.latitude.toFixed(7)
                        anchors.left: pointID.left
                        anchors.top:pointID.bottom
                        color: "blue"
                        font.pixelSize: 15
                    }
                    Text {
                        id:pointLat
                        text: "经度:" + airRangingPointItem.coordinate.longitude.toFixed(7)
                        anchors.left: pointLng.left
                        anchors.top:pointLng.bottom
                        color: "blue"
                        font.pixelSize: 15
                    }
                    Text {
                        id: item_text
                        x: 5
                        color: "blue"
                        font.pixelSize: 17
                        anchors.left: pointLat.left
                        anchors.top:pointLat.bottom
                        visible:true
                        anchors.verticalCenter: parent.verticalCenter
                        text:index<=0
                             ? "起点"
                             : (index === AirMapToolModel.count-1)
                               ? ("总长 "+mapTool_ranging.getDistanceCount()/1000+" km")
                               :("距离上一点： "+Math.round(airRangingPointItem.coordinate.distanceTo(mapTool_ranging.coordinateAt(index-1)))/1000+" km")
                    }
                }

            }

        }

    }


}
