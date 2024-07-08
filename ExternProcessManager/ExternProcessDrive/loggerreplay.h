#ifndef LOGGERREPLAY_H
#define LOGGERREPLAY_H
#include <QString>
#include <QByteArray>
#include "externprocessdrivebase.h"
#include "sharedmemdata.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QWidget>
#include <QWindow>
#include <windows.h>


class LoggerReplay : private ExternProcessDriveBase
{
    Q_OBJECT
public:
    //自定义结构体
    struct handle_data {
        unsigned long process_id;
        HWND best_handle;
    };

public:
    LoggerReplay(QString name = QStringLiteral("LoggerReplay"));

    QWidget *getWidget();
private:


//    BOOL IsMainWindow(HWND handle);
//    BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
//    HWND FindMainWindow(unsigned long process_id);//通过进程id号获取主窗口句柄


private:
    QWidget *widget = nullptr;
public slots:



private slots:
//    void processStartedSlot();


//    void selectTransmitAddress(QString ip,int port);
//    void selectReplayFile(QString filePath);
//    void selectRepalySpeed(float speed);
//    void startReplay();                                         //开始
//    void pauseReplay();                                       //暂停
//    void stopReplay();                                         //停止


//private:
//    void writeData(QJsonDocument &doc);


//private slots:
//    void readyreadSlot(QString name,QByteArray array);



};

#endif // LOGGERREPLAY_H
