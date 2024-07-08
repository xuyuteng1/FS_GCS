#include "hudviewitem_backgroundimg.h"

HUDViewItem_BackGroundImg::HUDViewItem_BackGroundImg(QRect imgRect)
{
    this->rect = imgRect;
    QPixmap pix(":/img/png/hudBG.png");
    pix = pix .scaled(abs(rect.x() * 2),abs(rect.y() * 2),Qt::KeepAspectRatio, Qt::SmoothTransformation);

    this->setPixmap(pix);

//    this->moveBy(boundingRect().x(),boundingRect().y());
    this->setTransformOriginPoint(pix.width() / 2,pix.height() / 2);
    this->moveBy(-pix.width() / 2,-pix.height() / 2);

}

void HUDViewItem_BackGroundImg::resize(QRect imgRect)
{
    this->rect = imgRect;

    QPixmap pix(":/img/png/hudBG.png");
    pix = pix .scaled(abs(rect.x() * 2),abs(rect.y() * 2));

    this->setPixmap(pix);

//    this->moveBy(boundingRect().x(),boundingRect().y());
    this->setTransformOriginPoint(pix.width() / 2,pix.height() / 2);
    this->moveBy(-pix.width() / 2,-pix.height() / 2);
    this->update();

}
