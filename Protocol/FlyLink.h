/**=================================================================**
 * @brief       : 通信协议部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-01-16     Jerry.xl     the first version
 **==================================================================**/
#ifndef FlyLink_H__
#define FlyLink_H__

#ifndef PROTOCOL_FlyLink_ENABLED
#define PROTOCOL_FlyLink_ENABLED (1)
#endif

#include <QDebug>
#include <QApplication>
#include <QLabel>
#include <QDateTime>
#include <QString>
#include <QTimer>
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QMutexLocker>
#include <QThread>
#include <QString>
#include "DeviceCommunication.h"
/**---------------------------------------------------**/
/// 2023--3-17  V1.0.3.0 Alpha
/**---------------------------------------------------**/
/*
- 修改导引点变量
- 增加返航点配置功能
*/

#if PROTOCOL_FlyLink_ENABLED
 /*====================== 协议版本 ====================*/
#define FlyLink_Protocol_Version                     (1030)
/*====================== 协议的帧定义相关内容 ====================*/
#define FlyLink_FRAME_HEADER_X                        (0X4b)
#define FlyLink_FRAME_HEADER_Y                        (0X57)
#define FlyLink_MAX_BUF_LEN                           (255+20)

/*======================= 协议MSG ID 定义 ========================*/
/// 通用信息 0~30
#define FlyLink_ID_HEARTBEAT                          (1)
#define FlyLink_ID_VEHICLE_INFO                       (2)
#define FlyLink_ID_GNSS                               (3)
#define FlyLink_ID_IMUS                               (4)
#define FlyLink_ID_COMPASS                            (5)
#define FlyLink_ID_BARO                               (6)
#define FlyLink_ID_RC_OUT                             (7)
#define FlyLink_ID_HOME                               (8)
#define FlyLink_ID_ORIGIN                             (9)
#define FlyLink_ID_EXTVoltageMonitor                  (10)
#define FlyLink_ID_RPMInfo                            (11)
#define FlyLink_ID_BoardInfo                          (12)
#define FlyLink_ID_Guidance                           (13)

#define FlyLink_ID_SYSINFO                            (14)
#define FlyLink_ID_CONTROL_TARGET                     (15)
#define FlyLink_ID_Guided_WP                          (16)
#define FlyLink_ID_ESC                                (17)

// 数据透传接口
#define FlyLink_ID_Transparent                        (31)

#define FlyLink_ID_STATUS_TEXT                        (32)
#define FlyLink_ID_ACC_CALI_POSITION                  (33)
#define FlyLink_ID_MAG_CALI_PROGRESS                  (34)

#define FlyLink_ID_COMMOM_PARAM_REQ                   (35)
#define FlyLink_ID_COMMOM_PARAM                       (36)

/**** 机载日志读取指令 ****/
#define FlyLink_ID_REQUEST_LOG_LIST                   (37)
#define FlyLink_ID_REQUEST_LOG_DATA                   (38)
#define FlyLink_ID_LOG_INFO                           (39)
#define FlyLink_ID_LOG_DATA                           (40)
#define FlyLink_ID_LOG_CLEARALL                       (41)

#define FlyLink_ID_COMMAND                            (42)
#define FlyLink_ID_COMMAND_ACK                        (43)
/****航线上传下载指令****/
#define FlyLink_ID_MISSION_COUNT                      (44)
#define FlyLink_ID_MISSION_ITEM                       (45)
#define FlyLink_ID_MISSION_REQUEST                    (46)
#define FlyLink_ID_MISSION_REQUEST_LIST               (47)
#define FlyLink_ID_MISSION_CLEAR_ALL                  (48)
#define FlyLink_ID_MISSION_ACK                        (49)
/****参数设定****/
#define FlyLink_ID_PARAM_SerialPort                   (50)
#define FlyLink_ID_Waypoint                           (51)

/*======================= 多旋翼参数 ========================*/
#define FlyLink_ID_PARAM_FAILSAFE                     (80)
#define FlyLink_ID_PARAM_MAIN_RC                      (81)
#define FlyLink_ID_PARAM_MOTORS                       (82)
#define FlyLink_ID_PARAM_GNSS_POSITION                (83)
#define FlyLink_ID_PARAM_INIT_CFG_PARAM               (84)
#define FlyLink_ID_PARAM_PILOT_CONTROL                (85)
#define FlyLink_ID_PARAM_AUTO_CONTROL                 (86)

#define FlyLink_ID_PARAM_Roll_CONTROL                 (87)
#define FlyLink_ID_PARAM_Pitch_CONTROL                (88)
#define FlyLink_ID_PARAM_Yaw_CONTROL                  (89)
#define FlyLink_ID_PARAM_POSZ_CONTROL                 (90)
#define FlyLink_ID_PARAM_POSXY_CONTROL                (91)
#define FlyLink_ID_PARAM_AUX_RC                       (92)


#define FlyLink_MAX_SensorBackend                     (3)
#define FlyLink_MAX_ESC                               (8)
#define FlyLink_LOG_DataSize                          (240)
/*====================== 类定义 ====================*/
class FlyLink : public DeviceCommunication
{
    Q_OBJECT
public:
    /*--------------构造/析构函数--------------*/
    FlyLink(QObject *parent=nullptr,uint8_t gcs_id = 1,bool IndependentThread = false);
    virtual ~FlyLink();

public slots:
    void update_send();
    void update_receive();
    void update_10Hz();
    void handle_DMMM_event(int ev,int linkid = 0);
public:
    typedef enum
    {
        VehicleType_Unkown = 0,
        VehicleType_Copter = 1,
        VehicleType_Plane = 2,
    }VehicleType_e;
    typedef enum
    {
       GPS_FIX_TYPE_NO_GPS=0, /* No GPS connected | */
       GPS_FIX_TYPE_NO_FIX=1, /* No position information, GPS is connected | */
       GPS_FIX_TYPE_2D_FIX=2, /* 2D position | */
       GPS_FIX_TYPE_3D_FIX=3, /* 3D position | */
       GPS_FIX_TYPE_DGPS=4, /* DGPS/SBAS aided 3D position | */
       GPS_FIX_TYPE_RTK_FLOAT=5, /* RTK float, 3D position | */
       GPS_FIX_TYPE_RTK_FIXED=6, /* RTK Fixed, 3D position | */
       GPS_FIX_TYPE_STATIC=7, /* Static fixed, typically used for base stations | */
       GPS_FIX_TYPE_PPP=8, /* PPP, 3D position. | */
       GPS_FIX_TYPE_ENUM_END=9, /*  | */
    }GPS_FIX_TYPE;

    typedef enum
    {
        MISSION_ALT_FRAME_RELATIVE_ALT  = 0,                 //相对高度
        MISSION_ALT_FRAME_GLOBAL,                   //海拔高度
        MISSION_ALT_FRAME_RELATIVE_TERRAIN_ALT,         //地形高度
    }MISSION_ALT_FRAME;

    typedef enum  {
        AltFrame_ABSOLUTE = 0,
        AltFrame_ABOVE_HOME = 1,
        AltFrame_ABOVE_ORIGIN = 2,
        AltFrame_ABOVE_TERRAIN = 3
    }AltFrame;

    typedef enum MagCaliStatus {
        NOT_STARTED = 0,
        WAITING_TO_START = 1,
        RUNNING_STEP_ONE = 2,
        RUNNING_STEP_TWO = 3,
        SUCCESS = 4,
        FAILED = 5,
        BAD_ORIENTATION = 6,
        BAD_RADIUS = 7,
    }MagCaliStatus;

