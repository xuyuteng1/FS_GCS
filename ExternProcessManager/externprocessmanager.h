#ifndef EXTERNPROCESSMANAGER_H
#define EXTERNPROCESSMANAGER_H
#include "externprocess.h"


class ExternProcessManager
{
public:
    ExternProcessManager();


public:
    static ExternProcess *getExternProcess();                   //使用getExternProcess访问  externProcess防止   externProcess = nullptr


    static ExternProcess * externProcess;

private:
};

#endif // EXTERNPROCESSMANAGER_H
