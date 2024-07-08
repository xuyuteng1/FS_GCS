#ifndef NETCAMERALOADER_H
#define NETCAMERALOADER_H

#include <QObject>
#include "deviceloader.h"
#include "netcamerainterface.h"
#include <QToolBox>

class NetCameraLoader : public DeviceLoader
{
public:
    NetCameraLoader();
    ~NetCameraLoader();

    bool initNetCameraLoader(QString dllPath);
    bool getHasConfigWidget();
    bool getHasInterFace();

    QWidget *getPluginWidget();
    QWidget *getPluginConfigWidget();
private:
    NetCameraInterface *netCamera = nullptr;

private:
    bool    isValid = false;

public:
signals:

};

#endif // NETCAMERALOADER_H
