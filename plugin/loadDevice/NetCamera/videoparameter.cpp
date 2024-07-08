#include "videoparameter.h"

VideoParameter::VideoParameter()
{
    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("Device",QCoreApplication::applicationDirPath() + "/cfg/Device.ini");

    this->ini->addNewField("Device","NetCamera","lastLinkModel",lastLinkModelStr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","tcpLastLinkAddress",tcpLastLinkAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","udpLastLinkAddress",udpLastLinkAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","rtspLastLinkAddress",rtspLastLinkAddress,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","tcpLinkAddressHistoryList",tcpLinkAddressHistoryList.join(';'),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","udpLinkAddressHistoryList",udpLinkAddressHistoryList.join(';'),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","rtspLinkAddressHistoryList",rtspLinkAddressHistoryList.join(';'),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","codecLastStr",codecLastStr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);

    this->ini->addNewField("Device","NetCamera","bufferSize",bufferSize,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","delay_ms",delay_ms,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","cfr",cfr,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","linkTimeout",linkTimeout,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("Device","NetCamera","fps",fps,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);


    this->ini->getFieldValue("Device","NetCamera","lastLinkModel",lastLinkModelStr);
    this->ini->getFieldValue("Device","NetCamera","tcpLastLinkAddress",tcpLastLinkAddress);
    this->ini->getFieldValue("Device","NetCamera","udpLastLinkAddress",udpLastLinkAddress);
    this->ini->getFieldValue("Device","NetCamera","rtspLastLinkAddress",rtspLastLinkAddress);

    QString tcpLinkAddressHistoryStr;
    this->ini->getFieldValue("Device","NetCamera","tcpLinkAddressHistoryList",tcpLinkAddressHistoryStr);
    this->tcpLinkAddressHistoryList = tcpLinkAddressHistoryStr.remove("\r").remove("\n").remove(" ").split(';');
    QString udpLinkAddressHistoryStr;
    this->ini->getFieldValue("Device","NetCamera","udpLinkAddressHistoryList",udpLinkAddressHistoryStr);
    this->udpLinkAddressHistoryList = udpLinkAddressHistoryStr.remove("\r").remove("\n").remove(" ").split(';');
    QString rtspLinkAddressHistoryStr;
    this->ini->getFieldValue("Device","NetCamera","rtspLinkAddressHistoryList",rtspLinkAddressHistoryStr);
    this->rtspLinkAddressHistoryList = rtspLinkAddressHistoryStr.remove("\r").remove("\n").remove(" ").split(';');
    this->ini->getFieldValue("Device","NetCamera","codecLastStr",codecLastStr);

    this->ini->getFieldValue("Device","NetCamera","bufferSize",bufferSize);
    this->ini->getFieldValue("Device","NetCamera","delay_ms",delay_ms);
    this->ini->getFieldValue("Device","NetCamera","cfr",cfr);
    this->ini->getFieldValue("Device","NetCamera","linkTimeout",linkTimeout);
    this->ini->getFieldValue("Device","NetCamera","fps",fps);
}

const QList<QString> &VideoParameter::getLinkModelStrList() const
{
    return linkModelStrList;
}

const QString &VideoParameter::getLastLinkModelStr() const
{
    return lastLinkModelStr;
}

void VideoParameter::setLastLinkModelStr(const QString &newLastLinkModelStr)
{
    if(lastLinkModelStr != newLastLinkModelStr){
        lastLinkModelStr = newLastLinkModelStr;
        this->ini->changedField("Device","NetCamera","lastLinkModel",lastLinkModelStr);
    }
}

const QString &VideoParameter::getTcpLastLinkAddress() const
{
    return tcpLastLinkAddress;
}

void VideoParameter::setTcpLastLinkAddress(const QString &newTcpLastLinkAddress)
{
    if(tcpLastLinkAddress.compare(newTcpLastLinkAddress) != 0){
        tcpLastLinkAddress = newTcpLastLinkAddress;
        this->ini->changedField("Device","NetCamera","tcpLastLinkAddress",tcpLastLinkAddress);
        if(this->tcpLinkAddressHistoryList.indexOf(tcpLastLinkAddress) == -1){
            if(tcpLinkAddressHistoryList.count() > 10){
                tcpLinkAddressHistoryList.removeLast();
            }
            tcpLinkAddressHistoryList.insert(0,tcpLastLinkAddress);
            this->ini->changedField("Device","NetCamera","tcpLinkAddressHistoryList",tcpLinkAddressHistoryList.join(';'));
        }
    }
}

const QString &VideoParameter::getUdpLastLinkAddress() const
{
    return udpLastLinkAddress;
}

void VideoParameter::setUdpLastLinkAddress(const QString &newUdpLastLinkAddress)
{
    if(udpLastLinkAddress.compare(newUdpLastLinkAddress) != 0){
        udpLastLinkAddress = newUdpLastLinkAddress;
        this->ini->changedField("Device","NetCamera","udpLastLinkAddress",udpLastLinkAddress);
        if(this->udpLinkAddressHistoryList.indexOf(udpLastLinkAddress) == -1){
            if(udpLinkAddressHistoryList.count() > 10){
                udpLinkAddressHistoryList.removeLast();
            }
            udpLinkAddressHistoryList.insert(0,udpLastLinkAddress);
            this->ini->changedField("Device","NetCamera","udpLinkAddressHistoryList",udpLinkAddressHistoryList.join(';'));
        }
    }
}

const QString &VideoParameter::getRtspLastLinkAddress() const
{
    return rtspLastLinkAddress;
}

void VideoParameter::setRtspLastLinkAddress(const QString &newRtspLastLinkAddress)
{

    if(rtspLastLinkAddress.compare(newRtspLastLinkAddress) != 0){
        rtspLastLinkAddress = newRtspLastLinkAddress;
        this->ini->changedField("Device","NetCamera","rtspLastLinkAddress",rtspLastLinkAddress);
        if(this->rtspLinkAddressHistoryList.indexOf(rtspLastLinkAddress) == -1){
            if(rtspLinkAddressHistoryList.count() > 10){
                rtspLinkAddressHistoryList.removeLast();
            }
            rtspLinkAddressHistoryList.insert(0,rtspLastLinkAddress);
            this->ini->changedField("Device","NetCamera","rtspLinkAddressHistoryList",rtspLinkAddressHistoryList.join(';'));
        }
    }
}

const QList<QString> &VideoParameter::getTcpLinkAddressHistoryList() const
{
    return tcpLinkAddressHistoryList;
}

const QList<QString> &VideoParameter::getUdpLinkAddressHistoryList() const
{
    return udpLinkAddressHistoryList;
}

const QList<QString> &VideoParameter::getRtspLinkAddressHistoryList() const
{
    return rtspLinkAddressHistoryList;
}

const QString &VideoParameter::getCodecLastStr() const
{
    return codecLastStr;
}

void VideoParameter::setCodecLastStr(const QString &newCodecLastStr)
{
    if(codecLastStr != newCodecLastStr){
        codecLastStr = newCodecLastStr;
        this->ini->changedField("Device","NetCamera","codecLastStr",codecLastStr);
    }
}

int VideoParameter::getBufferSize() const
{
    return bufferSize;
}

void VideoParameter::setBufferSize(int newBufferSize)
{
    if(bufferSize != newBufferSize){
        bufferSize = newBufferSize;
        this->ini->changedField("Device","NetCamera","bufferSize",QString::number(bufferSize));
    }
}

int VideoParameter::getDelay_ms() const
{
    return delay_ms;
}

void VideoParameter::setDelay_ms(int newDelay_ms)
{
    if(delay_ms != newDelay_ms){
        delay_ms = newDelay_ms;
        this->ini->changedField("Device","NetCamera","delay_ms",QString::number(delay_ms));
    }
}

int VideoParameter::getCfr() const
{
    return cfr;
}

void VideoParameter::setCfr(int newCfr)
{
    if(cfr != newCfr){
        cfr = newCfr;
        this->ini->changedField("Device","NetCamera","cfr",QString::number(cfr));
    }
}

int VideoParameter::getLinkTimeout() const
{
    return linkTimeout;
}

void VideoParameter::setLinkTimeout(int newLinkTimeout)
{
    if(linkTimeout != newLinkTimeout){
        linkTimeout = newLinkTimeout;
        this->ini->changedField("Device","NetCamera","linkTimeout",QString::number(linkTimeout));
    }
}

int VideoParameter::getFps() const
{
    return fps;
}

void VideoParameter::setFps(int newFps)
{
    if(fps != newFps){
        fps = newFps;
        this->ini->changedField("Device","NetCamera","fps",QString::number(fps));
    }
}
