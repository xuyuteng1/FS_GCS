#include "uchartview.h"
#include <qmath.h>
uChartView::uChartView(QWidget *parent, QString ChartName):
    QWidget(parent),
    _ChartName(ChartName)
{
    randomdata = new QRandomGenerator(100);
    widgetInit();
    rightButtonMenuInit();
    connectSignalAndSlot();

    this->setObjectName("stackedSubWidget_no_border");
}

void uChartView::updateData()
{
    // 30秒恢复一次
    if(QDateTime::currentDateTime().toMSecsSinceEpoch() -  last_resetGtaphics_ms > 300000){
        resetYGraphics();
    }
    if(_YAutoScale){
        rescaleYAxes();
    }

    if(_XAutoMove){
        rescaleXAxes(this->custonPlot->xAxis->range().size());
    }
    checkdatasize();
    this->custonPlot->replot();
}

void uChartView::widgetInit()
{
    if(this->custonPlot == nullptr){
        this->custonPlot = new QCustomPlot();

        //设置基本坐标轴（左侧Y轴和下方X轴）可拖动、可缩放、曲线可选、legend可选、设置伸缩比例，使所有图例可见
        this->custonPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom| QCP::iSelectAxes | QCP::iSelectLegend/* | QCP::iSelectPlottables*/);
        //设置legend只能选择图例
        this->custonPlot->legend->setSelectableParts(QCPLegend::spItems);
        this->custonPlot->xAxis2->setVisible(true);
        this->custonPlot->xAxis2->setTickLabels(false);
        this->custonPlot->yAxis2->setVisible(true);
        this->custonPlot->yAxis2->setTickLabels(false);

//        this->custonPlot->axisRect()->setBackground(QColor(22,25,41,255));//this->backGroundColor);            //设置背景颜色
//        this->custonPlot->axisRect()->setupFullAxesBox();
        this->custonPlot->setBackground(QColor(22,25,41,200));
        this->custonPlot->xAxis->setBasePen(QPen(QColor(255,255,255,120),1));//设置下轴
        this->custonPlot->yAxis->setBasePen(QPen(QColor(255,255,255,120),1));//设置左轴
        this->custonPlot->xAxis2->setBasePen(QPen(QColor(255,255,255,120),1));//设置上轴
        this->custonPlot->yAxis2->setBasePen(QPen(QColor(255,255,255,120),1));//设置右轴

        this->custonPlot->xAxis->setTickLabelColor(Qt::yellow);//设置右轴
        this->custonPlot->xAxis2->setTickLabelColor(Qt::yellow);//设置右轴
        this->custonPlot->yAxis->setTickLabelColor(Qt::yellow);//设置右轴
        this->custonPlot->yAxis2->setTickLabelColor(Qt::yellow);//设置右轴


        this->custonPlot->xAxis->setTickLabelFont(QFont("Microsoft YaHei", 9));//设置右轴
        this->custonPlot->xAxis2->setTickLabelFont(QFont("Microsoft YaHei", 9));//设置右轴
        this->custonPlot->yAxis->setTickLabelFont(QFont("Microsoft YaHei", 9));//设置右轴
        this->custonPlot->yAxis2->setTickLabelFont(QFont("Microsoft YaHei", 9));//设置右轴

        this->custonPlot->xAxis->setTickLabelRotation(0);                                   //设置X轴刻度显示旋转度数
        this->custonPlot->xAxis->ticker()->setTickCount(5);                             //设置X轴刻度个数

        this->custonPlot->yAxis->setTickLabelRotation(10);                               //设置y轴刻度显示旋转度数
        this->custonPlot->yAxis->ticker()->setTickCount(5);                             //设置y轴刻度个数

        this->custonPlot->legend->setBrush(QColor(255,255,255,120));              //设置示例背景色
        this->custonPlot->legend->setMargins(QMargins(2,0,2,0));                     //设置示例边距
        this->custonPlot->legend->setVisible(true);
        //修改左和底坐标轴,使之与右和上坐标轴始终匹配
        connect(this->custonPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->custonPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(this->custonPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->custonPlot->yAxis2, SLOT(setRange(QCPRange)));
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout  = new QGridLayout();
    }
    if(this->Box == nullptr){
        this->Box  = new QGroupBox(_ChartName);
        this->Box->setObjectName("widgetGroupBox_no_border");
    }
    if(this->boxlayout == nullptr){
        this->boxlayout  = new QGridLayout(this->Box);
    }

    this->boxlayout->addWidget(this->custonPlot,0,0,10,10);
    this->widgetLayout->addWidget(this->Box,0,0,10,10);
    this->widgetLayout->setSpacing(1);
    this->widgetLayout->setMargin(1);
    this->setLayout(this->widgetLayout);
}

