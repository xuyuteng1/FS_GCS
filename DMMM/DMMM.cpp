/**=================================================================**
 * @brief       : 原本定义为数据池，现升级为界面与底层协议的连接中间件
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-01-16     Jerry.xl     the first version
 **==================================================================**/
#include "DMMM.h"
#include <QMap>
#include <QtMath>
// 静态成员声明
Q_DMMM *Q_DMMM::singleton = nullptr;

/**===================================================================*
 * @brief      获取 Q_DMMM的指针
 * @param      None
 * @retval     Q_DMMM的指针
 **===================================================================*/
namespace Qt {
    Q_DMMM *DMMM() {
        return Q_DMMM::get_singleton();
    };
};

/**===================================================================*
 * @brief      Q_DMMM的构造函数
 * @param      None
 * @retval     None
 **===================================================================*/
Q_DMMM::Q_DMMM(int gcs_id):
    _gcs_id(gcs_id)
{

    if (singleton != nullptr) {
        qDebug()<<"Q_DMMM must be singleton";
        return;
    }

    map_link.clear();
    singleton = this;
    setMain_link_id(-1);
    _Payload = new PayloadLink(true);
//    RunThread = new QThread();
//    this->moveToThread(RunThread);
//    RunThread->start();
    if(timer_100Hz == nullptr){
        timer_100Hz = new QTimer();
    }
    timer_100Hz->start(10);
    connectSignalAndSlot();
}

/**===================================================================*
 * @brief      Q_DMMM的析构函数
 * @param      None
 * @retval     None
 **===================================================================*/
Q_DMMM::~Q_DMMM()
{
    singleton = nullptr;
    map_link.clear();
    if(RunThread != nullptr){
        if(RunThread->isRunning())
        {
            RunThread->quit();
            RunThread->wait();
        }
        delete RunThread;
    }
}

/**===================================================================*
 * @brief      获取主通信的数据
 * @param      None
 * @retval     DataPool_t
 **===================================================================*/
Q_DMMM::DataPool_t Q_DMMM::getData_main()
{
    return getData(main_link_id);
}

/**===================================================================*
 * @brief      获取通道的数据
 * @param      None
 * @retval     DataPool_t
 **===================================================================*/
Q_DMMM::DataPool_t Q_DMMM::getData(int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        FlyLink* link = map_link.find(linkid).value().link;
        if(link != nullptr){
            map_link.find(linkid).value().data.flylink = link->getTDataPort();
            map_link.find(linkid).value().data.gcs_id =  link->get_gcs_id();
            return map_link.find(linkid).value().data;
        }
    }
    DataPool_t pkt = {};
    return pkt;
}

FlyLink *Q_DMMM::getFlyLink_main()
{
    return getFlyLink(this->getMain_link_id());
}

FlyLink *Q_DMMM::getFlyLink(int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        return map_link.find(linkid).value().link;
    }
    return nullptr;
}

void Q_DMMM::push_msg(const text_msg_t &msg)
{
    QueueMSG.enqueue(msg);
    emit DMMM_Event(DMMM_GCSEvent_new_textmsg,msg.id);
    qDebug()<<msg.id<<":"<<msg.str;
}

bool Q_DMMM::pop_msg(text_msg_t &msg)
{
    if( msg_size() < 1){
        return false;
    }

    msg = QueueMSG.dequeue();
    return true;
}

int Q_DMMM::msg_size()
{
    return QueueMSG.size();
}

bool Q_DMMM::getLocal_mission(FlyLink::mission_local_t & mission,int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        mission =  map_link.find(linkid).value().link->getLocal_mission();
        return true;
    }
    return false;
}

bool Q_DMMM::setLocal_mission(const FlyLink::mission_local_t &newLocal_mission, int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        map_link.find(linkid).value().link->setLocal_mission(newLocal_mission);
        return true;
    }
    return false;
}

bool Q_DMMM::getMission_upload(FlyLink::mission_upload_t &uploadinfo, int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        uploadinfo =  map_link.find(linkid).value().link->getMission_upload();
        return true;
    }
    return false;
}

