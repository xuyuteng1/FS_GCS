#include "externprocessmanager.h"

ExternProcess * ExternProcessManager::externProcess = nullptr;

ExternProcessManager::ExternProcessManager()
{
    if(externProcess == nullptr){
        externProcess = new ExternProcess();
    }
}

ExternProcess *ExternProcessManager::getExternProcess()
{
    if(externProcess == nullptr){
        externProcess = new ExternProcess();
    }
    return externProcess;
}