void uChartView::connectSignalAndSlot()
{
    connect(this->custonPlot,&QCustomPlot::mouseWheel,this,&uChartView::mouseWheelSlot);
    connect(this->custonPlot,&QCustomPlot::mousePress,this,&uChartView::mousePressedSlot);
    connect(this->rightMenu,&QMenu::triggered,this,&uChartView::menuActionTargetSlot);

}

void uChartView::checkdatasize()
{
    QMap<int,ChartItemData>::iterator iter = this->graphMap.begin();
    while(iter != this->graphMap.end()){
        if(iter.value().graph != nullptr){
            if(iter.value().graph->data()->size() > MaxDataSize){
                iter.value().graph->data()->removeBefore(x_current-300);
            }
        }
        iter ++;
    }
}


void uChartView::rightButtonMenuInit()
{
    if(this->rightMenu == nullptr){
        this->rightMenu = new QMenu(this);
    }
    if(this->rescaleAxesAction == nullptr){
        this->rescaleAxesAction = new QAction(QStringLiteral("恢复默认"));
        this->rescaleAxesAction->setCheckable(true);
        this->rescaleAxesAction->setChecked(false);
    }

    if(this->rescaleyAxesAction == nullptr){
        this->rescaleyAxesAction = new QAction(QStringLiteral("y轴自动缩放"));
        this->rescaleyAxesAction->setCheckable(true);
        this->rescaleyAxesAction->setChecked(_YAutoScale);
    }
    if(this->xAxesRangleAction == nullptr){
        this->xAxesRangleAction = new QAction(QStringLiteral("X轴自动平移"));
        this->xAxesRangleAction->setCheckable(true);
        this->xAxesRangleAction->setChecked(_XAutoMove);
    }

    if(this->clearAction == nullptr){
        this->clearAction = new QAction(QStringLiteral("清除数据"));
        this->clearAction->setCheckable(true);
        this->clearAction->setChecked(false);
    }
    this->rightMenu->addAction(this->rescaleAxesAction);
    this->rightMenu->addAction(this->rescaleyAxesAction);
    this->rightMenu->addAction(this->xAxesRangleAction);
    this->rightMenu->addAction(this->clearAction);
}

/**===================================================================*
 * @brief      addGraphData 通过graph id 添加数据至对应图标
 * @param      int id, double x, double y
 * @retval     bool 添加结果
 **===================================================================*/
bool uChartView::addGraphData(int id, double x, double y)
{
    if(this->graphMap.find(id) != this->graphMap.end()){
        if(this->graphMap.find(id).value().graph != nullptr){
            this->graphMap.find(id).value().graph->addData(x,y);
            x_current = x;
            return true;
        }
    }
    return false;
}

/**===================================================================*
 * @brief      addNewGraph 初始化Map
 * @param      int id, double x, double y
 * @retval     bool 添加结果
 **===================================================================*/
bool uChartView::addNewGraph(int id,QString name,bool enable,bool smooth)
{
    if(this->graphMap.find(id) != this->graphMap.end()){
        return false;
    }

    ChartItemData item{};
    item.name = name;
    item.smooth = smooth;
    if(enable){
        this->custonPlot->addGraph();
        if(this->custonPlot->graph() != nullptr){
            item.graph = this->custonPlot->graph();
            item.graph->setPen(QPen(QColor(randomdata->bounded(125,255),randomdata->bounded(60,255),randomdata->bounded(125,255)),1.8f));
            item.graph->setName(item.name);
            item.graph->setVisible(true);
            item.graph->setLineStyle(QCPGraph::lsLine);
            item.graph->setSmooth(item.smooth);

            resetYGraphics();
        }
    }
    this->graphMap.insert(id,item);
    return true;
}

/**===================================================================*
 * @brief      增删响应槽函数
 * @param      int id, bool checked
 * @retval     None
 **===================================================================*/
