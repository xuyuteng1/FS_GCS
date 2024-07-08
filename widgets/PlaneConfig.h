#ifndef PLANECONFIG_H
#define PLANECONFIG_H

#include <QSplitter>
#include <QGridLayout>
#include <QListView>
#include <QStackedWidget>
#include <QAction>
#include <QMouseEvent>
#include <widgetitle.h>
#include <QStringListModel>
#include "P_Cfg_Takeoff.h"
#include "P_Cfg_Failsafe.h"
#include "P_Cfg_basic.h"
#include "P_Cfg_parachute.h"
class PlaneConfigWidget : public QWidget
{
    Q_OBJECT

public:
    class StringListModel : public QStringListModel{
    public:
        inline StringListModel(QObject *parent = nullptr) : QStringListModel(parent){};
        inline QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const{
            if(role == Qt::TextAlignmentRole){
                return Qt::AlignCenter;
            }else{
                return QStringListModel::data(index,role);
            }
        };
    };

public:
    PlaneConfigWidget(QWidget *parent = nullptr);
private:
    void initWidget();
    void connectSignalAndSlot();
private:
    QListView *listWidget = nullptr;
    QStackedWidget  *stackedWidget = nullptr;
    QSplitter *splitterWidget = nullptr;
    QGridLayout *splitterLayout = nullptr;
    QGridLayout *widgetLayout = nullptr;

    P_CFG_Takeoff*  P_widget_Takeoff = nullptr;
    P_CFG_Failsafe* P_widget_Failsafe = nullptr;
    P_CFG_Basic*    P_widget_Basic = nullptr;
    P_Cfg_Parachute*P_widget_Parachute = nullptr;
private:
    QMap<QString,QWidget *>widgetMap = {};
    StringListModel *listViewModel = nullptr;

protected:
public:
signals:
    void signalCloseEvent();

public slots:
    void addNewWidget(QString,QWidget*);

signals:


private slots:
    void listViewActionTargetSlot(const QModelIndex &index);
};

#endif // PlaneConfigWidget_H
