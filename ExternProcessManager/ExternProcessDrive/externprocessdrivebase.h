#ifndef EXTERNPROCESSDRIVEBASE_H
#define EXTERNPROCESSDRIVEBASE_H
#include <QString>
#include <QObject>
#include "externprocessmanager.h"
#include "externprocess.h"
#include <QDebug>
#include <QBuffer>
class ExternProcessDriveBase : public QObject
{
    Q_OBJECT
public:
    ExternProcessDriveBase(QString name);

    bool getIsValid() const;

    bool getIsRunning() const;

public:
    QString externProcessName = "";
    bool isValid        = false;
    bool isRunning = false;
public:
    ExternProcess *process = ExternProcessManager::getExternProcess();


public:
    void writeDataForSharedMemory(QBuffer &data);

public slots:
    bool start();

    void startedSlot();
};

#endif // EXTERNPROCESSDRIVEBASE_H
