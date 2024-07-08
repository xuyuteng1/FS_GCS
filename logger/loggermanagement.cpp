#include "loggermanagement.h"

#include <QDebug>
#include <QThreadPool>
SystemLogger *LoggerManagement::systemLogger = nullptr;
XlsxLogger *LoggerManagement::xlsxLogger = nullptr;
TextLogger *LoggerManagement::textLogger = nullptr;
LogReplay   *LoggerManagement::replay = nullptr;

LoggerManagement::LoggerManagement()
{
    if(systemLogger == nullptr){
        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        systemLogger = getLogger();
        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    }
    if(xlsxLogger == nullptr){
        xlsxLogger = getXlsxLogger();
    }

    if(textLogger == nullptr){
        textLogger = getTextLogger();
    }

    if(this->timer == nullptr){
        this->timer = new QTimer;
        connect(this->timer,&QTimer::timeout,this,&LoggerManagement::timeroutSlot);
    }
    this->dataLogFieldList = this->getDataLogFieldList();
    connectSignalAndSlot();
    this->timer->start(100);
}

SystemLogger *LoggerManagement::getLogger()
{
    if(systemLogger == nullptr){
        systemLogger = new SystemLogger;
        QThreadPool::globalInstance()->start(systemLogger);
    }
    return systemLogger;
}

XlsxLogger *LoggerManagement::getXlsxLogger()
{
    if(xlsxLogger == nullptr){
        xlsxLogger = new XlsxLogger;
    }
    return xlsxLogger;
}

LogReplay *LoggerManagement::getReplay()
{
    if(replay == nullptr){
        replay = new LogReplay;
    }
    return replay;
}


TextLogger *LoggerManagement::getTextLogger()
{
    if(textLogger == nullptr){
        textLogger = new TextLogger;
    }

    return textLogger;
}

