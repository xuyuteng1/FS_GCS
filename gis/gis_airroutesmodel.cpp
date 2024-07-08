#include "gis_airroutesmodel.h"

GIS_AirRoutesModel::GIS_AirRoutesModel(QObject *parent)
    : QAbstractItemModel(parent)
{


}

QVariant GIS_AirRoutesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        switch(role){
            case Qt::DisplayRole:{
                if(section == 0){
                    return QVariant(QString("航线编号").toUtf8());
                }else if(section == 1){
                    return QVariant(QString("航点编号").toUtf8());
                }else{
                    return QVariant();
                }
            }case Qt::TextAlignmentRole:{
                return Qt::AlignCenter;
            }case Qt::BackgroundRole:{
                return QColor(200,200,200);             //无效，需要修改
            }case Qt::FontRole:{
                return QFont("SimHei",13);
            }
        }
    }
    return QVariant();
}

QModelIndex GIS_AirRoutesModel::index(int row, int column, const QModelIndex &parent) const
{

    Q_UNUSED(parent);
    // FIXME: Implement me!
    return createIndex(row,column);
}

QModelIndex GIS_AirRoutesModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    // FIXME: Implement me!
    return QModelIndex();
}

int GIS_AirRoutesModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid())
        return 0;
    return this->routesList.count();
    // FIXME: Implement me!
}

int GIS_AirRoutesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    // FIXME: Implement me!
    return 1;
}

QVariant GIS_AirRoutesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }

    int row = index.row();
    int column = index.column();

    if(row < 0 || row > this->routesList.count() || row > this->routesMap.count()){
        return QVariant();
    }
    int key = this->routesList[row];

    if(this->routesMap.find(key) == this->routesMap.end()){
        return QVariant();
    }

    GIS_AirRouteItemModel *itemModel = this->routesMap.find(key).value();

    switch(role){
        case (Qt::TextAlignmentRole):
            return Qt::AlignCenter;
        case (Qt::DisplayRole):
        {
            switch(column + Qt::UserRole + 1){
            case DATA_RoutesID:
                return QString("%1").arg(key/*,4,10,QLatin1Char('0')*/);
//                return key;
            default:
                return QVariant();
            }
            default:
                return QVariant();
        }case (Qt::EditRole):{
            return QVariant();
        }case DATA_RouteModel:{
            return QVariant::fromValue(itemModel);
        }case Qt::FontRole:{
            return QFont("SimHei",15);
        }case Qt::TextColorRole:{
        if(row == const_cast<GIS_AirRoutesModel *>(this)->getRoutesIndexForRoutesID(this->currentRouteID)){
            return QColor(20,200,20);
        }else{
            return QColor(200,200,200);
        }
        }case DATA_RoutesID:{
            return key;
        }case DATA_RoutePath:{                      //获取航线航点
            return  QVariant::fromValue<QList<QGeoCoordinate>>(itemModel->getRoutePath());
        }case DATA_CurrentRouteID:{
            return this->currentRouteID;
        }case Qt::BackgroundRole:{
            if(row == const_cast<GIS_AirRoutesModel *>(this)->getRoutesIndexForRoutesID(this->currentRouteID)){
                return QColor(160,60,60);
            }else{
                return QColor(30,30,130);
            }
        }
    }

    // FIXME: Implement me!
    return QVariant();
}

bool GIS_AirRoutesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    Q_UNUSED(index);
    switch(role){
    case DATA_CurrentRouteID:{
        this->beginResetModel();
        this->currentRouteID = value.toInt();
        this->endResetModel();
        emit currentRoutesChangedSignal();
        return true;
    }
    }

    return false;
}

int GIS_AirRoutesModel::createNewRoute(int id)
{
//    if(this->routesList.indexOf(id) != -1){
//        this->beginResetModel();
//        this->routesMap.find(id).value()->removeAllPoint();
//        this->endResetModel();
//        return -1;
//    }
    qDebug()<<"createNewRoute : "<<id<<(this->routesMap.find(id) != this->routesMap.end());
    if(this->routesMap.find(id) != this->routesMap.end()){
        this->beginResetModel();
        this->routesMap.find(id).value()->removeAllPoint();
        this->endResetModel();
    }else{
        this->beginResetModel();
        GIS_AirRouteItemModel *model = new GIS_AirRouteItemModel();

    connect(model,&GIS_AirRouteItemModel::beginResetModelSignal,this,&GIS_AirRoutesModel::beginResetModel);
    connect(model,&GIS_AirRouteItemModel::endResetModelSignal,this,&GIS_AirRoutesModel::endResetModel);

        this->routesList.append(id);
        this->routesMap.insert(id,model);
        this->currentRouteID = id;
        this->endResetModel();
    }
    return 0;
}

int GIS_AirRoutesModel::addRouteItemPoint(int id, double lng, double lat, int alititude, int alititudeModel, int commondID, QVariant parameter1, QVariant parameter2, QVariant parameter3, QVariant parameter4)
{
    if(this->routesMap.find(id) == this->routesMap.end()){
        return -1;
    }

    GIS_AirRouteItemModel *model = this->routesMap.find(id).value();
    return model->createItemPoint(lng,lat,alititude,alititudeModel,commondID,parameter1,parameter2,parameter3,parameter4);

}

int GIS_AirRoutesModel::removeRoute(int routesRow)
{
    if(this->routesMap.find(this->routesList.at(routesRow)) != this->routesMap.end()){
        GIS_AirRouteItemModel *model = this->routesMap.find(this->routesList.at(routesRow)).value();
        this->beginResetModel();
        this->routesMap.remove(this->routesList.at(routesRow));
        this->routesList.removeAt(routesRow);
        this->endResetModel();
        model->deleteLater();
        return 0;
    }else{
        return -1;
    }
}

int GIS_AirRoutesModel::removeRouteForID(int id)
{
    if(this->routesMap.find(id) != this->routesMap.end()){
        GIS_AirRouteItemModel *model = this->routesMap.find(id).value();
        this->beginResetModel();
        this->routesMap.remove(id);
        this->routesList.removeAt(this->routesList.indexOf(id));
        this->endResetModel();
        model->deleteLater();
        return 0;

    }else{
        return -1;
    }
}

int GIS_AirRoutesModel::getRoutesIndexForRoutesID(int id)
{
    return this->routesList.indexOf(id);
}

int GIS_AirRoutesModel::getCurrentRouteID() const
{
    return currentRouteID;
}

QHash<int, QByteArray> GIS_AirRoutesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DATA_RoutesID] = "Air_RouteID";
    roles[DATA_RouteModel] = "Air_RouteModel";
    roles[DATA_RoutePath] = "Air_RoutePath";
    return roles;
}

GIS_AirRouteItemModel *GIS_AirRoutesModel::getAirRoutesItemModelForRoutesID(int id)
{
    if(this->routesMap.find(id) != this->routesMap.end()){
        return this->routesMap.find(id).value();
    }else{
        return nullptr;
    }
}






























GIS_AirRouteItemModel::GIS_AirRouteItemModel(QObject *parent) : QAbstractItemModel(parent)
{
    this->commondList.clear();
    this->commondList.insert(MAV_CMD_NAV_NOTDEF             ,QStringLiteral("未选择").toUtf8());
    this->commondList.insert(MAV_CMD_NAV_WAYPOINT           ,QStringLiteral("飞行航点").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_LOITER_UNLIM       ,QStringLiteral("悬停(无限制)").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_LOITER_TURNS       ,QStringLiteral("悬停(旋转)").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_LOITER_TIME        ,QStringLiteral("悬停(时间)").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_RETURN_TO_LAUNCH   ,QStringLiteral("返航RTL").toUtf8());
    this->commondList.insert(MAV_CMD_NAV_LAND               ,QStringLiteral("返航LAND").toUtf8());
    this->commondList.insert(MAV_CMD_NAV_TAKEOFF            ,QStringLiteral("起飞").toUtf8());
    this->commondList.insert(MAV_CMD_NAV_LOITER_TO_ALT      ,QStringLiteral("悬停").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_SPLINE_WAYPOINT    ,QStringLiteral("航点(spline)").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_DELAY              ,QStringLiteral("延时(Delay)").toUtf8());
//    this->commondList.insert(MAV_CMD_NAV_PAYLOAD_PLACE      ,QStringLiteral("释放负载").toUtf8());
//    this->commondList.insert(MAV_CMD_CONDITION_DELAY        ,QStringLiteral("条件-延时").toUtf8());
//    this->commondList.insert(MAV_CMD_CONDITION_DISTANCE     ,QStringLiteral("条件-距离").toUtf8());
//    this->commondList.insert(MAV_CMD_CONDITION_YAW          ,QStringLiteral("条件-航向").toUtf8());
    this->commondList.insert(MAV_CMD_DO_JUMP                ,QStringLiteral("Do跳转").toUtf8());
    this->commondList.insert(MAV_CMD_DO_LAND_START          ,QStringLiteral("开始降落").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_CHANGE_SPEED        ,QStringLiteral("Do改变速度").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_SET_RELAY           ,QStringLiteral("Do设置继电器状态").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_REPEAT_RELAY        ,QStringLiteral("Do继电器Repeat").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_SET_SERVO           ,QStringLiteral("Do设置伺服输出").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_SET_ROI             ,QStringLiteral("Do兴趣点").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_DIGICAM_CONFIGURE   ,QStringLiteral("Do相机配置").toUtf8());
//    this->commondList.insert(MAV_CMD_DO_WINCH               ,QStringLiteral("放线装置操作").toUtf8());


    this->alititudeList.clear();
    this->alititudeList.insert(AirRouteItemAltitudeModel::MISSION_ALT_FRAME_GLOBAL,QStringLiteral("海拔高度").toUtf8());
    this->alititudeList.insert(AirRouteItemAltitudeModel::MISSION_ALT_FRAME_RELATIVE_ALT,QStringLiteral("相对高度").toUtf8());
    this->alititudeList.insert(AirRouteItemAltitudeModel::MISSION_ALT_FRAME_RELATIVE_TERRAIN_ALT,QStringLiteral("地形高度").toUtf8());
}

