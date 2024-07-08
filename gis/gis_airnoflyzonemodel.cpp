#include "gis_airnoflyzonemodel.h"
GIS_AirNoFlyZoneModel::GIS_AirNoFlyZoneModel()
{

}

QVariant GIS_AirNoFlyZoneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(role);
    Q_UNUSED(orientation);
    Q_UNUSED(section);

    return QVariant();
}

QModelIndex GIS_AirNoFlyZoneModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex GIS_AirNoFlyZoneModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int GIS_AirNoFlyZoneModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

int GIS_AirNoFlyZoneModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

QVariant GIS_AirNoFlyZoneModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    return QVariant();
}


QHash<int, QByteArray> GIS_AirNoFlyZoneModel::roleNames() const
{
    return QHash<int,QByteArray>();
}

















GIS_AirNoFlyZoneCircleItem::GIS_AirNoFlyZoneCircleItem()
{

}

QVariant GIS_AirNoFlyZoneCircleItem::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QVariant();
}

QModelIndex GIS_AirNoFlyZoneCircleItem::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex GIS_AirNoFlyZoneCircleItem::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int GIS_AirNoFlyZoneCircleItem::rowCount(const QModelIndex &parent) const
{

    Q_UNUSED(parent);
    return 0;
}

int GIS_AirNoFlyZoneCircleItem::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

QVariant GIS_AirNoFlyZoneCircleItem::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    return QVariant();
}



QHash<int, QByteArray> GIS_AirNoFlyZoneCircleItem::roleNames() const
{

    return QHash<int,QByteArray>();
}






















GIS_AirNoFltZonePolygonModel::GIS_AirNoFltZonePolygonModel()
{

}

QVariant GIS_AirNoFltZonePolygonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QModelIndex GIS_AirNoFltZonePolygonModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex GIS_AirNoFltZonePolygonModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

int GIS_AirNoFltZonePolygonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

int GIS_AirNoFltZonePolygonModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 0;
}

QVariant GIS_AirNoFltZonePolygonModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    return QVariant();
}


QHash<int, QByteArray> GIS_AirNoFltZonePolygonModel::roleNames() const
{
    return QHash<int,QByteArray>();
}
