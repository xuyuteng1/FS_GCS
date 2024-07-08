#ifndef YJY_PHOTOELECTRICINTERFACE_H
#define YJY_PHOTOELECTRICINTERFACE_H


#include "videodeviceinterface.h"
#include <QObject>
#include <QWidget>


class YJY_PhotoElectricInterface :public VideoDeviceInterface
{
public:
    virtual ~YJY_PhotoElectricInterface(){};

//    virtual QWidget *creatorNetCameraConfigWidget() = 0;
protected slots:
    void drawImage(QImage){};
};

QT_BEGIN_NAMESPACE
#define YJY_PhotoElectricInterface_iid "gcs.DeviceInterface.YJY_PhotoElectricInterface"
Q_DECLARE_INTERFACE(YJY_PhotoElectricInterface, YJY_PhotoElectricInterface_iid)
QT_END_NAMESPACE

#endif // YJY_PHOTOELECTRICINTERFACE_H
