#ifndef HUDVIEWITEM_AIRICON_H
#define HUDVIEWITEM_AIRICON_H

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class HUDViewItem_AirIcon: public QGraphicsItem
{
public:
    HUDViewItem_AirIcon(QRect rect);
    void resize(QRect rect);
private:
    QColor airIconColor = QColor(255,20,20);

    QRect rect;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;
};

#endif // HUDVIEWITEM_AIRICON_H
