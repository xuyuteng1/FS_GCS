/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "G_cfg_mag_cali.h"
#include "DMMM.h"
#include <qmath.h>


G_CFG_MagCali::G_CFG_MagCali(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("罗盘校准"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void G_CFG_MagCali::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_MagCali::handle_DMMM_event);
    connect(PB_MagCali          , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagCaliStart();}});
    connect(PB_MagCaliStop      , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagCaliStop();}});
    connect(PB_InFlightMagCali  , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagInFlightCaliStart();}});
    connect(PB_SimpleMagCali    , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagSimpleCaliStart(this->SP_FixedYaw->value());}});
    connect(PB_InFlightMagCaliCancel, &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_MagInFlightCaliCancel();}});
}

void G_CFG_MagCali::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("罗盘校准"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(LB_MagInfo == nullptr){
        LB_MagInfo = new QLabel(QStringLiteral("       磁罗盘标准,请在室外空旷场地进行,身边不带任何含铁磁性的物体,\r\n"
                                               "待飞行器完成定位后沿着飞行器6个轴向分别进行循环旋转。"));
        LB_MagInfo->setObjectName(QString::fromUtf8("textLabel"));
//        LB_MagInfo->setWordWrap(true);
    }
    if(LB_InFlightMagInfo == nullptr){
        LB_InFlightMagInfo = new QLabel(QStringLiteral("       飞行中磁罗盘校准:请在自稳或定高模式下进行,点击\r\n"
                                                       "校准后,飞行至空中并绕圈旋转,飞控将自动进行校准,校\r\n"
                                                       "准结束时飞控将提醒校准完成。"));
        LB_InFlightMagInfo->setObjectName(QString::fromUtf8("textLabel"));
//        LB_InFlightMagInfo->setWordWrap(true);
    }
    if(LB_SimpleMagInfo == nullptr){
        LB_SimpleMagInfo =  new QLabel(QStringLiteral("       当飞行器尺寸较大时,无法使用常规校准方式进行磁罗\r\n"
                                                      "盘校准时,可使用简单校准方式。在室外空旷场地，待飞行\r\n"
                                                      "器定位完成后,将飞行器水平摆放至固定位置,使用手机等\r\n"
                                                      "测量当前飞行器的真实航向,并填入下方角度中，然后点击\r\n"
                                                      "校准即可。"));
        LB_SimpleMagInfo->setObjectName(QString::fromUtf8("textLabel"));
//        LB_SimpleMagInfo->setWordWrap(true);
    }
    if(LB_MagState [0] == nullptr){
        LB_MagState[0] = new QLabel(QStringLiteral("未开始"));
        LB_MagState[0]->setObjectName(QString::fromUtf8("SystemInfoWidgetLabel"));
        LB_MagState[0]->setWordWrap(true);
    }

    if(LB_MagState [1] == nullptr){
        LB_MagState[1] = new QLabel(QStringLiteral("未开始"));
        LB_MagState[1]->setObjectName(QString::fromUtf8("SystemInfoWidgetLabel"));
        LB_MagState[1]->setWordWrap(true);
    }
    if(LB_MagState [2] == nullptr){
        LB_MagState[2] = new QLabel(QStringLiteral("未开始"));
        LB_MagState[2]->setObjectName(QString::fromUtf8("SystemInfoWidgetLabel"));
        LB_MagState[2]->setWordWrap(true);
    }

    if(progress[0] == nullptr){
        progress[0] = new ProgressBarPercent();
        progress[0]->setMaximumSize(100,100);
    }
    if(progress [1] == nullptr){
        progress[1] = new ProgressBarPercent();
        progress[1]->setMaximumSize(100,100);
    }
    if(progress [2] == nullptr){
        progress[2] = new ProgressBarPercent();
        progress[2]->setMaximumSize(100,100);
    }

    if(PB_MagCali == nullptr){
        PB_MagCali = new QPushButton(QStringLiteral("开始校准"));
        PB_MagCali->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_MagCaliStop == nullptr){
        PB_MagCaliStop = new QPushButton(QStringLiteral("停止校准"));
        PB_MagCaliStop->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(PB_InFlightMagCali == nullptr){
        PB_InFlightMagCali = new QPushButton(QStringLiteral("开始校准"));
        PB_InFlightMagCali->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(PB_InFlightMagCaliCancel == nullptr){
        PB_InFlightMagCaliCancel = new QPushButton(QStringLiteral("取消校准"));
        PB_InFlightMagCaliCancel->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(PB_SimpleMagCali == nullptr){
        PB_SimpleMagCali = new QPushButton(QStringLiteral("开始校准"));
        PB_SimpleMagCali->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(Group_MagCali == nullptr){
        Group_MagCali = new QGroupBox(QStringLiteral("标准校准"));
        Group_MagCali->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_MagCali->setAlignment(Qt::AlignCenter);
    }

    if(Group_InFlightMagCali == nullptr){
        Group_InFlightMagCali = new QGroupBox(QStringLiteral("飞行中校准"));
        Group_InFlightMagCali->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_InFlightMagCali->setAlignment(Qt::AlignCenter);
    }

    if(Group_SimpleMagCali == nullptr){
        Group_SimpleMagCali = new QGroupBox(QStringLiteral("简单校准"));
        Group_SimpleMagCali->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_SimpleMagCali->setAlignment(Qt::AlignCenter);
    }

    if(LayoutMagCali == nullptr){
        LayoutMagCali = new QGridLayout(Group_MagCali);
    }

    if(LayoutInFlightMagCali == nullptr){
        LayoutInFlightMagCali = new QGridLayout(Group_InFlightMagCali);
    }
    if(LayoutSimpleMagCali == nullptr){
        LayoutSimpleMagCali = new QGridLayout(Group_SimpleMagCali);
    }
    if(LayoutProgress == nullptr){
        LayoutProgress = new QGridLayout();
    }


    if(SP_FixedYaw == nullptr){
        SP_FixedYaw = new QSpinBox();
        SP_FixedYaw->setRange(0,359);
        SP_FixedYaw->setObjectName("widgetSpinBox");
        SP_FixedYaw->setAlignment(Qt::AlignCenter);
    }

    // 常规校准布局
    LayoutProgress->addWidget(progress[0],0,0,1,1,Qt::AlignCenter);
    LayoutProgress->addWidget(progress[1],0,1,1,1,Qt::AlignCenter);
    LayoutProgress->addWidget(progress[2],0,2,1,1,Qt::AlignCenter);

    LayoutProgress->addWidget(LB_MagState[0],1,0,1,1,Qt::AlignCenter);
    LayoutProgress->addWidget(LB_MagState[1],1,1,1,1,Qt::AlignCenter);
    LayoutProgress->addWidget(LB_MagState[2],1,2,1,1,Qt::AlignCenter);
    LayoutProgress->setHorizontalSpacing(40);
    LayoutMagCali->addWidget(LB_MagInfo,0,0,1,20,Qt::AlignCenter);
    LayoutMagCali->addLayout(LayoutProgress,1,2,1,16,Qt::AlignCenter);
    LayoutMagCali->addWidget(PB_MagCali,2,9,1,1,Qt::AlignCenter);
    LayoutMagCali->addWidget(PB_MagCaliStop,2,10,1,1,Qt::AlignCenter);

    LayoutInFlightMagCali->addWidget(LB_InFlightMagInfo,0,0,2,20,Qt::AlignCenter);
    LayoutInFlightMagCali->addWidget(PB_InFlightMagCali,2,9,1,1,Qt::AlignCenter);
    LayoutInFlightMagCali->addWidget(PB_InFlightMagCaliCancel,2,10,1,1,Qt::AlignCenter);

    LayoutSimpleMagCali->addWidget(LB_SimpleMagInfo,0,0,1,20,Qt::AlignCenter);
    LayoutSimpleMagCali->addWidget(SP_FixedYaw,1,9,1,2,Qt::AlignCenter);
    LayoutSimpleMagCali->addWidget(PB_SimpleMagCali,2,9,1,2,Qt::AlignCenter);

    widgetLayout->addWidget(titleLabel,             0,0,1,2);
    widgetLayout->addWidget(Group_MagCali,          1,0,1,2);
    widgetLayout->addWidget(Group_SimpleMagCali,    2,0,1,1);
    widgetLayout->addWidget(Group_InFlightMagCali,  2,1,1,1);

    LayoutMagCali->setRowMinimumHeight(0,100);
    LayoutSimpleMagCali->setRowMinimumHeight(0,100);


    this->widgetLayout->setContentsMargins(10,20,10,20);

    this->setLayout(widgetLayout);
}

void G_CFG_MagCali::reset_state()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        mag_count = link->getTDataPort().Compass_count;
    }
    for(uint8_t i = 0;i < 3;i++){
        if(i<mag_count){
            progress[i]->setVisible(true);
            LB_MagState[i]->setVisible(true);
        }
        else{
            progress[i]->setVisible(false);
            LB_MagState[i]->setVisible(false);
        }
        progress[i]->setValue(0);
        LB_MagState[i]->setText(QStringLiteral("罗盘")+QString::number(i+1)+":"+getCaliState(0));
    }
}

QString G_CFG_MagCali::getCaliState(uint8_t state)
{
    switch(state){
        case FlyLink::NOT_STARTED:
            return QStringLiteral("未开始");
            break;

        case FlyLink::WAITING_TO_START:
            return QStringLiteral("等待开始");
            break;
        case FlyLink::RUNNING_STEP_ONE:
            return QStringLiteral("校准中");
            break;
        case FlyLink::RUNNING_STEP_TWO:
            return QStringLiteral("校准中...");
            break;
        case FlyLink::SUCCESS:
            return QStringLiteral("校准成功");
            break;
        case FlyLink::FAILED:
            return QStringLiteral("校准失败");
            break;
        case FlyLink::BAD_ORIENTATION:
            return QStringLiteral("方向错误");
            break;

        case FlyLink::BAD_RADIUS:
            return QStringLiteral("半径错误");
            break;
        default:
            return QStringLiteral("未开始");
            break;
    }

    return QStringLiteral("未开始");
}

void G_CFG_MagCali::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    uint8_t count = 0;
    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_MagCaliProgress:
            count = Qt::DMMM()->getData_main().flylink.MagCaliCount;
            for(uint8_t i = 0;i < 3;i++){
                if(i < count){
                    progress[i]->setVisible(true);
                    LB_MagState[i]->setVisible(true);
                }
                else{
                    progress[i]->setVisible(false);
                    LB_MagState[i]->setVisible(false);
                }
                progress[i]->setValue(Qt::DMMM()->getData_main().flylink.MagCaliProgress[i].completion_pct);
                LB_MagState[i]->setText(QStringLiteral("罗盘")+QString::number(i+1)+":"+getCaliState(Qt::DMMM()->getData_main().flylink.MagCaliProgress[i].cal_status));
            }
            break;

        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        case Q_DMMM::DMMM_GCSEvent_Protocol_lost:
        case Q_DMMM::DMMM_GCSEvent_MagCountChanged:
            reset_state();
            break;

        default:break;
    }
}


QGridLayout *G_CFG_MagCali::getWidgetLayout() const
{
    return widgetLayout;
}
