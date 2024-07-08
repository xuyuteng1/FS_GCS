#include "gis_RTLmodel.h"
#include "qglobal.h"

GIS_RTLWaypointModel::GIS_RTLWaypointModel()
{
}

QVariant GIS_RTLWaypointModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QModelIndex GIS_RTLWaypointModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex GIS_RTLWaypointModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int GIS_RTLWaypointModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int GIS_RTLWaypointModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;

}

QVariant GIS_RTLWaypointModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    if (!index.isValid())
        return QVariant();
    switch(role){
    case AirPointDataRole::DATA_PointCoor:      return QVariant::fromValue<QGeoCoordinate>(this->coor);
    case AirPointDataRole::DATA_PointIsShow:    return QVariant(this->isShow);
    case AirPointDataRole::DATA_PointAlt:       return QVariant(this->alt_m);
    case AirPointDataRole::DATA_PointRadius:       return QVariant(qAbs( this->radius));
    default: return QVariant();
    }
}

bool GIS_RTLWaypointModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    switch(role){
    case AirPointDataRole::DATA_PointCoor:{
        this->beginResetModel();
        QGeoCoordinate tmp = value.value<QGeoCoordinate>();
        if(tmp.isValid()){
            this->coor = tmp;
        }
        this->endResetModel();
        /* 通知已经修改 */
        emit dataChanged();
        return true;
    }
    case AirPointDataRole::DATA_PointIsShow:{
        this->beginResetModel();
        this->isShow = value.toBool();
        this->endResetModel();
        return true;
    }
    case AirPointDataRole::DATA_PointAlt:{
        this->beginResetModel();
        this->alt_m = value.toFloat();
        this->endResetModel();
        return true;
    }
    case AirPointDataRole::DATA_PointRadius:{
        this->beginResetModel();
        this->radius = value.toInt();
        this->endResetModel();
        return true;
    }
    }
    return false;
}


QHash<int, QByteArray> GIS_RTLWaypointModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AirPointDataRole::DATA_PointCoor] = "pointCoor";
    roles[AirPointDataRole::DATA_PointIsShow] = "pointIsShow";
    roles[AirPointDataRole::DATA_PointAlt] = "pointAlt";
    roles[AirPointDataRole::DATA_PointRadius] = "pointRadius";
    return roles;

}

bool GIS_RTLWaypointModel::getIsShow() const
{
    return isShow;

}

void GIS_RTLWaypointModel::setIsShow(bool newIsShow)
{
    this->beginResetModel();
    isShow = newIsShow;
    this->endResetModel();
}

const QGeoCoordinate &GIS_RTLWaypointModel::getCoor() const
{
    return coor;
}

void GIS_RTLWaypointModel::setCoor(const QGeoCoordinate &newCoor)
{
    this->beginResetModel();
    coor = newCoor;
    this->endResetModel();
}

void GIS_RTLWaypointModel::update_Waypoint(double lat, double lng, float alt,int _radius,bool visable)
{
    QGeoCoordinate tmp_coor = QGeoCoordinate(lat,lng);
    if(isShow != visable || tmp_coor != coor || radius!= _radius){
        this->beginResetModel();

        isShow = visable;
        coor = tmp_coor;
        radius= _radius;
        this->alt_m = alt;
        this->endResetModel();
    }

}
