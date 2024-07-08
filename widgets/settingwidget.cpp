#include "settingwidget.h"

SettingWidget::SettingWidget()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    widgetInit();
    signalAndSlot();
}

void SettingWidget::widgetInit()
{
    if(this->titleWidget == nullptr){
        this->titleWidget = new SettingWidgetTitle(":/img/logo/LOGO_fontWhite.png",QStringLiteral("参数配置"));
    }
    if(this->infoWidget == nullptr){
        this->infoWidget = new SettingWidgetInfo();
    }
    if(this->statusWidget == nullptr){
        this->statusWidget = new SettingWidgetStatus();
    }
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QVBoxLayout();
    }

    this->widgetLayout->addWidget(this->titleWidget);
    this->widgetLayout->addWidget(this->infoWidget);
    this->widgetLayout->addWidget(this->statusWidget);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);
    this->setLayout(this->widgetLayout);

    this->resize(800,600);

}

void SettingWidget::signalAndSlot()
{
    connect(this->titleWidget,&SettingWidgetTitle::closeButtonClickedSignal,this,&SettingWidget::close);
    connect(this->titleWidget,&SettingWidgetTitle::minSizeButtonClickedSignal,this,&SettingWidget::hide);
}

void SettingWidget::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);
    this->setWindowModality(Qt::ApplicationModal);              /*当前窗口显示时阻塞其他所有窗口*/
}

void SettingWidget::mousePressEvent(QMouseEvent *event)//窗口移动事件
{


}
void SettingWidget::mouseMoveEvent(QMouseEvent *event)//窗口移动事件
{

}





SettingWidgetTitle::SettingWidgetTitle(QString text)
{
    widgetInit();
    this->titleNameLabel->setText(text);
    this->setObjectName("settingTitleWidget");
}

