#include "svgbuttonitem.h"

SvgButtonItem::SvgButtonItem(QString svgPath)
{
    this->buttonSvgPath = svgPath;
    this->buttonPressedSvgPath = QString();
    this->buttonEnterSvgPath = QString();

    this->buttonRespondEnter      = false;
    this->buttonRespondPressed    = false;

    initWidget();
}

SvgButtonItem::SvgButtonItem(QString svgPath, QString svgPresssedPath)
{
    this->buttonSvgPath = svgPath;
    this->buttonPressedSvgPath = svgPresssedPath;
    this->buttonEnterSvgPath = QString();

    this->buttonRespondEnter      = false;
    this->buttonRespondPressed    = true;
    initWidget();
}

SvgButtonItem::SvgButtonItem(QString svgPath, QString svgPresssedPath, QString svgEnterPath)
{
    this->buttonSvgPath = svgPath;
    this->buttonPressedSvgPath = svgPresssedPath;
    this->buttonEnterSvgPath = svgEnterPath;

    this->buttonRespondEnter      = true;
    this->buttonRespondPressed    = true;

    initWidget();
}

void SvgButtonItem::buttonRespondPressedEvent(bool enable, QString respondSvgPath)
{
    this->buttonRespondPressed = enable;
    this->buttonPressedSvgPath = respondSvgPath;
}

void SvgButtonItem::buttonRespondEnterEvent(bool enable, QString svgEnterPath)
{
    this->buttonRespondEnter = enable;
    this->buttonEnterSvgPath = svgEnterPath;
}

void SvgButtonItem::initWidget()
{
    if(this->renderer == nullptr){
        this->renderer = new QSvgRenderer();
        this->renderer->load(this->buttonSvgPath);
        this->setSharedRenderer(this->renderer);
        this->setCacheMode(QGraphicsItem::NoCache);
        this->setFlags(this->flags() | QGraphicsItem::ItemClipsToShape);
    }

    if(this->maskItem == nullptr){
        this->maskItem = new QGraphicsPixmapItem(QPixmap(this->buttonSvgPath));
    }

    this->setAcceptDrops(true);
}

QPainterPath SvgButtonItem::shape() const
{
    if(this->maskItem != nullptr){
        return this->maskItem->shape();
    }
    return QPainterPath();
}

void SvgButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

    if(this->renderer != nullptr && this->buttonRespondPressed){
        this->renderer->load(this->buttonPressedSvgPath);
        this->setSharedRenderer(this->renderer);
        emit buttonPressedSignal();
    }
}

void SvgButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

    if(this->renderer != nullptr && this->buttonRespondPressed){
        this->renderer->load(this->buttonSvgPath);
        this->setSharedRenderer(this->renderer);
        emit buttonReleaseSignal();
    }
}

void SvgButtonItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

}

void SvgButtonItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

