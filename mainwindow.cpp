#include "mainwindow.h"
#include <QDesktopWidget>

#include <QtPlatformHeaders/QWindowsWindowFunctions>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->systemInit();
    this->setFixedSize(QApplication::desktop()->screen()->size());
    this->widgetBaseInit();
    this->initMapBaseWidget();
    this->initCommondBaseWidget();
    this->initSystemInfoBaseWidget();
    this->initSystemConfigBaseWidget();

    maintimer_10Hz = new QTimer();
    connectSignalAndSlot();
    maintimer_10Hz->start(100);

    this->showFullScreen();
    QWindowsWindowFunctions::setHasBorderInFullScreen(this->windowHandle(), true);
    this->setWindowState(Qt::WindowFullScreen);

    qDebug()<<"OpenSSL"<<QSslSocket::sslLibraryBuildVersionString();
    qDebug()<<"OpenSSL soupport:"<<QSslSocket::supportsSsl();
}

MainWindow::~MainWindow()
{
    if(datapoolThread->isRunning())
    {
        datapoolThread->quit();
        datapoolThread->wait();
    }
}

void MainWindow::systemInit()
{
    if(this->plugin == nullptr){
        this->plugin = new PluginManager( );
    }

    datapoolThread = new QThread();
    Qt::DMMM()->moveToThread(datapoolThread);
    datapoolThread->start(QThread::HighPriority);
    qDebug()<<"Q_DMMM"<<QThread::currentThreadId()<<Qt::DMMM()->thread();
}


