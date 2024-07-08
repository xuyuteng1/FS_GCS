#ifndef FILEIOTASK_H
#define FILEIOTASK_H
#include <QRunnable>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QQueue>
#include <QMutex>
#include <QThread>
#include <QString>
////////////////常见任务，文件IO读写////////////////
/* **********************************************
 * 文件IO任务，非持续性任务。
 * 步骤：
 *      1，相关参数配置
 *      2，任务执行，任务执行可直接start或在线程池中运行
 * **********************************************/
class FileReadTask : public QObject, public QRunnable{
    Q_OBJECT
public:
    FileReadTask(QString _filePath,int _signalCount = 1);
protected:
    void run();
private:
    QString filePath;
    int          signalCount;

public:
signals:
    void       fileReadDataSignal(QQueue<QString>);
    void       fileReadFinishSignal();
};



class FileWriteTask : public QRunnable{
public:
    FileWriteTask(QList<QString> data);

    int writeResults();
protected:
    void run();

private:
    QList<QString> fileWriteData;
    int writeCount = 0;

};
#endif // FILEIOTASK_H
