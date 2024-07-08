#include "netcameraloader.h"

NetCameraLoader::NetCameraLoader()
{
    this->hasConfigWidget = true;
    this->hasInterface = true;
}

NetCameraLoader::~NetCameraLoader()
{

}

bool NetCameraLoader::initNetCameraLoader(QString dllPath)
{
    bool status = initPlugin(dllPath);
    if(!status){
        return status;
    }
    if(this->loadPlugin()){
        if(this->plugin){
            this->netCamera  = qobject_cast<NetCameraInterface *>(this->plugin);
            if(this->netCamera){
                this->netCamera->start();
                emit this->pluginLoadSuccessSignal();
                return true;
            }
            return false;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool NetCameraLoader::getHasConfigWidget()
{
    return this->hasConfigWidget;
}

bool NetCameraLoader::getHasInterFace()
{
    return this->hasInterface;
}

QWidget *NetCameraLoader::getPluginWidget()
{
    return this->netCamera->creatorVideoPlayWidget();
}

QWidget *NetCameraLoader::getPluginConfigWidget()
{
    return this->netCamera->creatorNetCameraConfigWidget();
}


