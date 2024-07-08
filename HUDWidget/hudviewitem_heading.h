#ifndef HUDVIEWITEM_HEADING_H
#define HUDVIEWITEM_HEADING_H
#include <QGraphicsItem>
#include <QtMath>
#include <QPainter>
class HUDViewItem_Heading : public QGraphicsItem
{
public:
    HUDViewItem_Heading(QRect rect);
    void resize(QRect rect);

    void setHeading(int newHeading);

private:
    int heading = 10;
    QRect   rect;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;

};

#endif // HUDVIEWITEM_HEADING_H
