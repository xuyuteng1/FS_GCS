#include "systemdata.h"

DlsplayData *SystemData::displayData = nullptr;
PhotoelectricData *SystemData::photoelectricData = nullptr;
TextToSpeedData  *SystemData::textToSpeedData = nullptr;
LanguageData *SystemData::languageData = nullptr;
MapData           *SystemData::mapData = nullptr;
CommunicationsData  *SystemData::communicationsData = nullptr;

SystemData::SystemData()
{
    if(displayData == nullptr){
        displayData = new DlsplayData;
    }
    if(photoelectricData == nullptr){
        photoelectricData = new PhotoelectricData;
    }
    if(textToSpeedData == nullptr){
        textToSpeedData = new TextToSpeedData;
    }
    if(languageData == nullptr){
        languageData = new LanguageData;
    }
    if(mapData == nullptr){
        mapData = new MapData;
    }
    if(communicationsData == nullptr){
        communicationsData = new CommunicationsData;
    }

}

MapData *SystemData::getMapData()
{
    if(mapData == nullptr){
        mapData = new MapData;
    }
    return mapData;
}

CommunicationsData *SystemData::getCommunicationsData()
{
    if(communicationsData == nullptr){
        communicationsData = new CommunicationsData;
    }
    return communicationsData;
}

LanguageData *SystemData::getLanguageData()
{
    if(languageData == nullptr){
        languageData = new LanguageData;
    }
    return languageData;
}

TextToSpeedData *SystemData::getTextToSpeedData()
{
    if(textToSpeedData == nullptr){
        textToSpeedData = new TextToSpeedData;
    }
    return textToSpeedData;
}

PhotoelectricData *SystemData::getPhotoelectricData()
{
    if(photoelectricData == nullptr){
        photoelectricData = new PhotoelectricData;
    }
    return photoelectricData;
}

DlsplayData *SystemData::getDisplayData()
{
    if(displayData == nullptr){
        displayData = new DlsplayData;
    }
    return displayData;
}




DlsplayData::DlsplayData()
{
    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("SystemConfig",QCoreApplication::applicationDirPath() + "/cfg/systemconfig.ini");

    this->ini->addNewField("SystemConfig","Display","DisplayGamma",displayGamma,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);

    this->ini->getFieldValue("SystemConfig","Display","DisplayGamma",displayGamma);
}

int DlsplayData::getDisplayGamma() const
{
    return displayGamma;
}

void DlsplayData::setDisplayGamma(int newDisplayGamma)
{
    if(newDisplayGamma != displayGamma){
        displayGamma = newDisplayGamma;
        this->ini->changedField("SystemConfig","Display","DisplayGamma",displayGamma);
    }
}







