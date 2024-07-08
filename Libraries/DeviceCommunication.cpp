/**=================================================================**
 * @brief       : YJY 导引头协议,支持串口、UDP连接
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-28     Jerry.xl     the first version
 **==================================================================**/
#include "DeviceCommunication.h"
#include <QDateTime>
#include <QNetworkInterface>
#include <QNetworkDatagram>
#include "DMMM.h"

DeviceCommunication::DeviceCommunication(bool StartIndependentThread):
    QObject()
{
    if(StartIndependentThread){
        RunThread = new QThread();
        this->moveToThread(RunThread);
        RunThread->start();
    }
    DeviceInfo.clear();
    connect(this,&DeviceCommunication::Signal_write,this,&DeviceCommunication::Slot_write);
    connect(this,&DeviceCommunication::OpenProtocolDevice,this,&DeviceCommunication::Slot_OpenProtocolDevice);
    connect(this,&DeviceCommunication::CloseProtocolDevice,this,&DeviceCommunication::Slot_CloseProtocolDevice);
    qDebug()<<"DeviceCommunication"<<this->thread();

}

DeviceCommunication::~DeviceCommunication()
{
    if(RunThread != nullptr){
        if(RunThread->isRunning())
        {
            RunThread->quit();
            RunThread->wait();
        }
        delete RunThread;
    }
}

qint64 DeviceCommunication::write(const char *buffer, qint64 size)
{
    if(size <= 0){
        return size;
    }
    QByteArray arr;
    arr.resize(size);
    memcpy(arr.data(),buffer,size);
    return write(arr);
}

qint64 DeviceCommunication::write(QByteArray data)
{
    if(data.isEmpty()) return -1;
    QVariant arr = QVariant::fromValue(data);
    emit Signal_write(arr);

    return data.size();
}

qint64 DeviceCommunication::read(char *buffer, qint64 count)
{
    if(count <= 0) return count;
    QByteArray arr = read(count);
    if(arr.isEmpty()) return -1;
    memcpy(buffer,arr.constData(),arr.size());
    return arr.size();
}

QByteArray DeviceCommunication::read(qint64 maxsize)
{
    QByteArray arr;
    arr.clear();
    switch(e_DeviceType){
        case DeviceType_SerialPort:
            arr =  read_serial(maxsize);
        break;
        case DeviceType_NetUDP:
            arr = read_UDP(maxsize);
        break;
    default:
        break;
    }
    return arr;
}

qint64 DeviceCommunication::available() const
{
    switch(e_DeviceType){
        case DeviceType_SerialPort:
            return available_serial();
        break;
        case DeviceType_NetUDP:
            return available_UDP();
        break;
    default:
        break;
    }
    return 0;
}

void DeviceCommunication::ProtocolEvent(int ev, QVariant var)
{
    if(Qt::DMMM() != nullptr){
        emit Qt::DMMM()->DMMM_Event(ev,getIdentity(),var);
    }
}

void DeviceCommunication::Slot_CloseProtocolDevice()
{
    switch(e_DeviceType){
        case DeviceType_SerialPort:
        if(DeviceSerialport  != nullptr){
            if(DeviceSerialport->isOpen()){
                DeviceSerialport->close();
            }
        }
        break;

        case DeviceType_NetUDP:
        if(Device_UDPSocket.port  != nullptr){
            Device_UDPSocket.port->close();
        }
        break;
        default:break;
    }
    e_DeviceType = DeviceType_None;
    e_DeviceState = DeviceState_DisConnect;
    DeviceInfo.clear();
    qDebug()<<"Slot_CloseProtocolDevice";
}

void DeviceCommunication::Slot_write(QVariant data)
{
    QByteArray arr = data.value<QByteArray>();
    switch(e_DeviceType){
        case DeviceType_SerialPort:
            write_serial(arr);
            return;
        break;

        case DeviceType_NetUDP:
            write_UDP(arr);
            return;
        break;
    default:
        break;
    }
}

qint64 DeviceCommunication::write_serial(QByteArray data)
{
    if(data.isEmpty()){
        return -1;
    }
    if(DeviceSerialport != nullptr){
        if(DeviceSerialport->isWritable()){
            return DeviceSerialport->write(data);
        }
    }
    return -1;
}

QByteArray DeviceCommunication::read_serial(qint64 maxsize)
{
    if(DeviceSerialport != nullptr){
        if(DeviceSerialport->isOpen()){
            return DeviceSerialport->read(maxsize);
        }
    }
    QByteArray arr;
    arr.clear();
    return arr;
}

qint64 DeviceCommunication::available_serial() const
{
    if(DeviceSerialport != nullptr){
        if(DeviceSerialport->isReadable())
        return (DeviceSerialport->bytesAvailable()<0)?0:DeviceSerialport->bytesAvailable();
    }
    return 0;
}

