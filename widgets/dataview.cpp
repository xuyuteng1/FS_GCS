#include "dataview.h"
#include <QDebug>
#include <QDesktopWidget>
#include "DMMM.h"
#include <QSpacerItem>
DataView::DataView(QWidget *parent)
    :QWidget(parent)
{
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    widgetInit();
    this->setAttribute(Qt::WA_StyledBackground,true);
    QFile file(QString(":/style/systemDataView.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
    this->setWindowOpacity(0.95);
    this->resize(1000,600);
    this->move((QApplication::desktop()->width() - this->width())/2,0);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
}

void DataView::update_display()
{
    update_data();
    if(!this->isVisible()){
        return;
    }

    update_sysinfo();
    update_vehicle();
    update_rc_out();
//    update_target();
    update_esc();

    update_GNSS();
    update_IMU();
    update_Compass();
    update_Baro();
//    update_wp();
    // 放在最后用于更新
    last_data = data;
}

void DataView::update_sysinfo()
{
    MAP_sysinfo.find(sys_info_frame).value()->setValueLabelText(FlyLink::getCopterFrame(data.flylink.tSysInfo.frame));
    MAP_sysinfo.find(sys_info_flight_mode).value()->setValueLabelText(FlyLink::getFlightMode(data.flylink.VehicleType,data.flylink.tSysInfo.flight_mode));
    MAP_sysinfo.find(sys_info_armed).value()->setValueLabelText(data.flylink.tSysInfo.state1.state.armed?QStringLiteral("解锁"):QStringLiteral("锁定"));
    MAP_sysinfo.find(sys_info_isflying).value()->setValueLabelText(data.flylink.tSysInfo.state1.state.isflying?QStringLiteral("飞行中"):QStringLiteral("地面"));
    MAP_sysinfo.find(sys_info_CPULoad).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.CPULoad)+"%");
    MAP_sysinfo.find(sys_info_time_sinceboot_ms).value()->setValueLabelText(QString::asprintf("%02d:%02d:%02d",data.flylink.tSysInfo.time_sinceboot_s/3600,data.flylink.tSysInfo.time_sinceboot_s%3600/60,data.flylink.tSysInfo.time_sinceboot_s%60));
    MAP_sysinfo.find(sys_info_flight_time_s).value()->setValueLabelText(QString::asprintf("%02d:%02d:%02d",data.flylink.tSysInfo.flight_time_s/3600,data.flylink.tSysInfo.flight_time_s%3600/60,data.flylink.tSysInfo.flight_time_s%60));
    MAP_sysinfo.find(sys_info_total_flight_time_s).value()->setValueLabelText(QString::asprintf("%02d:%02d:%02d",data.flylink.tSysInfo.total_flight_time_s/3600,data.flylink.tSysInfo.total_flight_time_s%3600/60,data.flylink.tSysInfo.total_flight_time_s%60));
    MAP_sysinfo.find(sys_info_flight_dis_m).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.flight_dis_m));
    MAP_sysinfo.find(sys_info_total_flight_dis_m).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.total_flight_dis_m));
    MAP_sysinfo.find(sys_info_boot_cnt).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.boot_cnt));
    MAP_sysinfo.find(sys_info_Battery_voltage_mv).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.Battery_voltage_mv*0.001f,'f',3));// mV
    MAP_sysinfo.find(sys_info_Battery_Current_CA).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.Battery_Current_CA*0.01f,'f',2));// A*100
    MAP_sysinfo.find(sys_info_throttle).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.throttle)+"%");
    MAP_sysinfo.find(sys_info_temperture).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.temperture*0.01f,'f',2));     // ℃*100
    MAP_sysinfo.find(sys_info_arm_check).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.arm_check?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_acc).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.acc?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_gyro).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.gyro?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_mag).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.mag?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_baro).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.baro?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_airspeed).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.airspeed?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_GNSS).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.GNSS?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_INS).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.INS?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_AHRS).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.AHRS?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_RC).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.RC?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_datalink).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.datalink?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_motor).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.motor?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_datalog).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.datalog?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_power).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.power?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_vibration).value()->setValueLabelText(data.flylink.tSysInfo.sensor_state.state.vibration?QStringLiteral("正常"):QStringLiteral("异常"));
    MAP_sysinfo.find(sys_info_home_dist_m).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.home_dist_m,'f',2));
    MAP_sysinfo.find(sys_info_home_bearing_cd).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.home_bearing_cd*0.01f,'f',2));
    MAP_sysinfo.find(sys_info_wp_dist_m).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.wp_dist_m,'f',2));
    MAP_sysinfo.find(sys_info_alt_error).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.alt_error,'f',2));
    MAP_sysinfo.find(sys_info_xtrack_error).value()->setValueLabelText(QString::number(data.flylink.tSysInfo.xtrack_error,'f',2));
}

void DataView::update_vehicle()
{
    MAP_vehicle.find(vehicle_roll_cd).value()->setValueLabelText(QString::number(data.flylink.tVehicle.roll_cd*0.01f,'f',2));
    MAP_vehicle.find(vehicle_pitch_cd).value()->setValueLabelText(QString::number(data.flylink.tVehicle.pitch_cd*0.01f,'f',2));
    MAP_vehicle.find(vehicle_yaw_cd).value()->setValueLabelText(QString::number(data.flylink.tVehicle.yaw_cd*0.01f,'f',2)); //0~36000
    MAP_vehicle.find(vehicle_acc_mpss_x).value()->setValueLabelText(QString::number(data.flylink.tVehicle.acc_mpss[0],'f',2));
    MAP_vehicle.find(vehicle_acc_mpss_y).value()->setValueLabelText(QString::number(data.flylink.tVehicle.acc_mpss[1],'f',2));
    MAP_vehicle.find(vehicle_acc_mpss_z).value()->setValueLabelText(QString::number(data.flylink.tVehicle.acc_mpss[2],'f',2));
    MAP_vehicle.find(vehicle_gyro_dps_x).value()->setValueLabelText(QString::number(data.flylink.tVehicle.gyro_dps[0],'f',2));
    MAP_vehicle.find(vehicle_gyro_dps_y).value()->setValueLabelText(QString::number(data.flylink.tVehicle.gyro_dps[1],'f',2));
    MAP_vehicle.find(vehicle_gyro_dps_z).value()->setValueLabelText(QString::number(data.flylink.tVehicle.gyro_dps[2],'f',2));
    MAP_vehicle.find(vehicle_lat).value()->setValueLabelText(QString::number((double)data.flylink.tVehicle.lat*1e-7,'f',7));
    MAP_vehicle.find(vehicle_lng).value()->setValueLabelText(QString::number((double)data.flylink.tVehicle.lng*1e-7,'f',7));
    MAP_vehicle.find(vehicle_alt_m).value()->setValueLabelText(QString::number(data.flylink.tVehicle.alt_m,'f',2));
    MAP_vehicle.find(vehicle_pos_m_x).value()->setValueLabelText(QString::number(data.flylink.tVehicle.pos_m[0],'f',2));
    MAP_vehicle.find(vehicle_pos_m_y).value()->setValueLabelText(QString::number(data.flylink.tVehicle.pos_m[1],'f',2));
    MAP_vehicle.find(vehicle_pos_m_z).value()->setValueLabelText(QString::number(data.flylink.tVehicle.pos_m[2],'f',2));    // ENU
    MAP_vehicle.find(vehicle_vel_cmps_x).value()->setValueLabelText(QString::number(data.flylink.tVehicle.vel_cmps[0]*0.01f,'f',2)); // ENU
    MAP_vehicle.find(vehicle_vel_cmps_y).value()->setValueLabelText(QString::number(data.flylink.tVehicle.vel_cmps[1]*0.01f,'f',2)); // ENU
    MAP_vehicle.find(vehicle_vel_cmps_z).value()->setValueLabelText(QString::number(data.flylink.tVehicle.vel_cmps[2]*0.01f,'f',2)); // ENU
    MAP_vehicle.find(vehicle_airSpeed).value()->setValueLabelText(QString::number(data.flylink.tVehicle.airSpeed,'f',2)); // ENU
    MAP_vehicle.find(vehicle_wind_dir).value()->setValueLabelText(QString::number(data.flylink.tVehicle.wind_dir)); // ENU
    MAP_vehicle.find(vehicle_wind_spd).value()->setValueLabelText(QString::number(data.flylink.tVehicle.wind_spd*0.01f,'f',2)); // ENU
    MAP_vehicle.find(vehicle_wind_spd_z).value()->setValueLabelText(QString::number(data.flylink.tVehicle.wind_spd_z*0.01f,'f',2)); // ENU







}

