#include "genericplugin.h"

#include "videoplaywidget.h"
#include "videoconfigwidget.h"
#include "videoparameter.h"


class GenericPlugin::GenericPluginPtr{
public:
    GenericPluginPtr();

public:
     friend class GenericPlugin;
private:
    VideoPlayWidget *videoPlayWidget = nullptr;
    VideoConfigWidget *videoConfigWidget = nullptr;
    VideoParameter     *data = new VideoParameter();

    VideoCodec *video = nullptr;
private:
    QWidget *creatorVideoPlayWidget();
    QWidget *creatorNetCameraConfigWidget();

    void        drawImage(QImage img);
};

GenericPlugin::GenericPluginPtr::GenericPluginPtr()
{

}


QWidget *GenericPlugin::GenericPluginPtr::creatorVideoPlayWidget()
{
    if(this->videoPlayWidget == nullptr){
        this->videoPlayWidget = new VideoPlayWidget();
    }

    return this->videoPlayWidget;
}

QWidget *GenericPlugin::GenericPluginPtr::creatorNetCameraConfigWidget()
{
    if(this->videoConfigWidget == nullptr){
        this->videoConfigWidget = new VideoConfigWidget();
    }

    return this->videoConfigWidget;
}

void GenericPlugin::GenericPluginPtr::drawImage(QImage img)
{
//    if(this->videoPlayWidget != nullptr){
//        this->videoPlayWidget->drawImageSlot(img);
//    }
}





GenericPlugin::GenericPlugin(QObject *parent) : pluginPtr(new GenericPluginPtr())
{

}

bool GenericPlugin::start()
{
    if(this->pluginPtr->video == nullptr){
        this->pluginPtr->video = new VideoCodec();
        connect(this->pluginPtr->video,&VideoCodec::videoDataOutput,this,&GenericPlugin::drawImage);

//        return this->pluginPtr->video->videoStart(this->pluginPtr->data->getUrl(),this->pluginPtr->data->getParameterMap());
    }
    return false;
}

bool GenericPlugin::stop()
{
    if(this->pluginPtr->video != nullptr){
        return this->pluginPtr->video->videoStop();
    }
    return false;
}

bool GenericPlugin::pause()
{    if(this->pluginPtr->video != nullptr){
        return this->pluginPtr->video->videoPause();
    }
    return false;
}

QList<QString> GenericPlugin::getErrorStrList()
{
    if(this->pluginPtr->video != nullptr){
        return this->pluginPtr->video->getErrorStrList();
    }
    return QList<QString>();
}

QWidget *GenericPlugin::creatorVideoPlayWidget()
{
    return this->pluginPtr->creatorVideoPlayWidget();
}

QWidget *GenericPlugin::creatorNetCameraConfigWidget()
{
    return this->pluginPtr->creatorNetCameraConfigWidget();
}

QString GenericPlugin::getInterFaceName()
{
    return QString(NetCameraInterface_iid);
}

QString GenericPlugin::getAbstract()
{
    return QStringLiteral("通用网络视频流拉取插件，支持rtsp、tcp、udp模式视频码流，支持h264、h265编码格式。");
}

QString GenericPlugin::getDeviceName()
{
    return QStringLiteral("网络摄像头");
}


void GenericPlugin::drawImage(QImage image)
{
    if(this->pluginPtr != nullptr){
        this->pluginPtr->drawImage(image);
    }
}
