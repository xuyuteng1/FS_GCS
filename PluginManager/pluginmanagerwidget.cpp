#include "pluginmanagerwidget.h"

PluginManagerWidget::PluginManagerWidget(QWidget *parent) : QWidget(parent)
{
    widgetInit();
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    connectSignalAndSlot();
}

void PluginManagerWidget::widgetInit()
{
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("日志管理"));
        w_title->setMaximumHeight(40);
    }

    if(this->view == nullptr){
        this->view = new QTableView;
        this->view->setModel(this->model);
        this->view->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        this->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        this->view->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->view->setAttribute(Qt::WA_StyledBackground,true);
        this->view->setObjectName("widgetTableView");
        this->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->view->horizontalHeader()->setStretchLastSection(true);
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    this->widgetLayout->addWidget(this->w_title,0,0,1,10);
    this->widgetLayout->addWidget(this->view,1,0,10,10);

    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(5);

    this->setLayout(this->widgetLayout);

    this->resize(QSize(900,700));
}

void PluginManagerWidget::connectSignalAndSlot()
{
    connect(this->view,&QTableView::clicked,this,&PluginManagerWidget::tableItemClickedSlot);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();});
}


void PluginManagerWidget::tableItemClickedSlot(const QModelIndex &index)
{
    if((index.column() + Qt::UserRole + 1) == PluginManagerModel::PluginManagerRoles::ENABLED){
        bool pluginStatus = this->model->data(index, PluginManagerModel::PluginManagerRoles::ENABLED).toBool();
        this->model->setData(index, !pluginStatus,PluginManagerModel::PluginManagerRoles::ENABLED);
    }
}
