#ifndef YJY_PHOTOLOADER_H
#define YJY_PHOTOLOADER_H

#include "deviceloader.h"
#include <QObject>
#include "YJY_PhotoElectricInterface.h"

class YJY_PhotoLoader :  public DeviceLoader
{
public:
    YJY_PhotoLoader();

    bool init_yjy_photo_Device(QString dllPath);
    QWidget *getYJY_PhotoWidget();

private:
    YJY_PhotoElectricInterface * yjy_photo = nullptr;


public slots:
    void unLoadPluginSlot();

};

#endif // YJY_PHOTOLOADER_H