    typedef enum MAV_MISSION_RESULT
    {
       MAV_MISSION_ACCEPTED=0,              /* mission accepted OK | */
       MAV_MISSION_ERROR=1,                 /* Generic error / not accepting mission commands at all right now. | */
       MAV_MISSION_UNSUPPORTED_FRAME=2,     /* Coordinate frame is not supported. | */
       MAV_MISSION_UNSUPPORTED=3,           /* Command is not supported. | */
       MAV_MISSION_NO_SPACE=4,              /* Mission items exceed storage space. | */
       MAV_MISSION_INVALID=5,               /* One of the parameters has an invalid value. | */
       MAV_MISSION_INVALID_PARAM1=6,        /* param1 has an invalid value. | */
       MAV_MISSION_INVALID_PARAM2=7,        /* param2 has an invalid value. | */
       MAV_MISSION_INVALID_PARAM3=8,        /* param3 has an invalid value. | */
       MAV_MISSION_INVALID_PARAM4=9,        /* param4 has an invalid value. | */
       MAV_MISSION_INVALID_PARAM5_X=10,     /* x / param5 has an invalid value. | */
       MAV_MISSION_INVALID_PARAM6_Y=11,     /* y / param6 has an invalid value. | */
       MAV_MISSION_INVALID_PARAM7=12,       /* z / param7 has an invalid value. | */
       MAV_MISSION_INVALID_SEQUENCE=13,     /* Mission item received out of sequence | */
       MAV_MISSION_DENIED=14,               /* Not accepting any mission commands from this communication partner. | */
       MAV_MISSION_OPERATION_CANCELLED=15,  /* Current mission operation cancelled (e.g. mission upload, mission download). | */
       MAV_MISSION_RESULT_ENUM_END=16,      /*  | */
    } MAV_MISSION_RESULT;
     enum SerialProtocol {
        SerialProtocol_None = -1,
        SerialProtocol_Console = 0, // unused
        SerialProtocol_MAVLink = 1,
        SerialProtocol_MAVLink2 = 2,                 // do not use - use MAVLink and provide instance of 1
        SerialProtocol_FrSky_D = 3,                  // FrSky D protocol (D-receivers)
        SerialProtocol_FrSky_SPort = 4,              // FrSky SPort protocol (X-receivers)
        SerialProtocol_GPS = 5,
        SerialProtocol_GPS2 = 6,                     // do not use - use GPS and provide instance of 1
        SerialProtocol_AlexMos = 7,
        SerialProtocol_Gimbal = 8,                   // SToRM32, Siyi custom serial protocols
        SerialProtocol_Rangefinder = 9,
        SerialProtocol_FrSky_SPort_Passthrough = 10, // FrSky SPort Passthrough (OpenTX) protocol (X-receivers)
        SerialProtocol_Lidar360 = 11,                // Lightware SF40C, TeraRanger Tower or RPLidarA2
        SerialProtocol_Aerotenna_USD1      = 12, // USD1 support - deprecated, users should use Rangefinder
        SerialProtocol_Beacon = 13,
        SerialProtocol_Volz = 14,                    // Volz servo protocol
        SerialProtocol_Sbus1 = 15,
        SerialProtocol_ESCTelemetry = 16,
        SerialProtocol_Devo_Telem = 17,
        SerialProtocol_OpticalFlow = 18,
        SerialProtocol_Robotis = 19,
        SerialProtocol_NMEAOutput = 20,
        SerialProtocol_WindVane = 21,
        SerialProtocol_SLCAN = 22,
        SerialProtocol_RCIN = 23,
        SerialProtocol_EFI = 24,                   // EFI serial protocol
        SerialProtocol_LTM_Telem = 25,
        SerialProtocol_RunCam = 26,
        SerialProtocol_Hott = 27,
        SerialProtocol_Scripting = 28,
        SerialProtocol_CRSF = 29,
        SerialProtocol_Generator = 30,
        SerialProtocol_Winch = 31,
        SerialProtocol_MSP = 32,
        SerialProtocol_DJI_FPV = 33,
        SerialProtocol_AirSpeed = 34,
        SerialProtocol_ADSB = 35,
        SerialProtocol_AHRS = 36,
        SerialProtocol_SmartAudio = 37,
        SerialProtocol_FETtecOneWire = 38,
        SerialProtocol_Torqeedo = 39,
        SerialProtocol_AIS = 40,
        SerialProtocol_CoDevESC = 41,
        SerialProtocol_MSP_DisplayPort = 42,
        SerialProtocol_MAVLinkHL = 43,
        SerialProtocol_Tramp = 44,
        SerialProtocol_DDS_XRCE = 45,
        SerialProtocol_IMUOUT = 46,
        // Reserving Serial Protocol 47 for SerialProtocol_IQ
        SerialProtocol_PPP = 48,
        SerialProtocol_FlyLink = 49,
        SerialProtocol_NumProtocols                    // must be the last value
    };
    typedef enum{
        Frame_UNDIFINE = 0,
        //=================四旋翼=====================
        // ardupilot
        FrameQuad_Plus,
        FrameQuad_X,
        FrameQuad_NYT_PLUS,
        FrameQuad_NYT_NYT_X,
        FrameQuad_BF_X,
        FrameQuad_BF_X_REV,
        FrameQuad_DJI_X,
        FrameQuad_CW_X,
        FrameQuad_V,
        FrameQuad_H,
        FrameQuad_VTAIL,
        FrameQuad_ATAIL,
        FrameQuad_PLUSREV,
        //======================六旋翼==================
        // ardupilot
        FrameHex_PLUS ,
        FrameHex_X ,
        FrameHex_H  ,
        FrameHex_DJI_X,
        FrameHex_CW_X,
        //======================8旋翼==================
        // ardupilot
        FrameOctA_PLUS,
        FrameOctA_X,
        FrameOctA_V,
        FrameOctA_H,
        FrameOctA_I,
        FrameOctA_DJI_X,
        FrameOctA_CW_X,
        //======================4轴8桨==================
        // ardupilot
        FrameOctAQuad_PLUS,
        FrameOctAQuad_X,
        FrameOctAQuad_V,
        FrameOctAQuad_H,
        FrameOctAQuad_CW_X,
        //======================6轴12桨==================
        // ardupilot
        FrameDodecaHexA_PLUS,
        FrameDodecaHexA_X,
        //======================Y6 3轴6桨 ==================
        // ardupilot
        FrameY6_Y6B,
        FrameY6_Y6F,
        FrameY6_Y6,
        //======================12旋翼 ==================
        // ardupilot
        FrameDecA_PLUS,
        FrameDecA_X,
        //======================自定义构型 ==================
        /* 四旋翼 USER Frame */
        FrameQuad_User_X4,
        FrameQuad_User_X4R,
        FrameQuad_User_I4,
        FrameQuad_User_I4R,
        FrameQuad_User_H4,
        /* 六旋翼 USER Frame */
        FrameHex_User_I6R,
        FrameHex_User_I6,
        FrameHex_User_V6,
        FrameHex_User_V6R,
        /* 8旋翼 USER Frame */
        FrameOctA_User_I8,
        FrameOctA_User_I8R,
        FrameOctA_User_O8,
        FrameOctA_User_O8R,
        /* 4轴8桨 USER Frame */
        FrameOctAQuad_User_X8,
        FrameOctAQuad_User_X8R,
        FrameOctAQuad_User_X8CRP,
        FrameOctAQuad_User_IX8,
        FrameOctAQuad_User_IX8R,
        /* Y6 3轴6桨 USER Frame */
        FrameY6_User_Y6,
        FrameY6_User_Y6R,
        FrameY6_User_IY6,
        FrameY6_User_IY6R,
        /* 6轴12桨 USER Frame */
        FrameDodecaHexA_User_I12R,
        FrameDodecaHexA_User_I12,
        FrameDodecaHexA_User_X12,
        FrameDodecaHexA_User_X12R,
        FrameDodecaHexA_User_X12CRP,
        FrameEnd,
    }Copter_Frame_e;

    typedef enum {
        STABILIZE =     0,  // manual airframe angle with manual throttle
        ACRO =          1,  // manual body-frame angular rate with manual throttle
        ALT_HOLD =      2,  // manual airframe angle with automatic throttle
        AUTO =          3,  // fully automatic waypoint control using mission commands
        GUIDED =        4,  // fully automatic fly to coordinate or fly at velocity/direction using GCS immediate commands
        LOITER =        5,  // automatic horizontal acceleration with automatic throttle
        RTL =           6,  // automatic return to launching point
        CIRCLE =        7,  // automatic circular flight with automatic throttle
        LAND =          9,  // automatic landing with horizontal position control
        DRIFT =        11,  // semi-autonomous position, yaw and throttle control
        SPORT =        13,  // manual earth-frame angular rate control with manual throttle
        FLIP =         14,  // automatically flip the vehicle on the roll axis
        AUTOTUNE =     15,  // automatically tune the vehicle's roll and pitch gains
        POSHOLD =      16,  // automatic position hold with manual override, with automatic throttle
        BRAKE =        17,  // full-brake using inertial/GPS system, no pilot input
        THROW =        18,  // throw to launch mode using inertial/GPS system, no pilot input
        AVOID_ADSB =   19,  // automatic avoidance of obstacles in the macro scale - e.g. full-sized aircraft
        GUIDED_NOGPS = 20,  // guided mode but only accepts attitude and altitude
        SMART_RTL =    21,  // SMART_RTL returns to home by retracing its steps
        FLOWHOLD  =    22,  // FLOWHOLD holds position with optical flow without rangefinder
        FOLLOW    =    23,  // follow attempts to follow another vehicle or ground station
        ZIGZAG    =    24,  // ZIGZAG mode is able to fly in a zigzag manner with predefined point A and point B
        SYSTEMID  =    25,  // System ID mode produces automated system identification signals in the controllers
        AUTOROTATE =   26,  // Autonomous autorotation
        TRACK_ATTACK = 30,  // TRACK_ATTACK
    }flightmode_e;

