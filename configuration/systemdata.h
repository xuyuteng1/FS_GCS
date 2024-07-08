#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H
#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>
#include "configfile_ini.h"
/*显示相关*/
class DlsplayData{
public:
    DlsplayData();

    int getDisplayGamma() const;
    void setDisplayGamma(int newDisplayGamma);

private:
    int displayGamma = 100;                                         //显示器亮度


private:
    ConfigFile_Ini *ini = nullptr;

};

/*光电参数*/
class PhotoelectricData{
public:
    PhotoelectricData();

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
    QList<QString> linkModelStrList = QStringList()<<"tcp"<<"udp"<<"rtsp";                              //连接方式列表
    QString tcpLastLinkAddress;                                                                                                               //tcp最后一次连接地址
    QString udpLastLinkAddress;                                                                                                             //udp最后一次连接地址
    QString rtspLastLinkAddress;                                                                                                            //rtsp最后一次连接地址
    QList<QString> tcpLinkAddressHistoryList;                                                                                       //tcp连接方式历史记录
    QList<QString> udpLinkAddressHistoryList;                                                                                     //udp连接方式历史记录
    QList<QString> rtspLinkAddressHistoryList;                                                                                    //rtsp连接方式历史记录

    QList<QString> codecStrList = QStringList()<<"ultrafast"<<"superfast"<<"veryfast"<<"faster"<<"fast"<<"medium"<<"slow"<<"slower"<<"veryslow"<<"placebo";
    QString codecLastStr = "";

    int bufferSize = 1024000;                                                                                                                   //缓冲区大小
    int delay_ms = 500;                                                                                                                              //延时约束
    int cfr = 25;                                                                                                                                            //视频质量
    int linkTimeout = 5000;                                                                                                                       //连接超时时间
    int fps = 25;                                                                                                                                           //视频fps

private:
    ConfigFile_Ini *ini = nullptr;
};

class TextToSpeedData{
public:
    TextToSpeedData();


private:
    bool enable = false;                                                                                                                                //语音告警启用状态
    bool infoSpeedEnable = false;                                                                                                             //告警级别 info
    bool wornSpeedEnable = false;                                                                                                           //告警级别 worn
    bool errorSpeedEnable = false;                                                                                                          //告警级别 error
    bool speedForLevel = false;                                                                                                                //优先级播报
    bool breakModel = false;                                                                                                                    //优先级打断
    int    speedVolume = 100;                                                                                                                   //播报音量
    int    speedRate = 10;                                                                                                                           //播报语速
    int    speedPitch = 10;                                                                                                                         //播报音高

private:
    ConfigFile_Ini *ini = nullptr;
};

class LanguageData{
public:
    LanguageData();

private:
    QString languagePath;

};

class MapData{
public:
    MapData();

    int getMinLevel() const;
    void setMinLevel(int newMinLevel);

    int getMaxLevel() const;
    void setMaxLevel(int newMaxLevel);

    int getDefLevel() const;
    void setDefLevel(int newDefLevel);

    const QString &getMapNameStr() const;
    void setMapNameStr(const QString &newMapNameStr);

    const QString &getMapTypeStr() const;
    void setMapTypeStr(const QString &newMapTypeStr);

    const QMap<QString, QStringList> &getSupportedMap() const;

private:
    QString mapNameStr = "bingmaps";                                                                                               //地图名称
    QString mapTypeStr = "Bing Satellite Map";                                                                                                     //地图类型
    QMap<QString,QStringList> supportedMap;                                                                                     //名称类型对照表

    int minLevel = 0;                                                                                                                                //最小级别
    int maxLevel = 21;                                                                                                                              //最大级别
    int defLevel = 17;                                                                                                                                //默认级别

private:
    ConfigFile_Ini *ini = nullptr;
};

class CommunicationsData{
public:
    CommunicationsData();

    int getLastCommunicationType() const;
    void setLastCommunicationType(int newLastCommunicationType);

    const QString &getLastUdpConnectAddress() const;
    void setLastUdpConnectAddress(const QString &newLastUdpConnectAddress);

    const QString &getLastTcpConnectAddress() const;
    void setLastTcpConnectAddress(const QString &newLastTcpConnectAddress);

    const QString &getLastUdpConnectPort() const;
    void setLastUdpConnectPort(const QString &newLastUdpConnectPort);

    const QString &getLastTcpConnectPort() const;
    void setLastTcpConnectPort(const QString &newLastTcpConnectPort);

    const QString &getLastSerialConnectName() const;
    void setLastSerialConnectName(const QString &newLastSerialConnectName);

    const QString &getLastSerialConnectBaud() const;
    void setLastSerialConnectBaud(const QString &newLastSerialConnectBaud);

private:
    int lastCommunicationType = 0;                  //typedef enum{ Device_None = 0, Device_SerialPort,Device_NetUDP,Device_NetTCP, Device_end,}DeviceType;
    QString lastUdpConnectAddress = "";
    QString lastTcpConnectAddress = "";

    QString lastUdpConnectPort = "";
    QString lastTcpConnectPort = "";

    QString lastSerialConnectName = "";
    QString lastSerialConnectBaud = "";

    ConfigFile_Ini *ini = nullptr;


};

class SystemData
{
public:
    SystemData();

    static DlsplayData *displayData;
    static PhotoelectricData *photoelectricData;
    static TextToSpeedData  *textToSpeedData;
    static LanguageData *languageData;
    static MapData           *mapData;
    static CommunicationsData           *communicationsData;

    static DlsplayData *getDisplayData();
    static PhotoelectricData *getPhotoelectricData();
    static TextToSpeedData *getTextToSpeedData();
    static LanguageData *getLanguageData();
    static MapData *getMapData();
    static CommunicationsData *getCommunicationsData();
};






//namespace Sys_DataPool {
//    DlsplayData *displayPtr = SystemData::getDisplayData();
//    PhotoelectricData *photoelectricPtr = SystemData::getPhotoelectricData();
//    TextToSpeedData  *textToSpeedPtr = SystemData::getTextToSpeedData();
//    LanguageData *languagePtr = SystemData::getLanguageData();
//    MapData           *mapDataPtr = SystemData::getMapData();
//}



#endif // SYSTEMDATA_H
