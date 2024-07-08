/**=================================================================**
 * @brief       : 数据消息管理模块（Data Message Management Module）
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-20     Jerry.xl     the first version
 **==================================================================**/
#ifndef DATA_MESSAGE_MANAGEMENT_MODULE_H
#define DATA_MESSAGE_MANAGEMENT_MODULE_H
#include <QObject>
#include <QDebug>
#include <QTimer>
#include "YJYProtocol.h"
class Q_DMMM : public QObject
{
    Q_OBJECT
public:
    enum Q_DMMM_YJYEvent{
        DMMM_YJYEvent_OpenSerialPort_Succeed = 0,
        DMMM_YJYEvent_OpenSerialPort_Failed,
        DMMM_YJYEvent_SerialPort_Error,
        DMMM_YJYEvent_BindSocketUDP_Succeed,
        DMMM_YJYEvent_BindSocketUDP_Failed,
        DMMM_YJYEvent_JoinMulticastGroup_Succeed,
        DMMM_YJYEvent_JoinMulticastGroup_Failed,
        DMMM_YJYEvent_SocketUDP_Error,

        DMMM_YJYEvent_Ptl_Update,
        DMMM_YJYEvent_Timer10Hz,
    };
    /*--------------构造/析构函数--------------*/
    Q_DMMM();
    ~Q_DMMM();
    /*--------------外部访问接口----------------*/
    static Q_DMMM* get_singleton(void){
            if(singleton ==nullptr){
                singleton = new Q_DMMM();
            }
            return singleton;
    }
    void DMMM_Event(quint16,qint16 a = 0,qint16 b = 0);
signals:
    void Signal_DMMM_Event(quint16,qint16 a = 0,qint16 b = 0);
private slots:
    void Slot_DMMM_Event(quint16 event,qint16,qint16 );
private:
    static Q_DMMM *singleton;
    QTimer _Timer10Hz;
////////////////////////////////////////////////////////////////////
/// 此部分为用户自定义数据接口部分
////////////////////////////////////////////////////////////////////
public:
    YJYProtocol *getYJYPtl() const;
    YJYProtocol::SeekerYJY_State_t getYJYPtlState()const;
public:
    YJYProtocol* YJYPtl = nullptr;
};


/*--------------作用域声明----------------*/
namespace Qt {
    Q_DMMM *DMMM();
};
#endif // DATA_POOL_H