     enum PlaneModeNumber : uint8_t {
             PLANE_MANUAL        = 0,
             PLANE_CIRCLE        = 1,
             PLANE_STABILIZE     = 2,
             PLANE_TRAINING      = 3,
             PLANE_ACRO          = 4,
             PLANE_FLY_BY_WIRE_A = 5,
             PLANE_FLY_BY_WIRE_B = 6,
             PLANE_CRUISE        = 7,
             PLANE_AUTOTUNE      = 8,
             PLANE_AUTO          = 10,
             PLANE_RTL           = 11,
             PLANE_LOITER        = 12,
             PLANE_TAKEOFF       = 13,
             PLANE_AVOID_ADSB    = 14,
             PLANE_GUIDED        = 15,
             PLANE_INITIALISING  = 16,
             QSTABILIZE    = 17,
             QHOVER        = 18,
             QLOITER       = 19,
             QLAND         = 20,
             QRTL          = 21,
             QAUTOTUNE     = 22,
             QACRO         = 23,
             PLANE_THERMAL       = 24,
             LOITER_ALT_QLAND = 25,
         };
    typedef enum  {
        MOTOR_FRAME_UNDEFINED =         0,
        MOTOR_FRAME_QUAD =              1,
        MOTOR_FRAME_HEXA =              2,
        MOTOR_FRAME_OCTA =              3,
        MOTOR_FRAME_OCTAQUAD =          4,
        MOTOR_FRAME_Y6 =                5,
        MOTOR_FRAME_HELI =              6,
        MOTOR_FRAME_TRI =               7,
        MOTOR_FRAME_SINGLE =            8,
        MOTOR_FRAME_COAX =              9,
        MOTOR_FRAME_TAILSITTER =        10,
        MOTOR_FRAME_HELI_DUAL =         11,
        MOTOR_FRAME_DODECAHEXA =        12,
        MOTOR_FRAME_HELI_QUAD =         13,
        MOTOR_FRAME_DECA =              14,
        MOTOR_FRAME_SCRIPTING_MATRIX =  15,
        MOTOR_FRAME_6DOF_SCRIPTING =    16,
    }motor_frame_class;
    typedef enum  {
        MOTOR_FRAME_TYPE_PLUS =     0,
        MOTOR_FRAME_TYPE_X =        1,
        MOTOR_FRAME_TYPE_V =        2,
        MOTOR_FRAME_TYPE_H =        3,
        MOTOR_FRAME_TYPE_VTAIL =    4,
        MOTOR_FRAME_TYPE_ATAIL =    5,
        MOTOR_FRAME_TYPE_PLUSREV =  6,  // plus with reversed motor direction
        MOTOR_FRAME_TYPE_Y6B =      10,
        MOTOR_FRAME_TYPE_Y6F =      11, // for FireFlyY6
        MOTOR_FRAME_TYPE_BF_X =     12, // X frame, betaflight ordering
        MOTOR_FRAME_TYPE_DJI_X =    13, // X frame, DJI ordering
        MOTOR_FRAME_TYPE_CW_X =     14, // X frame, clockwise ordering
        MOTOR_FRAME_TYPE_I =        15, // (sideways H) octo only
        MOTOR_FRAME_TYPE_NYT_PLUS = 16, // plus frame, no differential torque for yaw
        MOTOR_FRAME_TYPE_NYT_X =    17, // X frame, no differential torque for yaw
        MOTOR_FRAME_TYPE_BF_X_REV = 18, // X frame, betaflight ordering, reversed motors

         // User Order
         MOTOR_FRAME_TYPE_USER_H = 30,       // X frame, XYFly Ordering
         MOTOR_FRAME_TYPE_USER_X = 31,       // X frame, XYFly Ordering
         MOTOR_FRAME_TYPE_USER_CW_X = 32,    // X CW frame, XYFly Ordering
         MOTOR_FRAME_TYPE_USER_PLUS = 33,    // + frame, XYFly Ordering
         MOTOR_FRAME_TYPE_USER_CW_PLUS = 34, // + CW frame, XYFly Ordering
    }motor_frame_type;

    enum Rotation : uint8_t {
        ROTATION_NONE                = 0,
        ROTATION_YAW_45              = 1,
        ROTATION_YAW_90              = 2,
        ROTATION_YAW_135             = 3,
        ROTATION_YAW_180             = 4,
        ROTATION_YAW_225             = 5,
        ROTATION_YAW_270             = 6,
        ROTATION_YAW_315             = 7,
        ROTATION_ROLL_180            = 8,
        ROTATION_ROLL_180_YAW_45     = 9,
        ROTATION_ROLL_180_YAW_90     = 10,
        ROTATION_ROLL_180_YAW_135    = 11,
        ROTATION_PITCH_180           = 12,
        ROTATION_ROLL_180_YAW_225    = 13,
        ROTATION_ROLL_180_YAW_270    = 14,
        ROTATION_ROLL_180_YAW_315    = 15,
        ROTATION_ROLL_90             = 16,
        ROTATION_ROLL_90_YAW_45      = 17,
        ROTATION_ROLL_90_YAW_90      = 18,
        ROTATION_ROLL_90_YAW_135     = 19,
        ROTATION_ROLL_270            = 20,
        ROTATION_ROLL_270_YAW_45     = 21,
        ROTATION_ROLL_270_YAW_90     = 22,
        ROTATION_ROLL_270_YAW_135    = 23,
        ROTATION_PITCH_90            = 24,
        ROTATION_PITCH_270           = 25,
        ROTATION_PITCH_180_YAW_90    = 26,
        ROTATION_PITCH_180_YAW_270   = 27,
        ROTATION_ROLL_90_PITCH_90    = 28,
        ROTATION_ROLL_180_PITCH_90   = 29,
        ROTATION_ROLL_270_PITCH_90   = 30,
        ROTATION_ROLL_90_PITCH_180   = 31,
        ROTATION_ROLL_270_PITCH_180  = 32,
        ROTATION_ROLL_90_PITCH_270   = 33,
        ROTATION_ROLL_180_PITCH_270  = 34,
        ROTATION_ROLL_270_PITCH_270  = 35,
        ROTATION_ROLL_90_PITCH_180_YAW_90 = 36,
        ROTATION_ROLL_90_YAW_270     = 37,
        ROTATION_ROLL_90_PITCH_68_YAW_293 = 38,
        ROTATION_PITCH_315           = 39,
        ROTATION_ROLL_90_PITCH_315   = 40,
        ROTATION_PITCH_7             = 41,
        ///////////////////////////////////////////////////////////////////////
        // Do not add more rotations without checking that there is not a conflict
        // with the MAVLink spec. MAV_SENSOR_ORIENTATION is expected to match our
        // list of rotations here. If a new rotation is added it needs to be added
        // to the MAVLink messages as well.
        ///////////////////////////////////////////////////////////////////////
        ROTATION_MAX,
        ROTATION_CUSTOM              = 100,
    };

    enum e_PayloadType : uint8_t {
        PayloadType_General = 0,
        PayloadType_YJYVedioControl,
    };

    typedef enum MAV_SYS_STATUS_SENSOR
    {
       MAV_SYS_STATUS_SENSOR_3D_GYRO=1, /* 0x01 3D gyro | */
       MAV_SYS_STATUS_SENSOR_3D_ACCEL=2, /* 0x02 3D accelerometer | */
       MAV_SYS_STATUS_SENSOR_3D_MAG=4, /* 0x04 3D magnetometer | */
       MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE=8, /* 0x08 absolute pressure | */
       MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE=16, /* 0x10 differential pressure | */
       MAV_SYS_STATUS_SENSOR_GPS=32, /* 0x20 GPS | */
       MAV_SYS_STATUS_SENSOR_OPTICAL_FLOW=64, /* 0x40 optical flow | */
       MAV_SYS_STATUS_SENSOR_VISION_POSITION=128, /* 0x80 computer vision position | */
       MAV_SYS_STATUS_SENSOR_LASER_POSITION=256, /* 0x100 laser based position | */
       MAV_SYS_STATUS_SENSOR_EXTERNAL_GROUND_TRUTH=512, /* 0x200 external ground truth (Vicon or Leica) | */
       MAV_SYS_STATUS_SENSOR_ANGULAR_RATE_CONTROL=1024, /* 0x400 3D angular rate control | */
       MAV_SYS_STATUS_SENSOR_ATTITUDE_STABILIZATION=2048, /* 0x800 attitude stabilization | */
       MAV_SYS_STATUS_SENSOR_YAW_POSITION=4096, /* 0x1000 yaw position | */
       MAV_SYS_STATUS_SENSOR_Z_ALTITUDE_CONTROL=8192, /* 0x2000 z/altitude control | */
       MAV_SYS_STATUS_SENSOR_XY_POSITION_CONTROL=16384, /* 0x4000 x/y position control | */
       MAV_SYS_STATUS_SENSOR_MOTOR_OUTPUTS=32768, /* 0x8000 motor outputs / control | */
       MAV_SYS_STATUS_SENSOR_RC_RECEIVER=65536, /* 0x10000 rc receiver | */
       MAV_SYS_STATUS_SENSOR_3D_GYRO2=131072, /* 0x20000 2nd 3D gyro | */
       MAV_SYS_STATUS_SENSOR_3D_ACCEL2=262144, /* 0x40000 2nd 3D accelerometer | */
       MAV_SYS_STATUS_SENSOR_3D_MAG2=524288, /* 0x80000 2nd 3D magnetometer | */
       MAV_SYS_STATUS_GEOFENCE=1048576, /* 0x100000 geofence | */
       MAV_SYS_STATUS_AHRS=2097152, /* 0x200000 AHRS subsystem health | */
       MAV_SYS_STATUS_TERRAIN=4194304, /* 0x400000 Terrain subsystem health | */
       MAV_SYS_STATUS_REVERSE_MOTOR=8388608, /* 0x800000 Motors are reversed | */
       MAV_SYS_STATUS_LOGGING=16777216, /* 0x1000000 Logging | */
       MAV_SYS_STATUS_SENSOR_BATTERY=33554432, /* 0x2000000 Battery | */
       MAV_SYS_STATUS_SENSOR_PROXIMITY=67108864, /* 0x4000000 Proximity | */
       MAV_SYS_STATUS_SENSOR_SATCOM=134217728, /* 0x8000000 Satellite Communication  | */
       MAV_SYS_STATUS_PREARM_CHECK=268435456, /* 0x10000000 pre-arm check status. Always healthy when armed | */
       MAV_SYS_STATUS_OBSTACLE_AVOIDANCE=536870912, /* 0x20000000 Avoidance/collision prevention | */
       MAV_SYS_STATUS_SENSOR_PROPULSION=1073741824, /* 0x40000000 propulsion (actuator, esc, motor or propellor) | */
       MAV_SYS_STATUS_SENSOR_ENUM_END=1073741825, /*  | */
    } MAV_SYS_STATUS_SENSOR;
    typedef enum{
        TYPE_RETURN_WAYPOINT = 1,
    }waypoint_type;

