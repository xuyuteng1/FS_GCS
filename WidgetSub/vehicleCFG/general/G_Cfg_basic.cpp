/**=================================================================**
 * @brief       : FixWing Basic Parameter Config Widget
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-10     Jerry.xl     the first version
 **==================================================================**/
#include "G_Cfg_basic.h"
#include "DMMM.h"
#include <qmath.h>

G_CFG_Basic::G_CFG_Basic(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("基础配置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void G_CFG_Basic::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_Basic::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{update_value(true);});
    connect(PB_upload   , &QPushButton::released,this,&G_CFG_Basic::Upload_Parameters);
}

void G_CFG_Basic::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("通用配置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }


    if( LOG_DISARMED == nullptr){
        LOG_DISARMED = new UCheckBox();
        LOG_DISARMED->setText(QStringLiteral("日志记录(仅飞行)"));
        LOG_DISARMED->setToolTip(QStringLiteral("关闭后，上电后将进行日志记录，开启后则在解锁后进行记录"));
    }

    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));

    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
        widgetLayout_pb->setObjectName(QString::fromUtf8("widgetLayout"));
        widgetLayout_pb->addStretch(5);
        widgetLayout_pb->addWidget(PB_download,1);
        widgetLayout_pb->addWidget(PB_upload,1);
        widgetLayout_pb->addStretch(5);
    }

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    QLabel* LB_info = new QLabel(QStringLiteral("勾选后仅在飞控解锁后记录数据，\r\n"
                                               "未勾选则上电初始化后进行记录。"));
    LB_info->setObjectName(QString::fromUtf8("infomationLabel"));

    /* widget title label */
    widgetLayout->addWidget(titleLabel,      0, 0, 1, 3);
    /* SpacerItem for automatic spacing adjustment */
    /* parachute parameters group */
    widgetLayout->addWidget(LB_info,1,0,1,3,Qt::AlignCenter);
    widgetLayout->addWidget(LOG_DISARMED,2,1,1,1,Qt::AlignCenter);

    widgetLayout->addLayout(widgetLayout_pb , 3, 0, 1, 3);
    /* general parameters setting  group */
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 0, 1,3);

    this->setLayout(widgetLayout);
}

void G_CFG_Basic::showEvent(QShowEvent *event)
{
    update_value();
    QWidget::showEvent(event);
}

void G_CFG_Basic::handle_DMMM_event(int ev, int linkid)
{
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_GetCommonParameter:
    {
        update_value();
    }break;
    case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
    case Q_DMMM::DMMM_GCSEvent_NewVehicleType:
    {
        update_value(true);
    }break;
        default:break;
    }
}

void G_CFG_Basic::update_value(bool getfromflight)
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        float val = 0;
        if(link->ParamGetValue_ByName("LOG_DISARMED",val,getfromflight)){
            int state = val;
            this->LOG_DISARMED->setNewChecked(!state?true:false);
        }
    }
}

void G_CFG_Basic::Upload_Parameters()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        if(this->LOG_DISARMED->IsChanged()){
            link->ParamSetToFlight_ByName("LOG_DISARMED",this->LOG_DISARMED->checkState()?0:1);
        }
    }
}
