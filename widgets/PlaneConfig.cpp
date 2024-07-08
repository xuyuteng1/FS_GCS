#include "PlaneConfig.h"

PlaneConfigWidget::PlaneConfigWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
    connectSignalAndSlot();
//    this->setAttribute(Qt::WA_StyledBackground,false);
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("固定翼配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
//    this->setFixedSize(1000,700);
}

void PlaneConfigWidget::initWidget()
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


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    this->setObjectName("systemWidget");
    this->widgetLayout->addWidget(this->splitterWidget,0,0,5,10);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);
    this->setLayout(this->widgetLayout);

    if(this->P_widget_Takeoff == nullptr){
        this->P_widget_Takeoff = new P_CFG_Takeoff();
    }
    if(this->P_widget_Failsafe == nullptr){
        this->P_widget_Failsafe = new P_CFG_Failsafe();
    }
    if(this->P_widget_Basic == nullptr){
        this->P_widget_Basic = new P_CFG_Basic();
    }

    if(this->P_widget_Parachute == nullptr){
        this->P_widget_Parachute = new P_Cfg_Parachute(nullptr,QStringLiteral("伞舱控制"));
    }

    addNewWidget(QStringLiteral("基础配置"),this->P_widget_Basic);
    addNewWidget(QStringLiteral("故障保护"),this->P_widget_Failsafe);
    addNewWidget(QStringLiteral("起飞配置"),this->P_widget_Takeoff);
    addNewWidget(QStringLiteral("伞舱控制"),this->P_widget_Parachute);


}

void PlaneConfigWidget::connectSignalAndSlot()
{
    connect(this->listWidget,&QListView::doubleClicked,this,&PlaneConfigWidget::listViewActionTargetSlot);
    connect(this->listWidget,&QListView::clicked,this,&PlaneConfigWidget::listViewActionTargetSlot);
}

void PlaneConfigWidget::addNewWidget(QString name, QWidget *widget)
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

void PlaneConfigWidget::listViewActionTargetSlot(const QModelIndex &index)
{
    qDebug()<<index.data().toString();
    if(!index.isValid()){
        return;
    }
    if(this->widgetMap.find(index.data().toString()) != this->widgetMap.end()){
        this->stackedWidget->setCurrentWidget(this->widgetMap.find(index.data().toString()).value());
    }
}
