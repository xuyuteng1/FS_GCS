#ifndef DEVICELOADER_H
#define DEVICELOADER_H

#include <QObject>
#include <QPluginLoader>
class DeviceLoader : public QObject
{
    Q_OBJECT
public:
    DeviceLoader();
    ~DeviceLoader();
    virtual bool    initPlugin(QString dllPath);                         //初始化插件
    virtual bool    loadPlugin();                                                   //加载插件
    virtual bool    unloadPlugin();                                              //卸载插件

protected:
    QObject *plugin = nullptr;
    QPluginLoader loader;


    bool    hasConfigWidget = false;
    bool    hasInterface = false;


public:
signals:
    void pluginLoadSuccessSignal();
    void pluginUnLoadSuccessSignal();

    void releaseResSignal();                    //通知释放资源

};

#endif // DEVICELOADER_H