void MainWindow::connectSignalAndSlot()
{
    connect(this->titleWidget,&TitleWidget::closeButtonPressedSignal,this,&MainWindow::closeButtonPressedSlot);                 //右上角退出按钮
    connect(this->titleWidget,&TitleWidget::minimizeButtonPressedSignal,this,&MainWindow::minimizeButtonPressedSlot);           //右上角最小化按钮
    connect(this->titleWidget,&TitleWidget::selectButtonPressedSignal,this,&MainWindow::selectButtonPressedSlot);               //左上角选择按钮
    connect(this->titleWidget,&TitleWidget::connectionButtonPressedSignal,this,&MainWindow::connectionButtonPressedSlot);       //右上角通讯连接按钮

    connect(this->toolBar,&SystemToolBar::ToolBar_RangingButtonPressedSignal,this,&MainWindow::ToolBar_RangingButtonPressedSlot);                       //左侧四个图标
    connect(this->toolBar,&SystemToolBar::ToolBar_RoutePlanningButtonPressedSignal,this,&MainWindow::ToolBar_RoutePlanningButtonPressedSlot);
    connect(this->toolBar,&SystemToolBar::ToolBar_ElectronicFenceButtonPressedSignal,this,&MainWindow::ToolBar_ElectronicFenceButtonPressedSlot);
    connect(this->toolBar,&SystemToolBar::ToolBar_WaypointMarkerButtonPressedSignal,this,&MainWindow::ToolBar_WaypointMarkerButtonPressedSlot);
    connect(this->toolBar->toggleViewAction(),&QAction::toggled,this,&MainWindow::ToolBar_ToggleActionChangedSlot);                                     //隐藏或显示这四个图标


    connect(this,&MainWindow::rangingButtonStatusChangedSignal,this->toolBar,&SystemToolBar::rangingButtonStatusChangedSlot);                           //设置四个图标的功能切换
    connect(this,&MainWindow::routePlanningButtonStatusChangedSignal,this->toolBar,&SystemToolBar::routePlanningButtonStatusChangedSlot);
    connect(this,&MainWindow::electronicFenceButtonStatusChangedSignal,this->toolBar,&SystemToolBar::electronicFenceButtonStatusChangedSlot);
    connect(this,&MainWindow::waypointMarkerButtonStatusChangedSignal,this->toolBar,&SystemToolBar::waypointMarkerButtonStatusChangedSlot);

    connect(this->rangingToolBarWidget,&RangingToolBarWidget::rangingButtonPressedSligal,this,&MainWindow::rangingButtonPressedSlot);                   //设置第一个图标的六种功能（地图功能）
    connect(this->rangingToolBarWidget,&RangingToolBarWidget::areaButtonPressedSignal,this,&MainWindow::areaButtonPressedSlot);
    connect(this->rangingToolBarWidget,&RangingToolBarWidget::pointButtonPressedSignal,this,&MainWindow::pointButtonPressedSlot);
    connect(this->rangingToolBarWidget,&RangingToolBarWidget::perspectiveFollowButtonPresssedSignal,this,&MainWindow::perspectiveFollowButtonPresssedSlot);
    connect(this->rangingToolBarWidget,&RangingToolBarWidget::seekAirButtonPressedSignal,this,&MainWindow::seekAirButtonPressedSlot);
    connect(this->rangingToolBarWidget,&RangingToolBarWidget::clearAirPathButtonPressedSignal,this,&MainWindow::clearAirPathButtonPressedSlot);

    connect(this->routesWidget,&RoutesWidget::appendPointForMousePressedSignal,this,&MainWindow::appendPointForMousePressedSlot);                       //设置第二个图标的功能（航线编辑）
    connect(this->routesWidget,&RoutesWidget::routesWidgetCloseSignal,this,&MainWindow::routesWidgetCloseSlot);

    connect(this->maintimer_10Hz,&QTimer::timeout,this->dataView,&DataView::update_display);                        //10HZ更新 通用工具->信息面板 的内容
    connect(this->maintimer_10Hz,&QTimer::timeout,this,&MainWindow::updateFor100HZTimerSlot);                       //10HZ更新 地图信息
    connect(this->maintimer_10Hz,&QTimer::timeout,this,&MainWindow::updateHUDData);                                 //10HZ更新 HUD（右上角）
    connect(this->maintimer_10Hz,&QTimer::timeout,this,&MainWindow::update_promptwidget);                           //10HZ更新 中间上方（黄色字体）
    connect(this->maintimer_10Hz,&QTimer::timeout,this->mapView,&GIS_MapView::updateGcsOnTimerSlot);                //空白
    connect(this->maintimer_10Hz,&QTimer::timeout,this,&MainWindow::update_gis);
    connect(this->maintimer_10Hz,&QTimer::timeout,this->systemInfoWidget,&SystemInfoWidget::update_sysinfo);        //10HZ更新 右侧状态显示栏


    connect(this->communicationWidget,&CommunicationsWidget::newConnectGcsIDSignal,this,&MainWindow::newConnectGcsIDSlot);
    connect(this->mapView,&GIS_MapView::mousePressedForMapSignal,this,&MainWindow::mousePressedForMapSlot);
//    connect(this->systemMenuWidget,&SystemMenuWidget::req_gis_loc_Signal,this,&MainWindow::req_gis_loc_Slot);
//    connect(this->systemMenuWidget,&SystemMenuWidget::event_edit_guidedPointModel,this,&MainWindow::event_edit_guidedPointModelSlot);
//    connect(this->systemMenuWidget,&SystemMenuWidget::clearWapPointSignal,this,&MainWindow::clearWapPointSlot);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&MainWindow::handle_DMMM_event);
    connect(this->promptWidget,&PromptWidget::promptWidgetLeftButtonPressedSignal,this,&MainWindow::promptWidgetLeftButtonPressedSlot);                         //按下中间上方左侧按钮（debug，无实际作用）
    connect(this->promptWidget,&PromptWidget::promptWidgetRightButtonPressedSignal,this,&MainWindow::promptWidgetRightButtonPressedSlot);                       //按下中间上方右侧按钮（对话框）

    connect(this->appConfigWidget,&ApplicatinConfigure::mapSourcesChangedSignal,this->mapView,&GIS_MapView::mapSourcesChangedSlot);

    connect(this->titleWidget,&TitleWidget::basicConfigActionTriggeredSignal,this,&MainWindow::basicConfigActionTriggeredSlot);                                 //左上角多旋翼配置->基础参数
    connect(this->titleWidget,&TitleWidget::systemConfigActionTriggeredSignal,this,&MainWindow::systemConfigActionTriggeredSlot);                               //左上角地面站配置->地面功能配置
    connect(this->titleWidget,&TitleWidget::parameterConfigAcitonTriggeredSignal,this,&MainWindow::parameterConfigAcitonTriggeredSlot);                         //左上角多旋翼配置->控制参数
    connect(this->titleWidget,&TitleWidget::communicationConfigActionTriggeredSignal,this,&MainWindow::communicationConfigActionTriggeredSlot);                 //左上角地面站配置->通讯接口配置
    connect(this->titleWidget,&TitleWidget::loggerManagerActionTriggeredSignal,this,&MainWindow::loggerManagerActionTriggeredSlot);                             //左上角通用工具->机载日志
    connect(this->titleWidget,&TitleWidget::realTimeDataActionTriggeredSignal,this,&MainWindow::realTimeDataActionTriggeredSlot);                               //左上角通用工具->波形显示
    connect(this->titleWidget,&TitleWidget::panelDataActionTriggeredSignal,this,&MainWindow::panelDataActionTriggeredSlot);                                     //左上角通用工具->信息面板
    connect(this->titleWidget,&TitleWidget::pluginManagerActionTriggeredSignal,this,&MainWindow::pluginManagerActionTriggeredSlot);                             //左上角地面站配置->插件管理模块
    connect(this->titleWidget,&TitleWidget::FCBoardInfoActionTriggeredSignal,this,&MainWindow::FCBoardInfoActionActionTriggeredSlot);                           //左上角硬件信息
    connect(this->titleWidget,&TitleWidget::FundbgPortActionTriggeredSignal,this,&MainWindow::FunDbgPortActionActionTriggeredSlot);                             //左上角调试界面
    connect(PluginManagerModelPtr::getModelPtr(),&PluginManagerModel::videoWidgetCreateSignal,this,&MainWindow::videoWidgetCreateSlot);
    connect(PluginManagerModelPtr::getModelPtr(),&PluginManagerModel::videoWidgetRemoveSignal,this,&MainWindow::videoWidgetRemoveSlot);
}

