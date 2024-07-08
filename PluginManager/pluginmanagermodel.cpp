#include "pluginmanagermodel.h"

 PluginManagerModel * PluginManagerModelPtr::modelPtr = new PluginManagerModel;

PluginManagerModel::PluginManagerModel()
{

}

PluginManagerModel::~PluginManagerModel()
{

}


QVariant PluginManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        if(role == Qt::DisplayRole){
            QHash<int, QString> roles = headNames();
            return QVariant(roles[section + Qt::UserRole + 1]);
        }else {
            return QVariant();
        }
    }
    return QVariant();
}

QModelIndex PluginManagerModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex PluginManagerModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int PluginManagerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->pluginItemList.count();
}

int PluginManagerModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 5;
}

QVariant PluginManagerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int colume = index.column();

        switch(role){
        case Qt::DisplayRole:{
            return getDataStrForRowColume(row,colume);
        }case PluginManagerRoles::DeviceName:
        case PluginManagerRoles::DeviceInterFaceName:
        case PluginManagerRoles::DeviceAbstract:
        case PluginManagerRoles::ENABLED:
        case PluginManagerRoles::ERRORSTR:
            return getDataForRowColume(row,colume);
    }
    return QVariant();
}

bool PluginManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row();
    int colume = index.column();
    if(row <this->pluginItemList.count() && colume < this->columnCount()){
        QString mapKey = this->pluginItemList.at(row);
        if(this->pluginItemMap.find(mapKey) != this->pluginItemMap.end()){
            this->beginResetModel();
            PluginManagerModelItem *item = this->pluginItemMap.value(mapKey);
            if(item != nullptr){
                switch (role){
                case PluginManagerRoles::ENABLED:{
                    item->setEnabled(value.toBool());
                    break;
                }default:{
                    break;
                }
                }
            }
            this->endResetModel();
            return true;
        }
    }

    return false;
}

QHash<int, QByteArray> PluginManagerModel::roleNames() const
{
    QHash<int,QByteArray> hash = {};
    hash[DeviceInterFaceName] = "DeviceInterFaceName";
    hash[DeviceName] = "DeviceName";
    hash[DeviceAbstract] = "DeviceAbstract";
//    hash[DLLPath] = "DLLPath";
    hash[ENABLED] = "ENABLED";
    hash[ERRORSTR] = "ERRORSTR";
    return hash;
}

bool PluginManagerModel::addNewPlugin(QString name, QString interfaceName, QString path, QString deviceAbs)
{

    if(this->pluginItemList.indexOf(interfaceName) != -1 || this->pluginItemMap.find(interfaceName) != this->pluginItemMap.end()){
        //添加插件失败
        qDebug()<<QStringLiteral("添加插件失败,interfaceName : %1 ,path : %2").arg(interfaceName).arg(path);
        return false;
    }
    qDebug()<<name<<interfaceName<<path<<deviceAbs;
    this->beginResetModel();
    this->pluginItemList.append(interfaceName);
    PluginManagerModelItem *pluginItem  = new PluginManagerModelItem(name,interfaceName,path,deviceAbs);
    this->pluginItemMap.insert(interfaceName,pluginItem);
    connect(pluginItem,&PluginManagerModelItem::pluginLoadSuccessSuccess,this,&PluginManagerModel::pluginLoaderSuccessSlot);
    connect(pluginItem,&PluginManagerModelItem::pluginUnLoadSuccessSuccess,this,&PluginManagerModel::pluignUnLoadSuccessSlot);
    this->endResetModel();
    return true;
}

QHash<int, QString> PluginManagerModel::headNames() const
{
    QHash<int,QString> hash = {};
    hash[DeviceInterFaceName] = QStringLiteral("类别");
    hash[DeviceName] = QStringLiteral("设备名称");
    hash[DeviceAbstract] = QStringLiteral("设备简介");
//    hash[DLLPath] = QStringLiteral("插件路径");
    hash[ENABLED] = QStringLiteral("插件状态");
    hash[ERRORSTR] = QStringLiteral("信息");
    return hash;
}

