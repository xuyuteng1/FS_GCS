#include "titlewidget.h"
#include "DMMM.h"
#include "ReleaseNotes.h"
TitleWidget::TitleWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void TitleWidget::widgetInit()
{
    if(this->logoLabel == nullptr){
        this->logoLabel = new QLabel(this);
        this->logoLabel->setObjectName("LogoLabel");
    }

    /*版本信息*/
    if(this->versionIconLabel == nullptr){
        this->versionIconLabel = new QLabel();
        this->versionIconLabel->setFixedSize(32,32);
        this->versionIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->versionIconLabel->setToolTip(QStringLiteral("版本信息"));
    }
    if(this->versionLabel == nullptr){
        this->versionLabel = new QLabel(QStringLiteral("N/A"));
        this->versionLabel->setObjectName("locationLng");
        this->versionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->versionLabel->setToolTip(QStringLiteral("通讯协议版本信息"));

    }
    if( this->firmwareversionLabel == nullptr){
        this->firmwareversionLabel = new QLabel(QStringLiteral("N/A"));
        this->firmwareversionLabel->setObjectName("locationLng");
        this->firmwareversionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->firmwareversionLabel->setToolTip(QStringLiteral("飞控固件版本信息"));

    }

    if(this->versionLayout == nullptr){
        this->versionLayout = new QGridLayout;
        this->versionLayout->addWidget(this->versionIconLabel,0,0,2,1);
        this->versionLayout->addWidget(this->versionLabel,1,1,1,1);
        this->versionLayout->addWidget(this->firmwareversionLabel,0,1,1,1);
        this->versionLayout->setSpacing(5);
        this->versionLayout->setContentsMargins(5,5,5,5);
    }

    if(this->nowAirIconLabel == nullptr){
        this->nowAirIconLabel = new QLabel();
        this->nowAirIconLabel->setFixedSize(32,32);
        this->nowAirIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->nowAirIconLabel->setToolTip(QStringLiteral("当前无人机ID"));
    }
    if(this->nowAirIDLabel == nullptr){
        this->nowAirIDLabel = new QLabel(QStringLiteral("未连接"));
        this->nowAirIDLabel->setObjectName("titleLabel");
        this->nowAirIDLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->nowAirIDLabel->setToolTip(QStringLiteral("当前无人机ID"));
    }

    if(this->nowAirIDLayout == nullptr){
        this->nowAirIDLayout = new QHBoxLayout;
        this->nowAirIDLayout->addWidget(this->nowAirIconLabel);
        this->nowAirIDLayout->addWidget(this->nowAirIDLabel);
        this->nowAirIDLayout->setSpacing(5);
        this->nowAirIDLayout->setContentsMargins(5,5,5,5);
    }

    /*经纬度信息*/
    if(this->locationIconLabel == nullptr){
        this->locationIconLabel = new QLabel();
        this->locationIconLabel->setFixedSize(32,32);
        this->locationIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->locationIconLabel->setToolTip(QStringLiteral("经纬度信息"));
    }



    if(this->locationLatLabel == nullptr){
        this->locationLatLabel = new QLabel(QStringLiteral("N/A"));
        this->locationLatLabel->setObjectName("locationLng");
        this->locationLatLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->locationLatLabel->setToolTip(QStringLiteral("纬度"));
    }
    if(this->locationLngLabel == nullptr){
        this->locationLngLabel = new QLabel(QStringLiteral("N/A"));
        this->locationLngLabel->setObjectName("locationLng");
        this->locationLngLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->locationLngLabel->setToolTip(QStringLiteral("经度"));
    }

    if(this->locationLayout == nullptr){
        this->locationLayout = new QGridLayout();
        this->locationLayout->addWidget(this->locationIconLabel,0,0,2,2);
        this->locationLayout->addWidget(this->locationLngLabel,0,2,1,3);
        this->locationLayout->addWidget(this->locationLatLabel,1,2,1,3);

        this->locationLayout->setSpacing(5);
        this->locationLayout->setContentsMargins(5,5,5,5);
    }


    /*海拔高度*/
    if(this->altitudeIconLabel == nullptr){
        this->altitudeIconLabel = new QLabel();
        this->altitudeIconLabel->setFixedSize(32,32);
        this->altitudeIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->altitudeIconLabel->setToolTip(QStringLiteral("海拔高度"));
    }
    if(this->altitudeLabel == nullptr){
        this->altitudeLabel = new QLabel(QStringLiteral("N/A 米"));
        this->altitudeLabel->setObjectName("titleLabel");
        this->altitudeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->altitudeLabel->setToolTip(QStringLiteral("海拔高度"));
    }
    if(this->altitudeLayout == nullptr){
        this->altitudeLayout = new QHBoxLayout;
        this->altitudeLayout->addWidget(this->altitudeIconLabel);
        this->altitudeLayout->addWidget(this->altitudeLabel);
        this->altitudeLayout->setSpacing(5);
        this->altitudeLayout->setContentsMargins(5,5,5,5);
    }


    /*卫星颗数*/
    if(this->sateNumIconLabel == nullptr){
        this->sateNumIconLabel = new QLabel();
        this->sateNumIconLabel->setFixedSize(32,32);
        this->sateNumIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->sateNumIconLabel->setToolTip(QStringLiteral("卫星颗数"));
    }
    if(this->sateNumLabel == nullptr){
        this->sateNumLabel = new QLabel(QStringLiteral("N/A 颗"));
        this->sateNumLabel->setObjectName("titleLabel");
        this->sateNumLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->sateNumLabel->setToolTip(QStringLiteral("卫星颗数"));
    }
    if(this->sateLayout == nullptr){
        this->sateLayout = new QHBoxLayout;
        this->sateLayout->addWidget(this->sateNumIconLabel);
        this->sateLayout->addWidget(this->sateNumLabel);
        this->sateLayout->setSpacing(5);
        this->sateLayout->setContentsMargins(5,5,5,5);
    }

    /*定位精度*/
    if(this->positionPerIconLabel == nullptr){
        this->positionPerIconLabel = new QLabel();
        this->positionPerIconLabel->setFixedSize(32,32);
        this->positionPerIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->positionPerIconLabel->setToolTip(QStringLiteral("定位精度"));
    }
    if(this->positionPerLabel == nullptr){
        this->positionPerLabel = new QLabel(QStringLiteral("N/A"));
        this->positionPerLabel->setObjectName("titleLabel");
        this->positionPerLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->positionPerLabel->setToolTip(QStringLiteral("定位精度"));
    }
    if(this->positionPerLayout == nullptr){
        this->positionPerLayout = new QHBoxLayout;
        this->positionPerLayout->addWidget(this->positionPerIconLabel);
        this->positionPerLayout->addWidget(this->positionPerLabel);
        this->positionPerLayout->setSpacing(5);
        this->positionPerLayout->setContentsMargins(5,5,5,5);
    }

    /*当前时间*/
    if(this->dateTimeIconLabel == nullptr){
        this->dateTimeIconLabel = new QLabel();
        this->dateTimeIconLabel->setFixedSize(32,32);
        this->dateTimeIconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->dateTimeIconLabel->setToolTip(QStringLiteral("当前时间"));
    }
    if(this->dateTimeLabel == nullptr){
        this->dateTimeLabel = new QLabel(QStringLiteral("2022-05-15\r\n 15:33:13"));
        this->dateTimeLabel->setObjectName("dateTimeLabel");
        this->dateTimeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->dateTimeLabel->setToolTip(QStringLiteral("当前时间"));
    }
    if(this->dateTimeLayout == nullptr){
        this->dateTimeLayout = new QHBoxLayout;
        this->dateTimeLayout->addWidget(this->dateTimeIconLabel);
        this->dateTimeLayout->addWidget(this->dateTimeLabel);
        this->dateTimeLayout->setSpacing(5);
        this->dateTimeLayout->setContentsMargins(5,5,5,5);
    }
    if( this->lb_GCS_Version == nullptr){
        this->lb_GCS_Version = new QLabel(GCS_Version);
        this->lb_GCS_Version->setObjectName("titleLabel");
        this->lb_GCS_Version->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->lb_GCS_Version->setToolTip(QStringLiteral("地面站版本"));
    }
    if( this->lb_GCS_Version_Icon == nullptr){
        this->lb_GCS_Version_Icon = new QLabel();
        this->lb_GCS_Version_Icon->setFixedSize(28,28);
        this->lb_GCS_Version_Icon->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->lb_GCS_Version_Icon->setToolTip(QStringLiteral("地面站版本"));
        QPixmap pix(":/img/Version.png");
        pix = pix.scaledToHeight(this->lb_GCS_Version_Icon->height(),Qt::SmoothTransformation );
        this->lb_GCS_Version_Icon->setPixmap(pix);
    }

    if( this->HLayout_GCS_Version == nullptr){
        this->HLayout_GCS_Version = new QHBoxLayout;
        this->HLayout_GCS_Version->addWidget(this->lb_GCS_Version_Icon);
        this->HLayout_GCS_Version->addWidget(this->lb_GCS_Version);
        this->HLayout_GCS_Version->setSpacing(5);
        this->HLayout_GCS_Version->setContentsMargins(5,5,5,5);
    }


    /*按键*/
    if(this->connectionButton == nullptr){
        this->connectionButton = new QPushButton(QStringLiteral("未连接"));
        this->connectionButton->setObjectName("connectionButton");
    }
    if(this->closeButton == nullptr){
        this->closeButton = new QPushButton();
        this->closeButton->setIcon(QIcon(":/img/png/closeButton.png"));
        this->closeButton->setObjectName("closeButton");
    }

    if(this->minimizeButton == nullptr){
        this->minimizeButton = new QPushButton();
        this->minimizeButton->setIcon(QIcon(":/img/png/miniButton.png"));
        this->minimizeButton->setObjectName("minimizeButton");
    }

    selectButtonInit();


    if(this->buttonGroupLayout == nullptr){
        this->buttonGroupLayout = new QHBoxLayout;
        this->buttonGroupLayout->setMargin(0);
        this->buttonGroupLayout->setSpacing(0);
    }

    this->buttonGroupLayout->addWidget(this->connectionButton);
//    this->buttonGroupLayout->addWidget(this->selectButton);
    this->buttonGroupLayout->addWidget(this->minimizeButton);
    this->buttonGroupLayout->addWidget(this->closeButton);

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
        this->widgetLayout->setMargin(0);
        this->widgetLayout->setSpacing(15);
    }

    this->widgetLayout->addWidget(this->selectButton,0,0,1,1);
    this->widgetLayout->addWidget(this->logoLabel,0,1,1,1);
    this->widgetLayout->addItem(this->HLayout_GCS_Version,0,2,1,1);
    this->widgetLayout->addItem(this->versionLayout,0,3,1,1);
    this->widgetLayout->addItem(this->nowAirIDLayout,0,4,1,1);
    this->widgetLayout->addItem(this->locationLayout,0,5,1,1);
    this->widgetLayout->addItem(this->altitudeLayout,0,6,1,1);
    this->widgetLayout->addItem(this->sateLayout,0,7,1,1);
    this->widgetLayout->addItem(this->positionPerLayout,0,8,1,1);
    this->widgetLayout->addItem(this->dateTimeLayout,0,9,1,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::MinimumExpanding,QSizePolicy::Minimum),0,9,1,17);
    this->widgetLayout->addItem(this->buttonGroupLayout,0,27,1,1);

    if(WidgetSIMCfg == nullptr){
        WidgetSIMCfg = new SIM_CFG();
    }

    this->setLayout(this->widgetLayout);

    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setObjectName("TitleWidget");
}

