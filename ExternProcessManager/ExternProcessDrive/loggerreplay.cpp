#include "loggerreplay.h"


LoggerReplay::LoggerReplay(QString name) : ExternProcessDriveBase(name)
{

}

QWidget *LoggerReplay::getWidget()
{
    qDebug()<<"getWidget "<<QDateTime::currentDateTime();
    if(this->widget == nullptr){
        WId winId = (WId)FindWindow(L"Qt5152QWindowIcon", L"LoggerReplay");
        QWindow *window = QWindow::fromWinId(winId);
//        window->setFlags(window->flags() | Qt::CustomizeWindowHint | Qt::WindowTitleHint); //这边可以设置一下属性
        this->widget = QWidget::createWindowContainer(window);
    }

    return this->widget;
}




//BOOL LoggerReplay::IsMainWindow(HWND handle)
//{
//    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
//}

//BOOL CALLBACK LoggerReplay::EnumWindowsCallback(HWND handle, LPARAM lParam)
//{
//    handle_data& data = *(handle_data*)lParam;
//    unsigned long process_id = 0;
//    GetWindowThreadProcessId(handle, &process_id);
//    if (data.process_id != process_id || !IsMainWindow(handle)) {
//        return TRUE;
//    }
//    data.best_handle = handle;
//    return FALSE;
//}


//通过进程id号获取主窗口句柄

//void LoggerReplay::selectTransmitAddress(QString ip, int port)
//{
//    QJsonDocument doc;
//    QJsonObject cmdObj;
//    QJsonObject parameterObj;
//    parameterObj.insert("ipaddr",ip);
//    parameterObj.insert("port",port);

//    cmdObj.insert("commond","selectTransmitAddress");
//    cmdObj.insert("parameter",parameterObj);

//    doc.setObject(cmdObj);
//    writeData(doc);
//}

//void LoggerReplay::selectReplayFile(QString filePath)
//{
//    QJsonDocument doc;
//    QJsonObject cmdObj;
//    QJsonObject parameterObj;
//    parameterObj.insert("replayFile",filePath);

//    cmdObj.insert("commond","selectReplayFile");
//    cmdObj.insert("parameter",parameterObj);

//    doc.setObject(cmdObj);
//    writeData(doc);
//}

//void LoggerReplay::selectRepalySpeed(float speed)
//{
//    QJsonDocument doc;
//    QJsonObject cmdObj;
//    QJsonObject parameterObj;
//    parameterObj.insert("replaySpeed",speed);

//    cmdObj.insert("commond","selectRepalySpeed");
//    cmdObj.insert("parameter",parameterObj);

//    doc.setObject(cmdObj);
//    writeData(doc);
//}

//void LoggerReplay::startReplay()
//{
//    QJsonDocument doc;
//    QJsonObject cmdObj;
//    QJsonObject parameterObj = {};

//    cmdObj.insert("commond","startReplay");
//    cmdObj.insert("parameter",parameterObj);

//    doc.setObject(cmdObj);
//    writeData(doc);
//}

//void LoggerReplay::pauseReplay()
//{
//    QJsonDocument doc;
//    QJsonObject cmdObj;
//    QJsonObject parameterObj = {};

//    cmdObj.insert("commond","pauseReplay");
//    cmdObj.insert("parameter",parameterObj);

//    doc.setObject(cmdObj);
//    writeData(doc);
//}

//void LoggerReplay::stopReplay()
//{
//    QJsonDocument doc;
//    QJsonObject cmdObj;
//    QJsonObject parameterObj = {};

//    cmdObj.insert("commond","stopReplay");
//    cmdObj.insert("parameter",parameterObj);

//    doc.setObject(cmdObj);
//    writeData(doc);
//}

//void LoggerReplay::writeData(QJsonDocument &doc)
//{
//    QByteArray data = doc.toJson();

//    SharedMemDataHeader header;
//    header.recver = 'M';                                    //设置主机接收
//    header.mode = 'U';                                     //设置主机使用
//    header.type = 'J';                                       //设置编码格式为Json
//    header.len = data.length();
//    qDebug()<<data<<header.len;
//    QBuffer buffer;

//    SharedMemData sharedMemData(SharedMemData::PackedType::PackData,buffer,header,data);

//    if(sharedMemData.getIsValid()){
//        this->writeDataForSharedMemory(buffer);
//    }
//}

//void LoggerReplay::readyreadSlot(QString name, QByteArray array)
//{
//    qDebug()<<"LoggerReplay recv"<<name<<array;
//}