void DataView::update_esc()
{

//    if(last_data.flylink.ESC_count != data.flylink.ESC_count ||
//        last_data.flylink.ESC_count == 0
//        ){
//        if(data.flylink.ESC_count == 0){
//            this->escInfoWidget->setVisible(false);
//        }
//        else{
//            this->escInfoWidget->setVisible(true);
//            int start_disVisible = data.flylink.ESC_count*MAP_ESC.count()/8;
//            QMap<int,QString>::Iterator ite = MAP_ESCStr.begin();
//            int cnt = 0;
//            while(ite != MAP_ESCStr.end()){
//                if(cnt>=start_disVisible){
//                    MAP_ESC.find(ite.key()).value()->setVisible(false);
//                }
//                else{
//                    MAP_ESC.find(ite.key()).value()->setVisible(true);
//                }
//                ite++;
//                cnt++;
//            }
//        }
//    }
    for (int var = 1; var <= 8; ++var) {
        MAP_ESC.find((var-1)*4+0).value()->setValueLabelText(QString::number(data.flylink.tESC[var-1].volt));
        MAP_ESC.find((var-1)*4+1).value()->setValueLabelText(QString::number(data.flylink.tESC[var-1].current));
        MAP_ESC.find((var-1)*4+2).value()->setValueLabelText(QString::number(data.flylink.tESC[var-1].rpm));
        MAP_ESC.find((var-1)*4+3).value()->setValueLabelText(QString::number(data.flylink.tESC[var-1].temperature));
    }
}

void DataView::update_GNSS()
{
    if(last_data.flylink.GNSS_count != data.flylink.GNSS_count ||
            last_data.flylink.GNSS_count == 0
    ){
        if(data.flylink.GNSS_count == 0){
            this->satelliteInfoWidget->setVisible(false);
        }
        else{
            this->satelliteInfoWidget->setVisible(true);
            int start_disVisible = data.flylink.GNSS_count*MAP_GNSS.count()/3;
            QMap<int,QString>::Iterator ite = MAP_GNSSStr.begin();
            int cnt = 0;
            while(ite != MAP_GNSSStr.end()){
                if(cnt>=start_disVisible){
                    MAP_GNSS.find(ite.key()).value()->setVisible(false);
                }
                else{
                    MAP_GNSS.find(ite.key()).value()->setVisible(true);
                }
                ite++;
                cnt++;
            }
        }
    }
    // 更新显示
    MAP_GNSS.find(gnss1_fix_type).value()->setValueLabelText(FlyLink::getGNSSFixType(data.flylink.tGNSS[0].fix_type)); /*<  GPS fix type.*/
    MAP_GNSS.find(gnss1_num_sats).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].num_sats)); /*<  Number of satellites visible. If unknown, set to 255*/
    MAP_GNSS.find(gnss1_lat).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].lat*1e-7,'f',7)); /*< [degE7] Latitude (WGS84).value()->setValueLabelText(FlyLink::getCopterFrame(data.flylink.tSysInfo.frame)); EGM96 ellipsoid)*/
    MAP_GNSS.find(gnss1_lon).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].lon*1e-7,'f',7)); /*< [degE7] Longitude (WGS84).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].num_sats)); EGM96 ellipsoid)*/
    MAP_GNSS.find(gnss1_alt_m).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].alt_m,'f',2));
    MAP_GNSS.find(gnss1_hdop_cm).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].hdop_cm*0.01f,'f',2));               ///< 3D velocity RMS accuracy estimate in cm/s
    MAP_GNSS.find(gnss1_vdop_cm).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].vdop_cm*0.01f,'f',2));          ///< horizontal RMS accuracy estimate in cm
    MAP_GNSS.find(gnss1_yaw).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].yaw,'f',2));
    MAP_GNSS.find(gnss1_yaw_accuracy).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].yaw_accuracy,'f',2));
    MAP_GNSS.find(gnss1_yaw_lagged_timestamp).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].yaw_lagged_timestamp));
    MAP_GNSS.find(gnss1_speed_accuracy_cmps).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].speed_accuracy_cmps*0.01f,'f',2));

    MAP_GNSS.find(gnss2_fix_type).value()->setValueLabelText(FlyLink::getGNSSFixType(data.flylink.tGNSS[1].fix_type)); /*<  GPS fix type.*/
    MAP_GNSS.find(gnss2_num_sats).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].num_sats)); /*<  Number of satellites visible. If unknown, set to 255*/
    MAP_GNSS.find(gnss2_lat).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].lat*1e-7,'f',7)); /*< [degE7] Latitude (WGS84).value()->setValueLabelText(FlyLink::getCopterFrame(data.flylink.tSysInfo.frame)); EGM96 ellipsoid)*/
    MAP_GNSS.find(gnss2_lon).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].lon*1e-7,'f',7)); /*< [degE7] Longitude (WGS84).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].num_sats)); EGM96 ellipsoid)*/
    MAP_GNSS.find(gnss2_alt_m).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].alt_m,'f',2));
    MAP_GNSS.find(gnss2_hdop_cm).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].hdop_cm*0.01f,'f',2));               ///< 3D velocity RMS accuracy estimate in cm/s
    MAP_GNSS.find(gnss2_vdop_cm).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].vdop_cm*0.01f,'f',2));          ///< horizontal RMS accuracy estimate in cm
    MAP_GNSS.find(gnss2_yaw).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].yaw,'f',2));
    MAP_GNSS.find(gnss2_yaw_accuracy).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].yaw_accuracy,'f',2));
    MAP_GNSS.find(gnss2_yaw_lagged_timestamp).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].yaw_lagged_timestamp));
    MAP_GNSS.find(gnss2_speed_accuracy_cmps).value()->setValueLabelText(QString::number(data.flylink.tGNSS[1].speed_accuracy_cmps*0.01f,'f',2));

    MAP_GNSS.find(gnss3_fix_type).value()->setValueLabelText(FlyLink::getGNSSFixType(data.flylink.tGNSS[2].fix_type)); /*<  GPS fix type.*/
    MAP_GNSS.find(gnss3_num_sats).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].num_sats)); /*<  Number of satellites visible. If unknown, set to 255*/
    MAP_GNSS.find(gnss3_lat).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].lat*1e-7,'f',7)); /*< [degE7] Latitude (WGS84).value()->setValueLabelText(FlyLink::getCopterFrame(data.flylink.tSysInfo.frame)); EGM96 ellipsoid)*/
    MAP_GNSS.find(gnss3_lon).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].lon*1e-7,'f',7)); /*< [degE7] Longitude (WGS84).value()->setValueLabelText(QString::number(data.flylink.tGNSS[0].num_sats)); EGM96 ellipsoid)*/
    MAP_GNSS.find(gnss3_alt_m).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].alt_m,'f',2));
    MAP_GNSS.find(gnss3_hdop_cm).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].hdop_cm*0.01f,'f',2));               ///< 3D velocity RMS accuracy estimate in cm/s
    MAP_GNSS.find(gnss3_vdop_cm).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].vdop_cm*0.01f,'f',2));          ///< horizontal RMS accuracy estimate in cm
    MAP_GNSS.find(gnss3_yaw).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].yaw,'f',2));
    MAP_GNSS.find(gnss3_yaw_accuracy).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].yaw_accuracy,'f',2));
    MAP_GNSS.find(gnss3_yaw_lagged_timestamp).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].yaw_lagged_timestamp));
    MAP_GNSS.find(gnss3_speed_accuracy_cmps).value()->setValueLabelText(QString::number(data.flylink.tGNSS[2].speed_accuracy_cmps*0.01f,'f',2));


}

void DataView::update_IMU()
{
    if(last_data.flylink.IMU_count != data.flylink.IMU_count ||
            last_data.flylink.IMU_count == 0
    ){
        if(data.flylink.IMU_count == 0){
            this->IMUStatusWidget->setVisible(false);
        }
        else{
            this->IMUStatusWidget->setVisible(true);
            int start_disVisible = data.flylink.IMU_count*MAP_IMU.count()/3;
            QMap<int,QString>::Iterator ite = MAP_IMUStr.begin();
            int cnt = 0;
            while(ite != MAP_IMUStr.end()){
                if(cnt>=start_disVisible){
                    MAP_IMU.find(ite.key()).value()->setVisible(false);
                }
                else{
                    MAP_IMU.find(ite.key()).value()->setVisible(true);
                }
                ite++;
                cnt++;
            }
        }
    }
    MAP_IMU.find(imu1_acc_mpss_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].acc_mpss[0],'f',2));
    MAP_IMU.find(imu1_acc_mpss_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].acc_mpss[1],'f',2));
    MAP_IMU.find(imu1_acc_mpss_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].acc_mpss[2],'f',2));
    MAP_IMU.find(imu1_gyro_dps_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].gyro_dps[0],'f',2));
    MAP_IMU.find(imu1_gyro_dps_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].gyro_dps[1],'f',2));
    MAP_IMU.find(imu1_gyro_dps_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].gyro_dps[2],'f',2));
    MAP_IMU.find(imu1_vibrations_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].vibrations[0]));
    MAP_IMU.find(imu1_vibrations_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].vibrations[1]));
    MAP_IMU.find(imu1_vibrations_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].vibrations[2]));
    MAP_IMU.find(imu1_temperture).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].temperture*0.01f,'f',2));     // ℃*100
    MAP_IMU.find(imu1_clips).value()->setValueLabelText(QString::number(data.flylink.tIMU[0].clips));
    MAP_IMU.find(imu2_acc_mpss_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].acc_mpss[0],'f',2));
    MAP_IMU.find(imu2_acc_mpss_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].acc_mpss[1],'f',2));
    MAP_IMU.find(imu2_acc_mpss_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].acc_mpss[2],'f',2));
    MAP_IMU.find(imu2_gyro_dps_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].gyro_dps[0],'f',2));
    MAP_IMU.find(imu2_gyro_dps_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].gyro_dps[1],'f',2));
    MAP_IMU.find(imu2_gyro_dps_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].gyro_dps[2],'f',2));
    MAP_IMU.find(imu2_vibrations_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].vibrations[0]));
    MAP_IMU.find(imu2_vibrations_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].vibrations[1]));
    MAP_IMU.find(imu2_vibrations_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].vibrations[2]));
    MAP_IMU.find(imu2_temperture).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].temperture*0.01f,'f',2));     // ℃*100
    MAP_IMU.find(imu2_clips).value()->setValueLabelText(QString::number(data.flylink.tIMU[1].clips));
    MAP_IMU.find(imu3_acc_mpss_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].acc_mpss[0],'f',2));
    MAP_IMU.find(imu3_acc_mpss_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].acc_mpss[1],'f',2));
    MAP_IMU.find(imu3_acc_mpss_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].acc_mpss[2],'f',2));
    MAP_IMU.find(imu3_gyro_dps_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].gyro_dps[0],'f',2));
    MAP_IMU.find(imu3_gyro_dps_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].gyro_dps[1],'f',2));
    MAP_IMU.find(imu3_gyro_dps_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].gyro_dps[2],'f',2));
    MAP_IMU.find(imu3_vibrations_x).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].vibrations[0]));
    MAP_IMU.find(imu3_vibrations_y).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].vibrations[1]));
    MAP_IMU.find(imu3_vibrations_z).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].vibrations[2]));
    MAP_IMU.find(imu3_temperture).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].temperture*0.01f,'f',2));     // ℃*100
    MAP_IMU.find(imu3_clips).value()->setValueLabelText(QString::number(data.flylink.tIMU[2].clips));



}