QVariant GIS_AirRouteItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        switch(role){
            case Qt::DisplayRole:{
                QHash<int,QByteArray>roles = headerNames();
                return QVariant(roles[section + Qt::UserRole + 1]);
            }case Qt::TextAlignmentRole:{
                return Qt::AlignCenter;
            }case Qt::FontRole:{
                return QFont("SimHei",11);
            }case Qt::TextColorRole:{
                return QColor(200,200,200);
            }

        }

    }
    return QVariant();
}

QModelIndex GIS_AirRouteItemModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return createIndex(row,column);
}

QModelIndex GIS_AirRouteItemModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

int GIS_AirRouteItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->routePointIDMap.count();
}

int GIS_AirRouteItemModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->itemColumnCount;
}

QVariant GIS_AirRouteItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }

    int row = index.row();
    int column = index.column();
    if(row < this->routePointIDMap.count() && row >= 0 && column < this->itemColumnCount && column >= 0){
        int key = this->routePointIDMap[row];
        if(this->routePointMap.find(key) == this->routePointMap.end()){
            return QVariant();
        }

        GIS_AirRoutePoitItem *item = this->routePointMap.find(key).value();

        switch(role){
            case (Qt::TextAlignmentRole):
                return Qt::AlignCenter;
            case (Qt::DisplayRole):{
                return (const_cast<GIS_AirRouteItemModel *>(this))->getItemDataForDisplayRole(index);
            }case (Qt::EditRole):{
                return QVariant();
            }case Qt::TextColorRole:{
                return QColor(200,200,200);
            }case DATA_PointID:{
                    return QString::number(item->getPointID());
            }case DATA_PointLat:{
                return item->getLat();
            }case DATA_PointLng:{
                return item->getLng();
            }case DATA_AlititudeType:{
                return QVariant::fromValue<QMap<int,QString>>(this->alititudeList);
            }case DATA_CMDList:{
                return QVariant::fromValue<QMap<int,QString>>(this->commondList);
            }case DATA_PointCommondID:{
                return item->getCommondID();
            }case DATA_PointAlititudeModel:{
                return item->getAlititudeModel();
            }case DATA_PointAlititude:{
                return item->getAlititude();
            }case DATA_PointParameter1:{
                return item->getParameter1();
            }case DATA_PointParameter2:{
                return item->getParameter2();
            }case DATA_PointParameter3:{
                return item->getParameter3();
            }case DATA_PointParameter4:{
                return item->getParameter4();
            }case DATA_WHATTHIS:{
                return (const_cast<GIS_AirRouteItemModel *>(this))->getItemDataWhatThis(index);
            }case DATA_RouteItemID:{
                return QVariant::fromValue(this->routePointIDMap.values());
            }
            default:
                return QVariant();
        }

    }
    return QVariant();

}

bool GIS_AirRouteItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()){
        return false;
    }
    int row = index.row();
    int column = index.column();

    if(row >= this->routePointIDMap.count() || row < 0 || column >= this->itemColumnCount || column < 0){
        return false;
    }
    int key = this->routePointIDMap[row];
    if(this->routePointMap.find(key) == this->routePointMap.end()){
        return false;
    }
    GIS_AirRoutePoitItem *item = this->routePointMap.find(key).value();
    bool retflag = false;
    emit this->beginResetModelSignal();
    this->beginResetModel();

    switch(role){
    case (Qt::EditRole):{
        switch(column + Qt::UserRole + 1){
            case DATA_PointLat:
                item->setLat(value.toDouble());
                retflag = true;
                break;
            case DATA_PointLng:
                item->setLng(value.toDouble());
                retflag = true;
                break;
            case DATA_PointAlititude:
                item->setAlititude(value.toInt());
                retflag = true;
                break;
            case DATA_PointAlititudeModel:{
                retflag = false;
                QMap<int,QString>::Iterator iter = this->alititudeList.begin();
                while(iter != this->alititudeList.end()){
                    if(value.toString().compare(iter.value()) == 0){
                        item->setAlititudeModel(iter.key());
                        retflag = true;
                        break;
                    }
                    iter ++;
                }
                break;
            }case DATA_PointCommondID:{
                retflag = false;
                QMap<int,QString>::Iterator iter = this->commondList.begin();
                while(iter != this->commondList.end()){
                    if(value.toString().compare(iter.value()) == 0){
                        item->setCommondID(iter.key());
                        retflag = true;
                        break;
                    }
                    iter ++;
                }
                break;
            }case DATA_PointParameter1:
                item->setParameter1(value);
                retflag = true;
                break;
            case DATA_PointParameter2:
                item->setParameter2(value);
                retflag = true;
                break;
            case DATA_PointParameter3:
                item->setParameter3(value);
                retflag = true;
                break;
            case DATA_PointParameter4:
                item->setParameter4(value);
                retflag = true;
                break;
            default:
                retflag = false;
                break;
        }
        break;
    }
    case DATA_PointCoor:{
        QGeoCoordinate pointCoor = value.value<QGeoCoordinate>();
        item->setLat(pointCoor.latitude());
        item->setLng(pointCoor.longitude());
        retflag = true;
        break;
    }default:
        break;

    }
    this->endResetModel();
    emit this->endResetModelSignal();
    return retflag;
}



QHash<int, QByteArray> GIS_AirRouteItemModel::roleNames() const
{
    QHash<int,QByteArray> screenRole;
    screenRole[DATA_PointID] = QString(tr("point_id")).toUtf8();
    screenRole[DATA_PointLng] = QString(tr("point_lng")).toUtf8();
    screenRole[DATA_PointLat] = QString(tr("point_lat")).toUtf8();
    screenRole[DATA_PointAlititude] = QString(tr("point_alt")).toUtf8();
    screenRole[DATA_PointAlititudeModel] = QString(tr("point_altModel")).toUtf8();
    screenRole[DATA_PointCommondID] = QString(tr("point_cmdID")).toUtf8();
    screenRole[DATA_PointParameter1] = QString(tr("point_par1")).toUtf8();
    screenRole[DATA_PointParameter2] = QString(tr("point_par2")).toUtf8();
    screenRole[DATA_PointParameter3] = QString(tr("point_par3")).toUtf8();
    screenRole[DATA_PointParameter4] = QString(tr("point_par4")).toUtf8();

    screenRole[DATA_PointCoor] = QString(tr("point_Coor")).toUtf8();

    return screenRole;
}

QHash<int, QByteArray> GIS_AirRouteItemModel::headerNames() const
{
    QHash<int,QByteArray> headerNames;
    headerNames[DATA_PointID] = QStringLiteral("编号").toUtf8();
    headerNames[DATA_PointLng] = QStringLiteral("航点经度").toUtf8();
    headerNames[DATA_PointLat] = QStringLiteral("航点纬度").toUtf8();
    headerNames[DATA_PointAlititude] = QStringLiteral("航点高度").toUtf8();
    headerNames[DATA_PointAlititudeModel] = QStringLiteral("高度模式").toUtf8();
    headerNames[DATA_PointCommondID] = QStringLiteral("航点任务").toUtf8();
    headerNames[DATA_PointParameter1] = QStringLiteral("参数1").toUtf8();
    headerNames[DATA_PointParameter2] = QStringLiteral("参数2").toUtf8();
    headerNames[DATA_PointParameter3] = QStringLiteral("参数3").toUtf8();
    headerNames[DATA_PointParameter4] = QStringLiteral("参数4").toUtf8();

    return headerNames;
}