PhotoelectricData::PhotoelectricData()
{
    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("SystemConfig",QCoreApplication::applicationDirPath() + "/cfg/systemconfig.ini");

    this->ini->addNewField("SystemConfig","Photoelectric","lastLinkModel",lastLinkModelStr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","tcpLastLinkAddress",tcpLastLinkAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","udpLastLinkAddress",udpLastLinkAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","rtspLastLinkAddress",rtspLastLinkAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","tcpLinkAddressHistoryList",tcpLinkAddressHistoryList.join(';'),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","udpLinkAddressHistoryList",udpLinkAddressHistoryList.join(';'),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","rtspLinkAddressHistoryList",rtspLinkAddressHistoryList.join(';'),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","codecLastStr",codecLastStr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);

    this->ini->addNewField("SystemConfig","Photoelectric","bufferSize",bufferSize,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","delay_ms",delay_ms,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","cfr",cfr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","linkTimeout",linkTimeout,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Photoelectric","fps",fps,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);


    this->ini->getFieldValue("SystemConfig","Photoelectric","lastLinkModel",lastLinkModelStr);
    this->ini->getFieldValue("SystemConfig","Photoelectric","tcpLastLinkAddress",tcpLastLinkAddress);
    this->ini->getFieldValue("SystemConfig","Photoelectric","udpLastLinkAddress",udpLastLinkAddress);
    this->ini->getFieldValue("SystemConfig","Photoelectric","rtspLastLinkAddress",rtspLastLinkAddress);

    QString tcpLinkAddressHistoryStr;
    this->ini->getFieldValue("SystemConfig","Photoelectric","tcpLinkAddressHistoryList",tcpLinkAddressHistoryStr);
    this->tcpLinkAddressHistoryList = tcpLinkAddressHistoryStr.remove("\r").remove("\n").remove(" ").split(';');
    QString udpLinkAddressHistoryStr;
    this->ini->getFieldValue("SystemConfig","Photoelectric","udpLinkAddressHistoryList",udpLinkAddressHistoryStr);
    this->udpLinkAddressHistoryList = udpLinkAddressHistoryStr.remove("\r").remove("\n").remove(" ").split(';');
    QString rtspLinkAddressHistoryStr;
    this->ini->getFieldValue("SystemConfig","Photoelectric","rtspLinkAddressHistoryList",rtspLinkAddressHistoryStr);
    this->rtspLinkAddressHistoryList = rtspLinkAddressHistoryStr.remove("\r").remove("\n").remove(" ").split(';');
    this->ini->getFieldValue("SystemConfig","Photoelectric","codecLastStr",codecLastStr);

    this->ini->getFieldValue("SystemConfig","Photoelectric","bufferSize",bufferSize);
    this->ini->getFieldValue("SystemConfig","Photoelectric","delay_ms",delay_ms);
    this->ini->getFieldValue("SystemConfig","Photoelectric","cfr",cfr);
    this->ini->getFieldValue("SystemConfig","Photoelectric","linkTimeout",linkTimeout);
    this->ini->getFieldValue("SystemConfig","Photoelectric","fps",fps);
}

const QList<QString> &PhotoelectricData::getLinkModelStrList() const
{
    return linkModelStrList;
}

const QString &PhotoelectricData::getLastLinkModelStr() const
{
    return lastLinkModelStr;
}

void PhotoelectricData::setLastLinkModelStr(const QString &newLastLinkModelStr)
{
    if(lastLinkModelStr != newLastLinkModelStr){
        lastLinkModelStr = newLastLinkModelStr;
        this->ini->changedField("SystemConfig","Photoelectric","lastLinkModel",lastLinkModelStr);
    }
}

const QString &PhotoelectricData::getTcpLastLinkAddress() const
{
    return tcpLastLinkAddress;
}

void PhotoelectricData::setTcpLastLinkAddress(const QString &newTcpLastLinkAddress)
{
    if(tcpLastLinkAddress.compare(newTcpLastLinkAddress) != 0){
        tcpLastLinkAddress = newTcpLastLinkAddress;
        this->ini->changedField("SystemConfig","Photoelectric","tcpLastLinkAddress",tcpLastLinkAddress);
        if(this->tcpLinkAddressHistoryList.indexOf(tcpLastLinkAddress) == -1){
            if(tcpLinkAddressHistoryList.count() > 10){
                tcpLinkAddressHistoryList.removeLast();
            }
            tcpLinkAddressHistoryList.insert(0,tcpLastLinkAddress);
            this->ini->changedField("SystemConfig","Photoelectric","tcpLinkAddressHistoryList",tcpLinkAddressHistoryList.join(';'));
        }
    }
}

const QString &PhotoelectricData::getUdpLastLinkAddress() const
{
    return udpLastLinkAddress;
}

void PhotoelectricData::setUdpLastLinkAddress(const QString &newUdpLastLinkAddress)
{
    if(udpLastLinkAddress.compare(newUdpLastLinkAddress) != 0){
        udpLastLinkAddress = newUdpLastLinkAddress;
        this->ini->changedField("SystemConfig","Photoelectric","udpLastLinkAddress",udpLastLinkAddress);
        if(this->udpLinkAddressHistoryList.indexOf(udpLastLinkAddress) == -1){
            if(udpLinkAddressHistoryList.count() > 10){
                udpLinkAddressHistoryList.removeLast();
            }
            udpLinkAddressHistoryList.insert(0,udpLastLinkAddress);
            this->ini->changedField("SystemConfig","Photoelectric","udpLinkAddressHistoryList",udpLinkAddressHistoryList.join(';'));
        }
    }
}

const QString &PhotoelectricData::getRtspLastLinkAddress() const
{
    return rtspLastLinkAddress;
}

void PhotoelectricData::setRtspLastLinkAddress(const QString &newRtspLastLinkAddress)
{

    if(rtspLastLinkAddress.compare(newRtspLastLinkAddress) != 0){
        rtspLastLinkAddress = newRtspLastLinkAddress;
        this->ini->changedField("SystemConfig","Photoelectric","rtspLastLinkAddress",rtspLastLinkAddress);
        if(this->rtspLinkAddressHistoryList.indexOf(rtspLastLinkAddress) == -1){
            if(rtspLinkAddressHistoryList.count() > 10){
                rtspLinkAddressHistoryList.removeLast();
            }
            rtspLinkAddressHistoryList.insert(0,rtspLastLinkAddress);
            this->ini->changedField("SystemConfig","Photoelectric","rtspLinkAddressHistoryList",rtspLinkAddressHistoryList.join(';'));
        }
    }
}

const QList<QString> &PhotoelectricData::getTcpLinkAddressHistoryList() const
{
    return tcpLinkAddressHistoryList;
}

const QList<QString> &PhotoelectricData::getUdpLinkAddressHistoryList() const
{
    return udpLinkAddressHistoryList;
}

const QList<QString> &PhotoelectricData::getRtspLinkAddressHistoryList() const
{
    return rtspLinkAddressHistoryList;
}

const QString &PhotoelectricData::getCodecLastStr() const
{
    return codecLastStr;
}

void PhotoelectricData::setCodecLastStr(const QString &newCodecLastStr)
{
    if(codecLastStr != newCodecLastStr){
        codecLastStr = newCodecLastStr;
        this->ini->changedField("SystemConfig","Photoelectric","codecLastStr",codecLastStr);
    }
}

int PhotoelectricData::getBufferSize() const
{
    return bufferSize;
}

void PhotoelectricData::setBufferSize(int newBufferSize)
{
    if(bufferSize != newBufferSize){
        bufferSize = newBufferSize;
        this->ini->changedField("SystemConfig","Photoelectric","bufferSize",QString::number(bufferSize));
    }
}

int PhotoelectricData::getDelay_ms() const
{
    return delay_ms;
}

void PhotoelectricData::setDelay_ms(int newDelay_ms)
{
    if(delay_ms != newDelay_ms){
        delay_ms = newDelay_ms;
        this->ini->changedField("SystemConfig","Photoelectric","delay_ms",QString::number(delay_ms));
    }
}

int PhotoelectricData::getCfr() const
{
    return cfr;
}

void PhotoelectricData::setCfr(int newCfr)
{
    if(cfr != newCfr){
        cfr = newCfr;
        this->ini->changedField("SystemConfig","Photoelectric","cfr",QString::number(cfr));
    }
}

int PhotoelectricData::getLinkTimeout() const
{
    return linkTimeout;
}

void PhotoelectricData::setLinkTimeout(int newLinkTimeout)
{
    if(linkTimeout != newLinkTimeout){
        linkTimeout = newLinkTimeout;
        this->ini->changedField("SystemConfig","Photoelectric","linkTimeout",QString::number(linkTimeout));
    }
}

int PhotoelectricData::getFps() const
{
    return fps;
}

void PhotoelectricData::setFps(int newFps)
{
    if(fps != newFps){
        fps = newFps;
        this->ini->changedField("SystemConfig","Photoelectric","fps",QString::number(fps));
    }
}




TextToSpeedData::TextToSpeedData()
{
    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("SystemConfig",QCoreApplication::applicationDirPath() + "/cfg/systemconfig.ini");
    this->ini->addNewField("SystemConfig","TextToSpeed","enable",enable,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","infoSpeedEnable",infoSpeedEnable,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","wornSpeedEnable",wornSpeedEnable,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","errorSpeedEnable",errorSpeedEnable,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","speedForLevel",speedForLevel,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","breakModel",breakModel,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","speedVolume",speedVolume,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","speedRate",speedRate,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","TextToSpeed","speedPitch",speedPitch,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);


    this->ini->getFieldValue("SystemConfig","TextToSpeed","enable",enable);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","infoSpeedEnable",infoSpeedEnable);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","wornSpeedEnable",wornSpeedEnable);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","errorSpeedEnable",errorSpeedEnable);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","speedForLevel",speedForLevel);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","breakModel",breakModel);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","speedVolume",speedVolume);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","speedRate",speedRate);
    this->ini->getFieldValue("SystemConfig","TextToSpeed","speedPitch",speedPitch);
}