void TitleWidget::selectButtonInit()
{
    // 主菜单
    if(this->selectMenu == nullptr){
        this->selectMenu = new QMenu(this);
        this->selectMenu->setObjectName("selectButtonMenu");
    }

    // 1级菜单
    if( this->GCSMenu == nullptr){
        this->GCSMenu = new QMenu(this);
        this->GCSMenu->setObjectName("selectButtonMenu");
    }

    if( this->CommonCfgMenu == nullptr){
        this->CommonCfgMenu = new QMenu(this);
        this->CommonCfgMenu->setObjectName("selectButtonMenu");
    }
    if( this->GeneralCfgMenu == nullptr){
        this->GeneralCfgMenu = new QMenu(this);
        this->GeneralCfgMenu->setObjectName("selectButtonMenu");
    }

    if( this->CopterCfgMenu == nullptr){
        this->CopterCfgMenu = new QMenu(this);
        this->CopterCfgMenu->setObjectName("selectButtonMenu");
    }

    if( this->PlaneCfgMenu == nullptr){
        this->PlaneCfgMenu = new QMenu(this);
        this->PlaneCfgMenu->setObjectName("selectButtonMenu");
    }

    //----------------------Main ACTION 1级Action------------------------

    if( this->GCSCFGAction == nullptr){
        this->GCSCFGAction = new QAction(QIcon(":/img/png/gcs.png"),QStringLiteral("地面站配置"),this->selectMenu);
        this->selectMenu->addAction(this->GCSCFGAction);
        this->GCSCFGAction->setMenu(this->GCSMenu);
    }
    this->selectMenu->addSeparator();
    if( this->CommonCfgAction == nullptr){
        this->CommonCfgAction = new QAction(QIcon(":/img/png/tools.png"),QStringLiteral("通用工具"),this->selectMenu);
        this->selectMenu->addAction(this->CommonCfgAction);
        this->CommonCfgAction->setMenu(this->CommonCfgMenu);
    }
    this->selectMenu->addSeparator();
    if(this->GeneralCfgAction == nullptr){
        this->GeneralCfgAction = new QAction(QIcon(":/img/png/comcfg.png"),QStringLiteral("通用配置"));
        this->selectMenu->addAction(this->GeneralCfgAction);
    }
    this->selectMenu->addSeparator();
    if( this->CopterCfgAction == nullptr){
        this->CopterCfgAction = new QAction(QIcon(":/img/png/coptercfg.png"),QStringLiteral("多旋翼配置"),this->selectMenu);
        this->selectMenu->addAction(this->CopterCfgAction);
        this->CopterCfgAction->setMenu(this->CopterCfgMenu);
    }
    this->selectMenu->addSeparator();
    if( this->PlaneCfgAction == nullptr){
        this->PlaneCfgAction = new QAction(QIcon(":/img/png/planecfg.png"),QStringLiteral("固定翼配置"),this->selectMenu);
        this->selectMenu->addAction(this->PlaneCfgAction);
        this->PlaneCfgAction->setMenu(this->PlaneCfgMenu);
    }
    this->selectMenu->addSeparator();
    if(this->FCBoardInfo == nullptr){
        this->FCBoardInfo = new QAction(QIcon(":/img/png/boardinfo.png"),QStringLiteral("硬件信息"));
        this->selectMenu->addAction(this->FCBoardInfo);
    }
    this->selectMenu->addSeparator();
    if(this->SIMCFGAction == nullptr){
        this->SIMCFGAction = new QAction(QIcon(":/img/png/SIMCFG.png"),QStringLiteral("仿真配置"));
        this->selectMenu->addAction(this->SIMCFGAction);
    }

#ifdef GCS_DEBUG_ENABLE
    this->selectMenu->addSeparator();
    if(this->FunDebugPort == nullptr){
        this->FunDebugPort = new QAction(QIcon(":/img/png/dbg_cfg.png"),QStringLiteral("调试界面"));
        this->selectMenu->addAction(this->FunDebugPort);
    }
#endif
    //---------------------- 2级ACTION ------------------------

    // 地面站配置项
    if(this->systemConfigAction == nullptr){
        this->systemConfigAction = new QAction(QStringLiteral("地面功能配置"),this->GCSMenu);
        this->GCSMenu->addAction(this->systemConfigAction);
    }

    if(this->communicationConfigAction == nullptr){
        this->communicationConfigAction = new QAction(QStringLiteral("通讯接口配置"),this->GCSMenu);
        this->GCSMenu->addAction(this->communicationConfigAction);
    }
    if(this->pluginManagerAction == nullptr){
        this->pluginManagerAction = new QAction(QStringLiteral("插件管理模块"),this->GCSMenu);
        this->GCSMenu->addAction(this->pluginManagerAction);
    }

    // 通用工具
    if(this->loggerManagerAction == nullptr){
        this->loggerManagerAction = new QAction(QStringLiteral("机载日志"),this->GCSMenu);
        this->CommonCfgMenu->addAction(this->loggerManagerAction);
    }
    if(this->realTimeDataAction == nullptr){
        this->realTimeDataAction = new QAction(QStringLiteral("波形显示"));
        this->CommonCfgMenu->addAction(this->realTimeDataAction);
    }
    if(this->panelDataAction == nullptr){
        this->panelDataAction = new QAction(QStringLiteral("信息面板"));
        this->CommonCfgMenu->addAction(this->panelDataAction);
    }

    // 多旋翼配置
    if(this->basicConfigAction == nullptr){
        this->basicConfigAction = new QAction(QStringLiteral("基础参数"));
        this->CopterCfgMenu->addAction(this->basicConfigAction);
    }


    if(this->parameterConfigAciton == nullptr){
        this->parameterConfigAciton = new QAction(QStringLiteral("控制参数"));
        this->CopterCfgMenu->addAction(this->parameterConfigAciton);
    }

    if(this->selectButton == nullptr){
        this->selectButton = new QToolButton();
        this->selectButton->setIcon(QIcon(":/img/png/settingButton.png"));
        this->selectButton->setObjectName("selectButton");
        this->selectButton->setMenu(this->selectMenu);
        this->selectButton->setPopupMode(QToolButton::MenuButtonPopup);
    }
    /* FixWing Config */
    if(this->Action_PlaneParamCFG == nullptr){
        this->Action_PlaneParamCFG = new QAction(QStringLiteral("参数配置"));
        this->PlaneCfgMenu->addAction(this->Action_PlaneParamCFG);
    }
}

