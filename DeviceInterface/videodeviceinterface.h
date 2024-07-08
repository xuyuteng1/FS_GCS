#ifndef VIDEODEVICEINTERFACE_H
#define VIDEODEVICEINTERFACE_H

#include <QObject>
#include <QWidget>
#include "devicebaseinterface.h"

class VideoDeviceInterface : public DeviceBaseInterface
{
    Q_OBJECT
public:
    virtual ~VideoDeviceInterface(){};

    virtual  bool start() = 0;
    virtual  bool stop() = 0;
    virtual  bool pause() = 0;

    virtual QList<QString> getErrorStrList() = 0;
    virtual QWidget *creatorVideoPlayWidget() = 0;

protected slots:
    virtual void drawImage(QImage) = 0;
};

QT_BEGIN_NAMESPACE
#define VideoDeviceInterface_iid "gcs.DeviceInterface.VideoDevice"
Q_DECLARE_INTERFACE(VideoDeviceInterface, VideoDeviceInterface_iid)
QT_END_NAMESPACE

#endif // VIDEODEVICEINTERFACE_H