MapData::MapData()
{
    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("SystemConfig",QCoreApplication::applicationDirPath() + "/cfg/systemconfig.ini");
    this->ini->addNewField("SystemConfig","Map","mapNameStr",mapNameStr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Map","mapTypeStr",mapTypeStr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Map","minLevel",minLevel,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Map","maxLevel",maxLevel,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Map","defLevel",defLevel,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);

    this->ini->getFieldValue("SystemConfig","Map","mapNameStr",mapNameStr);
    this->ini->getFieldValue("SystemConfig","Map","mapTypeStr",mapTypeStr);
    this->ini->getFieldValue("SystemConfig","Map","minLevel",minLevel);
    this->ini->getFieldValue("SystemConfig","Map","maxLevel",maxLevel);
    this->ini->getFieldValue("SystemConfig","Map","defLevel",defLevel);

//    this->mapNameComboBox->addItems(QStringList()<< "bingmaps"<<"googlemaps"<<"TiMap"<<"amap"<<"esri"<<"osm");
    this->supportedMap.insert(QStringLiteral("bingmaps"),QStringList()<<"Bing Street Map"<<"Bing Satellite Map"<<"Tianditu Street");
    this->supportedMap.insert(QStringLiteral("googlemaps"),QStringList()<<"Satellite"<<"Road Map"<<"Terrain"<<"Hybrid"<<"Tianditu Street");
    this->supportedMap.insert(QStringLiteral("TiMap"),QStringList()<<"Tianditu Satellite"<<"Tianditu Street");
    this->supportedMap.insert(QStringLiteral("esri"),QStringList()<<"World Street Map"<<"World Imagery"<<"World Terrain Base"<<"World Topography"<<"USA Topo Maps"<<"National Geographic World Map"<<"Light Gray Canvas"<<"World Physical Map"<<"World Shaded Relief"<<"World Ocean Base"<<"Dark Gray Canvas"<<"DeLorme World Basemap");



}

