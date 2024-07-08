#include "yjy_photoloader.h"

YJY_PhotoLoader::YJY_PhotoLoader()
{

}

bool YJY_PhotoLoader::init_yjy_photo_Device(QString dllPath)
{
    bool status = initPlugin(dllPath);
    if(!status){
        return status;
    }
    if(this->loadPlugin()){
        if(this->plugin){
            qDebug()<<"this.plugin != nullptr";
            this->yjy_photo  = qobject_cast<YJY_PhotoElectricInterface *>(this->plugin);
            if(this->yjy_photo){
                this->yjy_photo->start();
                emit this->pluginLoadSuccessSignal();
                return true;
            }
            return false;
        }else{
            return false;
        }
    }else{
    }

    return false;
}

QWidget *YJY_PhotoLoader::getYJY_PhotoWidget()
{
    return this->yjy_photo->creatorVideoPlayWidget();
}

void YJY_PhotoLoader::unLoadPluginSlot()
{
    this->unloadPlugin();
}