    enum TAKEOFF_ACTION{
        TAKEOFF_ACTION_NONE = 0,
        TAKEOFF_ACTION_RTL,
        TAKEOFF_ACTION_MISSION,
    };
/*=======================================================================*/
#pragma pack(push)
#pragma pack (1)    //单字节对齐
/*=================== 数据结构定义，详细请参照协议文档 ====================*/
    typedef struct{
        uint8_t  frame;
        uint8_t  flight_mode;
        union{
            struct{
                uint8_t armed:1;
                uint8_t isflying:1;
            }state;
            uint8_t reserve;
        }state1;
        uint8_t  CPULoad;
        uint32_t time_sinceboot_s;
        uint32_t flight_time_s;
        uint32_t total_flight_time_s;
        uint32_t flight_dis_m;
        uint32_t total_flight_dis_m;
        uint16_t boot_cnt;
        uint16_t Battery_voltage_mv; // mV
        uint16_t Battery_Current_CA; // A*100
         int8_t  throttle;
        int16_t  temperture;         // ℃*100
        union{
            uint32_t reserves;
            struct{
                uint32_t arm_check:1;
                uint32_t acc:1;
                uint32_t gyro:1;
                uint32_t mag:1;
                uint32_t baro:1;
                uint32_t airspeed:1;
                uint32_t GNSS:1;
                uint32_t INS:1;
                uint32_t AHRS:1;
                uint32_t RC:1;
                uint32_t datalink:1;
                uint32_t motor:1;
                uint32_t datalog:1;
                uint32_t power:1;
                uint32_t vibration:1;
                uint32_t GuidanceDevice:1;
            }state;
        }sensor_state;
        uint32_t control_sensors_present;
        uint32_t control_sensors_enabled;
        uint32_t control_sensors_health;
        uint16_t home_dist_m;
        uint16_t home_bearing_cd;
        uint16_t wp_dist_m;
        float    alt_error;      /*< [m] Current altitude error*/
        float    xtrack_error;   /*< [m] Current crosstrack error on x-y plane*/
    }SysInfo_t;

    typedef struct{
        // 欧拉角
        int16_t  roll_cd;
        int16_t  pitch_cd;
        uint16_t yaw_cd;         //0~36000

        float    acc_mpss[3];
        float    gyro_dps[3];
        int32_t  lat;
        int32_t  lng;
        float    alt_m;
        float    pos_m[3];       // ENU
        int16_t  vel_cmps[3];    // ENU
        float    airSpeed;
        uint16_t wind_dir;
        int16_t  wind_spd; //cm/s
        int16_t  wind_spd_z;//cm/s
        float         baro_alt_m;
    }vehicle_t;

    typedef struct{
        uint8_t         index;
        float           volt;
        float           current;
        int16_t         temperature;
        float           rpm;
    }ESC_t;

    typedef struct{
        uint8_t  index;
        uint8_t  fix_type;       /*<  GPS fix type.*/
        uint8_t  num_sats;       /*<  Number of satellites visible. If unknown, set to 255*/
        int32_t  lat;            /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
        int32_t  lon;            /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
        float    alt_m;
        uint16_t hdop_cm;        ///< 3D velocity RMS accuracy estimate in cm/s
        uint16_t vdop_cm;        ///< horizontal RMS accuracy estimate in cm
        float           yaw;
        float           yaw_accuracy;
        uint32_t        yaw_lagged_timestamp;
        uint16_t speed_accuracy_cmps;///< 3D velocity RMS accuracy estimate in cm/s

    }GNSS_t;

    typedef struct{
        uint8_t  index;
        float    acc_mpss[3];
        float    gyro_dps[3];
        uint8_t  vibrations[3];
        int16_t  temperture;     // ℃*100
        uint16_t clips;
    }IMU_t;

    typedef struct{
        uint8_t  index;
        float    mag_mG[3];          // 单位：mGs
    }Compass_t;

    typedef struct{
        uint8_t  index;
        float    Press_Pa;           // 单位：Pa
        int16_t  temperture;         // ℃*100
        uint8_t  air_density_ratio;  // *100
    }Baro_t;

    typedef struct{
        uint16_t rc[16];                 // us
        uint16_t out[16];                // us
    }RC_OUT_t;

    typedef struct{
        uint16_t MissionID;
        int32_t  TargetLat;
        int32_t  TargetLng;
        float    TargetASL_m;
        float    TargetAlt_m;
        float    DesiredAlt_m;
        int16_t  TargetVel_e_cmps;
        int16_t  TargetVel_n_cmps;
        int16_t  TargetVel_u_cmps;
        int16_t  NavRoll_cd;
        int16_t  NavPitch_cd;
        uint16_t NavYaw_cd;
        float    TargetAcc_mpss[3];
        float    TargetGyro_dps[3];
    }Control_target_t;
    typedef struct {
        int32_t  latitude;           /*< [degE7] Latitude (WGS84)*/
        int32_t  longitude;          /*< [degE7] Longitude (WGS84)*/
        float    alt_m;              /*< [m] Altitude (MSL). Positive for up.*/
    }waypoint_t;
    typedef struct{
        int32_t  latitude;           /*< [degE7] Latitude (WGS84)*/
        int32_t  longitude;          /*< [degE7] Longitude (WGS84)*/
        float    alt_m;              /*< [m] Altitude (MSL). Positive for up.*/
        uint8_t  alt_frame;          /* ABSOLUTE = 0, ABOVE_HOME = 1,ABOVE_ORIGIN = 2, ABOVE_TERRAIN = 3 */
        int16_t  radius;
    } guided_nav_wp_t;

    typedef struct {
        float           val[2];
    } extVoltage_t;

    typedef struct {
        int        val[2];
    } RPMInfo_t;

    typedef struct {
        uint8_t  severity;
        char     text[52];
    }status_text_t;

    typedef struct {
        uint16_t seq;                /*<  Waypoint ID (sequence number). Starts at zero. Increases monotonically for each waypoint, no gaps in the sequence (0,1,2,3,4).*/
        uint16_t command;            /*<  The scheduled action for the waypoint.*/
        float    param1;             /*<  PARAM1, see MAV_CMD enum*/
        float    param2;             /*<  PARAM2, see MAV_CMD enum*/
        float    param3;             /*<  PARAM3, see MAV_CMD enum*/
        float    param4;             /*<  PARAM4, see MAV_CMD enum*/
        int32_t  x;                  /*<  PARAM5 / local: x position in meters * 1e4, global: latitude in degrees * 10^7*/
        int32_t  y;                  /*<  PARAM6 / y position: local: x position in meters * 1e4, global: longitude in degrees *10^7*/
        float    z;                  /*<  PARAM7 / z position: global: altitude in meters (relative or absolute, depending on frame.*/
        uint8_t  frame;              /*<  The coordinate system of the waypoint.*/
    }mission_item_t;

    typedef struct {
        uint8_t         type;       /*< 1:返航点 >*/
        int32_t         x;          /* <  PARAM5 / local: x position in meters * 1e4, global: latitude in degrees * 10^7*/
        int32_t         y;          /*<  PARAM6 / y position: local: x position in meters * 1e4, global: longitude in degrees *10^7*/
        float           z;          /*< 返航点使用相对高度 >*/
        uint8_t         frame;      /*<  The coordinate system of the waypoint.*/
        int16_t         radius;
    } waypoint_new_t;

    typedef struct {
        uint8_t         WorkState;
        int8_t          PitchErr;
        int8_t          YawErr;
        uint8_t         TrackingResponsivity;
    } GuidanceDeviceInfo_t;
    typedef struct
    {
        /* data */
        uint8_t  header_x;
        uint8_t  header_y;
        uint8_t  sys_id;
        uint8_t  msg_seq;
        uint8_t  msg_id;
        uint8_t  datalen;
        uint8_t* dataptr;
        uint8_t  checksum;
    }FlyLink_RevMSG;

