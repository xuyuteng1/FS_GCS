#ifndef HUDWIDGET_H
#define HUDWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "hudviewitem_scanepitch.h"
#include "hudviewitem_background.h"
#include "hudviewitem_heading.h"
#include "hudviewitem_airicon.h"
#include "hudviewitem_airinfo.h"
#include "hudviewitem_backgroundimg.h"
#include "hudview.h"
#include <QResizeEvent>
#include <QDebug>

class HUDWidget : public QWidget
{
    Q_OBJECT
public:
    HUDWidget();

private:
    QGraphicsScene *hudScane = nullptr;
    HUDView  *hudView = nullptr;
    QGridLayout    *widgetLayout = nullptr;

    HUDViewItem_ScanePitch *scanePitch = nullptr;
    HUDViewItem_Heading      *scaneHeading = nullptr;
    HUDViewItem_BackGround *scaneBakGround = nullptr;
    HUDViewItem_BackGroundImg *scaneBakGroundImg = nullptr;
    HUDViewItem_AirIcon        *airIcon = nullptr;
    HUDViewItem_AirInfo        *airInfo = nullptr;
private:
    QColor background_sky   = QColor(0  ,150 ,200 ,255);            //颜色-天空


private:
    void widgetInit();

    void resizeEvent(QResizeEvent *event);
public slots:
    void updateHUDData(float altitude,float targetAltitude,float roll,float targetRoll,float heading,float targetHeading,float pitch,float targetPitch,float speed,float targetSpeed);
};

#endif // HUDWIDGET_H
