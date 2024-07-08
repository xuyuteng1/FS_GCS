#ifndef HUDVIEWITEM_SCANEPITCH_H
#define HUDVIEWITEM_SCANEPITCH_H
#include <QGraphicsItem>
#include <QPainter>
class HUDViewItem_ScanePitch : public QGraphicsItem
{
public:
    HUDViewItem_ScanePitch(QRect rect);

    void resize(QRect rect);
    void setPitch(int newPitch);

private:
    int         pitch = 0;
    float       pitchScale = 0.5f;                 //俯仰角度对应图形高度比例 1 ：10

    QRect   rect;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;


};

#endif // HUDVIEWITEM_SCANEPITCH_H
