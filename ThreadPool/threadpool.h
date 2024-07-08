#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QThreadPool>
#include <QObject>
#include <QQueue>
#include <QRunnable>



class ThreadPool : public QObject
{
public:
    ThreadPool();
    static QThreadPool *getTPool() ;

private:
    static void threadPoolInit();
private:
    static QThreadPool *taskPool;
    QQueue <QRunnable *>taskQueue;
};


namespace TPool {
    static QThreadPool *tPool = ThreadPool::getTPool();
}


#endif // THREADPOOL_H
