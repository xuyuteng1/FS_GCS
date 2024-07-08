#include "gis_airpositionmodel.h"

GIS_AirPositionModel::GIS_AirPositionModel(QObject *parent)
    : QAbstractItemModel(parent)
{   

}

QVariant GIS_AirPositionModel::headerData(int section, Qt::Orientation orientation, int role) const
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

QModelIndex GIS_AirPositionModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);
    Q_UNUSED(parent);
    return createIndex(row,0);
}

QModelIndex GIS_AirPositionModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int GIS_AirPositionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return airPositionMap.count();
}

int GIS_AirPositionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 0;
}

QVariant GIS_AirPositionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    if(row >= 0 && row < this->airPositionMap.count()&& row < this->airPositionIDList.count()){
        if(this->airPositionMap.find(this->airPositionIDList[row]) != this->airPositionMap.end()){
            GIS_AirPositionData *data = this->airPositionMap.find(this->airPositionIDList[row]).value();
            switch(role){
            case DATA_AirId:
                return data->getAirId();
            case DATA_AirLng:
                return QString::number(data->getAirLng(),'f',7).toDouble();
            case DATA_AirLat:
                return QString::number(data->getAirLat(),'f',7).toDouble();
            case DATA_AirAlititude:
                return QString::number(data->getAirAlititude(),'f',2).toFloat();
            case DATA_AirRelativeAlititude:
                return QString::number(data->getAirRelativeAlititude(),'f',2).toFloat();
            case DATA_AirSpeed:
                return QString::number(data->getAirSpeed(),'f',2).toFloat();
            case DATA_GndSpeed:
                return QString::number(data->getGndSpeed(),'f',2).toFloat();                                 //飞行器速度
            case DATA_AirMode:
                return data->getAirMode();
            case DATA_AirState:
                return data->getAirState();
            case DATA_AirCourse:
                return data->getAirCourse();
            case DATA_AirVisible:
                return data->getAirVisible();
            case DATA_AirTextVisible:
                return data->getAirTextVisible();
            case DATA_AirImage:
                return data->getAirImage();
            case DATA_AirTrackPath:
                return QVariant::fromValue<QList<QGeoCoordinate>>(data->getTrackList().path());
            case DATA_MAVID:
                return data->getMavID();
            default:
                return QVariant();
            }
        }
    }
    return QVariant();
}

QVariant GIS_AirPositionModel::dataForID(int id, int role) const
{
    if(this->airPositionMap.find(id) == this->airPositionMap.end()){
        return QVariant();
    }
    GIS_AirPositionData *data = this->airPositionMap.find(id).value();
    switch(role){
    case DATA_AirId:
        return data->getAirId();
    case DATA_AirLng:
        return data->getAirLng();
    case DATA_AirLat:
        return data->getAirLat();
    case DATA_AirAlititude:
        return data->getAirAlititude();
    case DATA_AirRelativeAlititude:
        return data->getAirRelativeAlititude();
    case DATA_AirSpeed:
        return data->getAirSpeed();
    case DATA_GndSpeed:
        return data->getGndSpeed();
    case DATA_AirMode:
        return data->getAirMode();
    case DATA_AirState:
        return data->getAirState();
    case DATA_AirCourse:
        return data->getAirCourse();
    case DATA_AirVisible:
        return data->getAirVisible();
    case DATA_AirTextVisible:
        return data->getAirTextVisible();
    case DATA_AirImage:
        return data->getAirImage();
    case DATA_MAVID:
        return data->getMavID();
    case DATA_AirTrackPath:
        return QVariant::fromValue<QList<QGeoCoordinate>>(data->getTrackList().path());
    default:
        return QVariant();
    }
}

QMap<int, QVariant> GIS_AirPositionModel::itemData(const QModelIndex &index) const
{
    int row = index.row();
    QMap<int ,QVariant> map;
    if(row >= 0 && row < this->airPositionMap.count()&& row < this->airPositionIDList.count()){
        GIS_AirPositionData *data = this->airPositionMap.find(this->airPositionIDList[row]).value();
        map.insert(DATA_AirId,data->getAirId());
        map.insert(DATA_AirLng,data->getAirLng());
        map.insert(DATA_AirLat,data->getAirLat());
        map.insert(DATA_AirAlititude,data->getAirAlititude());
        map.insert(DATA_AirCourse,data->getAirCourse());
        map.insert(DATA_AirVisible,data->getAirVisible());
        map.insert(DATA_AirTextVisible,data->getAirTextVisible());
        map.insert(DATA_AirImage,data->getAirImage());
        map.insert(DATA_AirTrackPath,QVariant::fromValue(data->getTrackList().path()));
        map.insert(DATA_AirRelativeAlititude,data->getAirRelativeAlititude());
        map.insert(DATA_AirSpeed,data->getAirSpeed());
        map.insert(DATA_GndSpeed,data->getGndSpeed());
        map.insert(DATA_AirMode,data->getAirMode());
        map.insert(DATA_AirState,data->getAirState());
        map.insert(DATA_AirId,data->getMavID());
    }
    return map;
}

