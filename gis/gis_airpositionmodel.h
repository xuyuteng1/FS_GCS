#ifndef GIS_AIRPOSITIONMODEL_H
#define GIS_AIRPOSITIONMODEL_H

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QHash>
#include <QDebug>
#include <QPair>
#include <QList>
#include <QtPositioning>


class GIS_AirPositionData{
public:
    inline GIS_AirPositionData(int id){this->airId = id;}

    double getAirLng() const;
    void setAirLng(double newAirLng);

    double getAirLat() const;
    void setAirLat(double newAirLat);

    float getAirAlititude() const;
    void setAirAlititude(float newAirAlititude);

    int getAirId() const;       /* 飞行器ID只有在创建数据模型时被赋值 */

    void setAirId(int newAirId);

    bool getAirVisible() const;
    void setAirVisible(bool newAirVisible);

    const QString &getAirImage() const;
    void setAirImage(const QString &newAirImage);

    bool getAirTextVisible() const;
    void setAirTextVisible(bool newAirTextVisible);

    QGeoPath &getTrackList();
    void setTrackList(const QGeoPath &newTrackList);

    void appendTrackPath(double lat,double lng);

    int getAirCourse() const;
    void setAirCourse(int newAirCourse);

    float getAirRelativeAlititude() const;
    void setAirRelativeAlititude(float newAirRelativeAlititude);

    float getAirSpeed() const;
    void setAirSpeed(float newAirSpeed);
    const QString &getAirMode() const;
    void setAirMode(const QString &newAirMode);

    const QString &getAirState() const;
    void setAirState(const QString &newAirState);

    void clearTrackList();



    float getGndSpeed() const;
    void setGndSpeed(float newGndSpeed);

    int getMavID() const;
    void setMavID(int newMavID);

private:
    int         airId;
    double      airLng;
    double      airLat;
    float       airAlititude;
    float       airRelativeAlititude;
    float       airSpeed;
    float       gndSpeed;
    int         airCourse = 0;

    bool        airVisible = true;
    bool        airTextVisible = false;
    QString     airImage = QString("qrc:/img/air/air.png");
    QString     airMode;
    QString     airState;
    QGeoPath    trackList;
    int         MavID;
};


class GIS_AirPositionModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_ENUMS(AirPositionDataRoles)
public:
    enum AirPositionDataRoles{
        DATA_AirId = Qt::UserRole + 1,              //飞行器ID
        DATA_AirLng,                                //飞行器经度
        DATA_AirLat,                                //飞行器纬度
        DATA_AirAlititude,                          //飞行器高度
        DATA_AirCourse,                             //飞行器航向

        DATA_AirVisible,                            //飞行器地图显示使能
        DATA_AirTextVisible,                        //飞行器文字信息显示使能
        DATA_AirImage,                              //飞行器图标
        DATA_AirTrackPath,                          //飞行轨迹数据

        DATA_AirRelativeAlititude,                  //飞行器相对
        DATA_AirSpeed,                              //飞行器速度
        DATA_GndSpeed,                              //飞行器速度
        DATA_AirMode,                              //飞行器模式
        DATA_AirState,                              //飞行器飞行状态
        DATA_MAVID,                                 //飞行器id
    };

    explicit GIS_AirPositionModel(QObject *parent = nullptr);

    // Header:
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QVariant dataForID(int id, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QMap<int, QVariant> itemData(const QModelIndex &index) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;


    int addAirPositionData(int airID);

    int updateAirPosition(int id,double lat,double lng,float alititude ,float relative_altitude,float speed,float airspeed,QString airmode,QString airstate,uint8_t mavid);                          //更新飞行器经度，纬度，高度信息

    int updateAirPosition(int id,double lat,double lng,float alititude,int course,float relative_altitude,float speed,float airspeed,QString airmode,QString airstate,uint8_t mavid);                 //更新飞行器经度，纬度，高度信息

    void clearAirTrackPath(int id);

private:
    QList<int>                      airPositionIDList;
    QMap<int ,GIS_AirPositionData *>airPositionMap;
signals:
    void updateAirPositionView(int id);

};

#endif // GIS_AIRPOSITIONMODEL_H
