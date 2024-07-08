/**=================================================================**
 * @brief       : 磁罗盘校准部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-07-19     Jerry.xl     the first version
 **==================================================================**/
#include "G_cfg_param_gnssposition.h"
#include "DMMM.h"
#include <qmath.h>


G_CFG_AntennaPos::G_CFG_AntennaPos(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("天线位置"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

QGridLayout *G_CFG_AntennaPos::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_AntennaPos::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_AntennaPos::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_reqParamGNSSPosition();}});
    connect(PB_upload   , &QPushButton::released,this,&G_CFG_AntennaPos::upload_param);
}

void G_CFG_AntennaPos::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("天线位置"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(LB_Info == nullptr){
        LB_Info = new QLabel(QStringLiteral("配置卫星定位模块天线位置，坐标系为\"前、右、下\",单位为米。"));
        LB_Info->setObjectName(QString::fromUtf8("textLabel"));
        LB_Info->setAlignment(Qt::AlignCenter);
    }

    if(LB_GNSS1 == nullptr){
        LB_GNSS1 = new QLabel(QStringLiteral("卫星天线1"));
        LB_GNSS1->setObjectName(QString::fromUtf8("CFGLabelState"));
        LB_GNSS1->setAlignment(Qt::AlignCenter);
        LB_GNSS1->setToolTip(QStringLiteral(""));
    }

    if( LB_GNSS2 == nullptr){
        LB_GNSS2 = new QLabel(QStringLiteral("卫星天线2"));
        LB_GNSS2->setObjectName(QString::fromUtf8("CFGLabelState"));
        LB_GNSS2->setAlignment(Qt::AlignCenter);
        LB_GNSS2->setToolTip(QStringLiteral(""));
    }

    if(LB_Posx == nullptr){
        LB_Posx = new QLabel(QStringLiteral("前向距离:"));
        LB_Posx->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_Posx->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_Posx->setToolTip(QStringLiteral(""));
    }
    if(LB_Posy == nullptr){
        LB_Posy = new QLabel(QStringLiteral("右方距离:"));
        LB_Posy->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_Posy->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_Posy->setToolTip(QStringLiteral(""));
    }
    if(LB_Posz == nullptr){
        LB_Posz = new QLabel(QStringLiteral("下方距离:"));
        LB_Posz->setObjectName(QString::fromUtf8("CFGLabelPre"));
        LB_Posz->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        LB_Posz->setToolTip(QStringLiteral(""));
    }

    if(SB_GNSS1_POS[0] == nullptr){
        SB_GNSS1_POS[0] = new UDoubleSpinBox();
        SB_GNSS1_POS[0]->setRange(-300,300);
        SB_GNSS1_POS[0]->setValue(0);
        SB_GNSS1_POS[0]->setSingleStep(0.05);
        SB_GNSS1_POS[0]->setDecimals(2);
        SB_GNSS1_POS[0]->setAlignment(Qt::AlignCenter);
        SB_GNSS1_POS[0]->setSuffix(QStringLiteral(""));
        SB_GNSS1_POS[0]->setChanged(false);
        SB_GNSS1_POS[0]->setToolTip(QStringLiteral("GPS天线距离飞行器质心的前向距离，前为正，后为负"));
        SB_GNSS1_POS[0]->setObjectName("widgetDoubleSpinBox");
    }
    if( SB_GNSS1_POS[1] == nullptr){
        SB_GNSS1_POS[1] = new UDoubleSpinBox();
        SB_GNSS1_POS[1]->setRange(-300,300);
        SB_GNSS1_POS[1]->setValue(0);
        SB_GNSS1_POS[1]->setSingleStep(0.05);
        SB_GNSS1_POS[1]->setDecimals(2);
        SB_GNSS1_POS[1]->setAlignment(Qt::AlignCenter);
        SB_GNSS1_POS[1]->setSuffix(QStringLiteral(""));
        SB_GNSS1_POS[1]->setChanged(false);
        SB_GNSS1_POS[1]->setToolTip(QStringLiteral("GPS天线距离飞行器质心的右侧距离，右侧为正，左侧为负"));
        SB_GNSS1_POS[1]->setObjectName("widgetDoubleSpinBox");
    }
    if( SB_GNSS1_POS[2] == nullptr){
        SB_GNSS1_POS[2] = new UDoubleSpinBox();
        SB_GNSS1_POS[2]->setRange(-300,300);
        SB_GNSS1_POS[2]->setValue(0);
        SB_GNSS1_POS[2]->setSingleStep(0.05);
        SB_GNSS1_POS[2]->setDecimals(2);
        SB_GNSS1_POS[2]->setAlignment(Qt::AlignCenter);
        SB_GNSS1_POS[2]->setSuffix(QStringLiteral(""));
        SB_GNSS1_POS[2]->setChanged(false);
        SB_GNSS1_POS[2]->setToolTip(QStringLiteral("GPS天线距离飞行器质心的下侧距离，下方为正，上方为负"));
        SB_GNSS1_POS[2]->setObjectName("widgetDoubleSpinBox");
    }

    if( SB_GNSS2_POS[0] == nullptr){
        SB_GNSS2_POS[0] = new UDoubleSpinBox();
        SB_GNSS2_POS[0]->setRange(-300,300);
        SB_GNSS2_POS[0]->setValue(0);
        SB_GNSS2_POS[0]->setSingleStep(0.05);
        SB_GNSS2_POS[0]->setDecimals(2);
        SB_GNSS2_POS[0]->setAlignment(Qt::AlignCenter);
        SB_GNSS2_POS[0]->setSuffix(QStringLiteral(""));
        SB_GNSS2_POS[0]->setChanged(false);
        SB_GNSS2_POS[0]->setToolTip(QStringLiteral("GPS天线距离飞行器质心的前向距离，前为正，后为负"));
        SB_GNSS2_POS[0]->setObjectName("widgetDoubleSpinBox");
    }
    if( SB_GNSS2_POS[1] == nullptr){
        SB_GNSS2_POS[1] = new UDoubleSpinBox();
        SB_GNSS2_POS[1]->setRange(-300,300);
        SB_GNSS2_POS[1]->setValue(0);
        SB_GNSS2_POS[1]->setSingleStep(0.05);
        SB_GNSS2_POS[1]->setDecimals(2);
        SB_GNSS2_POS[1]->setAlignment(Qt::AlignCenter);
        SB_GNSS2_POS[1]->setSuffix(QStringLiteral(""));
        SB_GNSS2_POS[1]->setChanged(false);
        SB_GNSS2_POS[1]->setToolTip(QStringLiteral("GPS天线距离飞行器质心的右侧距离，右侧为正，左侧为负"));
        SB_GNSS2_POS[1]->setObjectName("widgetDoubleSpinBox");
    }
    if( SB_GNSS2_POS[2] == nullptr){
        SB_GNSS2_POS[2] = new UDoubleSpinBox();
        SB_GNSS2_POS[2]->setRange(-300,300);
        SB_GNSS2_POS[2]->setValue(0);
        SB_GNSS2_POS[2]->setSingleStep(0.05);
        SB_GNSS2_POS[2]->setDecimals(2);
        SB_GNSS2_POS[2]->setAlignment(Qt::AlignCenter);
        SB_GNSS2_POS[2]->setSuffix(QStringLiteral(""));
        SB_GNSS2_POS[2]->setChanged(false);
        SB_GNSS2_POS[2]->setToolTip(QStringLiteral("GPS天线距离飞行器质心的下侧距离，下方为正，上方为负"));
        SB_GNSS2_POS[2]->setObjectName("widgetDoubleSpinBox");
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


    widgetLayout->addWidget(titleLabel,         0 ,0 ,1 ,20);
//    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 20);

    widgetLayout->addWidget(LB_Info,            2 ,0 ,1 ,20);
    widgetLayout->addWidget(LB_GNSS1,           3 ,9 ,1 ,1 );
    widgetLayout->addWidget(LB_GNSS2,           3 ,10,1 ,1 );
    widgetLayout->addWidget(LB_Posx,            4 ,8 ,1 ,1 );
    widgetLayout->addWidget(LB_Posy,            5 ,8 ,1 ,1 );
    widgetLayout->addWidget(LB_Posz,            6 ,8 ,1 ,1 );

    widgetLayout->addWidget(SB_GNSS1_POS[0],    4 ,9 ,1 ,1 );
    widgetLayout->addWidget(SB_GNSS1_POS[1],    5 ,9 ,1 ,1 );
    widgetLayout->addWidget(SB_GNSS1_POS[2],    6 ,9 ,1 ,1 );

    widgetLayout->addWidget(SB_GNSS2_POS[0],    4 ,10 ,1 ,1 );
    widgetLayout->addWidget(SB_GNSS2_POS[1],    5 ,10 ,1 ,1 );
    widgetLayout->addWidget(SB_GNSS2_POS[2],    6 ,10 ,1 ,1 );
    widgetLayout->addLayout(widgetLayout_pb,8,0,1,20);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 9, 0, 1, 20);




//    widgetLayout->setVerticalSpacing(15);

    this->widgetLayout->setContentsMargins(10,20,10,20);

    this->setLayout(widgetLayout);
}

void G_CFG_AntennaPos::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_GetGNSSPostion:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link){
                for(int i = 0 ;i < 3;i++){
                    SB_GNSS1_POS[i]->setValue(link->getTVehicleParam().GnssPostion[0].pos[i]*0.01f);
                    SB_GNSS2_POS[i]->setValue(link->getTVehicleParam().GnssPostion[1].pos[i]*0.01f);
                    SB_GNSS1_POS[i]->setChanged(false);
                    SB_GNSS2_POS[i]->setChanged(false);
                }
            }
        }break;
        default:break;
    }
}

void G_CFG_AntennaPos::upload_param()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link){
        FlyLink::param_GNSSPosition pkt{};

        pkt.is_set = 1;
        pkt.gnss_id = 0;
        for(int i = 0;i < 3;i++){
            pkt.pos[i] = SB_GNSS1_POS[i]->value()*100;
        }
        link->do_setParamGNSSPosition(pkt);


        pkt.gnss_id = 1;
        for(int i = 0;i < 3;i++){
            pkt.pos[i] = SB_GNSS2_POS[i]->value()*100;
        }
        link->do_setParamGNSSPosition(pkt);
    }
}
