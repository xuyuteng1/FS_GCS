#include "systemtoolbar.h"

SystemToolBar::SystemToolBar(QWidget *parent) : QToolBar(parent)
{
    initWidget();
    this->setObjectName("SystemToolBar");

    this->setAttribute(Qt::WA_StyledBackground,true);

    connectSignalAndSlot();
}

void SystemToolBar::initWidget()
{

    if(this->rangingButton == nullptr){
        this->rangingButton = new QAction();
        this->rangingButton->setIcon(QIcon(":/img/png/mapTool.png"));
        this->rangingButton->setObjectName("ToorBarButton");
        this->rangingButton->setToolTip(QStringLiteral("地图工具"));
    }

    if(this->routePlanningButton == nullptr){
        this->routePlanningButton = new QAction();
        this->routePlanningButton->setIcon(QIcon(":/img/png/routePlanning.png"));
        this->routePlanningButton->setObjectName("ToorBarButton");
        this->routePlanningButton->setToolTip(QStringLiteral("航线规划"));

    }

    if(this->electronicFenceButton == nullptr){
        this->electronicFenceButton = new QAction();
        this->electronicFenceButton->setIcon(QIcon(":/img/png/electronicFence.png"));
        this->electronicFenceButton->setObjectName("ToorBarButton");
        this->electronicFenceButton->setToolTip(QStringLiteral("电子围栏"));
    }

    if(this->waypointMarkerButton == nullptr){
        this->waypointMarkerButton = new QAction();
        this->waypointMarkerButton->setIcon(QIcon(":/img/png/pointMarker.png"));
        this->waypointMarkerButton->setObjectName("ToorBarButton");
        this->waypointMarkerButton->setToolTip(QStringLiteral("航点标记"));
    }

    this->toggleViewAction()->setText("<<");
    this->toggleViewAction()->setObjectName("ToorBarButton");
    this->addAction(this->rangingButton);
    this->addAction(this->routePlanningButton);
    this->addAction(this->electronicFenceButton);
    this->addAction(this->waypointMarkerButton);

    this->setOrientation(Qt::Horizontal);
}

void SystemToolBar::connectSignalAndSlot()
{
    connect(this->rangingButton,&QAction::triggered,this,&SystemToolBar::rangingButtonPressedSlot);
    connect(this->routePlanningButton,&QAction::triggered,this,&SystemToolBar::routePlanningButtonPressedSlot);
    connect(this->electronicFenceButton,&QAction::triggered,this,&SystemToolBar::electronicFenceButtonPressedSlot);
    connect(this->waypointMarkerButton,&QAction::triggered,this,&SystemToolBar::waypointMarkerButtonPressedSlot);
    connect(this->toggleViewAction(),&QAction::toggled,this,&SystemToolBar::toggleViewActionSlot);
}


void SystemToolBar::rangingButtonPressedSlot()
{
    emit ToolBar_RangingButtonPressedSignal(this->rangingButton->isChecked());
}

void SystemToolBar::routePlanningButtonPressedSlot()
{
    emit ToolBar_RoutePlanningButtonPressedSignal(this->routePlanningButton->isChecked());
}

void SystemToolBar::electronicFenceButtonPressedSlot()
{
    emit ToolBar_ElectronicFenceButtonPressedSignal(this->electronicFenceButton->isChecked());
}

void SystemToolBar::waypointMarkerButtonPressedSlot()
{
    emit ToolBar_WaypointMarkerButtonPressedSignal(this->electronicFenceButton->isChecked());
}

void SystemToolBar::toggleViewActionSlot(bool status)
{
    if(status){
        this->toggleViewAction()->setText("<<");
    }else{
        this->toggleViewAction()->setText(">>");
    }
}



void SystemToolBar::rangingButtonStatusChangedSlot(bool status)
{
    this->rangingButton->setChecked(status);
}

void SystemToolBar::routePlanningButtonStatusChangedSlot(bool status)
{
    this->routePlanningButton->setChecked(status);
}

void SystemToolBar::electronicFenceButtonStatusChangedSlot(bool status)
{
    this->electronicFenceButton->setChecked(status);
}

void SystemToolBar::waypointMarkerButtonStatusChangedSlot(bool status)
{
    this->waypointMarkerButton->setChecked(status);
}
