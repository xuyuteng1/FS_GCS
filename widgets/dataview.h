#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QFile>
#include "FlyLink.h"
#include "gis_model.h"
#include "DMMM.h"
#include <QApplication>
#include "widgetitle.h"
class DataItemView : public QGroupBox{
public:
    DataItemView(QString name = QStringLiteral("名称"),QString value = QStringLiteral("--"));
    void setNameLabelText(QString);
    QString getNameLabelText();

    void setValueLabelText(QString value);
    QString getValueLabelText();
private:
    QLabel *nameLabel = nullptr;
    QLabel *valueLabel = nullptr;
    QHBoxLayout *dataItemViewLayout = nullptr;
};


class DataView : public QWidget
{
    Q_OBJECT
public:
    DataView(QWidget *parent = nullptr);

    void setData(const Q_DMMM::DataPool_t &newData);
signals:
    void signalCloseEvent();
public slots:
    void update_display();
private:
    WidgetTitle*    w_title = nullptr;

    QGroupBox *systemStatusWidget = nullptr;                        /*系统状态信息面板*/
    QGridLayout *systemStatusLayout = nullptr;                      /*系统状态信息面板布局*/

    QGroupBox *airPlaneInfoWidget = nullptr;                        /*机体信息面板*/
    QGridLayout *airPlaneInfoLayout = nullptr;                      /*机体信息面板布局*/

    QGroupBox *satelliteInfoWidget = nullptr;                       /*卫星信息面板*/
    QGridLayout *satelliteInfoLayout = nullptr;                     /*卫星信息面板布局*/

    QGroupBox *escInfoWidget = nullptr;                        /*电调信息面板*/
    QGridLayout *escInfoLayout = nullptr;                      /*电调信息面板布局*/
    QComboBox* escSelect = nullptr;                             /*电调信息选择*/
    QVector<QGroupBox*> groupBoxes;

    QGroupBox *IMUStatusWidget = nullptr;                           /*IMU信息面板*/
    QGridLayout *IMUStatusLayout = nullptr;

    QGroupBox *magneticCompassStatusWidget = nullptr;               /*磁罗盘信息面板*/
    QGridLayout *magneticCompassStatusLayout = nullptr;

    QGroupBox *barometerStatusWidget = nullptr;                     /*气压计信息面板*/
    QGridLayout *barometerStatusLayout = nullptr;

    QGroupBox *rcAndMotorStatusWidget = nullptr;                    /*电机与手柄信息面板*/
    QGridLayout *rcAndMotorStatusLayout = nullptr;

    QGroupBox *targetInfoWidget = nullptr;                          /*控制目标值信息面板*/
    QGridLayout *targetInfoLayout = nullptr;

    QGroupBox *waypointWidget = nullptr;                          /*home与origin点*/
    QGridLayout *waypointLayout = nullptr;

    QGridLayout *widgetLayout = nullptr;
    QGridLayout *mainLayout = nullptr;

    /*系统状态信息面板子控件*/
    DataItemView *airLayoutWidget = nullptr;
    DataItemView *airFlyModel = nullptr;
    DataItemView *airStatus = nullptr;

    typedef enum{
        sys_info_frame = 0,
        sys_info_flight_mode,
        sys_info_armed,
        sys_info_isflying,
        sys_info_CPULoad,
        sys_info_time_sinceboot_ms,
        sys_info_flight_time_s,
        sys_info_total_flight_time_s,
        sys_info_flight_dis_m,
        sys_info_total_flight_dis_m,
        sys_info_boot_cnt,
        sys_info_Battery_voltage_mv,// mV
        sys_info_Battery_Current_CA,// A*100
        sys_info_throttle,
        sys_info_temperture,     // ℃*100
        sys_info_arm_check,
        sys_info_acc,
        sys_info_gyro,
        sys_info_mag,
        sys_info_baro,
        sys_info_airspeed,
        sys_info_GNSS,
        sys_info_INS,
        sys_info_AHRS,
        sys_info_RC,
        sys_info_datalink,
        sys_info_motor,
        sys_info_datalog,
        sys_info_power,
        sys_info_vibration,
        sys_info_home_dist_m,
        sys_info_home_bearing_cd,
        sys_info_wp_dist_m,
        sys_info_alt_error,
        sys_info_xtrack_error,
    }sysinfo_e;

