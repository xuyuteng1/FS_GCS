#ifndef GIS_RTLWAYPOINT_MODEL_H
#define GIS_RTLWAYPOINT_MODEL_H
#include <QAbstractItemModel>
#include <QGeoCoordinate>
#include <QDebug>

class GIS_RTLWaypointModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(AirPointDataRole)
public:
    enum AirPointDataRole{
        DATA_PointCoor = Qt::UserRole + 1,
        DATA_PointIsShow,
        DATA_PointAlt,
        DATA_PointRadius,
    };


public:
    GIS_RTLWaypointModel();

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

    bool getIsShow() const;
    void setIsShow(bool newIsShow);

private:
    QGeoCoordinate coor =QGeoCoordinate(0,0);
    float    alt_m;              /*< [m] Altitude (MSL). Positive for up.*/
    bool     isShow = false;
    int      radius = 0;
public:
    const QGeoCoordinate &getCoor() const;
    void setCoor(const QGeoCoordinate &newCoor);

public slots:
    void update_Waypoint(double lat, double lng, float alt,int radius, bool visable);
signals:
    void dataChanged();
};

#endif // GIS_RTLWaypointModel_H
