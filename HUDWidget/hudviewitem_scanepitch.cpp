#include "hudviewitem_scanepitch.h"
#include <QDebug>
HUDViewItem_ScanePitch::HUDViewItem_ScanePitch(QRect rect)
{

    this->rect = rect;
}

void HUDViewItem_ScanePitch::resize(QRect rect)
{
    this->rect = rect;

    this->update();
}

void HUDViewItem_ScanePitch::setPitch(int newPitch)
{
    if(pitch != newPitch){
        pitch = newPitch;
//        this->update();
    }
}

void HUDViewItem_ScanePitch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen      scanePen;
    scanePen.setWidth(3);
    //设置颜色
    scanePen.setColor(Qt::white);
    //设置线的样式 实线、虚线
    scanePen.setStyle(Qt::SolidLine);
    //设置线端点样式
    scanePen.setCapStyle(Qt::RoundCap);
    painter->setPen(scanePen);
    painter->drawLine(0,this->rect.y(),0 ,-this->rect.y());

    scanePen.setWidth(2);
    painter->setPen(scanePen);

    int pitchVal = this->pitch / this->pitchScale;

    //绘制刻度
    for(int i = -9; i <= 9; i++){

//        if(abs((this->pitch + i * 10) / this->pitchScale) > abs(this->rect.y())){
//            continue;
//        }

        if((this->pitch + i * 10) / this->pitchScale > -this->rect.y() || (this->pitch + i * 10) / this->pitchScale < this->rect.y() ){
            continue;
        }


        if(i % 2 == 0){
            painter->drawLine( - 20,  (this->pitch + i * 10) / this->pitchScale,20 ,  (this->pitch + i * 10) / this->pitchScale);
        }else{
            painter->drawLine( - 10, (this->pitch + i * 10) / this->pitchScale, 10 ,  (this->pitch + i * 10) / this->pitchScale);
        }
    }
    //绘制刻度值

    scanePen.setColor(Qt::green);
    QFont font;
    font.setFamily(QStringLiteral("微软雅黑"));
    font.setPixelSize(12);
    painter->setFont(font);
    painter->setPen(scanePen);
     for(int i = -9; i <= 9; i++){
         if(abs((this->pitch + i * 10) / this->pitchScale) > abs(this->rect.y())){
             continue;
         }

         if(i % 2 == 0){
             painter->drawText( 25,((this->pitch + i * 10) / this->pitchScale) - 5,30,10,Qt::AlignVCenter | Qt::AlignLeft,QString::number(0 - i * 10));
         }
     }
}

QRectF HUDViewItem_ScanePitch::boundingRect() const
{
    return QRectF(this->rect.x(),this->rect.y(),this->rect.width(),this->rect.height());
}
