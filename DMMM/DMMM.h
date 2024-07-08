/**=================================================================**
 * @brief       : 数据消息管理模块（Data Message Management Module）
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-20     Jerry.xl     the first version
 **==================================================================**/
#ifndef DATA_MESSAGE_MANAGEMENT_MODULE_H
#define DATA_MESSAGE_MANAGEMENT_MODULE_H
#include <QDebug>
#include <QTimer>
#include <QQueue>
#include "PayloadLink.h"
#include "FlyLink.h"


class Q_DMMM : public QObject
{
    Q_OBJECT
public:
    /*--------------构造/析构函数--------------*/
    Q_DMMM(int gcs_id = -1);
    ~Q_DMMM();
    /*--------------结构体、枚举定义--------------*/
    typedef struct{
        FlyLink::DataPort_t flylink;
        uint8_t gcs_id;
    }DataPool_t;
    enum Q_DMMM_YJYEvent{
        DMMM_GCSEvent_Mission_Upload_Succeed = 0,
        DMMM_GCSEvent_Mission_Upload_Failed,
        DMMM_GCSEvent_Mission_Upload_Item,
        DMMM_GCSEvent_Mission_Upload_Item_count,
        DMMM_GCSEvent_new_textmsg,
        DMMM_GCSEvent_get_heartbeat,
        DMMM_GCSEvent_Mission_download_Failed,
        DMMM_GCSEvent_Mission_download_Succeed,
        DMMM_GCSEvent_Mission_Download_start,
        DMMM_GCSEvent_Mission_Download_request_list,
        DMMM_GCSEvent_Mission_Download_request_item,
        DMMM_GCSEvent_Mission_Download_get_item_count,
        DMMM_GCSEvent_Mission_Download_get_item,
        DMMM_GCSEvent_link_is_no_active,
        DMMM_GCSEvent_mission_is_uploading,
        DMMM_GCSEvent_mission_is_downloading,
        DMMM_GCSEvent_Home_received,
        DMMM_GCSEvent_Home_FirstReceived,
        DMMM_GCSEvent_firstAvailiablePos,
        DMMM_GCSEvent_Origin_received,
        DMMM_GCSEvent_RTL_Waypoint_received,
        DMMM_GCSEvent_Protocol_Actived,
        DMMM_GCSEvent_Protocol_lost,
        DMMM_GCSEvent_device_write_buf,
        DMMM_GCSEvent_Acc3DCaliPostion,
        DMMM_GCSEvent_MagCaliProgress,
        DMMM_GCSEvent_MagCountChanged,
        DMMM_GCSEvent_frameChanged,
        DMMM_GCSEvent_GetMotorVal,
        /* parameters */
        DMMM_GCSEvent_GetParamFailsafe,
        DMMM_GCSEvent_GetParamMainRC,
        DMMM_GCSEvent_GetParamAuxRC,
        DMMM_GCSEvent_GetParamMotors,
        DMMM_GCSEvent_GetGNSSPostion,
        DMMM_GCSEvent_GetBoardOrientation,
        DMMM_GCSEvent_GetParamInitCtrlCfg,
        DMMM_GCSEvent_GetParamPilotCtrl,
        DMMM_GCSEvent_GetParamAutoCtrl,
        DMMM_GCSEvent_GetParamRollCtrl,
        DMMM_GCSEvent_GetParamPitchCtrl,
        DMMM_GCSEvent_GetParamYawCtrl,
        DMMM_GCSEvent_GetParamPosZCtrl,
        DMMM_GCSEvent_GetParamPosXYCtrl,
        DMMM_GCSEvent_GetParamSerialPortOption,
        DMMM_GCSEvent_GetCommonParameter,

        DMMM_GCSEvent_GetBoardInfo,
        DMMM_GCSEvent_MavIDChanged,

        /* flight log */
        DMMM_GCSEvent_log_reqlist_failed,
        DMMM_GCSEvent_log_getLogInfo,
        DMMM_GCSEvent_log_getLogList,