void DataView::update_Compass()
{
    if(last_data.flylink.Compass_count != data.flylink.Compass_count ||
            last_data.flylink.Compass_count == 0
    ){
        if(data.flylink.Compass_count == 0){
            this->magneticCompassStatusWidget->setVisible(false);
        }
        else{
            this->magneticCompassStatusWidget->setVisible(true);
            int start_disVisible = data.flylink.Compass_count*MAP_Compass.count()/3;
            QMap<int,QString>::Iterator ite = MAP_CompassStr.begin();
            int cnt = 0;
            while(ite != MAP_CompassStr.end()){
                if(cnt>=start_disVisible){
                    MAP_Compass.find(ite.key()).value()->setVisible(false);
                }
                else{
                    MAP_Compass.find(ite.key()).value()->setVisible(true);
                }
                ite++;
                cnt++;
            }
        }
    }
    MAP_Compass.find(mag1_mG_x).value()->setValueLabelText(QString::number(data.flylink.tCompass[0].mag_mG[0],'f',2));
    MAP_Compass.find(mag1_mG_y).value()->setValueLabelText(QString::number(data.flylink.tCompass[0].mag_mG[1],'f',2));
    MAP_Compass.find(mag1_mG_z).value()->setValueLabelText(QString::number(data.flylink.tCompass[0].mag_mG[2],'f',2));

    MAP_Compass.find(mag2_mG_x).value()->setValueLabelText(QString::number(data.flylink.tCompass[1].mag_mG[0],'f',2));
    MAP_Compass.find(mag2_mG_y).value()->setValueLabelText(QString::number(data.flylink.tCompass[1].mag_mG[1],'f',2));
    MAP_Compass.find(mag2_mG_z).value()->setValueLabelText(QString::number(data.flylink.tCompass[1].mag_mG[2],'f',2));

    MAP_Compass.find(mag3_mG_x).value()->setValueLabelText(QString::number(data.flylink.tCompass[2].mag_mG[0],'f',2));
    MAP_Compass.find(mag3_mG_y).value()->setValueLabelText(QString::number(data.flylink.tCompass[2].mag_mG[1],'f',2));
    MAP_Compass.find(mag3_mG_z).value()->setValueLabelText(QString::number(data.flylink.tCompass[2].mag_mG[2],'f',2));
}

void DataView::update_Baro()
{
    if(last_data.flylink.Baro_count != data.flylink.Baro_count ||
            last_data.flylink.Baro_count == 0
    ){
        if(data.flylink.Baro_count == 0){
            this->barometerStatusWidget->setVisible(false);
        }
        else{
            this->barometerStatusWidget->setVisible(true);
            int start_disVisible = data.flylink.Baro_count*MAP_Baro.count()/3;
            QMap<int,QString>::Iterator ite = MAP_BaroStr.begin();
            int cnt = 0;
            while(ite != MAP_BaroStr.end()){
                if(cnt>=start_disVisible){
                    MAP_Baro.find(ite.key()).value()->setVisible(false);
                }
                else{
                    MAP_Baro.find(ite.key()).value()->setVisible(true);
                }
                ite++;
                cnt++;
            }
        }
    }
    MAP_Baro.find(baro1_Press_Pa).value()->setValueLabelText(QString::number(data.flylink.tBaro[0].Press_Pa,'f',2));       // 单位：Pa
    MAP_Baro.find(baro1_temperture).value()->setValueLabelText(QString::number(data.flylink.tBaro[0].temperture*0.01f,'f',2));      // ℃*100
    MAP_Baro.find(baro1_air_density_ratio).value()->setValueLabelText(QString::number(data.flylink.tBaro[0].air_density_ratio)+"%");         // *100
    MAP_Baro.find(baro2_Press_Pa).value()->setValueLabelText(QString::number(data.flylink.tBaro[1].Press_Pa,'f',2));       // 单位：Pa
    MAP_Baro.find(baro2_temperture).value()->setValueLabelText(QString::number(data.flylink.tBaro[1].temperture*0.01f,'f',2));      // ℃*100
    MAP_Baro.find(baro2_air_density_ratio).value()->setValueLabelText(QString::number(data.flylink.tBaro[1].air_density_ratio)+"%");         // *100
    MAP_Baro.find(baro3_Press_Pa).value()->setValueLabelText(QString::number(data.flylink.tBaro[2].Press_Pa,'f',2));       // 单位：Pa
    MAP_Baro.find(baro3_temperture).value()->setValueLabelText(QString::number(data.flylink.tBaro[2].temperture*0.01f,'f',2));      // ℃*100
    MAP_Baro.find(baro3_air_density_ratio).value()->setValueLabelText(QString::number(data.flylink.tBaro[2].air_density_ratio)+"%");         // *100


}

void DataView::update_rc_out()
{
    MAP_RC_OUT.find(RC_OUT_rc1).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[0]));
    MAP_RC_OUT.find(RC_OUT_rc2).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[1]));
    MAP_RC_OUT.find(RC_OUT_rc3).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[2]));
    MAP_RC_OUT.find(RC_OUT_rc4).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[3]));
    MAP_RC_OUT.find(RC_OUT_rc5).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[4]));
    MAP_RC_OUT.find(RC_OUT_rc6).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[5]));
    MAP_RC_OUT.find(RC_OUT_rc7).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[6]));
    MAP_RC_OUT.find(RC_OUT_rc8).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[7]));
    MAP_RC_OUT.find(RC_OUT_rc9).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[8]));
    MAP_RC_OUT.find(RC_OUT_rc10).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[9]));
    MAP_RC_OUT.find(RC_OUT_rc11).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[10]));
    MAP_RC_OUT.find(RC_OUT_rc12).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[11]));
    MAP_RC_OUT.find(RC_OUT_rc13).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[12]));
    MAP_RC_OUT.find(RC_OUT_rc14).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[13]));
    MAP_RC_OUT.find(RC_OUT_rc15).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[14]));
    MAP_RC_OUT.find(RC_OUT_rc16).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.rc[15]));
    MAP_RC_OUT.find(RC_OUT_out1).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[0]));
    MAP_RC_OUT.find(RC_OUT_out2).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[1]));
    MAP_RC_OUT.find(RC_OUT_out3).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[2]));
    MAP_RC_OUT.find(RC_OUT_out4).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[3]));
    MAP_RC_OUT.find(RC_OUT_out5).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[4]));
    MAP_RC_OUT.find(RC_OUT_out6).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[5]));
    MAP_RC_OUT.find(RC_OUT_out7).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[6]));
    MAP_RC_OUT.find(RC_OUT_out8).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[7]));
    MAP_RC_OUT.find(RC_OUT_out9).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[8]));
    MAP_RC_OUT.find(RC_OUT_out10).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[9]));
    MAP_RC_OUT.find(RC_OUT_out11).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[10]));
    MAP_RC_OUT.find(RC_OUT_out12).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[11]));
    MAP_RC_OUT.find(RC_OUT_out13).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[12]));
    MAP_RC_OUT.find(RC_OUT_out14).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[13]));
    MAP_RC_OUT.find(RC_OUT_out15).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[14]));
    MAP_RC_OUT.find(RC_OUT_out16).value()->setValueLabelText(QString::number(data.flylink.tRC_OUT.out[15]));
}