void TitleWidget::connectSignalAndSlot()
{
    connect(this->closeButton,&QPushButton::pressed,this,&TitleWidget::closeButtonPressedSignal);
    connect(this->minimizeButton,&QPushButton::pressed,this,&TitleWidget::minimizeButtonPressedSignal);
    connect(this->selectButton,&QPushButton::pressed,this,[=]{this->selectMenu->show();});
    connect(this->connectionButton,&QPushButton::pressed,this,&TitleWidget::connectionButtonPressedSignal);

    connect(this->basicConfigAction,&QAction::triggered,this,&TitleWidget::basicConfigActionTriggeredSignal);
    connect(this->systemConfigAction,&QAction::triggered,this,&TitleWidget::systemConfigActionTriggeredSignal);
    connect(this->parameterConfigAciton,&QAction::triggered,this,&TitleWidget::parameterConfigAcitonTriggeredSignal);
    connect(this->communicationConfigAction,&QAction::triggered,this,&TitleWidget::communicationConfigActionTriggeredSignal);
    connect(this->loggerManagerAction,&QAction::triggered,this,&TitleWidget::loggerManagerActionTriggeredSignal);
    connect(this->realTimeDataAction,&QAction::triggered,this,&TitleWidget::realTimeDataActionTriggeredSignal);
    connect(this->panelDataAction,&QAction::triggered,this,&TitleWidget::panelDataActionTriggeredSignal);
    connect(this->pluginManagerAction,&QAction::triggered,this,&TitleWidget::pluginManagerActionTriggeredSignal);
    connect(this->FCBoardInfo,&QAction::triggered,this,&TitleWidget::FCBoardInfoActionTriggeredSignal);
    connect(this->SIMCFGAction,&QAction::triggered,this,&TitleWidget::handle_SIMCfgAction);

    /* FixWing Config Action Signals <--> Slots*/
    connect(this->Action_PlaneParamCFG,&QAction::triggered,this,&TitleWidget::handle_Action_PlaneParamCFG);
    connect(this->GeneralCfgAction,&QAction::triggered,this,&TitleWidget::handle_Action_GeneralCfg);


#ifdef GCS_DEBUG_ENABLE
    connect(this->FunDebugPort,&QAction::triggered,this,&TitleWidget::FundbgPortActionTriggeredSignal);
#endif
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&TitleWidget::handle_DMMM_event);
}

