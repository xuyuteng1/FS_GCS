#include "systemcommondwidget.h"



SystemMenuWidget::SystemMenuWidget(QWidget *parent)
{
    widgetInit();
    connectSignalAnsSlot();
}

void SystemMenuWidget::addSystemMenu(QString buttonName, QString buttonText, QWidget *widget, QIcon ico)
{
    if((this->commondContainer->widgetIsExist(buttonName) == false )&&( this->buttonContainer->buttonIsExist(buttonName) == false)){
        this->buttonContainer->addMenuButton(buttonName,buttonText,ico);
        this->commondContainer->addCommondWidget(buttonName,widget);
    }
}

void SystemMenuWidget::addSystemMenu(QString buttonName,QString buttonText, QString signalName,QIcon ico)
{

}

void SystemMenuWidget::widgetInit()
{
    if(this->buttonContainer == nullptr){
        this->buttonContainer = new SystemMenuButtonContainer();

    }

    if(this->commondContainer == nullptr){
        this->commondContainer = new SystemCommondWidgetContainer();
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }


    if(this->comondScene == nullptr){
        this->comondScene = new QGraphicsScene();
    }

    if(this->commondView == nullptr){
        this->commondView = new QGraphicsView();
    }

    if(this->buttonScene == nullptr){
        this->buttonScene = new QGraphicsScene();
    }

    if(this->buttonView == nullptr){
        this->buttonView = new QGraphicsView();
    }

//    if(this->buttonViewButton == nullptr){
//        this->buttonViewButton = new SvgButtonItem();
//    }

//    if(this->commondViewButton == nullptr){
//        this->commondViewButton = new SvgButtonItem();
//    }

//    if(this->buttonViewBorder == nullptr){
//        this->buttonViewBorder = new SvgBorderItem();
//    }

//    if(this->commondViewBorder == nullptr){
//        this->commondViewBorder = new SvgBorderItem();
//    }

    if(this->buttonViewWidget == nullptr){
        this->buttonViewWidget = new SvgGraphicsWidgetItem();
    }

    if(this->commondViewWidget == nullptr){
        this->commondViewWidget = new SvgGraphicsWidgetItem();
    }
    AddCopterWidget();
    this->widgetLayout->addWidget(this->commondContainer,1,0,2,1);
    this->widgetLayout->addWidget(this->buttonContainer,3,0,1,1);

    this->widgetLayout->setMargin(0);
    this->widgetLayout->setSpacing(0);

    this->setLayout(this->widgetLayout);

}

void SystemMenuWidget::connectSignalAnsSlot()
{
    connect(this->buttonContainer,&SystemMenuButtonContainer::buttonPressedSignal,this->commondContainer,&SystemCommondWidgetContainer::chooseWidgetChangeSlot);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&SystemMenuWidget::handle_DMMM_event);
}

void SystemMenuWidget::AddCopterWidget()
{
    this->buttonContainer->ClearMenuButton();
    this->commondContainer->ClearCommondWidget();
    this->commondContainer->setVisible(false);
    if(this->C_Widget_motorUnlock == nullptr){
        this->C_Widget_motorUnlock = new C_MotorUnlockWidget();
    }
    if(this->C_Widget_takeoffMenu == nullptr){
        this->C_Widget_takeoffMenu = new C_TakeoffMenuWidget();
    }

    if(this->C_Widget_Land == nullptr){
        this->C_Widget_Land = new C_LandWidget();
    }

    if(this->C_Widget_waypoint == nullptr){
        this->C_Widget_waypoint = new C_WaypointWidget();
    }

    if(this->C_Widget_routesButton == nullptr){
        this->C_Widget_routesButton = new C_RoutesButtonWidget();
    }

    if(this->C_Widget_SetModeWidget == nullptr){
        this->C_Widget_SetModeWidget = new C_SetModeWidget();
    }
    this->addSystemMenu("motorUnlock",QStringLiteral("解锁"),this->C_Widget_motorUnlock, QIcon(":/img/png/ARM.png"));
    this->addSystemMenu("takeoff",QStringLiteral("起飞"),this->C_Widget_takeoffMenu, QIcon(":/img/png/takeoff.png"));
    this->addSystemMenu("land",QStringLiteral("降落"),this->C_Widget_Land, QIcon(":/img/png/touckdown.png"));
    this->addSystemMenu("waypoint",QStringLiteral("航点"),this->C_Widget_waypoint, QIcon(":/img/png/waypoint.png"));
    this->addSystemMenu("routes",QStringLiteral("航线"),this->C_Widget_routesButton, QIcon(":/img/png/routes.png"));
    this->addSystemMenu("setmode",QStringLiteral("模式"),this->C_Widget_SetModeWidget, QIcon(":/img/png/model.png"));
}

