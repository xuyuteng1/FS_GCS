#include "general_config.h"

WidgetGeneralConfig::WidgetGeneralConfig(QWidget *parent) : QWidget(parent)
{
    initWidget();
    connectSignalAndSlot();
    this->setAttribute(Qt::WA_StyledBackground,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("通用配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
//    this->setFixedSize(1000,700);
}

void WidgetGeneralConfig::initWidget()
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

    /* Add Sub Widget */

    if(this->G_widget_Basic == nullptr){
        this->G_widget_Basic = new G_CFG_Basic();
    }
    addNewWidget(QStringLiteral("通用配置"),this->G_widget_Basic);

    if(this->G_widget_Orientation == nullptr){
        this->G_widget_Orientation = new G_CFG_BoardOrientation();
    }
    addNewWidget(QStringLiteral("安装方向"),this->G_widget_Orientation);

    if(this->G_widget_AccCali == nullptr){
        this->G_widget_AccCali = new G_CFG_AccCali();
    }
    addNewWidget(QStringLiteral("加计校准"),this->G_widget_AccCali);

    if(this->G_widget_MagCali == nullptr){
        this->G_widget_MagCali = new G_CFG_MagCali();
    }
    addNewWidget(QStringLiteral("罗盘校准"),this->G_widget_MagCali);

    if(this->G_widget_SerialManager == nullptr){
        this->G_widget_SerialManager = new G_CFG_SerialManager();
    }
    addNewWidget(QStringLiteral("串口配置"),this->G_widget_SerialManager);

    if(this->G_widget_AntennaPos == nullptr){
        this->G_widget_AntennaPos = new G_CFG_AntennaPos();
    }
    addNewWidget(QStringLiteral("天线位置"),this->G_widget_AntennaPos);

    if(this->G_widget_RC == nullptr){
        this->G_widget_RC = new G_CFG_RC();
    }
    addNewWidget(QStringLiteral("遥控配置"),this->G_widget_RC);

    if(this->G_widget_PreCali == nullptr){
        this->G_widget_PreCali = new G_CFG_PreCali();
    }
    addNewWidget(QStringLiteral("飞前校准"),this->G_widget_PreCali);


    if(this->G_widget_Debug == nullptr){
        this->G_widget_Debug = new G_CFG_Debug();
    }
    addNewWidget(QStringLiteral("参数调试"),this->G_widget_Debug);
}

void WidgetGeneralConfig::connectSignalAndSlot()
{
    connect(this->listWidget,&QListView::doubleClicked,this,&WidgetGeneralConfig::listViewActionTargetSlot);
    connect(this->listWidget,&QListView::clicked,this,&WidgetGeneralConfig::listViewActionTargetSlot);
}

void WidgetGeneralConfig::addNewWidget(QString name, QWidget *widget)
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

void WidgetGeneralConfig::listViewActionTargetSlot(const QModelIndex &index)
{
    qDebug()<<index.data().toString();
    if(!index.isValid()){
        return;
    }
    if(this->widgetMap.find(index.data().toString()) != this->widgetMap.end()){
        this->stackedWidget->setCurrentWidget(this->widgetMap.find(index.data().toString()).value());
    }
}