void MainWindow::widgetBaseInit()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->titleWidget == nullptr){
        this->titleWidget = new TitleWidget();
    }
    this->widgetLayout->addWidget(this->titleWidget,0,0,1,16);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);

    this->setLayout(this->widgetLayout);

    QFile file(QString(":/style/widgetStyle.qss"));

    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}


//地图，载荷显示 放入该层
void MainWindow::initMapBaseWidget()
{
    if(this->mapView == nullptr){
        this->mapView = new GIS_MapView();
        QSettings setting("./cfg/Setting.ini", QSettings::IniFormat);
        bool lat_ok = false;
        bool lng_ok = false;
        int lat = setting.value("home/lat").toInt(&lat_ok);
        int lng = setting.value("home/lng").toInt(&lng_ok);
        if(lat_ok&& lng_ok){

            QGeoCoordinate coor = QGeoCoordinate(lat*1e-7,lng*1e-7);
            emit this->mapView->setCenterCoordinateSiganl(QVariant::fromValue<QGeoCoordinate>(coor));
            qDebug()<<"init map pos"<<coor;
        }

    }

    if(this->videoWidget == nullptr){
        this->videoWidget = new VideoWidget();
        this->videoWidget->setObjectName("VideoWidget");
    }

    if(this->mapBaseWidget == nullptr){
        this->mapBaseWidget = new QWidget();
    }

    if(this->mapBaseLayout == nullptr){
        this->mapBaseLayout = new QGridLayout();
    }

    this->mapBaseLayout->addWidget(this->mapView,0,0,16,9);
    this->mapBaseLayout->addWidget(this->videoWidget,12,0,4,2);
    this->mapBaseLayout->setSpacing(0);
    this->mapBaseLayout->setMargin(0);

    this->mapBaseWidget->setLayout(this->mapBaseLayout);

    if(this->widgetLayout != nullptr){
        this->widgetLayout->addWidget(this->mapBaseWidget,1,0,17,16);
    }



}


