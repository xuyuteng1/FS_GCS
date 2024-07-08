#ifndef CONSTRUCATIONWIDGET_H
#define CONSTRUCATIONWIDGET_H

#include <QComboBox>
#include <QAction>
#include <QMouseEvent>
#include <QToolButton>
#include <QButtonGroup>
#include <QIcon>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QObject>
#include <QAbstractButton>
#include "FlyLink.h"

#include "widgetitle.h"
class ToolButton : public QToolButton{
public:
    ToolButton(QString name,QString path);
};



class ConstrucationListView:public QWidget{
    Q_OBJECT
public:

public:
    ConstrucationListView(QWidget *parent = nullptr);

public:
    QMap<uint8_t,QString> getConstrucationName();
    QMap<uint8_t,QString> getConstrucationIconPath();
private:
    QMap<uint8_t,ToolButton *> actionMap;
    QButtonGroup *buttonGroup = nullptr;
    QGridLayout *widgetLayout = nullptr;
    QGridLayout *mainLayout = nullptr;
    WidgetTitle *w_title = nullptr;

private:
    void widgetInit();
    void connectSignalAndSlot();

private slots:
    void buttonGroupChangedSlot(int );

protected:
    /**========= 窗口支持鼠标拖动 =========**/
    QPoint dragPosition;
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
           dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    };

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    };
public:
signals:
    void construcationChangedSignal(int);

};


#endif // CONSTRUCATIONWIDGET_H