    /*--------------指令设置用参数结构体定义----------------*/
    typedef enum
    {
       MAV_RESULT_ACCEPTED=0,               /* Command is valid (is supported and has valid parameters), and was executed. | */
       MAV_RESULT_TEMPORARILY_REJECTED=1,   /* Command is valid, but cannot be executed at this time. This is used to indicate a problem that should be fixed just by waiting (e.g. a state machine is busy, can't arm because have not got GPS lock, etc.). Retrying later should work. | */
       MAV_RESULT_DENIED=2,                 /* Command is invalid (is supported but has invalid parameters). Retrying same command and parameters will not work. | */
       MAV_RESULT_UNSUPPORTED=3,            /* Command is not supported (unknown). | */
       MAV_RESULT_FAILED=4,                 /* Command is valid, but execution has failed. This is used to indicate any non-temporary or unexpected problem, i.e. any problem that must be fixed before the command can succeed/be retried. For example, attempting to write a file when out of memory, attempting to arm when sensors are not calibrated, etc. | */
       MAV_RESULT_IN_PROGRESS=5,            /* Command is valid and is being executed. This will be followed by further progress updates, i.e. the component may send further COMMAND_ACK messages with result MAV_RESULT_IN_PROGRESS (at a rate decided by the implementation), and must terminate by sending a COMMAND_ACK message with final result of the operation. The COMMAND_ACK.progress field can be used to indicate the progress of the operation. There is no need for the sender to retry the command, but if done during execution, the component will return MAV_RESULT_IN_PROGRESS with an updated progress. | */
       MAV_RESULT_ENUM_END=6,               /*  | */
    } MAV_RESULT;
    typedef enum {
        FlyLink_CMD_ID_SetMode = 1,
        FlyLink_CMD_ID_ArmMotors                ,
        FlyLink_CMD_ID_Takeoff                  ,
        FlyLink_CMD_ID_Request_Home             ,
        FlyLink_CMD_ID_Request_Origin           ,
        FlyLink_CMD_ID_Change_Alt               ,
        FlyLink_CMD_ID_Change_Heading           ,
        FlyLink_CMD_ID_Factory                  ,
        FlyLink_CMD_ID_Restart                  ,
        FlyLink_CMD_ID_Motor_test               ,
        FlyLink_CMD_ID_StartMission             ,
        FlyLink_CMD_ID_ChangeMissionItem        ,
        FlyLink_CMD_ID_Calibration              ,
        FlyLink_CMD_ID_ReqMSG                   ,
        FlyLink_CMD_ID_FlashBootloader          ,
        FlyLink_CMD_ID_WriteSN                  ,
        FlyLink_CMD_ID_ReqRTLWP                 ,
        FlyLink_CMD_ID_Land                     ,
        FlyLink_CMD_ID_GoAround                 ,
    }command_id_e;
    struct  CMD_setmode{
        uint8_t  number;                 // 飞行模式number
        VehicleType_e type;
    };

    // 0:锁定，1：解锁 2：强制锁定 3：强制解锁
    enum  CMD_setMotorArmed{
        ARM_MOTERS = 0,
        DISARM_MOTORS,
        ARM_MOTERS_FORCE,
        DISARM_MOTORS_FORCE,
    };

    struct  CMD_Takeoff{
        float  alt_m;
    };

    struct  CMD_SetAlt{
        float  alt_m;
    };

    struct  CMD_SetHeading{
        float  heading;
    };

    struct  CMD_SetMotors{
        uint8_t  id;
        uint8_t  num;
        uint8_t  time;
        uint8_t  pct;
        uint8_t  esc_cali;
    };
    enum  CMD_SetESCCali{
        ESC_Cali_None = 0,
        ESC_Cali_Stop = 1,
        ESC_Cali_Start,
        ESC_Cali_shift,
    };

    struct CMD_StartMission{
        uint8_t  is_resume;
    };

    struct CMD_ChangeMissionCmd{
        uint16_t id;
    };

    typedef enum{
        CMD_ACC_CALITYPE_3D,
        CMD_ACC_CALITYPE_TRIM,
        CMD_ACC_CALITYPE_SIMPLE,
        CMD_CALITYPE_BARO,
        CMD_CALITYPE_GYRO,
        CMD_CALITYPE_Airspeed,
        CMD_CALITYPE_Compass,
        CMD_CALITYPE_CompassInFlight,
        CMD_CALITYPE_CompassSimple,
    }cali_type_e;
    typedef enum {
        CMD_ACC_CALISTEP_Start,
        CMD_ACC_CALISTEP_Cancel,
        CMD_ACC_CALISTEP_Next,
    }cali_Step_e;
    typedef enum{
        ACCELCAL_POS_LEVEL = 1,
        ACCELCAL_POS_LEFT,
        ACCELCAL_POS_RIGHT,
        ACCELCAL_POS_NOSEDOWN,
        ACCELCAL_POS_NOSEUP,
        ACCELCAL_POS_BACK,
        ACCELCAL_POS_SUCCESS,
        ACCELCAL_POS_FAILED,
        ACCELCAL_POS_ENUM_END
    }acc_cali_pos_e;

    struct CMD_ACC3DCalibration{
        uint8_t CaliType;
        uint8_t CaliStep;
        uint16_t param_val;
    };
    struct CMD_RewMsg{
        uint8_t id;
    };
    struct CMD_SetSn{
        uint32_t             SN;
    };
    struct CMD_PlaneTakeoff{
        uint8_t ACTION;
    };
    typedef  struct
    {
        uint8_t  cmd_id;
        union
        {
            uint8_t              val[5];
            CMD_setmode          mode;
            CMD_setMotorArmed    arm;
            CMD_Takeoff          takeoff;
            CMD_SetAlt           setAlt;
            CMD_SetHeading       setHeading;
            CMD_SetMotors        SetMotors;
            CMD_SetESCCali       SetESCCali;
            CMD_StartMission     StartMission;
            CMD_ChangeMissionCmd ChangeMissionItem;
            CMD_ACC3DCalibration Calibration;
            CMD_RewMsg           ReqMsg;
            CMD_SetSn            SN;
            CMD_PlaneTakeoff     p_takeoff;
        }param;
    }Command_t;
    typedef  struct
    {
        uint8_t  cmd_id;
        uint8_t  ack;
    }Command_ack_t;

    typedef struct{
        int16_t     param_index;    /*<   值不为-1，则以index为准 */
        char        param_name[17]; /*<  */
    } CommonParamReq_t;

    typedef struct {
        int16_t     param_index;    /*<  Index of this onboard parameter*/
        int16_t     param_count;    /*<  Total number of onboard parameters*/
        char        param_name[17]; /*<  Onboard parameter id, terminated by NULL if the length is less than 16 human-readable chars and WITHOUT null termination (NULL) byte if the length is exactly 16 chars - applications have to provide 16+1 bytes storage if the ID is stored as string*/
        uint8_t     param_type;     /*<  Onboard parameter type.*/
        float       param_value;    /*<  Onboard parameter value*/
    } CommonParam_t;

    typedef struct{
        uint8_t     id;
        uint8_t     cal_status;
        uint8_t     attempt;
        uint8_t     completion_pct;
        float       _fitness;
    } CompassCaliProgress_t;

    typedef struct {
        uint8_t     is_set:1;
        uint8_t     crash_enable:1;
        uint8_t     vibration_enable:1;
        uint8_t     Ekf;
        uint8_t     RC;
        uint8_t     GCS;
        uint8_t     GCS_timeout;                /*<  单位为S >*/
        uint8_t     battery_level1;
        uint8_t     battery_level2;
        uint16_t    battery_level1_voltage;     /*<  单位为V*10 >*/
        uint16_t    battery_level2_voltage;     /*<  单位为V*10 >*/
        uint16_t    batt_arm_volt;              /*<  单位为V*10 >*/
        uint16_t    _batt_voltage_max;          /*<  单位为V*10 >*/
        uint16_t    _batt_voltage_min;          /*<  单位为V*10 >*/
    }param_failsafe_t;

    typedef struct{
        uint8_t     is_set:1;
        struct{
        /*<  单位为us >*/
        uint16_t    radio_min;
        uint16_t    radio_trim;
        uint16_t    radio_max;
        uint16_t    dead_zone;
        }val[4];
    }param_MianRC;

    typedef struct{
        uint8_t     is_set:1;
        uint8_t     flight_modes_ch;
        uint8_t     flight_mode1;
        uint8_t     flight_mode2;
        uint8_t     flight_mode3;
        uint8_t     flight_mode4;
        uint8_t     flight_mode5;
        uint8_t     flight_mode6;
        int16_t     ch6_aux_fun;
        int16_t     ch7_aux_fun;
        int16_t     ch8_aux_fun;
        int16_t     ch9_aux_fun;
    }param_AuxRC;

    typedef struct {
        uint8_t     is_set:1;
        uint8_t     _spin_min;              // throttle out ratio which produces the minimum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
        uint8_t     _spin_max;              // throttle out ratio which produces the maximum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
        uint8_t     _spin_arm;              // throttle out ratio which produces the armed spin rate.  (i.e. 0 ~ 1 ) of the full throttle range
        uint16_t    _pwm_min;               // minimum PWM value that will ever be output to the motors (if 0, vehicle's throttle input channel's min pwm used)
        uint16_t    _pwm_max;               // maximum PWM value that will ever be output to the motors (if 0, vehicle's throttle input channel's max pwm used)
        uint8_t     _throttle_hover;        // estimated throttle required to hover throttle in the range 0 ~ 1
        uint8_t     _throttle_hover_learn;  // enable/disabled hover thrust learning
    }param_Motors;

    typedef struct {
        uint8_t     is_set:1;
        uint8_t     gnss_id:7;
        int16_t     pos[3];
    }param_GNSSPosition;

    typedef struct
    {
        int8_t  protocol;
        uint32_t baud;
        /* data */
    }SerialPortOption;

    typedef struct{
        uint8_t     is_set:1;
        uint8_t     count:7;              // throttle out ratio which produces the minimum thrust.  (i.e. 0 ~ 1 ) of the full throttle range
        SerialPortOption    param[8];
    }param_SerialPort_t;

    typedef struct {
        uint8_t is_set;
        float acro_yaw_p;
        float atc_accel_p_max;
        float atc_accel_r_max;
        float atc_accel_y_max;
        float atc_rat_pit_fltd;
        float atc_rat_pit_flte;
        float atc_rat_pit_fltt;
        float atc_rat_rll_fltd;
        float atc_rat_rll_flte;
        float atc_rat_rll_fltt;
        float atc_rat_yaw_fltd;
        float atc_rat_yaw_flte;
        float atc_rat_yaw_fltt;
        float atc_thr_mix_man;
        float ins_accel_filter;
        float ins_gyro_filter;
        float mot_thst_expo;
    }param_initCFGparam_t;

