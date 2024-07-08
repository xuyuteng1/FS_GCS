#ifndef YJY_PHOTOELECTRIC_PLUGIN_H
#define YJY_PHOTOELECTRIC_PLUGIN_H

#include "YJY_PhotoElectricInterface.h"

class YJY_PhotoElectric_Plugin : public YJY_PhotoElectricInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID YJY_PhotoElectricInterface_iid FILE "YJY_PhotoElectric_Plugin.json")
    Q_INTERFACES(YJY_PhotoElectricInterface)

    Q_PLUGIN_METADATA(IID DeviceBaseInterface_iid)
    Q_INTERFACES(DeviceBaseInterface)



public:
    explicit YJY_PhotoElectric_Plugin(QObject *parent = nullptr);

public:
     bool start();
     bool stop();
     bool pause();

    QList<QString> getErrorStrList();

    QWidget *creatorVideoPlayWidget();
    QString    getInterFaceName();
    QString    getAbstract();
    QString    getDeviceName();


private:

    class GenericPluginPtr;
    class GenericPluginPtr *const pluginPtr = nullptr;
private:

};

#endif // YJY_PHOTOELECTRIC_PLUGIN_H
