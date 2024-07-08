#ifndef GIS_AIRNOFLYZONEMODEL_H
#define GIS_AIRNOFLYZONEMODEL_H

#include <QAbstractItemModel>


class GIS_AirNoFlyZoneCircleItemData{
public:
    inline GIS_AirNoFlyZoneCircleItemData(){}


private:


};


class GIS_AirNoFltZonePolygonModel : public QAbstractItemModel
{
public:
    GIS_AirNoFltZonePolygonModel();

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

};


class GIS_AirNoFlyZoneCircleItem : public QAbstractItemModel{
public:
    GIS_AirNoFlyZoneCircleItem();

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;


};



class GIS_AirNoFlyZoneModel : public QAbstractItemModel
{
public:
    GIS_AirNoFlyZoneModel();

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

};

#endif // GIS_AIRNOFLYZONEMODEL_H