void DataView::update_target()
{
    MAP_Target.find(tar_MissionID           ).value()->setValueLabelText(QString::number(data.flylink.tTarget.MissionID));
    MAP_Target.find(tar_TargetLat               ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetLat*1e-7,'f',7));
    MAP_Target.find(tar_TargetLng           ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetLng*1e-7,'f',7));
    MAP_Target.find(tar_TargetASL_m         ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetASL_m     ,'f',2));
    MAP_Target.find(tar_TargetAlt_m         ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetAlt_m     ,'f',2));
    MAP_Target.find(tar_DesiredAlt_m        ).value()->setValueLabelText(QString::number(data.flylink.tTarget.DesiredAlt_m    ,'f',2));
    MAP_Target.find(tar_TargetVel_e_cmps    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetVel_e_cmps*0.01f,'f',2));
    MAP_Target.find(tar_TargetVel_n_cmps    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetVel_n_cmps*0.01f,'f',2));
    MAP_Target.find(tar_TargetVel_u_cmps    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetVel_u_cmps*0.01f,'f',2));
    MAP_Target.find(tar_NavRoll_cd          ).value()->setValueLabelText(QString::number(data.flylink.tTarget.NavRoll_cd      *0.01f,'f',2));
    MAP_Target.find(tar_NavPitch_cd         ).value()->setValueLabelText(QString::number(data.flylink.tTarget.NavPitch_cd     *0.01f,'f',2));
    MAP_Target.find(tar_NavYaw_cd           ).value()->setValueLabelText(QString::number(data.flylink.tTarget.NavYaw_cd       *0.01f,'f',2));
    MAP_Target.find(tar_TargetAcc_mpss_x    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetAcc_mpss[0],'f',2));
    MAP_Target.find(tar_TargetAcc_mpss_y    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetAcc_mpss[1],'f',2));
    MAP_Target.find(tar_TargetAcc_mpss_z    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetAcc_mpss[2],'f',2));
    MAP_Target.find(tar_TargetGyro_dps_x    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetGyro_dps[0],'f',2));
    MAP_Target.find(tar_TargetGyro_dps_y    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetGyro_dps[1],'f',2));
    MAP_Target.find(tar_TargetGyro_dps_z    ).value()->setValueLabelText(QString::number(data.flylink.tTarget.TargetGyro_dps[2],'f',2));
}

void DataView::update_wp()
{
    MAP_wp.find(wphome_sta).value()->setValueLabelText(data.flylink.tHome.is_get ? QStringLiteral("已获取"):QStringLiteral("未获取"));
    MAP_wp.find(wphome_Lat).value()->setValueLabelText(QString::number(data.flylink.tHome.loc.latitude*1e-7,'f',7));
    MAP_wp.find(wphome_Lng).value()->setValueLabelText(QString::number(data.flylink.tHome.loc.longitude*1e-7,'f',7));
    MAP_wp.find(wphome_Alt).value()->setValueLabelText(QString::number(data.flylink.tHome.loc.alt_m,'f',2));

    MAP_wp.find(wporigin_sta).value()->setValueLabelText(data.flylink.tOrigin.is_get ? QStringLiteral("已获取"):QStringLiteral("未获取"));
    MAP_wp.find(wporigin_Lat).value()->setValueLabelText(QString::number(data.flylink.tOrigin.loc.latitude*1e-7,'f',7));
    MAP_wp.find(wporigin_Lng).value()->setValueLabelText(QString::number(data.flylink.tOrigin.loc.longitude*1e-7,'f',7));
    MAP_wp.find(wporigin_Alt).value()->setValueLabelText(QString::number(data.flylink.tOrigin.loc.alt_m,'f',2));
}

void DataView::setData(const Q_DMMM::DataPool_t &newData)
{
    data = newData;
}


void DataView::widgetInit()
{
    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("信息面板"));
    }

    systemStatusWidgetInit();
    airPlaneInfoWidgetInit();
    escInfoWidgetInit();
    rcAndMotorStatusWidgetInit();
//    targetInfoWidgetInit();


    satelliteInfoWidgetInit();
    IMUStatusWidgetInit();
    magneticCompassStatusWidgetInit();
    barometerStatusWidgetInit();

//    waypointWidgetInit();


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout();
    }



    this->widgetLayout->addWidget(this->systemStatusWidget,         0,0,1,1);
    this->widgetLayout->addWidget(this->airPlaneInfoWidget,         1,0,1,1);
//    this->widgetLayout->addWidget(this->targetInfoWidget,           2,0,1,1);
    this->widgetLayout->addWidget(this->escInfoWidget,              2,0,1,1);
    this->widgetLayout->addWidget(this->IMUStatusWidget,            3,0,1,1);
    this->widgetLayout->addWidget(this->magneticCompassStatusWidget,4,0,1,1);
    this->widgetLayout->addWidget(this->barometerStatusWidget,      5,0,1,1);
    this->widgetLayout->addWidget(this->rcAndMotorStatusWidget,     6,0,1,1);
    this->widgetLayout->addWidget(this->satelliteInfoWidget,        7,0,1,1);
//    this->widgetLayout->addWidget(this->waypointWidget,             9,0,1,1);

    this->widgetLayout->setContentsMargins(5,5,5,5);
    this->widgetLayout->setSpacing(6);



    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->widgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);
    this->setObjectName("DataView");
    this->setWindowTitle(QStringLiteral("信息面板"));


}

