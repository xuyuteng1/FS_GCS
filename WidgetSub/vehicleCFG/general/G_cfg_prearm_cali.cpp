#include "G_cfg_prearm_cali.h"
#include "DMMM.h"
#include <qmath.h>

G_CFG_PreCali::G_CFG_PreCali(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("飞前校准"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}



QGridLayout *G_CFG_PreCali::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_PreCali::connectSignalAndSlot()
{
    connect(PB_AccTrim, &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_AccTrimCali();}});
    connect(PB_Baro,    &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_BaroCaliStart();}});
    connect(PB_Gyro,    &QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->do_GyroCaliStart();}});
}

void G_CFG_PreCali::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("飞前校准"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(LB_AccTrim == nullptr){
        LB_AccTrim = new QLabel(QStringLiteral("       请将飞行器置于水平,\r\n"
                                               "待稳定后,开始校准。"));
        LB_AccTrim->setObjectName(QString::fromUtf8("infomationLabel"));

    }
    if(LB_Gyro == nullptr){
        LB_Gyro = new QLabel(QStringLiteral("       请保持飞行器静止,\r\n"
                                            "待稳定后,开始校准。"));
        LB_Gyro->setObjectName(QString::fromUtf8("infomationLabel"));

    }
    if(LB_Baro == nullptr){
        LB_Baro = new QLabel(QStringLiteral("       请保持飞行器静止,\r\n"
                                            "待稳定后,开始校准。"));
        LB_Baro->setObjectName(QString::fromUtf8("infomationLabel"));

    }

    if(PB_AccTrim == nullptr){
        PB_AccTrim = new QPushButton(QStringLiteral("水平校准"));
        PB_AccTrim->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_Gyro == nullptr){
        PB_Gyro = new QPushButton(QStringLiteral("陀螺校准"));
        PB_Gyro->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(PB_Baro == nullptr){
        PB_Baro = new QPushButton(QStringLiteral("气压校准"));
        PB_Baro->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }

    if(Group_AccTrim == nullptr){
        Group_AccTrim = new QGroupBox(QStringLiteral("水平校准"));
        Group_AccTrim->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_AccTrim->setAlignment(Qt::AlignCenter);
    }
    if(LayoutAccTrim == nullptr){
        LayoutAccTrim = new QGridLayout(Group_AccTrim);
    }

    if(Group_Baro == nullptr){
        Group_Baro = new QGroupBox(QStringLiteral("气压校准"));
        Group_Baro->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_Baro->setAlignment(Qt::AlignCenter);
    }
    if(LayoutBaro == nullptr){
        LayoutBaro = new QGridLayout(Group_Baro);
    }

    if(Group_Gyro == nullptr){
        Group_Gyro = new QGroupBox(QStringLiteral("陀螺校准"));
        Group_Gyro->setObjectName("SystemConfigWidgetSubGroupBox");
        Group_Gyro->setAlignment(Qt::AlignCenter);
    }
    if(LayoutGyro == nullptr){
        LayoutGyro = new QGridLayout(Group_Gyro);
    }

    LayoutAccTrim->addWidget( LB_AccTrim,0,0,1,3,Qt::AlignCenter);
    LayoutAccTrim->addWidget( PB_AccTrim,1,1,1,1,Qt::AlignCenter);

    LayoutGyro->addWidget( LB_Gyro,0,0,1,3,Qt::AlignCenter);
    LayoutGyro->addWidget( PB_Gyro,1,1,1,1,Qt::AlignCenter);

    LayoutBaro->addWidget( LB_Baro,0,0,1,3,Qt::AlignCenter);
    LayoutBaro->addWidget( PB_Baro,1,1,1,1,Qt::AlignCenter);



    widgetLayout->addWidget(titleLabel,     0,0,1,3);
    widgetLayout->addWidget(Group_AccTrim,  1,0,1,1);
    widgetLayout->addWidget(Group_Gyro,     1,1,1,1);
    widgetLayout->addWidget(Group_Baro,     1,2,1,1);
    this->LayoutAccTrim->setRowMinimumHeight(0,100);
    this->LayoutGyro->setRowMinimumHeight(0,100);
    this->LayoutBaro->setRowMinimumHeight(0,100);
    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 2, 0, 1, 3);
    this->widgetLayout->setContentsMargins(10,20,10,20);
    this->setLayout(widgetLayout);
//    this->widgetLayout->setRowMinimumHeight(1,25);
}
