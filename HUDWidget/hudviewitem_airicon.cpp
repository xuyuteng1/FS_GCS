#include "hudviewitem_airicon.h"


HUDViewItem_AirIcon::HUDViewItem_AirIcon(QRect rect)
{
    this->rect = rect;
}

void HUDViewItem_AirIcon::resize(QRect rect)
{
    this->rect = rect;
    this->update();
}

void HUDViewItem_AirIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen      scanePen;
    //设置颜色
    scanePen.setColor(airIconColor);
    //设置线的样式 实线、虚线
    scanePen.setStyle(Qt::SolidLine);
    //设置线端点样式
    scanePen.setCapStyle(Qt::RoundCap);

    scanePen.setWidth(3);
    painter->setPen(scanePen);

    painter->drawLine(QPoint(-75,0),QPoint(-30,0));
    painter->drawLine(QPoint( 75,0),QPoint( 30,0));

    painter->drawLine(QPoint( -25,10),QPoint( 0,-10));
    painter->drawLine(QPoint( 25,10),QPoint( 0,-10));
}

QRectF HUDViewItem_AirIcon::boundingRect() const
{
    return QRectF(this->rect.x(),this->rect.y(),this->rect.width(),this->rect.height());
}