int MapData::getMinLevel() const
{
    return minLevel;
}

void MapData::setMinLevel(int newMinLevel)
{
    if(minLevel != newMinLevel){
        minLevel = newMinLevel;
        this->ini->changedField("SystemConfig","Map","minLevel",minLevel);
    }
}

int MapData::getMaxLevel() const
{
    return maxLevel;
}

void MapData::setMaxLevel(int newMaxLevel)
{
    if(maxLevel != newMaxLevel){
        maxLevel = newMaxLevel;
        this->ini->changedField("SystemConfig","Map","maxLevel",maxLevel);
    }
}

int MapData::getDefLevel() const
{
    return defLevel;
}

void MapData::setDefLevel(int newDefLevel)
{
    if(defLevel != newDefLevel){
        defLevel = newDefLevel;
        this->ini->changedField("SystemConfig","Map","defLevel",defLevel);
    }

}

const QString &MapData::getMapNameStr() const
{
    return mapNameStr;
}

void MapData::setMapNameStr(const QString &newMapNameStr)
{
    if(mapNameStr != newMapNameStr){
        mapNameStr = newMapNameStr;
        this->ini->changedField("SystemConfig","Map","mapNameStr",mapNameStr);
    }
}

const QString &MapData::getMapTypeStr() const
{
    return mapTypeStr;
}

void MapData::setMapTypeStr(const QString &newMapTypeStr)
{
    if(mapTypeStr != newMapTypeStr){
        mapTypeStr = newMapTypeStr;
        this->ini->changedField("SystemConfig","Map","mapTypeStr",mapTypeStr);
    }
}

const QMap<QString, QStringList> &MapData::getSupportedMap() const
{
    return supportedMap;
}




LanguageData::LanguageData()
{

}

