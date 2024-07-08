#ifndef XLSXLOGGER_H
#define XLSXLOGGER_H

#include <QQueue>
#include <QList>
#include <QMap>
#include <QHash>
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxworkbook.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QRunnable>
#include "threadpool.h"
#include <QTimer>
#include <QDebug>
#include <QCoreApplication>
#include <QTextStream>
#include <QQueue>
#include <QDateTime>

QTXLSX_USE_NAMESPACE


class XlsxFileWriteTask: public QObject,public QRunnable{
    Q_OBJECT
public:
    XlsxFileWriteTask(Document *doc,QString _sheetName,QQueue<QMap<QString,QString>> value);
protected:
    void run();

private:
    Document *doc = nullptr;
    QString sheetName;
    QQueue<QMap<QString,QString>> value = {};
public:
signals:
    void writeXlsxFinishSignal();
};


class XlsxFileReadTask : public QObject,public QRunnable{
Q_OBJECT
public:
    XlsxFileReadTask(QString _filePath);
protected:
    void run();
private:
    QString filePath = {};
    QQueue<QMap<QString,QString>> xlsxData = {};

private:
    QString columnIndexToXlsxColumnIndexStr(int index);

public:
signals:
    void xlsxFileReadSignal(QString sheetName,QQueue<QMap<QString,QString>> data);

};


class TextLoggerSaveAsXlsxFileTask : public QObject, public QRunnable{
Q_OBJECT
public:
    TextLoggerSaveAsXlsxFileTask(QTextStream *textStream);

protected:
    void run();

private:


};

class TextLoggerWriteTask :  public QThread{
    Q_OBJECT
public:
    TextLoggerWriteTask();
    ~TextLoggerWriteTask();
    void taskFinished();

    class TextWrite{
    public:
        TextWrite(QTextStream *s,QMap<QString ,QString> map,QList<QString> field) : stream(s),writeVal(map),writeField(field){};
        QTextStream *stream = nullptr;
        QMap<QString ,QString> writeVal;
        QList<QString> writeField;
    };
    void newTextLoggerWrite(TextWrite text);
protected:
    void run();


private:
    QQueue<TextWrite> writeQueue;
    bool finished = false;

};

//xlsx文件模型数据结构
class XlsxSheetArgument{

public:
    XlsxSheetArgument();
    XlsxSheetArgument(QString _sheetName,QList<QString> _headList,Document *xlsx);
public:
    void initializeXlsxSheet(QString _sheetName,QList<QString> _headList,Document *xlsx);
    void addXlsxValue(QMap<QString,QString>);
    QQueue<QMap<QString, QString> > getValueMap();

private:
    QString columnIndexToXlsxColumnIndexStr(int index);
private:
    QString                                                 sheetName = {};                                     //sheet名称，页名称
    QList<QString>                                    headList = {};                                         //sheet字段列表
    QHash<QString,QString>                    headColumnNumMap = {};                    //字段与xlxs sheet位置对照如：QHash<“序号”,"A1">  (ASCII A-Z : 65 - 90)
    QHash<QString,QString>                    columnNumHeadMap = {};
    QQueue<QMap<QString,QString>>    valueMap;

    Document *xlsx = nullptr;
};


//Xlsx文件参数数据
class XlsxFileArgument : public QObject{
    Q_OBJECT
public:
    XlsxFileArgument(QString path);
    ~XlsxFileArgument();
    int addSheet(QString sheet,QList<QString>field);
    void addXlsxSheetValue(QString sheetName,QMap<QString,QString>);
    void xlsxUpdate();


private:
    QString filePath = {};                                                              //Xlsx文件路径
    Document *xlsx = nullptr;                                                           //xlsx文件句柄
    XlsxFileWriteTask *task = nullptr;
    QMap<QString,XlsxSheetArgument *>   sheetMap = {};                                    //xlsx文件sheet对照表
    QMap<QString,QList<QString>>             sheetHeadMap = {};                                //sheet.字段对照表，分页存储时使用

    bool writeFlag= false;
};




class XlsxLogger : public QObject
{
    Q_OBJECT
public:
    XlsxLogger();

public:
    //添加xlsx文件，path:文件路径，header：文件字段
    int     addXlsxFileForID(int id,QString path);                                          //绑定linkid,path 文件存储路径
    int     addXlsxFileSheetForID(int id,QString sheetName,QList<QString> fieldName);
    void   addXlsxSheetValue(int id,QString sheetName,QMap<QString,QString>);
    void   readXlsxFile(QString path);

private:
    QMap<int,XlsxFileArgument *> xlsxFileMap;                                           //多机使用
    QTimer timer;
    XlsxFileReadTask *readXlsxTask = nullptr;


private slots:
    void timeroutslot();

public:
signals:
    void xlsxFileReadSignal(QString sheetName,QQueue<QMap<QString,QString>> data);
};



class TextInfo : public QObject{
Q_OBJECT
public:
    TextInfo(int id,QString fileName,QList<QString> fieldList ,QString filePath = QCoreApplication::applicationDirPath() + "/log");
    ~TextInfo();
    void writeText(QMap<QString,QString>);
    void textLogWriteFinish();
    bool getIsValid() const;
private:
    QList<QString> fieldNameList;                                                                   //参数名称列表
    int         columnCount = 0;                                                                            //文件列数
    QString dirPath = QCoreApplication::applicationDirPath() + "/log";
    QString fileName = "";
    int id = 0;
    QFile     file;
    QTextStream *stream = nullptr;

    bool isValid = false;                                                                                     //是否有效标志


private:
    bool textInfoInitialize();

public:
signals:
    void textLoggerWriteForTask(QTextStream *,QMap<QString,QString>value,QList<QString> fieldList);

};

class TextLogger : public QObject{
   Q_OBJECT
public:
    TextLogger();
    ~TextLogger();
public:
    QList<int> getTextLoggerLinkList();
private:
    QMap<int ,QMap<QString,TextInfo *>> textStreamMap;                      //QMap<飞行器ID,QMap<文件名称，文件信息>>
    TextLoggerWriteTask *textLoggerTask = nullptr;

private slots:
    void  textLoggerWriteForTaskSlot(QTextStream *,QMap<QString,QString>value,QList<QString> fieldList);

public:
signals:


public slots:
    void textLogBeginSlot(int id, QString fileName,QList<QString> fieldList,QString filePath = QCoreApplication::applicationDirPath() + "/log");                                                                        //开始记录日志系统
    void textLogWriteSlot(int id,QString fileName,QMap<QString,QString>);                                                                                                                                                                                            //日志系统写入数据
    void textLogFinishSlot(int id,QString fileName = QString());                                                                                                                                                                                                                 //当fileName = QString()时，所有当前linkID的日志文件全部结束存储                                                                                                                              //结束记录

};



//数据记录日志系统，实现数据的存储与转换
class DataLogger {

};

#endif // XLSXLOGGER_H
