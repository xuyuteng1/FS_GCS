#ifndef LOGGERMANAGEMENT_H
#define LOGGERMANAGEMENT_H
#include "systemlogger.h"
#include "xlsxlogger.h"
#include "DMMM.h"
#include "logreplay.h"

class LoggerManagement : public QObject
{
public:
    LoggerManagement();

    static SystemLogger *getLogger();
    static XlsxLogger      *getXlsxLogger();
    static TextLogger *getTextLogger();
    static LogReplay *getReplay();

private:
    QList<QString> getDataLogFieldList();
    QMap<QString,QString> getDataForLinkID(int linkID);

    void connectSignalAndSlot();

private:
    static  SystemLogger *systemLogger;
    static  XlsxLogger      *xlsxLogger;
    static TextLogger       *textLogger;
    static LogReplay        *replay;

    QList<QString> dataLogFieldList;

    QTimer *timer = nullptr;

signals:


private slots:
    void timeroutSlot();

    void handle_DMMM_event(int ev, int linkid);
};

namespace Log {
    void Log_Cmd(QString text);
    void Log_Warn(QString text);
    void Log_Error(QString text);
    void Log_Info(QString text);



    QString Log_ByteToString(QByteArray);

    TextLogger *getTextLoggerPtr();
    XlsxLogger *getXlsxLoggerPtr();
    SystemLogger *getSystemLoggerPtr();
    LogReplay  *getLogReplayPtr();
}


#endif // LOGGERMANAGEMENT_H