int GIS_AirRouteItemModel::createItemPoint(double lng, double lat, int alititude, int alititudeModel, int commondID, QVariant parameter1, QVariant parameter2, QVariant parameter3, QVariant parameter4)
{
    GIS_AirRoutePoitItem *item = new GIS_AirRoutePoitItem();
    int id = this->routePointIDMap.count() + 1;
    item->setPointID(id);
    item->setLat(lat);
    item->setLng(lng);
    item->setAlititude(alititude);
    item->setAlititudeModel(alititudeModel);
    item->setCommondID(commondID);
    item->setParameter1(parameter1);
    item->setParameter2(parameter2);
    item->setParameter3(parameter3);
    item->setParameter4(parameter4);

    emit beginResetModelSignal();
    this->beginResetModel();
    this->routePointIDMap.insert(this->routePointIDMap.count(),id);
    this->routePointMap.insert(id,item);
    this->endResetModel();
    emit endResetModelSignal();
    return 0;
}

int GIS_AirRouteItemModel::insertItemPointToHead(double lng, double lat, int alititude, int alititudeModel, int commondID, QVariant parameter1, QVariant parameter2, QVariant parameter3, QVariant parameter4)
{
    QMap<int,int> pointIDMap;                             //key:  插入顺序   value: pointID
    QMap<int,GIS_AirRoutePoitItem *>pointMap;              //key:  pointID
    GIS_AirRoutePoitItem *item = new GIS_AirRoutePoitItem();
    int id = pointIDMap.count() + 1;

    item->setPointID(id);
    item->setLat(lat);
    item->setLng(lng);
    item->setAlititude(alititude);
    item->setAlititudeModel(alititudeModel);
    item->setCommondID(commondID);
    item->setParameter1(parameter1);
    item->setParameter2(parameter2);
    item->setParameter3(parameter3);
    item->setParameter4(parameter4);

    pointIDMap.insert(pointIDMap.count(),id);
    pointMap.insert(id,item);


    QMap<int,int>::Iterator hashIter = this->routePointIDMap.begin();
    while(hashIter != this->routePointIDMap.end()){
        if(this->routePointMap.find(hashIter.value()) != this->routePointMap.end()){
            pointIDMap.insert(pointIDMap.count(),hashIter.value() + 1);
            GIS_AirRoutePoitItem *pointItem = this->routePointMap.find(hashIter.value()).value();
            pointItem->setPointID(hashIter.value() + 1);
            pointMap.insert(hashIter.value() + 1,pointItem);
        }
        hashIter ++;
    }
    emit beginResetModelSignal();
    this->beginResetModel();
    this->routePointIDMap.clear();
    this->routePointIDMap.insert(pointIDMap);
    this->routePointMap.clear();
    this->routePointMap.insert(pointMap);
    this->endResetModel();
    emit endResetModelSignal();

    return 0;
}

int GIS_AirRouteItemModel::insertItemPointBelowIndex(int index, double lng, double lat, int alititude, int alititudeModel, int commondID, QVariant parameter1, QVariant parameter2, QVariant parameter3, QVariant parameter4)
{
    if(index > this->routePointIDMap.count() || index < 0){
        return -1;
    }
    QMap<int,int> pointIDMap;                             //key:  插入顺序   value: pointID
    QMap<int,GIS_AirRoutePoitItem *>pointMap;              //key:  pointID
    GIS_AirRoutePoitItem *item = new GIS_AirRoutePoitItem();

    QMap<int,int>::Iterator hashIter = this->routePointIDMap.begin();

    for(int i = 0; i <= index; i++){
        if(this->routePointMap.find(hashIter.value()) != this->routePointMap.end()){
            pointIDMap.insert(hashIter.key(),hashIter.value());
            pointMap.insert(hashIter.value(),this->routePointMap.find(hashIter.value()).value());
        }
        hashIter ++;
    }

    int id = pointIDMap.count() + 1;

    item->setPointID(id);
    item->setLat(lat);
    item->setLng(lng);
    item->setAlititude(alititude);
    item->setAlititudeModel(alititudeModel);
    item->setCommondID(commondID);
    item->setParameter1(parameter1);
    item->setParameter2(parameter2);
    item->setParameter3(parameter3);
    item->setParameter4(parameter4);

    pointIDMap.insert(pointIDMap.count(),id);
    pointMap.insert(id,item);

    for(int i = index + 1; i < this->routePointIDMap.count(); i++){
        pointIDMap.insert(pointIDMap.count(),hashIter.value() + 1);
        GIS_AirRoutePoitItem *pointItem = this->routePointMap.find(hashIter.value()).value();
        pointItem->setPointID(hashIter.value() + 1);
        pointMap.insert(hashIter.value() + 1,pointItem);
        hashIter ++;
    }
    emit beginResetModelSignal();
    this->beginResetModel();
    this->routePointIDMap.clear();
    this->routePointIDMap.insert(pointIDMap);
    this->routePointMap.clear();
    this->routePointMap.insert(pointMap);
    this->endResetModel();
    emit endResetModelSignal();

    return 0;
}

int GIS_AirRouteItemModel::insertItemPointAboveIndex(int index, double lng, double lat, int alititude, int alititudeModel, int commondID, QVariant parameter1, QVariant parameter2, QVariant parameter3, QVariant parameter4)
{
    if(index > this->routePointIDMap.count() || index < 0){
        return -1;
    }
    QMap<int,int> pointIDMap;                             //key:  插入顺序   value: pointID
    QMap<int,GIS_AirRoutePoitItem *>pointMap;              //key:  pointID
    GIS_AirRoutePoitItem *item = new GIS_AirRoutePoitItem();

    QMap<int,int>::Iterator hashIter = this->routePointIDMap.begin();

    for(int i = 0; i < index; i++){
        if(this->routePointMap.find(hashIter.value()) != this->routePointMap.end()){
            pointIDMap.insert(hashIter.key(),hashIter.value());
            pointMap.insert(hashIter.value(),this->routePointMap.find(hashIter.value()).value());
        }
        hashIter ++;
    }

    int id = pointIDMap.count() + 1;

    item->setPointID(id);
    item->setLat(lat);
    item->setLng(lng);
    item->setAlititude(alititude);
    item->setAlititudeModel(alititudeModel);
    item->setCommondID(commondID);
    item->setParameter1(parameter1);
    item->setParameter2(parameter2);
    item->setParameter3(parameter3);
    item->setParameter4(parameter4);

    pointIDMap.insert(pointIDMap.count(),id);
    pointMap.insert(id,item);

    for(int i = index; i < this->routePointIDMap.count(); i++){
        pointIDMap.insert(pointIDMap.count(),hashIter.value() + 1);
        GIS_AirRoutePoitItem *pointItem = this->routePointMap.find(hashIter.value()).value();
        pointItem->setPointID(hashIter.value() + 1);
        pointMap.insert(hashIter.value() + 1,pointItem);
        hashIter ++;
    }
    emit beginResetModelSignal();
    this->beginResetModel();
    this->routePointIDMap.clear();
    this->routePointIDMap.insert(pointIDMap);
    this->routePointMap.clear();
    this->routePointMap.insert(pointMap);
    this->endResetModel();
    emit endResetModelSignal();
    return 0;
}

int GIS_AirRouteItemModel::removePointForIndex(int index)
{
    if(this->routePointIDMap.find(index) == this->routePointIDMap.end()){
        return -1;
    }
    int pointID = this->routePointIDMap.find(index).value();

    if(this->routePointMap.find(pointID) == this->routePointMap.end()){
        return -1;
    }

    GIS_AirRoutePoitItem *poitItem = this->routePointMap.find(pointID).value();

    QMap<int,int>pointIDMap;
    QMap<int,GIS_AirRoutePoitItem *>pointMap;

    QMap<int,int>::Iterator hashIter = this->routePointIDMap.begin();

    for(int i = 0; i < this->routePointIDMap.count(); i++){
        if(i < index){
            pointIDMap.insert(hashIter.key(),hashIter.value());
            pointMap.insert(hashIter.value(),this->routePointMap.find(hashIter.value()).value());
        }else if(i > index){
            pointIDMap.insert(hashIter.key() - 1,hashIter.value() - 1);
            pointMap.insert(hashIter.value() - 1,this->routePointMap.find(hashIter.value()).value());
            pointMap[hashIter.value() - 1]->setPointID(hashIter.value() - 1);
        }
        hashIter ++;
    }

    emit beginResetModelSignal();
    this->beginResetModel();
    this->routePointIDMap.clear();
    this->routePointIDMap.insert(pointIDMap);
    this->routePointMap.clear();
    this->routePointMap.insert(pointMap);
    this->endResetModel();
    delete poitItem;
    emit endResetModelSignal();
    return 0;

    return 0;
}

