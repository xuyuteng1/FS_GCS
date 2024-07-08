#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QButtonGroup>
#include <QComboBox>
#include "qcustomplot.h"
#include <QColor>
#include <QMap>


class ChartView : public QWidget
{
public:
    struct ChartItemData{
        int                 id = 0;
        QString             name = {};
        bool                enable = false;
        QColor              grapColor = Qt::red;
        QCPGraph *          graph = nullptr;
    };
public:
    ChartView(QWidget *parent = nullptr);

    void updateData();

private:
    QCustomPlot *custonPlot = nullptr;
    QGridLayout *widgetLayout = nullptr;


private:
    void widgetInit();
    void connectSignalAndSlot();
    void initChooseBox();
    void rightButtonMenuInit();

private:
    QMap<QString,int> nameMap = {};
    QMap<int,ChartItemData> graphMap;
    QColor  backGroundColor = Qt::black;

private:
    QMenu *rightMenu = nullptr;
    QAction *xAxesRangleAction = nullptr;                                 //x轴范围显示使能 与rescaleAxesAction,rescalexAxesAction互斥
    QAction *rescaleyAxesAction = nullptr;                                 //y轴自动缩放 与rescaleAxesAction互斥
    QAction *rescaleAxesAction = nullptr;                                   //自动缩放
    QAction *clearAction = nullptr;                                         //清除线条

private:
    QGroupBox   *chooseBox = nullptr;
    QVBoxLayout *chooseBoxLayout = nullptr;
    QButtonGroup *buttonGroup = nullptr;

public slots:
    void addGraphData(QString name,double x,double y);
    bool addNewGraph(QString name,QColor color = Qt::red, bool enable = false);
    void clearGraphics();
    void rescaleXAxes(double size);
    void rescaleYAxes();
    void resetGraphics();
private:
    void mouseWheelSlot(QWheelEvent *event);
    void mousePressedSlot(QMouseEvent *event);
private slots:
    void menuActionTargetSlot(QAction *action);
    void buttonGroupToggledSlot(int id,bool checked);


protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    double x_current;

    bool _YAutoScale = true;
    bool _XAutoMove = true;

};

#endif // CHARTVIEW_H
