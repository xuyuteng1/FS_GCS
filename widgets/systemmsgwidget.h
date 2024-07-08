#ifndef SYSTEMMSGWIDGET_H
#define SYSTEMMSGWIDGET_H

#include <QListView>
#include <QAbstractListModel>

class SystemMsgModel : public QAbstractListModel{



};


class SystemMsgWidget : public QListView
{
public:
    SystemMsgWidget();
};

#endif // SYSTEMMSGWIDGET_H
