#include "svgborderitem.h"

SvgBorderItem::SvgBorderItem(QString path)
{
    this->borderImagePath = path;

    initWidget();


}

void SvgBorderItem::initWidget()
{
    if(this->render == nullptr){
        this->render = new QSvgRenderer(borderImagePath);
    }

    this->setSharedRenderer(this->render);

    this->setCacheMode(QGraphicsItem::NoCache);

    this->setZValue(1);
}
