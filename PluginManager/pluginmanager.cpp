#include "pluginmanager.h"

PluginManager::PluginManager()
{
    if(this->model == nullptr){
        this->model = new PluginManagerModel();
    }
    pluginPreload();
}



//预加载、读取插件信息
void PluginManager::pluginPreload()
{
    qDebug()<<QCoreApplication::libraryPaths();
    //获取当前应用程序所在路径
    QDir pluginsDir(QCoreApplication::applicationDirPath());
    //切换到插件目录
    qDebug()<<"dir::"<<pluginsDir;
    pluginsDir.cd("plugins");

    pluginsDir.cd("loadDevice");

    QStringList list = findFiles(pluginsDir.path(),QStringList()<<"*.dll");
    qDebug()<<list;
    for(int i = 0; i < list.count(); i++){
        QPluginLoader pluginLoader(list.at(i));
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            //插件名称
            auto *netcamera = qobject_cast<DeviceBaseInterface *>(plugin);
            if(netcamera != nullptr){
                this->model->addNewPlugin(netcamera->getDeviceName(),netcamera->getInterFaceName(),list.at(i),netcamera->getAbstract());
                pluginLoader.unload();
            }else{
                qDebug()<<QStringLiteral("未识别插件");
            }
        }else{
            qDebug()<<pluginLoader.errorString();
        }
    }
}

QStringList PluginManager::findFiles(const QString &startDir, QStringList filters)
{
    QStringList names;
    QDir dir(startDir);
    qDebug()<<startDir;
    //搜索当前目录符合条件的文件
    foreach (QString file, dir.entryList(filters, QDir::Files)){
        names += startDir + '/' + file;
    }

    //搜索当前目录的子目录符合条件的文件
    foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        names += findFiles(startDir + '/' + subdir, filters);

    return names;
}



