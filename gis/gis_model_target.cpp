#include "gis_model_target.h"
#include "qglobal.h"
#include "DMMM.h"
GIS_ModelTarget::GIS_ModelTarget()
{

}

QVariant GIS_ModelTarget::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QModelIndex GIS_ModelTarget::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex GIS_ModelTarget::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int GIS_ModelTarget::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int GIS_ModelTarget::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;

}

QVariant GIS_ModelTarget::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    if (!index.isValid())
        return QVariant();
    switch(role){
    case AirPointDataRole::DATA_PointCoor:
        return QVariant::fromValue<QGeoCoordinate>(this->coor);
    case AirPointDataRole::DATA_PointIsShow:{
        return QVariant(this->isShow);
    }default:{
        return QVariant();
    }
    }

}

bool GIS_ModelTarget::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if (!index.isValid())
//        return false;

    switch(role){
    case AirPointDataRole::DATA_PointCoor:{

        QGeoCoordinate tmp = value.value<QGeoCoordinate>();
        if(!tmp.isValid()){
           return false;
        }
        if(this->coor == tmp){
            return true;
        }
        this->beginResetModel();
        if(tmp.isValid()){
            this->coor = tmp;
        }

        this->endResetModel();
        return true;
    }case AirPointDataRole::DATA_PointIsShow:{
        if(this->isShow == value.toBool())return true;
        this->beginResetModel();
        this->isShow = value.toBool();
        this->endResetModel();
        return true;
    }
    }

    return false;
}


QHash<int, QByteArray> GIS_ModelTarget::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AirPointDataRole::DATA_PointCoor] = "pointCoor";
    roles[AirPointDataRole::DATA_PointIsShow] = "pointIsShow";

    return roles;

}

void GIS_ModelTarget::update_target(double lat, double lng, bool visable)
{
    QGeoCoordinate tmp_coor = QGeoCoordinate(lat,lng);
    if(isShow != visable || tmp_coor != coor){
        this->beginResetModel();

        isShow = visable;
        coor = tmp_coor;
        this->endResetModel();
    }

}