int GIS_AirRouteItemModel::removeAllPoint()
{
    emit beginResetModelSignal();
    this->beginResetModel();
    this->routePointIDMap.clear();
    this->routePointMap.clear();
    this->endResetModel();
    emit endResetModelSignal();
    return 0;
}

int GIS_AirRouteItemModel::pointIndexMoveUp(int index)
{
    if(index > this->routePointIDMap.count() || index < 0){
        return -1;
    }
    QMap<int,int>::Iterator hashIter = this->routePointIDMap.begin();
    QMap<int,int>::Iterator lastHashIter = this->routePointIDMap.begin();   //上一个节点

    for(int i = 0; i < index; i++){
        lastHashIter = hashIter;
        hashIter ++;
    }

    if(hashIter != this->routePointIDMap.begin()){
        if(this->routePointMap.find(hashIter.value()) != this->routePointMap.end() && this->routePointMap.find(lastHashIter.value()) != this->routePointMap.end()){
            int id = this->routePointMap.find(hashIter.value()).value()->getPointID();
            GIS_AirRoutePoitItem *lastPointItem = this->routePointMap.find(lastHashIter.value()).value();
            GIS_AirRoutePoitItem *pointItem = this->routePointMap.find(hashIter.value()).value();
            pointItem->setPointID(lastPointItem->getPointID());
            lastPointItem->setPointID(id);
            emit beginResetModelSignal();
            this->beginResetModel();
            this->routePointMap[lastHashIter.value()] = pointItem;
            this->routePointMap[hashIter.value()] = lastPointItem;
            this->endResetModel();
            emit endResetModelSignal();
        }
    }
    return 0;
}

int GIS_AirRouteItemModel::pointIndexMoveDown(int index)
{
    if(index > this->routePointIDMap.count() || index < 0){
        return -1;
    }
    QMap<int,int>::Iterator hashIter = this->routePointIDMap.begin();
    QMap<int,int>::Iterator nextHashIter = this->routePointIDMap.begin();   //上一个节点

    for(int i = 0; i <= index; i++){
        hashIter = nextHashIter;
        nextHashIter ++;
    }

    if(nextHashIter != this->routePointIDMap.end()){
        if(this->routePointMap.find(hashIter.value()) != this->routePointMap.end() && this->routePointMap.find(nextHashIter.value()) != this->routePointMap.end()){
            int id = this->routePointMap.find(hashIter.value()).value()->getPointID();
            GIS_AirRoutePoitItem *lastPointItem = this->routePointMap.find(nextHashIter.value()).value();
            GIS_AirRoutePoitItem *pointItem = this->routePointMap.find(hashIter.value()).value();
            pointItem->setPointID(lastPointItem->getPointID());
            lastPointItem->setPointID(id);
            emit beginResetModelSignal();
            this->beginResetModel();
            this->routePointMap[nextHashIter.value()] = pointItem;
            this->routePointMap[hashIter.value()] = lastPointItem;
            this->endResetModel();
            emit endResetModelSignal();
        }
    }
    return 0;
}