void uChartView::buttonGroupToggledSlot(int id, bool checked)
{
    qDebug()<<"buttonGroup"<<id<<checked;
    if(this->graphMap.find(id) == this->graphMap.end()){
        return;
    }

    if(!checked){
        if(this->graphMap[id].graph){
            this->custonPlot->removeGraph(this->graphMap[id].graph);
            this->graphMap[id].graph = nullptr;
        }
    }
    else{
        this->custonPlot->addGraph();
        if(this->custonPlot->graph() != nullptr){
            this->graphMap[id].graph = this->custonPlot->graph();
            this->graphMap[id].graph->setPen(QPen(QColor(randomdata->bounded(125,255),randomdata->bounded(60,255),randomdata->bounded(125,255)),1.8f));

            this->graphMap[id].graph->setName(this->graphMap[id].name);
            this->graphMap[id].graph->setLineStyle(QCPGraph::lsLine);
            this->graphMap[id].graph->setSmooth(this->graphMap[id].smooth);
            resetYGraphics();
        }
    }
    this->custonPlot->replot();
}


void uChartView::mouseWheelSlot(QWheelEvent *event)
{
    Q_UNUSED(event)
    _YAutoScale = false;
    this->rescaleyAxesAction->setChecked(false);
    updateResetGraphics_time();
}

void uChartView::mousePressedSlot(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton){
        this->rightMenu->exec(QCursor::pos());
    }
}

void uChartView::clearGraphics()
{
    QMap<int,ChartItemData>::iterator iter = this->graphMap.begin();
    while(iter != this->graphMap.end()){
        if(iter.value().graph != nullptr){
            iter.value().graph->data()->clear();
        }
        iter ++;
    }
    this->custonPlot->replot();
}

void uChartView::rescaleXAxes(double size)
{
    if(x_current != 0){
        this->custonPlot->xAxis->setRange(x_current,x_current-size);
    }else{
        this->custonPlot->xAxis->setRange(25,25-size);
    }
}

void uChartView::rescaleYAxes()
{
    QMap<int,ChartItemData>::iterator iter = this->graphMap.begin();
    double lower = 0, upper = 0;
    bool ok = false;
    bool is_first = false;
    while(iter != this->graphMap.end()){
        if(iter.value().graph != nullptr){
            QCPRange rangetmp = iter.value().graph->getCurrentValueRange(ok);
            if(ok){
                if(!is_first){
                    upper = rangetmp.upper;
                    lower = rangetmp.lower;
                    is_first = true;
                }
                else{
                    if(rangetmp.upper > upper){
                        upper = rangetmp.upper;
                    }

                    if(rangetmp.lower < lower){
                        lower = rangetmp.lower;
                    }
                }
            }
        }
        iter ++;
    }
    this->custonPlot->replot();
    this->custonPlot->yAxis->setRangeLower(lower - qMax((double)0.001f,(double)qMin((double)0.5f,(double)(0.05f*qAbs(lower)))));
    this->custonPlot->yAxis->setRangeUpper(upper + qMax((double)0.001f,(double)qMin((double)0.5f,(double)(0.05f*qAbs(upper)))));
}

void uChartView::resetGraphics()
{
    rescaleXAxes(25);
    _YAutoScale = true;
    _XAutoMove = true;
    this->rescaleAxesAction->setChecked(false);
    this->rescaleyAxesAction->setChecked(true);
    this->xAxesRangleAction->setChecked(true);
    updateResetGraphics_time();
}

void uChartView::resetYGraphics()
{
    _YAutoScale = true;
    _XAutoMove = true;
    this->rescaleAxesAction->setChecked(false);
    this->rescaleyAxesAction->setChecked(true);
    this->xAxesRangleAction->setChecked(true);
    updateResetGraphics_time();
}

void uChartView::updateResetGraphics_time()
{
    last_resetGtaphics_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

void uChartView::menuActionTargetSlot(QAction *action)
{
    if(action == nullptr ){
        return;
    }
    // 恢复默认
    if(action == this->rescaleAxesAction){
        resetGraphics();
        this->rescaleAxesAction->setChecked(false);
    // Y自动缩放
    }else if(action == this->rescaleyAxesAction){
        if(action->isChecked()){
            _YAutoScale = true;
        }
        else{
            _YAutoScale = false;
        }
    }
    // X自动平移
    else if(action == this->xAxesRangleAction){
        if(action->isChecked()){
            _XAutoMove = true;
        }
        else{
            _XAutoMove = false;
        }
    }else if(action == this->clearAction){
        clearGraphics();
        this->clearAction->setChecked(false);
    }

    updateResetGraphics_time();
    this->custonPlot->replot();
}

void uChartView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control){
        this->custonPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
        updateResetGraphics_time();
    }
    return QWidget::keyPressEvent(event);
}

void uChartView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control){
        this->custonPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
        updateResetGraphics_time();
    }
    return QWidget::keyPressEvent(event);
}