QList<QString> LoggerManagement::getDataLogFieldList()
{
    QList<QString> fieldList;
    fieldList.append("time");

    fieldList.append("mav_version");

//SysInfo_t结构体数据
    fieldList.append("SysInfo_t.frame");
    fieldList.append("SysInfo_t.flight_mode");
    fieldList.append("SysInfo_t.state1");
    fieldList.append("SysInfo_t.CPULoad");
    fieldList.append("SysInfo_t.time_sinceboot_s");
    fieldList.append("SysInfo_t.flight_time_s");
    fieldList.append("SysInfo_t.total_flight_time_s");
    fieldList.append("SysInfo_t.flight_dis_m");
    fieldList.append("SysInfo_t.total_flight_dis_m");
    fieldList.append("SysInfo_t.boot_cnt");
    fieldList.append("SysInfo_t.Battery_voltage_mv");
    fieldList.append("SysInfo_t.Battery_Current_CA");
    fieldList.append("SysInfo_t.throttle");
    fieldList.append("SysInfo_t.temperture");
    fieldList.append("SysInfo_t.sensor_state");
    fieldList.append("SysInfo_t.home_dist_m");
    fieldList.append("SysInfo_t.home_bearing_cd");
    fieldList.append("SysInfo_t.wp_dist_m");
    fieldList.append("SysInfo_t.alt_error");
    fieldList.append("SysInfo_t.xtrack_error");

//vehicle_t.
    fieldList.append("vehicle_t.roll_cd");
    fieldList.append("vehicle_t.pitch_cd");
    fieldList.append("vehicle_t.yaw_cd");

    fieldList.append("vehicle_t.acc_mpss_x");
    fieldList.append("vehicle_t.acc_mpss_y");
    fieldList.append("vehicle_t.acc_mpss_z");
    fieldList.append("vehicle_t.gyro_dps_x");
    fieldList.append("vehicle_t.gyro_dps_y");
    fieldList.append("vehicle_t.gyro_dps_z");
    fieldList.append("vehicle_t.lat");
    fieldList.append("vehicle_t.lng");
    fieldList.append("vehicle_t.alt_m");
    fieldList.append("vehicle_t.pos_m_x");
    fieldList.append("vehicle_t.pos_m_y");
    fieldList.append("vehicle_t.pos_m_z");
    fieldList.append("vehicle_t.vel_cmps_x");
    fieldList.append("vehicle_t.vel_cmps_y");
    fieldList.append("vehicle_t.vel_cmps_z");

//GNSS_t
    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        fieldList.append(QString("GNSS_t%1.index").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.fix_type").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.num_sats").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.lat").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.lon").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.alt_m").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.hdop_cm").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.vdop_cm").arg(QString::number(i)));
        fieldList.append(QString("GNSS_t%1.speed_accuracy_cmps").arg(QString::number(i)));
    }

    fieldList.append("GNSS_count");

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        fieldList.append(QString("tIMU%1.index").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.acc_mpss[0]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.acc_mpss[1]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.acc_mpss[2]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.gyro_dps[0]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.gyro_dps[1]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.gyro_dps[2]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.vibrations[0]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.vibrations[1]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.vibrations[2]").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.temperture").arg(QString::number(i)));
        fieldList.append(QString("tIMU%1.clips").arg(QString::number(i)));
    }

    fieldList.append("IMU_count");

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        fieldList.append(QString("tCompass%1.index").arg(QString::number(i)));
        fieldList.append(QString("tCompass%1.mag_mG[0]").arg(QString::number(i)));
        fieldList.append(QString("tCompass%1.mag_mG[1]").arg(QString::number(i)));
        fieldList.append(QString("tCompass%1.mag_mG[2]").arg(QString::number(i)));
    }
    fieldList.append("Compass_count");

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        fieldList.append(QString("tBaro%1.index").arg(QString::number(i)));
        fieldList.append(QString("tBaro%1.Press_Pa").arg(QString::number(i)));
        fieldList.append(QString("tBaro%1.temperture").arg(QString::number(i)));
        fieldList.append(QString("tBaro%1.air_density_ratio").arg(QString::number(i)));
    }

    fieldList.append("Baro_count");

    for(int i =0;i < 16; i++){
        fieldList.append(QString("tRC_OUT.rc[%1]").arg(QString::number(i)));
        fieldList.append(QString("tRC_OUT.out[%1]").arg(QString::number(i)));
    }

    fieldList.append("tTarget.MissionID");
    fieldList.append("tTarget.TargetLat");
    fieldList.append("tTarget.TargetLng");
    fieldList.append("tTarget.TargetASL_m");
    fieldList.append("tTarget.TargetAlt_m");
    fieldList.append("tTarget.DesiredAlt_m");
    fieldList.append("tTarget.TargetVel_e_cmps");
    fieldList.append("tTarget.TargetVel_n_cmps");
    fieldList.append("tTarget.TargetVel_u_cmps");
    fieldList.append("tTarget.NavRoll_cd");
    fieldList.append("tTarget.NavPitch_cd");
    fieldList.append("tTarget.NavYaw_cd");
    fieldList.append("tTarget.TargetAcc_mpss[0]");
    fieldList.append("tTarget.TargetAcc_mpss[1]");
    fieldList.append("tTarget.TargetAcc_mpss[2]");
    fieldList.append("tTarget.TargetGyro_dps[0]");
    fieldList.append("tTarget.TargetGyro_dps[1]");
    fieldList.append("tTarget.TargetGyro_dps[2]");


    fieldList.append("tHome.latitude");
    fieldList.append("tHome.longitude");
    fieldList.append("tHome.alt_m");
    fieldList.append("tHome.isGet");

    fieldList.append("tOrigin.latitude");
    fieldList.append("tOrigin.longitude");
    fieldList.append("tOrigin.alt_m");
    fieldList.append("tOrigin.isGet");

    fieldList.append("Acc3DCaliPostion");

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        fieldList.append(QString("MagCaliProgress%1.id").arg(QString::number(i)));
        fieldList.append(QString("MagCaliProgress%1.cal_status").arg(QString::number(i)));
        fieldList.append(QString("MagCaliProgress%1.attempt").arg(QString::number(i)));
        fieldList.append(QString("MagCaliProgress%1.completion_pct").arg(QString::number(i)));
        fieldList.append(QString("MagCaliProgress%1._fitness").arg(QString::number(i)));
    }

    fieldList.append("MagCaliCount");
    fieldList.append("FrameMotorCount");
    fieldList.append("BoardOrientation");


    fieldList.append("extVol[0]");
    fieldList.append("extVol.[1]");

    fieldList.append("RPM[0]");
    fieldList.append("RPM[1]");

    return fieldList;
}