Qt::ItemFlags GIS_AirRouteItemModel::flags(const QModelIndex &index) const
{

    if (!index.isValid())
        return QAbstractItemModel::flags(index);


    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    int row = index.row();
    int column = index.column();
    if(row < this->routePointIDMap.count() && row >= 0 && column < this->itemColumnCount && column >= 0){
        int key = this->routePointIDMap[row];
        if(this->routePointMap.find(key) == this->routePointMap.end()){
            return flags;
        }
        GIS_AirRoutePoitItem *item = this->routePointMap.find(key).value();


    switch(column + Qt::UserRole + 1){
    case DATA_PointLng:{
        switch(item->getCommondID()){
        case MAV_CMD_NAV_NOTDEF:
        case MAV_CMD_NAV_WAYPOINT:
        case MAV_CMD_NAV_LOITER_UNLIM:
        case MAV_CMD_NAV_LOITER_TURNS:
        case MAV_CMD_NAV_LOITER_TIME:
        case MAV_CMD_NAV_LAND:
        case MAV_CMD_NAV_TAKEOFF:
        case MAV_CMD_NAV_LOITER_TO_ALT:
        case MAV_CMD_NAV_SPLINE_WAYPOINT:
        case MAV_CMD_NAV_PAYLOAD_PLACE:
        case MAV_CMD_DO_SET_ROI:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    }case DATA_PointLat:{
        switch(item->getCommondID()){
        case MAV_CMD_NAV_NOTDEF:
        case MAV_CMD_NAV_WAYPOINT:
        case MAV_CMD_NAV_LOITER_UNLIM:
        case MAV_CMD_NAV_LOITER_TURNS:
        case MAV_CMD_NAV_LOITER_TIME:
        case MAV_CMD_NAV_LAND:
        case MAV_CMD_NAV_TAKEOFF:
        case MAV_CMD_NAV_LOITER_TO_ALT:
        case MAV_CMD_NAV_SPLINE_WAYPOINT:
        case MAV_CMD_NAV_PAYLOAD_PLACE:
        case MAV_CMD_DO_SET_ROI:
            flags |= Qt::ItemIsEditable;
            break;
        default:

            break;
        }
        break;
    }case DATA_PointAlititude:
        switch(item->getCommondID()){
        case MAV_CMD_NAV_NOTDEF:
        case MAV_CMD_NAV_WAYPOINT:
        case MAV_CMD_NAV_LOITER_UNLIM:
        case MAV_CMD_NAV_LOITER_TURNS:
        case MAV_CMD_NAV_LOITER_TIME:
        case MAV_CMD_NAV_LAND:
        case MAV_CMD_NAV_TAKEOFF:
        case MAV_CMD_NAV_LOITER_TO_ALT:
        case MAV_CMD_NAV_SPLINE_WAYPOINT:
        case MAV_CMD_NAV_PAYLOAD_PLACE:
        case MAV_CMD_DO_SET_ROI:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    case DATA_PointAlititudeModel:
        switch(item->getCommondID()){
        case MAV_CMD_NAV_NOTDEF:
        case MAV_CMD_NAV_WAYPOINT:
        case MAV_CMD_NAV_LOITER_UNLIM:
        case MAV_CMD_NAV_LOITER_TURNS:
        case MAV_CMD_NAV_LOITER_TIME:
        case MAV_CMD_NAV_LAND:
        case MAV_CMD_NAV_TAKEOFF:
        case MAV_CMD_NAV_LOITER_TO_ALT:
        case MAV_CMD_NAV_SPLINE_WAYPOINT:
        case MAV_CMD_NAV_PAYLOAD_PLACE:
        case MAV_CMD_DO_SET_ROI:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    case DATA_PointCommondID:
        flags |= Qt::ItemIsEditable;
        break;
    case DATA_PointParameter1:
        switch(item->getCommondID()){
        case MAV_CMD_NAV_WAYPOINT:
        case MAV_CMD_NAV_LOITER_TURNS:
        case MAV_CMD_NAV_LOITER_TIME:
        case MAV_CMD_NAV_SPLINE_WAYPOINT:
        case MAV_CMD_NAV_DELAY:
        case MAV_CMD_NAV_PAYLOAD_PLACE:
        case MAV_CMD_CONDITION_DELAY:
        case MAV_CMD_CONDITION_DISTANCE:
        case MAV_CMD_CONDITION_YAW:
        case MAV_CMD_DO_JUMP:
        case MAV_CMD_DO_CHANGE_SPEED:
        case MAV_CMD_DO_SET_RELAY:
        case MAV_CMD_DO_REPEAT_RELAY:
        case MAV_CMD_DO_SET_SERVO:
        case MAV_CMD_DO_WINCH:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    case DATA_PointParameter2:
        switch(item->getCommondID()){
        case MAV_CMD_NAV_DELAY:
        case MAV_CMD_DO_JUMP:
        case MAV_CMD_DO_CHANGE_SPEED:
        case MAV_CMD_DO_SET_RELAY:
        case MAV_CMD_DO_REPEAT_RELAY:
        case MAV_CMD_DO_SET_SERVO:
        case MAV_CMD_DO_WINCH:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    case DATA_PointParameter3:
        switch(item->getCommondID()){
        case MAV_CMD_NAV_LOITER_TURNS:
        case MAV_CMD_NAV_DELAY:
        case MAV_CMD_CONDITION_YAW:
        case MAV_CMD_DO_REPEAT_RELAY:
        case MAV_CMD_DO_WINCH:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    case DATA_PointParameter4:
        switch(item->getCommondID()){
        case MAV_CMD_NAV_DELAY:
        case MAV_CMD_CONDITION_YAW:
        case MAV_CMD_DO_WINCH:
            flags |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    }
    return flags;
}

QList<QGeoCoordinate> GIS_AirRouteItemModel::getRoutePath()
{
    QList<QGeoCoordinate> path;
    for(int i = 0; i < routePointIDMap.count(); i++){
        int key = this->routePointIDMap.find(i).value();
        if(this->routePointMap.find(key) == this->routePointMap.end()){
            continue;
        }

        GIS_AirRoutePoitItem *item = this->routePointMap.find(key).value();
        int cmdID = item->getCommondID();
        if(cmdID == MAV_CMD::MAV_CMD_NAV_WAYPOINT || cmdID == MAV_CMD::MAV_CMD_NAV_LOITER_UNLIM || cmdID == MAV_CMD::MAV_CMD_NAV_LOITER_TURNS || cmdID == MAV_CMD::MAV_CMD_NAV_LOITER_TIME ||\
            cmdID == MAV_CMD::MAV_CMD_NAV_LAND || cmdID == MAV_CMD::MAV_CMD_NAV_TAKEOFF || cmdID == MAV_CMD::MAV_CMD_NAV_LOITER_TO_ALT || cmdID == MAV_CMD::MAV_CMD_NAV_SPLINE_WAYPOINT ||\
            cmdID == MAV_CMD::MAV_CMD_NAV_PAYLOAD_PLACE || cmdID == MAV_CMD::MAV_CMD_DO_SET_ROI){

            QGeoCoordinate coor(item->getLat(),item->getLng());
            path.append(coor);
        }else{
            continue;
        }

    }


    return path;
}

QVariant GIS_AirRouteItemModel::getItemDataForDisplayRole(const QModelIndex &index)
{
    int row = index.row();
    int column = index.column();
    if(row < this->routePointIDMap.count() && row >= 0 && column < this->itemColumnCount && column >= 0){
        int key = this->routePointIDMap[row];
        if(this->routePointMap.find(key) == this->routePointMap.end()){
            return QVariant();
        }

        GIS_AirRoutePoitItem *item = this->routePointMap.find(key).value();

        switch(column + Qt::UserRole + 1){
            case DATA_PointID:
                return item->getPointID();
            case DATA_PointLat:{
                switch(item->getCommondID()){
                case MAV_CMD_NAV_NOTDEF:
                case MAV_CMD_NAV_WAYPOINT:
                case MAV_CMD_NAV_LOITER_UNLIM:
                case MAV_CMD_NAV_LOITER_TURNS:
                case MAV_CMD_NAV_LOITER_TIME:
                case MAV_CMD_NAV_LAND:
                case MAV_CMD_NAV_TAKEOFF:
                case MAV_CMD_NAV_LOITER_TO_ALT:
                case MAV_CMD_NAV_SPLINE_WAYPOINT:
                case MAV_CMD_NAV_PAYLOAD_PLACE:
                case MAV_CMD_DO_SET_ROI:
                    return item->getLat();
                default:
                    return "/";
                }

            }case DATA_PointLng:{
                switch(item->getCommondID()){
                case MAV_CMD_NAV_NOTDEF:
                case MAV_CMD_NAV_WAYPOINT:
                case MAV_CMD_NAV_LOITER_UNLIM:
                case MAV_CMD_NAV_LOITER_TURNS:
                case MAV_CMD_NAV_LOITER_TIME:
                case MAV_CMD_NAV_LAND:
                case MAV_CMD_NAV_TAKEOFF:
                case MAV_CMD_NAV_LOITER_TO_ALT:
                case MAV_CMD_NAV_SPLINE_WAYPOINT:
                case MAV_CMD_NAV_PAYLOAD_PLACE:
                case MAV_CMD_DO_SET_ROI:
                    return item->getLng();
                default:
                    return "/";
                }
            }case DATA_PointAlititude:{
                switch(item->getCommondID()){
                case MAV_CMD_NAV_NOTDEF:
                case MAV_CMD_NAV_WAYPOINT:
                case MAV_CMD_NAV_LOITER_UNLIM:
                case MAV_CMD_NAV_LOITER_TURNS:
                case MAV_CMD_NAV_LOITER_TIME:
                case MAV_CMD_NAV_LAND:
                case MAV_CMD_NAV_TAKEOFF:
                case MAV_CMD_NAV_LOITER_TO_ALT:
                case MAV_CMD_NAV_SPLINE_WAYPOINT:
                case MAV_CMD_NAV_PAYLOAD_PLACE:
                case MAV_CMD_DO_SET_ROI:
                    return item->getAlititude();
                default:
                    return "/";
                }
            }case DATA_PointAlititudeModel:
                switch(item->getCommondID()){
                case MAV_CMD_NAV_NOTDEF:
                case MAV_CMD_NAV_WAYPOINT:
                case MAV_CMD_NAV_LOITER_UNLIM:
                case MAV_CMD_NAV_LOITER_TURNS:
                case MAV_CMD_NAV_LOITER_TIME:
                case MAV_CMD_NAV_LAND:
                case MAV_CMD_NAV_TAKEOFF:
                case MAV_CMD_NAV_LOITER_TO_ALT:
                case MAV_CMD_NAV_SPLINE_WAYPOINT:
                case MAV_CMD_NAV_PAYLOAD_PLACE:
                case MAV_CMD_DO_SET_ROI:
                    if(this->alititudeList.find(item->getAlititudeModel()) != this->alititudeList.end()){
                        return this->alititudeList.find(item->getAlititudeModel()).value();
                    }
                    return "未选择";
                default:
                    return "/";
                }

            case DATA_PointCommondID:
                if(this->commondList.find(item->getCommondID()) != this->commondList.end()){
                    return this->commondList.find(item->getCommondID()).value();
                }
                return "未选择";
            case DATA_PointParameter1:
                switch(item->getCommondID()){
                case MAV_CMD_NAV_WAYPOINT:
                case MAV_CMD_NAV_LOITER_TURNS:
                case MAV_CMD_NAV_LOITER_TIME:
                case MAV_CMD_NAV_SPLINE_WAYPOINT:
                case MAV_CMD_NAV_DELAY:
                case MAV_CMD_NAV_PAYLOAD_PLACE:
                case MAV_CMD_CONDITION_DELAY:
                case MAV_CMD_CONDITION_DISTANCE:
                case MAV_CMD_CONDITION_YAW:
                case MAV_CMD_DO_SET_RELAY:
                case MAV_CMD_DO_REPEAT_RELAY:
                case MAV_CMD_DO_SET_SERVO:
                case MAV_CMD_DO_WINCH:
                    return QString::number(item->getParameter1().toInt());
                case MAV_CMD_DO_JUMP:
                    if(this->routePointMap.find(item->getParameter1().toInt()) != this->routePointMap.end()){
//                        return this->commondList.find(item->getParameter1().toInt()).value();
                        return QString::number(item->getParameter1().toInt());
                    }
                    return QVariant();
                case MAV_CMD_DO_CHANGE_SPEED:
                    switch(item->getParameter1().toInt()){
                        case 0:
                        return "Airspeed";
                    case 1:
                    return "Ground Speed";
                    case 2:
                    return "Climb Speed";
                    case 3:
                    return "Descent Speed";
                    default:
                        return "failed";
                    }
                    return item->getParameter1().toInt();
                default:
                    return "/";
            }
            case DATA_PointParameter2:
                switch(item->getCommondID()){
                case MAV_CMD_NAV_DELAY:
                case MAV_CMD_DO_JUMP:
                case MAV_CMD_DO_CHANGE_SPEED:
                case MAV_CMD_DO_SET_RELAY:
                case MAV_CMD_DO_REPEAT_RELAY:
                case MAV_CMD_DO_SET_SERVO:
                case MAV_CMD_DO_WINCH:
                    return QString::number(item->getParameter2().toInt());
                default:
                    return "/";
            }
            case DATA_PointParameter3:
                switch(item->getCommondID()){
                case MAV_CMD_NAV_LOITER_TURNS:
                case MAV_CMD_NAV_DELAY:
                case MAV_CMD_CONDITION_YAW:
                case MAV_CMD_DO_REPEAT_RELAY:
                case MAV_CMD_DO_WINCH:
                    return QString::number(item->getParameter3().toInt());
                default:
                    return "/";
                }
            case DATA_PointParameter4:
                switch(item->getCommondID()){
                case MAV_CMD_NAV_DELAY:
                case MAV_CMD_CONDITION_YAW:
                case MAV_CMD_DO_WINCH:
                    return QString::number(item->getParameter4().toInt());
                default:
                    return "/";
                }
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QVariant GIS_AirRouteItemModel::getItemDataWhatThis(const QModelIndex &index)
{
    int row = index.row();
    int column = index.column();
    if(row < this->routePointIDMap.count() && row >= 0 && column < this->itemColumnCount && column >= 0){
        int key = this->routePointIDMap[row];
        if(this->routePointMap.find(key) == this->routePointMap.end()){
            return QVariant();
        }

        GIS_AirRoutePoitItem *item = this->routePointMap.find(key).value();

        switch(column + Qt::UserRole + 1){
        case DATA_PointID:
            return QStringLiteral("航点编号").toUtf8();
        case DATA_PointLat:{
            switch(item->getCommondID()){
            case MAV_CMD_NAV_NOTDEF:
            case MAV_CMD_NAV_WAYPOINT:
            case MAV_CMD_NAV_LOITER_UNLIM:
            case MAV_CMD_NAV_LOITER_TURNS:
            case MAV_CMD_NAV_LOITER_TIME:
            case MAV_CMD_NAV_LAND:
            case MAV_CMD_NAV_TAKEOFF:
            case MAV_CMD_NAV_LOITER_TO_ALT:
            case MAV_CMD_NAV_SPLINE_WAYPOINT:
            case MAV_CMD_NAV_PAYLOAD_PLACE:
            case MAV_CMD_DO_SET_ROI:
                return QStringLiteral("经度").toUtf8();
            default:
                return QStringLiteral("无效参数").toUtf8();
            }

        }case DATA_PointLng:{
            switch(item->getCommondID()){
            case MAV_CMD_NAV_NOTDEF:
            case MAV_CMD_NAV_WAYPOINT:
            case MAV_CMD_NAV_LOITER_UNLIM:
            case MAV_CMD_NAV_LOITER_TURNS:
            case MAV_CMD_NAV_LOITER_TIME:
            case MAV_CMD_NAV_LAND:
            case MAV_CMD_NAV_TAKEOFF:
            case MAV_CMD_NAV_LOITER_TO_ALT:
            case MAV_CMD_NAV_SPLINE_WAYPOINT:
            case MAV_CMD_NAV_PAYLOAD_PLACE:
            case MAV_CMD_DO_SET_ROI:
                return QStringLiteral("纬度").toUtf8();
            default:
                return QStringLiteral("无效参数").toUtf8();
            }
        }case DATA_PointAlititude:{
            switch(item->getCommondID()){
            case MAV_CMD_NAV_NOTDEF:
            case MAV_CMD_NAV_WAYPOINT:
            case MAV_CMD_NAV_LOITER_UNLIM:
            case MAV_CMD_NAV_LOITER_TURNS:
            case MAV_CMD_NAV_LOITER_TIME:
            case MAV_CMD_NAV_LAND:
            case MAV_CMD_NAV_LOITER_TO_ALT:
            case MAV_CMD_NAV_SPLINE_WAYPOINT:
            case MAV_CMD_NAV_PAYLOAD_PLACE:
            case MAV_CMD_DO_SET_ROI:
                return QStringLiteral("高度").toUtf8();
            default:
                return QStringLiteral("无效参数").toUtf8();
            }
        }case DATA_PointAlititudeModel:
            switch(item->getCommondID()){
            case MAV_CMD_NAV_NOTDEF:
            case MAV_CMD_NAV_WAYPOINT:
            case MAV_CMD_NAV_LOITER_UNLIM:
            case MAV_CMD_NAV_LOITER_TURNS:
            case MAV_CMD_NAV_LOITER_TIME:
            case MAV_CMD_NAV_LAND:
            case MAV_CMD_NAV_LOITER_TO_ALT:
            case MAV_CMD_NAV_SPLINE_WAYPOINT:
            case MAV_CMD_NAV_PAYLOAD_PLACE:
            case MAV_CMD_DO_SET_ROI:
                return QStringLiteral("高度类型").toUtf8();
            default:
                return QStringLiteral("无效参数").toUtf8();
            }
        case DATA_PointCommondID:
            return QStringLiteral("指令类型").toUtf8();
        case DATA_PointParameter1:
            switch(item->getCommondID()){
            case MAV_CMD_NAV_WAYPOINT:
                return QStringLiteral("/").toUtf8();
            case MAV_CMD_NAV_LOITER_TURNS:
                return QStringLiteral("转圈圈数").toUtf8();
            case MAV_CMD_NAV_LOITER_TIME:
                return QStringLiteral("悬停时间(S)").toUtf8();
            case MAV_CMD_NAV_SPLINE_WAYPOINT:
                return QStringLiteral("保持时间(S)").toUtf8();
            case MAV_CMD_NAV_DELAY:
                return QStringLiteral("延时时间(S)").toUtf8();
            case MAV_CMD_NAV_PAYLOAD_PLACE:
                return QStringLiteral("最大下降高度(M)").toUtf8();
            case MAV_CMD_CONDITION_DELAY:
                return QStringLiteral("延时时间(S)").toUtf8();
            case MAV_CMD_CONDITION_DISTANCE:
                return QStringLiteral("距离下一航点距离(M)").toUtf8();
            case MAV_CMD_CONDITION_YAW:
                return QStringLiteral("目标角度(°)").toUtf8();
            case MAV_CMD_DO_JUMP:
                return QStringLiteral("mavcommand序号").toUtf8();
            case MAV_CMD_DO_CHANGE_SPEED:
                return QStringLiteral("速度类型").toUtf8();
            case MAV_CMD_DO_SET_RELAY:
                return QStringLiteral("继电器序号").toUtf8();
            case MAV_CMD_DO_REPEAT_RELAY:
                return QStringLiteral("继电器序号").toUtf8();
            case MAV_CMD_DO_SET_SERVO:
                return QStringLiteral("伺服序号").toUtf8();
            case MAV_CMD_DO_WINCH:
                return QStringLiteral("放线装置序号").toUtf8();
            default:
                return QStringLiteral("未使用").toUtf8();
            }
        case DATA_PointParameter2:
            switch(item->getCommondID()){
            case MAV_CMD_NAV_DELAY:
                return QStringLiteral("小时(0~23)").toUtf8();
            case MAV_CMD_DO_JUMP:
                return QStringLiteral("跳转次数").toUtf8();
            case MAV_CMD_DO_CHANGE_SPEED:
                return QStringLiteral("速度(m/s)").toUtf8();
            case MAV_CMD_DO_SET_RELAY:
                return QStringLiteral("开关状态(1:on/0:off)").toUtf8();
            case MAV_CMD_DO_REPEAT_RELAY:
                return QStringLiteral("循环次数").toUtf8();
            case MAV_CMD_DO_SET_SERVO:
                return QStringLiteral("脉宽值(us)").toUtf8();
            case MAV_CMD_DO_WINCH:
                return QStringLiteral("WINCH_ACTIONS指定动作").toUtf8();
            default:
                return QStringLiteral("未使用").toUtf8();
            }
        case DATA_PointParameter3:
            switch(item->getCommondID()){
            case MAV_CMD_NAV_LOITER_TURNS:
                return QStringLiteral("悬停半径(M)").toUtf8();
            case MAV_CMD_NAV_DELAY:
                return QStringLiteral("分钟(0~59)").toUtf8();
            case MAV_CMD_CONDITION_YAW:
                return QStringLiteral("方向").toUtf8();
            case MAV_CMD_DO_REPEAT_RELAY:
                return QStringLiteral("循环时间(s)").toUtf8();
            case MAV_CMD_DO_WINCH:
                return QStringLiteral("放线长度(m)").toUtf8();
            default:
                return QStringLiteral("未使用").toUtf8();
            }
        case DATA_PointParameter4:
            switch(item->getCommondID()){
            case MAV_CMD_NAV_DELAY:
                return QStringLiteral("秒(0~59)").toUtf8();
            case MAV_CMD_CONDITION_YAW:
                return QStringLiteral("模式").toUtf8();
            case MAV_CMD_DO_WINCH:
                return QStringLiteral("放线速度(m/s)").toUtf8();
            default:
                return QStringLiteral("未使用").toUtf8();
            }
        default:
            return QVariant();
        }
    }

    return QVariant();
}





















GIS_AirRoutePoitItem::GIS_AirRoutePoitItem()
{

}

int GIS_AirRoutePoitItem::getPointID() const
{
    return pointID;
}

void GIS_AirRoutePoitItem::setPointID(int newPointID)
{
    pointID = newPointID;
}

double GIS_AirRoutePoitItem::getLng() const
{
    return lng;
}

void GIS_AirRoutePoitItem::setLng(double newLng)
{
    lng = newLng;
}

double GIS_AirRoutePoitItem::getLat() const
{
    return lat;
}

void GIS_AirRoutePoitItem::setLat(double newLat)
{
    lat = newLat;
}

int GIS_AirRoutePoitItem::getAlititude() const
{
    return alititude;
}

void GIS_AirRoutePoitItem::setAlititude(int newAlititude)
{
    alititude = newAlititude;
}

int GIS_AirRoutePoitItem::getAlititudeModel() const
{
    return alititudeModel;
}

void GIS_AirRoutePoitItem::setAlititudeModel(int newAlititudeModel)
{
    alititudeModel = newAlititudeModel;
}

int GIS_AirRoutePoitItem::getCommondID() const
{
    return commondID;
}

void GIS_AirRoutePoitItem::setCommondID(int newCommondID)
{
    commondID = newCommondID;
}

const QVariant &GIS_AirRoutePoitItem::getParameter1() const
{
    return parameter1;
}

void GIS_AirRoutePoitItem::setParameter1(const QVariant &newParameter1)
{
    parameter1 = newParameter1;
}

const QVariant &GIS_AirRoutePoitItem::getParameter2() const
{
    return parameter2;
}

void GIS_AirRoutePoitItem::setParameter2(const QVariant &newParameter2)
{
    parameter2 = newParameter2;
}

const QVariant &GIS_AirRoutePoitItem::getParameter3() const
{
    return parameter3;
}

void GIS_AirRoutePoitItem::setParameter3(const QVariant &newParameter3)
{
    parameter3 = newParameter3;
}

const QVariant &GIS_AirRoutePoitItem::getParameter4() const
{
    return parameter4;
}

void GIS_AirRoutePoitItem::setParameter4(const QVariant &newParameter4)
{
    parameter4 = newParameter4;
}










GIS_AirRoutesPointCMDDelegate::GIS_AirRoutesPointCMDDelegate(QObject *parent) : QItemDelegate(parent)
{

}


QWidget *GIS_AirRoutesPointCMDDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    QComboBox *editor = new QComboBox(parent);
    editor->setObjectName("DelegateComboBox");
    editor->setView(new QListView());
    editor->setFrame(true);
    QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();

    editor->setToolTip(whatThisText);
//    setItemEditorFactory(editor->itemDelegate().);
    QMap<int,QString> cmdList = index.model()->data(index,GIS_AirRouteItemModel::DATA_CMDList).value<QMap<int,QString>>();
    QMap<int,QString>::Iterator iter = cmdList.begin();
    while(iter != cmdList.end()){
        editor->addItem(iter.value());
        iter++;
    }
    editor->setCurrentText(index.model()->data(index,Qt::DisplayRole).toString());
    return editor;
}

void GIS_AirRoutesPointCMDDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QComboBox* box = static_cast<QComboBox*>(editor);
    box->setCurrentText(value);
}

void GIS_AirRoutesPointCMDDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void GIS_AirRoutesPointCMDDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

//void GIS_AirRoutesPointCMDDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QStyleOptionComboBox* comboBoxOption = nullptr;
//    if(this->comboBoxMap.find(index.row()) != this->comboBoxMap.end()){
//        comboBoxOption = const_cast<GIS_AirRoutesPointCMDDelegate *>(this)->comboBoxMap.find(index.row()).value();
//    }else{
//        comboBoxOption = new QStyleOptionComboBox();
//        const_cast<GIS_AirRoutesPointCMDDelegate *>(this)->comboBoxMap.insert(index.row(),comboBoxOption);
//    }

//    if(comboBoxOption == nullptr)
//        return;

//    int top = option.rect.top();
//    int left = option.rect.left();
//    int width = option.rect.width() ;
//    int height = option.rect.height();
//    comboBoxOption->currentText = index.model()->data(index,Qt::DisplayRole).toString();
//    comboBoxOption->rect.setRect(left,top,width,height);
//    comboBoxOption->editable = false;
//    comboBoxOption->state = QStyle::State_Enabled;

//    QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, comboBoxOption, painter);
////    QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, comboBoxOption, painter);

//}





GIS_AirRoutesPointAlititudeTypeDelegate::GIS_AirRoutesPointAlititudeTypeDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *GIS_AirRoutesPointAlititudeTypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    QComboBox *editor = new QComboBox(parent);
    editor->setObjectName("DelegateComboBox");
    editor->setView(new QListView());
    editor->setFrame(true);

    QMap<int,QString> cmdList = index.model()->data(index,GIS_AirRouteItemModel::DATA_AlititudeType).value<QMap<int,QString>>();
    QMap<int,QString>::Iterator iter = cmdList.begin();
    while(iter != cmdList.end()){
        editor->addItem(iter.value());
        iter++;
    }
    editor->setCurrentText(index.model()->data(index,Qt::DisplayRole).toString());
    return editor;
}

void GIS_AirRoutesPointAlititudeTypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QComboBox* box = static_cast<QComboBox*>(editor);
    box->setCurrentText(value);
}

void GIS_AirRoutesPointAlititudeTypeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void GIS_AirRoutesPointAlititudeTypeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}






GIS_AirRoutesPointCoordinatesDelegate::GIS_AirRoutesPointCoordinatesDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *GIS_AirRoutesPointCoordinatesDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    QLineEdit *editor = new QLineEdit(parent);
    editor->setObjectName("DelegateLineEdit");

//    QDoubleValidator *pDfValidator = new QDoubleValidator(15, 36, 7, parent);
//    pDfValidator->setNotation(QDoubleValidator::StandardNotation);
//    editor->setValidator(pDfValidator);
    editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
    return editor;
}

void GIS_AirRoutesPointCoordinatesDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    edit->setText(value);
}

void GIS_AirRoutesPointCoordinatesDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    QString str = edit->text();
    model->setData(index, str, Qt::EditRole);
}

void GIS_AirRoutesPointCoordinatesDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    editor->setGeometry(option.rect.x(),option.rect.y(),option.rect.width() * 2,option.rect.height());
}





GIS_AirRoutesPointParameter1Delegate::GIS_AirRoutesPointParameter1Delegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *GIS_AirRoutesPointParameter1Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TURNS:{          //旋转圈数
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");
        QRegExp regx("[0-9]+$");
        QValidator* validator = new QRegExpValidator(regx, editor);
        editor->setValidator(validator);                            //设置只能输入正整数
        editor->setMaxLength(2);                                    //设置输入范围0~99
        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        editor->setToolTip(index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString());
        return editor;
    }case GIS_AirRouteItemModel::MAV_CMD_NAV_WAYPOINT:              //航点
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TIME:            //悬停时间
    case GIS_AirRouteItemModel::MAV_CMD_NAV_SPLINE_WAYPOINT:        //航点(spline)
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_DELAY:{           //条件-延时
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        QRegExp regx("[0-9]+$");
        QValidator* validator = new QRegExpValidator(regx, editor);
        editor->setValidator(validator);                            //设置只能输入正整数
        editor->setMaxLength(4);                                    //设置输入范围0~9999
        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }case  GIS_AirRouteItemModel::MAV_CMD_NAV_PAYLOAD_PLACE:        //最大下降高度
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_DISTANCE:{        //条件-距离
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        QRegExp regx("[0-9]+$");
        QValidator* validator = new QRegExpValidator(regx, editor);
        editor->setValidator(validator);                            //设置只能输入正整数
        editor->setMaxLength(3);                                    //设置输入范围0~99
        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }case GIS_AirRouteItemModel::MAV_CMD_DO_SET_RELAY:              //继电器序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:            //继电器序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_SERVO:               //伺服序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{                  //放线装置序号
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        QRegExp regx("[0-9]+$");
        QValidator* validator = new QRegExpValidator(regx, editor);
        editor->setValidator(validator);                            //设置只能输入正整数
        editor->setMaxLength(2);                                    //设置输入范围0~99

        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:{                //延时
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        QIntValidator * validator = new QIntValidator(-1,127,editor);      //仅能输入整数
        editor->setValidator(validator);
        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:{            //目标角度
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");
        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        QIntValidator * validator = new QIntValidator(editor);      //仅能输入整数
        editor->setValidator(validator);

        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }case GIS_AirRouteItemModel::MAV_CMD_DO_JUMP:{                  //Do跳转
        QComboBox *editor = new QComboBox(parent);
        editor->setObjectName("DelegateComboBox");
        editor->setView(new QListView());
        editor->setFrame(true);
        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        QList<int> pointList = index.data(GIS_AirRouteItemModel::DATA_RouteItemID).value<QList<int>>();
        int selfID = index.data(GIS_AirRouteItemModel::DATA_PointID).toInt();
        for(int i = 0; i < pointList.count(); i++){
            if(pointList.at(i) == selfID){
                continue;
            }
            editor->addItem(QString::number(pointList.at(i)));
        }

        editor->setToolTip(whatThisText);

        editor->setCurrentText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }
    case GIS_AirRouteItemModel::MAV_CMD_DO_LAND_START:{                  //Do跳转
            QComboBox *editor = new QComboBox(parent);
            editor->setObjectName("DelegateComboBox");
            editor->setView(new QListView());
            editor->setFrame(true);
            QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
            QList<int> pointList = index.data(GIS_AirRouteItemModel::DATA_RouteItemID).value<QList<int>>();
            int selfID = index.data(GIS_AirRouteItemModel::DATA_PointID).toInt();
            for(int i = 0; i < pointList.count(); i++){
                if(pointList.at(i) == selfID){
                    continue;
                }
                editor->addItem(QString::number(pointList.at(i)));
            }

            editor->setToolTip(whatThisText);

            editor->setCurrentText(index.model()->data(index,Qt::DisplayRole).toString());
            return editor;
        }
    case GIS_AirRouteItemModel::MAV_CMD_DO_CHANGE_SPEED:{          //Do改变速度
        QComboBox *editor = new QComboBox(parent);
        editor->setObjectName("DelegateComboBox");
        editor->setView(new QListView());
        editor->setFrame(true);
        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();

        editor->setToolTip(whatThisText);

        editor->insertItem(0,QString("Airspeed"));
        editor->insertItem(1,QString("Ground Speed"));
        editor->insertItem(2,QString("Climb Speed"));
        editor->insertItem(3,QString("Descent Speed"));
        editor->setCurrentIndex(index.model()->data(index,Qt::DisplayRole).toInt());
        return editor;
    }

    default:
        return nullptr;
    }
}

void GIS_AirRoutesPointParameter1Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TURNS:          //旋转圈数
    case GIS_AirRouteItemModel::MAV_CMD_NAV_WAYPOINT:              //航点
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TIME:           //悬停时间
    case GIS_AirRouteItemModel::MAV_CMD_NAV_SPLINE_WAYPOINT:       //航点(spline)
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_DELAY:           //条件-延时
    case  GIS_AirRouteItemModel::MAV_CMD_NAV_PAYLOAD_PLACE:        //最大下降高度
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_DISTANCE:        //条件-距离
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_RELAY:              //继电器序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:           //继电器序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_SERVO:              //伺服序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:                  //放线装置序号
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:                 //延时
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:{            //目标角度
        QString value = QString::number(index.model()->data(index, Qt::DisplayRole).toInt());
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        edit->setText(value);
        break;
    }case GIS_AirRouteItemModel::MAV_CMD_DO_JUMP:{                  //Do跳转
        QString value = QString::number(index.model()->data(index, Qt::DisplayRole).toInt());
        QComboBox *edit = static_cast<QComboBox*>(editor);
        edit->setCurrentText(value);
        break;};
    case GIS_AirRouteItemModel::MAV_CMD_DO_LAND_START:{                  //Do跳转
            QString value = QString::number(index.model()->data(index, Qt::DisplayRole).toInt());
            QComboBox *edit = static_cast<QComboBox*>(editor);
            edit->setCurrentText(value);
            break;
    }case GIS_AirRouteItemModel::MAV_CMD_DO_CHANGE_SPEED:{          //Do改变速度
        int value = index.model()->data(index, Qt::DisplayRole).toInt();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentIndex(value);
        break;
    }
    default:
        break;
    }
}

