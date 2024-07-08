#ifndef SYSTEMLOGGER_H
#define SYSTEMLOGGER_H

#include <QDebug>
#include <QtPlugin>
#include "log4cplus/loggingmacros.h"
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/initializer.h>
#include "log4cplus/logger.h"
#include "log4cplus/fileappender.h"
#include <QCoreApplication>
#include <QDateTime>
#include "log4cplus/loglevel.h"
#include <QRunnable>
#include <QObject>
#include <QDateTime>
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

class SystemLogger : public QObject,public QRunnable{
    Q_OBJECT
public:
    SystemLogger();
    void Log_Worning(QString worning);
    void Log_Error(QString error);
    void Log_Info(QString info);
    void Log_Cmd(QString cmd);

    QString Log_ByteToString(QByteArray);

protected:
    void run();
private:
    bool initLogger();

private:
    Logger rootLogger=  Logger::getRoot();
    bool isInit = false;
};

#endif // SYSTEMLOGGER_H
