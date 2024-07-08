#include "systemlogger.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
SystemLogger::SystemLogger(){
    qDebug()<<"SystemLogger init";
    this->setAutoDelete(false);
}

void SystemLogger::Log_Worning(QString worning){
    if(isInit){
        LOG4CPLUS_WARN(rootLogger, worning.toLocal8Bit().data());
    }
}

void SystemLogger::Log_Error(QString error){
    if(isInit){
        LOG4CPLUS_ERROR(rootLogger, error.toLocal8Bit().data());
    }
}

void SystemLogger::Log_Info(QString info){
    if(isInit){
        LOG4CPLUS_INFO(rootLogger, info.toLocal8Bit().data());
    }
}

void SystemLogger::Log_Cmd(QString cmd){
    if(isInit){
        LOG4CPLUS_TRACE(rootLogger, cmd.toLocal8Bit().data());
    }
}

QString SystemLogger::Log_ByteToString(QByteArray array)
{
    QString retStr = "";
    for(int i = 0; i < array.count(); i++){
        int tmp = array.at(i);
        retStr.append(QString("%1").arg(QString::number(tmp,16),2,QLatin1Char('0')));
        if(i  + 1 < array.count()){
            retStr.append(" ");
        }
    }

    return retStr;
}

void SystemLogger::run()
{
    this->initLogger();
}

bool SystemLogger::initLogger(){
    QFileInfo fileInfo("urconfig.properties");
    if(!fileInfo.exists()){
        if(!fileInfo.dir().exists()){
            fileInfo.dir().mkpath(fileInfo.dir().path());
        }
        QFile file("urconfig.properties");
        if(file.open(QIODevice::Text |QIODevice::WriteOnly)){
            QTextStream stream(&file);
            stream<<QStringLiteral("log4cplus.rootLogger=TRACE,console,file,errorFile,wornfile,cmdFile\r\n");
            stream<<QStringLiteral("log4cplus.appender.console=log4cplus::ConsoleAppender\r\n");
            stream<<QStringLiteral("log4cplus.appender.console.layout=log4cplus::PatternLayout\r\n");
            stream<<QStringLiteral("log4cplus.appender.console.layout.ConversionPattern=%D{ %Y-%m-%d %H:%M:%S.%q} [%5p] %c-: %m %n\r\n");
            stream<<QStringLiteral("\r\n");

            stream<<QStringLiteral("log4cplus.appender.file=log4cplus::TimeBasedRollingFileAppender\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.Threshold=ALL\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.CreateDirs=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.Append=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.FilenamePattern=log/%d{yyyy-MM-dd}/all_%d{hh_mm_ss}.log\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.MaxHistory=1\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.CleanHistoryOnStart=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.RollOnClose=false\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.layout=log4cplus::PatternLayout\r\n");
            stream<<QStringLiteral("log4cplus.appender.file.layout.ConversionPattern=%D{ %Y-%m-%d %H:%M:%S.%q} [%5p] %c-: %m %n\r\n");
            stream<<QStringLiteral("\r\n");

            stream<<QStringLiteral("log4cplus.appender.errorFile=log4cplus::TimeBasedRollingFileAppender\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.CreateDirs=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.Append=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.FilenamePattern=log/%d{yyyy-MM-dd}/error_%d{hh_mm_ss}.log\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.MaxHistory=365\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.CleanHistoryOnStart=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.RollOnClose=false\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.layout=log4cplus::PatternLayout\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.layout.ConversionPattern=%D{ %Y-%m-%d %H:%M:%S.%q} [%5p] %c-: %m %n\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.filters.1=log4cplus::spi::LogLevelMatchFilter\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.filters.1.LogLevelToMatch=ERROR\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.filters.1.AcceptOnMatch=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.errorFile.filters.2=log4cplus::spi::DenyAllFilter\r\n");
            stream<<QStringLiteral("\r\n");

            stream<<QStringLiteral("log4cplus.appender.wornfile=log4cplus::TimeBasedRollingFileAppender\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.CreateDirs=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.Append=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.FilenamePattern=log/%d{yyyy-MM-dd}/warn_%d{hh_mm_ss}.log\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.MaxHistory=365\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.CleanHistoryOnStart=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.RollOnClose=false\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.layout=log4cplus::PatternLayout\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.layout.ConversionPattern=%D{ %Y-%m-%d %H:%M:%S.%q} [%5p] %c-: %m %n\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.filters.1=log4cplus::spi::LogLevelMatchFilter\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.filters.1.LogLevelToMatch=WARN\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.filters.1.AcceptOnMatch=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.wornfile.filters.2=log4cplus::spi::DenyAllFilter\r\n");
            stream<<QStringLiteral("\r\n");

            stream<<QStringLiteral("log4cplus.appender.cmdFile=log4cplus::TimeBasedRollingFileAppender\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.CreateDirs=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.Append=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.FilenamePattern=log/%d{yyyy-MM-dd}/cmd_%d{hh_mm_ss}.log\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.MaxHistory=365\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.CleanHistoryOnStart=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.RollOnClose=false\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.layout=log4cplus::PatternLayout\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.layout.ConversionPattern=%D{ %Y-%m-%d %H:%M:%S.%q} [%5p] %c-: %m %n\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.filters.1=log4cplus::spi::LogLevelMatchFilter\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.filters.1.LogLevelToMatch=TRACE\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.filters.1.AcceptOnMatch=true\r\n");
            stream<<QStringLiteral("log4cplus.appender.cmdFile.filters.2=log4cplus::spi::DenyAllFilter\r\n");
        }
    }

    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("urconfig.properties"));
    isInit = true;
    return true;
}
