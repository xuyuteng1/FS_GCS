#ifndef HUDVIEWITEM_BACKGROUND_H
#define HUDVIEWITEM_BACKGROUND_H

#include <QGraphicsItem>
#include <QtMath>
#include <QPainter>
#include <QList>
#include <QPointF>
#include <qDebug>
class HUDViewItem_BackGround : public QGraphicsItem
{
public:
    HUDViewItem_BackGround(QRect rect);
    void resize(QRect rect);

    void valueChanged(float roll,float pitch);

private:
    float           pitchScale = 0.5f;                 //俯仰角度对应图形高度比例 1 ：10
    QColor       background_land  = QColor(230,150 ,50  ,255);            //颜色-土地

    float roll = 0;                 //滚转角
    float pitch = 0;               //俯仰角

    QRect   rect;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;


};

#endif // HUDVIEWITEM_BACKGROUND_H
