#ifndef DEVICEBASEINTERFACE_H
#define DEVICEBASEINTERFACE_H
#include <QString>
#include <QObject>
class DeviceBaseInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~DeviceBaseInterface(){};
    virtual QString     getInterFaceName() = 0;
    virtual QString     getDeviceName() = 0;
    virtual QString    getAbstract() = 0;
};


QT_BEGIN_NAMESPACE
#define DeviceBaseInterface_iid "gcs.DeviceInterface.DeviceBaseInterface"
Q_DECLARE_INTERFACE(DeviceBaseInterface, DeviceBaseInterface_iid)
QT_END_NAMESPACE
#endif // DEVICEBASEINTERFACE_H
