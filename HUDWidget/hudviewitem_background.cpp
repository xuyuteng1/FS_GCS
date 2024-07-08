#include "hudviewitem_background.h"
#include "qvector3d.h"


HUDViewItem_BackGround::HUDViewItem_BackGround(QRect rect)
{
    this->rect = rect;
}

void HUDViewItem_BackGround::resize(QRect rect)
{
    this->rect = rect;
}

void HUDViewItem_BackGround::valueChanged(float roll, float pitch)
{
    if(this->roll  != roll  || this->pitch != pitch){
        this->roll = roll;
        this->pitch = pitch;
        this->update();
    }
}

void HUDViewItem_BackGround::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//创建画刷
    QBrush brush(this->background_land, Qt::SolidPattern);
    //使用画刷
    painter->setBrush(brush);

    int roll = static_cast<int>(360 - this->roll);
    QPolygonF graphicPoint;

    float offset_Y = -this->pitch / this->pitchScale;                       //根据俯仰值计算出图形偏移尺寸

    float offset_y_top = abs(this->rect.y()) - offset_Y;               //偏移点距离顶部距离
    float offset_y_bottom = abs(this->rect.y()) + offset_Y;       //偏移点距离底部距离

    QPoint offsetCenterPoint(0,-offset_Y);

    if(roll % 360  == 0){
        graphicPoint.clear();
        graphicPoint.append(QPointF(-this->rect.x(), -offset_Y));
        graphicPoint.append(QPointF(this->rect.x(),-offset_Y));
        graphicPoint.append(QPointF(this->rect.x(),-this->rect.y()));
        graphicPoint.append(QPointF(-this->rect.x(),-this->rect.y()));
    }else if(roll % 360 == 180){
        graphicPoint.clear();
        graphicPoint.append(QPointF(this->rect.x(), -offset_Y));
        graphicPoint.append(QPointF(-this->rect.x(),-offset_Y));
        graphicPoint.append(QPointF(-this->rect.x(),this->rect.y()));
        graphicPoint.append(QPointF(this->rect.x(),this->rect.y()));
    }else{

        float top_x = qTan((abs(roll % 360) <  180 ? (90 - abs(roll % 360) ) : (90 + abs(roll % 360) )) * M_PI / 180) * ((((360 + roll) % 360) > 180) ? offset_y_top : offset_y_bottom);                       //计算顶部x值
        float bottom_x = qTan( (abs(roll % 360) < 180 ?(90 + abs(roll % 360)) : (90 - abs(roll % 360)) ) * M_PI / 180) * ((((360 + roll) % 360) > 180) ? offset_y_bottom : offset_y_top) ;           //计算底部x值

        top_x = top_x > 0 ? (top_x > abs(this->rect.x()) ? top_x : abs(this->rect.x())) : (top_x < this->rect.x() ? top_x : this->rect.x());
        float top_y = qTan(( roll) * M_PI / 180) * top_x;


        bottom_x = bottom_x > 0 ? (bottom_x > abs(this->rect.x()) ? bottom_x : abs(this->rect.x())) : (bottom_x < this->rect.x() ? bottom_x : this->rect.x());
        float bottom_y = qTan(( roll) * M_PI / 180) * bottom_x ;

//        qDebug()<<"offset_y_top = "<<offset_y_top<<"    offset_y_bottom"<<offset_y_bottom<<"    top X = "<<top_x<<"    top_y = "<<top_y<<"        bottom_x="<<bottom_x<<"    bottom_y="<<bottom_y;
        graphicPoint.clear();

        graphicPoint.append(QPointF(top_x + offsetCenterPoint.x(),top_y + offsetCenterPoint.y()));
        graphicPoint.append(QPointF(bottom_x + offsetCenterPoint.x(),bottom_y + offsetCenterPoint.y()));
        graphicPoint.append(QPointF(top_y > bottom_y ? (top_x < bottom_x ? (this->rect.x()) : (this->rect.x())) :(top_x > bottom_x ? (-this->rect.x()) : (-this->rect.x())) ,
                                                        top_y > bottom_y ?(top_x < bottom_x ? (this->rect.y()) : (-this->rect.y())) :  (top_x > bottom_x ? (-this->rect.y()) : (this->rect.y())) ));

    }
    painter->drawPolygon(graphicPoint);

}

QRectF HUDViewItem_BackGround::boundingRect() const
{
    return QRectF(this->rect.x(),this->rect.y(),this->rect.width(),this->rect.height());
}