qint64 DeviceCommunication::write_UDP(QByteArray data)
{
    if(Device_UDPSocket.port != nullptr){
        QHostAddress add = Device_UDPSocket.Sourse_addr;
        quint16 port = Device_UDPSocket.Sourse_port;
        if(DeviceInfo.contains(STR_SocketUDP_TargetIP)){
            add =  DeviceInfo.find(STR_SocketUDP_TargetIP).value().value<QHostAddress>();
        }
        if(DeviceInfo.contains(STR_SocketUDP_TargetPort)){
            port =  DeviceInfo.find(STR_SocketUDP_TargetPort).value().value<quint16>();
        }
        QNetworkDatagram netData(data,add,port);
        return Device_UDPSocket.port->writeDatagram(netData);
    }

    return -1;
}

QByteArray DeviceCommunication::read_UDP(qint64 maxsize)
{
    QNetworkDatagram netData;
    netData.clear();
    if(Device_UDPSocket.port != nullptr){
        if(Device_UDPSocket.port->hasPendingDatagrams()){
//        if(Device_UDPSocket.port->bytesAvailable()){
            netData = Device_UDPSocket.port->receiveDatagram(maxsize);
            Device_UDPSocket.Sourse_addr = netData.senderAddress();
            Device_UDPSocket.Sourse_port = netData.senderPort();
        }
    }
    return netData.data();
}

qint64 DeviceCommunication::available_UDP() const
{
    if(Device_UDPSocket.port != nullptr){
        return (Device_UDPSocket.port->bytesAvailable()<0)?0:Device_UDPSocket.port->bytesAvailable();

        /*此种方式存在断线后无法监听数据的可能*/
//        return (Device_UDPSocket.port->pendingDatagramSize()<0)?0:Device_UDPSocket.port->pendingDatagramSize();
    }
    return 0;
}


