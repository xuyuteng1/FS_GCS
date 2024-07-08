/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "G_cfg_boardorientation.h"
#include "DMMM.h"
#include <qmath.h>

G_CFG_BoardOrientation::G_CFG_BoardOrientation(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("安装方向"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}


QGridLayout *G_CFG_BoardOrientation::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_BoardOrientation::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_BoardOrientation::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->req_BoardOrientation();}});
    connect(PB_upload   , &QPushButton::released,this,&G_CFG_BoardOrientation::upload_param);

}

void G_CFG_BoardOrientation::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("安装方向"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("请尽量按照飞控标准坐标系进行安装,若因机舱尺寸等原因,确需更换安装方向,\r\n"
                                            "请按照下方选项,由标准安装方向顺序旋转至目标方向。"));
        LB_Info->setObjectName(QString::fromUtf8("warningLabel"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    if(CB_boardorientation == nullptr){
        CB_boardorientation = new UComboBox();
        CB_boardorientation->setEditable(false);
        for(int i = 0;i < FlyLink::ROTATION_MAX;i++){
            if(i == FlyLink::ROTATION_ROLL_90_PITCH_68_YAW_293 ||
               i == FlyLink::ROTATION_PITCH_7){
                continue;
            }
            CB_boardorientation->addItem(FlyLink::getBoardOrientation(i),i);
        }
        CB_boardorientation->setChanged(false);
        CB_boardorientation->setToolTip(QStringLiteral("旋转角度为按照右手法则在对应轴上的旋转角度"));
        CB_boardorientation->setObjectName("widgetComboBox");

    }

    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_download->setToolTip(QStringLiteral(""));
    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
        PB_upload->setToolTip(QStringLiteral(""));
    }
    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
    }
    widgetLayout_pb->addStretch(5);
    widgetLayout_pb->addWidget(PB_download,1);
    widgetLayout_pb->addWidget(PB_upload,1);
    widgetLayout_pb->addStretch(5);

    widgetLayout->addWidget(titleLabel,    0 ,0 ,1 ,20);
//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 20);
    widgetLayout->addWidget(LB_Info,    2 ,0 ,1 ,20);

//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 3, 0, 1, 1);
//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 3, 19, 1, 1);
    widgetLayout->addWidget(CB_boardorientation,   3 ,0 ,1 ,20,Qt::AlignCenter );



    widgetLayout->addLayout(widgetLayout_pb,4,0,1,20);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 5, 0, 1, 1);
    widgetLayout->setRowMinimumHeight(0,60);
    widgetLayout->setRowMinimumHeight(1,45);
    widgetLayout->setRowMinimumHeight(2,40);

    this->widgetLayout->setContentsMargins(10,20,10,20);
    this->setLayout(widgetLayout);
}

void G_CFG_BoardOrientation::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetBoardOrientation:
        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                uint8_t orientation = link->getTDataPort().BoardOrientation;
                CB_boardorientation->setCurrentIndex(CB_boardorientation->findData(QVariant(orientation)));
                CB_boardorientation->setChanged(false);
            }
        }break;
        default:break;
    }
}

void G_CFG_BoardOrientation::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){

        uint8_t orientation = CB_boardorientation->currentData().toInt();
        link->set_BoardOrientation(orientation);
    }
}
