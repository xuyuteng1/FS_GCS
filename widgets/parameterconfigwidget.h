#ifndef PARAMETERCONFIGWIDGET_H
#define PARAMETERCONFIGWIDGET_H

#include <QSplitter>
#include <QGridLayout>
#include <QListView>
#include <QStackedWidget>
#include <QAction>
#include <QMouseEvent>
#include <widgetitle.h>
#include <QStringListModel>
#include "cfg_param_initcfg.h"
#include "cfg_param_failsafe.h"
#include "cfg_param_control.h"
#include "cfg_param_attcontrol.h"
#include "cfg_param_poscontrol.h"
class ParameterConfigWidget : public QWidget
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
    ParameterConfigWidget(QWidget *parent = nullptr);
private:
    void initWidget();
    void connectSignalAndSlot();
private:
    QListView *listWidget = nullptr;
    QStackedWidget  *stackedWidget = nullptr;
    QSplitter *splitterWidget = nullptr;
    QGridLayout *splitterLayout = nullptr;
    QGridLayout *widgetLayout = nullptr;
    WidgetTitle *w_title = nullptr;

    CFG_InitCfg*                CFGwidget_InitCfg = nullptr;
    CFG_ParamFailsafe*          CFGwidget_ParamFailsafe = nullptr;
    CFG_ParamControl*           CFGwidget_ParamControl = nullptr;
    CFG_ParamRollControl*       CFGwidget_RollControl = nullptr;
    CFG_ParamPitchControl*      CFGwidget_PitchControl = nullptr;
    CFG_ParamYawControl*      CFGwidget_YawControl = nullptr;
    CFG_ParamPosZControl*     CFGwidget_PosControl = nullptr;
    CFG_ParamPosXYControl *CFGwidget_PosXYControl = nullptr;
private:
    QMap<QString,QWidget *>widgetMap = {};
    StringListModel *listViewModel = nullptr;

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
    void signalCloseEvent();

public slots:
    void addNewWidget(QString,QWidget*);

signals:


private slots:
    void listViewActionTargetSlot(const QModelIndex &index);
};

#endif // PARAMETERCONFIGWIDGET_H
