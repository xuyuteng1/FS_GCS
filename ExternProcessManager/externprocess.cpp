#include "externprocess.h"

ExternProcess::ExternProcess()
{
    initExternProcess();
    connectSignalAndSlot();
}

qint64 ExternProcess::getProcessID(QString name)
{
    if(this->processBaseMap.find(name) != this->processBaseMap.end()){
        return this->processBaseMap.find(name).value()->getProcessID();
    }
    return 0;
}

bool ExternProcess::getProcessStatus(QString name, QString &err)
{
    if(this->processBaseMap.find(name) != this->processBaseMap.end()){
        if(this->processBaseMap.find(name).value() == nullptr){
            err  = QString("外部进程初始化失败!");
            return false;
        }

        if(!this->processBaseMap.find(name).value()->getIsValid()){
            err  = QString("外部进程初始化失败!");
            return false;
        }

        return true;
    }else{
        err  = QString("无法查询到预加载外部进程");
        return false;
    }
}


void ExternProcess::initExternProcess()
{
    errorList.clear();

    if(this->ini == nullptr){
        this->ini = new ConfigFile_Ini();
    }

    this->ini->createNewSettings("ExternProcess",QCoreApplication::applicationDirPath() + "/cfg/externprocess.ini");
    this->ini->addNewField("ExternProcess","LoggerReplay","processName",QString("LoggerReplay"),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","processPath",QCoreApplication::applicationDirPath() + "/module/LoggerReplay.exe",ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","hasInterface",false,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","hasDataExchangeSpace",false,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","hasCommunication",true,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","hasTransmit",false,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","communicationType",0,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","communicationAddress","",ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","key",QString("LoggerReplayExchangeSpace"),ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","dataExchangeSpaceSize",4096,ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);

    this->ini->addNewField("ExternProcess","LoggerReplay","IpClassName","",ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","IpWindowName","",ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);
    this->ini->addNewField("ExternProcess","LoggerReplay","arguments","",ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange);

    QList<QString> fieldList = this->ini->getAllGroups("ExternProcess");
    for(int i = 0;  i < fieldList.count() ; i++){

        ExternProcessBase::ProcessParameter parameter = {};
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"processName",parameter.processName);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"processPath",parameter.processPath);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"hasInterface",parameter.hasInterface);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"hasDataExchangeSpace",parameter.hasSharedMemory);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"hasCommunication",parameter.hasCommunication);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"hasTransmit",parameter.hasTransmit);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"communicationType",parameter.communicationType);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"communicationAddress",parameter.communicationAddress);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"key",parameter.key);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"dataExchangeSpaceSize",parameter.size);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"IpClassName",parameter.IpClassName);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"IpWindowName",parameter.IpWindowName);
        this->ini->getFieldValue("ExternProcess",fieldList.at(i),"arguments",parameter.arguments);

        if(this->processBaseMap.find(parameter.processName) != this->processBaseMap.end()){
            errorList.append(QStringLiteral("外部程序 %1 名称存在重复").arg(parameter.processName));
            continue;
        }

        if(parameter.hasSharedMemory){
            if(this->sharedMemoryKeyList.indexOf(parameter.key) != -1){
                errorList.append(QStringLiteral("数据交换空间 %1 Key存在重复").arg(parameter.key));
                continue;
            }else{
                if(parameter.key.length() == 0){
                    errorList.append(QStringLiteral("数据交换空间 Key 为空"));
                }else{
                    this->sharedMemoryKeyList.append(parameter.key);
                    if(this->sharedMemManger == nullptr){
                        this->sharedMemManger = new SharedMemManger;
                    }
                    this->sharedMemManger->addNewSharedMenory(parameter.processName,parameter.key);
                }
            }
        }

        qDebug()<<"errorList"<<errorList;
        ExternProcessBase *base = new ExternProcessBase(parameter);
        connect(base,&ExternProcessBase::started,this,&ExternProcess::started);
        this->processBaseMap.insert(base->getProcessName(),base);
    }
}

void ExternProcess::connectSignalAndSlot()
{
    connect(this->sharedMemManger,&SharedMemManger::recvDataSignal,this,&ExternProcess::externProcessSharedMemoryRecvSignal);
}

bool ExternProcess::externProcessStart(QString name)
{
    if(this->processBaseMap.find(name) != this->processBaseMap.end()){
        if(this->processBaseMap.value(name) == nullptr){
            return false;
        }
        if(this->processBaseMap.value(name)->getIsValid() == false){
            return false;
        }
        this->processBaseMap.value(name)->processStart();
        return true;
    }else{
        return false;
    }
}

void ExternProcess::externProcessWriteDataForShareMemory(QString name, QBuffer &buffer)
{
    this->sharedMemManger->writeData(name,buffer.data());
}