SettingWidgetTitle::SettingWidgetTitle(QString iconPath, QString text)
{
    widgetInit();
    this->titleNameLabel->setText(text);
    /*按比例缩放*/
    this->iconLabel->setPixmap(QPixmap(iconPath).scaled(this->iconLabel->width(),this->iconLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->setObjectName("settingTitleWidget");
}

void SettingWidgetTitle::widgetInit()
{
    if(this->quitButton == nullptr){
        this->quitButton = new QPushButton(QStringLiteral("X"));
        this->quitButton->setMaximumSize(30,30);
        this->quitButton->setMinimumSize(30,30);
        this->quitButton->setObjectName("TitleButton");
    }
    if(this->minSizeButton == nullptr){
        this->minSizeButton = new QPushButton("-");
        this->minSizeButton->setMaximumSize(30,30);
        this->minSizeButton->setMinimumSize(30,30);
        this->minSizeButton->setObjectName("TitleButton");
    }

    if(this->titleNameLabel == nullptr){
        this->titleNameLabel = new QLabel;
        this->titleNameLabel->setAlignment(Qt::AlignCenter);
        this->titleNameLabel->setObjectName("SettingNameLabel");
    }

    if(this->iconLabel == nullptr){
        this->iconLabel = new QLabel;
        this->iconLabel->setMaximumSize(28,28);
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QHBoxLayout;
    }
    if(this->btnLayout == nullptr){
        this->btnLayout = new QHBoxLayout;
    }

    this->btnLayout->addWidget(this->minSizeButton);
    this->btnLayout->addWidget(this->quitButton);
//    this->btnLayout->setMargin(0);
    this->btnLayout->setSpacing(0);
    this->btnLayout->setContentsMargins(5,0,0,15);

    this->widgetLayout->addWidget(this->iconLabel);
    this->widgetLayout->addItem(new QSpacerItem(10,40,QSizePolicy::Maximum,QSizePolicy::Minimum));
    this->widgetLayout->addWidget(this->titleNameLabel);
    this->widgetLayout->addItem(new QSpacerItem(10,40,QSizePolicy::Maximum,QSizePolicy::Minimum));
    this->widgetLayout->addItem(this->btnLayout);
    this->widgetLayout->setMargin(0);
    this->widgetLayout->setSpacing(0);
    this->setLayout(this->widgetLayout);

    connect(this->quitButton,&QPushButton::clicked,this,&SettingWidgetTitle::closeButtonClickedSignal);
    connect(this->minSizeButton,&QPushButton::clicked,this,&SettingWidgetTitle::minSizeButtonClickedSignal);

}

SettingWidgetInfo::SettingWidgetInfo()
{
    widgetInit();

    connect(this->tabBarWidget,&TabBarWidget::buttonClickedSignal,this->widgetStack,&SettingWidgetStack::stackWidgetSwitch);
}

void SettingWidgetInfo::widgetInit()
{
    if(this->widgetStack == nullptr){
        this->widgetStack = new SettingWidgetStack();
    }

    if(this->tabBarWidget == nullptr){
        this->tabBarWidget = new TabBarWidget;
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout;
    }

    this->widgetLayout->addWidget(this->tabBarWidget,0,0,5,2);
    this->widgetLayout->addWidget(this->widgetStack,0,2,5,8);
    this->widgetLayout->setMargin(0);
    this->widgetLayout->setSpacing(0);

    this->setLayout(this->widgetLayout);

}

SettingWidgetStack::SettingWidgetStack()
{
    widgetInit();
    this->setObjectName("SettingWidgetStack");

}

void SettingWidgetStack::widgetInit()
{
    widgetMap.clear();
    if(this->settingFCWidget == nullptr){
        this->settingFCWidget = new SettingWidgetFlightControl();
        widgetMap.insert(Setting_StackWidget::SW_FCWidget,this->settingFCWidget);
    }

    if(this->settingTTSWidget == nullptr){
        this->settingTTSWidget = new SettingWidgetTTS();
        widgetMap.insert(Setting_StackWidget::SW_TTSWidget,this->settingTTSWidget);
    }

    if(this->settignLoggerWidget == nullptr){
        this->settignLoggerWidget = new SettingWidgetLogger();
        widgetMap.insert(Setting_StackWidget::SW_LogWidget,this->settignLoggerWidget);
    }

    if(this->settingCommunWidget == nullptr){
        this->settingCommunWidget = new SettingWidgetCommun();
        widgetMap.insert(Setting_StackWidget::SW_ComWidget,this->settingCommunWidget);
    }

    this->addWidget(this->settingFCWidget);
    this->addWidget(this->settingTTSWidget);
    this->addWidget(this->settignLoggerWidget);
    this->addWidget(this->settingCommunWidget);

}

void SettingWidgetStack::stackWidgetSwitch(Setting_StackWidget sw)
{
    if(this->widgetMap.find(sw) != this->widgetMap.end()){
        this->setCurrentWidget(this->widgetMap.find(sw).value());
    }
}









TabBarWidget::TabBarWidget()
{
    widgetInit();

    connect(this->tabBarFCButton,&QPushButton::clicked,this,&TabBarWidget::tabBarFCButtonClickedSlot);
    connect(this->tabBarTTSButton,&QPushButton::clicked,this,&TabBarWidget::tabBarTTSButtonClickedSlot);
    connect(this->tabBarLogButton,&QPushButton::clicked,this,&TabBarWidget::tabBarLogButtonClickedSlot);
    connect(this->tabBarComButton,&QPushButton::clicked,this,&TabBarWidget::tabBarComButtonClickedSlot);
}

void TabBarWidget::widgetInit()
{
    if(this->tabBarFCButton == nullptr){
        this->tabBarFCButton = new QPushButton(QStringLiteral("飞行器设置"));
        this->tabBarFCButton->setObjectName("tabBarButton");
    }

    if(this->tabBarTTSButton == nullptr){
        this->tabBarTTSButton = new QPushButton(QStringLiteral("告警设置"));
        this->tabBarTTSButton->setObjectName("tabBarButton");
    }

    if(this->tabBarLogButton == nullptr){
        this->tabBarLogButton = new QPushButton(QStringLiteral("日志设置"));
        this->tabBarLogButton->setObjectName("tabBarButton");
    }

    if(this->tabBarComButton == nullptr){
        this->tabBarComButton = new QPushButton(QStringLiteral("链路设置"));
        this->tabBarComButton->setObjectName("tabBarButton");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QVBoxLayout();
    }

    this->widgetLayout->addWidget(this->tabBarFCButton);
    this->widgetLayout->addWidget(this->tabBarTTSButton);
    this->widgetLayout->addWidget(this->tabBarLogButton);
    this->widgetLayout->addWidget(this->tabBarComButton);
    this->widgetLayout->addItem(new QSpacerItem(20,this->height(),QSizePolicy::Minimum,QSizePolicy::Maximum));

    this->widgetLayout->setMargin(0);
    this->widgetLayout->setSpacing(0);
    this->setLayout(this->widgetLayout);

    this->setObjectName("TabBarWidget");
    this->setAttribute(Qt::WA_StyledBackground);

    this->setMinimumWidth(160);
}

void TabBarWidget::tabBarFCButtonClickedSlot()
{
    emit buttonClickedSignal(Setting_StackWidget::SW_FCWidget);
}

void TabBarWidget::tabBarTTSButtonClickedSlot()
{
    emit buttonClickedSignal(Setting_StackWidget::SW_TTSWidget);
}

void TabBarWidget::tabBarLogButtonClickedSlot()
{
    emit buttonClickedSignal(Setting_StackWidget::SW_LogWidget);
}

void TabBarWidget::tabBarComButtonClickedSlot()
{
    emit buttonClickedSignal(Setting_StackWidget::SW_ComWidget);
}


GroupCommbox::GroupCommbox(QString name)
{
    widgetInit();
    if(this->nameLabel != nullptr){
        this->nameLabel->setText(name);
    }
}

GroupCommbox::GroupCommbox(QString name, QStringList str)
{
    widgetInit();
    if(this->nameLabel != nullptr){
        this->nameLabel->setText(name);
    }

    if(this->combobox != nullptr){
        this->combobox->addItems(str);
    }
}

void GroupCommbox::setComboBoxVal(QStringList str)
{
    if(this->combobox != nullptr){
        this->combobox->addItems(str);
    }
}

void GroupCommbox::widgetInit()
{
    if(this->nameLabel == nullptr){
        this->nameLabel = new QLabel();
        this->nameLabel->setMaximumWidth(120);
        this->nameLabel->setMinimumWidth(120);
        this->nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        this->nameLabel->setObjectName("GroupCommboxLabel");
    }

    if(this->combobox == nullptr){
        this->combobox = new QComboBox;
        this->combobox->setMaximumWidth(120);
        this->combobox->setMinimumWidth(120);
        this->combobox->setObjectName("GroupCommbox");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QHBoxLayout;
    }

    this->widgetLayout->addWidget(nameLabel);
    this->widgetLayout->addWidget(combobox);
    this->widgetLayout->addItem(new QSpacerItem(2,2,QSizePolicy::Maximum,QSizePolicy::Maximum));
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);
    this->setLayout(this->widgetLayout);

    this->setObjectName("GroupCommboxWidget");
}




SettingWidgetFlightControl::SettingWidgetFlightControl()
{
    widgetInit();
}

void SettingWidgetFlightControl::widgetInit()
{

}



/*语音告警参数配置*/
SettingWidgetTTS::SettingWidgetTTS()
{
    widgetInit();
}

void SettingWidgetTTS::widgetInit()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("--------------------- 语音告警参数设置 ---------------------"));
        this->titleLabel->setAlignment(Qt::AlignCenter );
        this->titleLabel->setObjectName("SettingWidgetName");
        this->titleLabel->setMinimumHeight(40);
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QVBoxLayout;
    }

    this->widgetLayout->addWidget(this->titleLabel);

    this->widgetLayout->addItem(new QSpacerItem(20,this->height(),QSizePolicy::Minimum,QSizePolicy::Maximum));
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setContentsMargins(5,15,5,10);

    this->setLayout(this->widgetLayout);
}

