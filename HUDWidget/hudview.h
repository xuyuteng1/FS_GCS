#ifndef HUDVIEW_H
#define HUDVIEW_H


#include <QGraphicsView>
#include "hudviewitem_scanepitch.h"
#include <QGraphicsLayout>

class HUDView : public QGraphicsView
{
public:
    HUDView();

private:
    void initHUDView();

private:
    QColor background_sky   = QColor(0  ,150 ,200 ,255);            //颜色-天空
    QColor background_land  = QColor(230,150 ,50  ,255);            //颜色-土地
    QColor background_scale = QColor(20 ,20  ,20  ,255);            //颜色-刻度背景色
    QColor background_heading = QColor(115 ,150 ,60 ,255);          //颜色-刻度背景色
    QColor background_roll = QColor(60 ,115 ,150 ,255);             //颜色-刻度背景色

    QColor backGround_label =  QColor(200 ,200 ,20  ,0);             //颜色-刻度背景色
    QColor color_airPlane =  QColor(255 ,20  ,20  ,255);
    QColor color_scale      = QColor(255,255 ,255 ,255);            //颜色-刻度
    QColor color_scaleHeading = QColor(0,0 ,0 ,255);

private:
    HUDViewItem_ScanePitch *sacnePitch = nullptr;


    QGraphicsLayout *viewLayout = nullptr;

};

#endif // HUDVIEW_H