    typedef struct {
        uint8_t     is_set;
        uint16_t    angle_max_cd;           // 手动控制最切斜角
        uint16_t    pilot_speed_up_cms;
        uint16_t    pilot_speed_dn_cms;
        uint16_t    pilot_accel_z_cmms;
        uint16_t    _speed_cms;             // maximum horizontal speed in cm/s while in loiter
        uint16_t    _accel_cmss;            // loiter's max acceleration in cm/s/s
        uint16_t    _brake_accel_cmss;      // loiter's acceleration during braking in cm/s/s
        uint16_t    _brake_jerk_max_cmsss;
        uint16_t    _brake_delay_ms;        // delay (in  m  seconds) before loiter braking begins after sticks are released
    }param_pilot_control_t;
    typedef struct {
        uint8_t     is_set;
        uint16_t    _wp_speed_cms;          // default maximum horizontal speed in cm/s during missions
        uint16_t    _wp_speed_up_cms;       // default maximum climb rate in cm/s
        uint16_t    _wp_speed_down_cms;     // default maximum descent rate in cm/s
        uint16_t    _wp_radius_cm;          // distance from a waypoint in cm that, when crossed, indicates the wp has been reached
        uint16_t    _wp_accel_cmss;          // horizontal acceleration in cm/s/s during missions
        uint16_t    _wp_accel_z_cmss;        // vertical acceleration in cm/s/s during missions
        uint16_t    land_speed;
        uint16_t    land_alt_low;            // Land alt final stage
        uint16_t    rtl_altitude;
    }param_auto_control_t;

    /*====================== MSG ID #52 ====================*/
    typedef struct {
        uint16_t    log_id;
    } log_request_list_t;

    /*====================== MSG ID #53 ====================*/
    typedef struct {
        uint32_t ofs;       /*<  Offset into the log*/
        uint8_t  count;     /*< [bytes] Number of bytes Max 128Bytes*/
        uint16_t id;        /*<  Log id (from LOG_ENTRY reply)*/
    } log_request_data_t;
    /*====================== MSG ID #54 ====================*/
    typedef struct {
        uint16_t id;        /*<  Log id*/
        uint32_t time_utc;  /*< [s] UTC timestamp of log since 1970, or 0 if not available*/
        uint32_t size;      /*< [bytes] Size of the log (may be approximate)*/
        uint16_t num_logs;  /*<  Total number of logs*/
        uint16_t last_log_num; /*<  High log number*/
    }log_info_t;
    /*====================== MSG ID #55 ====================*/
    typedef struct {
        uint16_t    id; /*<  Log id (from LOG_ENTRY reply)*/
        uint32_t    ofs; /*<  Offset into the log*/
        uint8_t     count; /*< [bytes] Number of bytes (zero for end of log)*/
        uint8_t     data[FlyLink_LOG_DataSize]; /*<  log data*/
    }log_data_t;


    typedef struct{
        uint32_t      udid[3];
        uint32_t      boardId;
        uint32_t      fw_version;
        uint16_t      link_version;
        uint32_t      total_flight_time_s;
        uint32_t      total_flight_dis_m;
        uint32_t      boardSN;
    }boardinfo_t;


    typedef struct {
        uint8_t     is_set;                 // 0:读取  1:写入
        float       _accel_max;             // Maximum rotation acceleration for earth-frame pitch axis
        float       _ang_vel_max;
        float       angle_p;
        float       rate_p;
        float       rate_i;
        float       rate_d;
        float       rate_ff;
        float       rate_imax;
        float       rate_slew_rate_max;
    }param_att_roll_control_t;
    typedef struct {
        uint8_t     is_set;                 // 0:读取  1:写入
        float       _accel_max;             // Maximum rotation acceleration for earth-frame pitch axis
        float       _ang_vel_max;
        float       angle_p;
        float       rate_p;
        float       rate_i;
        float       rate_d;
        float       rate_ff;
        float       rate_imax;
        float       rate_slew_rate_max;
    }param_att_pitch_control_t;
    typedef struct {
        uint8_t     is_set;                 // 0:读取  1:写入
        float       _accel_max;             // Maximum rotation acceleration for earth-frame pitch axis
        float       _ang_vel_max;
        float       angle_p;
        float       rate_p;
        float       rate_i;
        float       rate_d;
        float       rate_ff;
        float       rate_imax;
        float       rate_slew_rate_max;
        float       _slew_yaw;
    }param_att_yaw_control_t;

    typedef struct {
        uint8_t     is_set;                 // 0:读取  1:写入
        float       shaping_jerk;
        float       pos_p;
        float       vel_p;
        float       vel_i;
        float       vel_d;
        float       vel_ff;
        float       vel_imax;
        float       acc_p;
        float       acc_i;
        float       acc_d;
        float       acc_ff;
        float       acc_imax;
        float       acc_slew_rate_max;
    }param_posz_control_t;
    typedef struct {
        uint8_t     is_set;                 // 0:读取  1:写入
        float       shaping_jerk;
        float       pos_p;
        float       vel_p;
        float       vel_i;
        float       vel_d;
        float       vel_ff;
        float       vel_imax;
    }param_posxy_control_t;

#pragma pack(pop)//恢复对齐状态
    /*--------------协议解析基础变量----------------*/
    typedef enum
    {
        STA_WAIT_HEADER_X = 0,
        STA_WAIT_HEADER_Y,
        STA_RCV_SYS_ID,
        STA_RCV_INDEX,
        STA_RCV_MSG_ID,
        STA_RCV_DATALEN,
        STA_RCV_DATA,
        STA_RCV_CHECKSUM
    }FlyLink_status_e;
    struct {
        FlyLink_status_e  status;
        uint8_t           datacnt;
        uint8_t           datalen;
    }rev_state;

    uint8_t  sendbuf[FlyLink_MAX_BUF_LEN];
    uint8_t  revbuf [FlyLink_MAX_BUF_LEN];
    /*------------------发送相关变量----------------------*/
    typedef struct{
        qint64 last_send_ms;
        qint64 time_interval_ms;
    }send_time_t;
    uint8_t interval_mode;
    enum{
        interval_wait_active = 0, // 等待连接状态
        interval_Check_active,    // 检查连接状态，失去连接将进入WAIT_ACTIVE
        interval_General,
        interval_dbg,
        interval_mode_end
    }interval_mode_e;

    typedef struct{
        waypoint_t loc;
        bool       is_get;
    }home_origin_t;
    typedef struct{
        waypoint_new_t loc;
        bool       is_get;
    }RTL_Waypoint_t;
    /* 1000Hz */
    typedef struct{
        uint16_t    mav_version;
        SysInfo_t   tSysInfo;
        vehicle_t   tVehicle;
        ESC_t       tESC[FlyLink_MAX_ESC];
        uint8_t     ESC_count;
        GNSS_t      tGNSS[FlyLink_MAX_SensorBackend];
        uint8_t     GNSS_count;
        IMU_t       tIMU[FlyLink_MAX_SensorBackend];
        uint8_t     IMU_count;
        Compass_t   tCompass[FlyLink_MAX_SensorBackend];
        uint8_t     Compass_count;
        Baro_t      tBaro[FlyLink_MAX_SensorBackend];
        uint8_t     Baro_count;
        RC_OUT_t    tRC_OUT;
        Control_target_t tTarget;
        home_origin_t tHome;
        home_origin_t tOrigin;
        uint8_t     Acc3DCaliPostion;
        CompassCaliProgress_t   MagCaliProgress[FlyLink_MAX_SensorBackend];
        uint8_t     MagCaliCount;
        uint8_t     FrameMotorCount;
        uint8_t     BoardOrientation;
        extVoltage_t extVol;
        RPMInfo_t   RPM;
        GuidanceDeviceInfo_t GuidanceInfo;
        boardinfo_t boardinfo;
        uint8_t     VehicleType;
        bool        pos_get;
        int         mav_id;
        RTL_Waypoint_t RTL;
    }DataPort_t;

    typedef struct{
        union{
            uint32_t val;
            struct{
                uint32_t failsafe:1;
                uint32_t MainRC:1;
                uint32_t AuxRC:1;
                uint32_t Motors:1;
                uint32_t GnssPostion1:1;
                uint32_t GnssPostion2:1;
                uint32_t initCtrlCFG:1;
                uint32_t PilotCtrl:1;
                uint32_t AutoCtrl:1;
                uint32_t RollCtrl:1;
                uint32_t PitchCtrl:1;
                uint32_t YawCtrl:1;
                uint32_t PosZCtrl:1;
                uint32_t PosXYCtrl:1;
                uint32_t SerialPortOption:1;
            }UpdateFlags;
        };
        param_failsafe_t            failsafe;
        param_MianRC                MainRC;
        param_AuxRC                 AuxRC;
        param_Motors                Motors;
        param_GNSSPosition          GnssPostion[2];
        param_initCFGparam_t        initCtrlCFG;
        param_pilot_control_t       PilotCtrl;
        param_auto_control_t        AutoCtrl;
        param_att_roll_control_t    RollCtrl;
        param_att_pitch_control_t   PitchCtrl;
        param_att_yaw_control_t     YawCtrl;
        param_posz_control_t        PosZCtrl;
        param_posxy_control_t       PosXYCtrl;
        param_SerialPort_t          SerialPortOption;
    }VehicleParam_t;


    const DataPort_t& getTDataPort() const;

    typedef struct{
        QList<mission_item_t> mission;
    }mission_local_t;

