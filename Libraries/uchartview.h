#ifndef U_CHARTVIEW_H__
#define U_CHARTVIEW_H__

#include <QWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QComboBox>
#include "qcustomplot.h"
#include <QColor>
#include <QMap>


class uChartView : public QWidget
{
public:
    struct ChartItemData{
        QString             name = {};
        QCPGraph *          graph = nullptr;
        bool                smooth = false;
    };
public:
    uChartView(QWidget *parent = nullptr, QString ChartName = "");

    void updateData();

private:
    QCustomPlot *custonPlot = nullptr;
    QGridLayout *widgetLayout = nullptr;
    QGridLayout *boxlayout = nullptr;
    QGroupBox* Box = nullptr;
    const double MaxDataSize = 50000;

private:
    void widgetInit();
    void connectSignalAndSlot();
    void checkdatasize();
    void rightButtonMenuInit();
private:
    QMap<int,ChartItemData> graphMap;
    QColor  backGroundColor = Qt::black;

private:
    QMenu *rightMenu = nullptr;
    QAction *xAxesRangleAction = nullptr;                                 //x轴范围显示使能 与rescaleAxesAction,rescalexAxesAction互斥
    QAction *rescaleyAxesAction = nullptr;                                 //y轴自动缩放 与rescaleAxesAction互斥
    QAction *rescaleAxesAction = nullptr;                                   //自动缩放
    QAction *clearAction = nullptr;                                         //清除线条


public slots:
    bool addGraphData(int id,double x,double y);
    bool addNewGraph (int id,QString name,bool enable = false,bool smooth = false);
    void buttonGroupToggledSlot(int id,bool checked);
    void clearGraphics();

private:
    void mouseWheelSlot(QWheelEvent *event);
    void mousePressedSlot(QMouseEvent *event);
private slots:
    void menuActionTargetSlot(QAction *action);
    void rescaleXAxes(double size);
    void rescaleYAxes();
    void resetGraphics();
    void resetYGraphics();
    void updateResetGraphics_time();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    double x_current;

    bool _YAutoScale = true;
    bool _XAutoMove = true;
    QRandomGenerator* randomdata = nullptr;
    qint64 last_resetGtaphics_ms = 0;
    QString _ChartName = {};

};

#endif // uChartView_H