void TitleWidget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    this->setFixedHeight(48);


    /*titleWidget大小改变时重绘图片*/
    if(this->logoLabel != nullptr){
        this->logoLabel->setMinimumHeight(this->height() - 10);
        this->logoLabel->setMaximumHeight(this->height() - 2);
#if CUSTOMER_NAME==CUSTOMER_KEYWAY
        this->logoLabel->setMaximumWidth(this->height()*5);
        this->logoLabel->setMinimumWidth(this->height()*3);
        QPixmap pix(":/img/logo/LOGO_fontWhite.png");
#elif CUSTOMER_NAME == CUSTOMER_NUAA
        QPixmap pix(":/img/logo/NUAA.png");
#elif CUSTOMER_NAME == CUSTOMER_CHENGGONG
        QPixmap pix(":/img/logo/chenggong.png");

#else
        QPixmap pix(":/img/logo/logo_fly.png");
#endif
        pix = pix.scaledToHeight(this->logoLabel->height()-5,Qt::SmoothTransformation);
        this->logoLabel->setPixmap(pix);
    }

    if(this->versionIconLabel != nullptr){
        QPixmap pix(":/img/icon/versionIcon.png");
        pix = pix.scaledToHeight(this->versionIconLabel->height(),Qt::SmoothTransformation );
        this->versionIconLabel->setPixmap(pix);
    }

    if(this->nowAirIconLabel != nullptr){
        QPixmap pix(AirIconType);

        pix = pix.scaledToHeight(this->nowAirIconLabel->height(),Qt::SmoothTransformation );
        this->nowAirIconLabel->setPixmap(pix);
    }


    if(this->locationIconLabel != nullptr){
        QPixmap pix(":/img/icon/locationIcon.png");

        pix = pix.scaledToHeight(this->locationIconLabel->height(),Qt::SmoothTransformation );
        this->locationIconLabel->setPixmap(pix);
    }

    if(this->altitudeIconLabel != nullptr){
        QPixmap pix(":/img/icon/aktitudeIco.png");

        pix = pix.scaledToHeight(this->altitudeIconLabel->height(),Qt::SmoothTransformation );
        this->altitudeIconLabel->setPixmap(pix);
    }

    if(this->sateNumIconLabel != nullptr){
        QPixmap pix(":/img/icon/sateIcon.png");

        pix = pix.scaledToHeight(this->sateNumIconLabel->height(),Qt::SmoothTransformation );
        this->sateNumIconLabel->setPixmap(pix);
    }

    if(this->positionPerIconLabel != nullptr){
        QPixmap pix(":/img/icon/positionPerIcon.png");

        pix = pix.scaledToHeight(this->positionPerIconLabel->height(),Qt::SmoothTransformation );
        this->positionPerIconLabel->setPixmap(pix);
    }

    if(this->dateTimeIconLabel != nullptr){
        QPixmap pix(":/img/icon/dateTimeIcon.png");

        pix = pix.scaledToHeight(this->dateTimeIconLabel->height(),Qt::SmoothTransformation );
        this->dateTimeIconLabel->setPixmap(pix);
    }

    if(this->logoLabel != nullptr){
        this->connectionButton->setFixedHeight(this->logoLabel->height());
        this->closeButton->setFixedSize(QSize(this->logoLabel->height(),this->logoLabel->height()));
        this->minimizeButton->setFixedSize(QSize(this->logoLabel->height(),this->logoLabel->height()));
        this->selectButton->setFixedSize(QSize(this->logoLabel->height(),this->logoLabel->height()));

        this->closeButton->setIconSize(0.6*this->closeButton->size());
        this->minimizeButton->setIconSize(0.6*this->closeButton->size());
        this->selectButton->setIconSize(0.6*this->closeButton->size());
    }
}