void SystemMenuWidget::AddPlaneWidget()
{
    this->buttonContainer->ClearMenuButton();
    this->commondContainer->ClearCommondWidget();
    this->commondContainer->setVisible(false);

    if(this->C_Widget_motorUnlock == nullptr){
        this->C_Widget_motorUnlock = new C_MotorUnlockWidget();
    }

    if(this->P_Widget_SetModeWidget == nullptr){
        this->P_Widget_SetModeWidget = new P_SetModeWidget();
    }

    if(this->P_Widget_preaction == nullptr){
        this->P_Widget_preaction = new WidgetPreAction();
    }
    if(this->P_Widget_RTL == nullptr){
        this->P_Widget_RTL = new P_CMD_RTL();
    }
    if(this->P_Widget_Takeoff == nullptr){
        this->P_Widget_Takeoff = new P_CMD_Takeoff();
    }
    if(this->P_Widget_Waypoint == nullptr){
        this->P_Widget_Waypoint = new P_CMD_Waypoint();
    }
    if(this->P_Widget_Land == nullptr){
        this->P_Widget_Land = new P_LandWidget();
    }
    this->addSystemMenu("motorUnlock",QStringLiteral("解锁"),this->C_Widget_motorUnlock, QIcon(":/img/png/ARM.png"));
    this->addSystemMenu("PlaneTakeoff",QStringLiteral("起飞"),this->P_Widget_Takeoff, QIcon(":/img/png/takeoff.png"));
    this->addSystemMenu("land",QStringLiteral("降落"),this->P_Widget_Land, QIcon(":/img/png/touckdown.png"));
    this->addSystemMenu("PlaneRTL",QStringLiteral("返航"),this->P_Widget_RTL, QIcon(":/img/png/RTL.png"));
    this->addSystemMenu("Planewaypoint",QStringLiteral("航点"),this->P_Widget_Waypoint, QIcon(":/img/png/waypoint.png"));

    this->addSystemMenu("routes",QStringLiteral("航线"),this->C_Widget_routesButton, QIcon(":/img/png/routes.png"));
    this->addSystemMenu("setmode",QStringLiteral("模式"),this->P_Widget_SetModeWidget, QIcon(":/img/png/model.png"));
//    this->addSystemMenu("preaction",QStringLiteral("清零"),this->P_Widget_preaction, QIcon(":/img/png/cali.png"));
}

void SystemMenuWidget::buttonPressedSlot(QString name)
{
}


SystemMenuButtonContainer::SystemMenuButtonContainer(QWidget *parent) : QWidget(parent)
{
    initWidget();
    this->setObjectName("SystemMenuWidget");
    this->setAttribute(Qt::WA_StyledBackground,true);
}

void SystemMenuButtonContainer::addMenuButton(QString name,QString buttonText,QIcon &ico,QString buttonObjectName)
{
    if(this->buttonMap.find(name) == this->buttonMap.end()){
        QToolButton *button = new QToolButton();
        button->setIcon(ico);
        button->setText(buttonText);
        button->setToolTip(name);
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setObjectName(buttonObjectName);
        button->setIconSize(QSize(42, 42));
        button->setPopupMode(QToolButton::InstantPopup);
        this->widgetLayout->addWidget(button);
        connect(button,&QPushButton::clicked,[=]{emit buttonPressedSignal(name);});
    }else{
        qDebug()<<QStringLiteral("按键'%1'添加失败,命名重复").arg(name);
    }
}

