#include "deviceloader.h"

DeviceLoader::DeviceLoader()
{

}

DeviceLoader::~DeviceLoader()
{

}

bool DeviceLoader::initPlugin(QString dllPath)
{
    this->loader.setFileName(dllPath);
    return true;
}

bool DeviceLoader::loadPlugin()
{
    if(!this->loader.isLoaded()){
        this->loader.load();
    }
    this->plugin = loader.instance();
    if(this->plugin){
        return true;
    }else{
        return false;
    }
    return false;
}

bool DeviceLoader::unloadPlugin()
{
    if(this->loader.isLoaded()){
        this->loader.unload();
        return true;
    }
    return false;
}