void GIS_AirRoutesPointParameter1Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TURNS:          //旋转圈数
    case GIS_AirRouteItemModel::MAV_CMD_NAV_WAYPOINT:              //航点
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TIME:           //悬停时间
    case GIS_AirRouteItemModel::MAV_CMD_NAV_SPLINE_WAYPOINT:       //航点(spline)
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_DELAY:           //条件-延时
    case  GIS_AirRouteItemModel::MAV_CMD_NAV_PAYLOAD_PLACE:        //最大下降高度
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_DISTANCE:        //条件-距离
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_RELAY:              //继电器序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:           //继电器序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_SERVO:              //伺服序号
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:                  //放线装置序号
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:                 //延时
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:{            //目标角度
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        QString str = edit->text();
        model->setData(index, str, Qt::EditRole);
        break;
    }case GIS_AirRouteItemModel::MAV_CMD_DO_JUMP:{                  //Do跳转
        QComboBox *edit = static_cast<QComboBox *>(editor);
        QString str = edit->currentText();
        model->setData(index,str.toInt(),Qt::EditRole);

        break;}
    case GIS_AirRouteItemModel::MAV_CMD_DO_LAND_START:{                  //Do跳转
            QComboBox *edit = static_cast<QComboBox *>(editor);
            QString str = edit->currentText();
            model->setData(index,str.toInt(),Qt::EditRole);

            break;
    }case GIS_AirRouteItemModel::MAV_CMD_DO_CHANGE_SPEED:{          //Do改变速度
        int value = index.model()->data(index, Qt::DisplayRole).toInt();
        QComboBox* box = static_cast<QComboBox*>(editor);
        box->setCurrentIndex(value);
        break;
    }
    }

}

