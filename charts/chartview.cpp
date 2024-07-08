#include "chartview.h"
#include <qmath.h>
ChartView::ChartView(QWidget *parent) : QWidget(parent)
{
    widgetInit();
    rightButtonMenuInit();
    connectSignalAndSlot();
    QFile file(QString(":/style/system_cfg.qss"));

    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
    this->setObjectName("QWidgetChart");
    //    this->chooseBox->setVisible(false);
}

void ChartView::updateData()
{
    if(_YAutoScale){
        rescaleYAxes();
    }

    if(_XAutoMove){
        rescaleXAxes(this->custonPlot->xAxis->range().size());
    }
    this->custonPlot->replot();
}

void ChartView::widgetInit()
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

    if(this->chooseBox == nullptr){
        this->initChooseBox();
    }


    if(this->widgetLayout == nullptr){
        this->widgetLayout  = new QGridLayout();
    }

    this->widgetLayout->setMargin(0);
    this->widgetLayout->addWidget(this->chooseBox,0,0,10,2);
    this->widgetLayout->addWidget(this->custonPlot,0,2,10,10);
    this->widgetLayout->setSpacing(0);
    this->setLayout(this->widgetLayout);
}

void ChartView::connectSignalAndSlot()
{
    connect(this->custonPlot,&QCustomPlot::mouseWheel,this,&ChartView::mouseWheelSlot);
    connect(this->custonPlot,&QCustomPlot::mousePress,this,&ChartView::mousePressedSlot);
    connect(this->rightMenu,&QMenu::triggered,this,&ChartView::menuActionTargetSlot);
    connect(this->buttonGroup,&QButtonGroup::idToggled,this,&ChartView::buttonGroupToggledSlot);
}

void ChartView::initChooseBox()
{
    if(this->chooseBox == nullptr){
        this->chooseBox = new QGroupBox;
        this->chooseBox->setObjectName(QStringLiteral("GroupChartAction"));
    }
    if(this->chooseBoxLayout == nullptr){
        this->chooseBoxLayout = new QVBoxLayout();
    }

    if(this->buttonGroup == nullptr){
        this->buttonGroup = new QButtonGroup();
        this->buttonGroup->setExclusive(false);                             //设置不互斥
    }

    this->chooseBoxLayout->setAlignment(Qt::AlignTop);
    this->chooseBox->setLayout(this->chooseBoxLayout);
}

void ChartView::rightButtonMenuInit()
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


void ChartView::addGraphData(QString name, double x, double y)
{
    if(this->nameMap.find(name) == this->nameMap.end()){
        return;
    }

    int id = this->nameMap.find(name).value();
    if(this->graphMap.find(id) != this->graphMap.end()){
        if(this->graphMap.find(id).value().graph != nullptr){
            this->graphMap.find(id).value().graph->addData(x,y);
            x_current = x;
        }
        else{
            return;
        }
    }



}

void ChartView::mouseWheelSlot(QWheelEvent *event)
{
    Q_UNUSED(event)
    _YAutoScale = false;
    this->rescaleyAxesAction->setChecked(false);
}

void ChartView::mousePressedSlot(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton){
        this->rightMenu->exec(QCursor::pos());
    }
}

bool ChartView::addNewGraph( QString name, QColor color, bool enable)
{
    if(this->nameMap.find(name) != this->nameMap.end()){
        return false;
    }
    ChartItemData item;
    item.id = this->nameMap.count();
    item.enable = enable;
    item.name = name;
    item.grapColor = color;
    if(enable){
        this->custonPlot->addGraph();
        if(this->custonPlot->graph() != nullptr){
            item.graph = this->custonPlot->graph();
            item.graph->setPen(QPen(item.grapColor,2));
            item.graph->setName(item.name);
            if(item.enable == false){
                item.graph->setVisible(false);
            }else{
                item.graph->setVisible(true);
            }
        }
    }

    this->nameMap.insert(name, item.id );
    this->graphMap.insert(item.id,item);

    if(this->chooseBoxLayout != nullptr){
        QCheckBox *checkBox = new QCheckBox(item.name);
        checkBox->setChecked(item.enable);
        checkBox->setObjectName(QString::fromUtf8("Checkbox_chart"));

        this->chooseBoxLayout->addWidget(checkBox);
        this->buttonGroup->addButton(checkBox,item.id);
    }
    return true;
}

void ChartView::clearGraphics()
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

void ChartView::rescaleXAxes(double size)
{
    if(x_current != 0){
        this->custonPlot->xAxis->setRange(x_current,x_current-size);
    }else{
        this->custonPlot->xAxis->setRange(8,8-size);
    }
}

void ChartView::rescaleYAxes()
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
//                if(iter.value().graph->data()->size() > 40*10){
//                    qDebug()<<"remove"<<iter.value().graph->data()->size();
//                    iter.value().graph->data()->removeBefore(x_current-20);

//                    qDebug()<<"x_current"<<x_current-20;
//                }
            }
        }
        iter ++;
    }

    this->custonPlot->replot();
    this->custonPlot->yAxis->setRangeLower(lower-1);
    this->custonPlot->yAxis->setRangeUpper(upper+1);
}

void ChartView::resetGraphics()
{
    rescaleXAxes(8);
    _YAutoScale = true;
    _XAutoMove = true;
    this->rescaleAxesAction->setChecked(false);
    this->rescaleyAxesAction->setChecked(true);
    this->xAxesRangleAction->setChecked(true);
}

void ChartView::menuActionTargetSlot(QAction *action)
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
    this->custonPlot->replot();
}

void ChartView::buttonGroupToggledSlot(int id, bool checked)
{
    if(this->graphMap.find(id) == this->graphMap.end()){
        return;
    }

    if(!checked){
        this->custonPlot->removeGraph(this->graphMap[id].graph);
        this->graphMap[id].graph = nullptr;
    }
    else{
        this->custonPlot->addGraph();
        if(this->custonPlot->graph() != nullptr){
            this->graphMap[id].graph = this->custonPlot->graph();
            this->graphMap[id].graph->setPen(QPen(this->graphMap[id].grapColor,2));
            this->graphMap[id].graph->setName(this->graphMap[id].name);
            this->graphMap[id].graph->setAntialiased(true);
            resetGraphics();
        }
    }
    this->graphMap[id].enable = checked;
    this->custonPlot->replot();

}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control){
        this->custonPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    }
    return QWidget::keyPressEvent(event);
}

void ChartView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control){
        this->custonPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
    }
    return QWidget::keyPressEvent(event);
}