void TitleWidget::setCommuncationStr(const QString &newCommuncationStr)
{
    if(this->communcationStr.compare(newCommuncationStr) != 0){
        this->communcationStr = newCommuncationStr;
        this->connectionButton->setText(this->communcationStr);
    }
}

void TitleWidget::setDateTime(const QDateTime &newDateTime)
{
    if(this->dateTime != newDateTime){
        this->dateTime = newDateTime;
        this->dateTimeLabel->setText(this->dateTime.toString("yyyy-MM-dd\r\nhh:mm:ss"));
    }
}

void TitleWidget::setPositionPerStr(float newPositionPerStr)
{
    if(this->positionPerStr != newPositionPerStr){
        this->positionPerStr = newPositionPerStr;
        this->positionPerLabel->setText(QString::number(newPositionPerStr,'f',2));
    }
}

void TitleWidget::setSateNumStr(int newSateNumStr)
{
    if(this->sateNumStr != newSateNumStr){
        this->sateNumStr = newSateNumStr;
        this->sateNumLabel->setText(QString::number(this->sateNumStr,10) + QStringLiteral("颗"));
    }
}

void TitleWidget::setAlititudeVal(float newAlititudeVal)
{
    if(this->alititudeVal != newAlititudeVal){
        this->alititudeVal = newAlititudeVal;
        this->altitudeLabel->setText(QString::number(this->alititudeVal,'f',2) + QStringLiteral("米"));
    }
}