QMap<QString, QString> LoggerManagement::getDataForLinkID(int linkID)
{
    QMap<QString,QString> map = {};
    QList<int >linkList = Qt::DMMM()->getLinksID();
    if(linkList.indexOf(linkID) == -1){
        return map;
    }

    Q_DMMM::DataPool_t linkData = Qt::DMMM()->getData(linkID);

    map.insert("time",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));

    map.insert("mav_version",QString::number(linkData.flylink.mav_version));

    //SysInfo_t结构体数据
    map.insert("SysInfo_t.frame",QString::number(linkData.flylink.tSysInfo.frame));
    map.insert("SysInfo_t.flight_mode",QString::number(linkData.flylink.tSysInfo.flight_mode));
    //        map.insert("SysInfo_t.state1",QString::number(linkData.flylink.tSysInfo.state1));
    map.insert("SysInfo_t.CPULoad",QString::number(linkData.flylink.tSysInfo.CPULoad));
    map.insert("SysInfo_t.time_sinceboot_s",QString::number(linkData.flylink.tSysInfo.time_sinceboot_s));
    map.insert("SysInfo_t.flight_time_s",QString::number(linkData.flylink.tSysInfo.flight_time_s));
    map.insert("SysInfo_t.total_flight_time_s",QString::number(linkData.flylink.tSysInfo.total_flight_time_s));
    map.insert("SysInfo_t.flight_dis_m",QString::number(linkData.flylink.tSysInfo.flight_dis_m));
    map.insert("SysInfo_t.total_flight_dis_m",QString::number(linkData.flylink.tSysInfo.total_flight_dis_m));
    map.insert("SysInfo_t.boot_cnt",QString::number(linkData.flylink.tSysInfo.boot_cnt));
    map.insert("SysInfo_t.Battery_voltage_mv",QString::number(linkData.flylink.tSysInfo.Battery_voltage_mv));
    map.insert("SysInfo_t.Battery_Current_CA",QString::number(linkData.flylink.tSysInfo.Battery_Current_CA));
    map.insert("SysInfo_t.throttle",QString::number(linkData.flylink.tSysInfo.throttle));
    map.insert("SysInfo_t.temperture",QString::number(linkData.flylink.tSysInfo.temperture));
    //        map.insert("SysInfo_t.sensor_state",QString::number(linkData.flylink.tSysInfo.sensor_state));
    map.insert("SysInfo_t.home_dist_m",QString::number(linkData.flylink.tSysInfo.home_dist_m));
    map.insert("SysInfo_t.home_bearing_cd",QString::number(linkData.flylink.tSysInfo.home_bearing_cd));
    map.insert("SysInfo_t.wp_dist_m",QString::number(linkData.flylink.tSysInfo.wp_dist_m));
    map.insert("SysInfo_t.alt_error",QString::number(linkData.flylink.tSysInfo.alt_error));
    map.insert("SysInfo_t.xtrack_error",QString::number(linkData.flylink.tSysInfo.xtrack_error));

    //vehicle_t.
    map.insert("vehicle_t.roll_cd",QString::number(linkData.flylink.tVehicle.roll_cd));
    map.insert("vehicle_t.pitch_cd",QString::number(linkData.flylink.tVehicle.pitch_cd));
    map.insert("vehicle_t.yaw_cd",QString::number(linkData.flylink.tVehicle.yaw_cd));

    map.insert("vehicle_t.acc_mpss_x",QString::number(linkData.flylink.tVehicle.acc_mpss[0]));
    map.insert("vehicle_t.acc_mpss_y",QString::number(linkData.flylink.tVehicle.acc_mpss[1]));
    map.insert("vehicle_t.acc_mpss_z",QString::number(linkData.flylink.tVehicle.acc_mpss[2]));
    map.insert("vehicle_t.gyro_dps_x",QString::number(linkData.flylink.tVehicle.gyro_dps[0]));
    map.insert("vehicle_t.gyro_dps_y",QString::number(linkData.flylink.tVehicle.gyro_dps[1]));
    map.insert("vehicle_t.gyro_dps_z",QString::number(linkData.flylink.tVehicle.gyro_dps[2]));
    map.insert("vehicle_t.lat",QString::number(linkData.flylink.tVehicle.lat));
    map.insert("vehicle_t.lng",QString::number(linkData.flylink.tVehicle.lng));
    map.insert("vehicle_t.alt_m",QString::number(linkData.flylink.tVehicle.alt_m));
    map.insert("vehicle_t.pos_m_x",QString::number(linkData.flylink.tVehicle.pos_m[0]));
    map.insert("vehicle_t.pos_m_y",QString::number(linkData.flylink.tVehicle.pos_m[1]));
    map.insert("vehicle_t.pos_m_z",QString::number(linkData.flylink.tVehicle.pos_m[2]));
    map.insert("vehicle_t.vel_cmps_x",QString::number(linkData.flylink.tVehicle.vel_cmps[0]));
    map.insert("vehicle_t.vel_cmps_y",QString::number(linkData.flylink.tVehicle.vel_cmps[1]));
    map.insert("vehicle_t.vel_cmps_z",QString::number(linkData.flylink.tVehicle.vel_cmps[2]));

    //GNSS_t
    for(int i = 0; i < FlyLink_MAX_SensorBackend;i++){
        map.insert(QString("GNSS_t%1.index").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].index));
        map.insert(QString("GNSS_t%1.fix_type").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].fix_type));
        map.insert(QString("GNSS_t%1.num_sats").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].num_sats));
        map.insert(QString("GNSS_t%1.lat").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].lat));
        map.insert(QString("GNSS_t%1.lon").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].lon));
        map.insert(QString("GNSS_t%1.alt_m").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].alt_m));
        map.insert(QString("GNSS_t%1.hdop_cm").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].hdop_cm));
        map.insert(QString("GNSS_t%1.vdop_cm").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].vdop_cm));
        map.insert(QString("GNSS_t%1.speed_accuracy_cmps").arg(QString::number(i)),QString::number(linkData.flylink.tGNSS[i].speed_accuracy_cmps));
    }

    map.insert(QString("GNSS_count"),QString::number(linkData.flylink.GNSS_count));

    for(int i = 0; i < FlyLink_MAX_SensorBackend;i++){
        map.insert(QString("tIMU%1.index").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].index));
        map.insert(QString("tIMU%1.acc_mpss[0]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].acc_mpss[0]));
        map.insert(QString("tIMU%1.acc_mpss[1]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].acc_mpss[1]));
        map.insert(QString("tIMU%1.acc_mpss[2]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].acc_mpss[2]));
        map.insert(QString("tIMU%1.gyro_dps[0]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].gyro_dps[0]));
        map.insert(QString("tIMU%1.gyro_dps[1]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].gyro_dps[1]));
        map.insert(QString("tIMU%1.gyro_dps[2]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].gyro_dps[2]));
        map.insert(QString("tIMU%1.vibrations[0]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].vibrations[0]));
        map.insert(QString("tIMU%1.vibrations[1]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].vibrations[1]));
        map.insert(QString("tIMU%1.vibrations[2]").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].vibrations[2]));
        map.insert(QString("tIMU%1.temperture").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].temperture));
        map.insert(QString("tIMU%1.clips").arg(QString::number(i)),QString::number(linkData.flylink.tIMU[i].clips));
    }
    map.insert(QString("IMU_count"),QString::number(linkData.flylink.IMU_count));

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        map.insert(QString("tCompass%1.index").arg(QString::number(i)),QString::number(linkData.flylink.tCompass->index));
        map.insert(QString("tCompass%1.mag_mG[0]").arg(QString::number(i)),QString::number(linkData.flylink.tCompass->mag_mG[0]));
        map.insert(QString("tCompass%1.mag_mG[1]").arg(QString::number(i)),QString::number(linkData.flylink.tCompass->mag_mG[1]));
        map.insert(QString("tCompass%1.mag_mG[2]").arg(QString::number(i)),QString::number(linkData.flylink.tCompass->mag_mG[2]));
    }

    map.insert(QString("Compass_count"),QString::number(linkData.flylink.Compass_count));

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        map.insert(QString("tBaro%1.index").arg(QString::number(i)),QString::number(linkData.flylink.tBaro[i].index));
        map.insert(QString("tBaro%1.Press_Pa").arg(QString::number(i)),QString::number(linkData.flylink.tBaro[i].Press_Pa));
        map.insert(QString("tBaro%1.temperture").arg(QString::number(i)),QString::number(linkData.flylink.tBaro[i].temperture));
        map.insert(QString("tBaro%1.air_density_ratio").arg(QString::number(i)),QString::number(linkData.flylink.tBaro[i].air_density_ratio));
    }

    map.insert(QString("Baro_count"),QString::number(linkData.flylink.Baro_count));

    for(int i =0;i < 16; i++){
        map.insert(QString("tRC_OUT.rc[%1]").arg(QString::number(i)),QString::number(linkData.flylink.tRC_OUT.rc[i]));
        map.insert(QString("tRC_OUT.out[%1]").arg(QString::number(i)),QString::number(linkData.flylink.tRC_OUT.out[i]));
    }

    map.insert(QString("tTarget.MissionID"),QString::number(linkData.flylink.tTarget.MissionID));
    map.insert(QString("tTarget.TargetLat"),QString::number(linkData.flylink.tTarget.TargetLat));
    map.insert(QString("tTarget.TargetLng"),QString::number(linkData.flylink.tTarget.TargetLng));
    map.insert(QString("tTarget.TargetASL_m"),QString::number(linkData.flylink.tTarget.TargetASL_m));
    map.insert(QString("tTarget.TargetAlt_m"),QString::number(linkData.flylink.tTarget.TargetAlt_m));
    map.insert(QString("tTarget.DesiredAlt_m"),QString::number(linkData.flylink.tTarget.DesiredAlt_m));
    map.insert(QString("tTarget.TargetVel_e_cmps"),QString::number(linkData.flylink.tTarget.TargetVel_e_cmps));
    map.insert(QString("tTarget.TargetVel_n_cmps"),QString::number(linkData.flylink.tTarget.TargetVel_n_cmps));
    map.insert(QString("tTarget.TargetVel_u_cmps"),QString::number(linkData.flylink.tTarget.TargetVel_u_cmps));
    map.insert(QString("tTarget.NavRoll_cd"),QString::number(linkData.flylink.tTarget.NavRoll_cd));
    map.insert(QString("tTarget.NavPitch_cd"),QString::number(linkData.flylink.tTarget.NavPitch_cd));
    map.insert(QString("tTarget.NavYaw_cd"),QString::number(linkData.flylink.tTarget.NavYaw_cd));
    map.insert(QString("tTarget.TargetAcc_mpss[0]"),QString::number(linkData.flylink.tTarget.TargetAcc_mpss[0]));
    map.insert(QString("tTarget.TargetAcc_mpss[1]"),QString::number(linkData.flylink.tTarget.TargetAcc_mpss[1]));
    map.insert(QString("tTarget.TargetAcc_mpss[2]"),QString::number(linkData.flylink.tTarget.TargetAcc_mpss[2]));
    map.insert(QString("tTarget.TargetGyro_dps[0]"),QString::number(linkData.flylink.tTarget.TargetGyro_dps[0]));
    map.insert(QString("tTarget.TargetGyro_dps[1]"),QString::number(linkData.flylink.tTarget.TargetGyro_dps[1]));
    map.insert(QString("tTarget.TargetGyro_dps[2]"),QString::number(linkData.flylink.tTarget.TargetGyro_dps[2]));


    map.insert("tHome.latitude",QString::number(linkData.flylink.tHome.loc.latitude));
    map.insert("tHome.longitude",QString::number(linkData.flylink.tHome.loc.longitude));
    map.insert("tHome.alt_m",QString::number(linkData.flylink.tHome.loc.alt_m));
    map.insert("tHome.isGet",(linkData.flylink.tHome.is_get) ? "true":"false");

    map.insert("tOrigin.latitude",QString::number(linkData.flylink.tOrigin.loc.latitude));
    map.insert("tOrigin.longitude",QString::number(linkData.flylink.tOrigin.loc.longitude));
    map.insert("tOrigin.alt_m",QString::number(linkData.flylink.tOrigin.loc.alt_m));
    map.insert("tOrigin.isGet",(linkData.flylink.tOrigin.is_get) ? "true":"false");

    map.insert(QString("Acc3DCaliPostion"),QString::number(linkData.flylink.Acc3DCaliPostion));

    for(int i = 1; i <= FlyLink_MAX_SensorBackend;i++){
        map.insert(QString("MagCaliProgress%1.id").arg(QString::number(i)),QString::number(linkData.flylink.MagCaliProgress[i].id));
        map.insert(QString("MagCaliProgress%1.cal_status").arg(QString::number(i)),QString::number(linkData.flylink.MagCaliProgress[i].cal_status));
        map.insert(QString("MagCaliProgress%1.attempt").arg(QString::number(i)),QString::number(linkData.flylink.MagCaliProgress[i].attempt));
        map.insert(QString("MagCaliProgress%1.completion_pct").arg(QString::number(i)),QString::number(linkData.flylink.MagCaliProgress[i].completion_pct));
        map.insert(QString("MagCaliProgress%1._fitness").arg(QString::number(i)),QString::number(linkData.flylink.MagCaliProgress[i]._fitness));
    }

    map.insert(QString("MagCaliCount"),QString::number(linkData.flylink.MagCaliCount));
    map.insert(QString("FrameMotorCount"),QString::number(linkData.flylink.FrameMotorCount));
    map.insert(QString("BoardOrientation"),QString::number(linkData.flylink.BoardOrientation));


    map.insert("extVol[0]",QString::number(linkData.flylink.extVol.val[0]));
    map.insert("extVol.[1]",QString::number(linkData.flylink.extVol.val[1]));

    map.insert("RPM[0]",QString::number(linkData.flylink.RPM.val[0]));
    map.insert("RPM[1]",QString::number(linkData.flylink.RPM.val[1]));


    return map;
}

void LoggerManagement::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&LoggerManagement::handle_DMMM_event);
}


void LoggerManagement::timeroutSlot()
{

    QList<int> linkList = Log::getTextLoggerPtr()->getTextLoggerLinkList();

    for(int i = 0; i < linkList.count(); i++){
        QMap<QString, QString>  map = this->getDataForLinkID(linkList.at(i));
        Log::getTextLoggerPtr()->textLogWriteSlot(linkList.at(i),"data",map);
    }
}



void LoggerManagement::handle_DMMM_event(int ev, int linkid)
{

//    Q_UNUSED(linkid);
    switch(ev){

        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        qDebug()<<"DMMM_GCSEvent_Protocol_Actived";
        Log::getTextLoggerPtr()->textLogBeginSlot(linkid,"data",this->dataLogFieldList);
        Log::getLogReplayPtr()->logReplayBeginSlot(linkid);
        break;
        case Q_DMMM::DMMM_GCSEvent_Protocol_lost:{
        qDebug()<<"DMMM_GCSEvent_Protocol_lost";
        Log::getTextLoggerPtr()->textLogFinishSlot(linkid,"data");
        Log::getLogReplayPtr()->logReplayFinishSlot(linkid);
        }break;
    }
}



void Log::Log_Cmd(QString text) {
        LoggerManagement::getLogger()->Log_Cmd(text);
}

void Log::Log_Warn(QString text){
        LoggerManagement::getLogger()->Log_Worning(text);

}

void Log::Log_Error(QString text){
        LoggerManagement::getLogger()->Log_Error(text);
}

void Log::Log_Info(QString text)   {
        LoggerManagement::getLogger()->Log_Info(text);
}



XlsxLogger *Log::getXlsxLoggerPtr()
{
    return LoggerManagement::getXlsxLogger();
}

SystemLogger *Log::getSystemLoggerPtr()
{
    return LoggerManagement::getLogger();
}

QString Log::Log_ByteToString(QByteArray array)
{
    return LoggerManagement::getLogger()->Log_ByteToString(array);
}

TextLogger *Log::getTextLoggerPtr()
{
    return LoggerManagement::getTextLogger();
}

LogReplay *Log::getLogReplayPtr()
{
    return LoggerManagement::getReplay();
}
