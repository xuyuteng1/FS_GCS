#ifndef PLUGINMANAGERMODEL_H
#define PLUGINMANAGERMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QDebug>
#include <QObject>
#include <QPluginLoader>
#include "loader/netcameraloader.h"
#include "loader/yjy_photoloader.h"


class PluginManagerModelItem : public QObject{
    Q_OBJECT
public:
    union DeviceLoader{
        NetCameraLoader               *netCamera;
        YJY_PhotoLoader                 *yjy_photo;
    };


public:
    PluginManagerModelItem(QString name, QString interfaceName, QString path, QString deviceAbs);

private:
    QString deviceName = {};                                                       //设备名称
    QString deviceInterfaceName = {};                                      //设备类别
    QString deviceAbstract = {};                                                 //设备简介
    QString dllPath = {};                                                              //插件路径
    DeviceLoader *device = new DeviceLoader();                  //设备

    bool        isEnable = false;                                                       //启用
    bool        isVaild = false;                                                      //是否有效
    QStringList errorList = {};                                                 //错误信息

private:
//    QVariant loader = {};
    QObject *plugin = nullptr;




public:
    void       setEnabled(bool enable);

    const QString &getDeviceName() const;
    const QString &getDeviceInterfaceName() const;
    const QString &getDeviceAbstract() const;
    const QString &getDllPath() const;
    bool getEnable() const;
    const QStringList &getErrorList() const;
    PluginManagerModelItem::DeviceLoader *getDevice();

signals:
    void pluginLoadSuccessSuccess(QString devName);
    void pluginUnLoadSuccessSuccess(QString devName);


private slots:
    void pluginLoadSuccessSlot();
    void pluginUnLoadSuccessSlot();

};


class PluginManagerModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum PluginManagerRoles{
        DeviceName = Qt::UserRole + 1,
        DeviceInterFaceName,
        DeviceAbstract,
//        DLLPath,
        ENABLED,
        ERRORSTR,
    };


public:
    PluginManagerModel();
    ~PluginManagerModel();

public:
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

    bool addNewPlugin(QString name,QString interfaceName,QString path,QString deviceAbs);

    QHash<int,QString> headNames() const;


private:
    const QString getDataStrForRowColume(int row,int colume) const;
    const QVariant getDataForRowColume(int row,int colume) const;


private:
    QMap<QString,PluginManagerModelItem *> pluginItemMap = {};
    QList<QString> pluginItemList = {};

private slots:
    void pluginLoaderSuccessSlot(QString name);
    void pluignUnLoadSuccessSlot(QString name);


public:
signals:
    void videoWidgetCreateSignal(QWidget *);
    void videoWidgetRemoveSignal(QWidget *);
};


class PluginManagerModelPtr{
public:
    PluginManagerModelPtr();
    static PluginManagerModel *getModelPtr();

private:
   static  PluginManagerModel * modelPtr;
};


#endif // PLUGINMANAGERMODEL_H
