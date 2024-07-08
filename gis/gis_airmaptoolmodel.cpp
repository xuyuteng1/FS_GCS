#include "gis_airmaptoolmodel.h"

GIS_AirMapToolModel::GIS_AirMapToolModel()
{

}

QVariant GIS_AirMapToolModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal){
        if(role == Qt::DisplayRole){
            QHash<int, QByteArray> roles = roleNames();
            return QVariant(roles[section + Qt::UserRole + 1]);
        }else {
            return QVariant();
        }
    }
    return QVariant();
}

QModelIndex GIS_AirMapToolModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,0);
}

QModelIndex GIS_AirMapToolModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int GIS_AirMapToolModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->pointList.count();

}

int GIS_AirMapToolModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;

}

QVariant GIS_AirMapToolModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role == AirMapToolRoles::ToolGeoCoorList){
        switch(this->model){
            case 2:{                
                return QVariant::fromValue<QList<QGeoCoordinate>>(pointList);
            }case 3:{
                return QVariant::fromValue<QList<QGeoCoordinate>>(this->pointList);
            }case 4:{
                return QVariant::fromValue<QList<QGeoCoordinate>>(this->pointList);
            }default:
                return QVariant();
        }

    }else if(role == AirMapToolRoles::ToolGeoCoorPoint){
        int row = index.row();
        if(row < 0 || row >= this->pointList.count()){
            return QVariant();
        }
        return QVariant::fromValue<QGeoCoordinate>(this->pointList.at(row));
    }else if(role ==AirMapToolRoles::ToolMouseClickedPoint){
        return QVariant::fromValue<QGeoCoordinate>(this->mouseClickedPoint);
    }else{
        return QVariant();
    }
}

bool GIS_AirMapToolModel::setData(const QModelIndex &index, const QVariant &data, int role)
{
    if (!index.isValid())
        return false;

    switch(role){
    case ToolModel:{
        this->beginResetModel();
        this->model = data.toInt();
        this->pointList.clear();
        this->firstPointValid = false;
        this->endResetModel();
        return true;
    }case ToolMouseClickedPoint:{
        if(this->model == 2){
            if(this->firstPointValid == false){
                this->beginResetModel();
                this->pointList.clear();
                this->pointList.append(data.value<QGeoCoordinate>());
                this->firstPointValid = true;
                this->endResetModel();
                return true;
            }else{
                this->beginResetModel();
                this->pointList.append(data.value<QGeoCoordinate>());
                this->endResetModel();
                return true;
            }
        }else if(this->model == 3){
            if(this->firstPointValid == false){
                this->beginResetModel();
                this->pointList.clear();
                this->pointList.append(data.value<QGeoCoordinate>());
                this->pointList.append(data.value<QGeoCoordinate>());
                this->firstPointValid = true;
                this->endResetModel();
            }else{
                this->beginResetModel();
                this->pointList.insert(this->pointList.count() - 1,data.value<QGeoCoordinate>());
                this->endResetModel();
                return true;

            }
        }else if(this->model == 4){

        }else if(this->model == 5){
            this->mouseClickedPoint = data.value<QGeoCoordinate>();
        }

        return false;
    }
    default:

        break;
    }
    return false;

}

QHash<int, QByteArray> GIS_AirMapToolModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ToolModel] = "ToolModel";
    roles[ToolGeoCoorList] = "ToolGeoCoorList";
    roles[ToolGeoCoorPoint] = "ToolGeoCoorPoint";
    roles[ToolMouseClickedPoint] = "ToolMouseClickedPoint";

    return roles;
}