void SystemMenuButtonContainer::addMenuButton(QString name,QString buttonText, QString signalName,QIcon& ico,QString buttonObjectName)
{
    if(this->buttonMap.find(name) == this->buttonMap.end()){
        QToolButton *button = new QToolButton();
        button->setIcon(ico);
        button->setText(buttonText);
        button->setToolTip(name);
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setObjectName(buttonObjectName);
        button->setIconSize(QSize(42, 42));
        button->setPopupMode(QToolButton::InstantPopup);
        this->widgetLayout->addWidget(button);
        this->buttonMap.insert(name,button);
        connect(button,&QToolButton::clicked,[=]{globalObserver::getGlobalObserver()->notify(signalName);});
    }else{
        qDebug()<<QStringLiteral("按键'%1'添加失败,命名重复").arg(name);
    }
}

void SystemMenuButtonContainer::ClearMenuButton()
{
    while(this->widgetLayout->count()){
        QWidget *pWidget = this->widgetLayout->itemAt(0)->widget();//循环每次取第一个控件，依次删除下去
        pWidget->setParent(NULL);
        this->widgetLayout->removeWidget(pWidget);
        delete pWidget;
    }
    this->buttonMap.clear();
}
bool SystemMenuButtonContainer::buttonIsExist(QString name)
{
    return ((this->buttonMap.find(name) != this->buttonMap.end()) ? true : false);
}

void SystemMenuButtonContainer::initWidget()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QHBoxLayout();
        this->widgetLayout->setContentsMargins(15,15,15,25);
        this->setLayout(this->widgetLayout);
    }
}

SystemCommondWidgetContainer::SystemCommondWidgetContainer(QWidget *parent)
{
    this->setObjectName("SystemCommondWidgetContainer");
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->addWidget(new QWidget);
    this->setMinimumHeight(160);
    this->setVisible(false);
}

void SystemCommondWidgetContainer::addCommondWidget(QString name, QWidget *widget)
{
    if(this->widgetMap.find(name) == this->widgetMap.end()){
        this->widgetMap.insert(name,widget);
        this->addWidget(widget);
//        this->setCurrentWidget(widget);
    }else{
        qDebug()<<QStringLiteral("页面'%1'添加失败,命名重复").arg(name);
    }
}

void SystemCommondWidgetContainer::ClearCommondWidget()
{
    this->widgetMap.clear();
}

bool SystemCommondWidgetContainer::widgetIsExist(QString name)
{
    return ((this->widgetMap.find(name) != this->widgetMap.end()) ? true : false);
}

void SystemCommondWidgetContainer::chooseWidgetChangeSlot(QString widgetName)
{
    if(this->widgetMap.find(widgetName) != this->widgetMap.end()){
        if(this->isVisible()){
            if(this->widgetMap.find(widgetName).value() == this->currentWidget()){
                this->setVisible(false);
            }else{
                this->setCurrentWidget(this->widgetMap.find(widgetName).value());
                this->setVisible(true);
            }
        }else{
            this->setCurrentWidget(this->widgetMap.find(widgetName).value());
            this->setVisible(true);
        }
    }else{
        this->setVisible(false);
    }
}



void SystemMenuWidget::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_NewVehicleType:
        if(Qt::DMMM()->getFlyLink_main() != nullptr){
            switch(Qt::DMMM()->getFlyLink_main()->getTDataPort().VehicleType){
                case FlyLink::VehicleType_e::VehicleType_Plane:
                AddPlaneWidget();
                break;
                case FlyLink::VehicleType_e::VehicleType_Copter:
                default:
                AddCopterWidget();
                break;
            }
        }
        break;
    default:break;
    }
}
