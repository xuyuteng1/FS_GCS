#ifndef GENERAL_CONFIG_H
#define GENERAL_CONFIG_H

#include <QSplitter>
#include <QGridLayout>
#include <QListView>
#include <QStackedWidget>
#include <QAction>
#include <QMouseEvent>
#include <widgetitle.h>
#include <QStringListModel>
#include "G_cfg_boardorientation.h"
#include "G_cfg_acc_cali.h"
#include "G_cfg_communicationinterface.h"
#include "G_cfg_mag_cali.h"
#include "G_cfg_param_gnssposition.h"
#include "G_cfg_param_mainrc.h"
#include "G_cfg_prearm_cali.h"
#include "G_debug.h"
#include "G_Cfg_basic.h"

class WidgetGeneralConfig : public QWidget
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
    WidgetGeneralConfig(QWidget *parent = nullptr);
private:
    void initWidget();
    void connectSignalAndSlot();
private:
    QListView *listWidget = nullptr;
    QStackedWidget  *stackedWidget = nullptr;
    QSplitter *splitterWidget = nullptr;
    QGridLayout *splitterLayout = nullptr;
    QGridLayout *widgetLayout = nullptr;

    G_CFG_BoardOrientation*     G_widget_Orientation = nullptr;
    G_CFG_AccCali*              G_widget_AccCali = nullptr;
    G_CFG_SerialManager*        G_widget_SerialManager = nullptr;
    G_CFG_MagCali*              G_widget_MagCali = nullptr;
    G_CFG_AntennaPos*           G_widget_AntennaPos = nullptr;
    G_CFG_RC*                   G_widget_RC = nullptr;
    G_CFG_PreCali*              G_widget_PreCali = nullptr;
    G_CFG_Debug*                G_widget_Debug = nullptr;
    G_CFG_Basic*                G_widget_Basic = nullptr;
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

#endif // WidgetGeneralConfig_H