const QString PluginManagerModel::getDataStrForRowColume(int row, int colume) const
{
    if(row <this->pluginItemList.count() && colume < this->columnCount()){
        QString mapKey = this->pluginItemList.at(row);
        if(this->pluginItemMap.find(mapKey) != this->pluginItemMap.end()){
            PluginManagerModelItem *item = this->pluginItemMap.value(mapKey);
            if(item != nullptr){
                switch(colume + Qt::UserRole +1){
                case PluginManagerRoles::DeviceName:{
                    return item->getDeviceName();
                }case PluginManagerRoles::DeviceInterFaceName:{
                    return item->getDeviceInterfaceName();
                }/*case PluginManagerRoles::DLLPath:{
                    return item->getDllPath();
                }*/case PluginManagerRoles::DeviceAbstract:{
                    return item->getDeviceAbstract();
                }case PluginManagerRoles::ENABLED:{
                    return item->getEnable() ? QStringLiteral("运行") : QStringLiteral("未运行");
                }case PluginManagerRoles::ERRORSTR:{
                    return item->getErrorList().join(';');
                }
                }
            }
        }
    }
    return "";
}

const QVariant PluginManagerModel::getDataForRowColume(int row, int colume) const
{
    if((this->pluginItemList.count() > row) && (colume < this->columnCount())){
        QString mapKey = this->pluginItemList.at(row);

        if(this->pluginItemMap.find(mapKey) != this->pluginItemMap.end()){

            PluginManagerModelItem *item = this->pluginItemMap.value(mapKey);
            if(item != nullptr){
                switch(colume + Qt::UserRole +1){
                case PluginManagerRoles::DeviceName:{
                    return item->getDeviceName();
                }case PluginManagerRoles::DeviceInterFaceName:{
                    return item->getDeviceInterfaceName();
                }/*case PluginManagerRoles::DLLPath:{
                    return item->getDllPath();
                }*/case PluginManagerRoles::DeviceAbstract:{
                    return item->getDeviceAbstract();
                }case PluginManagerRoles::ENABLED:{
                    qDebug()<<"item->getEnable() = "<<item->getEnable();
                    return item->getEnable();
                }case PluginManagerRoles::ERRORSTR:{
                    return item->getErrorList();
                }
                }
            }
        }
    }
    return QVariant();
}

void PluginManagerModel::pluginLoaderSuccessSlot(QString name)
{
    if(this->pluginItemList.indexOf(name) != -1){
        if(name == NetCameraInterface_iid){
            if(this->pluginItemMap.find(name) != this->pluginItemMap.end()){
                PluginManagerModelItem *item = this->pluginItemMap.value(name);
                if(item != nullptr){
                    if(item->getDevice()  != nullptr){

                        qDebug()<<"item->getDevice()->netCamera->getPluginWidget()->showNormal();";

//                        emit videoWidgetCreateSignal(item->getDevice()->yjy_photo->getYJY_PhotoWidget());
                        item->getDevice()->netCamera->getPluginWidget()->showNormal();
                    }
                }
            }

        }else if(name == YJY_PhotoElectricInterface_iid){
            if(this->pluginItemMap.find(name) != this->pluginItemMap.end()){
                PluginManagerModelItem *item = this->pluginItemMap.value(name);
                if(item != nullptr){

                    if(item->getDevice()  != nullptr){
//                        emit videoWidgetCreateSignal(item->getDevice()->yjy_photo->getYJY_PhotoWidget());
                        item->getDevice()->yjy_photo->getYJY_PhotoWidget()->showNormal();
                    }
                }
//                emit videoWidgetCreateSignal(item->getDevice()->yjy_photo->getYJY_PhotoWidget());
            }

        }else{

        }
    }
}

