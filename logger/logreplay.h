#ifndef LOGREPLAY_H
#define LOGREPLAY_H
#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QByteArray>
#include <QDir>
#include "DMMM.h"


class LogReplayFileInfo{
public:
    LogReplayFileInfo(int linkID,QString fileName = "data",QString filePath = QCoreApplication::applicationDirPath() + "/data");
    void logReplayWriteData(QDateTime,QByteArray);
    void logReplayFinished();
    bool getIsValid() const;
private:
    QString dirPath = QCoreApplication::applicationDirPath() + "/data";
    QString fileName = "";
    QTextStream *stream = nullptr;
    QFile file;
    int linkID = 0;

    bool isValid = false;
private:
    bool initLogReplay();
    QString byteArrayToString(QByteArray);

};


class LogReplay : public QObject
{
    Q_OBJECT
public:
    LogReplay();

private:
    QMap<int,LogReplayFileInfo *>replayFileMap;

public slots:
    void logReplayBeginSlot(int id, QString fileName  = "data",QString filePath = QCoreApplication::applicationDirPath() + "/data");                                                                                                 //开始记录日志系统
    void logReplayWriteSlot(int id,QDateTime,QByteArray);                                                                                                                                                                                                                     //日志系统写入数据
    void logReplayFinishSlot(int id);
};

#endif // LOGREPLAY_H
