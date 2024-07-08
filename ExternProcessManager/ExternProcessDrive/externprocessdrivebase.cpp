#include "externprocessdrivebase.h"

ExternProcessDriveBase::ExternProcessDriveBase(QString name)
{
    this->externProcessName = name;
    this->start();

}

bool ExternProcessDriveBase::getIsValid() const
{
    return isValid;
}

bool ExternProcessDriveBase::getIsRunning() const
{
    return isRunning;
}

void ExternProcessDriveBase::writeDataForSharedMemory(QBuffer &buffer)
{
    this->process->externProcessWriteDataForShareMemory(this->externProcessName,buffer);
}

bool ExternProcessDriveBase::start()
{
    QString error = "";
    bool ret = this->process->getProcessStatus(this->externProcessName,error);

    if(!ret){
        qDebug()<<error;
        return ret;
    }
    connect(this->process,&ExternProcess::started,this,&ExternProcessDriveBase::startedSlot);
    ret = this->process->externProcessStart(this->externProcessName);
    return ret;
}

void ExternProcessDriveBase::startedSlot()
{
    this->isRunning = true;
}