void TitleWidget::setLatVal(double newLatVal)
{
    if(this->latVal != newLatVal){
        this->latVal = newLatVal;
        this->locationLatLabel->setText(QString::number(this->latVal,'f',7));
    }
}

void TitleWidget::setLngVal(double newLngVal)
{
    if(this->lngVal != newLngVal){
        this->lngVal = newLngVal;
        this->locationLngLabel->setText(QString::number(this->lngVal,'f',7));
    }
}


void TitleWidget::setAirIDStr(const QString &newAirIDStr)
{
    if(this->airIDStr.compare(newAirIDStr) != 0){
        this->airIDStr = newAirIDStr;
        this->nowAirIDLabel->setText(this->airIDStr);
    }
}

void TitleWidget::setVersionStr(const QString &newVersionStr)
{
    if(this->versionStr.compare(newVersionStr) != 0){
        this->versionStr = newVersionStr;
        this->versionLabel->setText(this->versionStr);
    }
}

void TitleWidget::setfirmwareversionStr(const QString &newVersionStr)
{
    if(this->firmwareversionStr.compare(newVersionStr) != 0){
        this->firmwareversionStr = newVersionStr;
        this->firmwareversionLabel->setText(this->firmwareversionStr);
    }
}


void TitleWidget::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
        {
            updatestate();
        }break;

    default:break;
    }
}

