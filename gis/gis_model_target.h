#ifndef GIS_TARGETMODEL_H
#define GIS_TARGETMODEL_H
#include <QAbstractItemModel>
#include <QGeoCoordinate>
#include <QDebug>

class GIS_ModelTarget : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(AirPointDataRole)
public:
    enum AirPointDataRole{
        DATA_PointCoor = Qt::UserRole + 1,
        DATA_PointIsShow,
    };


public:
    GIS_ModelTarget();

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;


private:
    QGeoCoordinate coor =QGeoCoordinate(34,108) ;
    bool isShow = false;

public:
    void update_target(double lat,double lng,bool visable);

};
#endif // GIS_ModelTarget_H
