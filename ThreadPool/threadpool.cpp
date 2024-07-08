#include "threadpool.h"


QThreadPool *ThreadPool::taskPool = nullptr;

ThreadPool::ThreadPool()
{
    threadPoolInit();
}

QThreadPool *ThreadPool::getTPool()
{
    if(taskPool == nullptr){
        threadPoolInit();
    }
    return taskPool;
}


void ThreadPool::threadPoolInit()
{
    if(taskPool == nullptr){
       taskPool = new QThreadPool();
       taskPool->setMaxThreadCount(5);
    }
}
