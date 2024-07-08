#include "logreplay.h"

LogReplay::LogReplay()
{

}

void LogReplay::logReplayBeginSlot(int id, QString fileName, QString filePath)
{
    if(this->replayFileMap.find(id) != this->replayFileMap.end()){
        disconnect(Qt::DMMM(),&Q_DMMM::replayDataWriteSignal,this,&LogReplay::logReplayWriteSlot);
        LogReplayFileInfo *info = this->replayFileMap.find(id).value();
        info->logReplayFinished();
        delete info;
        this->replayFileMap.remove(id);
    }

    LogReplayFileInfo *fileInfo = new LogReplayFileInfo(id,fileName,filePath);
    if(fileInfo != nullptr){
        if(!fileInfo->getIsValid()){
            delete fileInfo;
            return;
        }
        connect(Qt::DMMM(),&Q_DMMM::replayDataWriteSignal,this,&LogReplay::logReplayWriteSlot);
        this->replayFileMap.insert(id,fileInfo);
    }
}

void LogReplay::logReplayWriteSlot(int id, QDateTime time, QByteArray data)
{
    if(this->replayFileMap.find(id) != this->replayFileMap.end()){
        this->replayFileMap.find(id).value()->logReplayWriteData(time,data);
    }
}

void LogReplay::logReplayFinishSlot(int id)
{
    if(this->replayFileMap.find(id) != this->replayFileMap.end()){
        this->replayFileMap.find(id).value()->logReplayFinished();
    }
}




LogReplayFileInfo::LogReplayFileInfo(int linkID, QString fileName, QString filePath)
{
    this->fileName = fileName+ QString("_%1_").arg(QString::number(linkID)) + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss") + ".data";
    this->linkID = linkID;
    this->dirPath = filePath;
    this->isValid = initLogReplay();
}

void LogReplayFileInfo::logReplayWriteData(QDateTime time, QByteArray array)
{
    if(this->isValid && this->stream != nullptr){
        *(this->stream)<<QString("[ %1 ] ").arg(time.toString("yyyy-MM-dd hh:mm:ss.zzz"))<<array.toHex(' ')<<"\n";
        this->stream->flush();
    }
}

void LogReplayFileInfo::logReplayFinished()
{
    this->stream->flush();
    this->file.close();
}

bool LogReplayFileInfo::getIsValid() const
{
    return isValid;
}

bool LogReplayFileInfo::initLogReplay()
{
    QString filePath = this->dirPath + "/" + this->fileName;

    QDir dir(this->dirPath);
    if(!dir.exists()){
        if(!dir.mkpath(this->dirPath)){                                                          //若路径不存在则创建路径
            return false;                                                                                       //无法创建路径则返回 false
        }
    }

    this->file.setFileName(filePath);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly)){
        if(this->stream == nullptr){                                                                //初始化stream
            this->stream = new QTextStream(&file);
            this->stream->setFieldAlignment(QTextStream::AlignCenter);  //设置字段对齐方式为居中对齐
        }
    }else{
        return false;
    }
    return true;
}