bool Q_DMMM::getMission_download(FlyLink::mission_download_t &downloadinfo, int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        downloadinfo =  map_link.find(linkid).value().link->getMission_download();
        return true;
    }
    return false;
}

bool Q_DMMM::mission_upload_start(int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        map_link.find(linkid).value().link->app_mission_upload_start();
        return true;
    }

    DisplayMsg(QStringLiteral("上传航线失败:找不到协议对象"));
    return false;
}

bool Q_DMMM::mission_download_start(int linkid)
{
    if(map_link.find(linkid) != map_link.end()){
        map_link.find(linkid).value().link->app_mission_download_start();
        return true;
    }

    DisplayMsg(QStringLiteral("下载航线失败:找不到协议对象"));
    return false;
}

void Q_DMMM::DisplayMsg(const QString &str)
{
    if(Qt::DMMM() != nullptr){
        Q_DMMM::text_msg_t MSG = {};
        MSG.id = getGcs_id();
        MSG.str = str;
        Qt::DMMM()->push_msg(MSG);
    }
}


/**===================================================================*
 * @brief      数据池更新
 * @param      None
 * @retval     None
 **===================================================================*/
void Q_DMMM::update_datapool()
{
    update_data();
}

void Q_DMMM::handle_DMMM_event(int ev, int linkid )
{
    switch(ev){
        case DMMM_GCSEvent_Mission_Upload_Succeed  :
            qDebug()<<"DMMM_GCSEvent_Mission_Upload_Succeed";
        break;
        case DMMM_GCSEvent_Mission_Upload_Failed   :
            qDebug()<<"DMMM_GCSEvent_Mission_Upload_Failed";
        break;
        case DMMM_GCSEvent_Mission_Upload_Item     :
        {
            FlyLink::mission_upload_t uploadinfo = {};
            if(getMission_upload(uploadinfo,linkid)){
                qDebug()<<"DMMM_GCSEvent_Mission_Upload_Item:"<<uploadinfo.progress*100;
            }
        }
        break;

        case DMMM_GCSEvent_Mission_Upload_Item_count     :
            qDebug()<<"DMMM_GCSEvent_Mission_Upload_Item_count";
        break;
        case DMMM_GCSEvent_get_heartbeat           :

        break;

        case DMMM_GCSEvent_Mission_Download_get_item :{
            FlyLink::mission_download_t info = {};
            if(getMission_download(info,linkid)){
                qDebug()<<"DMMM_GCSEvent_Mission_Download_get_item:"<<info.progress*100;
            }
        }
        break;

        case DMMM_GCSEvent_new_textmsg:qDebug()<<"DMMM_GCSEvent_new_textmsg";break;
        case DMMM_GCSEvent_Mission_download_Failed:qDebug()<<"DMMM_GCSEvent_Mission_download_Failed";break;
        case DMMM_GCSEvent_Mission_download_Succeed:qDebug()<<"DMMM_GCSEvent_Mission_download_Succeed";break;
        case DMMM_GCSEvent_Mission_Download_start:qDebug()<<"DMMM_GCSEvent_Mission_Download_start";break;
        case DMMM_GCSEvent_Mission_Download_request_list:qDebug()<<"DMMM_GCSEvent_Mission_Download_request_list";break;
        case DMMM_GCSEvent_Mission_Download_request_item:qDebug()<<"DMMM_GCSEvent_Mission_Download_request_item";break;
        case DMMM_GCSEvent_Mission_Download_get_item_count:qDebug()<<"DMMM_GCSEvent_Mission_Download_get_item_count";break;
        case DMMM_GCSEvent_link_is_no_active:qDebug()<<"DMMM_GCSEvent_link_is_no_active";break;
        case DMMM_GCSEvent_mission_is_uploading:qDebug()<<"DMMM_GCSEvent_mission_is_uploading";break;
        case DMMM_GCSEvent_mission_is_downloading:qDebug()<<"DMMM_GCSEvent_mission_is_downloading";break;
        case DMMM_GCSEvent_Home_received:qDebug()<<"DMMM_GCSEvent_Home_received";break;
        case DMMM_GCSEvent_Origin_received:qDebug()<<"DMMM_GCSEvent_Origin_received";break;

        default:
//            qDebug()<<"event:"<<ev;
        break;
    }
}

