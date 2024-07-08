#include "svggraphicswidgetitem.h"

SvgGraphicsWidgetItem::SvgGraphicsWidgetItem()
{

}

SvgGraphicsWidgetItem::SvgGraphicsWidgetItem(QString maskItemPath)
{
    this->maskItem = new QGraphicsPixmapItem(QPixmap(maskItemPath));
}

void SvgGraphicsWidgetItem::addCenterWidget(QWidget *wid)
{
    this->setWidget(wid);
}

QPainterPath SvgGraphicsWidgetItem::shape() const
{
    if(this->maskItem != nullptr){
        return this->maskItem->shape();
    }
    return QPainterPath();
}

void SvgGraphicsWidgetItem::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    this->shape();
    QGraphicsProxyWidget::resizeEvent(event);
}
