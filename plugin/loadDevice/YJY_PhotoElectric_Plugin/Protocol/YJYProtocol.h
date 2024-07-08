/**=================================================================**
 * @brief       : YJY 导引头协议
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-28     Jerry.xl     the first version
 **==================================================================**/
#ifndef YJYProtocol_H__
#define YJYProtocol_H__

#include <QMetaType>
#include <QWaitCondition>
#include <QThread>
#include <QDebug>
#include <QMutexLocker>
#include <QDebug>
#include <QTimer>
#include "DeviceCommunication.h"
#define SEEKERYJY_HEADER0          (uint8_t)0x55
#define SEEKERYJY_HEADER1          (uint8_t)0xAA
#define SEEKERYJY_MAX_BUF_LEN      (100)
class YJYProtocol:public DeviceCommunication
{
    Q_OBJECT
public:
    YJYProtocol(bool IndependentThread = false);
    ~YJYProtocol();
    ////////////////////////////////////////////////////////////////////////
public:
    typedef enum{
        CMD_GateWaveIncrement   = 0xC1,
        CMD_GateWaveMovePos     = 0xC2,
        CMD_TrackPointRepair  = 0xC3,

        CMD_LockTarget          = 0xE1,

        CMD_P_in_PSwitch        = 0xB1,
        CMD_SensorSwitch        = 0xB2,
        CMD_FieldViewSwitch     = 0xB3,

        CMD_TargetTypePlus      = 0x62,
        CMD_TargetTypeGeneral   = 0x63,
        CMD_TargetTypeCar       = 0x64,
    }eControlCommand;
/*=======================================================================*/
#pragma pack(push)
#pragma pack (1)//单字节对齐
/*=================== 数据结构定义，详细请参照协议文档 ====================*/
    typedef struct {
        uint8_t         selfcheckInfo;
        uint8_t         WorkState;
        int16_t         PitchErr_cd;
        int16_t         YawErr_cd;
        int16_t         WaveGatePos_x;
        int16_t         WaveGatePos_y;
        int16_t         WaveGateSize_x;
        int16_t         WaveGateSize_y;
        uint8_t         TrackingResponsivity;
        int16_t         Pitch_cd;
        int16_t         Roll_cd;
        uint16_t        Yaw_cd;
        int16_t         bodyRateX_cdps;
        int16_t         bodyRateY_cdps;
        int16_t         bodyRateZ_cdps;
        uint16_t        FocalLength;
        uint16_t        TargetSize;
        uint8_t         BottomView;
        uint8_t         reserved[8];
    }SeekerYJY_State_t;

    typedef struct PACKED{
        uint8_t         ControlCMD;
        int16_t         GateWaveLRRange;
        int16_t         GateWaveUDRange;
        uint8_t         AttackState;
        int16_t         Pitch_cd;
        int16_t         Roll_cd;
        int16_t         Yaw_cd;
        int16_t         bodyRateX_cdps;
        int16_t         bodyRateY_cdps;
        int16_t         bodyRateZ_cdps;
        uint8_t         reserved[8];
    }SeekerYJY_Command_t;

#pragma pack(pop)//恢复对齐状态

    ////////////////////////////////////////////////////////////////////////
public:
    bool    SendControlPacket(SeekerYJY_Command_t ControlCMD);
    bool    SendCMD_GateWaveIncrement(int16_t x,int16_t y);
    bool    SendCMD_GateWaveMovePos(int16_t x,int16_t y);
    bool    SendCMD_TrackPointRepair (int16_t x,int16_t y);

    bool    SendCMD_GateWaveMovePos(uint8_t cmd);

    bool    SendCMD_LockTarget       (){return SendCMD_GateWaveMovePos(CMD_LockTarget       );};
    bool    SendCMD_P_in_PSwitch     (){return SendCMD_GateWaveMovePos(CMD_P_in_PSwitch     );};
    bool    SendCMD_SensorSwitch     (){return SendCMD_GateWaveMovePos(CMD_SensorSwitch     );};
    bool    SendCMD_FieldViewSwitch  (){return SendCMD_GateWaveMovePos(CMD_FieldViewSwitch  );};
    bool    SendCMD_TargetTypePlus   (){return SendCMD_GateWaveMovePos(CMD_TargetTypePlus   );};
    bool    SendCMD_TargetTypeGeneral(){return SendCMD_GateWaveMovePos(CMD_TargetTypeGeneral);};
    bool    SendCMD_TargetTypeCar    (){return SendCMD_GateWaveMovePos(CMD_TargetTypeCar    );};

    const SeekerYJY_State_t &getState() const;

public slots:
    void SlotReadData();
private:
    uint8_t DecodeByte(uint8_t c);
private:

    // 协议解析相关变量
    uint8_t             _step = 0;
    uint16_t            recv_count = 0;         // amount of bytes received
    uint16_t            frame_len = 0;         // amount of bytes received
    uint8_t             check_sum = 0;          //checksum
    uint8_t             revBuf [SEEKERYJY_MAX_BUF_LEN];
    uint32_t            last_update_ms;
    SeekerYJY_State_t   state{};
    bool                is_read = false;
    QMutex              _data_mutex; // 数据发送互斥量
};


#endif // NETWORK_UDP_H
