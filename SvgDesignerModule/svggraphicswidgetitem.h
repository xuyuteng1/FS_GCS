#ifndef SVGGRAPHICSWIDGETITEM_H
#define SVGGRAPHICSWIDGETITEM_H

#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>

class SvgGraphicsWidgetItem : public QGraphicsProxyWidget
{
public:
    SvgGraphicsWidgetItem();
    SvgGraphicsWidgetItem(QString maskItemPath);

    void addCenterWidget(QWidget *);
protected:
    QPainterPath shape() const;
    void resizeEvent(QGraphicsSceneResizeEvent *event);


private:
    QGraphicsPixmapItem *maskItem = nullptr;


};

#endif // SVGGRAPHICSWIDGETITEM_H