    typedef enum{
        vehicle_roll_cd = 0,
        vehicle_pitch_cd,
        vehicle_yaw_cd, //0~36000
        vehicle_acc_mpss_x,
        vehicle_acc_mpss_y,
        vehicle_acc_mpss_z,
        vehicle_gyro_dps_x,
        vehicle_gyro_dps_y,
        vehicle_gyro_dps_z,
        vehicle_lat,
        vehicle_lng,
        vehicle_alt_m,
        vehicle_pos_m_x,
        vehicle_pos_m_y,
        vehicle_pos_m_z,    // ENU
        vehicle_vel_cmps_x, // ENU
        vehicle_vel_cmps_y, // ENU
        vehicle_vel_cmps_z, // ENU
        vehicle_airSpeed,
        vehicle_wind_dir,
        vehicle_wind_spd, //cm/s
        vehicle_wind_spd_z,//cm/s
    }vehicle_e;

    typedef enum{
        esc1_input_vol = 0,
        esc1_input_cur,
        esc1_output_cur,
        esc1_input_thr,
        esc1_output_thr,
        esc1_output_rpm,
        esc1_module_tem,
        esc1_motor_tem,
        esc2_input_vol,
        esc2_input_cur,
        esc2_output_cur,
        esc2_input_thr,
        esc2_output_thr,
        esc2_output_rpm,
        esc2_module_tem,
        esc2_motor_tem,
        //        esc3_input_vol,
        //        esc3_input_cur,
        //        esc3_output_cur,
        //        esc3_input_thr,
        //        esc3_output_thr,
        //        esc3_output_rpm,
        //        esc3_module_tem,
        //        esc3_motor_tem,
        //        esc4_input_vol,
        //        esc4_input_cur,
        //        esc4_output_cur,
        //        esc4_input_thr,
        //        esc4_output_thr,
        //        esc4_output_rpm,
        //        esc4_module_tem,
        //        esc4_motor_tem,
    }ESC_e;

    typedef enum{
        gnss1_fix_type, /*<  GPS fix type.*/
        gnss1_num_sats, /*<  Number of satellites visible. If unknown, set to 255*/
        gnss1_lat, /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
        gnss1_lon, /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
        gnss1_alt_m,
        gnss1_hdop_cm,               ///< 3D velocity RMS accuracy estimate in cm/s
        gnss1_vdop_cm,          ///< horizontal RMS accuracy estimate in cm
        gnss1_yaw,
        gnss1_yaw_accuracy,
        gnss1_yaw_lagged_timestamp,
        gnss1_speed_accuracy_cmps,


        gnss2_fix_type, /*<  GPS fix type.*/
        gnss2_num_sats, /*<  Number of satellites visible. If unknown, set to 255*/
        gnss2_lat, /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
        gnss2_lon, /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
        gnss2_alt_m,
        gnss2_hdop_cm,               ///< 3D velocity RMS accuracy estimate in cm/s
        gnss2_vdop_cm,          ///< horizontal RMS accuracy estimate in cm
        gnss2_yaw,
        gnss2_yaw_accuracy,
        gnss2_yaw_lagged_timestamp,
        gnss2_speed_accuracy_cmps,

        gnss3_fix_type, /*<  GPS fix type.*/
        gnss3_num_sats, /*<  Number of satellites visible. If unknown, set to 255*/
        gnss3_lat, /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
        gnss3_lon, /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
        gnss3_alt_m,
        gnss3_hdop_cm,               ///< 3D velocity RMS accuracy estimate in cm/s
        gnss3_vdop_cm,          ///< horizontal RMS accuracy estimate in cm
        gnss3_yaw,
        gnss3_yaw_accuracy,
        gnss3_yaw_lagged_timestamp,
        gnss3_speed_accuracy_cmps,
     }GNSS_e;

    typedef enum{
        imu1_acc_mpss_x = 0,
        imu1_acc_mpss_y,
        imu1_acc_mpss_z,
        imu1_gyro_dps_x,
        imu1_gyro_dps_y,
        imu1_gyro_dps_z,
        imu1_vibrations_x,
        imu1_vibrations_y,
        imu1_vibrations_z,
        imu1_temperture,     // ℃*100
        imu1_clips,
        imu2_acc_mpss_x,
        imu2_acc_mpss_y,
        imu2_acc_mpss_z,
        imu2_gyro_dps_x,
        imu2_gyro_dps_y,
        imu2_gyro_dps_z,
        imu2_vibrations_x,
        imu2_vibrations_y,
        imu2_vibrations_z,
        imu2_temperture,     // ℃*100
        imu2_clips,
        imu3_acc_mpss_x,
        imu3_acc_mpss_y,
        imu3_acc_mpss_z,
        imu3_gyro_dps_x,
        imu3_gyro_dps_y,
        imu3_gyro_dps_z,
        imu3_vibrations_x,
        imu3_vibrations_y,
        imu3_vibrations_z,
        imu3_temperture,     // ℃*100
        imu3_clips,
    }IMU_e;

    typedef enum{
        mag1_mG_x = 0,
        mag1_mG_y ,
        mag1_mG_z ,
        mag2_mG_x ,
        mag2_mG_y ,
        mag2_mG_z ,
        mag3_mG_x ,
        mag3_mG_y ,
        mag3_mG_z ,
    }Compass_e;//

