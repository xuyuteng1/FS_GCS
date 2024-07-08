#ifndef ENUMDEF_H
#define ENUMDEF_H

#include <QString>
//#include "../Common/loggerinterface.h"
//#include "../Common/loggerinterface.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>

//namespace Log {
//    static LoggerInterface *logger  = nullptr;
//    inline void Log_Cmd(QString text) {     if(logger){logger->Log_Cmd(text);}}
//    inline void Log_Warn(QString text){     if(logger){logger->Log_Worning(text);}}
//    inline void Log_Error(QString text){    if(logger){logger->Log_Error(text);}}
//    inline void Log_Info(QString text)   {     if(logger){logger->Log_Info(text);}}

//    inline void loggerInit(){
//        QDir pluginsDir(QCoreApplication::applicationDirPath());
//        pluginsDir.cd("debug");
//        pluginsDir.cd("plugin");
//        pluginsDir.cd("common");
//        // 遍历插件目录
////         qDebug()<<pluginsDir.absolutePath();
//        foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
//            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));

//            QFileInfo info(fileName);
//            if(info.completeSuffix().compare("dll") == 0){                  //只加载dll文件
//                QObject *plugin = pluginLoader.instance();
//                if (plugin) {
//                    logger = qobject_cast<LoggerInterface *>(plugin);
//                    if (logger == nullptr) {
//                        QMessageBox::information(nullptr, "错误", "插件加载失败");
//                    }
//                }else{
//                        qDebug()<<fileName<<"is loaded failed: "<<pluginLoader.errorString();
//                }
//            }
//        }
//    }
//};

#endif // ENUMDEF_H