//工具栏，菜单栏放入该层
void MainWindow::initCommondBaseWidget()
{
    if(this->cmdBaseLayout == nullptr){
        this->cmdBaseLayout = new QGridLayout();
    }

    QGridLayout *toolBarLayout = new QGridLayout();

    if(this->rangingToolBarWidget == nullptr){
        this->rangingToolBarWidget = new RangingToolBarWidget();
        this->rangingToolBarWidget->setOrientation(Qt::Vertical);
        toolBarLayout->addWidget(this->rangingToolBarWidget,1,1,6,1);
        this->rangingToolBarWidget->setWidgetVisable(false);
    }

    if(this->toolBar == nullptr){
        this->toolBar = new SystemToolBar();
        this->toolBar->setAllowedAreas(Qt::LeftToolBarArea);
        this->toolBar->setOrientation(Qt::Vertical);
        toolBarLayout->addWidget(this->toolBar,1,0,4,1);
        toolBarLayout->addItem(new QSpacerItem(0,40,QSizePolicy::Fixed,QSizePolicy::Expanding),6,0,1,1);
        toolBarLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),1,2,1,1);
    }

    QToolBar *menuMineSizeBar = new QToolBar();
    menuMineSizeBar->addAction(this->toolBar->toggleViewAction());

    toolBarLayout->addWidget(menuMineSizeBar,0,0,1,1);
    menuMineSizeBar->setObjectName("SystemToolBar");

    toolBarLayout->setSpacing(0);

    this->cmdBaseLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),0,0,9,9);
    this->cmdBaseLayout->addLayout(toolBarLayout,0,0,3,3);
    if(this->systemMenuWidget == nullptr){
        this->systemMenuWidget = new SystemMenuWidget();
        this->cmdBaseLayout->addWidget(this->systemMenuWidget,8,3,1,3);
    }

    this->cmdBaseLayout->setRowStretch(0,1);
    this->cmdBaseLayout->setRowStretch(1,1);
    this->cmdBaseLayout->setRowStretch(2,1);
    this->cmdBaseLayout->setRowStretch(6,1);
    this->cmdBaseLayout->setRowStretch(7,1);
    this->cmdBaseLayout->setRowStretch(8,1);

    this->cmdBaseLayout->setColumnStretch(0,1);
    this->cmdBaseLayout->setColumnStretch(1,2);
    this->cmdBaseLayout->setColumnStretch(3,1);
    this->cmdBaseLayout->setColumnStretch(4,1);
    this->cmdBaseLayout->setColumnStretch(5,1);
    this->cmdBaseLayout->setColumnStretch(6,3);


    if(this->widgetLayout != nullptr){
        this->widgetLayout->addLayout(this->cmdBaseLayout,1,0,17,16);
    }
}

//HUD界面，系统信息，模式界面，聊天界面放入该层界面
void MainWindow::initSystemInfoBaseWidget()
{
    if(this->systemInfoBaseLayout == nullptr){
        this->systemInfoBaseLayout = new QGridLayout();
    }

    if(this->hudOpenGLView ==nullptr){
        this->hudOpenGLView = new HUDWidget();
    }

    if(this->systemInfoWidget == nullptr){
        this->systemInfoWidget = new SystemInfoWidget();
    }

    if(this->chatWidget == nullptr){
        this->chatWidget = new ChatWidget();
    }

    if(this->promptWidget == nullptr){
        this->promptWidget = new PromptWidget();
    }

    QVBoxLayout *promptLayout = new QVBoxLayout();
    promptLayout->addWidget(this->promptWidget);
    promptLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding));

    QVBoxLayout *systemInfoLayout = new QVBoxLayout();
    systemInfoLayout->addWidget(this->systemInfoWidget);
    systemInfoLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Fixed,QSizePolicy::Fixed));

    this->systemInfoBaseLayout->addLayout(promptLayout,0,4,3,2);
    this->systemInfoBaseLayout->addWidget(this->chatWidget,0,6,3,2);
    this->systemInfoBaseLayout->addWidget(this->hudOpenGLView,0,8,3,2);
    this->systemInfoBaseLayout->addLayout(systemInfoLayout,3,8,8,2);
    this->systemInfoBaseLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),0,8,3,2);
    this->systemInfoBaseLayout->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding),0,0,11,10);

    this->systemInfoBaseLayout->setColumnStretch(0,4);
    this->systemInfoBaseLayout->setColumnStretch(4,2);
    this->systemInfoBaseLayout->setColumnStretch(6,2);
    this->systemInfoBaseLayout->setColumnStretch(8,2);

    this->systemInfoBaseLayout->setRowStretch(0,3);
    this->systemInfoBaseLayout->setRowStretch(3,8);

    this->systemInfoBaseLayout->setMargin(0);

    if(this->widgetLayout != nullptr){
        this->widgetLayout->addLayout(this->systemInfoBaseLayout,1,0,17,16);
    }
    this->chatWidget->setVisible(false);
}