bool GIS_AirPositionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    int row = index.row();
    if(row >= 0 && row < this->airPositionMap.count()&& row < this->airPositionIDList.count()){
        GIS_AirPositionData *data = this->airPositionMap.find(this->airPositionIDList[row]).value();
        switch(role){
        case DATA_AirId:
            return false;
        case DATA_AirLng:
            data->setAirLng(value.toDouble());
            return true;
        case DATA_AirLat:
            data->setAirLat(value.toDouble());
            return true;
        case DATA_AirAlititude:
            data->setAirAlititude(value.toFloat());
            return true;
        case DATA_AirCourse:
            data->setAirCourse(value.toInt());
            return true;
        case DATA_AirVisible:
            data->setAirVisible(value.toBool());
            return true;
        case DATA_AirTextVisible:
            data->setAirTextVisible(value.toBool());
            return true;
        case DATA_AirImage:
            data->setAirImage(value.toString());
            return true;

        case DATA_AirRelativeAlititude:
            data->setAirRelativeAlititude(value.toFloat());
            return true;
        case DATA_AirSpeed:
            data->setAirSpeed(value.toFloat());
            return true;
        case DATA_GndSpeed:
            data->setGndSpeed(value.toFloat());
            return true;
        case DATA_AirMode:
            data->setAirMode(value.toString());
            return true;
        case DATA_AirState:
            data->setAirState(value.toString());
            return true;
        case DATA_MAVID:
            data->setMavID(value.toInt());
            return true;
        default:
            return false;
        }
    }
    return false;
}

QHash<int, QByteArray> GIS_AirPositionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DATA_AirId] = "AirID";
    roles[DATA_AirLng] = "AirLng";
    roles[DATA_AirLat] = "AirLat";
    roles[DATA_AirAlititude] = "AirAlt";
    roles[DATA_AirCourse] = "AirCourse";

    roles[DATA_AirVisible] = "AirVisible";
    roles[DATA_AirTextVisible] = "AirTextVisible";
    roles[DATA_AirImage] = "AirImage";
    roles[DATA_AirTrackPath] = "AirTrackPath";
    roles[DATA_AirRelativeAlititude] = "AirRelativeAlititude";
    roles[DATA_AirSpeed] = "AirSpeed";
    roles[DATA_GndSpeed] = "GndSpeed";
    roles[DATA_AirMode] = "AirMode";
    roles[DATA_AirState] = "AirState";
    roles[DATA_MAVID] = "MAVID";
    return roles;
}

int GIS_AirPositionModel::addAirPositionData(int airID)
{
    if(this->airPositionIDList.indexOf(airID) == -1 && this->airPositionMap.find(airID) == this->airPositionMap.end()){
        GIS_AirPositionData *data = new GIS_AirPositionData(airID);
        data->setAirVisible(true);
        data->setAirTextVisible(true);
        this->airPositionIDList.append(airID);
        this->airPositionMap.insert(airID,data);
        return 0;
    }else{
        return -1;                  //当前ID存在，添加失败
    }
}

int GIS_AirPositionModel::updateAirPosition(int id, double lat, double lng, float alititude,float relative_altitude,float speed,float airspeed,QString airmode,QString airstate,uint8_t mavid)
{

    if(this->airPositionIDList.indexOf(id) == -1 || this->airPositionMap.find(id) == this->airPositionMap.end()){
        return -2;                  //当前ID不存在
    }else{
        this->beginResetModel();
        GIS_AirPositionData *data = this->airPositionMap.find(id).value();
        data->setAirLng(lng);
        data->setAirLat(lat);
        data->setAirAlititude(alititude);
        data->setAirRelativeAlititude(relative_altitude);
        data->setAirSpeed(airspeed);
        data->setGndSpeed(speed);
        data->setAirMode(airmode);
        data->setAirState(airstate);
        data->setMavID(mavid);
        if(data->getAirVisible() == false){
            data->setAirVisible(true);
        }

        data->appendTrackPath(lat,lng);
        this->endResetModel();
        emit dataChanged(index(0,0),index(this->airPositionMap.count(),6));
        return 0;
    }
}

