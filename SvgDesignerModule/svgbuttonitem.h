#ifndef SVGBUTTONITEM_H
#define SVGBUTTONITEM_H

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QGraphicsPixmapItem>


#include <QPixmap>


class SvgButtonItem : public QGraphicsSvgItem
{
    Q_OBJECT
public:
    SvgButtonItem(QString svgPath);                                                                                                 //使用该构造函数构造后默认不响应任何事件
    SvgButtonItem(QString svgPath,QString svgPresssedPath);                                                       //使用该构造函数构造后默认响应鼠标点击事件及松开事件
    SvgButtonItem(QString svgPath,QString svgPresssedPath,QString svgEnterPath);                    //使用该构造函数构造后默认响应鼠标点击事件、松开事件、鼠标进入事件和退出事件

    void buttonRespondPressedEvent(bool enable, QString respondSvgPath = QString());            //使能鼠标点击和松开事件
    void buttonRespondEnterEvent(bool enable, QString svgEnterPath = QString());                    //使能鼠标进入和离开事件

public:



private:
    QSvgRenderer *renderer = nullptr;                                                   //svg图片加载器
    QGraphicsPixmapItem *maskItem = nullptr;                                    //按键有效区域遮罩层

    QString buttonSvgPath;                                                                      //按键默认图标
    QString buttonPressedSvgPath;                                                         //按键按下时图标
    QString buttonEnterSvgPath;                                                            //鼠标进入时按键图标

    bool        buttonRespondEnter      = false;                                        //按键响应鼠标进入事件标志
    bool        buttonRespondPressed    = false;                                        //按键响应鼠标按下事件标志

private:
    void initWidget();


protected:
    QPainterPath shape() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
public:
signals:
    void buttonPressedSignal();                                                     //鼠标按下事件
    void buttonReleaseSignal();                                                     //鼠标松开事件

    void mouseEnterSignal();                                                        //鼠标进入事件
    void mouseLeaveSignal();                                                        //鼠标离开事件


};

#endif // SVGBUTTONITEM_H
