/**=================================================================**
 * @brief       : 通用设备通信类：支持串口、UDP连接
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-10-28     Jerry.xl     the first version
 **==================================================================**/
#ifndef PAYLOAD_LINK_H__
#define PAYLOAD_LINK_H__

#include <QUdpSocket>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <QThread>


class PayloadLink:public QObject
{
    Q_OBJECT
public:
    PayloadLink(bool StartIndependentThread = false);
    ~PayloadLink();

private:
signals:
    void Signal_PayloadInit();
    void Signal_write(QVariant data);
private slots:
    void Slot_PayloadInit();
    void Slot_udpsocket_error(QAbstractSocket::SocketError error);
    void Slot_ReadReady();
    void Slot_write(QVariant data);
public:
    // 研究院吊舱数据发送与处理
    void YJYVideoControl_DataSend(const QByteArray arr);
    void YJYVideoControl_DataHandle(const QByteArray arr);
private:
    QThread*        RunThread = nullptr;
    QUdpSocket*     socket = nullptr;

    QHostAddress  IP_GCS                  = QHostAddress("226.0.0.25");
    quint16       Port_GCS                = 6000;

    quint16       SocketPort_YJYVideoControl = (6001);

};
#endif // NETWORK_UDP_H
