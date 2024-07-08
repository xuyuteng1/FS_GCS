/**=================================================================**
 * @brief       : 通用设备通信类：支持串口、UDP连接
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-28     Jerry.xl     the first version
 **==================================================================**/
#ifndef DEVICE_COMMUNICATION_H__
#define DEVICE_COMMUNICATION_H__

#include <QUdpSocket>
#include <QTcpSocket>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMap>
#include <QString>
#include <QThread>
#include <QWidget>

#define STR_SerialPort                  "SerialPortName"
#define STR_SerialPort_DataBit          "SerialPort_DataBit"
#define STR_SerialPort_StopBit          "SerialPort_StopBit"
#define STR_SerialPort_Parity           "SerialPort_Parity"
#define STR_SerialPort_baudRate         "SerialPort_baudRate"

#define STR_SocketUDP                   "SocketUDP_IP"
#define STR_SocketUDP_Port              "SocketUDP_Port"
#define STR_SocketUDP_TargetIP          "SocketUDP_TargetIP"
#define STR_SocketUDP_TargetPort        "SocketUDP_TargetPort"
class DeviceCommunication:public QObject
{
    Q_OBJECT
public:
    DeviceCommunication(bool StartIndependentThread = false);
    ~DeviceCommunication();

    typedef enum{
        DeviceType_None = 0,
        DeviceType_SerialPort,
        DeviceType_NetUDP,
    }DeviceType_e;

    typedef enum{
        DeviceState_DisConnect = 0,
        DeviceState_Connect,
        DeviceState_Error
    }DeviceState_e;

////////////////////////////////////////////////////////////////////////
/// 开放接口
////////////////////////////////////////////////////////////////////////
public:
    DeviceType_e getE_DeviceType() const;
    DeviceState_e getE_DeviceState() const;
    int     getIdentity() const;
    void    setIdentity(int newIdentity);
signals:
    /**===================================================================*
     * @brief      打开设备类，传入参数为QMap
     * @param      QMap<QString,QVariant>
     * @retval     None
     **===================================================================*/
    void OpenProtocolDevice(QMap<QString,QVariant>);
    void CloseProtocolDevice();
    void readyRead();
////////////////////////////////////////////////////////////////////////
protected:
    qint64 write      (const char *buffer, qint64 size);
    qint64 write      (QByteArray data);
    qint64 read       (char *buffer, qint64 count);
    QByteArray read       (qint64 maxsize = -1);
    qint64 available  ()const ;
    void   ProtocolEvent(int ev);
private:
signals:
    void Signal_write(QVariant data);
private slots:
    void Slot_OpenProtocolDevice(QMap<QString,QVariant>);
    void Slot_CloseProtocolDevice();
    void Slot_write(QVariant data);
    void Slot_serial_error(QSerialPort::SerialPortError error);
    void Slot_udpsocket_error(QAbstractSocket::SocketError error);
private:
    /*-------------- SerialPort读写函数 ----------------*/
    qint64 write_serial(QByteArray data);
    QByteArray read_serial(qint64 maxsize = -1);
    qint64 available_serial() const ;
    /*-------------- UDP读写函数 ----------------*/
    qint64 write_UDP(QByteArray data);
    QByteArray read_UDP(qint64 maxsize = -1);
    qint64 available_UDP() const ;


private:
    QSerialPort*   DeviceSerialport = nullptr;
    struct{
        QUdpSocket*    port = nullptr;
        QHostAddress   Sourse_addr;
        quint16        Sourse_port;
    }Device_UDPSocket;
    QMap<QString,QVariant> DeviceInfo;
    DeviceType_e    e_DeviceType;
    DeviceState_e   e_DeviceState;
    QThread*        RunThread = nullptr;
    int             identity;
};
Q_DECLARE_METATYPE(QHostAddress);

#endif // NETWORK_UDP_H
