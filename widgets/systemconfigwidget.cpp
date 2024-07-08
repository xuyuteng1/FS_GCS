#include "systemconfigwidget.h"
#include "qdebug.h"


SystemConfigWidget::SystemConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    this->configWidgetMap.clear();
    this->actionWidgetMap.clear();
    widgetInit();
    connectSignalAndSlot();
    this->setAttribute(Qt::WA_StyledBackground,false);
    this->setWindowTitle(QStringLiteral("基础配置"));
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);

    if(CFGwidget_Frame == nullptr){
        CFGwidget_Frame = new CFG_CopterFrame();
        addNewConfigWidget(QStringLiteral("构型配置"),CFGwidget_Frame->getWidgetLayout());
    }


    if(CFGwidget_MotorTest == nullptr){
        CFGwidget_MotorTest = new CFG_MotorTest();
        addNewConfigWidget(QStringLiteral("电机测试"),CFGwidget_MotorTest->getWidgetLayout());
    }

    if(CFGwidget_ESCCali == nullptr){
        CFGwidget_ESCCali = new CFG_ESCCalibration();
        addNewConfigWidget(QStringLiteral("电调校准"),CFGwidget_ESCCali->getWidgetLayout());
    }

    if(CFGwidget_ParamMotors == nullptr){
        CFGwidget_ParamMotors = new CFG_ParamMotors();
        addNewConfigWidget(QStringLiteral("电机参数"),CFGwidget_ParamMotors->getWidgetLayout());
    }




}

SystemConfigWidget::~SystemConfigWidget()
{

    this->configWidgetMap.clear();
    this->actionWidgetMap.clear();
}

void SystemConfigWidget::addNewConfigWidget(QString name, QGridLayout *layout)
{
    if(this->configWidgetMap.find(name) == this->configWidgetMap.end()){

        // action list
        QListWidgetItem *itemAction = new QListWidgetItem(name);
        this->actionWidget->addItem(itemAction);
        if(itemAction != nullptr){
            itemAction->setTextAlignment(Qt::AlignCenter);
            if(actionWidgetMap.find(name) == this->actionWidgetMap.end()){
                this->actionWidgetMap.insert(name,itemAction);
            }
        }


        // configure list
        QListWidgetItem *item = new QListWidgetItem();
        QGroupBox *box = new QGroupBox(name);
        box->setObjectName("SystemInfoWidgetGroupBox");
        box->setLayout(layout);
        item->setSizeHint(box->minimumSizeHint());

        this->configWidget->addItem(item);
        item->setSizeHint(box->sizeHint());
        this->configWidget->setItemWidget(item,box);
        this->configWidgetMap.insert(name,item);
    }
}

void SystemConfigWidget::widgetInit()
{
    if(this->configWidgetLayout == nullptr){
        this->configWidgetLayout = new QGridLayout();
    }
    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }

    if(this->actionWidget == nullptr){
        this->actionWidget = new QListWidget();
        this->actionWidget->setMaximumWidth(200);
        this->actionWidget->setObjectName("actionWidget");
    }
    if(this->configWidget == nullptr){
        this->configWidget = new QListWidget();
        this->configWidget->setObjectName("configWidget");
        this->configWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        QScroller::grabGesture(this->configWidget,QScroller::LeftMouseButtonGesture);
        this->configWidget->verticalScrollBar()->setSingleStep(8);

    }

    this->configWidgetLayout->addWidget(this->actionWidget,0,0,10,2);
    this->configWidgetLayout->addWidget(this->configWidget,0,2,10,20);
    this->configWidget->verticalScrollBar()->setVisible(false);


    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("基础参数配置"));
        w_title->setMaximumHeight(40);
    }
//    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->configWidgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);

//    QFile file(QString(":/style/system_cfg.qss"));
//    if(file.open(QIODevice::ReadOnly)){
//        this->setStyleSheet(file.readAll());
//        file.close();
//    }

    this->setObjectName("systemWidget");
//    this->setFixedSize(1300,750);
    this->setMinimumSize(1200,750);
}

void SystemConfigWidget::connectSignalAndSlot()
{
    connect(this->actionWidget,&QListWidget::currentTextChanged,this,&SystemConfigWidget::actionWidgetItemPressedSlot);
    connect(this->configWidget,&QListWidget::currentTextChanged,this,&SystemConfigWidget::configWidgetItemPressedSlot);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
}

void SystemConfigWidget::actionWidgetItemPressedSlot(QString text)
{

    if(this->configWidgetMap.find(text) != this->configWidgetMap.end()){
        QListWidgetItem * item = this->configWidgetMap.find(text).value();
        if(item != nullptr){
            qDebug()<<text;
            item->setSelected(true);
            this->configWidget->scrollToItem(item,QListWidget::PositionAtTop);
        }

    }

}

void SystemConfigWidget::configWidgetItemPressedSlot(QString text)
{
    if(this->actionWidgetMap.find(text) != this->actionWidgetMap.end()){
        QListWidgetItem * item = this->actionWidgetMap.find(text).value();
        if(item != nullptr){
            item->setSelected(true);
        }
    }
}

ConfigTestLayout::ConfigTestLayout()
{
    configTestLayoutInit();
}

QGridLayout *ConfigTestLayout::getWidgetLayout() const
{
    return widgetLayout;
}

void ConfigTestLayout::configTestLayoutInit()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addWidget(new QComboBox());

}

void QComboBox::wheelEvent(QWheelEvent *e)
{
}

void QAbstractSpinBox::wheelEvent(QWheelEvent *e)
{
}
