#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QPluginLoader>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QPluginMetaData>
#include <QFileInfo>
#include "devicebaseinterface.h"
#include <QMetaMethod>
#include "pluginmanagermodel.h"
#include <QTableView>
#include "pluginloadermanager.h"

class PluginManager : public QObject
{
public:
    PluginManager();

    QTableView *getView() const;

private:
    void pluginPreload();                                                   //插件预加载
    QStringList findFiles(const QString &startDir, QStringList filters);


private:
    PluginManagerModel *model = PluginManagerModelPtr::getModelPtr();

private slots:



public slots:

};

#endif // PLUGINMANAGER_H