int GIS_AirPositionModel::updateAirPosition(int id, double lat, double lng, float alititude, int course,float relative_altitude,float speed,float airspeed,QString airmode,QString airstate,uint8_t mavid)
{
    if(this->airPositionIDList.indexOf(id) == -1 || this->airPositionMap.find(id) == this->airPositionMap.end()){
        return -2;                  //当前ID不存在
    }else{
        this->beginResetModel();
        GIS_AirPositionData *data = this->airPositionMap.find(id).value();
        data->setAirLng(lng);
        data->setAirLat(lat);
        data->setAirAlititude(alititude);
        data->setAirRelativeAlititude(relative_altitude);
        data->setAirSpeed(airspeed);
        data->setGndSpeed(speed);
        data->setAirMode(airmode);
        data->setAirState(airstate);
        if(data->getAirVisible() == false){
            data->setAirVisible(true);
        }

        data->setMavID(mavid);
        data->setAirCourse(course);

        data->appendTrackPath(lat,lng);
        this->endResetModel();
        emit dataChanged(index(0,0),index(this->airPositionMap.count(),6));
        return 0;
    }
}

void GIS_AirPositionModel::clearAirTrackPath(int id)
{
    if(this->airPositionIDList.indexOf(id) == -1 || this->airPositionMap.find(id) == this->airPositionMap.end()){
        return;                  //当前ID不存在
    }else{
        this->beginResetModel();
        GIS_AirPositionData *data = this->airPositionMap.find(id).value();
        data->clearTrackList();
        this->endResetModel();
    }

}
















double GIS_AirPositionData::getAirLng() const
{
    return airLng;
}

void GIS_AirPositionData::setAirLng(double newAirLng)
{
    airLng = newAirLng;
}

double GIS_AirPositionData::getAirLat() const
{
    return airLat;
}

void GIS_AirPositionData::setAirLat(double newAirLat)
{
    airLat = newAirLat;
}

float GIS_AirPositionData::getAirAlititude() const
{
    return airAlititude;
}

void GIS_AirPositionData::setAirAlititude(float newAirAlititude)
{
    airAlititude = newAirAlititude;
}

int GIS_AirPositionData::getAirId() const
{
    return airId;
}

void GIS_AirPositionData::setAirId(int newAirId)
{
    airId = newAirId;
}

bool GIS_AirPositionData::getAirVisible() const
{
    return airVisible;
}

void GIS_AirPositionData::setAirVisible(bool newAirVisible)
{
    airVisible = newAirVisible;
}

const QString &GIS_AirPositionData::getAirImage() const
{
    return airImage;
}

void GIS_AirPositionData::setAirImage(const QString &newAirImage)
{
    airImage = newAirImage;
}

bool GIS_AirPositionData::getAirTextVisible() const
{
    return airTextVisible;
}

void GIS_AirPositionData::setAirTextVisible(bool newAirTextVisible)
{
    airTextVisible = newAirTextVisible;
}

void GIS_AirPositionData::appendTrackPath(double lat, double lng)
{
    if(this->trackList.path().count() >= 1000){
        this->trackList.removeCoordinate(0);
    }
    if(lat > -90 && lat < 90 && lng > -180 && lng < 180){
        this->trackList.addCoordinate(QGeoCoordinate(lat,lng));
    }
}

int GIS_AirPositionData::getAirCourse() const
{
    return airCourse;
}


void GIS_AirPositionData::setAirCourse(int newAirCourse)
{
    airCourse = newAirCourse;
}

float GIS_AirPositionData::getAirRelativeAlititude() const
{
    return airRelativeAlititude;
}

void GIS_AirPositionData::setAirRelativeAlititude(float newAirRelativeAlititude)
{
    airRelativeAlititude = newAirRelativeAlititude;
}

float GIS_AirPositionData::getAirSpeed() const
{
    return airSpeed;
}

void GIS_AirPositionData::setAirSpeed(float newAirSpeed)
{
    airSpeed = newAirSpeed;
}

const QString &GIS_AirPositionData::getAirMode() const
{
    return airMode;
}

void GIS_AirPositionData::setAirMode(const QString &newAirMode)
{
    airMode = newAirMode;
}

const QString &GIS_AirPositionData::getAirState() const
{
    return airState;
}

void GIS_AirPositionData::setAirState(const QString &newAirState)
{
    airState = newAirState;
}

QGeoPath &GIS_AirPositionData::getTrackList()
{
    return trackList;
}

void GIS_AirPositionData::setTrackList(const QGeoPath &newTrackList)
{
    trackList = newTrackList;
}


void GIS_AirPositionData::clearTrackList()
{
    this->trackList.clearPath();
}

float GIS_AirPositionData::getGndSpeed() const
{
    return gndSpeed;
}

void GIS_AirPositionData::setGndSpeed(float newGndSpeed)
{
    gndSpeed = newGndSpeed;
}

int GIS_AirPositionData::getMavID() const
{
    return MavID;
}

void GIS_AirPositionData::setMavID(int newMavID)
{
    MavID = newMavID;
}
