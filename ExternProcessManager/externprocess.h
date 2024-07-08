#ifndef EXTERNPROCESS_H
#define EXTERNPROCESS_H

#include <QProcess>
#include <QSharedMemory>
#include <QMap>
#include "sharedmenmanger.h"
#include "externprocessbase.h"
#include "configfile_ini.h"
#include <QDebug>
#include <QBuffer>
class ExternProcess : public QObject
{
    Q_OBJECT
public:
    ExternProcess();
    qint64 getProcessID(QString name);;
    bool getProcessStatus(QString name,QString &err);                                    //获取外部进程状态
private:
    SharedMemManger *sharedMemManger = nullptr;                                     //外部程序共享内存管理器

    QMap<QString,ExternProcessBase *> processBaseMap;                             //所有预加载进程

    ConfigFile_Ini *ini = nullptr;

    QList<QString> errorList = {};

    QList<QString> sharedMemoryKeyList = {};
private:
    void    initExternProcess();                                                                         //初始化外部进程管理，读取配置文件，校验路径
    void    connectSignalAndSlot();
public slots:
    bool    externProcessStart(QString name);
    void    externProcessWriteDataForShareMemory(QString name,QBuffer &buffer);


public:
signals:
    void    readyReadSignal(QByteArray);
    void    externProcessSharedMemoryRecvSignal(QString name,QByteArray buffer);
    void    started();



};

#endif // EXTERNPROCESS_H