    typedef struct{
        bool        is_uploading;
        qint64      time_start_upload;
        qint64      time_last_upload;
        qint64      time_last_get_request;
        uint16_t    upload_request_id;
        float       progress;
    }mission_upload_t;

    typedef struct{
        bool        is_downloading;
        qint64      time_start_download;
        qint64      time_last_request_item;
        qint64      time_last_get_item;
        qint64      time_last_request_count;
        qint64      time_last_get_count;
        uint16_t    download_request_id;
        uint16_t    download_item_count;
        float       progress;
    }mission_download_t;


    typedef struct{
        bool    is_get;
        float   value;
        uint8_t req_cnt;
    }ParameterState;

public:
    /*--------------初始化及周期调用相关函数----------------*/
    bool init();
    uint32_t get_last_rev_update_ms();
    /*--------------用于发送消息提示用----------------*/
    bool    link_is_active()const;
    uint8_t get_gcs_id() const;
    void    set_gcs_id(const uint8_t id);
    int get_mav_id() const;
    void    set_mav_id(const int id);


    static QString getCopterFlightMode(uint8_t mode);
    static QString getFlightMode(uint8_t vihecle,uint8_t mode);
    QString getVihecleFlightMode(uint8_t mode);
    QString getVihecleFlightMode();
    static QString getPlaneFlightMode(uint8_t mode);
    static QString getCopterFrame(uint8_t frame);
    static QString getGNSSFixType(uint8_t type);
    static QString getMAVResultString(uint8_t res);
    static QString getCommandString(uint8_t command);
    static uint8_t get_frame_output_count(uint8_t frame);
    static QString getBoardOrientation(uint8_t orientation);
    static QString getSerialProtocolString(int8_t protocol);
    static QString getProtocolType(uint8_t type);
    uint8_t get_frame_output_count();

    static uint32_t map_baudrate(int32_t rate);;
    bool getIs_active() const;

    /*--------------开放给用户的控制接口----------------*/
    // Copter
    bool set_mode(uint8_t mode);
    bool set_CopterMode_stabilize()   {return set_mode(STABILIZE);}
    bool set_CopterMode_alt_hold()    {return set_mode(ALT_HOLD);}
    bool set_CopterMode_loiter()      {return set_mode(LOITER);}
    bool set_CopterMode_poshold()     {return set_mode(POSHOLD);}
    bool set_CopterMode_guided()      {return set_mode(GUIDED);}
    bool set_CopterMode_rtl()         {return set_mode(RTL);}
    bool set_CopterMode_smart_rtl()   {return set_mode(SMART_RTL);}
    bool set_CopterMode_land()        {return set_mode(LAND);}
    bool set_CopterMode_auto()        {return set_mode(AUTO);}
    bool set_CopterMode_break()       {return set_mode(BRAKE);}
    bool set_CopterMode_circle()      {return set_mode(CIRCLE);}
    bool set_CopterMode_trackattack() {return set_mode(TRACK_ATTACK);}

    bool do_takeoff(float alt_m = 10.0f);
    bool do_set_alt_m(float alt_m);
    bool do_set_heading(float heading);
    bool do_startMission(bool resume);
    bool do_ChangeMissionItem(uint16_t index);

    // Plane
    bool set_PlaneMode_Manual()         {return set_mode(PLANE_MANUAL);}
    bool set_PlaneMode_Circle()         {return set_mode(PLANE_CIRCLE);}
    bool set_PlaneMode_TrainIng()       {return set_mode(PLANE_TRAINING);}
    bool set_PlaneMode_Stabilize()      {return set_mode(PLANE_STABILIZE);}
    bool set_PlaneMode_Acro()           {return set_mode(PLANE_ACRO);}
    bool set_PlaneMode_FlyByWireA()     {return set_mode(PLANE_FLY_BY_WIRE_A);}
    bool set_PlaneMode_FlyByWireB()     {return set_mode(PLANE_FLY_BY_WIRE_B);}
    bool set_PlaneMode_Cruise()         {return set_mode(PLANE_CRUISE       );}
    bool set_PlaneMode_AutoTune()       {return set_mode(PLANE_AUTOTUNE     );}
    bool set_PlaneMode_Auto()           {return set_mode(PLANE_AUTO         );}
    bool set_PlaneMode_RTL()            {return set_mode(PLANE_RTL          );}
    bool set_PlaneMode_Loiter()         {return set_mode(PLANE_LOITER       );}
    bool set_PlaneMode_Takeoff()        {return set_mode(PLANE_TAKEOFF      );}
    bool set_PlaneMode_AvoidADSB()      {return set_mode(PLANE_AVOID_ADSB   );}
    bool set_PlaneMode_Guided()         {return set_mode(PLANE_GUIDED       );}
    bool set_PlaneMode_Initialising()   {return set_mode(PLANE_INITIALISING );}
    bool set_PlaneMode_QStabilize()     {return set_mode(QSTABILIZE         );}
    bool set_PlaneMode_QHover()         {return set_mode(QHOVER             );}
    bool set_PlaneMode_QLoiter()        {return set_mode(QLOITER            );}
    bool set_PlaneMode_QLand()          {return set_mode(QLAND              );}
    bool set_PlaneMode_QRTL()           {return set_mode(QRTL               );}
    bool set_PlaneMode_QAutoTune()      {return set_mode(QAUTOTUNE          );}
    bool set_PlaneMode_QAcro()          {return set_mode(QACRO              );}
    bool set_PlaneMode_Thermal()        {return set_mode(PLANE_THERMAL      );}
    bool set_PlaneMode_Loiter_Alt_QLand(){return set_mode(LOITER_ALT_QLAND   );}
    bool do_PlaneTakeoff(uint8_t ACT);
    bool do_PlaneLand();
    bool do_PlaneGoAround(float alt = 0);

    bool do_req_RTLWaypoint();

    bool set_RTLWaypoint(waypoint_new_t& wp);



    /*--------------通用----------------*/
    bool set_motors_arm();
    bool set_motors_force_arm();
    bool set_motors_disarm();
    bool set_motors_force_disarm();

    bool request_home();
    bool request_origin();
    bool do_factory();
    bool do_reboot();
    bool do_SetBoardSN(uint32_t SN);
    bool set_guided_nav_wp(const guided_nav_wp_t& wp);


    uint8_t get_vehicle_frame();
    uint8_t get_vehicle_frame(uint8_t frame_class,uint8_t frame_type);
    bool set_vehicle_frame(const uint8_t & frame);

    bool do_FlashBootloader();
    /*--------------校准接口----------------*/
    bool do_Acc3DCaliStart();
    bool do_Acc3DCaliCancel();
    bool do_Acc3DCaliNextPostion();
    bool do_AccTrimCali();
    bool do_AccSimpleCaliStart();
    bool do_BaroCaliStart();
    bool do_AirspeedCaliStart();
    bool do_GyroCaliStart();

    /*--------------罗盘校准接口----------------*/
    bool do_MagCaliStart();
    bool do_MagCaliStop();
    bool do_MagSimpleCaliStart(uint16_t fixed_yaw);
    bool do_MagInFlightCaliStart();
    bool do_MagInFlightCaliCancel();
    /*--------------电机测试接口----------------*/
    bool do_ESCcali_start();
    bool do_ESCcali_stop();
    bool do_ESCcali_toggle();
    bool do_MotorTest_stop();
    bool do_MotorTest(uint8_t seq,uint8_t num,uint8_t time,uint8_t pct);
    /*--------------参数接口----------------*/
    bool do_reqParamAll();
    bool do_reqParamfailsafe();
    bool do_setParamfailsafe(param_failsafe_t pkt);

    bool do_reqParamMainRC();
    bool do_setParamMainRC(param_MianRC pkt);

    bool do_reqParamAuxRC();
    bool do_setParamAuxRC(param_AuxRC pkt);

    bool do_reqParamMotors();
    bool do_setParamMotors(param_Motors pkt);

    bool do_reqParamGNSSPosition();
    bool do_setParamGNSSPosition(param_GNSSPosition pkt);

    bool do_reqParamInitCtrlCfg();
    bool do_setParamInitCtrlCfg(param_initCFGparam_t pkt);

    bool do_reqParamPilotCtrl();
    bool do_setParamPilotCtrl(param_pilot_control_t pkt);

    bool do_reqParamAutoCtrl();
    bool do_setParamAutoCtrl(param_auto_control_t pkt);

    bool do_reqParamRollCtrl();
    bool do_setParamRollCtrl(param_att_roll_control_t pkt);

    bool do_reqParamPitchCtrl();
    bool do_setParamPitchCtrl(param_att_pitch_control_t pkt);

    bool do_reqParamYawCtrl();
    bool do_setParamYawCtrl(param_att_yaw_control_t pkt);

    bool do_reqParamPosZCtrl();
    bool do_setParamPosZCtrl(param_posz_control_t pkt);

    bool do_reqParamPosXYCtrl();
    bool do_setParamPosXYCtrl(param_posxy_control_t pkt);

    bool req_ParamSerialPort();
    bool do_setParamSerialPort(param_SerialPort_t pkt);

    bool send_ReqCommonParameter(CommonParamReq_t pkt);
    bool send_ReqCommonParameter(QString str);

    bool set_CommonParameter(CommonParam_t pkt);
    bool set_CommonParameter(QString str, float val);

    bool set_BoardOrientation(uint8_t Orientation);
    bool req_BoardOrientation();

    const VehicleParam_t &getTVehicleParam() const;

    bool req_boardInfo();

