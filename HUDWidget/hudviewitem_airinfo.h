#ifndef HUDVIEWITEM_AIRINFO_H
#define HUDVIEWITEM_AIRINFO_H
#include <QGraphicsItem>
#include <QBrush>
#include <QPainter>
#include <QTextOption>

class HUDViewItem_AirInfo : public QGraphicsItem
{
public:
    HUDViewItem_AirInfo( QRect rect);
    void resize(QRect rect);

    void valueChanged(float roll,float pitch, float heading,float currentRoll,float currentPitch,float currentAltitude,float currentSpeed,float targetRoll ,float targetPitch,float targetAlititude,float targetSpeed);
private:
    float roll = 0;                                      //滚转角
    float pitch = 0;                                    //俯仰角
    float heading = 0;

    float currentRoll = 0;                          //当前滚转角
    float currentPitch = 0;                        //当前俯仰角
    float currentAltitude = 0;                   //当前高度
    float currentSpeed = 0;                   //当前速度

    float targetRoll = 0;                          //目标滚转角
    float targetPitch = 0;                        //目标俯仰角
    float targetAltitude = 0;                   //目标高度
    float targetSpeed = 0;                   //当前速度



    float diffAltitude = -1;                     //高度差
    float diffSpeed = 0;                       //速度差

    QRect rect;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;


};

#endif // HUDVIEWITEM_AIRINFO_H