void DeviceCommunication::Slot_OpenProtocolDevice(QMap<QString, QVariant> device)
{
    // 串口设备
    if(device.contains(STR_SerialPort)){
        if( e_DeviceType != DeviceType_SerialPort && e_DeviceState != DeviceState_DisConnect){
            // 执行关闭操作
            Slot_CloseProtocolDevice();
        }
        // 串口默认连接参数
        QSerialPort::DataBits SerialPort_DataBit  = QSerialPort::Data8;
        QSerialPort::StopBits SerialPort_StopBit  = QSerialPort::OneStop;
        QSerialPort::Parity SerialPort_Parity  = QSerialPort::NoParity;
        qint32 SerialPort_baudRate = QSerialPort::Baud115200;

        // 获取串口设备名称
        QString SerialPort_Name =  device.find(STR_SerialPort).value().value<QString>();
        SerialPort_Name = SerialPort_Name.section(':', 0, 0);

        // 修改数据位
        if(device.contains(STR_SerialPort_DataBit)){
            SerialPort_DataBit =  device.find(STR_SerialPort_DataBit).value().value<QSerialPort::DataBits>();
        }

        // 修改停止位
        if(device.contains(STR_SerialPort_StopBit)){
            SerialPort_StopBit =  device.find(STR_SerialPort_StopBit).value().value<QSerialPort::StopBits>();
        }

        // 修改校验位
        if(device.contains(STR_SerialPort_Parity)){
            SerialPort_Parity =  device.find(STR_SerialPort_Parity).value().value<QSerialPort::Parity>();
        }

        // 修改波特率
        if(device.contains(STR_SerialPort_baudRate)){
            SerialPort_baudRate =  device.find(STR_SerialPort_baudRate).value().value<qint32>();
        }

        if(DeviceSerialport == nullptr){
            DeviceSerialport = new QSerialPort();
            // 绑定处理函数
            connect(this->DeviceSerialport,&QSerialPort::readyRead,this,[=]{emit readyRead();});
            connect(this->DeviceSerialport,&QSerialPort::errorOccurred,this,&DeviceCommunication::Slot_serial_error);
        }

        DeviceSerialport->setDataBits(SerialPort_DataBit);
        DeviceSerialport->setStopBits(SerialPort_StopBit);
        DeviceSerialport->setParity(SerialPort_Parity);
        DeviceSerialport->setBaudRate(SerialPort_baudRate);
        DeviceSerialport->setPortName(SerialPort_Name);

        if(DeviceSerialport->open(QIODevice::ReadWrite) == true){
            qDebug()<<"OpenSerialPort:"<<SerialPort_Name<<SerialPort_DataBit<<SerialPort_Parity<<SerialPort_StopBit<<SerialPort_baudRate << "Succeed";
            DeviceSerialport->clear(QSerialPort::AllDirections);
            e_DeviceType = DeviceType_SerialPort;
            e_DeviceState = DeviceState_Connect;
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_DeviceOpenSucceed);
//            Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_OpenSerialPort_Succeed);
            DeviceInfo = device;
        }else{

            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_DeviceOpenFailed);
//            Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_OpenSerialPort_Failed);
            qDebug()<<"OpenSerialPort:"<<SerialPort_Name<<SerialPort_DataBit<<SerialPort_Parity<<SerialPort_StopBit<<SerialPort_baudRate << "Failed";
            DeviceInfo.clear();
        }
        return;
    }

    if(device.contains(STR_SocketUDP)){
        if( e_DeviceType != DeviceType_NetUDP && e_DeviceState != DeviceState_DisConnect){
            // 执行关闭操作
            Slot_CloseProtocolDevice();
        }

        QHostAddress m_IP;
        quint16      m_port = 0;
        // 解析IP
        m_IP =  device.find(STR_SocketUDP).value().value<QHostAddress>();
        // 解析端口号
        if(device.contains(STR_SocketUDP_Port)){
            m_port =  device.find(STR_SocketUDP_Port).value().value<quint16>();
        }

        if(Device_UDPSocket.port == nullptr){
            Device_UDPSocket.port = new QUdpSocket();
            // 绑定处理函数
            connect(this->Device_UDPSocket.port,&QUdpSocket::readyRead,     this,[=]{emit readyRead();});
            connect(this->Device_UDPSocket.port,&QUdpSocket::errorOccurred, this,&DeviceCommunication::Slot_udpsocket_error);
        }

        // 属于组播
        if(m_IP.isMulticast()){
            Device_UDPSocket.port->setSocketOption(QAbstractSocket::MulticastLoopbackOption,1);             //设置Socket为组播模式
            bool ok = Device_UDPSocket.port->bind(QHostAddress::AnyIPv4,m_port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);     //绑定目标IP，端口
            QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); //获取系统里所有的网络接口
            foreach(QNetworkInterface intf, list){ //遍历所有接口
                //intf.addressEntries()返回此接口拥有的IP地址列表及其相关的网掩码和广播地址。
                foreach(QNetworkAddressEntry entry, intf.addressEntries()){
                    if (entry.broadcast() != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost && entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                        Device_UDPSocket.port->setMulticastInterface(intf);
                    }
                }
            }
            qDebug()<<"bind"<<QHostAddress::AnyIPv4<<m_port<<ok;

            if(Device_UDPSocket.port->joinMulticastGroup(m_IP)){
                qDebug()<<"Device_UDPSocket joinMulticastGroup success:"<<m_IP<<m_port;
                Device_UDPSocket.Sourse_addr = m_IP;
                e_DeviceType = DeviceType_NetUDP;
                e_DeviceState = DeviceState_Connect;
                ProtocolEvent(Q_DMMM::DMMM_GCSEvent_DeviceOpenSucceed);
//                Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_JoinMulticastGroup_Succeed);
                DeviceInfo = device;
            }
            else{
                qDebug()<<"Device_UDPSocket joinMulticastGroup failed:"<<m_IP<<m_port;
//                Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_JoinMulticastGroup_Failed);
                DeviceInfo.clear();
                ProtocolEvent(Q_DMMM::DMMM_GCSEvent_DeviceOpenFailed);
            }
        }
        // 单播
        else{
            // UDP绑定
            if(Device_UDPSocket.port->bind(m_IP,m_port)){
                qDebug()<<"bind UDPSocket:"<<m_IP<<m_port<<"Succeed";
                e_DeviceType = DeviceType_NetUDP;
                e_DeviceState = DeviceState_Connect;
                ProtocolEvent(Q_DMMM::DMMM_GCSEvent_DeviceOpenSucceed);
//                Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_BindSocketUDP_Succeed);
                DeviceInfo = device;
            }
            else{
                qDebug()<<"bind UDPSocket:"<<m_IP<<m_port<<"failed";
                DeviceInfo.clear();
                ProtocolEvent(Q_DMMM::DMMM_GCSEvent_DeviceOpenFailed);
//                Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_BindSocketUDP_Failed);
            }
        }
    }
}

void DeviceCommunication::Slot_serial_error(QSerialPort::SerialPortError error)
{
    qDebug()<<"serialPort"<<error;
    if(error == QSerialPort::SerialPortError::NoError)return;

    if(DeviceSerialport != nullptr){
        if(DeviceSerialport->isOpen()){
            DeviceSerialport->close();
        }
    }
    e_DeviceState = DeviceState_Error;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_ComDeviceErr);
//    Qt::DMMM()->DMMM_Event(Qt::Q_DMMM_YJYEvent::DMMM_YJYEvent_SerialPort_Error);
}

void DeviceCommunication::Slot_udpsocket_error(QAbstractSocket::SocketError error)
{
}



DeviceCommunication::DeviceState_e DeviceCommunication::getE_DeviceState() const
{
    return e_DeviceState;
}

DeviceCommunication::DeviceType_e DeviceCommunication::getE_DeviceType() const
{
    return e_DeviceType;
}

int DeviceCommunication::getIdentity() const
{
    return identity;
}

void DeviceCommunication::setIdentity(int newIdentity)
{
    identity = newIdentity;
}
