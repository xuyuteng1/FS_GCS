#ifndef ROUTESWIDGET_H
#define ROUTESWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QGridLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableView>
#include <QListView>
#include <QTreeView>
#include <gis_airroutesmodel.h>
#include <QFile>
#include "gis_model.h"
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QCoreApplication>
#include <QMessageBox>
#include <QCloseEvent>
#include "widgetitle.h"
#include <QSplitter>
/*航线规划界面*/
class RoutesWidget : public QWidget
{
    Q_OBJECT
public:
    RoutesWidget(QWidget *parent = nullptr);


private:
    WidgetTitle*    w_title = nullptr;
    QListView *routesListView = nullptr;
    QTableView *routesPointView = nullptr;

    QGridLayout *WidgetLayout = nullptr;
    QGridLayout *mainLayout = nullptr;

    QPushButton *addRoutesButton = nullptr;                 //添加航线
    QPushButton *removeRoutesButton = nullptr;              //删除航线
    QPushButton *loadLoacationRouteButton = nullptr;        //加载航线
    QPushButton *saveAsButton = nullptr;                    //保存航线
    QPushButton *uploadRouteButton = nullptr;               //上传航线
    QPushButton *downloadRouteButton = nullptr;             //下载航线
    QGridLayout *routesButtonsLayout = nullptr;             //航线操作按钮布局

    QPushButton *apppendPointButton = nullptr;                  //添加航点-追加
    QPushButton *insertPointButton = nullptr;                   //添加航点-首行插入
    QPushButton *insertPointBelowIndexButton = nullptr;         //添加航点-行下插入
    QPushButton *insertPointAboveIndexButton = nullptr;         //添加航点-行上插入

    QPushButton *moveUpPointButton = nullptr;                   //航点上移
    QPushButton *moveDownPointButton = nullptr;                 //航点下移

    QPushButton *removePointButton = nullptr;                   //删除航点
    QPushButton *removeAllPointsButton = nullptr;               //删除所有航点
    QPushButton *signPointButton = nullptr;                     //标定航点
    QPushButton *appendPointForMouseButton = nullptr;           //鼠标点选
    QGridLayout *pointButtonsLayout = nullptr;                  //航点操作按钮布局

    QSplitter       *widgetSplitter = nullptr;

private:
    GIS_AirRouteItemModel *currentItemModel = nullptr;
private:
    GIS_AirRoutesModel *routesModel = nullptr;

    GIS_AirRoutesPointCMDDelegate *cmdDelegate = nullptr;                           //指令类型代理
    GIS_AirRoutesPointAlititudeTypeDelegate *alititudeTypeDelegate = nullptr;       //高度类型代理
    GIS_AirRoutesPointCoordinatesDelegate *lngDelegate = nullptr;
    GIS_AirRoutesPointCoordinatesDelegate *latDelegate = nullptr;

    GIS_AirRoutesPointParameter1Delegate  *parameter1Delegate = nullptr;
    GIS_AirRoutesPointParameter2Delegate  *parameter2Delegate = nullptr;
    GIS_AirRoutesPointParameter3Delegate  *parameter3Delegate = nullptr;
    GIS_AirRoutesPointParameter4Delegate  *parameter4Delegate = nullptr;

    GIS_Models *models = nullptr;
private:
    void widgetInit();

    void connectSignalAndSlot();
    void get_route_from_datapool(int link_id);
private slots:
    void indexClickedSlot(const QModelIndex &index);


    void addRoutesButtonClickedSlot();
    void removeRoutesButtonClickedSlot();
    void loadLoacationRouteButtonClickedSlot();
    void saveAsButtonClickedSlot();
    void uploadRouteButtonClickedSlot();
    void downloadRouteButtonClickedSlot();

    void apppendPointButtonPressedSlot();
    void insertPointButtonPressedSlot();
    void insertPointBelowIndexButtonPressedSlot();
    void insertPointAboveIndexButtonPressedSlot();
    void moveUpPointButtonPressedSlot();
    void moveDownPointButtonPressedSlot();
    void removePointButtonPressedSlot();
    void removeAllPointsButtonPressedSlot();
    void signPointButtonPressedSlot();
    void appendPointForMouseButtonPressedSlot();

    void handle_DMMM_event(int ev,int linkid = 0);

    void currentRoutesChangedSlot();

protected:
    void closeEvent(QCloseEvent *e);
    void changeEvent(QEvent *);

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
signals:
    void appendPointForMousePressedSignal(bool,int id);
    void routesWidgetCloseSignal();
    void signalCloseEvent();


};

#endif // ROUTESWIDGET_H
