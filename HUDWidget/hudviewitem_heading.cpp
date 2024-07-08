#include "hudviewitem_heading.h"

HUDViewItem_Heading::HUDViewItem_Heading(QRect rect)
{
    this->rect = rect;
}

void HUDViewItem_Heading::resize(QRect rect)
{
    this->rect = rect;
    this->update();
}

void HUDViewItem_Heading::setHeading(int newHeading)
{
    if(this->heading != newHeading){
        heading = newHeading;
        this->update();
    }
}

void HUDViewItem_Heading::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen      scanePen;
    //设置颜色
    scanePen.setColor(Qt::black);
    //设置线的样式 实线、虚线
    scanePen.setStyle(Qt::SolidLine);
    //设置线端点样式
    scanePen.setCapStyle(Qt::RoundCap);

    scanePen.setWidth(3);
    painter->setPen(scanePen);

    painter->drawArc(this->boundingRect(),30 * 16,120 * 16);

    scanePen.setColor(Qt::white);
    painter->setPen(scanePen);
    QFont font;
    font.setFamily(QStringLiteral("微软雅黑"));
    font.setPixelSize(12);
    painter->setFont(font);
    painter->drawText(-20,this->rect.y() + this->rect.height() * 0.08f + 5 ,40,15,Qt::AlignCenter,QString::number(this->heading));



    QPainterPath path;
    path.moveTo (0, this->rect.y() + this->rect.height() * 0.08f);
    path.lineTo (-5,   this->rect.y() + this->rect.height() * 0.08f + 5 );

    path.lineTo (5,    this->rect.y() + this->rect.height() * 0.08f + 5);

    painter->setPen (Qt :: NoPen);
    painter->fillPath (path, QBrush (QColor ("black")));


    scanePen.setColor(Qt::black);
    scanePen.setWidth(1);
    painter->setPen(scanePen);
    for(int i = 0; i < 360; i++){
        if(((i + this->heading)  % 360 < 120)   || ( (i + this->heading) % 360 > 240)){
                continue;
        }
        if(i % 10 == 0){
            painter->drawLine(QPoint(qSin((i + heading) % 360 * M_PI / 180)  * this->rect.width() / 2 ,qCos((i  + heading) % 360* M_PI / 180) * this->rect.width() / 2),QPoint(qSin((i + heading) % 360 * M_PI / 180)  * this->rect.width() / 2 * 0.95f,qCos((i  + heading) % 360* M_PI / 180) * this->rect.width() / 2* 0.95f));
        }


    }
    scanePen.setColor(Qt::white);
    painter->setPen(scanePen);

    for(int i = 0; i < 360; i++){
        if(((i + this->heading)  % 360 < 120)   || ( (i + this->heading) % 360 > 240)){
                continue;
        }

        if(i % 20 == 0){
            painter->drawText(qSin((i + heading) % 360 * M_PI / 180)  * this->rect.width() / 2 * 0.87f - 5,qCos((i  + heading) % 360* M_PI / 180) * this->rect.width() / 2* 0.87f,QString::number((360 - i + 180) % 360));
        }
    }
}

QRectF HUDViewItem_Heading::boundingRect() const
{
    return QRectF(this->rect.x(),this->rect.y(),this->rect.width(),this->rect.height());
}