void GIS_AirRoutesPointParameter1Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    editor->setGeometry(option.rect.x(),option.rect.y(),option.rect.width(),option.rect.height());
}








GIS_AirRoutesPointParameter2Delegate::GIS_AirRoutesPointParameter2Delegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *GIS_AirRoutesPointParameter2Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:                 //延时
    case GIS_AirRouteItemModel::MAV_CMD_DO_JUMP:                  //Do跳转
    case GIS_AirRouteItemModel::MAV_CMD_DO_LAND_START:                  //Do跳转
    case GIS_AirRouteItemModel::MAV_CMD_DO_CHANGE_SPEED:
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_RELAY:
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_SERVO:
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }default:
        return nullptr;
    }

    return nullptr;
}

void GIS_AirRoutesPointParameter2Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:                 //延时
    case GIS_AirRouteItemModel::MAV_CMD_DO_JUMP:                  //Do跳转
    case GIS_AirRouteItemModel::MAV_CMD_DO_LAND_START:                  //Do跳转
    case GIS_AirRouteItemModel::MAV_CMD_DO_CHANGE_SPEED:
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_RELAY:
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:
    case GIS_AirRouteItemModel::MAV_CMD_DO_SET_SERVO:
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{
        QString value = QString::number(index.model()->data(index, Qt::DisplayRole).toInt());
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        edit->setText(value);
        break;
    }default:
        break;
    }
}