        DMMM_GCSEvent_log_reqdata_failed,
        DMMM_GCSEvent_log_getLogData,      // 获取到日志一帧数据
        DMMM_GCSEvent_log_getLogFile,      // 获取到一个完整日志
        DMMM_GCSEvent_log_getLogAll,       // 全部下载完成

        /* flight log */
        DMMM_GCSEvent_ComDeviceErr,       // 通信设备出错，指得是串口、UDP等连接出现错误
        DMMM_GCSEvent_DeviceOpenSucceed,  // 通信设备连接成功
        DMMM_GCSEvent_DeviceOpenFailed,  // 通信设备连接成功

        /* PayLoad Link */
        DMMM_GCSEvent_JoinMulticastGroup_Succeed,
        DMMM_GCSEvent_JoinMulticastGroup_Failed,
        /* TimerOut  */
        DMMM_GCSEvent_Timer_10Hz_Event,
        DMMM_GCSEvent_Timer_100Hz_Event,
         /* NewVihecle  */
        DMMM_GCSEvent_NewVehicleType,
    };
    typedef struct{
        int         id;
        QString     str;
    }text_msg_t;

    /*--------------外部访问接口----------------*/
    static Q_DMMM* get_singleton(void){
            return singleton;
    }

/// ===============================================================================
/// 应用接口
/// =================================================================================
    /*--------------遥测数据访问接口----------------*/
    DataPool_t getData_main();
    DataPool_t getData(int linkid = 0);

    /*--------------协议对象指针获取----------------*/
    FlyLink* getFlyLink_main();
    FlyLink* getFlyLink(int linkid = 0);

    /*--------------通信设备控制接口----------------*/
    void open(QMap<QString,QVariant>,int linkid = 0);
    bool getLinkActive(int linkid = 0);
    /*--------------消息队列接口----------------*/
    void push_msg(const text_msg_t &msg);
    bool pop_msg(text_msg_t &msg);
    int  msg_size();
    /*--------------任务访问接口----------------*/
    bool getLocal_mission(FlyLink::mission_local_t & mission,int linkid = 0);
    bool setLocal_mission(const FlyLink::mission_local_t &newLocal_mission,int linkid = 0);
    bool getMission_upload(FlyLink::mission_upload_t& uploadinfo,int linkid = 0);
    bool getMission_download(FlyLink::mission_download_t& downloadinfo,int linkid = 0);
    bool mission_upload_start(int linkid = 0);
    bool mission_download_start(int linkid = 0);

    /*--------------本地消息显示（代表地面自己）----------------*/
    void DisplayMsg(const QString &str);
    int  getGcs_id() const;
    void setGcs_id(int newGcs_id);

    QList<int> getLinksID();
    int  getMain_link_id() const;
    void setMain_link_id(int newMain_link_id);

    static QString GetSuitableUnits_Bytes(int byte);

signals:
    /*--------------信号----------------*/
//    void DMMM_Event(int ev,int linkid = 0);
    void DMMM_Event(int ev,int linkid = 0,QVariant var = {0});
    void replayDataWriteSignal(int linkid,QDateTime time,QByteArray array);
    /*--------------槽函数----------------*/
public slots:
    void update_datapool();
    void handle_DMMM_event(int ev,int linkid = 0);
    void handle_close(int linkid);
    void Slot_Timer100Hz();
public :
    PayloadLink *Payload() const;
signals:
    void close(int linkid);
private:
    /*--------------私有成员变量----------------*/
    typedef struct{
        FlyLink*        link;
        DataPool_t      data;
    }map_data_t;
    QMap<int,map_data_t> map_link  = {};

    int main_link_id = -1;
    static Q_DMMM *singleton;
    QQueue<text_msg_t> QueueMSG;
    int _gcs_id;
    /*--------------私有成员函数----------------*/
    void update_data();
    void connectSignalAndSlot();

    PayloadLink* _Payload = nullptr;
    QTimer      *timer_100Hz = nullptr;
    quint64     timer_cnt = 0;
    QThread*        RunThread = nullptr;
};


/*--------------作用域声明----------------*/
namespace Qt {
    Q_DMMM *DMMM();

};
#endif // DATA_POOL_H