void TitleWidget::handle_SIMCfgAction()
{
    if(WidgetSIMCfg == nullptr){
        WidgetSIMCfg = new SIM_CFG();
    }
    WidgetSIMCfg->showNormal();
//    WidgetSIMCfg->update_value(true);
}

void TitleWidget::handle_Action_PlaneParamCFG()
{
    if(widget_PlaneCFG == nullptr){
        widget_PlaneCFG = new PlaneConfigWidget();
    }
    widget_PlaneCFG->showNormal();
}

void TitleWidget::handle_Action_GeneralCfg()
{
    if(widget_GeneralCFG == nullptr){
        widget_GeneralCFG = new WidgetGeneralConfig();
    }
    widget_GeneralCFG->showNormal();
}

void TitleWidget::updatestate()
{
    this->setDateTime(QDateTime::currentDateTime());
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        uint16_t ver = link->getTDataPort().mav_version;
        this->setVersionStr(QString().asprintf("LK%d.%d.%d",0xf&(ver>>12),0xf&(ver>>8),0xf&(ver>>4))+FlyLink::getProtocolType(0xf&ver));

        uint32_t FW_ver = link->getTDataPort().boardinfo.fw_version;
        this->setfirmwareversionStr(QString().asprintf("V%d.%d.%d.%d",0xff&(FW_ver>>24),0xff&(FW_ver>>16),0xff&(FW_ver>>8),0xff&FW_ver));

        this->setAirIDStr(QStringLiteral("ID-")+QString::number(link->get_mav_id()));

        this->setLngVal(static_cast<double>(link->getTDataPort().tVehicle.lng)/1e7);

        this->setLatVal(static_cast<double>(link->getTDataPort().tVehicle.lat)/1e7);

        this->setAlititudeVal(link->getTDataPort().tVehicle.alt_m);

        this->setSateNumStr(link->getTDataPort().tGNSS->num_sats);

        this->setPositionPerStr(link->getTDataPort().tGNSS->hdop_cm*0.01f);

        if(link->getIs_active()){
            this->setCommuncationStr(QStringLiteral("已连接"));
        }
        else{
            this->setCommuncationStr(QStringLiteral("已断开"));
        }
        uint8_t Vtype = link->getVehicleType();
        if( Vtype!= vehicletype){
            vehicletype = Vtype;
            switch (vehicletype) {
            case FlyLink::VehicleType_e::VehicleType_Copter:
                AirIconType = ":/img/icon/AirBlack.png";
                break;
            case FlyLink::VehicleType_e::VehicleType_Plane:
                AirIconType = ":/img/png/planecfg.png";
                break;
            default:
                AirIconType = ":/img/icon/AirBlack.png";
                break;
            }
            if(this->nowAirIconLabel != nullptr){
                QPixmap pix(AirIconType);
                pix = pix.scaledToHeight(this->nowAirIconLabel->height(),Qt::SmoothTransformation );
                this->nowAirIconLabel->setPixmap(pix);
            }
        }

    }
    else{
        this->setCommuncationStr(QStringLiteral("未连接"));
    }
}
