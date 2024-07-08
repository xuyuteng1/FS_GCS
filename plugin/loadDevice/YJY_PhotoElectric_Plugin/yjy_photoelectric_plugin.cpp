#include "yjy_photoelectric_plugin.h"
#include "widget.h"

class YJY_PhotoElectric_Plugin::GenericPluginPtr{
public:
    GenericPluginPtr();

public:
     friend class YJY_PhotoElectric_Plugin;
private:
    VideoWidget *videoPlayWidget = nullptr;

private:
    QWidget *creatorVideoPlayWidget();

    void        drawImage(QImage img);
};


YJY_PhotoElectric_Plugin::GenericPluginPtr::GenericPluginPtr()
{
    Q_DMMM dmmm;
}

QWidget *YJY_PhotoElectric_Plugin::GenericPluginPtr::creatorVideoPlayWidget()
{
    qDebug()<<"QWidget *YJY_PhotoElectric_Plugin::GenericPluginPtr::creatorVideoPlayWidget()";
    if(this->videoPlayWidget == nullptr){
        this->videoPlayWidget = new VideoWidget();
    }
    return this->videoPlayWidget;
}






YJY_PhotoElectric_Plugin::YJY_PhotoElectric_Plugin(QObject *parent) : pluginPtr(new  YJY_PhotoElectric_Plugin::GenericPluginPtr())
{
    qDebug()<<"YJY_PhotoElectric_Plugin::YJY_PhotoElectric_Plugin(QObject *parent) ";
}


bool YJY_PhotoElectric_Plugin::start()
{
//    if(this->pluginPtr->video == nullptr){
//        this->pluginPtr->video = new VideoCodec();
//        connect(this->pluginPtr->video,&VideoCodec::videoDataOutput,this,&YJY_PhotoElectric_Plugin::drawImage);
//    }
    return false;
}

bool YJY_PhotoElectric_Plugin::stop()
{
//    if(this->pluginPtr->video != nullptr){
//        return this->pluginPtr->video->videoStop();
//    }
    return false;
}

bool YJY_PhotoElectric_Plugin::pause()
{
    /*if(this->pluginPtr->video != nullptr){
        return this->pluginPtr->video->videoPause();
    }*/
    return false;
}

QList<QString> YJY_PhotoElectric_Plugin::getErrorStrList()
{
//    if(this->pluginPtr->video != nullptr){
//        return this->pluginPtr->video->getErrorStrList();
//    }
    return QList<QString>();
}

QWidget *YJY_PhotoElectric_Plugin::creatorVideoPlayWidget()
{
    qDebug()<<"QWidget *YJY_PhotoElectric_Plugin::creatorVideoPlayWidget()";
    return this->pluginPtr->creatorVideoPlayWidget();
}


QString YJY_PhotoElectric_Plugin::getInterFaceName()
{
    return QString(YJY_PhotoElectricInterface_iid);
}

QString YJY_PhotoElectric_Plugin::getAbstract()
{
    return QStringLiteral("支持YJY光电设备控制与数据接收");
}

QString YJY_PhotoElectric_Plugin::getDeviceName()
{
    return QStringLiteral("YJY光电设备");
}



