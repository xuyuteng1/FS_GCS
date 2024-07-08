#ifndef HUDVIEWITEM_BACKGROUNDIMG_H
#define HUDVIEWITEM_BACKGROUNDIMG_H

#include <QGraphicsPixmapItem>

class HUDViewItem_BackGroundImg : public QGraphicsPixmapItem
{
public:
    HUDViewItem_BackGroundImg(QRect imgRect);
    void resize(QRect imgRect);
private:
    QRect rect;




};

#endif // HUDVIEWITEM_BACKGROUNDIMG_H
