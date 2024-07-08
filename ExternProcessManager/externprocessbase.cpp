#include "externprocessbase.h"

ExternProcessBase::ExternProcessBase(ProcessParameter p)
{
    this->parameter = p;
    initExternProcess();
}

const QString &ExternProcessBase::getProcessName() const
{
    return parameter.processName;
}

void ExternProcessBase::setProcessName(const QString &newProcessName)
{
    parameter.processName = newProcessName;
}

const QString &ExternProcessBase::getProcessPath() const
{
    return parameter.processPath;
}

void ExternProcessBase::setProcessPath(const QString &newProcessPath)
{
    parameter.processPath = newProcessPath;
}

bool ExternProcessBase::getHasInterface() const
{
    return parameter.hasInterface;
}

void ExternProcessBase::setHasInterface(bool newHasInterface)
{
    parameter.hasInterface = newHasInterface;
}

bool ExternProcessBase::getHasSharedMemory() const
{
    return parameter.hasSharedMemory;
}

void ExternProcessBase::setHasSharedMemory(bool newHasSharedMemory)
{
    parameter.hasSharedMemory = newHasSharedMemory;
}

bool ExternProcessBase::getHasCommunication() const
{
    return parameter.hasCommunication;
}

void ExternProcessBase::setHasCommunication(bool newHasCommunication)
{
    parameter.hasCommunication = newHasCommunication;
}

bool ExternProcessBase::getHasTransmit() const
{
    return parameter.hasTransmit;
}

void ExternProcessBase::setHasTransmit(bool newHasTransmit)
{
   parameter. hasTransmit = newHasTransmit;
}

uchar ExternProcessBase::getCommunicationType() const
{
    return parameter.communicationType;
}

void ExternProcessBase::setCommunicationType(uchar newCommunicationType)
{
    parameter.communicationType = newCommunicationType;
}

const QString &ExternProcessBase::getCommunicationAddress() const
{
    return parameter.communicationAddress;
}

void ExternProcessBase::setCommunicationAddress(const QString &newCommunicationAddress)
{
    parameter.communicationAddress = newCommunicationAddress;
}

const QString &ExternProcessBase::getKey() const
{
    return parameter.key;
}

void ExternProcessBase::setKey(const QString &newKey)
{
    parameter.key = newKey;
}

int ExternProcessBase::getSize() const
{
    return parameter.size;
}

void ExternProcessBase::setSize(int newSize)
{
    parameter.size = newSize;
}

const QString &ExternProcessBase::getIpClassName() const
{
    return parameter.IpClassName;
}

void ExternProcessBase::setIpClassName(const QString &newIpClassName)
{
    parameter.IpClassName = newIpClassName;
}

const QString &ExternProcessBase::getIpWindowName() const
{
    return parameter.IpWindowName;
}

void ExternProcessBase::setIpWindowName(const QString &newIpWindowName)
{
    parameter.IpWindowName = newIpWindowName;
}

bool ExternProcessBase::getIsValid() const
{
    return isValid;
}

bool ExternProcessBase::getIsRunning() const
{
    return isRunning;
}

qint64 ExternProcessBase::getProcessID()
{
    return this->process->processId();
}

void ExternProcessBase::initExternProcess()
{
    this->isValid = false;
    this->errorList.clear();

    QFileInfo info(parameter.processPath);
    if(!info.isExecutable()){
        this->errorList.append(QStringLiteral("应用程序 ‘ %1 ’不存在").arg(parameter.processPath));
    }

    if(parameter.hasSharedMemory == true){
        if(parameter.size < 16){
            this->errorList.append(QStringLiteral("共享内存大小设置错误，当前为%1, 最小16Byte").arg(QString::number(parameter.size)));
        }
    }

    if(errorList.count() == 0){                             //当前置参数无误时，初始化进程
        this->isValid  = true;
    }
}

void ExternProcessBase::processStart()
{
    if(this->isValid){
        if(this->process != nullptr){
            this->processClose();
        }
        this->process = new QProcess(this);
        connect(this->process,&QProcess::started,[=]{emit this->started();});
        this->process->start(parameter.processPath,parameter.arguments.split(";"));
    }
}

void ExternProcessBase::processClose()
{
    if(this->process->state() == QProcess::Running){
        this->process->close();
        this->process->waitForFinished(3000);
    }

    this->process->deleteLater();
    this->process = nullptr;
}