CommunicationsData::CommunicationsData()
{
    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("SystemConfig",QCoreApplication::applicationDirPath() + "/cfg/systemconfig.ini");
    this->ini->addNewField("SystemConfig","Communications","lastCommunicationType",lastCommunicationType,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Communications","lastUdpConnectAddress",lastUdpConnectAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Communications","lastTcpConnectAddress",lastTcpConnectAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Communications","lastUdpConnectPort",lastUdpConnectPort,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Communications","lastTcpConnectPort",lastTcpConnectPort,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Communications","lastSerialConnectName",lastSerialConnectName,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("SystemConfig","Communications","lastSerialConnectBaud",lastSerialConnectBaud,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);


    this->ini->getFieldValue("SystemConfig","Communications","lastCommunicationType",lastCommunicationType);
    this->ini->getFieldValue("SystemConfig","Communications","lastUdpConnectAddress",lastUdpConnectAddress);
    this->ini->getFieldValue("SystemConfig","Communications","lastTcpConnectAddress",lastTcpConnectAddress);
    this->ini->getFieldValue("SystemConfig","Communications","lastUdpConnectPort",lastUdpConnectPort);
    this->ini->getFieldValue("SystemConfig","Communications","lastTcpConnectPort",lastTcpConnectPort);
    this->ini->getFieldValue("SystemConfig","Communications","lastSerialConnectName",lastSerialConnectName);
    this->ini->getFieldValue("SystemConfig","Communications","lastSerialConnectBaud",lastSerialConnectBaud);

}

int CommunicationsData::getLastCommunicationType() const
{
    return lastCommunicationType;
}

void CommunicationsData::setLastCommunicationType(int newLastCommunicationType)
{
    if(lastCommunicationType != newLastCommunicationType){
        lastCommunicationType = newLastCommunicationType;
        this->ini->changedField("SystemConfig","Communications","lastCommunicationType",lastCommunicationType);
    }
}

const QString &CommunicationsData::getLastUdpConnectAddress() const
{
    return lastUdpConnectAddress;
}

void CommunicationsData::setLastUdpConnectAddress(const QString &newLastUdpConnectAddress)
{
    if(lastUdpConnectAddress != newLastUdpConnectAddress){
        lastUdpConnectAddress = newLastUdpConnectAddress;
        this->ini->changedField("SystemConfig","Communications","lastUdpConnectAddress",lastUdpConnectAddress);
    }
}

const QString &CommunicationsData::getLastTcpConnectAddress() const
{
    return lastTcpConnectAddress;
}

void CommunicationsData::setLastTcpConnectAddress(const QString &newLastTcpConnectAddress)
{
    if(lastTcpConnectAddress != newLastTcpConnectAddress){
        lastTcpConnectAddress = newLastTcpConnectAddress;
        this->ini->changedField("SystemConfig","Communications","lastTcpConnectAddress",lastTcpConnectAddress);
    }
}

const QString &CommunicationsData::getLastUdpConnectPort() const
{
    return lastUdpConnectPort;
}

void CommunicationsData::setLastUdpConnectPort(const QString &newLastUdpConnectPort)
{
    if(lastUdpConnectPort != newLastUdpConnectPort){
        lastUdpConnectPort = newLastUdpConnectPort;
        this->ini->changedField("SystemConfig","Communications","lastUdpConnectPort",lastUdpConnectPort);
    }
}

const QString &CommunicationsData::getLastTcpConnectPort() const
{
    return lastTcpConnectPort;
}

void CommunicationsData::setLastTcpConnectPort(const QString &newLastTcpConnectPort)
{
    if(lastTcpConnectPort != newLastTcpConnectPort){
        lastTcpConnectPort = newLastTcpConnectPort;
        this->ini->changedField("SystemConfig","Communications","lastTcpConnectPort",lastTcpConnectPort);
    }
}

const QString &CommunicationsData::getLastSerialConnectName() const
{
    return lastSerialConnectName;
}

void CommunicationsData::setLastSerialConnectName(const QString &newLastSerialConnectName)
{
    if(lastSerialConnectName != newLastSerialConnectName){
        lastSerialConnectName = newLastSerialConnectName;
        this->ini->changedField("SystemConfig","Communications","lastSerialConnectName",lastSerialConnectName);
    }
}

const QString &CommunicationsData::getLastSerialConnectBaud() const
{
    return lastSerialConnectBaud;
}

void CommunicationsData::setLastSerialConnectBaud(const QString &newLastSerialConnectBaud)
{
    if(lastSerialConnectBaud != newLastSerialConnectBaud){
        lastSerialConnectBaud = newLastSerialConnectBaud;
        this->ini->changedField("SystemConfig","Communications","lastSerialConnectBaud",lastSerialConnectBaud);
    }
}
