#include "hudviewitem_airinfo.h"

HUDViewItem_AirInfo::HUDViewItem_AirInfo(QRect rect)
{
    this->rect = rect;
}

void HUDViewItem_AirInfo::resize(QRect rect)
{
    this->rect = rect;
    this->update();
}

void HUDViewItem_AirInfo::valueChanged(float roll, float pitch, float heading, float currentRoll, float currentPitch, float currentAltitude, float currentSpeed, float targetRoll, float targetPitch, float targetAltitude, float targetSpeed)
{
    this->diffAltitude = currentAltitude -  this->currentAltitude;
    this->diffSpeed = currentSpeed - this->currentSpeed;

    this->roll = roll;
    this->pitch = pitch;
    this->heading = heading;
    this->currentRoll = currentRoll;
    this->currentPitch = currentPitch;
    this->currentAltitude = currentAltitude;
    this->currentSpeed = currentSpeed;
    this->targetRoll = targetRoll;
    this->targetPitch = targetPitch;
    this->targetAltitude = targetAltitude;
    this->targetSpeed = targetSpeed;

    this->update();
}

void HUDViewItem_AirInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font;
    font.setFamily(QStringLiteral("微软雅黑"));
    font.setPixelSize(12);
    painter->setFont(font);

    QBrush brush(QColor(255,0,0,120), Qt::SolidPattern);
    //使用画刷
    painter->setBrush(brush);
    QPolygonF graphicPoint;

    graphicPoint.clear();
    graphicPoint.append(QPointF(this->rect.x()        ,0));
    graphicPoint.append(QPointF(this->rect.x() + 45,0));
    graphicPoint.append(QPointF(this->rect.x() + 55,-10));
    graphicPoint.append(QPointF(this->rect.x() + 45,-20));
    graphicPoint.append(QPointF(this->rect.x()         ,-20));
    painter->drawPolygon(graphicPoint);

    painter->drawText(this->rect.x(),-20,45,20,Qt::AlignCenter,QString::number(this->currentAltitude,'f',2));


    brush = QBrush(QColor(0,255,0,120), Qt::SolidPattern);
    //使用画刷
    painter->setBrush(brush);
    graphicPoint.clear();
    graphicPoint.append(QPointF(this->rect.x()        ,0));
    graphicPoint.append(QPointF(this->rect.x() + 45,0));
    graphicPoint.append(QPointF(this->rect.x() + 55,10));
    graphicPoint.append(QPointF(this->rect.x() + 45,20));
    graphicPoint.append(QPointF(this->rect.x()        ,20));

    painter->drawPolygon(graphicPoint);

    painter->drawText(this->rect.x() ,0,45,20,Qt::AlignCenter,QString::number(this->targetAltitude));

    brush = QBrush(QColor(255,0,0,120), Qt::SolidPattern);
    //使用画刷
    painter->setBrush(brush);
    graphicPoint.clear();
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width()        ,0));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width() - 45,0));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width() - 55,-10));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width() - 45,-20));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width()        ,-20));

    painter->drawPolygon(graphicPoint);
    painter->drawText(this->rect.x() +  this->rect.width() - 45,-20,45,20,Qt::AlignCenter,QString::number(this->currentSpeed));

    brush = QBrush(QColor(0,255,0,120), Qt::SolidPattern);
    //使用画刷
    painter->setBrush(brush);
    graphicPoint.clear();
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width()        ,0));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width() - 45,0));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width() - 55,10));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width() - 45,20));
    graphicPoint.append(QPointF(this->rect.x() +  this->rect.width()        ,20));

    painter->drawPolygon(graphicPoint);
    painter->drawText(this->rect.x() +  this->rect.width() - 45,0,45,20,Qt::AlignCenter,QString::number(this->targetSpeed));


    painter->drawText( 70,50,60,15,Qt::AlignVCenter | Qt::AlignLeft,"CR:" + QString::number(this->currentRoll,'f',3));            //current roll
    painter->drawText(70,65,60,15, Qt::AlignVCenter | Qt::AlignLeft,"TR:" + QString::number(this->targetRoll,'f',3));             //target roll

    painter->drawText(70,80,60,15,Qt::AlignVCenter | Qt::AlignLeft,"CP:" + QString::number(this->currentPitch,'f',3));           //current  pitch
    painter->drawText(70,95,60,15,Qt::AlignVCenter | Qt::AlignLeft,"TP:" + QString::number(this->targetPitch,'f',3));           //target pitch



    if(this->diffAltitude > 0){
        brush = QBrush(QColor(0,255,0,120), Qt::SolidPattern);
        painter->setBrush(brush);
        graphicPoint.clear();
        graphicPoint.append(QPointF(-70       ,50));
        graphicPoint.append(QPointF( -65,55));
        graphicPoint.append(QPointF( -67,55));
        graphicPoint.append(QPointF( -67,65));
        graphicPoint.append(QPointF( -73  ,65));
        graphicPoint.append(QPointF( -73,55));
        graphicPoint.append(QPointF( -75  ,55));
        graphicPoint.append(QPointF( -70  ,50));
        painter->drawPolygon(graphicPoint);

    }else if(this->diffAltitude < 0){
        brush = QBrush(QColor(255,0,0,120), Qt::SolidPattern);
        painter->setBrush(brush);
        graphicPoint.clear();
        graphicPoint.append(QPointF(-70       ,65));
        graphicPoint.append(QPointF( -65,60));
        graphicPoint.append(QPointF( -67,60));
        graphicPoint.append(QPointF( -67,50));
        graphicPoint.append(QPointF( -73  ,50));
        graphicPoint.append(QPointF( -73,60));
        graphicPoint.append(QPointF( -75  ,60));
        graphicPoint.append(QPointF( -70  ,65));
        painter->drawPolygon(graphicPoint);
    }else{

    }
    painter->drawText( -150,50,75,15,Qt::AlignRight | Qt::AlignVCenter,QString::number(this->diffAltitude,'f',3));


    if(this->diffSpeed > 0){
        brush = QBrush(QColor(0,255,0,120), Qt::SolidPattern);
        painter->setBrush(brush);
        graphicPoint.clear();
        graphicPoint.append(QPointF(-70       ,70));
        graphicPoint.append(QPointF( -65,75));
        graphicPoint.append(QPointF( -67,75));
        graphicPoint.append(QPointF( -67,85));
        graphicPoint.append(QPointF( -73  ,85));
        graphicPoint.append(QPointF( -73,75));
        graphicPoint.append(QPointF( -75  ,75));
        graphicPoint.append(QPointF( -70  ,70));
        painter->drawPolygon(graphicPoint);

    }else if(this->diffSpeed < 0){
        brush = QBrush(QColor(255,0,0,120), Qt::SolidPattern);
        painter->setBrush(brush);
        graphicPoint.clear();
        graphicPoint.append(QPointF(-70 ,85));
        graphicPoint.append(QPointF( -65,80));
        graphicPoint.append(QPointF( -67,80));
        graphicPoint.append(QPointF( -67,70));
        graphicPoint.append(QPointF( -73  ,70));
        graphicPoint.append(QPointF( -73,80));
        graphicPoint.append(QPointF( -75  ,80));
        graphicPoint.append(QPointF( -70  ,85));
        painter->drawPolygon(graphicPoint);
    }else{

    }
    painter->drawText( -150,70,75,15,Qt::AlignRight | Qt::AlignVCenter,QString::number(this->diffSpeed,'f',3));


}

QRectF HUDViewItem_AirInfo::boundingRect() const
{
    return QRectF(this->rect.x(),this->rect.y(),this->rect.width(),this->rect.height());
}