//配置界面，航线规划界面放入该层
void MainWindow::initSystemConfigBaseWidget()
{
    if(this->baseConfigWidget == nullptr){
        this->baseConfigWidget = new QMdiArea();
        this->baseConfigWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    }

    if(this->widgetLayout != nullptr){
//        this->widgetLayout->addWidget(this->baseConfigWidget,1,0,17,16);
    }

    if(this->routesWidget == nullptr){
        this->routesWidget = new RoutesWidget(this);
    }

    if(this->dataView == nullptr){
        this->dataView = new DataView(this);
    }

    if(this->chartWidget == nullptr){
        this->chartWidget = new ChartWidget(this);
    }

    if(this->widget_CFG == nullptr){
        this->widget_CFG = new SystemConfigWidget(this);
//        this->widget_CFG->setVisible(false);
    }



    if(this->pluginWidget == nullptr){
        this->pluginWidget = new PluginManagerWidget(this);
        this->pluginWidget->setVisible(false);
    }

    if(this->parameterWidget == nullptr){
        this->parameterWidget = new ParameterConfigWidget(this);
        this->routesWidget->setVisible(false);
    }

    if(this->appConfigWidget == nullptr){
        this->appConfigWidget = new ApplicatinConfigure(this);
        this->appConfigWidget->setVisible(false);
    }

    if(this->communicationWidget == nullptr){
        this->communicationWidget = new CommunicationsWidget();
    }

    if(this->logwidget == nullptr){
        this->logwidget = new LoggerWidget(this);
        this->logwidget->setVisible(false);
    }

}



void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    if(this->width() != interfaceWidgetWidth || this->height() != interfaceWidgetHeight){
        interfaceWidgetWidth = this->width();
        interfaceWidgetHeight = this->height();
        if(this->titleWidget != nullptr){
            this->titleWidget->update();
        }
        if(this->systemMenuWidget != nullptr){
            this->systemMenuWidget->update();
        }
        if(this->mapView != nullptr){
            this->mapView->update();
        }
    }
}