    // 数据透传接口
public:
    void Write_Transparent_YJYVedioControl(QByteArray arr);
private:
    void Send_Transparent_YJYVedioControl();
    void Recive_Transparent_YJYVedioControl(QByteArray arr);

    int  send_TransparentDataToFC(QByteArray arr,uint8_t Payload_type);
    void handle_Transparent(FlyLink_RevMSG msg);
    QByteArray              RXBuf_YJYVedioControl;
private:
    QMutex                  _data_mutex; // 数据发送互斥量
    uint8_t                 seq_index;
    QTimer                  timer_10hz;
    /*--------------协议建立连接基础变量----------------*/
    bool        is_active;
    uint32_t    last_rev_update_ms;
    uint8_t     _gcs_id;
    DataPort_t  tDataPort = {};
    VehicleParam_t tVehicleParam = {};
    bool        is_read = false;
    /*------------------消息提示队列----------------------*/

    /*------------------时间间隔相关变量定义----------------------*/
    send_time_t time_heartbeat = {};
    /*====== 函数列表 ======*/

    void    connectSignalAndSlot();
    /*--------------协议接收与解析输处理函数----------------*/
    uint8_t parse_char(uint8_t c);
    void    Decode(uint8_t *Buf,uint16_t u16Len);
    void    active_com(FlyLink_RevMSG msg);
    void    disactive_com(void);
    void    handle_msg(FlyLink_RevMSG msg);
    /*--------------发送函数----------------*/
    void    SendPacketByID(uint8_t u8Id , void * data, uint8_t u8DataLen);
    void    SendPacketByID(uint8_t u8Id , QByteArray data);
    bool    should_to_send(send_time_t& tTime);
    /*--------------发送函数时间间隔相关函数列表----------------*/
    bool    set_interval_mode(uint8_t mode = interval_wait_active);
    uint8_t get_interval_mode()const;
    void    update_interval_ms();
    /*--------------协议发送基础函数----------------*/
    bool    send_heartbeat();
    bool    send_command(const Command_t& cmd);
    /*--------------协议处理函数----------------*/
    void    handle_heartbeat(FlyLink_RevMSG msg);
    void    handle_command_ack(FlyLink_RevMSG msg);
    void    handle_sysinfo(FlyLink_RevMSG msg);
    void    handle_vehicle(FlyLink_RevMSG msg);
    void    handle_esc(FlyLink_RevMSG msg);
    void    handle_gnss(FlyLink_RevMSG msg);
    void    handle_imus(FlyLink_RevMSG msg);
    void    handle_compass(FlyLink_RevMSG msg);
    void    handle_baro(FlyLink_RevMSG msg);
    void    handle_rc_out(FlyLink_RevMSG msg);
    void    handle_target(FlyLink_RevMSG msg);
    void    handle_statustext(FlyLink_RevMSG msg);
    void    handle_origin(FlyLink_RevMSG msg);
    void    handle_home(FlyLink_RevMSG msg);
    void    handle_waypoint(FlyLink_RevMSG msg);
    void    handle_extVol(FlyLink_RevMSG msg);
    void    handle_RPMInfo(FlyLink_RevMSG msg);
    void    handle_GuidanceDevice(FlyLink_RevMSG msg);

    /*--------------参数解析----------------*/
    void    handle_Param_failsafe(FlyLink_RevMSG msg);
    void    handle_Param_MainRC(FlyLink_RevMSG msg);
    void    handle_Param_AuxRC(FlyLink_RevMSG msg);
    void    handle_Param_Motors(FlyLink_RevMSG msg);
    void    handle_Param_GnssPosition(FlyLink_RevMSG msg);
    void    handle_Param_InitCtrlCfg(FlyLink_RevMSG msg);
    void    handle_Param_PilotControl(FlyLink_RevMSG msg);
    void    handle_Param_AutoControl(FlyLink_RevMSG msg);
    void    handle_Param_RollControl(FlyLink_RevMSG msg);
    void    handle_Param_PitchControl(FlyLink_RevMSG msg);
    void    handle_Param_Yawontrol(FlyLink_RevMSG msg);
    void    handle_Param_PosZControl(FlyLink_RevMSG msg);
    void    handle_Param_PosXYControl(FlyLink_RevMSG msg);
    void    handle_Param_SerialPort(FlyLink_RevMSG msg);

    void    handle_BoardInfo(FlyLink_RevMSG msg);
    /*--------------日志下载----------------*/
    /*----协议层----*/
    bool    send_log_req_info(uint16_t id);
    bool    send_log_req_data(log_request_data_t datainfo);
public:
    bool    send_log_clearAll();
private:
    void    handle_log_info(FlyLink_RevMSG msg);
    void    handle_log_data(FlyLink_RevMSG msg);
    /*----应用层------------------------------*/
    /*----list----*/
    typedef struct
    {
        QList<log_info_t> log_info;
        QTimer*      timer_10Hz;
        uint32_t    loop_timer_10Hz;
        uint16_t    rx_id;        /*<  Log id*/
        uint16_t    num_logs;  /*<  Total number of logs*/
        uint16_t    last_log_num; /*<  High log number*/

    }log_list_t;

    log_list_t log_list = {};
public:
    void log_list_start();
    const QList<log_info_t> &getLog_info() const
    {
        return log_list.log_info;
    }
private:
    void log_list_stop();
    void log_list_clear();
    void log_list_insert_log_info(log_info_t &pkt);
    void log_list_handle_log_list(log_info_t & pkt);
private slots:
    void log_list_timer_callback();

    /*----data----*/
private:
    typedef struct
    {
        QTimer*      timer_10Hz;
        uint32_t    loop_timer_10Hz;
        uint16_t    rx_id; /*<  Log id (from LOG_ENTRY reply)*/
        uint32_t    ofs; /*<  Offset into the log*/
        uint32_t    size; /*< [bytes] Number of bytes (zero for end of log)*/
        QFile*      file;
    }log_file_t;
    log_file_t log_file = {};
    QList<uint16_t>  log_download_list = {};
private slots:
    bool log_file_start(uint16_t index);
    void log_file_timer_callback();
private:
    void log_file_stop();
    void log_file_handle_log_data(log_data_t & pkt);
public:
    void log_download_start();
    void log_download_do_next_start();

    bool log_download_current_state(uint16_t& index,uint32_t& size);
    void log_download_cancel_all();
    void log_download_cancel_current();
    void addDownloadIdToList(uint16_t index);
    //////////////////////////////////////////////////////////
    /*--------------协议层----------------*/
    //////////////////////////////////////////////////////////
    // 航线上传下载相关
public:
    void app_mission_upload_start();
    bool app_mission_download_start();
    const mission_download_t &getMission_download() const;
    const mission_local_t &getLocal_mission() const;
    void setLocal_mission(const mission_local_t &newLocal_mission);
    const mission_upload_t &getMission_upload() const;
    uint8_t getVehicleType() const;
    void setVehicleType(uint8_t newVehicleType);

private:
    /*--------------协议层----------------*/
    void    handle_mission_request(FlyLink_RevMSG msg);
    void    handle_mission_ack(FlyLink_RevMSG msg);
    bool    send_mission_count(uint16_t count);
    bool    send_mission_item(mission_item_t item);

    bool    send_mission_ack(uint8_t type);
    bool    send_mission_request_list();
    bool    send_mission_request(uint16_t seq);
    bool    send_mission_clear_all();
    void    handle_mission_item(FlyLink_RevMSG msg);
    void    handle_mission_count(FlyLink_RevMSG msg);

    /*-------------- 航线上传与下载应用 ----------------*/
    mission_local_t local_mission = {};
    mission_upload_t mission_upload ={};
    mission_download_t mission_download = {};
    /*-------------- 航线上传 ----------------*/
private:
    void    app_mission_upload_update();
    void    app_mission_upload_request_handle(uint16_t request_id);
    void    app_mission_upload_init();
    void    app_mission_upload_end();
    int     app_mission_item_count();
    void    app_mission_upload_handle_ack(uint8_t ack);
private:
    /*-------------- 校准相关 ----------------*/
    void    handle_Acc3DCali(FlyLink_RevMSG msg);
    void    handle_MagCaliProgress(FlyLink_RevMSG msg);
private:
    void    app_mission_download_init      ();
    void    app_mission_download_update    ();
    void    app_mission_download_end       ();

    void    app_mission_download_handle_item_count (uint16_t count);
    void    app_mission_download_handle_item       (mission_item_t item);
    /*-------------- 通用参数上传与下载 ----------------*/
private:
    void    handle_CommonParamter  (FlyLink_RevMSG msg);
    void    ResetAllVariant();
protected:
    void    DisplayMsg(const QString &str,int id = 0);
    void    DisplayGcsCMD(const QString &str,bool needuav_prev = true);

    /*-------------- 通用参数处理 ----------------*/
public:
    /* New API*/
    bool ParamGetValue_ByName(QString name,float& value,bool update = false);
    bool ParamValueClearFlags_ByName(QString name);
    bool ParamSetToFlight_ByName(QString name,const float value);
    bool ParamSetValue_ByName(QString name,const float value);

private:
    QMap<QString,ParameterState>    CommonParamMap;

    bool AllCommonParamGet = false;


    void Init_CommonParamMap();
    void Update_CommonParamMap();

    void InitParamMap();
    void Update_ParamMap();
    uint32_t    last_Update_ParamMap_ms;
};

Q_DECLARE_METATYPE(FlyLink::CommonParam_t);
#endif
#endif // FlyLink_H
