#include "FCBoardInfo.h"
#include <QDebug>
#include <QDesktopWidget>
#include "DMMM.h"
#include <QSpacerItem>
#include <QtGlobal>
#include <QDebug>
#include    <QFileDialog>
#include    <QTextStream>
#include    <QSettings>
FCBoardINFO::FCBoardINFO(QWidget *parent)
    :QWidget(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(this->windowFlags() |Qt::Dialog|Qt::FramelessWindowHint);
    this->setWindowModality(Qt::ApplicationModal);
    widgetInit();
    this->setAttribute(Qt::WA_StyledBackground,true);
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }

    this->setWindowOpacity(0.95);
    this->resize(300,100);
    this->move(50,100);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&FCBoardINFO::handle_DMMM_event);
    void (QComboBox::*currentIndexChangedSignal)(int) = &QComboBox::currentIndexChanged;
    connect(this->MavIDComBox,currentIndexChangedSignal,this,&FCBoardINFO::slot_MavIdChanged);
#ifdef GCS_DEBUG_ENABLE
    connect(this->PB_saveinfo,&QPushButton::released,this,&FCBoardINFO::SaveBoardInfo);
#endif
}

QString FCBoardINFO::getFCBoardModelString(uint32_t id)
{
    switch(id){
    case FCBoardManufactor_KWYWAY_KYFly_FC_V100 :return QStringLiteral("KYFly_FC_V100 ");
    case FCBoardManufactor_KWYWAY_KYFly_GPS_V100:return QStringLiteral("KYFly_GPS_V100");
    case FCBoardManufactor_XYFly_FC_V100        :return QStringLiteral("XYFly_FC_V100 ");
    case FCBoardManufactor_XYFly_FC_V200        :return QStringLiteral("XYFly_FC_V200 ");
    case FCBoardManufactor_XYFly_GPS_V100       :return QStringLiteral("XYFly_GPS_V100");
    case FCBoardManufactor_XYFly_FC_V300        :return QStringLiteral("XYFly_FC_V30-H7");
    case FCBoardManufactor_XYFly_FC_V310        :return QStringLiteral("XYFly_FC_V31-F7");
    case FCBoardManufactor_XYFly_FC_V330E_J30J  :return QStringLiteral("XYFly_FC_V330E");
    case FCBoardManufactor_XYFly_FT_INS_V100    :return QStringLiteral("XYFly_FT-INS_V100");
    case FCBoardManufactor_XYFly_FT_CTRL_V100   :return QStringLiteral("XYFly_FT-CTRL_V100");
    case FCBoardManufactor_CUAV_X7              :return QStringLiteral("CUAV_X7 ");
    case FCBoardManufactor_CUAVv5               :return QStringLiteral("CUAVv5  ");
    case FCBoardManufactor_CUAVNora             :return QStringLiteral("CUAVNora");

    }
    return QString::asprintf("%d",id);
}

