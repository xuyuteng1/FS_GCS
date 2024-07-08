/**=================================================================**
 * @brief       : YJY 导引头协议,支持串口、UDP连接
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-28     Jerry.xl     the first version
 **==================================================================**/
#include "PayloadLink.h"
#include <QDateTime>
#include <QNetworkInterface>
#include <QNetworkDatagram>
#include "DMMM.h"
#include <QSettings>

PayloadLink::PayloadLink(bool StartIndependentThread):
    QObject()
{
    if(StartIndependentThread){
        RunThread = new QThread();
        this->moveToThread(RunThread);
        RunThread->start();
    }
    connect(this,&PayloadLink::Signal_PayloadInit,this,&PayloadLink::Slot_PayloadInit);
    connect(this,&PayloadLink::Signal_write, this,&PayloadLink::Slot_write);
    emit Signal_PayloadInit();
}

PayloadLink::~PayloadLink()
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

void PayloadLink::Slot_PayloadInit()
{
    // 读取配置文件
    QSettings setting("./cfg/Setting.ini", QSettings::IniFormat);
    bool ok = false;
    QString ipstr = setting.value("Multicast/IP").toString();
    QHostAddress tmp_ip = QHostAddress(ipstr);
    if(tmp_ip.isMulticast()){
        IP_GCS = tmp_ip;
    }else{
        setting.setValue("Multicast/IP",IP_GCS.toString());  //记录路径到QSetting中保存
    }
    quint16 port_tmp = setting.value("Multicast/GCS_Port").toUInt(&ok);
    if(ok){
        Port_GCS = port_tmp;
    }else{
        setting.setValue("Multicast/GCS_Port",Port_GCS);  //记录路径到QSetting中保存
    }
    port_tmp = setting.value("Multicast/YJYVedio_Port").toUInt(&ok);
    if(ok){
        SocketPort_YJYVideoControl = port_tmp;
    }else{
        setting.setValue("Multicast/YJYVedio_Port",SocketPort_YJYVideoControl);  //记录路径到QSetting中保存
    }


    // Socket 加入组播
    if(socket == nullptr){
        socket = new QUdpSocket();
        connect(this->socket,&QUdpSocket::readyRead,     this,&PayloadLink::Slot_ReadReady);
        connect(this->socket,&QUdpSocket::errorOccurred, this,&PayloadLink::Slot_udpsocket_error);
    }

    socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption,1);             //设置Socket为组播模式
    ok = socket->bind(QHostAddress::AnyIPv4,Port_GCS,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);     //绑定目标IP，端口

    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces(); //获取系统里所有的网络接口
    foreach(QNetworkInterface intf, list){ //遍历所有接口
        //intf.addressEntries()返回此接口拥有的IP地址列表及其相关的网掩码和广播地址。
        foreach(QNetworkAddressEntry entry, intf.addressEntries()){
            if (entry.broadcast() != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost && entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                socket->setMulticastInterface(intf);
            }
        }
    }
    qDebug()<<"PayloadInit socket udp bind port:"<<Port_GCS<<ok;
    if(socket->joinMulticastGroup(IP_GCS)){
        qDebug()<<"PayloadInit joinMulticastGroup success:"<<IP_GCS<<Port_GCS;
        emit Qt::DMMM()->DMMM_Event(Q_DMMM::DMMM_GCSEvent_JoinMulticastGroup_Succeed);
    }
    else{
        qDebug()<<"PayloadInit joinMulticastGroup failed:"<<IP_GCS<<Port_GCS;
        emit Qt::DMMM()->DMMM_Event(Q_DMMM::DMMM_GCSEvent_JoinMulticastGroup_Failed);
    }
}

void PayloadLink::Slot_udpsocket_error(QAbstractSocket::SocketError error)
{

}

void PayloadLink::Slot_ReadReady()
{
    if(socket != nullptr){
        if(socket->hasPendingDatagrams()){
//        if(_port_udp->bytesAvailable()){
            QNetworkDatagram rev_data = socket->receiveDatagram();
            qDebug()<<rev_data.senderAddress()<<rev_data.senderPort()<<rev_data.destinationAddress()<<rev_data.destinationPort();
            // 处理对应数据
            if(rev_data.senderPort()== SocketPort_YJYVideoControl){
                YJYVideoControl_DataHandle(rev_data.data());
            }
        }
    }
}

void PayloadLink::Slot_write(QVariant data)
{
    QNetworkDatagram buf = data.value<QNetworkDatagram>();
    if(socket == nullptr){
        return;
    }
    socket->writeDatagram(buf);
}

void PayloadLink::YJYVideoControl_DataSend(const QByteArray arr)
{
    if(arr.isEmpty()){
        return;
    }

    QNetworkDatagram NetData(arr,IP_GCS,SocketPort_YJYVideoControl);
    QVariant data = QVariant::fromValue(NetData);
    emit Signal_write(data);
}

void PayloadLink::YJYVideoControl_DataHandle(const QByteArray arr)
{
    // 发送至 协议层上传至飞控
    if(arr.isEmpty()){
        return;
    }
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        Qt::DMMM()->getFlyLink_main()->Write_Transparent_YJYVedioControl(arr);
    }
}