void MainWindow::closeButtonPressedSlot()
{
    this->communicationWidget->close();
    this->routesWidget->close();

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(QStringLiteral("退出"));
    msgBox.setText(QStringLiteral("系统退出"));
    msgBox.setInformativeText(QStringLiteral("确认退出系统？"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:{
        this->close();
        if(!this->chatWidget->isHidden()){
            this->chatWidget->close();
        }
        if(!this->widget_CFG->isHidden()){
            this->widget_CFG->close();
        }
        if(!this->chartWidget->isHidden()){
            this->chartWidget->close();
        }
        if(!this->logwidget->isHidden()){
            this->logwidget->close();
        }
        if(!this->parameterWidget->isHidden()){
            this->parameterWidget->close();
        }
        if(!this->appConfigWidget->isHidden()){
            this->appConfigWidget->close();
        }

        if(!this->routesWidget->isHidden()){
            this->routesWidget->close();
        }

//        Log::Log_Info(QStringLiteral("系统退出"));
        TPool::tPool->waitForDone(0);
        break;
    }default:
        break;
    }

}

void MainWindow::minimizeButtonPressedSlot()
{
    this->setWindowState(Qt::WindowMinimized | this->windowState() );
}

void MainWindow::selectButtonPressedSlot()
{
    if(this->appConfigWidget == nullptr){
        this->appConfigWidget = new ApplicatinConfigure(this);
    }
    this->appConfigWidget->setVisible(true);
    this->appConfigWidget->showNormal();
}

void MainWindow::connectionButtonPressedSlot()
{
    if(this->communicationWidget == nullptr){
        this->communicationWidget = new CommunicationsWidget(this);
    }
    this->communicationWidget->setVisible(true);
    this->communicationWidget->showNormal();
}



void MainWindow::ToolBar_RangingButtonPressedSlot(bool buttontStatus)
{
    this->rangingToolBarWidget->setWidgetVisable(!this->rangingToolBarWidget->isVisible());
    if(!this->rangingToolBarWidget->isVisible()){
        this->setCursor(Qt::ArrowCursor);
        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
}

void MainWindow::ToolBar_RoutePlanningButtonPressedSlot(bool buttontStatus)
{

    if(!this->routesWidget->isVisible()){
        if(this->routesWidget->isMinimized()){
            this->routesWidget->showNormal();
        }else{
            this->routesWidget->setVisible(true);
            this->routesWidget->show();
            this->routesWidget->raise();
        }
    }else{
        this->routesWidget->hide();
        this->routesWidget->setVisible(false);
        this->setCursor(Qt::ArrowCursor);
//        this->mapView->setMapMode(WidgetModel::RoutesPlanningModel);
    }
}

void MainWindow::ToolBar_ElectronicFenceButtonPressedSlot(bool buttontStatus)
{
    Q_UNUSED(buttontStatus);
}

void MainWindow::ToolBar_WaypointMarkerButtonPressedSlot(bool buttontStatus)
{
    Q_UNUSED(buttontStatus);
}

void MainWindow::ToolBar_ToggleActionChangedSlot(bool status)
{
    Q_UNUSED(status)
    this->rangingToolBarWidget->setVisible(false);
    this->setCursor(Qt::ArrowCursor);
    this->mapView->setMapMode(WidgetModel::NormolModel);
}


void MainWindow::basicConfigActionTriggeredSlot()
{
    if(this->widget_CFG){
        this->widget_CFG->showNormal();
    }
}

void MainWindow::systemConfigActionTriggeredSlot()
{
    if(this->appConfigWidget){
        this->appConfigWidget->showNormal();
    }
}

void MainWindow::parameterConfigAcitonTriggeredSlot()
{
    if(this->parameterWidget){
        this->parameterWidget->showNormal();
    }
}

void MainWindow::communicationConfigActionTriggeredSlot()
{
    if(this->communicationWidget){
        this->communicationWidget->showNormal();
    }
}
void MainWindow::FCBoardInfoActionActionTriggeredSlot()
{
    if(FCBoardInfoptr == nullptr){
        FCBoardInfoptr = new FCBoardINFO();
        FCBoardInfoptr->show();
        FCBoardInfoptr->move(100,50);
    }
    FCBoardInfoptr->req_boardinfo();
    if(FCBoardInfoptr->isVisible()){
        return;
    }
    FCBoardInfoptr->show();
}

void MainWindow::FunDbgPortActionActionTriggeredSlot()
{
#ifdef GCS_DEBUG_ENABLE
    if(w_fundbg == nullptr){
        w_fundbg = new FunDebug();
        w_fundbg->show();
    }
    if(w_fundbg->isVisible()){
        return;
    }
    w_fundbg->show();
#endif
}

void MainWindow::loggerManagerActionTriggeredSlot()
{
    if(this->logwidget){
        this->logwidget->showNormal();
    }
}

void MainWindow::realTimeDataActionTriggeredSlot()
{
    if(this->chartWidget){
        this->chartWidget->showNormal();
    }
}

void MainWindow::panelDataActionTriggeredSlot()
{
    if(this->dataView){
        this->dataView->showNormal();
    }
}

void MainWindow::pluginManagerActionTriggeredSlot()
{
    if(this->pluginWidget){
        this->pluginWidget->showNormal();
    }
}

void MainWindow::videoWidgetCreateSlot(QWidget *wid)
{
    if(wid != nullptr){
//        qDebug()<<"MainWindow::videoWidgetCreateSlot(QWidget *wid)";
        this->widgetLayout->addWidget(wid,38,0,9,7);
//        this->videoWidget->addWidget(wid);
        this->videoWidget->update();
    }
}

void MainWindow::videoWidgetRemoveSlot(QWidget *wid)
{
    if(wid != nullptr){
        this->widgetLayout->removeWidget(wid);
        this->update();
    }
}


void MainWindow::routesWidgetCloseSlot()
{
    if(this->mapView->getMapMode() == WidgetModel::RoutesPlanningModel){
        this->setCursor(Qt::ArrowCursor);
        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
    emit this->routePlanningButtonStatusChangedSignal(false);
}

void MainWindow::rangingButtonPressedSlot(bool buttontStatus)
{
    if(buttontStatus){
        this->setCursor(Qt::PointingHandCursor);
        this->mapView->setMapMode(WidgetModel::RangingModel);
    }else{
        this->setCursor(Qt::ArrowCursor);

        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
}

void MainWindow::areaButtonPressedSlot(bool buttontStatus)
{
    if(buttontStatus){
        this->setCursor(Qt::PointingHandCursor);

        this->mapView->setMapMode(WidgetModel::AreaModel);
    }else{
        this->setCursor(Qt::ArrowCursor);

        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
}

void MainWindow::pointButtonPressedSlot(bool buttontStatus)
{
    if(buttontStatus){
        this->setCursor(Qt::PointingHandCursor);

        this->mapView->setMapMode(WidgetModel::PointModel);
    }else{
        this->setCursor(Qt::ArrowCursor);

        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
}

void MainWindow::perspectiveFollowButtonPresssedSlot(bool buttontStatus)
{
    if(buttontStatus){
        this->mapView->setCenterAirFlag(true);
    }else{
        this->mapView->setCenterAirFlag(false);
    }
}

void MainWindow::seekAirButtonPressedSlot()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        if(link->getTDataPort().pos_get){
            QGeoCoordinate coor = QGeoCoordinate(link->getTDataPort().tVehicle.lat*1e-7,link->getTDataPort().tVehicle.lng*1e-7);
            qDebug()<<coor;
            emit this->mapView->setCenterCoordinateSiganl(QVariant::fromValue<QGeoCoordinate>(coor));
        }
    }
}

void MainWindow::clearAirPathButtonPressedSlot()
{
    GIS_Models::positionModel->clearAirTrackPath(Qt::DMMM()->getMain_link_id());
}

void MainWindow::appendPointForMousePressedSlot(bool checked,int id)
{
    Q_UNUSED(id);
    if(this->mapView->getMapMode() != WidgetModel::RoutesPlanningModel && checked){
        this->setCursor(Qt::CrossCursor);
        this->mapView->setMapMode(WidgetModel::RoutesPlanningModel);
    }else{
        this->setCursor(Qt::ArrowCursor);
        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
}

void MainWindow::updateFor100HZTimerSlot()
{

    this->mapView->updateMapView();
}


void MainWindow::update_gis()
{
    QList<int>linkList = Qt::DMMM()->getLinksID();
    for(int i = 0;i < linkList.count();i++){
        Q_DMMM::DataPool_t data = Qt::DMMM()->getData(linkList.at(i));
        if( data.flylink.tVehicle.lat==0 && data.flylink.tVehicle.lng == 0 )return;
        float speed = 0.01f*sqrt(data.flylink.tVehicle.vel_cmps[0]*data.flylink.tVehicle.vel_cmps[0]+data.flylink.tVehicle.vel_cmps[1]*data.flylink.tVehicle.vel_cmps[1]);
        QString airmode = FlyLink::getFlightMode(data.flylink.VehicleType,data.flylink.tSysInfo.flight_mode);
        QString airState;
        if(data.flylink.tSysInfo.state1.state.armed && data.flylink.tSysInfo.state1.state.isflying){
            airState = QStringLiteral("飞行");
        }else if(data.flylink.tSysInfo.state1.state.armed && !data.flylink.tSysInfo.state1.state.isflying){
            airState= QStringLiteral("地面");
        }else{
            airState =(QStringLiteral("锁定"));
        }
        GIS_Models::positionModel->updateAirPosition(linkList.at(i),\
                                                     (double)data.flylink.tVehicle.lat*1e-7,\
                                                     (double)data.flylink.tVehicle.lng*1e-7,\
                                                     data.flylink.tVehicle.alt_m,\
                                                     data.flylink.tVehicle.yaw_cd*0.01f,\
                                                     data.flylink.tVehicle.pos_m[2],\
                                                     speed,\
                                                     data.flylink.tVehicle.airSpeed,\
                                                     airmode,\
                                                     airState,\
                                                     data.flylink.mav_id);

    }
}

void MainWindow::update_promptwidget()
{
    Q_DMMM * gcs = Qt::DMMM();
    QString str{};
    if(gcs != nullptr){
        Q_DMMM::DataPool_t data = gcs->getData_main();
        QString airmode = FlyLink::getFlightMode(data.flylink.VehicleType,data.flylink.tSysInfo.flight_mode);;
        QString airState;
        if(data.flylink.tSysInfo.state1.state.armed && data.flylink.tSysInfo.state1.state.isflying){
            airState = QStringLiteral("飞行");
        }else if(data.flylink.tSysInfo.state1.state.armed && !data.flylink.tSysInfo.state1.state.isflying){
            airState= QStringLiteral("地面");
        }else{
            airState =(QStringLiteral("锁定"));
        }
        str = airState+"-"+airmode;
    }
    else{
        str = QStringLiteral("未知模式");
    }

    this->promptWidget->addPromptMsgSlot(PromptWidgetModel::PromptMessageType::MsgCommondReply,str);


}

void MainWindow::newConnectGcsIDSlot(bool isopen, int id)
{
    if(isopen){
        GIS_Models::positionModel->addAirPositionData(id);
    }
}

void MainWindow::mousePressedForMapSlot(int type, QGeoCoordinate coor)
{
    if(type == WidgetModel::GetMapPositionModel ){
        this->setCursor(Qt::ArrowCursor);
        this->mapView->setMapMode(WidgetModel::NormolModel);
    }
}

void MainWindow::event_edit_guidedPointModelSlot(QGeoCoordinate coor)
{
    GIS_Models *models = new GIS_Models();
    if(models == nullptr){
        return;
    }
    models->getPointModel()->setData(models->getMapToolsModel()->index(0,0),QVariant(true),GIS_AirPointModel::DATA_PointIsShow);
    models->getPointModel()->setData(models->getMapToolsModel()->index(0,0),QVariant::fromValue<QGeoCoordinate>(coor),GIS_AirPointModel::DATA_PointCoor);
}



void MainWindow::req_gis_loc_Slot()
{
    if(this->mapView->getMapMode() != WidgetModel::GetMapPositionModel){
        this->setCursor(Qt::CrossCursor);
        this->mapView->setMapMode(WidgetModel::GetMapPositionModel);
    }
}

void MainWindow::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_new_textmsg:{
            int msgCount = Qt::DMMM()->msg_size();
            for(int i = 0;i < msgCount;i++){
                Q_DMMM::text_msg_t msg{};
                if(Qt::DMMM()->pop_msg(msg)){

                    /* 显示飞控编号 */
                    if(msg.id != -1){
                        FlyLink* fclink =Qt::DMMM()->getFlyLink(msg.id);
                        if(fclink){
                            msg.id = fclink->get_mav_id();
                        }
                    }
                    this->chatWidget->addNewPromptMessageSlot(msg.str,this->isMinimized(),msg.id);
                }
            }
        }break;

        case Q_DMMM::DMMM_GCSEvent_Origin_received:{
//            seekAirButtonPressedSlot();
//            perspectiveFollowButtonPresssedSlot(true);
        }break;
        case Q_DMMM::DMMM_GCSEvent_Home_FirstReceived:{
                seekAirButtonPressedSlot();
                clearAirPathButtonPressedSlot();

        }break;

        case Q_DMMM::DMMM_GCSEvent_MavIDChanged:{
                seekAirButtonPressedSlot();
                clearAirPathButtonPressedSlot();
        }break;


    case Q_DMMM::DMMM_GCSEvent_firstAvailiablePos:{
                seekAirButtonPressedSlot();
                clearAirPathButtonPressedSlot();
        }break;

    }
}

void MainWindow::promptWidgetLeftButtonPressedSlot()
{
    qDebug()<<"promptWidgetLeftButtonPressedSlot";

}

void MainWindow::promptWidgetRightButtonPressedSlot()
{
    if(this->chatWidget->isHidden()){
        this->chatWidget->setVisible(true);
    }else{
        this->chatWidget->setVisible(false);
    }
}

void MainWindow::updateHUDData()
{
    Q_DMMM::DataPool_t copter = Qt::DMMM()->getData_main();

    this->hudOpenGLView->updateHUDData( copter.flylink.tVehicle.pos_m[2],
                                        copter.flylink.tTarget.DesiredAlt_m,
                                        copter.flylink.tVehicle.roll_cd*0.01f,
                                        copter.flylink.tTarget.NavRoll_cd*0.01f,
                                        copter.flylink.tVehicle.yaw_cd*0.01f,
                                        copter.flylink.tTarget.NavYaw_cd*0.01f,
                                        copter.flylink.tVehicle.pitch_cd*0.01f,
                                        copter.flylink.tTarget.NavPitch_cd*0.01f,
                                        copter.flylink.tVehicle.vel_cmps[2]*0.01f,
            copter.flylink.tTarget.TargetVel_u_cmps*0.01f);
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()){
    case Qt::Key_Escape:
        if(this->mapView->getMapMode() != WidgetModel::NormolModel){
            this->setCursor(Qt::ArrowCursor);
            this->mapView->setMapMode(WidgetModel::NormolModel);
        }else{
            closeButtonPressedSlot();
        }
        break;
    default:
        return QWidget::keyPressEvent(e);
    }

}

