#ifndef PLUGINMANAGERWIDGET_H
#define PLUGINMANAGERWIDGET_H

#include <QWidget>
#include <QObject>
#include "pluginmanagermodel.h"

#include <QTableView>
#include <QGridLayout>
#include <QHeaderView>
#include "widgetitle.h"
#include <QMouseEvent>

class PluginManagerWidget : public QWidget
{
    Q_OBJECT
public:
    PluginManagerWidget(QWidget *parent = nullptr);


private:
    void widgetInit();
    void connectSignalAndSlot();

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

private:
    QTableView *view = nullptr;

    QGridLayout *widgetLayout = nullptr;

    WidgetTitle *w_title = nullptr;

    PluginManagerModel *model = PluginManagerModelPtr::getModelPtr();



private slots:
    void tableItemClickedSlot(const QModelIndex &index);

};

#endif // PLUGINMANAGERWIDGET_H