void DataView::systemStatusWidgetInit()
{
    if(this->systemStatusWidget == nullptr){
        this->systemStatusWidget = new QGroupBox(QStringLiteral("系统状态信息"));
        this->systemStatusWidget->setObjectName("systemStatusWidget");
    }


    if(this->systemStatusLayout == nullptr){
        this->systemStatusLayout = new QGridLayout();
        this->systemStatusLayout->setContentsMargins(2,30,2,2);
//        this->systemStatusLayout->setSpacing(0);
        this->systemStatusLayout->setVerticalSpacing(2);
        this->systemStatusLayout->setHorizontalSpacing(2);
    }

    MAP_sysinfoStr.insert(sys_info_frame,QStringLiteral("构    型:"));
    MAP_sysinfoStr.insert(sys_info_flight_mode,QStringLiteral("飞行模式:"));
    MAP_sysinfoStr.insert(sys_info_armed,QStringLiteral("解锁状态:"));
    MAP_sysinfoStr.insert(sys_info_isflying,QStringLiteral("飞行状态:"));
    MAP_sysinfoStr.insert(sys_info_CPULoad,QStringLiteral("CPU 负载:"));
    MAP_sysinfoStr.insert(sys_info_time_sinceboot_ms,QStringLiteral("上电时间:"));
    MAP_sysinfoStr.insert(sys_info_flight_time_s,QStringLiteral("飞机航时:"));
    MAP_sysinfoStr.insert(sys_info_total_flight_time_s,QStringLiteral("累计航时:"));
    MAP_sysinfoStr.insert(sys_info_flight_dis_m,QStringLiteral("飞机航程:"));
    MAP_sysinfoStr.insert(sys_info_total_flight_dis_m,QStringLiteral("累计航程:"));
    MAP_sysinfoStr.insert(sys_info_boot_cnt,QStringLiteral("上电次数:"));
    MAP_sysinfoStr.insert(sys_info_Battery_voltage_mv,QStringLiteral("电压:"));// mV
    MAP_sysinfoStr.insert(sys_info_Battery_Current_CA,QStringLiteral("电    流:"));// A*100
    MAP_sysinfoStr.insert(sys_info_throttle,QStringLiteral("油    门:"));
    MAP_sysinfoStr.insert(sys_info_temperture,QStringLiteral("飞控温度:"));     // ℃*100
    MAP_sysinfoStr.insert(sys_info_arm_check,QStringLiteral("解锁条件:"));
    MAP_sysinfoStr.insert(sys_info_acc,QStringLiteral("加计状态:"));
    MAP_sysinfoStr.insert(sys_info_gyro,QStringLiteral("陀螺状态:"));
    MAP_sysinfoStr.insert(sys_info_mag,QStringLiteral("罗盘状态:"));
    MAP_sysinfoStr.insert(sys_info_baro,QStringLiteral("气压状态:"));
    MAP_sysinfoStr.insert(sys_info_airspeed,QStringLiteral("空速状态:"));
    MAP_sysinfoStr.insert(sys_info_GNSS,QStringLiteral("卫星状态:"));
    MAP_sysinfoStr.insert(sys_info_INS,QStringLiteral("惯导状态:"));
    MAP_sysinfoStr.insert(sys_info_AHRS,QStringLiteral("航姿状态:"));
    MAP_sysinfoStr.insert(sys_info_RC,QStringLiteral("遥控状态:"));
    MAP_sysinfoStr.insert(sys_info_datalink,QStringLiteral("通信状态:"));
    MAP_sysinfoStr.insert(sys_info_motor,QStringLiteral("电机输出:"));
    MAP_sysinfoStr.insert(sys_info_datalog,QStringLiteral("日志系统:"));
    MAP_sysinfoStr.insert(sys_info_power,QStringLiteral("电源状态:"));
    MAP_sysinfoStr.insert(sys_info_vibration,QStringLiteral("震动状态:"));
    MAP_sysinfoStr.insert(sys_info_home_dist_m,QStringLiteral("离家距离:"));
    MAP_sysinfoStr.insert(sys_info_home_bearing_cd,QStringLiteral("家角度:"));
    MAP_sysinfoStr.insert(sys_info_wp_dist_m,QStringLiteral("目标距离:"));
    MAP_sysinfoStr.insert(sys_info_alt_error,QStringLiteral("高度差值:"));
    MAP_sysinfoStr.insert(sys_info_xtrack_error,QStringLiteral("偏航距离:"));
    QMap<int,QString>::Iterator ite = MAP_sysinfoStr.begin();
    int cnt = 0;
    while(ite != MAP_sysinfoStr.end()){

        MAP_sysinfo.insert(ite.key(),new DataItemView(ite.value(),"0"));
        this->systemStatusLayout->addWidget(MAP_sysinfo.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        ite++;
        cnt++;
    }
    this->systemStatusWidget->setLayout(this->systemStatusLayout);

}

void DataView::airPlaneInfoWidgetInit()
{
    if(this->airPlaneInfoWidget == nullptr){
        this->airPlaneInfoWidget = new QGroupBox(QStringLiteral("机体信息"));
        this->airPlaneInfoWidget->setObjectName("airPlaneInfoWidget");
    }

    if(this->airPlaneInfoLayout == nullptr){
        this->airPlaneInfoLayout = new QGridLayout();
        this->airPlaneInfoLayout->setContentsMargins(2,15,2,2);
//        this->systemStatusLayout->setSpacing(0);
        this->airPlaneInfoLayout->setVerticalSpacing(2);
        this->airPlaneInfoLayout->setHorizontalSpacing(2);
    }
    MAP_vehicleStr.insert(vehicle_roll_cd,QStringLiteral("滚转角度:"));
    MAP_vehicleStr.insert(vehicle_pitch_cd,QStringLiteral("俯仰角度:"));
    MAP_vehicleStr.insert(vehicle_yaw_cd,QStringLiteral("航向角度:")); //0~36000
    MAP_vehicleStr.insert(vehicle_acc_mpss_x,QStringLiteral("加速度前:"));
    MAP_vehicleStr.insert(vehicle_acc_mpss_y,QStringLiteral("加速度右:"));
    MAP_vehicleStr.insert(vehicle_acc_mpss_z,QStringLiteral("加速度下:"));
    MAP_vehicleStr.insert(vehicle_gyro_dps_x,QStringLiteral("角速度前:"));
    MAP_vehicleStr.insert(vehicle_gyro_dps_y,QStringLiteral("角速度右:"));
    MAP_vehicleStr.insert(vehicle_gyro_dps_z,QStringLiteral("角速度下:"));
    MAP_vehicleStr.insert(vehicle_lat,QStringLiteral("纬    度:"));
    MAP_vehicleStr.insert(vehicle_lng,QStringLiteral("经    度:"));
    MAP_vehicleStr.insert(vehicle_alt_m,QStringLiteral("海拔高度:"));
    MAP_vehicleStr.insert(vehicle_pos_m_x,QStringLiteral("东向距离:"));
    MAP_vehicleStr.insert(vehicle_pos_m_y,QStringLiteral("北向距离:"));
    MAP_vehicleStr.insert(vehicle_pos_m_z,QStringLiteral("相对高度:"));    // ENU
    MAP_vehicleStr.insert(vehicle_vel_cmps_x,QStringLiteral("东向速度:")); // ENU
    MAP_vehicleStr.insert(vehicle_vel_cmps_y,QStringLiteral("北向速度:")); // ENU
    MAP_vehicleStr.insert(vehicle_vel_cmps_z,QStringLiteral("爬升速度:")); // ENU
    MAP_vehicleStr.insert(vehicle_airSpeed,QStringLiteral("空    速:")); // ENU
    MAP_vehicleStr.insert(vehicle_wind_dir,QStringLiteral("风    向:")); // ENU
    MAP_vehicleStr.insert(vehicle_wind_spd, QStringLiteral("风    速:")); // ENU
    MAP_vehicleStr.insert(vehicle_wind_spd_z,QStringLiteral("垂直风速:")); // ENU

    QMap<int,QString>::Iterator ite = MAP_vehicleStr.begin();
    int cnt = 0;
    while(ite != MAP_vehicleStr.end()){

        MAP_vehicle.insert(ite.key(),new DataItemView(ite.value(),"0"));
        this->airPlaneInfoLayout->addWidget(MAP_vehicle.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        ite++;
        cnt++;
    }

    this->airPlaneInfoWidget->setLayout(this->airPlaneInfoLayout);
}

void DataView::escInfoWidgetInit()
{
    if(this->escInfoWidget == nullptr){
        this->escInfoWidget = new QGroupBox(QStringLiteral("电调信息"));
        this->escInfoWidget->setObjectName("escInfoWidget");
    }
    if(this->escInfoLayout == nullptr){
        this->escInfoLayout = new QGridLayout();
        this->escInfoLayout->setContentsMargins(2,15,2,2);
        this->escInfoLayout->setVerticalSpacing(2);
        this->escInfoLayout->setHorizontalSpacing(2);
    }


    //    MAP_ESCStr.insert(esc1_input_vol,QStringLiteral("ESC1输入电压:"));
    //    MAP_ESCStr.insert(esc1_input_cur,QStringLiteral("ESC1输入电流:"));
    //    MAP_ESCStr.insert(esc1_output_cur,QStringLiteral("ESC1输出电流:"));
    //    MAP_ESCStr.insert(esc1_input_thr,QStringLiteral("ESC1输入油门:"));
    //    MAP_ESCStr.insert(esc1_output_thr,QStringLiteral("ESC1输出油门:"));
    //    MAP_ESCStr.insert(esc1_output_rpm,QStringLiteral("ESC1输出转速:"));
    //    MAP_ESCStr.insert(esc1_module_tem,QStringLiteral("ESC1模块温度:"));
    //    MAP_ESCStr.insert(esc1_motor_tem,QStringLiteral("ESC1电机温度:"));
    //    MAP_ESCStr.insert(esc2_input_vol,QStringLiteral("ESC2输入电压:"));
    //    MAP_ESCStr.insert(esc2_input_cur,QStringLiteral("ESC2输入电流:"));
    //    MAP_ESCStr.insert(esc2_output_cur,QStringLiteral("ESC2输出电流:"));
    //    MAP_ESCStr.insert(esc2_input_thr,QStringLiteral("ESC2输入油门:"));
    //    MAP_ESCStr.insert(esc2_output_thr,QStringLiteral("ESC2输出油门:"));
    //    MAP_ESCStr.insert(esc2_output_rpm,QStringLiteral("ESC2输出转速:"));
    //    MAP_ESCStr.insert(esc2_module_tem,QStringLiteral("ESC2模块温度:"));
    //    MAP_ESCStr.insert(esc2_motor_tem,QStringLiteral("ESC2电机温度:"));


    for (int i = 1; i <= 8; ++i) {
        MAP_ESCStr.insert((i-1)*4+0,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("输入电压:"));
        MAP_ESCStr.insert((i-1)*4+1,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("输入电流:"));
//        MAP_ESCStr.insert((i-1)*8+2,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("输出电流:"));
//        MAP_ESCStr.insert((i-1)*8+3,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("输入油门:"));
//        MAP_ESCStr.insert((i-1)*8+4,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("输出油门:"));
        MAP_ESCStr.insert((i-1)*4+2,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("输出转速:"));
        MAP_ESCStr.insert((i-1)*4+3,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("模块温度:"));
//        MAP_ESCStr.insert((i-1)*8+7,QStringLiteral("ESC")+QString::number(i)+QStringLiteral("电机温度:"));
    }


//    this->escSelect = new QComboBox(this);
//    QStringList items;
//    for (int i = 1; i <= 8; ++i) {
//        items << QStringLiteral("电调") + QString::number(i);
//    }

//    this->escSelect->addItems(items);
//    this->escInfoLayout->addWidget(escSelect,0,0,1,1);
//    int cnt = 0;
//    int row = 1;
//    QMap<int,QString>::Iterator ite = MAP_ESCStr.begin();
//    while(ite != MAP_ESCStr.end()){
//        QGroupBox* groupBox = new QGroupBox(this);
//        QHBoxLayout* layout = new QHBoxLayout(groupBox);
//        while(!(cnt/8))
//        {
//            MAP_ESC.insert(ite.key(),new DataItemView(ite.value(),"0"));
//            layout->addWidget(MAP_ESC.find(ite.key()).value());
//            ite++;
//            cnt++;
//        }
//        groupBox->setLayout(layout);
//        groupBox->hide();
//        this->escInfoLayout->addWidget(groupBox,row,0,1,8);
//        groupBoxes.push_back(groupBox);
//        cnt = 0;
//        row++;
//    }

//    this->escInfoWidget->setLayout(this->escInfoLayout);
//    this->escInfoWidget->setVisible(false);

//    connect(this->escSelect,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[=](int index){
//        for (auto groupBox : qAsConst(groupBoxes)) {
//            groupBox->hide();
//        }
//        if (index >= 0 && index < groupBoxes.size()) {
//            groupBoxes[index]->show();
//        }
//    });

        QMap<int,QString>::Iterator ite = MAP_ESCStr.begin();
        int cnt = 0;
        while(ite != MAP_ESCStr.end()){
            MAP_ESC.insert(ite.key(),new DataItemView(ite.value(),"0"));
            this->escInfoLayout->addWidget(MAP_ESC.find(ite.key()).value(),cnt/8,cnt%8,1,1);
            ite++;
            cnt++;
        }
        this->escInfoWidget->setLayout(this->escInfoLayout);

}

void DataView::satelliteInfoWidgetInit()
{
    if(this->satelliteInfoWidget == nullptr){
        this->satelliteInfoWidget = new QGroupBox(QStringLiteral("卫星信息"));
        this->satelliteInfoWidget->setObjectName("satelliteInfoWidget");
        this->satelliteInfoWidget->setVisible(false);
    }
    if(this->satelliteInfoLayout == nullptr){
        this->satelliteInfoLayout = new QGridLayout();
        this->satelliteInfoLayout->setContentsMargins(2,15,2,2);
//        this->systemStatusLayout->setSpacing(0);
        this->satelliteInfoLayout->setVerticalSpacing(2);
        this->satelliteInfoLayout->setHorizontalSpacing(2);
    }
    MAP_GNSSStr.insert(gnss1_fix_type,QStringLiteral("定位类型:")); /*<  GPS fix type.*/
    MAP_GNSSStr.insert(gnss1_num_sats,QStringLiteral("可用卫星:")); /*<  Number of satellites visible. If unknown,QStringLiteral("爬升速度:")); set to 255*/
    MAP_GNSSStr.insert(gnss1_lat,QStringLiteral("纬度:")); /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
    MAP_GNSSStr.insert(gnss1_lon,QStringLiteral("经度:")); /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
    MAP_GNSSStr.insert(gnss1_alt_m,QStringLiteral("海拔高度:"));
    MAP_GNSSStr.insert(gnss1_hdop_cm,QStringLiteral("水平精度:"));               ///< 3D velocity RMS accuracy estimate in cm/s
    MAP_GNSSStr.insert(gnss1_vdop_cm,QStringLiteral("垂直精度:"));          ///< horizontal RMS accuracy estimate in cm
    MAP_GNSSStr.insert(gnss1_yaw,QStringLiteral("偏航:"));
    MAP_GNSSStr.insert(gnss1_yaw_accuracy,QStringLiteral("偏航精度:"));
    MAP_GNSSStr.insert(gnss1_yaw_lagged_timestamp,QStringLiteral("偏航延时:"));
    MAP_GNSSStr.insert(gnss1_speed_accuracy_cmps,QStringLiteral("速度精度:"));

    MAP_GNSSStr.insert(gnss2_fix_type,QStringLiteral("定位类型:")); /*<  GPS fix type.*/
    MAP_GNSSStr.insert(gnss2_num_sats,QStringLiteral("可用卫星:")); /*<  Number of satellites visible. If unknown,QStringLiteral("爬升速度:")); set to 255*/
    MAP_GNSSStr.insert(gnss2_lat,QStringLiteral("纬度:")); /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
    MAP_GNSSStr.insert(gnss2_lon,QStringLiteral("经度:")); /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
    MAP_GNSSStr.insert(gnss2_alt_m,QStringLiteral("海拔高度:"));
    MAP_GNSSStr.insert(gnss2_hdop_cm,QStringLiteral("水平精度:"));               ///< 3D velocity RMS accuracy estimate in cm/s
    MAP_GNSSStr.insert(gnss2_vdop_cm,QStringLiteral("垂直精度:"));          ///< horizontal RMS accuracy estimate in cm
    MAP_GNSSStr.insert(gnss2_yaw,QStringLiteral("偏航:"));
    MAP_GNSSStr.insert(gnss2_yaw_accuracy,QStringLiteral("偏航精度:"));
    MAP_GNSSStr.insert(gnss2_yaw_lagged_timestamp,QStringLiteral("偏航延时:"));
    MAP_GNSSStr.insert(gnss2_speed_accuracy_cmps,QStringLiteral("速度精度:"));

    MAP_GNSSStr.insert(gnss3_fix_type,QStringLiteral("定位类型:")); /*<  GPS fix type.*/
    MAP_GNSSStr.insert(gnss3_num_sats,QStringLiteral("可用卫星:")); /*<  Number of satellites visible. If unknown,QStringLiteral("爬升速度:")); set to 255*/
    MAP_GNSSStr.insert(gnss3_lat,QStringLiteral("纬度:")); /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
    MAP_GNSSStr.insert(gnss3_lon,QStringLiteral("经度:")); /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
    MAP_GNSSStr.insert(gnss3_alt_m,QStringLiteral("海拔高度:"));
    MAP_GNSSStr.insert(gnss3_hdop_cm,QStringLiteral("水平精度:"));               ///< 3D velocity RMS accuracy estimate in cm/s
    MAP_GNSSStr.insert(gnss3_vdop_cm,QStringLiteral("垂直精度:"));          ///< horizontal RMS accuracy estimate in cm
    MAP_GNSSStr.insert(gnss3_yaw,QStringLiteral("偏航:"));
    MAP_GNSSStr.insert(gnss3_yaw_accuracy,QStringLiteral("偏航精度:"));
    MAP_GNSSStr.insert(gnss3_yaw_lagged_timestamp,QStringLiteral("偏航延时:"));
    MAP_GNSSStr.insert(gnss3_speed_accuracy_cmps,QStringLiteral("速度精度:"));
    QMap<int,QString>::Iterator ite = MAP_GNSSStr.begin();
    int cnt = 0;
    int single_size = MAP_GNSSStr.count()/3;
    while(ite != MAP_GNSSStr.end()){
        if(cnt < single_size)
        {
            MAP_GNSS.insert(ite.key(),new DataItemView(ite.value(),"0"));
            MAP_GNSS.find(ite.key()).value()->setVisible(false);
            this->satelliteInfoLayout->addWidget(MAP_GNSS.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        }
        else if(cnt < single_size * 2)
        {
            MAP_GNSS.insert(ite.key(),new DataItemView(ite.value(),"0"));
            MAP_GNSS.find(ite.key()).value()->setVisible(false);
            this->satelliteInfoLayout->addWidget(MAP_GNSS.find(ite.key()).value(),2+(cnt-single_size)/6,(cnt-single_size)%6,1,1);
        }
        else
        {
            MAP_GNSS.insert(ite.key(),new DataItemView(ite.value(),"0"));
            MAP_GNSS.find(ite.key()).value()->setVisible(false);
            this->satelliteInfoLayout->addWidget(MAP_GNSS.find(ite.key()).value(),4+(cnt-single_size*2)/6,(cnt-single_size*2)%6,1,1);
        }
        ite++;
        cnt++;
    }
    this->satelliteInfoWidget->setLayout(this->satelliteInfoLayout);
}

void DataView::IMUStatusWidgetInit()
{
    if(this->IMUStatusWidget == nullptr){
        this->IMUStatusWidget = new QGroupBox(QStringLiteral("IMU信息"));
        this->IMUStatusWidget->setObjectName("IMUStatusWidget");

        this->IMUStatusWidget->setVisible(false);
    }

    if(this->IMUStatusLayout == nullptr){
        this->IMUStatusLayout = new QGridLayout();
        this->IMUStatusLayout->setContentsMargins(2,15,2,2);
        this->IMUStatusLayout->setVerticalSpacing(2);
        this->IMUStatusLayout->setHorizontalSpacing(2);
    }

    MAP_IMUStr.insert(imu1_acc_mpss_x,QStringLiteral("加速度X1:"));
    MAP_IMUStr.insert(imu1_acc_mpss_y,QStringLiteral("加速度Y1:"));
    MAP_IMUStr.insert(imu1_acc_mpss_z,QStringLiteral("加速度Z1:"));
    MAP_IMUStr.insert(imu1_gyro_dps_x,QStringLiteral("陀螺仪X1:"));
    MAP_IMUStr.insert(imu1_gyro_dps_y,QStringLiteral("陀螺仪Y1:"));
    MAP_IMUStr.insert(imu1_gyro_dps_z,QStringLiteral("陀螺仪Z1:"));
    MAP_IMUStr.insert(imu1_vibrations_x,QStringLiteral("震动X1:"));
    MAP_IMUStr.insert(imu1_vibrations_y,QStringLiteral("震动Y1:"));
    MAP_IMUStr.insert(imu1_vibrations_z,QStringLiteral("震动Z1:"));
    MAP_IMUStr.insert(imu1_temperture,QStringLiteral("温度1:"));     // ℃*100
    MAP_IMUStr.insert(imu1_clips,QStringLiteral("过载次数1:"));

    MAP_IMUStr.insert(imu2_acc_mpss_x,QStringLiteral("加速度X2:"));
    MAP_IMUStr.insert(imu2_acc_mpss_y,QStringLiteral("加速度Y2:"));
    MAP_IMUStr.insert(imu2_acc_mpss_z,QStringLiteral("加速度Z2:"));
    MAP_IMUStr.insert(imu2_gyro_dps_x,QStringLiteral("陀螺仪X2:"));
    MAP_IMUStr.insert(imu2_gyro_dps_y,QStringLiteral("陀螺仪Y2:"));
    MAP_IMUStr.insert(imu2_gyro_dps_z,QStringLiteral("陀螺仪Z2:"));
    MAP_IMUStr.insert(imu2_vibrations_x,QStringLiteral("震动X2:"));
    MAP_IMUStr.insert(imu2_vibrations_y,QStringLiteral("震动Y2:"));
    MAP_IMUStr.insert(imu2_vibrations_z,QStringLiteral("震动Z2:"));
    MAP_IMUStr.insert(imu2_temperture,QStringLiteral("温度2:"));     // ℃*100
    MAP_IMUStr.insert(imu2_clips,QStringLiteral("过载次数2:"));

    MAP_IMUStr.insert(imu3_acc_mpss_x,QStringLiteral("加速度X3:"));
    MAP_IMUStr.insert(imu3_acc_mpss_y,QStringLiteral("加速度Y3:"));
    MAP_IMUStr.insert(imu3_acc_mpss_z,QStringLiteral("加速度Z3:"));
    MAP_IMUStr.insert(imu3_gyro_dps_x,QStringLiteral("陀螺仪X3:"));
    MAP_IMUStr.insert(imu3_gyro_dps_y,QStringLiteral("陀螺仪Y3:"));
    MAP_IMUStr.insert(imu3_gyro_dps_z,QStringLiteral("陀螺仪Z3:"));
    MAP_IMUStr.insert(imu3_vibrations_x,QStringLiteral("震动X3:"));
    MAP_IMUStr.insert(imu3_vibrations_y,QStringLiteral("震动Y3:"));
    MAP_IMUStr.insert(imu3_vibrations_z,QStringLiteral("震动Z3:"));
    MAP_IMUStr.insert(imu3_temperture,QStringLiteral("温度3:"));     // ℃*100
    MAP_IMUStr.insert(imu3_clips,QStringLiteral("过载次数3:"));

    QMap<int,QString>::Iterator ite = MAP_IMUStr.begin();
    int cnt = 0;
    int single_size = MAP_IMUStr.count()/3;
    while(ite != MAP_IMUStr.end()){

        if(cnt < single_size){
            MAP_IMU.insert(ite.key(),new DataItemView(ite.value(),"0"));
            MAP_IMU.find(ite.key()).value()->setVisible(false);
            this->IMUStatusLayout->addWidget(MAP_IMU.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        }
        else if(cnt < single_size*2){
            MAP_IMU.insert(ite.key(),new DataItemView(ite.value(),"0"));
            MAP_IMU.find(ite.key()).value()->setVisible(false);
            this->IMUStatusLayout->addWidget(MAP_IMU.find(ite.key()).value(),2+(cnt-single_size)/6,(cnt-single_size)%6,1,1);

        }
        else {
            MAP_IMU.insert(ite.key(),new DataItemView(ite.value(),"0"));
            MAP_IMU.find(ite.key()).value()->setVisible(false);
            this->IMUStatusLayout->addWidget(MAP_IMU.find(ite.key()).value(),4+(cnt-single_size*2)/6,(cnt-single_size*2)%6,1,1);
        }

        ite++;
        cnt++;
    }

    this->IMUStatusWidget->setLayout(this->IMUStatusLayout);
}

void DataView::magneticCompassStatusWidgetInit()
{
    if(this->magneticCompassStatusWidget == nullptr){
        this->magneticCompassStatusWidget = new QGroupBox(QStringLiteral("磁罗盘信息"));
        this->magneticCompassStatusWidget->setObjectName("magneticCompassStatusWidget");
        this->magneticCompassStatusWidget->setVisible(false);
    }

    if(this->magneticCompassStatusLayout == nullptr){
        this->magneticCompassStatusLayout = new QGridLayout();
        this->magneticCompassStatusLayout->setContentsMargins(2,15,2,2);
        this->magneticCompassStatusLayout->setVerticalSpacing(2);
        this->magneticCompassStatusLayout->setHorizontalSpacing(2);
    }

    MAP_CompassStr.insert(mag1_mG_x ,QStringLiteral("磁罗盘X1:"));
    MAP_CompassStr.insert(mag1_mG_y ,QStringLiteral("磁罗盘Y1:"));
    MAP_CompassStr.insert(mag1_mG_z ,QStringLiteral("磁罗盘Z1:"));
    MAP_CompassStr.insert(mag2_mG_x ,QStringLiteral("磁罗盘X2:"));
    MAP_CompassStr.insert(mag2_mG_y ,QStringLiteral("磁罗盘Y2:"));
    MAP_CompassStr.insert(mag2_mG_z ,QStringLiteral("磁罗盘Z2:"));
    MAP_CompassStr.insert(mag3_mG_x ,QStringLiteral("磁罗盘X3:"));
    MAP_CompassStr.insert(mag3_mG_y ,QStringLiteral("磁罗盘Y3:"));
    MAP_CompassStr.insert(mag3_mG_z ,QStringLiteral("磁罗盘Z3:"));

    QMap<int,QString>::Iterator ite = MAP_CompassStr.begin();
    int cnt = 0;
    while(ite != MAP_CompassStr.end()){
        MAP_Compass.insert(ite.key(),new DataItemView(ite.value(),"0"));
        MAP_Compass.find(ite.key()).value()->setVisible(false);
        this->magneticCompassStatusLayout->addWidget(MAP_Compass.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        ite++;
        cnt++;
    }
    this->magneticCompassStatusWidget->setLayout(this->magneticCompassStatusLayout);
}

void DataView::barometerStatusWidgetInit()
{
    if(this->barometerStatusWidget == nullptr){
        this->barometerStatusWidget = new QGroupBox(QStringLiteral("气压计信息"));
        this->barometerStatusWidget->setObjectName("barometerStatusWidget");
        this->barometerStatusWidget->setVisible(false);
    }

    if(this->barometerStatusLayout == nullptr){
        this->barometerStatusLayout = new QGridLayout();
        this->barometerStatusLayout->setContentsMargins(2,15,2,2);
        this->barometerStatusLayout->setVerticalSpacing(2);
        this->barometerStatusLayout->setHorizontalSpacing(2);
    }

    MAP_BaroStr.insert(baro1_Press_Pa,          QStringLiteral("气压值1:"));      // 单位：Pa
    MAP_BaroStr.insert(baro1_temperture,        QStringLiteral("温度值1:"));    // ℃*100
    MAP_BaroStr.insert(baro1_air_density_ratio, QStringLiteral("相对密度1:"));       // *100
    MAP_BaroStr.insert(baro2_Press_Pa,          QStringLiteral("气压值2:"));       // 单位：Pa
    MAP_BaroStr.insert(baro2_temperture,        QStringLiteral("温度值2:"));     // ℃*100
    MAP_BaroStr.insert(baro2_air_density_ratio, QStringLiteral("相对密度2:"));
    MAP_BaroStr.insert(baro3_Press_Pa,          QStringLiteral("气压值3:"));       // 单位：Pa
    MAP_BaroStr.insert(baro3_temperture,        QStringLiteral("温度值3:"));     // ℃*100
    MAP_BaroStr.insert(baro3_air_density_ratio, QStringLiteral("相对密度3:"));

    QMap<int,QString>::Iterator ite = MAP_BaroStr.begin();
    int cnt = 0;
    while(ite != MAP_BaroStr.end()){
        MAP_Baro.insert(ite.key(),new DataItemView(ite.value(),"0"));
        MAP_Baro.find(ite.key()).value()->setVisible(false);
        this->barometerStatusLayout->addWidget(MAP_Baro.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        ite++;
        cnt++;
    }

    this->barometerStatusWidget->setLayout(this->barometerStatusLayout);
}

void DataView::rcAndMotorStatusWidgetInit()
{
    if(this->rcAndMotorStatusWidget == nullptr){
        this->rcAndMotorStatusWidget = new QGroupBox(QStringLiteral("遥控输入及电机输出"));
        this->rcAndMotorStatusWidget->setObjectName("rcAndMotorStatusWidget");
    }

    if(this->rcAndMotorStatusLayout == nullptr){
        this->rcAndMotorStatusLayout = new QGridLayout();
        this->rcAndMotorStatusLayout->setContentsMargins(2,15,2,2);
        this->rcAndMotorStatusLayout->setVerticalSpacing(2);
        this->rcAndMotorStatusLayout->setHorizontalSpacing(2);
    }

    MAP_RC_OUTStr.insert(RC_OUT_rc1,QStringLiteral("RC  1:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc2,QStringLiteral("RC  2:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc3,QStringLiteral("RC  3:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc4,QStringLiteral("RC  4:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc5,QStringLiteral("RC  5:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc6,QStringLiteral("RC  6:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc7,QStringLiteral("RC  7:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc8,QStringLiteral("RC  8:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc9,QStringLiteral("RC  9:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc10,QStringLiteral("RC 10:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc11,QStringLiteral("RC 11:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc12,QStringLiteral("RC 12:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc13,QStringLiteral("RC 13:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc14,QStringLiteral("RC 14:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc15,QStringLiteral("RC 15:"));
    MAP_RC_OUTStr.insert(RC_OUT_rc16,QStringLiteral("RC 16:"));
    MAP_RC_OUTStr.insert(RC_OUT_out1,QStringLiteral("OUT 1:"));
    MAP_RC_OUTStr.insert(RC_OUT_out2,QStringLiteral("OUT 2:"));
    MAP_RC_OUTStr.insert(RC_OUT_out3,QStringLiteral("OUT 3:"));
    MAP_RC_OUTStr.insert(RC_OUT_out4,QStringLiteral("OUT 4:"));
    MAP_RC_OUTStr.insert(RC_OUT_out5,QStringLiteral("OUT 5:"));
    MAP_RC_OUTStr.insert(RC_OUT_out6,QStringLiteral("OUT 6:"));
    MAP_RC_OUTStr.insert(RC_OUT_out7,QStringLiteral("OUT 7:"));
    MAP_RC_OUTStr.insert(RC_OUT_out8,QStringLiteral("OUT 8:"));
    MAP_RC_OUTStr.insert(RC_OUT_out9,QStringLiteral("OUT 9:"));
    MAP_RC_OUTStr.insert(RC_OUT_out10,QStringLiteral("OUT10:"));
    MAP_RC_OUTStr.insert(RC_OUT_out11,QStringLiteral("OUT11:"));
    MAP_RC_OUTStr.insert(RC_OUT_out12,QStringLiteral("OUT12:"));
    MAP_RC_OUTStr.insert(RC_OUT_out13,QStringLiteral("OUT13:"));
    MAP_RC_OUTStr.insert(RC_OUT_out14,QStringLiteral("OUT14:"));
    MAP_RC_OUTStr.insert(RC_OUT_out15,QStringLiteral("OUT15:"));
    MAP_RC_OUTStr.insert(RC_OUT_out16,QStringLiteral("OUT16:"));

    QMap<int,QString>::Iterator ite = MAP_RC_OUTStr.begin();
    int cnt = 0;
    while(ite != MAP_RC_OUTStr.end()){
        MAP_RC_OUT.insert(ite.key(),new DataItemView(ite.value(),"1000"));
        this->rcAndMotorStatusLayout->addWidget(MAP_RC_OUT.find(ite.key()).value(),cnt/8,cnt%8,1,1);
        ite++;
        cnt++;
    }




    this->rcAndMotorStatusWidget->setLayout(this->rcAndMotorStatusLayout);
}

void DataView::targetInfoWidgetInit()
{
    if(this->targetInfoWidget == nullptr){
        this->targetInfoWidget = new QGroupBox(QStringLiteral("控制目标值信息"));
        this->targetInfoWidget->setObjectName("targetInfoWidget");
    }

    if(this->targetInfoLayout == nullptr){
        this->targetInfoLayout = new QGridLayout();
        this->targetInfoLayout->setContentsMargins(2,15,2,2);
        this->targetInfoLayout->setVerticalSpacing(2);
        this->targetInfoLayout->setHorizontalSpacing(2);
    }

    MAP_TargetStr.insert(tar_MissionID,QStringLiteral("目标序号:"));
    MAP_TargetStr.insert(tar_TargetLat,QStringLiteral("目标纬度:"));
    MAP_TargetStr.insert(tar_TargetLng,QStringLiteral("目标经度:"));
    MAP_TargetStr.insert(tar_TargetASL_m,QStringLiteral("目标海拔:"));
    MAP_TargetStr.insert(tar_TargetAlt_m,QStringLiteral("目标高度:"));
    MAP_TargetStr.insert(tar_DesiredAlt_m,QStringLiteral("期望高度:"));
    MAP_TargetStr.insert(tar_TargetVel_e_cmps,QStringLiteral("T速度-E:"));
    MAP_TargetStr.insert(tar_TargetVel_n_cmps,QStringLiteral("T速度-N:"));
    MAP_TargetStr.insert(tar_TargetVel_u_cmps,QStringLiteral("T速度-U:"));
    MAP_TargetStr.insert(tar_NavRoll_cd,QStringLiteral("目标滚转:"));
    MAP_TargetStr.insert(tar_NavPitch_cd,QStringLiteral("目标俯仰:"));
    MAP_TargetStr.insert(tar_NavYaw_cd,QStringLiteral("目标航向:"));
    MAP_TargetStr.insert(tar_TargetAcc_mpss_x,QStringLiteral("T加速度X:"));
    MAP_TargetStr.insert(tar_TargetAcc_mpss_y,QStringLiteral("T加速度Y:"));
    MAP_TargetStr.insert(tar_TargetAcc_mpss_z,QStringLiteral("T加速度Z:"));
    MAP_TargetStr.insert(tar_TargetGyro_dps_x,QStringLiteral("T角速度X:"));
    MAP_TargetStr.insert(tar_TargetGyro_dps_y,QStringLiteral("T角速度Y:"));
    MAP_TargetStr.insert(tar_TargetGyro_dps_z,QStringLiteral("T角速度Z:"));
    QMap<int,QString>::Iterator ite = MAP_TargetStr.begin();
    int cnt = 0;
    while(ite != MAP_TargetStr.end()){
        MAP_Target.insert(ite.key(),new DataItemView(ite.value(),"1000"));
        this->targetInfoLayout->addWidget(MAP_Target.find(ite.key()).value(),cnt/6,cnt%6,1,1);
        ite++;
        cnt++;
    }
    this->targetInfoWidget->setLayout(this->targetInfoLayout);

}

void DataView::waypointWidgetInit()
{
    if(this->waypointWidget == nullptr){
        this->waypointWidget = new QGroupBox(QStringLiteral("家的位置"));
        this->waypointWidget->setObjectName("targetInfoWidget");
    }

    if(this->waypointLayout == nullptr){
        this->waypointLayout = new QGridLayout();
        this->waypointLayout->setContentsMargins(2,15,2,2);
        this->waypointLayout->setVerticalSpacing(2);
        this->waypointLayout->setHorizontalSpacing(2);
    }

    MAP_wpStr.insert(wphome_sta,QStringLiteral("家的状态:"));
    MAP_wpStr.insert(wphome_Lat,QStringLiteral("纬度:"));
    MAP_wpStr.insert(wphome_Lng,QStringLiteral("经度:"));
    MAP_wpStr.insert(wphome_Alt,QStringLiteral("海拔:"));
    MAP_wpStr.insert(wporigin_sta,QStringLiteral("原点状态:"));
    MAP_wpStr.insert(wporigin_Lat,QStringLiteral("纬度:"));
    MAP_wpStr.insert(wporigin_Lng,QStringLiteral("经度:"));
    MAP_wpStr.insert(wporigin_Alt,QStringLiteral("海拔:"));


    int cnt = 0;
    QMap<int,QString>::Iterator ite = MAP_wpStr.begin();
    while(ite != MAP_wpStr.end()){
        MAP_wp.insert(ite.key(),new DataItemView(ite.value(),"0"));
        this->waypointLayout->addWidget(MAP_wp.find(ite.key()).value(),cnt/4,cnt%4,1,1);
        ite++;
        cnt++;
    }
    this->waypointWidget->setLayout(this->waypointLayout);
}

//void DataView::update_gis()
//{
//    if(this->airPositionModel == nullptr){
//        return;
//    }
//    qDebug()<<"data.gcs_id =  "<<data.gcs_id;
//    this->airPositionModel->addAirPositionData(data.gcs_id);
//    this->airPositionModel->updateAirPosition(data.gcs_id,data.flylink.tVehicle.lat*1e-7,data.flylink.tVehicle.lng*1e-7,data.flylink.tVehicle.alt_m,data.flylink.tVehicle.yaw_cd*0.01f);
//}

void DataView::update_data()
{
    if(Qt::DMMM()!= nullptr){
        data = Qt::DMMM()->getData_main();
    }
}

DataItemView::DataItemView(QString name,QString value)
{
    if(this->nameLabel == nullptr){
        this->nameLabel = new QLabel(name);
        this->nameLabel->setObjectName("DataItemViewName");
        this->nameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        this->nameLabel->setMaximumWidth(150);
        this->nameLabel->setMinimumHeight(25);
    }

    if(this->valueLabel == nullptr){
        this->valueLabel = new QLabel(value);
        this->valueLabel->setObjectName("DataItemViewValue");
        this->valueLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        this->valueLabel->setMaximumWidth(150);
        this->valueLabel->setMinimumHeight(25);
    }

    if(this->dataItemViewLayout == nullptr){
        this->dataItemViewLayout = new QHBoxLayout();
        this->dataItemViewLayout->addWidget(this->nameLabel);
        this->dataItemViewLayout->addWidget(this->valueLabel);
        this->dataItemViewLayout->setSpacing(0);
        this->dataItemViewLayout->setMargin(0);
        this->setLayout(this->dataItemViewLayout);
    }
    this->setObjectName("DataItemView");
}


void DataItemView::setNameLabelText(QString name)
{
    if(this->nameLabel != nullptr){
        this->nameLabel->setText(name);
    }
}

QString DataItemView::getNameLabelText()
{
    if(this->nameLabel != nullptr){
        return this->nameLabel->text();
    }

    return QString();
}

void DataItemView::setValueLabelText(QString value)
{
    if(this->valueLabel != nullptr){
        this->valueLabel->setText(value);
    }
}

QString DataItemView::getValueLabelText()
{
    if(this->valueLabel != nullptr){
        return this->valueLabel->text();
    }
    return QString();
}
