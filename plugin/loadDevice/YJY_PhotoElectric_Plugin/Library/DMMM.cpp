/**=================================================================**
 * @brief       : 数据消息管理模块（Data Message Management Module）
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-20     Jerry.xl     the first version
 **==================================================================**/
#include "DMMM.h"

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
Q_DMMM::Q_DMMM()
{
    if (singleton != nullptr) {
        qDebug()<<"Q_DMMM must be singleton";
        return;
    }
    singleton = this;
    connect(this,&Q_DMMM::Signal_DMMM_Event,this,&Q_DMMM::Slot_DMMM_Event);
    YJYPtl = new YJYProtocol(true);
    _Timer10Hz.start(100);
    connect(&this->_Timer10Hz,&QTimer::timeout,this,[=]{DMMM_Event(Q_DMMM::DMMM_YJYEvent_Timer10Hz);});
}

/**===================================================================*
 * @brief      Q_DMMM的析构函数
 * @param      None
 * @retval     None
 **===================================================================*/
Q_DMMM::~Q_DMMM()
{
    singleton = nullptr;
}

void Q_DMMM::DMMM_Event(quint16 ev, qint16 a, qint16 b)
{
    emit Signal_DMMM_Event(ev,a,b);
}

void Q_DMMM::Slot_DMMM_Event(quint16 event, qint16 a, qint16 b)
{
//    qDebug()<<"Slot_DMMM_Event"<<event<<a<<b;
}

YJYProtocol *Q_DMMM::getYJYPtl() const
{
    return YJYPtl;
}

YJYProtocol::SeekerYJY_State_t Q_DMMM::getYJYPtlState() const
{
    YJYProtocol::SeekerYJY_State_t state{};
    if(YJYPtl != nullptr){
        state = YJYPtl->getState();
    }
    return state;
}