void PluginManagerModel::pluignUnLoadSuccessSlot(QString name)
{
    if(this->pluginItemList.indexOf(name) != -1){
        if(name == NetCameraInterface_iid){


        }else if(name == YJY_PhotoElectricInterface_iid){
            if(this->pluginItemMap.find(name) != this->pluginItemMap.end()){
                PluginManagerModelItem *item = this->pluginItemMap.value(name);
                if(item != nullptr){

                    if(item->getDevice()  != nullptr){
                        emit videoWidgetRemoveSignal(item->getDevice()->yjy_photo->getYJY_PhotoWidget());
                    }
                }
//                emit videoWidgetCreateSignal(item->getDevice()->yjy_photo->getYJY_PhotoWidget());
            }

        }else{

        }
    }
}

PluginManagerModelItem::PluginManagerModelItem(QString name, QString interfaceName, QString path,QString deviceAbs)
{
    this->deviceName = name;
    this->deviceInterfaceName = interfaceName;
    this->dllPath = path;
    this->deviceAbstract = deviceAbs;


   if(this->deviceInterfaceName.compare(NetCameraInterface_iid) == 0){
       this->device->netCamera = new NetCameraLoader();
       this->device->netCamera->initNetCameraLoader(this->dllPath);
       connect(this->device->netCamera,&NetCameraLoader::pluginLoadSuccessSignal,this,&PluginManagerModelItem::pluginLoadSuccessSlot);
       connect(this->device->netCamera,&NetCameraLoader::releaseResSignal,this,&PluginManagerModelItem::pluginUnLoadSuccessSlot);
    }else if(this->deviceInterfaceName.compare(YJY_PhotoElectricInterface_iid) == 0){
        this->device->yjy_photo = new YJY_PhotoLoader();
        this->device->yjy_photo->init_yjy_photo_Device(this->dllPath);
       connect(this->device->yjy_photo,&YJY_PhotoLoader::pluginLoadSuccessSignal,this,&PluginManagerModelItem::pluginLoadSuccessSlot);
       connect(this->device->yjy_photo,&YJY_PhotoLoader::releaseResSignal,this,&PluginManagerModelItem::pluginUnLoadSuccessSlot);
   }

   this->setEnabled(false);
}

PluginManagerModelItem::DeviceLoader *PluginManagerModelItem::getDevice()
{
    return device;
}


const QStringList &PluginManagerModelItem::getErrorList() const
{
    return errorList;
}

void PluginManagerModelItem::pluginLoadSuccessSlot()
{
    qDebug()<<this->deviceInterfaceName<<" load success";
    emit pluginLoadSuccessSuccess(this->deviceInterfaceName);
}

void PluginManagerModelItem::pluginUnLoadSuccessSlot()
{
    qDebug()<<this->deviceInterfaceName<<" unload success";
    emit pluginUnLoadSuccessSuccess(this->deviceInterfaceName);
}


bool PluginManagerModelItem::getEnable() const
{
    return this->isEnable;
}

const QString &PluginManagerModelItem::getDllPath() const
{
    return dllPath;
}

const QString &PluginManagerModelItem::getDeviceAbstract() const
{
    return deviceAbstract;
}

const QString &PluginManagerModelItem::getDeviceInterfaceName() const
{
    return deviceInterfaceName;
}

const QString &PluginManagerModelItem::getDeviceName() const
{
    return deviceName;
}


void PluginManagerModelItem::setEnabled(bool enable)
{
    if(this->deviceInterfaceName.compare(NetCameraInterface_iid) == 0){
        if(this->device->netCamera != nullptr){
            if(enable){
                this->device->netCamera->initNetCameraLoader(this->getDllPath());
            }else{
                emit this->device->netCamera->releaseResSignal();                   //通知释放资源
            }
        }
     }else if(this->deviceInterfaceName.compare(YJY_PhotoElectricInterface_iid) == 0){
        if(this->device->yjy_photo != nullptr){
            if(enable){
                this->device->yjy_photo->init_yjy_photo_Device(this->getDllPath());
            }else{
                emit this->device->yjy_photo->releaseResSignal();                   //通知释放资源
            }
        }
    }
    this->isEnable = enable;
    qDebug()<<this->isEnable;
}






PluginManagerModelPtr::PluginManagerModelPtr()
{

}


PluginManagerModel *PluginManagerModelPtr::getModelPtr()
{
    return modelPtr;
}
