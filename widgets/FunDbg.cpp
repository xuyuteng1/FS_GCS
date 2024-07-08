#include "FunDbg.h"
#include <QDebug>
#include <QDesktopWidget>
#include "DMMM.h"
#include <QSpacerItem>
#include <QMessageBox>

FunDebug::FunDebug(QWidget *parent)
    :QWidget(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    widgetInit();
    this->setAttribute(Qt::WA_StyledBackground,true);
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }

    this->setWindowOpacity(0.95);
    this->resize(300,100);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();});
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&FunDebug::handle_DMMM_event);
    connect(Pb_Attack_mode,&QPushButton::released,this,&FunDebug::Slot_ModeAttack);
    connect(Pb_flashbootloader,&QPushButton::released,this,&FunDebug::Slot_Flashbootloader);
    connect(Pb_reboot,&QPushButton::released,this,&FunDebug::Slot_Reboot);
    connect(Pb_factory,&QPushButton::released,this,&FunDebug::Slot_Factory);
    connect(Pb_WriteSN,&QPushButton::released,this,&FunDebug::Slot_WriteSN);


}

void FunDebug::widgetInit()
{
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("调试界面"));
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }  

    Pb_Attack_mode = new QPushButton(QStringLiteral("攻击模式"));
    Pb_flashbootloader = new QPushButton(QStringLiteral("写入出厂数据"));
    Pb_reboot = new QPushButton(QStringLiteral("重启飞控"));
    Pb_factory = new QPushButton(QStringLiteral("恢复出厂设置"));
    Pb_WriteSN = new QPushButton(QStringLiteral("写入SN"));
    SN_High = new QSpinBox();
    SN_Low = new QSpinBox();
    SN_High->setRange(2301,2312);
    SN_Low->setRange(1,9999);
    QHBoxLayout* write_SN = new QHBoxLayout();
    write_SN->addWidget(SN_High);
    write_SN->addWidget(SN_Low);
    write_SN->addWidget(Pb_WriteSN);


    this->widgetLayout->addWidget(Pb_Attack_mode,0,0,1,1);
    this->widgetLayout->addWidget(Pb_flashbootloader,0,1,1,1);

    this->widgetLayout->addWidget(Pb_reboot,1,0,1,1);
    this->widgetLayout->addWidget(Pb_factory,1,1,1,1);
    this->widgetLayout->addLayout(write_SN,2,0,1,2);



    this->widgetLayout->setContentsMargins(5,5,5,5);
    this->widgetLayout->setSpacing(6);

    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->widgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);
    this->setObjectName("FunDebug");
    this->setWindowTitle(QStringLiteral("调试界面"));
}

void FunDebug::handle_DMMM_event(int ev, int linkid)
{
//    Q_UNUSED(linkid);
//    // 处理事件
//    switch(ev){
//    case Q_DMMM::DMMM_GCSEvent_GetBoardInfo:
//    case Q_DMMM::DMMM_GCSEvent_MavIDChanged:
//        if(Qt::DMMM()->getFlyLink_main() != nullptr){


//            FlyLink::boardinfo_t pkt  = Qt::DMMM()->getFlyLink_main()->getTDataPort().boardinfo;
//            QString str;
//            // UUID
//            for(int i = 0; i< 12;i++ ){
//                str += QString::asprintf("%02X",*((uint8_t*)(&pkt.udid[0])+i));
//            }
//            UDID[1]->setText(str);

//            // BoardID
//            BoardID[1]->setText(getFCBoardModelString(pkt.boardId));
//            // FW_Version
//            str = QString::asprintf("%d.%d.%d.%d",pkt.fw_version>>24, \
//                                    (pkt.fw_version&0xff0000)>>16,  \
//                                    (pkt.fw_version&0xff00)>>8,\
//                                    (pkt.fw_version&0xff));
//            FW_Version[1]->setText(str);
//            // Link_Version
//            str = QString::asprintf("%d.%d.%d.%d",pkt.link_version>>12, \
//            (pkt.link_version&0xF00)>>8,  \
//            (pkt.link_version&0xF0)>>4,\
//            (pkt.link_version&0xf));
//            Link_Version[1]->setText(str);
//            // FlightDis
//            str = QString::asprintf("%.3f km",pkt.total_flight_dis_m*0.001f);
//            FlightDis[1]->setText(str);
//            // FlightTime
//            str = QString::asprintf("%02d:%02d:%02d",pkt.total_flight_time_s/3600, \
//                                                     pkt.total_flight_time_s%3600/60,\
//                                                     pkt.total_flight_time_s%60);
//            FlightTime[1]->setText(str);
//            is_getinfo = true;
//            MavID[1]->setText(QString::number(Qt::DMMM()->getFlyLink_main()->get_mav_id()));
//            MavIDComBox->setCurrentIndex(MavIDComBox->findData(Qt::DMMM()->getFlyLink_main()->get_mav_id()));
//            MavIDComBox->setChanged(false);
//        }
//        break;
//    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
//        {
//            qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
//            if(!is_getinfo && (last_req_ms-tnow) > 1000){
//                req_boardinfo();
//                last_req_ms = tnow;
//            }
//        }break;

//    default:break;
    //    }
}

void FunDebug::Slot_ModeAttack()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->set_CopterMode_trackattack();
    }
}

void FunDebug::Slot_Flashbootloader()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_FlashBootloader();
    }
}

void FunDebug::Slot_Reboot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_reboot();
    }
}

void FunDebug::Slot_Factory()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_factory();
    }
}

void FunDebug::Slot_WriteSN()
{
    QMessageBox msgBox;

    msgBox.setStyleSheet(QString("QMessageBox {\
                                 color:#FFFFFF;\
                                 font: 400 11pt \"Microsoft YaHei\";\
                                 background-color:rgba(6,7,19,255);\
                                 border: 0px solid gray;  \
                             }\
                             \
                             QMessageBox QLabel {\
                                 color:#FFFFFF;\
                                 font: 400 9.5pt \"Microsoft YaHei\";\
                             }\
                             \
                             QMessageBox QPushButton {\
                                 color:#FFFFFF;\
                                 font: 400 9pt \"Microsoft YaHei\";\
                                 background-color:rgba(22, 119, 255,255);\
                             }\
                             \
                             QMessageBox QPushButton:hover{\
                                 color:#FFFFFF;\
                                 font: 400 9pt \"Microsoft YaHei\";\
                                 background-color:rgba(239, 87, 103,255);\
                             }\
                             \
                             QMessageBox QPushButton:pressed{\
                                 color:#FFFFFF;\
                                 font: 400 9.5pt \"Microsoft YaHei\";\
                                 background-color:rgba(239, 87, 103,200);\
                             }"));

    msgBox.setWindowTitle(QStringLiteral("写入序列号"));
    msgBox.setText(QStringLiteral("确认给飞控写入SN:")+QString::asprintf("%d-%d",this->SN_High->value(),this->SN_Low->value()));
    msgBox.setInformativeText(QStringLiteral("飞控将写入OTP区域,一旦写入将永远无法修改。"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:{

            FlyLink* link = nullptr;
            link = Qt::DMMM()->getFlyLink_main();
            if(link!=nullptr){
                uint32_t SN = (uint32_t)(this->SN_High->value()<<16) + this->SN_Low->value();
                link->do_SetBoardSN(SN);
            }

        break;
    }
    default:{
        break;
    }
    }
}