SettingWidgetLogger::SettingWidgetLogger()
{
    widgetInit();
}

void SettingWidgetLogger::widgetInit()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("--------------------- 日志系统参数设置 ---------------------"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("SettingWidgetName");
        this->titleLabel->setMinimumHeight(40);
    }


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QVBoxLayout;
    }

    this->widgetLayout->addWidget(this->titleLabel);

    this->widgetLayout->addItem(new QSpacerItem(20,this->height(),QSizePolicy::Minimum,QSizePolicy::Maximum));
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setContentsMargins(5,15,5,10);

    this->setLayout(this->widgetLayout);
}




/*网络通讯参数配置界面*/
SettingWidgetCommun::SettingWidgetCommun()
{
    widgetInit();
}

void SettingWidgetCommun::widgetInit()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("--------------------- 网络通讯参数设置 ---------------------"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("SettingWidgetName");
        this->titleLabel->setMinimumHeight(40);
    }


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QVBoxLayout;
    }

    this->widgetLayout->addWidget(this->titleLabel);

    this->widgetLayout->addItem(new QSpacerItem(20,this->height(),QSizePolicy::Minimum,QSizePolicy::Maximum));
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setContentsMargins(5,15,5,10);

    this->setLayout(this->widgetLayout);
}





GroupEdit::GroupEdit(QString name, QValidator *validator)
{
    widgetInit();
    this->nameLabel->setText(name);
    if(validator != nullptr){
        this->valEdit->setValidator(validator);
    }
}

void GroupEdit::widgetInit()
{
    if(this->nameLabel == nullptr){
        this->nameLabel = new QLabel;
        this->nameLabel->setObjectName("GroupEditName");
    }
    if(this->valEdit == nullptr){
        this->valEdit = new QLineEdit;
        this->valEdit->setMinimumWidth(80);
        this->valEdit->setMaximumWidth(80);
        this->valEdit->setObjectName("GroupEditValue");
    }
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QHBoxLayout;
    }

    this->widgetLayout->addWidget(this->nameLabel);
    this->widgetLayout->addWidget(this->valEdit);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);
    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Maximum,QSizePolicy::Minimum));

    this->setLayout(this->widgetLayout);
    this->setObjectName("GroupEditWidget");
}

SettingWidgetStatus::SettingWidgetStatus()
{
    this->setObjectName("SettingWidgetStatus");
}
