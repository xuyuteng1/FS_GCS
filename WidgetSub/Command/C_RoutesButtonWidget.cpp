#include "C_RoutesButtonWidget.h"
#include "DMMM.h"





C_RoutesButtonWidget::C_RoutesButtonWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void C_RoutesButtonWidget::widgetInit()
{
    if(this->changedCurrentRoutePointSpinBox == nullptr){
        this->changedCurrentRoutePointSpinBox = new QSpinBox;
        this->changedCurrentRoutePointSpinBox->setObjectName("WidgetCMD");
        this->changedCurrentRoutePointSpinBox->setMinimum(1);
    }

    if(this->changedCurrentRoutePointButton == nullptr){
        this->changedCurrentRoutePointButton = new QPushButton(QStringLiteral("跳转至此航点"));
        this->changedCurrentRoutePointButton->setObjectName("WidgetCMD_Action");
    }
    if(this->beginRoutesTaskButton == nullptr){
        this->beginRoutesTaskButton = new QPushButton(QStringLiteral("开始任务"));
        this->beginRoutesTaskButton->setObjectName("WidgetCMD_Action");
    }
    if(this->reloadRoutesTaskButton == nullptr){
        this->reloadRoutesTaskButton = new QPushButton(QStringLiteral("恢复任务"));
        this->reloadRoutesTaskButton->setObjectName("WidgetCMD_Action");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,1,1);
    this->widgetLayout->addWidget(this->beginRoutesTaskButton,1,1,1,4);
    this->widgetLayout->addWidget(this->reloadRoutesTaskButton,2,1,1,4);
    this->widgetLayout->addWidget(this->changedCurrentRoutePointSpinBox,3,1,1,2);
    this->widgetLayout->addWidget(this->changedCurrentRoutePointButton,3,3,1,2);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,5,1,1);

    this->setLayout(this->widgetLayout);

}

void C_RoutesButtonWidget::connectSignalAndSlot()
{
    connect(this->changedCurrentRoutePointButton,&QPushButton::pressed,this,&C_RoutesButtonWidget::changedCurrentRoutePointButtonPressedSlot);
    connect(this->beginRoutesTaskButton,&QPushButton::pressed,this,&C_RoutesButtonWidget::beginRoutesTaskButtonPressedSlot);
    connect(this->reloadRoutesTaskButton,&QPushButton::pressed,this,&C_RoutesButtonWidget::reloadRoutesTaskButtonPressedSlot);
}

void C_RoutesButtonWidget::changedCurrentRoutePointButtonPressedSlot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_ChangeMissionItem(this->changedCurrentRoutePointSpinBox->value());
        }
    }
}

void C_RoutesButtonWidget::beginRoutesTaskButtonPressedSlot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_startMission(false);
        }
    }
}

void C_RoutesButtonWidget::reloadRoutesTaskButtonPressedSlot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_startMission(true);
        }
    }
}










