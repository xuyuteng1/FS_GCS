#include "parameterconfigwidget.h"

ParameterConfigWidget::ParameterConfigWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
    connectSignalAndSlot();
    this->setAttribute(Qt::WA_StyledBackground,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);


    if(CFGwidget_ParamFailsafe == nullptr){
        CFGwidget_ParamFailsafe = new CFG_ParamFailsafe(this);
        addNewWidget(QStringLiteral("故障保护"),CFGwidget_ParamFailsafe);
    }
    if(CFGwidget_ParamControl == nullptr){
        CFGwidget_ParamControl = new CFG_ParamControl(this);
        addNewWidget(QStringLiteral("基础控制"),CFGwidget_ParamControl);
    }
    if(CFGwidget_InitCfg == nullptr){
        CFGwidget_InitCfg = new CFG_InitCfg(this);
        addNewWidget(QStringLiteral("初始配置"),CFGwidget_InitCfg);
    }
    if(this->CFGwidget_RollControl == nullptr){
        this->CFGwidget_RollControl = new CFG_ParamRollControl(this);
        addNewWidget(QStringLiteral("滚转控制"),CFGwidget_RollControl);
    }
    if(this->CFGwidget_PitchControl == nullptr){
        this->CFGwidget_PitchControl = new CFG_ParamPitchControl(this);
        addNewWidget(QStringLiteral("俯仰控制"),CFGwidget_PitchControl);
    }
    if(this->CFGwidget_YawControl == nullptr){
        this->CFGwidget_YawControl = new CFG_ParamYawControl(this);
        addNewWidget(QStringLiteral("航向控制"),CFGwidget_YawControl);
    }

    if(CFGwidget_PosControl == nullptr){
        CFGwidget_PosControl = new CFG_ParamPosZControl(this);
        addNewWidget(QStringLiteral("高度位置控制"),CFGwidget_PosControl);
    }

    if(CFGwidget_PosXYControl == nullptr){
        CFGwidget_PosXYControl = new CFG_ParamPosXYControl(this);
        addNewWidget(QStringLiteral("水平位置控制"),CFGwidget_PosXYControl);
    }






    this->setFixedSize(1000,700);
}

void ParameterConfigWidget::initWidget()
{
    if(this->listViewModel == nullptr){
        this->listViewModel = new StringListModel();
    }

    if(this->splitterWidget == nullptr){
        this->splitterWidget = new QSplitter(this);
        this->splitterWidget->setOrientation(Qt::Horizontal);
        this->splitterWidget->setSizes(QList<int>()<<50<<200);
        this->splitterWidget->setObjectName("widgetSplitter");
    }

    if(this->listWidget == nullptr){
        this->listWidget = new QListView(this->splitterWidget);
        this->listWidget->setObjectName("widgetListView");
        this->listWidget->setModel(this->listViewModel);
        this->listWidget->setMaximumWidth(200);
        this->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->splitterWidget->addWidget(this->listWidget);
    }

    if(this->stackedWidget == nullptr){
        this->stackedWidget = new QStackedWidget(this->splitterWidget);
        this->stackedWidget->setObjectName("widgetStackedWidget_no_border");
        this->splitterWidget->addWidget(this->stackedWidget);
    }

    if(this->w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("飞行配置"));
        w_title->setMaximumHeight(40);
        this->w_title->setObjectName("widgetitle");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    this->setObjectName("systemWidget");
    this->widgetLayout->addWidget(this->w_title,0,0,1,10);
    this->widgetLayout->addWidget(this->splitterWidget,1,0,5,10);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);
    this->setLayout(this->widgetLayout);


}

void ParameterConfigWidget::connectSignalAndSlot()
{
    connect(this->listWidget,&QListView::doubleClicked,this,&ParameterConfigWidget::listViewActionTargetSlot);
    connect(this->listWidget,&QListView::clicked,this,&ParameterConfigWidget::listViewActionTargetSlot);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
}

void ParameterConfigWidget::addNewWidget(QString name, QWidget *widget)
{
    if(this->widgetMap.find(name) == this->widgetMap.end()){
        this->stackedWidget->addWidget(widget);
        this->listViewModel->insertRow(this->listViewModel->rowCount());
        QModelIndex index = this->listViewModel->index(this->listViewModel->rowCount() - 1,0);
        this->listViewModel->setData(index,name);
        this->widgetMap.insert(name,widget);
    }else{
        QWidget *w = this->widgetMap.find(name).value();
        if(w != nullptr){
            this->stackedWidget->removeWidget(w);
            w->deleteLater();
            this->widgetMap.remove(name);

            this->stackedWidget->addWidget(widget);
            this->widgetMap.insert(name,widget);
        }
    }
}

void ParameterConfigWidget::listViewActionTargetSlot(const QModelIndex &index)
{
    qDebug()<<index.data().toString();
    if(!index.isValid()){
        return;
    }
    if(this->widgetMap.find(index.data().toString()) != this->widgetMap.end()){
        this->stackedWidget->setCurrentWidget(this->widgetMap.find(index.data().toString()).value());
    }
}
