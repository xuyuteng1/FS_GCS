#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include <QGenericPlugin>
#include "netcamerainterface.h"
#include "videocodec.h"
#include "devicebaseinterface.h"


class GenericPlugin : public NetCameraInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID NetCameraInterface_iid FILE "NetCamera.json")
    Q_INTERFACES(NetCameraInterface)

    Q_PLUGIN_METADATA(IID DeviceBaseInterface_iid)
    Q_INTERFACES(DeviceBaseInterface)

public:
    explicit GenericPlugin(QObject *parent = nullptr);

public:
     bool start();
     bool stop();
     bool pause();

    QList<QString> getErrorStrList();

    QWidget *creatorVideoPlayWidget();
    QWidget *creatorNetCameraConfigWidget();
    QString    getInterFaceName();
    QString    getAbstract();
    QString    getDeviceName();
protected slots:
    void drawImage(QImage);

private:

    class GenericPluginPtr;
    class GenericPluginPtr *const pluginPtr = nullptr;
private:


};

#endif // GENERICPLUGIN_H