void GIS_AirRoutesPointParameter2Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    QString str = edit->text();
    model->setData(index, str, Qt::EditRole);

}

void GIS_AirRoutesPointParameter2Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}





GIS_AirRoutesPointParameter3Delegate::GIS_AirRoutesPointParameter3Delegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *GIS_AirRoutesPointParameter3Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TURNS:                 //延时
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }default:
        return nullptr;
    }

    return nullptr;
}

void GIS_AirRoutesPointParameter3Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_LOITER_TURNS:                 //延时
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:
    case GIS_AirRouteItemModel::MAV_CMD_DO_REPEAT_RELAY:
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{
        QString value = QString::number(index.model()->data(index, Qt::DisplayRole).toInt());
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        edit->setText(value);
        break;
    }default:
        break;
    }
}

void GIS_AirRoutesPointParameter3Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    QString str = edit->text();
    model->setData(index, str, Qt::EditRole);
}

void GIS_AirRoutesPointParameter3Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}







GIS_AirRoutesPointParameter4Delegate::GIS_AirRoutesPointParameter4Delegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *GIS_AirRoutesPointParameter4Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{
        QLineEdit *editor = new QLineEdit(parent);
        editor->setObjectName("DelegateLineEdit");

        QString whatThisText = index.model()->data(index,GIS_AirRouteItemModel::DATA_WHATTHIS).toString();
        editor->setToolTip(whatThisText);

        editor->setText(index.model()->data(index,Qt::DisplayRole).toString());
        return editor;
    }default:
        return nullptr;
    }

    return nullptr;
}

void GIS_AirRoutesPointParameter4Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int commondID = index.model()->data(index,GIS_AirRouteItemModel::DATA_PointCommondID).toInt();
    switch(commondID){
    case GIS_AirRouteItemModel::MAV_CMD_NAV_DELAY:
    case GIS_AirRouteItemModel::MAV_CMD_CONDITION_YAW:
    case GIS_AirRouteItemModel::MAV_CMD_DO_WINCH:{
        QString value = QString::number(index.model()->data(index, Qt::DisplayRole).toInt());
        QLineEdit *edit = static_cast<QLineEdit*>(editor);
        edit->setText(value);
        break;
    }default:
        break;
    }
}

void GIS_AirRoutesPointParameter4Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = static_cast<QLineEdit*>(editor);
    QString str = edit->text();
    model->setData(index, str, Qt::EditRole);
}

void GIS_AirRoutesPointParameter4Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
