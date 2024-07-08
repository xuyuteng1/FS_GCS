#ifndef MOTORTESTWIDGET_H
#define MOTORTESTWIDGET_H

#include <QGraphicsScale>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>

class MotorItem : public QGraphicsItem{

};


class MotorTestWidget : public QGraphicsView
{
public:
    MotorTestWidget();
};

#endif // MOTORTESTWIDGET_H