    typedef enum{
        baro1_Press_Pa = 0,       // 单位：Pa
        baro1_temperture,     // ℃*100
        baro1_air_density_ratio,        // *100
        baro2_Press_Pa,       // 单位：Pa
        baro2_temperture,     // ℃*100
        baro2_air_density_ratio,
        baro3_Press_Pa,       // 单位：Pa
        baro3_temperture,     // ℃*100
        baro3_air_density_ratio,
    }baro_e;//

    typedef enum{
        RC_OUT_rc1,
        RC_OUT_rc2,
        RC_OUT_rc3,
        RC_OUT_rc4,
        RC_OUT_rc5,
        RC_OUT_rc6,
        RC_OUT_rc7,
        RC_OUT_rc8,
        RC_OUT_rc9,
        RC_OUT_rc10,
        RC_OUT_rc11,
        RC_OUT_rc12,
        RC_OUT_rc13,
        RC_OUT_rc14,
        RC_OUT_rc15,
        RC_OUT_rc16,
        RC_OUT_out1,
        RC_OUT_out2,
        RC_OUT_out3,
        RC_OUT_out4,
        RC_OUT_out5,
        RC_OUT_out6,
        RC_OUT_out7,
        RC_OUT_out8,
        RC_OUT_out9,
        RC_OUT_out10,
        RC_OUT_out11,
        RC_OUT_out12,
        RC_OUT_out13,
        RC_OUT_out14,
        RC_OUT_out15,
        RC_OUT_out16,
    }rc_out_e;

    typedef enum{
        tar_MissionID,
        tar_TargetLat,
        tar_TargetLng,
        tar_TargetASL_m,
        tar_TargetAlt_m,
        tar_DesiredAlt_m,
        tar_TargetVel_e_cmps,
        tar_TargetVel_n_cmps,
        tar_TargetVel_u_cmps,
        tar_NavRoll_cd,
        tar_NavPitch_cd,
        tar_NavYaw_cd,
        tar_TargetAcc_mpss_x,
        tar_TargetAcc_mpss_y,
        tar_TargetAcc_mpss_z,
        tar_TargetGyro_dps_x,
        tar_TargetGyro_dps_y,
        tar_TargetGyro_dps_z,
    }target_e;

    typedef enum{
        wphome_sta,
        wphome_Lat,
        wphome_Lng,
        wphome_Alt,
        wporigin_sta,
        wporigin_Lat,
        wporigin_Lng,
        wporigin_Alt,

    }home_origin_e;
    QMap<int,DataItemView*> MAP_sysinfo;
    QMap<int,QString> MAP_sysinfoStr;

    QMap<int,DataItemView*> MAP_vehicle;
    QMap<int,QString> MAP_vehicleStr;

    QMap<int,DataItemView*> MAP_ESC;
    QMap<int,QString> MAP_ESCStr;

    QMap<int,DataItemView*> MAP_GNSS;
    QMap<int,QString> MAP_GNSSStr;

    QMap<int,DataItemView*> MAP_IMU;
    QMap<int,QString> MAP_IMUStr;

    QMap<int,DataItemView*> MAP_Compass;
    QMap<int,QString> MAP_CompassStr;

    QMap<int,DataItemView*> MAP_Baro;
    QMap<int,QString> MAP_BaroStr;

    QMap<int,DataItemView*> MAP_RC_OUT;
    QMap<int,QString> MAP_RC_OUTStr;

    QMap<int,DataItemView*> MAP_Target;
    QMap<int,QString> MAP_TargetStr;


    QMap<int,DataItemView*> MAP_wp;
    QMap<int,QString> MAP_wpStr;

    void update_sysinfo();
    void update_vehicle();
    void update_esc();
    void update_GNSS();
    void update_IMU();
    void update_Compass();
    void update_Baro();
    void update_rc_out();
    void update_target();
    void update_wp();

private:
    Q_DMMM::DataPool_t data = {};
    Q_DMMM::DataPool_t last_data = {};

private:
    void widgetInit();
    void systemStatusWidgetInit();
    void airPlaneInfoWidgetInit();
    void satelliteInfoWidgetInit();
    void escInfoWidgetInit();
    void IMUStatusWidgetInit();
    void magneticCompassStatusWidgetInit();
    void barometerStatusWidgetInit();
    void rcAndMotorStatusWidgetInit();
    void targetInfoWidgetInit();
    void waypointWidgetInit();


//    void update_gis();
    void update_data();

protected:
    /**========= 窗口支持鼠标拖动 =========**/
    QPoint dragPosition;
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
           dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    };

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    };
};

#endif // DATAVIEW_H
