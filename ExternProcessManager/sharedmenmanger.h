#ifndef SHAREDMENMANGER_H
#define SHAREDMENMANGER_H

#include <QThread>
#include <QList>
#include <QSharedMemory>
#include <QMap>
#include <QBuffer>
#include "sharedmemdata.h"
#include <QByteArray>
class SharedMemManger : public QThread
{
    Q_OBJECT
public:
    SharedMemManger();

    void addNewSharedMenory(QString name,QString key);
protected:
    void run();

private:
    QMap<QString,QSharedMemory *> sharedMemoryMap;
    QMap<QString,QString> sharedMemKeyMap;

public slots:
    void writeData(QString name,QByteArray array);


signals:
    void recvDataSignal(QString name,QByteArray data);

};

#endif // SHAREDMENMANGER_H
