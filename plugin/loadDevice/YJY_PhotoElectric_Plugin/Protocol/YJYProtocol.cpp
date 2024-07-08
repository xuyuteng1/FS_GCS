/**=================================================================**
 * @brief       : YJY 导引头协议
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-28     Jerry.xl     the first version
 **==================================================================**/
#include "YJYProtocol.h"
#include <QDateTime>
#include "DMMM.h"
YJYProtocol::YJYProtocol(bool IndependentThread):
    DeviceCommunication(IndependentThread)
{
    _step = 0;
    connect(this,&YJYProtocol::readyRead,this,&YJYProtocol::SlotReadData);
}


YJYProtocol::~YJYProtocol()
{

}

uint8_t YJYProtocol::DecodeByte(uint8_t c)
{
    switch(_step){
        case 1:
            if(c == SEEKERYJY_HEADER1){
                check_sum += c;
                recv_count++;
                _step++;
                break;
            }
            _step = 0;
//            [[fallthrough]];

        case 0:
            check_sum = 0;
            recv_count = 0;
            if(c == SEEKERYJY_HEADER0){
                check_sum += c;
                recv_count++;
                _step++;
            }
            break;
        // 接收数据长度
        case 2:
            frame_len = c;
            check_sum += c;
            recv_count++;
            // frame len 整个包长
            if(frame_len == 0x2C){
                _step ++;
                break;
            }
            _step = 0;
            break;
        // 接收数据
        case 3:
            // 数据接收
            check_sum += c;
            recv_count++;
            revBuf[recv_count-4] = c;
            // 数据接收完成
            if(recv_count >= frame_len-1){
                _step++;
            }
            break;
        // 接收ChkSum
        case 4:
            if(check_sum == c){
                // 校验通过,处理数据
                memcpy(&state,revBuf,sizeof(state));
                last_update_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
                Qt::DMMM()->DMMM_Event(Q_DMMM::Q_DMMM_YJYEvent::DMMM_YJYEvent_Ptl_Update);
            }
            else{
                qDebug()<<"checksum err"<<check_sum<<c;
            }
            _step = 0;
            break;
        default:break;
    }
    return _step;
}

const YJYProtocol::SeekerYJY_State_t &YJYProtocol::getState() const
{
    return state;
}

bool YJYProtocol::SendControlPacket(SeekerYJY_Command_t ControlCMD)
{
    uint8_t datalen = sizeof(SeekerYJY_Command_t);
    QMutexLocker locker(&_data_mutex);
    QByteArray sendbuf;
    sendbuf.resize(4+datalen);
    uint8_t U8_Cnt = 0;
    uint8_t U8_CheckSum = 0;
    if(datalen + 4 > SEEKERYJY_MAX_BUF_LEN) return false;
    sendbuf[0] = 0xAA;
    sendbuf[1] = 0x55;
    sendbuf[2] = 0X1E;
    memcpy(sendbuf.data()+3,&ControlCMD,datalen);
    for(U8_Cnt = 0; U8_Cnt < datalen + 3;U8_Cnt++){
        U8_CheckSum += sendbuf.at(U8_Cnt);
    }
    sendbuf[3+datalen] = U8_CheckSum;
    write(sendbuf);
    return true;
}

bool YJYProtocol::SendCMD_GateWaveIncrement(int16_t x, int16_t y)
{
    SeekerYJY_Command_t pkt {};
    pkt.ControlCMD = CMD_GateWaveIncrement;
    pkt.GateWaveLRRange = x;
    pkt.GateWaveUDRange = y;
    return SendControlPacket(pkt);
}

bool YJYProtocol::SendCMD_GateWaveMovePos(int16_t x, int16_t y)
{
    SeekerYJY_Command_t pkt {};
    pkt.ControlCMD = CMD_GateWaveMovePos;
    pkt.GateWaveLRRange = x;
    pkt.GateWaveUDRange = y;
    return SendControlPacket(pkt);
}

bool YJYProtocol::SendCMD_TrackPointRepair(int16_t x, int16_t y)
{
    SeekerYJY_Command_t pkt {};
    pkt.ControlCMD = CMD_TrackPointRepair;
    pkt.GateWaveLRRange = x;
    pkt.GateWaveUDRange = y;
    return SendControlPacket(pkt);
}

bool YJYProtocol::SendCMD_GateWaveMovePos(uint8_t cmd)
{
    SeekerYJY_Command_t pkt {};
    pkt.ControlCMD = cmd;
    return SendControlPacket(pkt);
}

void YJYProtocol::SlotReadData()
{
    if(is_read)
    {
        return;
    };

    is_read = true;
    /* 处理收到的数据，按照协议进行帧解析 */
    qint64 nbytes = available();
    if(0 >= nbytes){
        is_read = false;
        return;
    }
    QByteArray recBuf{};
    recBuf = read(nbytes);


    for(int i = 0 ; i <nbytes;i++ ){
        uint8_t b = (uint8_t)recBuf[i];
        DecodeByte(b);
    }
    is_read = false;
}
