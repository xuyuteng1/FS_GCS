#include "G_cfg_acc_cali.h"
#include "DMMM.h"
#include <qmath.h>

G_CFG_AccCali::G_CFG_AccCali(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("加计校准"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

QGridLayout *G_CFG_AccCali::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_AccCali::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_AccCali::handle_DMMM_event);
    connect(PB_3DCaliStart,&QPushButton::released,this,&G_CFG_AccCali::start_or_continue_acc_cali);
    connect(PB_3DCaliCancel,&QPushButton::released,this,&G_CFG_AccCali::cancel_acc_cali);
    connect(PB_SimpleCaliStart,&QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_AccSimpleCaliStart();}});
}

void G_CFG_AccCali::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
    }
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("加计标准"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    if(LB_CaliState == nullptr){
        LB_CaliState = new QLabel(QStringLiteral("等待开始"));
        LB_CaliState->setObjectName(QString::fromUtf8("widgetNameLabel"));
    }
    if(LB_3DCaliInfo == nullptr){
        LB_3DCaliInfo = new QLabel(QStringLiteral("       加速度计3D校准时,请按照下方提示放置\r\n"
                                                  "飞行器,请确保飞行器稳定后点击操作按钮。"));
        LB_3DCaliInfo->setObjectName(QString::fromUtf8("infomationLabel"));


    }

    if(PB_3DCaliStart == nullptr){
        PB_3DCaliStart = new QPushButton(QStringLiteral("3D校准"));
        PB_3DCaliStart->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_3DCaliCancel == nullptr){
        PB_3DCaliCancel = new QPushButton(QStringLiteral("停止校准"));
        PB_3DCaliCancel->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(LB_SimpleCaliInfo == nullptr){
        LB_SimpleCaliInfo = new QLabel(QStringLiteral("       加计基础校准,将飞行器放置水平,\r\n"
                                                      "待飞行器稳定后执行校准。"));
        LB_SimpleCaliInfo->setObjectName(QString::fromUtf8("infomationLabel"));
    }

    if(PB_SimpleCaliStart == nullptr){
        PB_SimpleCaliStart = new QPushButton(QStringLiteral("基础校准"));
        PB_SimpleCaliStart->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(Group_3DCali == nullptr){
        Group_3DCali = new QGroupBox(QStringLiteral("3D校准"));
        Group_3DCali->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_3DCali->setAlignment(Qt::AlignCenter);
    }
    if(Layout3DCali == nullptr){
        Layout3DCali = new QGridLayout(Group_3DCali);
    }

    if(Group_SimpleCali == nullptr){
        Group_SimpleCali = new QGroupBox(QStringLiteral("基础校准"));
        Group_SimpleCali->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_SimpleCali->setAlignment(Qt::AlignCenter);
    }
    if(LayoutSimpleCali == nullptr){
        LayoutSimpleCali = new QGridLayout(Group_SimpleCali);
    }

    Layout3DCali->addWidget( LB_3DCaliInfo,0,0,1,20,Qt::AlignCenter);
    Layout3DCali->addWidget( LB_CaliState,1,0,1,20,Qt::AlignCenter);
    Layout3DCali->addWidget( PB_3DCaliStart,2,9,1,1,Qt::AlignCenter);
    Layout3DCali->addWidget( PB_3DCaliCancel,2,10,1,1,Qt::AlignCenter);

    LayoutSimpleCali->addWidget( LB_SimpleCaliInfo,0,0,2,20,Qt::AlignCenter);
    LayoutSimpleCali->addWidget( PB_SimpleCaliStart,2,9,1,2,Qt::AlignCenter);

    widgetLayout->addWidget(titleLabel,0,0,1,4);
//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 1);
    widgetLayout->addWidget(Group_3DCali,2,1,1,1);
    widgetLayout->addWidget(Group_SimpleCali,2,2,1,1);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 3, 3, 1, 1);
    this->Layout3DCali->setRowMinimumHeight(0,100);
    this->Layout3DCali->setRowMinimumHeight(1,25);
    this->Layout3DCali->setRowMinimumHeight(2,30);

    this->widgetLayout->setContentsMargins(10,20,10,20);
    this->setLayout(widgetLayout);
}

void G_CFG_AccCali::update_cali_position(uint8_t pos,bool forceupdate)
{
    if(caliposition == pos && !forceupdate){
        return;
    }
    switch(pos){
        case FlyLink::ACCELCAL_POS_LEVEL:
        case FlyLink::ACCELCAL_POS_LEFT:
        case FlyLink::ACCELCAL_POS_RIGHT:
        case FlyLink::ACCELCAL_POS_NOSEDOWN:
        case FlyLink::ACCELCAL_POS_NOSEUP:
        case FlyLink::ACCELCAL_POS_BACK:
            caliposition = pos;
            PB_3DCaliStart->setText(QStringLiteral("继续校准"));
            break;
        case FlyLink::ACCELCAL_POS_SUCCESS:
        case FlyLink::ACCELCAL_POS_FAILED:
        default:
            caliposition = 0;
            PB_3DCaliStart->setText(QStringLiteral("3D 校准"));
        break;
    }
    QString statestr = getCaliPostionName(pos);
    LB_CaliState->setText(statestr);
}

QString G_CFG_AccCali::getCaliPostionName(uint8_t pos)
{
    QString str;
    switch(pos){
        case 0: str = QStringLiteral("等待开始");break;
        case FlyLink::ACCELCAL_POS_LEVEL:str = QStringLiteral("水平放置");break;
        case FlyLink::ACCELCAL_POS_LEFT:str = QStringLiteral("左侧朝下放置");break;
        case FlyLink::ACCELCAL_POS_RIGHT:str = QStringLiteral("右侧朝下放置");break;
        case FlyLink::ACCELCAL_POS_NOSEDOWN:str = QStringLiteral("机头朝下放置");break;
        case FlyLink::ACCELCAL_POS_NOSEUP:str = QStringLiteral("机头朝上放置");break;
        case FlyLink::ACCELCAL_POS_BACK:str = QStringLiteral("背面朝上放置");break;
        case FlyLink::ACCELCAL_POS_SUCCESS:str = QStringLiteral("加速度计校准成功");break;
        case FlyLink::ACCELCAL_POS_FAILED:str = QStringLiteral("加速度计校准失败");break;
        default:str = QStringLiteral("未知状态");break;
    }
    return str;
}

void G_CFG_AccCali::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_Acc3DCaliPostion:
            update_cali_position(Qt::DMMM()->getData_main().flylink.Acc3DCaliPostion);
        break;

        default:break;
    }
}

void G_CFG_AccCali::start_or_continue_acc_cali()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr)return;
    // 执行开始任务
    if(caliposition == 0){
        link->do_Acc3DCaliStart();
    }else{
        // 执行继续任务
        link->do_Acc3DCaliNextPostion();
    }
    caliposition = 0;


}

void G_CFG_AccCali::cancel_acc_cali()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();

    if(link == nullptr)return;
    link->do_Acc3DCaliCancel();
    update_cali_position(0);
}


