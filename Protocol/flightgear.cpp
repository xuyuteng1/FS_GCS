/**=================================================================**
 * @brief       : FlightGear_Link通信协议部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-01-16     Jerry.xl     the first version
 **==================================================================**/
#include "flightgear.h"
#include "DMMM.h"
#include <QtGlobal>
#include <QDateTime>
#include <QDate>
#include <QDir>
#include <QtCore/qmath.h>
#include <QByteArray>
#include <QtEndian>
#include "AP_Math.h"
/**===================================================================*
 * @brief      FlightGear_Link 析构函数
 * @param      None
 * @retval     None
 **===================================================================*/
FlightGear_Link::FlightGear_Link(QObject *parent, bool IndependentThread):
    DeviceCommunication(IndependentThread)
{

    Q_UNUSED(parent);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&FlightGear_Link::handle_DMMM_event);
}

FlightGear_Link::~FlightGear_Link()
{

}

void FlightGear_Link::Open()
{
    QMap<QString,QVariant>openMap{};
    // 依据类型传入参数

    openMap[STR_SocketUDP] = QVariant::fromValue(QHostAddress("127.0.0.1"));
    openMap[STR_SocketUDP_Port] = QVariant::fromValue(1000);
    openMap[STR_SocketUDP_TargetIP] = QVariant::fromValue(QHostAddress("127.0.0.1"));
    openMap[STR_SocketUDP_TargetPort] = QVariant::fromValue(5503);
    emit OpenProtocolDevice(openMap);
    this->setIdentity(FlightGearLinkID);
}

void FlightGear_Link::Close()
{
    emit CloseProtocolDevice();
}

void FlightGear_Link::_output_to_flightgear()
{
    if(getE_DeviceState()!=DeviceState_Connect){
        return;
    }

    FGNetFDM fdm = {};
    fdm.version = 0x18;
    fdm.padding = 0;

    Q_DMMM::DataPool_t data = Qt::DMMM()->getData_main();
    fdm.longitude = (double)DEG_TO_RAD_DOUBLE * (double)data.flylink.tVehicle.lng*(double)1e-7;//DEG_TO_RAD_DOUBLE*sfdm.longitude;
    fdm.latitude = (double)DEG_TO_RAD_DOUBLE * (double)data.flylink.tVehicle.lat*(double)1e-7;
    fdm.altitude = data.flylink.tVehicle.alt_m;
    fdm.agl = data.flylink.tVehicle.alt_m;
    fdm.phi   = DEG_TO_RAD*(data.flylink.tVehicle.roll_cd*0.01f);
    fdm.theta = DEG_TO_RAD*(data.flylink.tVehicle.pitch_cd*0.01f);
    fdm.psi   = DEG_TO_RAD*(data.flylink.tVehicle.yaw_cd*0.01f);

    if(data.flylink.VehicleType == FlyLink::VehicleType_e::VehicleType_Copter){
        fdm.num_engines = 4;
        for (uint8_t i=0; i<4; i++) {
            fdm.rpm[i] = data.flylink.tRC_OUT.out[i]-1000;
        }
    } else {
        fdm.num_engines = 4;
        fdm.rpm[0] = (data.flylink.tRC_OUT.out[2]-1000)*3;
        // for quadplane
        fdm.rpm[1] = (data.flylink.tRC_OUT.out[5]-1000)*12;
        fdm.rpm[2] = (data.flylink.tRC_OUT.out[6]-1000)*12;
        fdm.rpm[3] = (data.flylink.tRC_OUT.out[7]-1000)*12;
    }
    fdm.ByteSwap();

    this->write((char*)&fdm, sizeof(fdm));
}


void FGNetFDM::ByteSwap()
{
    uint32_t *buf = (uint32_t *)this;
    for (uint16_t i=0; i<sizeof(*this)/4; i++) {
//        buf[i] = ntohl(buf[i]);

        buf[i] = qToBigEndian(buf[i]);
    }
    // fixup the 3 doubles
    buf = (uint32_t *)&longitude;
    uint32_t tmp;
    for (uint8_t i=0; i<3; i++) {
        tmp = buf[0];
        buf[0] = buf[1];
        buf[1] = tmp;
        buf += 2;
    }
}


void FlightGear_Link::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_Timer_100Hz_Event:
        {
            _output_to_flightgear();
        }break;

    default:break;
    }
}
