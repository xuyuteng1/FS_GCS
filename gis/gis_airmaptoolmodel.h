#ifndef GIS_AIRMAPTOOLMODEL_H
#define GIS_AIRMAPTOOLMODEL_H
#include <QAbstractItemModel>
#include <QtPositioning>


class GIS_AirMapToolModel : public QAbstractItemModel
{
    Q_ENUMS(AirMapToolRoles)
public:
    GIS_AirMapToolModel();

    enum AirMapToolRoles{
        ToolModel = Qt::UserRole + 1,
        ToolGeoCoorList,
        ToolGeoCoorPoint,
        ToolMouseClickedPoint,
    };


    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

private:
    int model = 0;
    bool firstPointValid = false;       /*第一个点有效标志*/
    QList<QGeoCoordinate> pointList;    /*点经纬度测量*/

    QGeoCoordinate mouseClickedPoint;

};

#endif // GIS_AIRMAPTOOLMODEL_H

