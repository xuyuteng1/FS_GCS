#ifndef VIDEOPARAMETER_H
#define VIDEOPARAMETER_H

#include <QUrl>
#include <QMap>
#include "configfile_ini.h"
class VideoParameter
{
public:
    VideoParameter();

    const QList<QString> &getLinkModelStrList() const;

    const QString &getLastLinkModelStr() const;
    void setLastLinkModelStr(const QString &newLastLinkModelStr);

    const QString &getTcpLastLinkAddress() const;
    void setTcpLastLinkAddress(const QString &newTcpLastLinkAddress);

    const QString &getUdpLastLinkAddress() const;
    void setUdpLastLinkAddress(const QString &newUdpLastLinkAddress);

    const QString &getRtspLastLinkAddress() const;
    void setRtspLastLinkAddress(const QString &newRtspLastLinkAddress);

    const QList<QString> &getTcpLinkAddressHistoryList() const;

    const QList<QString> &getUdpLinkAddressHistoryList() const;

    const QList<QString> &getRtspLinkAddressHistoryList() const;

    const QString &getCodecLastStr() const;
    void setCodecLastStr(const QString &newCodecLastStr);

    int getBufferSize() const;
    void setBufferSize(int newBufferSize);

    int getDelay_ms() const;
    void setDelay_ms(int newDelay_ms);

    int getCfr() const;
    void setCfr(int newCfr);

    int getLinkTimeout() const;
    void setLinkTimeout(int newLinkTimeout);

    int getFps() const;
    void setFps(int newFps);


private:
    QString lastLinkModelStr;                                                                                                                    //上次连接方式
    QList<QString> linkModelStrList = QStringList()<<"tcp"<<"udp"<<"rtsp";                                      //连接方式列表
    QString tcpLastLinkAddress;                                                                                                                //tcp最后一次连接地址
    QString udpLastLinkAddress;                                                                                                              //udp最后一次连接地址
    QString rtspLastLinkAddress;                                                                                                             //rtsp最后一次连接地址
    QList<QString> tcpLinkAddressHistoryList;                                                                                       //tcp连接方式历史记录
    QList<QString> udpLinkAddressHistoryList;                                                                                      //udp连接方式历史记录
    QList<QString> rtspLinkAddressHistoryList;                                                                                     //rtsp连接方式历史记录

    QList<QString> codecStrList = QStringList()<<"ultrafast"<<"superfast"<<"veryfast"<<"faster"<<"fast"<<"medium"<<"slow"<<"slower"<<"veryslow"<<"placebo";
    QString codecLastStr = "";

    int bufferSize = 1024000;                                                                                                                  //缓冲区大小
    int delay_ms = 500;                                                                                                                           //延时约束
    int cfr = 25;                                                                                                                                       //视频质量
    int linkTimeout = 5000;                                                                                                                    //连接超时时间
    int fps = 25;                                                                                                                                      //视频fps

private:
    ConfigFile_Ini *ini = nullptr;
};

#endif // VIDEOPARAMETER_H