QString FCBoardINFO::getFCBoardSimPleString(uint32_t id)
{
    switch(id){
    case FCBoardManufactor_KWYWAY_KYFly_FC_V100 :return QStringLiteral("V100 ");
    case FCBoardManufactor_KWYWAY_KYFly_GPS_V100:return QStringLiteral("V100");
    case FCBoardManufactor_XYFly_FC_V100        :return QStringLiteral("V100 ");
    case FCBoardManufactor_XYFly_FC_V200        :return QStringLiteral("V200 ");
    case FCBoardManufactor_XYFly_GPS_V100       :return QStringLiteral("V100");
    case FCBoardManufactor_XYFly_FC_V300        :return QStringLiteral("V30-H7");
    case FCBoardManufactor_XYFly_FC_V310        :return QStringLiteral("V31-F7");
    case FCBoardManufactor_XYFly_FC_V330E_J30J  :return QStringLiteral("V330E");
    case FCBoardManufactor_XYFly_FT_INS_V100    :return QStringLiteral("FTINS_V100");
    case FCBoardManufactor_XYFly_FT_CTRL_V100   :return QStringLiteral("FTCTRL_V100");
    case FCBoardManufactor_CUAV_X7              :return QStringLiteral("CUAV_X7 ");
    case FCBoardManufactor_CUAVv5               :return QStringLiteral("CUAVv5  ");
    case FCBoardManufactor_CUAVNora             :return QStringLiteral("CUAVNora");
    }
    return QString::asprintf("%d",id);
}
void FCBoardINFO::widgetInit()
{
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("飞控信息"));
    }
    UDID[0] = new QLabel(QStringLiteral("硬件UUID:"));
    UDID[1] = new QLabel();
    BoardID[0] = new QLabel(QStringLiteral("硬件型号:"));
    BoardID[1] = new QLabel();
    BoardSN[0] = new QLabel(QStringLiteral("硬件序号:"));
    BoardSN[1] = new QLabel();

    FW_Version[0] = new QLabel(QStringLiteral("固件版本:"));
    FW_Version[1] = new QLabel();
    Link_Version[0] = new QLabel(QStringLiteral("协议版本:"));
    Link_Version[1] = new QLabel();
    FlightDis[0] = new QLabel(QStringLiteral("飞行里程:"));
    FlightDis[1] = new QLabel();
    FlightTime[0] = new QLabel(QStringLiteral("飞行时间:"));
    FlightTime[1] = new QLabel();

    UDID[1]->setTextInteractionFlags(Qt::TextSelectableByMouse);
    BoardID[1]->setTextInteractionFlags(Qt::TextSelectableByMouse);
    BoardSN[1]->setTextInteractionFlags(Qt::TextSelectableByMouse);
    FW_Version[1]->setTextInteractionFlags(Qt::TextSelectableByMouse);
    Link_Version[1]->setTextInteractionFlags(Qt::TextSelectableByMouse);

    MavID[0] = new QLabel(QStringLiteral("飞机编号:"));
    MavID[1] = new QLabel();
    MavIDComBox = new UComboBox();
    for(uint8_t i = 0;i<255;i++){
        MavIDComBox->addItem(QString::number(i+1),QVariant(i+1));
        MavIDComBox->setEditable(false);
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    widgetLayout->addWidget(UDID[0]         ,0,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(UDID[1]         ,0,1,1,2,Qt::AlignLeft|Qt::AlignVCenter);

    widgetLayout->addWidget(BoardSN[0]      ,1,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(BoardSN[1]      ,1,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
    widgetLayout->addWidget(BoardID[0]      ,2,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(BoardID[1]      ,2,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
    widgetLayout->addWidget(FW_Version[0]   ,3,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(FW_Version[1]   ,3,1 ,1,1,Qt::AlignLeft|Qt::AlignVCenter);
    widgetLayout->addWidget(Link_Version[0] ,4,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(Link_Version[1] ,4,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
    widgetLayout->addWidget(FlightDis[0]    ,5,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(FlightDis[1]    ,5,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
    widgetLayout->addWidget(FlightTime[0]   ,6,0,1,1,Qt::AlignCenter);
    widgetLayout->addWidget(FlightTime[1]   ,6,1,1,1,Qt::AlignLeft|Qt::AlignVCenter);
    widgetLayout->addWidget(MavIDComBox        ,7,0,1,1,Qt::AlignCenter);
#ifdef GCS_DEBUG_ENABLE
    PB_saveinfo = new QPushButton(QStringLiteral("保存信息"));
    widgetLayout->addWidget(PB_saveinfo     ,8,0,1,2,Qt::AlignVCenter);
#endif

//    widgetLayout->setColumnStretch(0,1);
//    widgetLayout->setColumnStretch(0,1);
//    widgetLayout->setColumnStretch(0,3);
//    widgetLayout->setColumnStretch(0,1);

    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }  

    this->widgetLayout->setContentsMargins(5,5,5,5);
    this->widgetLayout->setSpacing(6);



    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->widgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);
    this->setObjectName("FCBoardINFO");
    this->setWindowTitle(QStringLiteral("飞控信息"));
}

void FCBoardINFO::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_GetBoardInfo:
    case Q_DMMM::DMMM_GCSEvent_MavIDChanged:
        if(Qt::DMMM()->getFlyLink_main() != nullptr){


            FlyLink::boardinfo_t pkt  = Qt::DMMM()->getFlyLink_main()->getTDataPort().boardinfo;
            QString str;
            // UUID
            for(int i = 11;;i-- ){
                str += QString::asprintf("%1X",(*((uint8_t*)(&pkt.udid[0])+i))&0xf);
                str += QString::asprintf("%1X",(*((uint8_t*)(&pkt.udid[0])+i))>>4);
                if(i==0)break;
            }
            UDID[1]->setText(str);
            str = QString::asprintf("20%d-%04d",pkt.boardSN>>16,pkt.boardSN&0xffff);
            BoardSN[1]->setText(str);
            // BoardID
            BoardID[1]->setText(getFCBoardModelString(pkt.boardId));
            // FW_Version
            str = QString::asprintf("%d.%d.%d.%d",pkt.fw_version>>24, \
                                    (pkt.fw_version&0xff0000)>>16,  \
                                    (pkt.fw_version&0xff00)>>8,\
                                    (pkt.fw_version&0xff));
            FW_Version[1]->setText(str);

            // Link_Version
            str = QString::asprintf("%d.%d.%d",pkt.link_version>>12, \
            (pkt.link_version&0xF00)>>8,  \
            (pkt.link_version&0xF0)>>4)+FlyLink::getProtocolType(0xf&pkt.link_version);
            Link_Version[1]->setText(str);
            // FlightDis
            str = QString::asprintf("%.3f km",pkt.total_flight_dis_m*0.001f);
            FlightDis[1]->setText(str);
            // FlightTime
            str = QString::asprintf("%02d:%02d:%02d",pkt.total_flight_time_s/3600, \
                                                     pkt.total_flight_time_s%3600/60,\
                                                     pkt.total_flight_time_s%60);
            FlightTime[1]->setText(str);
            is_getinfo = true;
            MavID[1]->setText(QString::number(Qt::DMMM()->getFlyLink_main()->get_mav_id()));
            MavIDComBox->setCurrentIndex(MavIDComBox->findData(Qt::DMMM()->getFlyLink_main()->get_mav_id()));
            MavIDComBox->setChanged(false);
        }
        break;
    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
        {
            qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
            if(!is_getinfo && (last_req_ms-tnow) > 1000){
                req_boardinfo();
                last_req_ms = tnow;
            }
        }break;

    default:break;
    }
}

void FCBoardINFO::slot_MavIdChanged(int index)
{
    if(Qt::DMMM()->getFlyLink_main() != nullptr){
        if(MavIDComBox != nullptr){
            bool ok = false;
            uint8_t id = MavIDComBox->currentData().toUInt(&ok);
            if(ok){
                Qt::DMMM()->getFlyLink_main()->set_CommonParameter("SYSID_THISMAV",id);
            }
        }
    }
}
#ifdef GCS_DEBUG_ENABLE
void FCBoardINFO::SaveBoardInfo()
{
    //保存为文件
    QSettings setting("./cfg/Setting.ini", QSettings::IniFormat);  //QSettings能记录一些程序中的信息，下次再打开时可以读取出来
    QString curPath = setting.value("BoradInfo").toString();  //获取上次的打开路径

    if(curPath.isEmpty()){
        curPath=QDir::currentPath();
    }
    //调用打开文件对话框选择一个文件
    QString aFileName=QFileDialog::getSaveFileName(this,QStringLiteral("保存硬件信息"),curPath,
                     QStringLiteral("信息文件(*.csv);;所有文件(*.*)"));

    if (aFileName.isEmpty()){
        Qt::DMMM()->DisplayMsg(QStringLiteral("保存失败，文件名为空"));
        return;
    }

    setting.setValue("BoradInfo",aFileName);  //记录路径到QSetting中保存

    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))){
        Qt::DMMM()->DisplayMsg(QStringLiteral("打开文件失败"));
        return; //以读写、覆盖原有内容方式打开文件
    }

    QTextStream aStream(&aFile); //用文本流读取文件
    // 添加首行
    QString str = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+",";

    if(Qt::DMMM()->getFlyLink_main() != nullptr){
        FlyLink::boardinfo_t pkt  = Qt::DMMM()->getFlyLink_main()->getTDataPort().boardinfo;

        // BoardID
        str +=getFCBoardSimPleString(pkt.boardId)+",";
        // SN
        str += QString::asprintf("20%d-%04d",pkt.boardSN>>16,pkt.boardSN&0xffff);
        str +=",";
        // UUID
        // UUID
        for(int i = 11;;i-- ){
            str += QString::asprintf("%1X",(*((uint8_t*)(&pkt.udid[0])+i))&0xf);
            str += QString::asprintf("%1X",(*((uint8_t*)(&pkt.udid[0])+i))>>4);
            if(i==0)break;
        }
        str +=",";



        // FW_Version
        str += QString::asprintf("%d.%d.%d.%d",pkt.fw_version>>24, \
                                (pkt.fw_version&0xff0000)>>16,  \
                                (pkt.fw_version&0xff00)>>8,\
                                (pkt.fw_version&0xff));
        str +=",";

        // Link_Version
        str += QString::asprintf("%d.%d.%d",pkt.link_version>>12, \
        (pkt.link_version&0xF00)>>8,  \
        (pkt.link_version&0xF0)>>4)+FlyLink::getProtocolType(0xf&pkt.link_version);
    }
    aStream<<str<<"\n";
    aStream.flush();
    aFile.close();
    Qt::DMMM()->DisplayMsg(QStringLiteral("信息保存完成"));
}
#endif
void FCBoardINFO::req_boardinfo()
{
    if(Qt::DMMM()->getFlyLink_main() != nullptr){
        Qt::DMMM()->getFlyLink_main()->req_boardInfo();
    }
}
