#ifndef SVGBORDERITEM_H
#define SVGBORDERITEM_H
#include <QGraphicsItem>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

class SvgBorderItem : public QGraphicsSvgItem
{
public:
    SvgBorderItem(QString path);



private:
    QString borderImagePath;


    QSvgRenderer *render = nullptr;

private:
    void initWidget();

};

#endif // SVGBORDERITEM_H