void Q_DMMM::handle_close(int linkid)
{
    if(map_link.find(linkid) == map_link.end()){
        return ;
    }
    if(map_link.find(linkid).value().link == nullptr){
        return ;
    }
    FlyLink* temp = map_link.find(linkid).value().link;
    emit temp->CloseProtocolDevice();
    return ;
}

void Q_DMMM::Slot_Timer100Hz()
{
    timer_cnt++;
    if(timer_cnt%10 == 0){
        emit DMMM_Event(DMMM_GCSEvent_Timer_10Hz_Event,-1);
    }
    emit DMMM_Event(DMMM_GCSEvent_Timer_100Hz_Event,-1);
}

int Q_DMMM::getMain_link_id() const
{
    return main_link_id;
}

void Q_DMMM::setMain_link_id(int newMain_link_id)
{
    main_link_id = newMain_link_id;
}

QString Q_DMMM::GetSuitableUnits_Bytes(int byte)
{
    if(qFabs(byte) < 1024){
        return QString::asprintf("%d B",byte);
    }
    else if(qFabs(byte) < 1024*1024){
        return QString::asprintf("%.2f KB",byte/(float)1024);
    }
    else{
        return QString::asprintf("%.2f MB",byte/(float)(1024*1024));
    }
}

int Q_DMMM::getGcs_id() const
{
    return _gcs_id;
}

void Q_DMMM::setGcs_id(int newGcs_id)
{
    _gcs_id = newGcs_id;
}

QList<int> Q_DMMM::getLinksID()
{
    return this->map_link.keys();
}

/**===================================================================*
 * @brief      依据MAP更新数据
 * @param      None
 * @retval     None
 **===================================================================*/
void Q_DMMM::update_data()
{
    QMap<int,map_data_t>::Iterator ite = map_link.begin();
    while(ite != map_link.end()){
        if(ite.value().link != nullptr){
            FlyLink* link = ite.value().link;
            ite.value().data.flylink = link->getTDataPort();
            ite.value().data.gcs_id =  link->get_gcs_id();
        }
        ite++;
    }
}

void Q_DMMM::connectSignalAndSlot()
{
    connect(this,&Q_DMMM::DMMM_Event,this,&Q_DMMM::handle_DMMM_event);
    connect(this, &Q_DMMM::close,this,&Q_DMMM::handle_close);
    connect(this->timer_100Hz, &QTimer::timeout,this,&Q_DMMM::Slot_Timer100Hz);
}

PayloadLink *Q_DMMM::Payload() const
{
    return _Payload;
}

void Q_DMMM::open(QMap<QString,QVariant>map, int linkid)
{
    if(map_link.find(linkid) == map_link.end()){
        map_data_t pkt{};
        pkt.link = new FlyLink(nullptr,1,true);
        if(pkt.link != nullptr){
            pkt.link->setIdentity(linkid);
        }
        emit pkt.link->OpenProtocolDevice(map);
        map_link.insert(linkid,pkt);
        setMain_link_id(linkid);
        return;
    }
    else{
        if(map_link.find(linkid).value().link == nullptr){
            map_link.find(linkid).value().link = new FlyLink(nullptr,1,true);
            return;
        }
        emit map_link.find(linkid).value().link->OpenProtocolDevice(map);
        setMain_link_id(linkid);
    }
}



bool Q_DMMM::getLinkActive(int linkid)
{
    if(map_link.find(linkid) == map_link.end()){
        return false;
    }

    if(map_link.find(linkid).value().link == nullptr){
        return false;
    }
    map_link.find(linkid).value().link->getIs_active();
    return true;
}
