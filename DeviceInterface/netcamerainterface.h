#ifndef NETCAMERAINTERFACE_H
#define NETCAMERAINTERFACE_H

#include "videodeviceinterface.h"
#include <QObject>
#include <QWidget>


class NetCameraInterface :public VideoDeviceInterface
{
public:
    virtual ~NetCameraInterface(){};

    virtual QWidget *creatorNetCameraConfigWidget() = 0;

};

QT_BEGIN_NAMESPACE
#define NetCameraInterface_iid "gcs.DeviceInterface.NetCamera"
Q_DECLARE_INTERFACE(NetCameraInterface, NetCameraInterface_iid)
QT_END_NAMESPACE
#endif // NETCAMERAINTERFACE_H
