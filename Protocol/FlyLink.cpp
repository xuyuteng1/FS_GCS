/**=================================================================**
 * @brief       : FlyLink通信协议部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-01-16     Jerry.xl     the first version
 **==================================================================**/
#include "FlyLink.h"
#include "DMMM.h"
#include <QtGlobal>
#include <QDateTime>
#include <QDate>
#include <QDir>
#include <QtCore/qmath.h>
#include <QByteArray>
#include    <QFileDialog>
#include    <QTextStream>
#include    <QSettings>
#if PROTOCOL_FlyLink_ENABLED
/**===================================================================*
 * @brief      FlyLink 析构函数
 * @param      None
 * @retval     None
 **===================================================================*/
FlyLink::FlyLink(QObject *parent, uint8_t gcs_id, bool IndependentThread):
    DeviceCommunication(IndependentThread),
    _gcs_id(gcs_id)
{
    Q_UNUSED(parent);
    init();
}

FlyLink::~FlyLink()
{

}

/**===================================================================*
 * @brief      执行初始化
 * @param      None
 * @retval     None
 **===================================================================*/
bool FlyLink::init()
{
    is_active = false;
    last_rev_update_ms = 0;
    set_interval_mode(interval_wait_active);
    set_mav_id(255);
//    timer_10hz.start(100);
    connectSignalAndSlot();

    mission_item_t PKT{};
    PKT.command = 16;
    PKT.z = 100;
    PKT.x = 341527625;
    PKT.y = 1088370466;

    local_mission.mission.append(PKT);
    for(int i = 1 ; i < 1000;i++){
        PKT.x = 341527625+100*i;
        local_mission.mission.append(PKT);
    }

    RXBuf_YJYVedioControl.clear();
    InitParamMap();
    return true;
}

uint32_t FlyLink::get_last_rev_update_ms(){return last_rev_update_ms;}

bool FlyLink::link_is_active() const {return is_active;}

uint8_t FlyLink::get_gcs_id() const {return _gcs_id;}

void FlyLink::set_gcs_id(const uint8_t id){ _gcs_id = id;}

int FlyLink::get_mav_id() const {return tDataPort.mav_id;}

void FlyLink::set_mav_id(const int id)
{
    if(tDataPort.mav_id != id){
        tDataPort.mav_id = id;
        ProtocolEvent   (Q_DMMM::DMMM_GCSEvent_MavIDChanged);
    }
}

QString FlyLink::getCopterFrame(uint8_t frame)
{
    switch(frame)
    {
        case Frame_UNDIFINE :return QStringLiteral("未定义");
        //=================四旋翼=====================
        // ardupilot
        case FrameQuad_Plus         :return QStringLiteral("非官方Quad+");
        case FrameQuad_X            :return QStringLiteral("非官方QuadX");
        case FrameQuad_NYT_PLUS     :return QStringLiteral("非官方QuadNYT+");
        case FrameQuad_NYT_NYT_X    :return QStringLiteral("非官方QuadNYTX");
        case FrameQuad_BF_X         :return QStringLiteral("非官方QuadBFX");
        case FrameQuad_BF_X_REV     :return QStringLiteral("非官方QuadBFXR");
        case FrameQuad_DJI_X        :return QStringLiteral("非官方QuadDJIX");
        case FrameQuad_CW_X         :return QStringLiteral("非官方QuadXR");
        case FrameQuad_V            :return QStringLiteral("非官方QuadV");
        case FrameQuad_H            :return QStringLiteral("非官方QuadH");
        case FrameQuad_VTAIL        :return QStringLiteral("非官方QuadVTAIL");
        case FrameQuad_ATAIL        :return QStringLiteral("非官方QuadATAIL");
        case FrameQuad_PLUSREV      :return QStringLiteral("非官方Quad+R");
        //======================六旋翼==================
        // ardupilot
        case FrameHex_PLUS          :return QStringLiteral("非官方HEX+");
        case FrameHex_X             :return QStringLiteral("非官方HEX-X");
        case FrameHex_H             :return QStringLiteral("非官方HEX-H");
        case FrameHex_DJI_X         :return QStringLiteral("非官方HEX-DJI-X");
        case FrameHex_CW_X          :return QStringLiteral("非官方HEX-XR");
        //======================8旋翼=================XR
        // ardupilo
        case FrameOctA_PLUS         :return QStringLiteral("非官方OctA+");
        case FrameOctA_X            :return QStringLiteral("非官方OctA-X");
        case FrameOctA_V            :return QStringLiteral("非官方OctA-V");
        case FrameOctA_H            :return QStringLiteral("非官方OctA-H");
        case FrameOctA_I            :return QStringLiteral("非官方OctA-I");
        case FrameOctA_DJI_X        :return QStringLiteral("非官方OctA-DJI-X");
        case FrameOctA_CW_X         :return QStringLiteral("非官方OctA-XR");
        //======================4轴8桨==================
        // ardupilot
        case FrameOctAQuad_PLUS     :return QStringLiteral("非官方OctaQuad-+");
        case FrameOctAQuad_X        :return QStringLiteral("非官方OctaQuad-X");
        case FrameOctAQuad_V        :return QStringLiteral("非官方OctaQuad-V");
        case FrameOctAQuad_H        :return QStringLiteral("非官方OctaQuad-H");
        case FrameOctAQuad_CW_X     :return QStringLiteral("非官方OctaQuad-XR");
        //======================6轴12桨==================
        // ardupilot
        case FrameDodecaHexA_PLUS   :return QStringLiteral("非官方DecHex+");
        case FrameDodecaHexA_X      :return QStringLiteral("非官方DecHex-X");
        //======================Y6 3轴6桨 ==================
        // ardupilot
        case FrameY6_Y6B            :return QStringLiteral("非官方Y6B");
        case FrameY6_Y6F            :return QStringLiteral("非官方Y6F");
        case FrameY6_Y6             :return QStringLiteral("非官方Y6");
        //======================12旋翼 ==================
        // ardupilot
        case FrameDecA_PLUS         :return QStringLiteral("非官方Dec+");
        case FrameDecA_X            :return QStringLiteral("非官方Dec-X");
        //======================自定义构型 ==================
        /* 四旋翼 USER Frame */
        case FrameQuad_User_X4      :return QStringLiteral("X4 ");
        case FrameQuad_User_X4R     :return QStringLiteral("X4R");
        case FrameQuad_User_I4      :return QStringLiteral("I4 ");
        case FrameQuad_User_I4R     :return QStringLiteral("I4R");
        case FrameQuad_User_H4      :return QStringLiteral("H4 ");
        /* 六旋翼 USER Frame */
        case FrameHex_User_I6R      :return QStringLiteral("I6R");
        case FrameHex_User_I6       :return QStringLiteral("I6 ");
        case FrameHex_User_V6       :return QStringLiteral("V6 ");
        case FrameHex_User_V6R      :return QStringLiteral("V6R");
        /* 8旋翼 USER Frame */
        case FrameOctA_User_I8      :return QStringLiteral("I8 ");
        case FrameOctA_User_I8R     :return QStringLiteral("I8R");
        case FrameOctA_User_O8      :return QStringLiteral("V8 ");
        case FrameOctA_User_O8R     :return QStringLiteral("V8R");
        /* 4轴8桨 USER Frame */
        case FrameOctAQuad_User_X8  :return QStringLiteral  ("R4X8  ");
        case FrameOctAQuad_User_X8R :return QStringLiteral  ("R4X8R ");
        case FrameOctAQuad_User_X8CRP:return QStringLiteral ("R4X8CRP");
        case FrameOctAQuad_User_IX8 :return QStringLiteral  ("R4IX8 ");
        case FrameOctAQuad_User_IX8R:return QStringLiteral  ("R4IX8R");
        /* Y6 3轴6桨 USER Frame */
        case FrameY6_User_Y6        :return QStringLiteral("Y6 ");
        case FrameY6_User_Y6R       :return QStringLiteral("Y6R");
        case FrameY6_User_IY6        :return QStringLiteral("IY6 ");
        case FrameY6_User_IY6R       :return QStringLiteral("IY6R");
        /* 6轴12桨 USER Frame */
        case FrameDodecaHexA_User_I12R  :return QStringLiteral("R6I12R  ");
        case FrameDodecaHexA_User_I12   :return QStringLiteral("R6I12   ");
        case FrameDodecaHexA_User_X12   :return QStringLiteral("R6X12   ");
        case FrameDodecaHexA_User_X12R  :return QStringLiteral("R6X12R  ");
        case FrameDodecaHexA_User_X12CRP:return QStringLiteral("R6X12CRP");
        default:return QStringLiteral("未知布局:")+QString::number(frame);
    }
    return QStringLiteral("未知布局:")+QString::number(frame);


}

/**===================================================================*
 * @brief      依据当前模式返回字符串
 * @param      uint8_t mode
 * @retval     str
 **===================================================================*/
QString FlyLink::getCopterFlightMode(uint8_t mode)
{
    switch(mode){
        case STABILIZE      :return QStringLiteral("C姿态模式");  // manual airframe angle with manual throttle
        case ACRO           :return QStringLiteral("C竞技模式1"); // manual body-frame angular rate with manual throttle
        case ALT_HOLD       :return QStringLiteral("C定高模式");  // manual airframe angle with automatic throttle
        case AUTO           :return QStringLiteral("C任务模式");  // fully automatic waypoint control using mission commands
        case GUIDED         :return QStringLiteral("C引导模式");  // fully automatic fly to coordinate or fly at velocity/direction using GCS immediate commands
        case LOITER         :return QStringLiteral("C悬停模式");  // automatic horizontal acceleration with automatic throttle
        case RTL            :return QStringLiteral("C返航模式");  // automatic return to launching point
        case CIRCLE         :return QStringLiteral("C绕圈模式");  // automatic circular flight with automatic throttle
        case LAND           :return QStringLiteral("C降落模式");  // automatic landing with horizontal position control
        case DRIFT          :return QStringLiteral("C-Drift");    // semi-autonomous position, yaw and throttle control
        case SPORT          :return QStringLiteral("C竞技模式2"); // manual earth-frame angular rate control with manual throttle
        case FLIP           :return QStringLiteral("C翻滚模式");  // automatically flip the vehicle on the roll axis
        case AUTOTUNE       :return QStringLiteral("C自动调参");  // automatically tune the vehicle's roll and pitch gains
        case POSHOLD        :return QStringLiteral("C位置保持");  // automatic position hold with manual override, with automatic throttle
        case BRAKE          :return QStringLiteral("C刹车模式");  // full-brake using inertial/GPS system, no pilot input
        case THROW          :return QStringLiteral("C抛飞模式");  // throw to launch mode using inertial/GPS system, no pilot input
        case AVOID_ADSB     :return QStringLiteral("C-ADSB避障");  // automatic avoidance of obstacles in the macro scale - e.g. full-sized aircraft
        case GUIDED_NOGPS   :return QStringLiteral("C无卫星引导模式");  // guided mode but only accepts attitude and altitude
        case SMART_RTL      :return QStringLiteral("C智能返航");  // SMART_RTL returns to home by retracing its steps
        case FLOWHOLD       :return QStringLiteral("C光流模式");  // FLOWHOLD holds position with optical flow without rangefinder
        case FOLLOW         :return QStringLiteral("C跟随模式");  // follow attempts to follow another vehicle or ground station
        case ZIGZAG         :return QStringLiteral("C-ZIGZAG");   // ZIGZAG mode is able to fly in a zigzag manner with predefined point A and point B
        case TRACK_ATTACK   :return QStringLiteral("C攻击模式");   // ZIGZAG mode is able to fly in a zigzag manner with predefined point A and point B
        default:return QStringLiteral("未知模式:C")+QString::number(mode);
    }
    return QStringLiteral("未知模式:C")+QString::number(mode);
}

QString FlyLink::getFlightMode(uint8_t vihecle, uint8_t mode)
{
    switch(vihecle){
        case VehicleType_Copter:return getCopterFlightMode(mode);
        case VehicleType_Plane:return getPlaneFlightMode(mode);
        default:return getCopterFlightMode(mode);
    }
    return getCopterFlightMode(mode);
}

QString FlyLink::getVihecleFlightMode(uint8_t mode)
{
    switch(getVehicleType()){
        case VehicleType_Copter:return getCopterFlightMode(mode);
        case VehicleType_Plane:return getPlaneFlightMode(mode);
        default:return getCopterFlightMode(mode);
    }
    return getCopterFlightMode(mode);
}

QString FlyLink::getVihecleFlightMode()
{
    return getVihecleFlightMode(tDataPort.tSysInfo.flight_mode);
}

QString FlyLink::getPlaneFlightMode(uint8_t mode)
{
    switch(mode){
    case PLANE_MANUAL        :return QStringLiteral("P手动模式");
    case PLANE_CIRCLE        :return QStringLiteral("P绕圈模式");
    case PLANE_STABILIZE     :return QStringLiteral("P手动(自动平飞)");
    case PLANE_TRAINING      :return QStringLiteral("P训练模式");
    case PLANE_ACRO          :return QStringLiteral("P竞技模式");
    case PLANE_FLY_BY_WIRE_A :return QStringLiteral("P自稳模式");
    case PLANE_FLY_BY_WIRE_B :return QStringLiteral("P辅助模式(AS)");
    case PLANE_CRUISE        :return QStringLiteral("P辅助模式(ASY)");
    case PLANE_AUTOTUNE      :return QStringLiteral("P自动调参");
    case PLANE_AUTO          :return QStringLiteral("P任务模式");
    case PLANE_RTL           :return QStringLiteral("P返航模式");
    case PLANE_LOITER        :return QStringLiteral("P绕点模式");
    case PLANE_TAKEOFF       :return QStringLiteral("P自主起飞");
    case PLANE_AVOID_ADSB    :return QStringLiteral("P-ADSB避障");
    case PLANE_GUIDED        :return QStringLiteral("P引导模式");
    case PLANE_INITIALISING  :return QStringLiteral("P初始模式");
    case QSTABILIZE          :return QStringLiteral("Q姿态模式");
    case QHOVER              :return QStringLiteral("Q定高模式");
    case QLOITER             :return QStringLiteral("Q悬停模式");
    case QLAND               :return QStringLiteral("Q降落模式");
    case QRTL                :return QStringLiteral("Q返航模式");
    case QAUTOTUNE           :return QStringLiteral("Q自动调参");
    case QACRO               :return QStringLiteral("Q竞技模式");
    case PLANE_THERMAL       :return QStringLiteral("热力模式");
    case LOITER_ALT_QLAND    :return QStringLiteral("Q-Alt降落模式");
    default:return QStringLiteral("未知模式:P")+QString::number(mode);
    }
    return QStringLiteral("未知模式:P")+QString::number(mode);
}

/**===================================================================*
 * @brief      依据定位类型返回字符串
 * @param      uint8_t 类型
 * @retval     QString 字符串
 **===================================================================*/
QString FlyLink::getGNSSFixType(uint8_t type)
{
    switch(type)
    {
        case GPS_FIX_TYPE_NO_GPS    :return QStringLiteral("未连接");      /* No GPS connected | */
        case GPS_FIX_TYPE_NO_FIX    :return QStringLiteral("未定位");      /* No position information, GPS is connected | */
        case GPS_FIX_TYPE_2D_FIX    :return QStringLiteral("2D定位");     /* 2D position | */
        case GPS_FIX_TYPE_3D_FIX    :return QStringLiteral("3D定位");     /* 3D position | */
        case GPS_FIX_TYPE_DGPS      :return QStringLiteral("DGPS");       /* DGPS/SBAS aided 3D position | */
        case GPS_FIX_TYPE_RTK_FLOAT :return QStringLiteral("RTK-Float");  /* RTK float, 3D position | */
        case GPS_FIX_TYPE_RTK_FIXED :return QStringLiteral("RTK-Fixed");  /* RTK Fixed, 3D position | */
        case GPS_FIX_TYPE_STATIC    :return QStringLiteral("Static");     /* Static fixed, typically used for base stations | */
        case GPS_FIX_TYPE_PPP       :return QStringLiteral("PPP");        /* PPP, 3D position. | */
        default                     :return QStringLiteral("位置类型:")+QString::number(type);
    }
    return QStringLiteral("位置类型:")+QString::number(type);
}

QString FlyLink::getMAVResultString(uint8_t res)
{
    switch(res){
        case MAV_RESULT_ACCEPTED                :return QStringLiteral("指令接受");
        case MAV_RESULT_TEMPORARILY_REJECTED    :return QStringLiteral("指令暂时拒绝");
        case MAV_RESULT_DENIED                  :return QStringLiteral("指令拒绝");
        case MAV_RESULT_UNSUPPORTED             :return QStringLiteral("指令无效");
        case MAV_RESULT_FAILED                  :return QStringLiteral("指令执行失败");
        case MAV_RESULT_IN_PROGRESS             :return QStringLiteral("指令执行中");
        default                                 :return QStringLiteral("未知结果")+QString::number(res);
    }
    return QStringLiteral("未知结果")+QString::number(res);
}

QString FlyLink::getCommandString(uint8_t command)
{
    switch(command){
    case FlyLink_CMD_ID_SetMode                  :return QStringLiteral("设置模式");
    case FlyLink_CMD_ID_ArmMotors                :return QStringLiteral("电机");
    case FlyLink_CMD_ID_Takeoff                  :return QStringLiteral("起飞");
    case FlyLink_CMD_ID_Request_Home             :return QStringLiteral("获取家位置");
    case FlyLink_CMD_ID_Request_Origin           :return QStringLiteral("获取原点位置");
    case FlyLink_CMD_ID_Change_Alt               :return QStringLiteral("修改高度");
    case FlyLink_CMD_ID_Change_Heading           :return QStringLiteral("修改航向");
    case FlyLink_CMD_ID_Factory                  :return QStringLiteral("恢复出厂设置");
    case FlyLink_CMD_ID_Restart                  :return QStringLiteral("重启");
    case FlyLink_CMD_ID_Motor_test               :return QStringLiteral("电机测试/电调校准");
    case FlyLink_CMD_ID_StartMission             :return QStringLiteral("开启任务");
    case FlyLink_CMD_ID_ChangeMissionItem        :return QStringLiteral("切换任务点");
    case FlyLink_CMD_ID_Calibration              :return QStringLiteral("校准");
    case FlyLink_CMD_ID_ReqMSG                   :return QStringLiteral("请求消息");
    case FlyLink_CMD_ID_FlashBootloader          :return QStringLiteral("写入出厂数据");
    case FlyLink_CMD_ID_WriteSN                  :return QStringLiteral("写入SN");
    case FlyLink_CMD_ID_ReqRTLWP                 :return QStringLiteral("读取返航点");
    case FlyLink_CMD_ID_Land                     :return QStringLiteral("执行降落");
    case FlyLink_CMD_ID_GoAround                 :return QStringLiteral("执行复飞");
    default                                      :return QStringLiteral("指令")+QString::number(command);
    }
    return QStringLiteral("未知");
}

uint8_t FlyLink::get_frame_output_count(uint8_t frame)
{
    uint8_t copter_num;
    switch(frame)
    {

        case Frame_UNDIFINE :
        //=================四旋翼===========
        // ardupilot
        case FrameQuad_Plus         :
        case FrameQuad_X            :
        case FrameQuad_NYT_PLUS     :
        case FrameQuad_NYT_NYT_X    :
        case FrameQuad_BF_X         :
        case FrameQuad_BF_X_REV     :
        case FrameQuad_DJI_X        :
        case FrameQuad_CW_X         :
        case FrameQuad_V            :
        case FrameQuad_H            :
        case FrameQuad_VTAIL        :
        case FrameQuad_ATAIL        :
        case FrameQuad_PLUSREV      :
        /* 四旋翼 USER Frame */
        case FrameQuad_User_X4      :
        case FrameQuad_User_X4R     :
        case FrameQuad_User_I4      :
        case FrameQuad_User_I4R     :
        case FrameQuad_User_H4      :
            copter_num = 4;
        break;
    //======================六旋翼======
        // ardupilot
        case FrameHex_PLUS          :
        case FrameHex_X             :
        case FrameHex_H             :
        case FrameHex_DJI_X         :
        case FrameHex_CW_X          :

        /* 六旋翼 USER Frame */
        case FrameHex_User_I6R      :
        case FrameHex_User_I6       :
        case FrameHex_User_V6       :
        case FrameHex_User_V6R      :


        //======================Y6 3轴
        // ardupilot
        case FrameY6_Y6B            :
        case FrameY6_Y6F            :
        case FrameY6_Y6             :

        /* Y6 3轴6桨 USER Frame */
        case FrameY6_User_Y6        :
        case FrameY6_User_Y6R       :
        case FrameY6_User_IY6        :
        case FrameY6_User_IY6R       :
            copter_num = 6;
        break;
    //======================8旋翼======
        // ardupilo
        case FrameOctA_PLUS         :
        case FrameOctA_X            :
        case FrameOctA_V            :
        case FrameOctA_H            :
        case FrameOctA_I            :
        case FrameOctA_DJI_X        :
        case FrameOctA_CW_X         :
        /* 8旋翼 USER Frame */
        case FrameOctA_User_I8      :
        case FrameOctA_User_I8R     :
        case FrameOctA_User_O8      :
        case FrameOctA_User_O8R     :
    //======================4轴8桨=
        // ardupilot
        case FrameOctAQuad_PLUS     :
        case FrameOctAQuad_X        :
        case FrameOctAQuad_V        :
        case FrameOctAQuad_H        :
        case FrameOctAQuad_CW_X     :

        /* 4轴8桨 USER Frame */
        case FrameOctAQuad_User_X8  :
        case FrameOctAQuad_User_X8R :
        case FrameOctAQuad_User_X8CRP:
        case FrameOctAQuad_User_IX8 :
        case FrameOctAQuad_User_IX8R:
            copter_num = 8;
        break;
        //======================6轴12桨
        // ardupilot
        case FrameDodecaHexA_PLUS   :
        case FrameDodecaHexA_X      :
        //======================12旋翼
        // ardupilot
        case FrameDecA_PLUS         :
        case FrameDecA_X            :
        //======================自定义构型

        /* 6轴12桨 USER Frame */
        case FrameDodecaHexA_User_I12R  :
        case FrameDodecaHexA_User_I12   :
        case FrameDodecaHexA_User_X12   :
        case FrameDodecaHexA_User_X12R  :
        case FrameDodecaHexA_User_X12CRP:
            copter_num = 12;
        break;


    default:
            copter_num = 0;
        break;
    }
    return copter_num;
}

QString FlyLink::getBoardOrientation(uint8_t orientation)
{
    switch(orientation){
        case ROTATION_NONE                          :return QStringLiteral("正常");
        case ROTATION_YAW_45                        :return QStringLiteral("航向旋转:45°");
        case ROTATION_YAW_90                        :return QStringLiteral("航向旋转:90°");
        case ROTATION_YAW_135                       :return QStringLiteral("航向旋转:135°");
        case ROTATION_YAW_180                       :return QStringLiteral("航向旋转:180°");
        case ROTATION_YAW_225                       :return QStringLiteral("航向旋转:-135°");
        case ROTATION_YAW_270                       :return QStringLiteral("航向旋转:-90°");
        case ROTATION_YAW_315                       :return QStringLiteral("航向旋转:-45°");
        case ROTATION_ROLL_180                      :return QStringLiteral("滚转旋转:180°");
        case ROTATION_ROLL_180_YAW_45               :return QStringLiteral("滚转旋转:180°->航向旋转:45°");
        case ROTATION_ROLL_180_YAW_90               :return QStringLiteral("滚转旋转:180°->航向旋转:90°");
        case ROTATION_ROLL_180_YAW_135              :return QStringLiteral("滚转旋转:180°->航向旋转:135°");
        case ROTATION_PITCH_180                     :return QStringLiteral("俯仰旋转:180°");
        case ROTATION_ROLL_180_YAW_225              :return QStringLiteral("滚转旋转:180°->航向旋转:-135°");
        case ROTATION_ROLL_180_YAW_270              :return QStringLiteral("滚转旋转:180°->航向旋转:-90°");
        case ROTATION_ROLL_180_YAW_315              :return QStringLiteral("滚转旋转:180°->航向旋转:-45°");
        case ROTATION_ROLL_90                       :return QStringLiteral("滚转旋转:90°");
        case ROTATION_ROLL_90_YAW_45                :return QStringLiteral("滚转旋转:90°->航向旋转:45°");
        case ROTATION_ROLL_90_YAW_90                :return QStringLiteral("滚转旋转:90°->航向旋转:90°");
        case ROTATION_ROLL_90_YAW_135               :return QStringLiteral("滚转旋转:90°->航向旋转:135°");
        case ROTATION_ROLL_270                      :return QStringLiteral("滚转旋转:-90°");
        case ROTATION_ROLL_270_YAW_45               :return QStringLiteral("滚转旋转:-90°->航向旋转:45°");
        case ROTATION_ROLL_270_YAW_90               :return QStringLiteral("滚转旋转:-90°->航向旋转:90°");
        case ROTATION_ROLL_270_YAW_135              :return QStringLiteral("滚转旋转:-90°->航向旋转:135°");
        case ROTATION_PITCH_90                      :return QStringLiteral("俯仰旋转:90°");
        case ROTATION_PITCH_270                     :return QStringLiteral("俯仰旋转:-90°");
        case ROTATION_PITCH_180_YAW_90              :return QStringLiteral("俯仰旋转:180°->航向旋转:90°");
        case ROTATION_PITCH_180_YAW_270             :return QStringLiteral("俯仰旋转:180°->航向旋转:-90°");
        case ROTATION_ROLL_90_PITCH_90              :return QStringLiteral("滚转旋转:90°->俯仰旋转:90°");
        case ROTATION_ROLL_180_PITCH_90             :return QStringLiteral("滚转旋转:180°->俯仰旋转:90°");
        case ROTATION_ROLL_270_PITCH_90             :return QStringLiteral("滚转旋转:-90°->俯仰旋转:90°");
        case ROTATION_ROLL_90_PITCH_180             :return QStringLiteral("滚转旋转:90°->俯仰旋转:180°");
        case ROTATION_ROLL_270_PITCH_180            :return QStringLiteral("滚转旋转:-90°->俯仰旋转:180°");
        case ROTATION_ROLL_90_PITCH_270             :return QStringLiteral("滚转旋转:90°->俯仰旋转:-90°");
        case ROTATION_ROLL_180_PITCH_270            :return QStringLiteral("滚转旋转:180°->俯仰旋转:-90°");
        case ROTATION_ROLL_270_PITCH_270            :return QStringLiteral("滚转旋转:-90°->俯仰旋转:-90°");
        case ROTATION_ROLL_90_PITCH_180_YAW_90      :return QStringLiteral("滚转旋转:90°->俯仰旋转:180°->航向旋转:90°");
        case ROTATION_ROLL_90_YAW_270               :return QStringLiteral("滚转旋转:90°->航向旋转:-90°");
        case ROTATION_PITCH_315                     :return QStringLiteral("俯仰旋转:-45°");
        case ROTATION_ROLL_90_PITCH_315             :return QStringLiteral("滚转旋转:90°->俯仰旋转:-45°");
    default:break;
    }
    return QStringLiteral("未知方向")+QString::number(orientation);
}

QString FlyLink::getSerialProtocolString(int8_t protocol)
{
    switch(protocol){
    case SerialProtocol_None                    :return QStringLiteral("None");
    case SerialProtocol_Console                 :return QStringLiteral("Console");
    case SerialProtocol_MAVLink                 :return QStringLiteral("MAVLink");
    case SerialProtocol_MAVLink2                :return QStringLiteral("MAVLink2");
    case SerialProtocol_FrSky_D                 :return QStringLiteral("FrSky_D");
    case SerialProtocol_FrSky_SPort             :return QStringLiteral("FrSky_SPort");
    case SerialProtocol_GPS                     :return QStringLiteral("GPS");
    case SerialProtocol_GPS2                    :return QStringLiteral("GPS2");
    case SerialProtocol_AlexMos                 :return QStringLiteral("AlexMos");
//    case SerialProtocol_SToRM32                 :return QStringLiteral("SToRM32");
    case SerialProtocol_Rangefinder             :return QStringLiteral("Rangefinder");
    case SerialProtocol_FrSky_SPort_Passthrough :return QStringLiteral("FrSky_SPort_Passthrough ");
    case SerialProtocol_Lidar360                :return QStringLiteral("Lidar360");
//    case SerialProtocol_Aerotenna_uLanding      :return QStringLiteral("Aerotenna_uLanding");
    case SerialProtocol_Beacon                  :return QStringLiteral("Beacon");
    case SerialProtocol_Volz                    :return QStringLiteral("Volz");
    case SerialProtocol_Sbus1                   :return QStringLiteral("Sbus1");
    case SerialProtocol_ESCTelemetry            :return QStringLiteral("ESCTelemetry");
    case SerialProtocol_Devo_Telem              :return QStringLiteral("Devo_Telem");
    case SerialProtocol_OpticalFlow             :return QStringLiteral("OpticalFlow");
    case SerialProtocol_Robotis                 :return QStringLiteral("Robotis");
    case SerialProtocol_NMEAOutput              :return QStringLiteral("NMEAOutput");
    case SerialProtocol_WindVane                :return QStringLiteral("WindVane");
    case SerialProtocol_SLCAN                   :return QStringLiteral("SLCAN");
    case SerialProtocol_RCIN                    :return QStringLiteral("RCIN");
//    case SerialProtocol_EFI_MS                  :return QStringLiteral("EFI_MS");
//    case SerialProtocol_LTM_Telem               :return QStringLiteral("LTM_Telem");
    case SerialProtocol_RunCam                  :return QStringLiteral("RunCam");
    case SerialProtocol_Hott                    :return QStringLiteral("Hott");
    case SerialProtocol_Scripting               :return QStringLiteral("Scripting");
    case SerialProtocol_CRSF                    :return QStringLiteral("CRSF");
    case SerialProtocol_Generator               :return QStringLiteral("Generator");
    case SerialProtocol_Winch                   :return QStringLiteral("Winch");
    case SerialProtocol_MSP                     :return QStringLiteral("MSP");
    case SerialProtocol_DJI_FPV                 :return QStringLiteral("DJI_FPV");
//    case SerialProtocol_AirSpeed                :return QStringLiteral("AirSpeed");
    case SerialProtocol_ADSB                    :return QStringLiteral("ADSB");
    case SerialProtocol_AHRS                    :return QStringLiteral("AHRS");
    case SerialProtocol_SmartAudio              :return QStringLiteral("SmartAudio");
    case SerialProtocol_FETtecOneWire           :return QStringLiteral("FETtecOneWire");
//    case SerialProtocol_NumProtocols            :return QStringLiteral("NumProtocols");
//    case SerialProtocol_XYFly                   :return QStringLiteral("XYFly");
//    case SerialProtocol_OpenLink                :return QStringLiteral("OpenLink");
    case SerialProtocol_FlyLink                 :return QStringLiteral("FlyLink");
//    case SerialProtocol_INS_Telem               :return QStringLiteral("INS_Telem");

//    case SerialProtocol_YJYSeeker               :return QStringLiteral("YJYSeeker");
    default:break;
    }
    return QStringLiteral("PTC:")+QString::number(protocol);
}

QString FlyLink::getProtocolType(uint8_t type)
{
    switch(type){
    case VehicleType_Copter:return QStringLiteral("-Copter");
    case VehicleType_Plane:return QStringLiteral("-Plane");
    default:return QStringLiteral("");
    }
    return QStringLiteral("");
}

uint8_t FlyLink::get_frame_output_count()
{
    return tDataPort.FrameMotorCount;
}

uint32_t FlyLink::map_baudrate(int32_t rate)
{
    if (rate <= 0) {
        rate = 57;
    }
    switch (rate) {
    case 1:    return 1200;
    case 2:    return 2400;
    case 4:    return 4800;
    case 9:    return 9600;
    case 19:   return 19200;
    case 38:   return 38400;
    case 57:   return 57600;
    case 100:  return 100000;
    case 111:  return 111100;
    case 115:  return 115200;
    case 230:  return 230400;
    case 256:  return 256000;
    case 460:  return 460800;
    case 500:  return 500000;
    case 921:  return 921600;
    case 1500:  return 1500000;
    }

    if (rate > 2000) {
        // assume it is a direct baudrate. This allows for users to
        // set an exact baudrate as long as it is over 2000 baud
        return (uint32_t)rate;
    }

    // otherwise allow any other kbaud rate
    return rate*1000;
}

/**===================================================================*
 * @brief      parse_char
 * @param      u8Data Input data
 * @retval     rev_status
 **===================================================================*/
uint8_t FlyLink::parse_char(uint8_t c)
{
    switch(rev_state.status){
    case STA_WAIT_HEADER_X :
        if(FlyLink_FRAME_HEADER_X == c){
            rev_state.status = STA_WAIT_HEADER_Y;
            revbuf[0] = c;
        }
        break;

    case STA_WAIT_HEADER_Y:
        if(FlyLink_FRAME_HEADER_Y == c){
            rev_state.status = STA_RCV_SYS_ID;
            revbuf[1] = c;
        }
        else{
            rev_state.status = STA_WAIT_HEADER_X;
        }
        break;

    case STA_RCV_SYS_ID:
        revbuf[2] = c;
        rev_state.status = STA_RCV_INDEX;
        break;

    case STA_RCV_INDEX:
        revbuf[3] = c;
        rev_state.status = STA_RCV_MSG_ID;
            break;

        case STA_RCV_MSG_ID:
            revbuf[4] = c;
            rev_state.status = STA_RCV_DATALEN;
            break;

        case STA_RCV_DATALEN:
            revbuf[5] = c;
            rev_state.datalen = c;
            rev_state.datacnt = 0;
            if(0 == rev_state.datalen){
                rev_state.status = STA_RCV_CHECKSUM;
            }
            else{
                rev_state.status = STA_RCV_DATA;
            }
            break;

        case STA_RCV_DATA:
            revbuf[6+rev_state.datacnt] = c;
            rev_state.datacnt++;
            if(rev_state.datacnt >= rev_state.datalen){
                rev_state.status = STA_RCV_CHECKSUM;
            }
            break;

        case STA_RCV_CHECKSUM:
            revbuf[6+rev_state.datalen] = c;
            // 收到一帧数据进行处理

            Decode(revbuf,7+rev_state.datalen);
            rev_state.status = STA_WAIT_HEADER_X;
            break;

        default:
            rev_state.status = STA_WAIT_HEADER_X;
            break;
    }
    return rev_state.status;
}

/**===================================================================*
 * @brief      Decode buffer data from DMZK
 * @param      u8 *Buf 有效数据的buf指针
 * @param      u8 u8Len 数据长度
 * @retval     None
 **===================================================================*/
void FlyLink::Decode(uint8_t *Buf,uint16_t u16Len)
{
    uint8_t u8CheckSum = 0;
    if(Buf == nullptr)
    {
        return;
    }
    // Check Sum
    for(int i = 0;i< u16Len - 1;i++){
        u8CheckSum += *(Buf+i);
    }

    if(*(Buf+u16Len-1)!=u8CheckSum){
        return;
    }
    QByteArray arr;
    arr.resize(u16Len);
    memcpy(arr.data(),Buf,u16Len);
    emit Qt::DMMM()->replayDataWriteSignal(getIdentity(),QDateTime::currentDateTime(),arr);
    FlyLink_RevMSG revmsg{};
    memcpy(&revmsg,Buf,6);
    revmsg.dataptr = Buf+6;
    revmsg.checksum = *(Buf+u16Len-1);
    handle_msg(revmsg);
}

/**===================================================================*
 * @brief      active_com
 * @param      当收到消息后激活通信
 * @retval     None
 **===================================================================*/
void FlyLink::active_com(FlyLink_RevMSG msg)
{
    last_rev_update_ms = QDateTime::currentDateTime().toMSecsSinceEpoch();
    set_mav_id(msg.sys_id);
    if(interval_mode == interval_wait_active){
        set_interval_mode(interval_Check_active);
    }
    if(!getIs_active()){
        ProtocolEvent   (Q_DMMM::DMMM_GCSEvent_Protocol_Actived);
        DisplayGcsCMD   (QStringLiteral("通信建立连接"));
        do_reqParamAll  ();
        req_boardInfo   ();
    }
    is_active = true;
}

/**===================================================================*
 * @brief      disactive_com
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::disactive_com(void)
{
    if(getIs_active()){
        DisplayGcsCMD(QStringLiteral("通信连接断开"));
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Protocol_lost);
        tDataPort.tHome.is_get = false;
    }
    is_active = false;
    if(interval_mode == interval_Check_active){
        set_interval_mode(interval_wait_active);
    }
}

/**===================================================================*
 * @brief      handle_msg
 * @param      FlyLink_RevMSG msg
 * @retval     None
 **===================================================================*/
void FlyLink::handle_msg(FlyLink_RevMSG msg)
{
    active_com(msg);
    switch(msg.msg_id){
        case FlyLink_ID_HEARTBEAT:
            handle_heartbeat(msg);
            break;
        case FlyLink_ID_SYSINFO:
            handle_sysinfo(msg);
            break;
        case FlyLink_ID_VEHICLE_INFO:
            handle_vehicle(msg);
            break;
        case FlyLink_ID_ESC:
            handle_esc(msg);
            break;
        case FlyLink_ID_GNSS:
            handle_gnss(msg);
            break;
        case FlyLink_ID_IMUS:
            handle_imus(msg);
            break;
        case FlyLink_ID_COMPASS:
            handle_compass(msg);
            break;
        case FlyLink_ID_BARO:
            handle_baro(msg);
            break;
        case FlyLink_ID_RC_OUT:
            handle_rc_out(msg);
            break;
        case FlyLink_ID_CONTROL_TARGET:
            handle_target(msg);
            break;
        case FlyLink_ID_STATUS_TEXT:
            handle_statustext(msg);
            break;
        case FlyLink_ID_MISSION_ACK:
            handle_mission_ack(msg);
            break;
        case FlyLink_ID_MISSION_REQUEST:
            handle_mission_request(msg);
            break;
        case FlyLink_ID_MISSION_COUNT:
            handle_mission_count(msg);
            break;
        case FlyLink_ID_MISSION_ITEM:
            handle_mission_item(msg);
            break;
        case FlyLink_ID_COMMAND_ACK:
            handle_command_ack(msg);
            break;
        case FlyLink_ID_HOME:
            handle_home(msg);
            break;
        case FlyLink_ID_ORIGIN:
            handle_origin(msg);
            break;

        case FlyLink_ID_EXTVoltageMonitor:
            handle_extVol(msg);
            break;

        case FlyLink_ID_RPMInfo:
            handle_RPMInfo(msg);
            break;

        case FlyLink_ID_Guidance:
            handle_GuidanceDevice(msg);
            break;

        case FlyLink_ID_COMMOM_PARAM:
            handle_CommonParamter(msg);
            break;
        case FlyLink_ID_ACC_CALI_POSITION:
            handle_Acc3DCali(msg);
            break;
        case FlyLink_ID_MAG_CALI_PROGRESS:
            handle_MagCaliProgress(msg);
            break;
        case FlyLink_ID_PARAM_FAILSAFE:
            handle_Param_failsafe(msg);
            break;
        case FlyLink_ID_PARAM_MAIN_RC:
            handle_Param_MainRC(msg);
            break;
        case FlyLink_ID_PARAM_AUX_RC:
            handle_Param_AuxRC(msg);
            break;
        case FlyLink_ID_PARAM_MOTORS:
            handle_Param_Motors(msg);
            break;
        case FlyLink_ID_PARAM_GNSS_POSITION:
            handle_Param_GnssPosition(msg);
            break;
        case FlyLink_ID_PARAM_INIT_CFG_PARAM:
            handle_Param_InitCtrlCfg(msg);
            break;
        case FlyLink_ID_PARAM_PILOT_CONTROL:
            handle_Param_PilotControl(msg);
            break;

        case FlyLink_ID_PARAM_AUTO_CONTROL:
            handle_Param_AutoControl(msg);
            break;

        case FlyLink_ID_PARAM_Roll_CONTROL:
            handle_Param_RollControl(msg);
            break;
        case FlyLink_ID_PARAM_Pitch_CONTROL:
            handle_Param_PitchControl(msg);
            break;
        case FlyLink_ID_PARAM_Yaw_CONTROL:
            handle_Param_Yawontrol(msg);
            break;
        case FlyLink_ID_PARAM_POSZ_CONTROL:
            handle_Param_PosZControl(msg);
            break;
        case FlyLink_ID_PARAM_POSXY_CONTROL:
            handle_Param_PosXYControl(msg);
            break;

        case FlyLink_ID_PARAM_SerialPort:
            handle_Param_SerialPort(msg);
            break;

        case FlyLink_ID_BoardInfo:
            handle_BoardInfo(msg);
        break;

        case FlyLink_ID_LOG_INFO:
            handle_log_info(msg);
            break;

        case FlyLink_ID_LOG_DATA:
            handle_log_data(msg);
            break;

        case FlyLink_ID_Transparent:
            handle_Transparent(msg);
            break;
        case FlyLink_ID_Waypoint:
            handle_waypoint(msg);
            break;

        default:
            break;
    }
}

/**===================================================================*
 * @brief      发送函数 更新频率 > 200Hz
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::update_send()
{
    app_mission_upload_update();
    app_mission_download_update();
    Send_Transparent_YJYVedioControl();
    if(should_to_send(time_heartbeat)){
        send_heartbeat();
    }
}

/**===================================================================*
 * @brief      更新接收，更新频率>200Hz
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::update_receive()
{
    if(is_read)
    {
        return;
    };

    is_read = true;
    // qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")+"update_receive\n";
    /*== 超过5s未收到地面信息，则Disable通信 ==*/
    uint32_t tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if(tnow - last_rev_update_ms > 1500){
        disactive_com();
    }

    is_read = true;
    /* 处理收到的数据，按照协议进行帧解析 */
    qint64 nbytes = available();
    if(0 >= nbytes){
        is_read = false;
        return;
    }
    QByteArray recBuf{};
    recBuf = read(nbytes);
    for(int i = 0 ; i <nbytes;i++ ){
        uint8_t b = (uint8_t)recBuf[i];
        parse_char(b);
    }
    is_read = false;
}

void FlyLink::update_10Hz()
{
    // qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")+"update_receive\n";
    /*== 超过5s未收到地面信息，则Disable通信 ==*/
    uint32_t tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if(tnow - last_rev_update_ms > 1500){
        disactive_com();
    }

}

void FlyLink::handle_DMMM_event(int ev, int linkid)
{
    switch(ev){
    // 10Hz 执行
    case Q_DMMM::DMMM_GCSEvent_Timer_100Hz_Event:
    case Q_DMMM::DMMM_GCSEvent_Timer_10Hz_Event:
    {
        update_send();
        update_10Hz();
//        uint32_t tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
//        if(tnow - last_Update_ParamMap_ms > 50){
            Update_ParamMap();
//            last_Update_ParamMap_ms = tnow;
//        }
    }break;
    case Q_DMMM::DMMM_GCSEvent_DeviceOpenSucceed:
        if(linkid == getIdentity()){
            ResetAllVariant();
        }
        break;
    }
}

bool FlyLink::getIs_active() const
{
    return is_active;
}

bool FlyLink::set_mode(uint8_t mode)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_SetMode;
    CMD.param.mode.number = mode;
    DisplayGcsCMD(QStringLiteral("切换")+getVihecleFlightMode(mode),true);
    return send_command(CMD);
}

bool FlyLink::set_motors_arm()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ArmMotors;
    CMD.param.arm = ARM_MOTERS;
    DisplayGcsCMD(QStringLiteral("解锁电机"),true);
    return send_command(CMD);
}

bool FlyLink::set_motors_force_arm()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ArmMotors;
    CMD.param.arm = ARM_MOTERS_FORCE;
    DisplayGcsCMD(QStringLiteral("强制解锁电机"),true);
    return send_command(CMD);
}

bool FlyLink::set_motors_disarm()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ArmMotors;
    CMD.param.arm = DISARM_MOTORS;
    DisplayGcsCMD(QStringLiteral("锁定电机"),true);
    return send_command(CMD);
}

bool FlyLink::set_motors_force_disarm()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ArmMotors;
    CMD.param.arm = DISARM_MOTORS_FORCE;
    DisplayGcsCMD(QStringLiteral("强制锁定电机"),true);
    return send_command(CMD);
}

bool FlyLink::do_takeoff(float alt_m)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Takeoff;
    CMD.param.takeoff.alt_m = alt_m;
    DisplayGcsCMD(QStringLiteral("一键起飞,高度:")+QString::number(alt_m)+QStringLiteral("米"),true);
    return send_command(CMD);
}

bool FlyLink::request_home()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Request_Home;
    return send_command(CMD);
}

bool FlyLink::request_origin()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Request_Origin;
    return send_command(CMD);
}

bool FlyLink::do_set_alt_m(float alt_m)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Change_Alt;
    CMD.param.setAlt.alt_m = alt_m ;
    DisplayGcsCMD(QStringLiteral("修改高度:")+QString::number(alt_m,'f',1)+QStringLiteral("米"),true);
    return send_command(CMD);
}

bool FlyLink::do_set_heading(float heading)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Change_Heading;
    CMD.param.setHeading.heading = heading ;
    DisplayGcsCMD(QStringLiteral("修改航向:")+QString::number(heading,'f',1)+QStringLiteral("°"),true);
    return send_command(CMD);
}

bool FlyLink::do_factory()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Factory;
    DisplayGcsCMD(QStringLiteral("恢复出厂设置"),true);
    return send_command(CMD);
}

bool FlyLink::do_reboot()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Restart;
    DisplayGcsCMD(QStringLiteral("重启飞控系统"),true);
    return send_command(CMD);
}

bool FlyLink::do_SetBoardSN(uint32_t SN)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_WriteSN;
    CMD.param.SN.SN = SN;
    DisplayGcsCMD(QStringLiteral("设置飞控SN：")+QString::asprintf("%d-%04d",SN>>16,SN&0XFFFF),true);
    return send_command(CMD);
}

bool FlyLink::do_startMission(bool resume)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_StartMission;
    CMD.param.StartMission.is_resume = resume ? 1 : 0;
    DisplayGcsCMD(QStringLiteral("开始任务"),true);
    return send_command(CMD);
}

bool FlyLink::do_ChangeMissionItem(uint16_t index)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ChangeMissionItem;
    CMD.param.ChangeMissionItem.id = index;
    if(index == 0){
        DisplayGcsCMD(QStringLiteral("恢复任务"),true);
    }
    else{
        DisplayGcsCMD(QStringLiteral("切换任务点至")+QString::number(index),true);
    }
    return send_command(CMD);
}

bool FlyLink::do_PlaneTakeoff(uint8_t ACT)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Takeoff;
    CMD.param.p_takeoff.ACTION = ACT;
    DisplayGcsCMD(QStringLiteral("执行起飞"));
    return send_command(CMD);
}

bool FlyLink::do_PlaneLand()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Land;
    DisplayGcsCMD(QStringLiteral("执行降落"));
    return send_command(CMD);
}

bool FlyLink::do_PlaneGoAround(float alt)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_GoAround;
    CMD.param.setAlt.alt_m = alt;
    QString str = QStringLiteral("执行复飞");
    if(alt >= 0.0001){
        str+=QStringLiteral(",高度")+QString::number(alt,'f',1)+QStringLiteral("米");
    }
    DisplayGcsCMD(str);
    return send_command(CMD);
}

bool FlyLink::do_req_RTLWaypoint()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqRTLWP;
    return send_command(CMD);
}

bool FlyLink::set_RTLWaypoint(waypoint_new_t &wp)
{
    wp.type = TYPE_RETURN_WAYPOINT;
    wp.frame = AltFrame_ABOVE_HOME;
    SendPacketByID(FlyLink_ID_Waypoint,(void*)&wp,sizeof(wp));
    return true;
}

bool FlyLink::set_guided_nav_wp(const guided_nav_wp_t &wp)
{
    SendPacketByID(FlyLink_ID_Guided_WP,(void*)&wp,sizeof(wp));
    DisplayGcsCMD(QStringLiteral("设置航点"),true);
    return true;
}



const FlyLink::DataPort_t &FlyLink::getTDataPort() const
{
    return tDataPort;
}

/**===================================================================*
 * @brief      绑定信号与槽
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::connectSignalAndSlot()
{
    connect(this,&FlyLink::readyRead,this,&FlyLink::update_receive);
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&FlyLink::handle_DMMM_event);
}

/**===================================================================*
 * @brief      SendPacketByID

 * @param      u8 u8Id  function code
 * @param      data data buffer pointer
 * @param      u8DataLen data length

 * @retval     None
 **===================================================================*/
void FlyLink::SendPacketByID(uint8_t u8Id , void * data, uint8_t u8DataLen)
{
    QMutexLocker locker(&_data_mutex);

    if(getE_DeviceState() != DeviceState_Connect)return;
    uint8_t U8_Cnt = 0;
    uint8_t U8_CheckSum = 0;
    if(data == NULL&& u8DataLen!=0) return;
    sendbuf[0] = FlyLink_FRAME_HEADER_X;
    sendbuf[1] = FlyLink_FRAME_HEADER_Y;
    sendbuf[2] = get_gcs_id();
    sendbuf[3] = seq_index++;
    sendbuf[4] = u8Id;
    sendbuf[5] = u8DataLen;
    memcpy(&sendbuf[6],data,u8DataLen);
    for(U8_Cnt = 0; U8_Cnt < u8DataLen + 6;U8_Cnt++){
        U8_CheckSum += *(sendbuf+U8_Cnt);
    }
    sendbuf[6+u8DataLen] = U8_CheckSum;
    write((char*)sendbuf,u8DataLen+7);
}

void FlyLink::SendPacketByID(uint8_t u8Id, QByteArray data)
{
    if(data.size() > 255){
        qDebug()<<"SendPacketByID QByteArray > 255";
        return;
    }

    QMutexLocker locker(&_data_mutex);

    if(getE_DeviceState() != DeviceState_Connect)return;

    uint8_t U8_Cnt = 0;
    uint8_t U8_CheckSum = 0;
    uint8_t u8DataLen = data.size();
    QByteArray sendbuf;
    sendbuf.resize(7 + u8DataLen);

    sendbuf[0] = FlyLink_FRAME_HEADER_X;
    sendbuf[1] = FlyLink_FRAME_HEADER_Y;
    sendbuf[2] = get_gcs_id();
    sendbuf[3] = seq_index++;
    sendbuf[4] = u8Id;
    sendbuf[5] = u8DataLen;
    memcpy(sendbuf.data()+6,data.data(),u8DataLen);
    for(U8_Cnt = 0; U8_Cnt < u8DataLen + 6;U8_Cnt++){
        U8_CheckSum += sendbuf.at(U8_Cnt);
    }
    sendbuf[6+u8DataLen] = U8_CheckSum;
    write(sendbuf);
}

/**===================================================================*
 * @brief      判断当前是否要发送内容
 * @param      None
 * @retval     None
 **===================================================================*/
bool FlyLink::should_to_send(send_time_t& tTime)
{
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();  // 通用消息的处理
    /* heartbeat 1Hz */
    if(((tnow - tTime.last_send_ms) > tTime.time_interval_ms) &&  \
        tTime.time_interval_ms != 0){
        tTime.last_send_ms = tnow;
        return true;
    }
    return false;
}

/**===================================================================*
 * @brief      设置遥测的发送时间间隔模式
 * @param      None
 * @retval     None
 **===================================================================*/
bool FlyLink::set_interval_mode(uint8_t mode)
{
    if(mode < interval_mode_end){
        interval_mode = mode;
        update_interval_ms();
        return true;
    }
    return false;
}

uint8_t FlyLink::get_interval_mode() const{return interval_mode;}

/**===================================================================*
 * @brief      更新遥测的发送时间间隔
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::update_interval_ms()
{
    switch (interval_mode)
    {
        case interval_wait_active:
            time_heartbeat.time_interval_ms = 200;
            break;
        case interval_Check_active:
        case interval_General:
            time_heartbeat.time_interval_ms = 1000;
            break;
        case interval_dbg:
            time_heartbeat.time_interval_ms = 1000;
            break;
        default:
            set_interval_mode(interval_wait_active);
            break;
    }
}

/**===================================================================*
 * @brief      发送心跳信息
 * @param      None
 * @retval     None
 **===================================================================*/
bool FlyLink::send_heartbeat()
{
    uint16_t ver = FlyLink_Protocol_Version;
//    SendPacketByID(FlyLink_ID_HEARTBEAT,(void*)&ver,sizeof(ver));
    QByteArray data;
    data.append((char*)&ver,sizeof(ver));
    SendPacketByID(FlyLink_ID_HEARTBEAT,data);
    return true;
}

bool FlyLink::send_command(const Command_t &cmd)
{
    SendPacketByID(FlyLink_ID_COMMAND,(void*)&cmd,sizeof(cmd));
    return true;
}

/**===================================================================*
 * @brief      发送心跳信息
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::handle_heartbeat(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(tDataPort.mav_version)){
        memcpy(&tDataPort.mav_version,msg.dataptr,msg.datalen);
        set_mav_id(msg.sys_id);
        uint8_t vehicle = tDataPort.mav_version&0x0f;
        if( vehicle != getVehicleType()){
            setVehicleType(vehicle);
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_NewVehicleType);
        }

        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_get_heartbeat);
    }
}

/**===================================================================*
 * @brief      处理指令ack
 * @param      None
 * @retval     None
 **===================================================================*/
void FlyLink::handle_command_ack(FlyLink_RevMSG msg)
{
    Command_ack_t ack{};
    if(msg.datalen == sizeof(Command_ack_t)){
        memcpy(&ack,msg.dataptr,msg.datalen);
        QString str = getCommandString(ack.cmd_id)+getMAVResultString(ack.ack);
        DisplayMsg(str);
    }
}

void FlyLink::handle_sysinfo(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(tDataPort.tSysInfo)){
        memcpy(&tDataPort.tSysInfo,msg.dataptr,msg.datalen);
        uint8_t cnt = get_frame_output_count(tDataPort.tSysInfo.frame);
        if(cnt != tDataPort.FrameMotorCount){
            tDataPort.FrameMotorCount = cnt;
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_frameChanged);
        }
    }
}

void FlyLink::handle_vehicle(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(tDataPort.tVehicle)){
        memcpy(&tDataPort.tVehicle,msg.dataptr,msg.datalen);
        if(!tDataPort.pos_get&&(tDataPort.tVehicle.lat || tDataPort.tVehicle.lng)){
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_firstAvailiablePos);
            tDataPort.pos_get = true;
        }
    }
}

void FlyLink::handle_esc(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(ESC_t)){
        ESC_t pkt{};
        memcpy(&pkt,msg.dataptr,msg.datalen);
        if(pkt.index > FlyLink_MAX_ESC-1){
            return;
        }
        if(pkt.index+1 > tDataPort.ESC_count){
            tDataPort.ESC_count = qMin(pkt.index+1,FlyLink_MAX_ESC);
        }
        tDataPort.tESC[pkt.index] = pkt;
    }
}

void FlyLink::handle_gnss(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(GNSS_t)){
        GNSS_t pkt{};
        memcpy(&pkt,msg.dataptr,msg.datalen);
        if(pkt.index > FlyLink_MAX_SensorBackend-1){
            return;
        }
        if(pkt.index+1 > tDataPort.GNSS_count){
            tDataPort.GNSS_count = qMin(pkt.index+1,FlyLink_MAX_SensorBackend);
        }
        tDataPort.tGNSS[pkt.index] = pkt;
    }
}

void FlyLink::handle_imus(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(IMU_t)){
        IMU_t pkt{};
        memcpy(&pkt,msg.dataptr,msg.datalen);
        if(pkt.index > FlyLink_MAX_SensorBackend-1){
            return;
        }
        if(pkt.index+1 > tDataPort.IMU_count){
            tDataPort.IMU_count = qMin(pkt.index+1,FlyLink_MAX_SensorBackend);
        }
        tDataPort.tIMU[pkt.index] = pkt;
    }
}

void FlyLink::handle_compass(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(Compass_t)){
        Compass_t pkt{};
        memcpy(&pkt,msg.dataptr,msg.datalen);
        if(pkt.index > FlyLink_MAX_SensorBackend-1){
            return;
        }
        if(pkt.index+1 > tDataPort.Compass_count){
            tDataPort.Compass_count = qMin(pkt.index+1,FlyLink_MAX_SensorBackend);
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_MagCountChanged);
        }
        tDataPort.tCompass[pkt.index] = pkt;
    }
}

void FlyLink::handle_baro(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(Baro_t)){
        Baro_t pkt{};
        memcpy(&pkt,msg.dataptr,msg.datalen);
        if(pkt.index > FlyLink_MAX_SensorBackend-1){
            return;
        }
        if(pkt.index+1 > tDataPort.Baro_count){
            tDataPort.Baro_count = qMin(pkt.index+1,FlyLink_MAX_SensorBackend);
        }
        tDataPort.tBaro[pkt.index] = pkt;
    }
}

void FlyLink::handle_rc_out(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(tDataPort.tRC_OUT)){
        memcpy(&tDataPort.tRC_OUT,msg.dataptr,msg.datalen);
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetMotorVal);
//
    }
}

void FlyLink::handle_target(FlyLink_RevMSG msg)
{
    if(msg.datalen == sizeof(tDataPort.tTarget)){
        memcpy(&tDataPort.tTarget,msg.dataptr,msg.datalen);
    }
}

void FlyLink::handle_statustext(FlyLink_RevMSG msg)
{
    status_text_t pkt{};
    if(msg.datalen == sizeof(status_text_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        DisplayMsg(QString(pkt.text));
    }
}

void FlyLink::handle_origin(FlyLink_RevMSG msg)
{
    waypoint_t pkt{};
    if(msg.datalen == sizeof(waypoint_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tDataPort.tOrigin.is_get = true;
        tDataPort.tOrigin.loc = pkt;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Origin_received);
//        DisplayGcsCMD(QStringLiteral("获得原点"));
    }
}

void FlyLink::handle_home(FlyLink_RevMSG msg)
{
    waypoint_t pkt{};
    if(msg.datalen == sizeof(waypoint_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tDataPort.tHome.loc = pkt;
        if(!tDataPort.tHome.is_get){
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Home_FirstReceived);
        }
        tDataPort.tHome.is_get = true;
//        DisplayGcsCMD(QStringLiteral("获得Home点"));
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Home_received);
        //保存为文件
        QSettings setting("./cfg/Setting.ini", QSettings::IniFormat);  //QSettings能记录一些程序中的信息，下次再打开时可以读取出来
        setting.setValue("home/lat",tDataPort.tHome.loc.latitude);  //记录路径到QSetting中保存
        setting.setValue("home/lng",tDataPort.tHome.loc.longitude);  //记录路径到QSetting中保存
    }
}

void FlyLink::handle_waypoint(FlyLink_RevMSG msg)
{
    waypoint_new_t pkt{};
    if(msg.datalen == sizeof(waypoint_new_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        switch(pkt.type){
        case TYPE_RETURN_WAYPOINT:
            tDataPort.RTL.loc = pkt;
            tDataPort.RTL.is_get = true;
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_RTL_Waypoint_received);
            qDebug()<<"handle_waypoint"<<tDataPort.RTL.loc.x<<tDataPort.RTL.loc.y;
            break;
        }
    }
}

void FlyLink::handle_extVol(FlyLink_RevMSG msg)
{
    extVoltage_t pkt{};
    if(msg.datalen == sizeof(extVoltage_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tDataPort.extVol = pkt;
    }
}

void FlyLink::handle_RPMInfo(FlyLink_RevMSG msg)
{
    RPMInfo_t pkt{};
    if(msg.datalen == sizeof(RPMInfo_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tDataPort.RPM = pkt;
//        qDebug()<<"rpm";
    }
}

void FlyLink::handle_GuidanceDevice(FlyLink_RevMSG msg)
{
    GuidanceDeviceInfo_t pkt{};
    if(msg.datalen == sizeof(GuidanceDeviceInfo_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tDataPort.GuidanceInfo = pkt;
    }
}

void FlyLink::handle_Param_failsafe(FlyLink_RevMSG msg)
{
    param_failsafe_t pkt{};
    if(msg.datalen == sizeof(param_failsafe_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.failsafe = pkt;
        tVehicleParam.UpdateFlags.failsafe = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamFailsafe);
    }
}

void FlyLink::handle_Param_MainRC(FlyLink_RevMSG msg)
{
    param_MianRC pkt{};
    if(msg.datalen == sizeof(param_MianRC)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.MainRC = pkt;
        tVehicleParam.UpdateFlags.MainRC = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamMainRC);
    }
}

void FlyLink::handle_Param_AuxRC(FlyLink_RevMSG msg)
{
    param_AuxRC pkt{};
    if(msg.datalen == sizeof(param_AuxRC)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.AuxRC = pkt;
        tVehicleParam.UpdateFlags.AuxRC = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamAuxRC);
    }
}

void FlyLink::handle_Param_Motors(FlyLink_RevMSG msg)
{
    param_Motors pkt{};
    if(msg.datalen == sizeof(param_Motors)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.Motors = pkt;
        tVehicleParam.UpdateFlags.Motors = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamMotors);
    }
}

void FlyLink::handle_Param_GnssPosition(FlyLink_RevMSG msg)
{
    param_GNSSPosition pkt{};
    if(msg.datalen == sizeof(param_GNSSPosition)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        if(pkt.gnss_id >= 2){return;}

        tVehicleParam.GnssPostion[pkt.gnss_id] = pkt;
        if(pkt.gnss_id > 0){
            tVehicleParam.UpdateFlags.GnssPostion2 = true;
        }else{
            tVehicleParam.UpdateFlags.GnssPostion1 = true;
        }
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetGNSSPostion);
    }
}

void FlyLink::handle_Param_InitCtrlCfg(FlyLink_RevMSG msg)
{
    param_initCFGparam_t pkt{};
    if(msg.datalen == sizeof(param_initCFGparam_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.initCtrlCFG = pkt;
        tVehicleParam.UpdateFlags.initCtrlCFG = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamInitCtrlCfg);

    }
}

void FlyLink::handle_Param_PilotControl(FlyLink_RevMSG msg)
{
    param_pilot_control_t pkt{};
    if(msg.datalen == sizeof(param_pilot_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.PilotCtrl = pkt;
        tVehicleParam.UpdateFlags.PilotCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamPilotCtrl);
    }
}

void FlyLink::handle_Param_AutoControl(FlyLink_RevMSG msg)
{
    param_auto_control_t pkt{};
    if(msg.datalen == sizeof(param_auto_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.AutoCtrl = pkt;
        tVehicleParam.UpdateFlags.AutoCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamAutoCtrl);
    }
}

void FlyLink::handle_Param_RollControl(FlyLink_RevMSG msg)
{
    param_att_roll_control_t pkt{};
    if(msg.datalen == sizeof(param_att_roll_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.RollCtrl = pkt;
        tVehicleParam.UpdateFlags.RollCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamRollCtrl);
        qDebug()<<"handle_Param_RollControl";
    }
}

void FlyLink::handle_Param_PitchControl(FlyLink_RevMSG msg)
{
    param_att_pitch_control_t pkt{};
    if(msg.datalen == sizeof(param_att_pitch_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.PitchCtrl = pkt;
        tVehicleParam.UpdateFlags.PitchCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamPitchCtrl);
        qDebug()<<"handle_Param_PitchControl";
    }
}

void FlyLink::handle_Param_Yawontrol(FlyLink_RevMSG msg)
{
    param_att_yaw_control_t pkt{};
    if(msg.datalen == sizeof(param_att_yaw_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.YawCtrl = pkt;
        tVehicleParam.UpdateFlags.YawCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamYawCtrl);
        qDebug()<<"handle_Param_YawControl";
    }
}

void FlyLink::handle_Param_PosZControl(FlyLink_RevMSG msg)
{
    param_posz_control_t pkt{};
    if(msg.datalen == sizeof(param_posz_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.PosZCtrl = pkt;
        tVehicleParam.UpdateFlags.PosZCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamPosZCtrl);
        qDebug()<<"handle_Param_PosZControl";
    }
}

void FlyLink::handle_Param_PosXYControl(FlyLink_RevMSG msg)
{
    param_posxy_control_t pkt{};
    if(msg.datalen == sizeof(param_posxy_control_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.PosXYCtrl = pkt;
        tVehicleParam.UpdateFlags.PosXYCtrl = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamPosXYCtrl);
        qDebug()<<"handle_Param_PosXYControl";
    }
}

void FlyLink::handle_Param_SerialPort(FlyLink_RevMSG msg)
{
    param_SerialPort_t pkt{};
    if(msg.datalen == sizeof(param_SerialPort_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tVehicleParam.SerialPortOption = pkt;
        tVehicleParam.UpdateFlags.SerialPortOption = true;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetParamSerialPortOption);
        qDebug()<<"handle_Param_SerialPort";
        for(int i  = 0 ;i <8 ;i++){
            qDebug()<<tVehicleParam.SerialPortOption.param[i].baud<<tVehicleParam.SerialPortOption.param[i].protocol;
        }
    }
}

void FlyLink::handle_BoardInfo(FlyLink_RevMSG msg)
{
    boardinfo_t pkt{};
    if(msg.datalen == sizeof(boardinfo_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        tDataPort.boardinfo = pkt;
        qDebug()<<"handle_BoardInfo"<<pkt.udid[0]<<pkt.udid[1]<<pkt.udid[2]<<pkt.boardId<<pkt.fw_version<<pkt.link_version<<pkt.total_flight_dis_m<<pkt.total_flight_time_s<<pkt.boardSN;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetBoardInfo);
    }
}

bool FlyLink::send_log_req_info(uint16_t id)
{
    SendPacketByID(FlyLink_ID_REQUEST_LOG_LIST,(void*)&id,sizeof(id));
    return true;
}

bool FlyLink::send_log_req_data(log_request_data_t datainfo)
{
    SendPacketByID(FlyLink_ID_REQUEST_LOG_DATA,(void*)&datainfo,sizeof(datainfo));
    return true;
}

bool FlyLink::send_log_clearAll()
{
    SendPacketByID(FlyLink_ID_LOG_CLEARALL,nullptr,0);

    DisplayGcsCMD(QStringLiteral("清除机载日志"),true);
    return true;
}

void FlyLink::handle_log_info(FlyLink_RevMSG msg)
{
    log_info_t pkt{};
    if(msg.datalen == sizeof(log_info_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        // Handle log Info
        log_list_handle_log_list(pkt);
    }
}

void FlyLink::handle_log_data(FlyLink_RevMSG msg)
{
    log_data_t pkt{};
    if(msg.datalen == sizeof(log_data_t)){
        memcpy(&pkt,msg.dataptr,msg.datalen);
        // Handle log data
        log_file_handle_log_data(pkt);
        //
    }
}

void FlyLink::handle_mission_request(FlyLink_RevMSG msg)
{
    uint16_t request_id = 0xffff;
    if(msg.datalen == sizeof(uint16_t)){
        memcpy(&request_id,msg.dataptr,msg.datalen);
        app_mission_upload_request_handle(request_id);
    }
}

void FlyLink::handle_mission_ack(FlyLink_RevMSG msg)
{
    uint8_t ack = 0xff;
    if(msg.datalen == sizeof(ack)){
        memcpy(&ack,msg.dataptr,msg.datalen);
        app_mission_upload_handle_ack(ack);
    }
}

bool FlyLink::send_mission_count(uint16_t count)
{
    SendPacketByID(FlyLink_ID_MISSION_COUNT,(void*)&count,sizeof(count));
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Item_count);
    return true;
}

bool FlyLink::send_mission_item(mission_item_t item)
{
    SendPacketByID(FlyLink_ID_MISSION_ITEM,(void*)&item,sizeof(item));
    qDebug()<<item.x<<item.y;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Item);
    return true;
}

bool FlyLink::send_mission_ack(uint8_t type)
{
    SendPacketByID(FlyLink_ID_MISSION_ACK,(void*)&type,sizeof(type));
    return true;
}

bool FlyLink::send_mission_request_list()
{
    SendPacketByID(FlyLink_ID_MISSION_REQUEST_LIST,nullptr,0);
    return true;
}

bool FlyLink::send_mission_request(uint16_t seq)
{
    SendPacketByID(FlyLink_ID_MISSION_REQUEST,(void*)&seq,sizeof(seq));
    return true;
}

bool FlyLink::send_mission_clear_all()
{
    SendPacketByID(FlyLink_ID_MISSION_CLEAR_ALL,nullptr,0);
    return true;
}

void FlyLink::handle_mission_item(FlyLink_RevMSG msg)
{
    mission_item_t item{};
    if(msg.datalen == sizeof(item)){
        memcpy(&item,msg.dataptr,msg.datalen);
        app_mission_download_handle_item(item);
    }
}

void FlyLink::handle_mission_count(FlyLink_RevMSG msg)
{
    uint16_t count = 0;
    if(msg.datalen == sizeof(count)){
        memcpy(&count,msg.dataptr,msg.datalen);
        app_mission_download_handle_item_count(count);
    }
}

void FlyLink::log_list_start()
{
    log_list.log_info.clear();
    log_list.rx_id = 0;        /*<  Log id*/
    log_list.num_logs = 0;  /*<  Total number of logs*/
    log_list.last_log_num = 0; /*<  High log number*/
    log_list.loop_timer_10Hz = 0;

    if(log_list.timer_10Hz == nullptr){
        log_list.timer_10Hz = new QTimer();
    }

    log_list.timer_10Hz->start(100);

    connect(log_list.timer_10Hz, SIGNAL(timeout()), this, SLOT(log_list_timer_callback()));
    send_log_req_info(log_list.rx_id);
    qDebug()<<"req list id:"<<log_list.rx_id;
}

void FlyLink::log_list_stop()
{
    log_list.loop_timer_10Hz = 0;
    log_list.timer_10Hz->stop();
    disconnect(log_list.timer_10Hz, SIGNAL(timeout()), this, SLOT(log_list_timer_callback()));
}

void FlyLink::log_list_clear()
{
    log_list.loop_timer_10Hz = 0;
    log_list.timer_10Hz->stop();
    log_list.log_info.clear();
    log_list.rx_id = 0;         /*<  Log id*/
    log_list.num_logs = 0;      /*<  Total number of logs*/
    log_list.last_log_num = 0;  /*<  High log number*/
}

void FlyLink::log_list_timer_callback()
{
    log_list.loop_timer_10Hz++;

    // 500ms 申请超时一次
    if(log_list.loop_timer_10Hz%5 ==0){
        send_log_req_info(log_list.rx_id);
        qDebug()<<"req list id:"<<log_list.rx_id;
    }

    if(log_list.loop_timer_10Hz > 25){
        log_list_stop();

        //触发超时中断提示
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_reqlist_failed);
    }
}

bool FlyLink::log_file_start(uint16_t index)
{
    // 先判断是否存在于LogInfoList
    for(uint16_t i = 0; i < log_list.log_info.length();i++){
        if(index == log_list.log_info[i].id){
            // 建立新的文件内容
            QDir dir;
            if(!dir.exists("log")){
                dir.mkdir("log");
                if(!dir.exists("log/flight")){
                    dir.mkdir("log/flight");
                }
            }
            else{
                if(!dir.exists("log/flight")){
                    dir.mkdir("log/flight");
                }
            }
            dir.setPath("log/flight");
            QString str = dir.filePath(QString().asprintf("%d_",log_list.log_info[i].id)+QDateTime::fromTime_t(log_list.log_info[i].time_utc).toString("yyyyMMdd_hhmmss")+".bin");
            log_file.file = new QFile(str);
            if (!(log_file.file->open(QIODevice::WriteOnly | QIODevice::Truncate))){
                return false; //以读写、覆盖原有内容方式打开文件
            }
            log_file.file->close();

            // 开始获取数据
            log_file.rx_id = index;
            log_file.ofs = 0;
            log_file.size = log_list.log_info[i].size;
            log_file.rx_id = index;
            if(log_file.timer_10Hz == nullptr){
                log_file.timer_10Hz = new QTimer();
            }

            log_file.timer_10Hz->start(100);
            log_file.loop_timer_10Hz = 0;
            connect(log_file.timer_10Hz, SIGNAL(timeout()), this, SLOT(log_file_timer_callback()));
            log_request_data_t pkt{};
            pkt.id = log_file.rx_id;
            pkt.ofs = log_file.ofs;
            pkt.count = qMin((uint32_t)FlyLink_LOG_DataSize,log_file.size - log_file.ofs);
            send_log_req_data(pkt);
            qDebug()<<pkt.id<<"+"<<pkt.ofs<<"+"<<pkt.count;
            return true;
        }
    }
    return false;
}

void FlyLink::log_file_stop()
{
    log_file.timer_10Hz->stop();
    log_file.loop_timer_10Hz = 0;
    disconnect(log_file.timer_10Hz, SIGNAL(timeout()), this, SLOT(log_file_timer_callback()));
    log_file.rx_id = 0xffff; /*<  Log id (from LOG_ENTRY reply)*/
    log_file.ofs = 0; /*<  Offset into the log*/
    log_file.size = 0; /*< [bytes] Number of bytes (zero for end of log)*/
}

void FlyLink::log_file_timer_callback()
{
    log_file.loop_timer_10Hz++;
    // 500ms 超时申请一次
    if(log_file.loop_timer_10Hz % 6 == 0){
        log_request_data_t pkt{};
        pkt.id = log_file.rx_id;
        pkt.ofs = log_file.ofs;
        pkt.count = qMin((uint32_t)FlyLink_LOG_DataSize,log_file.size - log_file.ofs);
        send_log_req_data(pkt);
        qDebug()<<pkt.id<<"+"<<pkt.ofs<<"+"<<pkt.count;
    }

    // 超时3s失败
    if(log_file.loop_timer_10Hz > 30){
        log_file_stop();
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_reqlist_failed);
    }
}

void FlyLink::log_file_handle_log_data(log_data_t &pkt)
{
    if(pkt.id != log_file.rx_id){
        qDebug()<<"logid_err"<<pkt.id;
        return;
    }
    if(pkt.ofs != log_file.ofs){
        qDebug()<<"logofs_err"<<pkt.ofs;
        return;
    }

    if(pkt.count > FlyLink_LOG_DataSize ){
        qDebug()<<"logcnt_err"<<pkt.count;
        return;
    }

    // 接收数据，写入数据
    if (!(log_file.file->open(QIODevice::WriteOnly | QIODevice::Append))){
        qDebug()<<"打开文件错误";
        return; //
    }
    log_file.file->write((char*)pkt.data,pkt.count);
    log_file.file->close();

    log_file.loop_timer_10Hz = 0;

    log_file.ofs += pkt.count;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_getLogData);
    // 判断是否结束
    if(log_file.ofs >=  log_file.size){
        // 接收成功
        log_file_stop();
        log_download_do_next_start();
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_getLogFile);
        return;
    }
    // 申请新的数据
    log_request_data_t req{};
    req.id = log_file.rx_id;
    req.ofs = log_file.ofs;
    req.count = qMin((uint32_t)FlyLink_LOG_DataSize,log_file.size - log_file.ofs);
    send_log_req_data(req);
    qDebug()<<req.id<<"+"<<req.ofs<<"+"<<req.count;
}

void FlyLink::addDownloadIdToList(uint16_t index)
{
    log_download_list.append(index);
}

void FlyLink::log_download_start()
{
    if(log_download_list.isEmpty()){
        DisplayGcsCMD(QStringLiteral("无下载列表"));
        return;
    }
    log_download_do_next_start();
}

void FlyLink::log_download_do_next_start()
{
    if(log_download_list.isEmpty()){
        return;
    }
    log_download_list.first();

    log_file_start(log_download_list.first());
    qDebug()<<"start new file:"<<log_download_list.first();
    log_download_list.removeFirst();
}

bool FlyLink::log_download_current_state(uint16_t &index, uint32_t &size)
{
    index = log_file.rx_id;
    size = log_file.ofs;
    if(0xffff == log_file.rx_id){
        return false;
    }
    return true;
}

void FlyLink::log_download_cancel_all()
{
    log_file_stop();
    log_download_list.clear();

}

void FlyLink::log_download_cancel_current()
{
    log_file_stop();
    log_download_do_next_start();
}

void FlyLink::log_list_insert_log_info(log_info_t &pkt)
{
    QDateTime time =  QDateTime::fromTime_t(pkt.time_utc);
    qDebug()<<"log_info:"<<pkt.id<<"+"<<pkt.size<<"+"<<time;
    for(uint16_t i = 0 ;i < log_list.log_info.length();i++){
        // 已经存在于队列，仅更新数据
        if(pkt.id == log_list.log_info[i].id){
            log_list.log_info[i] = pkt;
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_getLogInfo);
            return;
        }
    }
    // 若不存咋，在放入尾部
    log_list.log_info.append(pkt);
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_getLogInfo);
}

void FlyLink::log_list_handle_log_list(log_info_t &pkt)
{
    if(pkt.num_logs == 0){
        log_list_clear();
        DisplayMsg(QStringLiteral("机载日志为空"));
        return;
    }

    // 有效数据则放入QList中
    log_list_insert_log_info(pkt);

    // 请求新的数据
    log_list.last_log_num = pkt.last_log_num;
    log_list.num_logs = pkt.num_logs;
    if(log_list.rx_id == 0){
        log_list.rx_id = pkt.id;
    }

    if(log_list.rx_id == pkt.id){
        // 最后一个
        if(pkt.id == log_list.last_log_num){
            // 接收完成
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_log_getLogList);
            log_list_stop();
            return;
        }

        // 请求信息
        log_list.rx_id += 1;
        send_log_req_info(log_list.rx_id);
        qDebug()<<"req list id:"<<log_list.rx_id;
    }
}

const FlyLink::mission_download_t &FlyLink::getMission_download() const
{
    return mission_download;
}


bool FlyLink::do_FlashBootloader()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_FlashBootloader;
    DisplayGcsCMD(QStringLiteral("写入出厂数据"),true);
    return send_command(CMD);
}

bool FlyLink::do_Acc3DCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_ACC_CALITYPE_3D;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("加速度3D校准开始"),true);
    return send_command(CMD);
}

bool FlyLink::do_Acc3DCaliCancel()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_ACC_CALITYPE_3D;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Cancel;
    DisplayGcsCMD(QStringLiteral("停止加速度3D校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_Acc3DCaliNextPostion()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_ACC_CALITYPE_3D;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Next;
    DisplayGcsCMD(QStringLiteral("加速度3D校准开始下一面"),true);
    return send_command(CMD);
}

bool FlyLink::do_AccTrimCali()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_ACC_CALITYPE_TRIM;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("加速度水平校准开始"),true);
    return send_command(CMD);
}

bool FlyLink::do_AccSimpleCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_ACC_CALITYPE_SIMPLE;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("加速度基础校准开始"),true);
    return send_command(CMD);
}

bool FlyLink::do_BaroCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_BARO;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("执行气压校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_AirspeedCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_Airspeed;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("执行空速校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_GyroCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_GYRO;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("执行陀螺零漂校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_MagCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_Compass;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("执行罗盘校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_MagCaliStop()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_Compass;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Cancel;
    DisplayGcsCMD(QStringLiteral("停止罗盘校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_MagSimpleCaliStart(uint16_t fixed_yaw)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_CompassSimple;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    CMD.param.Calibration.param_val = fixed_yaw;

    DisplayGcsCMD(QStringLiteral("执行罗盘简单校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_MagInFlightCaliStart()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_CompassInFlight;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Start;
    DisplayGcsCMD(QStringLiteral("执行罗盘空中校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_MagInFlightCaliCancel()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Calibration;
    CMD.param.Calibration.CaliType = CMD_CALITYPE_CompassInFlight;
    CMD.param.Calibration.CaliStep = CMD_ACC_CALISTEP_Cancel;
    DisplayGcsCMD(QStringLiteral("取消罗盘空中校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_ESCcali_start()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Motor_test;
    CMD.param.SetMotors.esc_cali = ESC_Cali_Start;
    DisplayGcsCMD(QStringLiteral("开始电调校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_ESCcali_stop()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Motor_test;
    CMD.param.SetMotors.esc_cali = ESC_Cali_Stop;
    DisplayGcsCMD(QStringLiteral("结束电调校准"),true);
    return send_command(CMD);
}

bool FlyLink::do_ESCcali_toggle()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Motor_test;
    CMD.param.SetMotors.esc_cali = ESC_Cali_shift;
    DisplayGcsCMD(QStringLiteral("切换校准电平"),true);
    return send_command(CMD);
}

bool FlyLink::do_MotorTest_stop()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Motor_test;
    CMD.param.SetMotors.num = 0;
    DisplayGcsCMD(QStringLiteral("停止电机测试"),true);
    return send_command(CMD);
}

bool FlyLink::do_MotorTest(uint8_t seq, uint8_t num, uint8_t time, uint8_t pct)
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_Motor_test;
    CMD.param.SetMotors.id = seq;
    CMD.param.SetMotors.num = num;
    CMD.param.SetMotors.pct = pct;
    CMD.param.SetMotors.time = time;
    CMD.param.SetMotors.esc_cali = ESC_Cali_None;
    DisplayGcsCMD(QStringLiteral("电机测试"),true);
    return send_command(CMD);
}

bool FlyLink::do_reqParamAll()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = 0;
    return send_command(CMD);
}

bool FlyLink::do_reqParamfailsafe()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_FAILSAFE;
    return send_command(CMD);
}

bool FlyLink::do_setParamfailsafe(param_failsafe_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_FAILSAFE,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置故障保护参数"),true);
    return true;
}

bool FlyLink::do_reqParamMainRC()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_MAIN_RC;
    return send_command(CMD);
}

bool FlyLink::do_setParamMainRC(param_MianRC pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_MAIN_RC,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置RC参数"),true);
    return true;
}

bool FlyLink::do_reqParamAuxRC()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_AUX_RC;
    return send_command(CMD);
}

bool FlyLink::do_setParamAuxRC(param_AuxRC pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_AUX_RC,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置RC通道参数"),true);
    return true;
}

bool FlyLink::do_reqParamMotors()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_MOTORS;
    return send_command(CMD);
}

bool FlyLink::do_setParamMotors(param_Motors pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_MOTORS,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置电机参数"),true);
    return true;
}

bool FlyLink::do_reqParamGNSSPosition()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_GNSS_POSITION;
    return send_command(CMD);
}

bool FlyLink::do_setParamGNSSPosition(param_GNSSPosition pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_GNSS_POSITION,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置卫星天线位置"),true);
    return true;
}

bool FlyLink::do_reqParamInitCtrlCfg()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_INIT_CFG_PARAM;
    return send_command(CMD);
}

bool FlyLink::do_setParamInitCtrlCfg(param_initCFGparam_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_INIT_CFG_PARAM,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置控制初始参数"),true);
    return true;
}

bool FlyLink::do_reqParamPilotCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_PILOT_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamPilotCtrl(param_pilot_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_PILOT_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置辅助控制参数"),true);
    return true;
}

bool FlyLink::do_reqParamAutoCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_AUTO_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamAutoCtrl(param_auto_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_AUTO_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置自动控制参数"),true);
    return true;
}

bool FlyLink::do_reqParamRollCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_Roll_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamRollCtrl(param_att_roll_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_Roll_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置滚转轴控制参数"),true);
    return true;
}

bool FlyLink::do_reqParamPitchCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_Pitch_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamPitchCtrl(param_att_pitch_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_Pitch_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置俯仰轴控制参数"),true);
    return true;
}

bool FlyLink::do_reqParamYawCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_Yaw_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamYawCtrl(param_att_yaw_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_Yaw_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置航向轴控制参数"),true);
    return true;
}

bool FlyLink::do_reqParamPosZCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_POSZ_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamPosZCtrl(param_posz_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_POSZ_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置高度控制参数"),true);
    return true;
}

bool FlyLink::do_reqParamPosXYCtrl()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_POSXY_CONTROL;
    return send_command(CMD);
}

bool FlyLink::do_setParamPosXYCtrl(param_posxy_control_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_POSXY_CONTROL,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置水平位置控制参数"),true);
    return true;
}

bool FlyLink::req_ParamSerialPort()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_PARAM_SerialPort;
    return send_command(CMD);
}

bool FlyLink::do_setParamSerialPort(param_SerialPort_t pkt)
{
    pkt.is_set = true;
    SendPacketByID(FlyLink_ID_PARAM_SerialPort,(void*)&pkt,sizeof(pkt));
    DisplayGcsCMD(QStringLiteral("设置飞控串口配置参数"),true);
    return true;
}

const FlyLink::VehicleParam_t &FlyLink::getTVehicleParam() const
{
    return tVehicleParam;
}

bool FlyLink::req_boardInfo()
{
    Command_t CMD{};
    CMD.cmd_id = FlyLink_CMD_ID_ReqMSG;
    CMD.param.ReqMsg.id = FlyLink_ID_BoardInfo;
    return send_command(CMD);
}

const FlyLink::mission_upload_t &FlyLink::getMission_upload() const
{
    return mission_upload;
}

const FlyLink::mission_local_t &FlyLink::getLocal_mission() const
{
    return local_mission;
}

void FlyLink::setLocal_mission(const mission_local_t &newLocal_mission)
{
    local_mission = newLocal_mission;
}

void FlyLink::app_mission_upload_start()
{
    if(mission_upload.is_uploading){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_mission_is_uploading);
        DisplayGcsCMD(QStringLiteral("正在上传"));
        return;
    }

    if(mission_download.is_downloading){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Failed);
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_mission_is_downloading);
        DisplayGcsCMD(QStringLiteral("无法上传,当前正在下载航线"));
        return;
    }

    // 判断通信是否连接
    if(!getIs_active()){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Failed);
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_link_is_no_active);
        DisplayGcsCMD(QStringLiteral("无法上传,通信异常"));
        return;
    }

    DisplayGcsCMD(QStringLiteral("上传航线"));
    app_mission_upload_init();
    send_mission_count(app_mission_item_count());
}

void FlyLink::app_mission_upload_init()
{
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mission_upload.time_last_get_request = 0;
    mission_upload.time_start_upload = tnow;
    mission_upload.time_last_upload = tnow;
    mission_upload.progress = 0;
    mission_upload.upload_request_id = 0;
    mission_upload.is_uploading = true;
}

void FlyLink::app_mission_upload_end()
{
    mission_upload.is_uploading = false;
    mission_upload.time_last_get_request = 0;
    mission_upload.time_start_upload = 0;
    mission_upload.time_last_upload = 0;
    mission_upload.progress = 1;
    mission_upload.upload_request_id = 0;
}

int FlyLink:: app_mission_item_count()
{
    return local_mission.mission.count()+1;
}

void FlyLink::app_mission_upload_handle_ack(uint8_t ack)
{
    if(mission_upload.is_uploading){
        switch(ack){
            case MAV_MISSION_ACCEPTED:
                {
                    // 上传成功
                    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Succeed);
                    DisplayGcsCMD(QStringLiteral("航线上传成功"));
                    app_mission_upload_end();
                }
                break;
            case MAV_MISSION_NO_SPACE:
                {
                    // 上传失败
                    DisplayMsg(QStringLiteral("任务超过最大数量"));
                    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Failed);
                    app_mission_upload_end();
                }
                break;
            case MAV_MISSION_ERROR:
                {
                    // 上传失败
                    DisplayGcsCMD(QStringLiteral("航线上传失败"));
                    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Failed);
                    app_mission_upload_end();
                }
                break;
        }
    }
}

void FlyLink::handle_Acc3DCali(FlyLink_RevMSG msg)
{
    uint8_t position = 0;
    if(msg.datalen != sizeof(position)){
        return;
    }
    memcpy(&position,msg.dataptr,msg.datalen);
    tDataPort.Acc3DCaliPostion = position;
    qDebug()<<position;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Acc3DCaliPostion);
}

void FlyLink::handle_MagCaliProgress(FlyLink_RevMSG msg)
{
    CompassCaliProgress_t progress{};
    if(msg.datalen != sizeof(progress)){
        return;
    }
    memcpy(&progress,msg.dataptr,msg.datalen);

    if(progress.id > FlyLink_MAX_SensorBackend-1){
        return;
    }
    if(progress.id+1 > tDataPort.MagCaliCount){
        tDataPort.MagCaliCount = qMin(progress.id+1,FlyLink_MAX_SensorBackend);
    }
    tDataPort.MagCaliProgress[progress.id] = progress;
    qDebug()<<progress.id<<progress.completion_pct;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_MagCaliProgress);
}

bool FlyLink::app_mission_download_start()
{
    if(mission_upload.is_uploading){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_download_Failed);
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_mission_is_uploading);
        DisplayGcsCMD(QStringLiteral("无法下载,正在上传航线"));
        return false;
    }
    if(mission_download.is_downloading){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_mission_is_downloading);
        DisplayGcsCMD(QStringLiteral("正在下载"));
        return false;
    }

    // 判断通信是否连接
    if(!getIs_active()){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_download_Failed);
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_link_is_no_active);
        DisplayGcsCMD(QStringLiteral("无法下载,通信连接异常"));
        return false;
    }

    // 清除本地航线
    app_mission_download_init();
    local_mission.mission.clear();
    send_mission_request_list();
    mission_download.time_last_request_count = QDateTime::currentDateTime().toMSecsSinceEpoch();
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Download_start);
    DisplayGcsCMD(QStringLiteral("下载航线"));
    return true;
}

uint8_t FlyLink::get_vehicle_frame()
{
    return tDataPort.tSysInfo.frame;
}

uint8_t FlyLink::get_vehicle_frame(uint8_t frame_class, uint8_t frame_type)
{
    uint8_t frame = Frame_UNDIFINE;
    switch(frame_class){
        case MOTOR_FRAME_QUAD:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_PLUS          :frame = FrameQuad_Plus         ;break;
                case MOTOR_FRAME_TYPE_X             :frame = FrameQuad_X            ;break;
                case MOTOR_FRAME_TYPE_NYT_PLUS      :frame = FrameQuad_NYT_PLUS     ;break;
                case MOTOR_FRAME_TYPE_NYT_X         :frame = FrameQuad_NYT_NYT_X    ;break;
                case MOTOR_FRAME_TYPE_BF_X          :frame = FrameQuad_BF_X         ;break;
                case MOTOR_FRAME_TYPE_BF_X_REV      :frame = FrameQuad_BF_X_REV     ;break;
                case MOTOR_FRAME_TYPE_DJI_X         :frame = FrameQuad_DJI_X        ;break;
                case MOTOR_FRAME_TYPE_CW_X          :frame = FrameQuad_CW_X         ;break;
                case MOTOR_FRAME_TYPE_V             :frame = FrameQuad_V            ;break;
                case MOTOR_FRAME_TYPE_H             :frame = FrameQuad_H            ;break;
                case MOTOR_FRAME_TYPE_VTAIL         :frame = FrameQuad_VTAIL        ;break;
                case MOTOR_FRAME_TYPE_ATAIL         :frame = FrameQuad_ATAIL        ;break;
                case MOTOR_FRAME_TYPE_PLUSREV       :frame = FrameQuad_PLUSREV      ;break;

                case MOTOR_FRAME_TYPE_USER_X        :frame = FrameQuad_User_X4      ;break;
                case MOTOR_FRAME_TYPE_USER_CW_X     :frame = FrameQuad_User_X4R     ;break;
                case MOTOR_FRAME_TYPE_USER_PLUS     :frame = FrameQuad_User_I4      ;break;
                case MOTOR_FRAME_TYPE_USER_CW_PLUS  :frame = FrameQuad_User_I4R     ;break;
                case MOTOR_FRAME_TYPE_USER_H        :frame = FrameQuad_User_H4      ;break;
            }break;
        }break;

        case MOTOR_FRAME_HEXA:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_PLUS          :frame = FrameHex_PLUS          ;break;
                case MOTOR_FRAME_TYPE_X             :frame = FrameHex_X             ;break;
                case MOTOR_FRAME_TYPE_H             :frame = FrameHex_H             ;break;
                case MOTOR_FRAME_TYPE_DJI_X         :frame = FrameHex_DJI_X         ;break;
                case MOTOR_FRAME_TYPE_CW_X          :frame = FrameHex_CW_X          ;break;

                case MOTOR_FRAME_TYPE_USER_CW_PLUS  :frame = FrameHex_User_I6R      ;break;
                case MOTOR_FRAME_TYPE_USER_PLUS     :frame = FrameHex_User_I6       ;break;
                case MOTOR_FRAME_TYPE_USER_X        :frame = FrameHex_User_V6       ;break;
                case MOTOR_FRAME_TYPE_USER_CW_X     :frame = FrameHex_User_V6R      ;break;
            }break;
        }break;

        case MOTOR_FRAME_OCTA:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_PLUS         :frame = FrameOctA_PLUS          ;break;
                case MOTOR_FRAME_TYPE_X            :frame = FrameOctA_X             ;break;
                case MOTOR_FRAME_TYPE_V            :frame = FrameOctA_V             ;break;
                case MOTOR_FRAME_TYPE_H            :frame = FrameOctA_H             ;break;
                case MOTOR_FRAME_TYPE_I            :frame = FrameOctA_I             ;break;
                case MOTOR_FRAME_TYPE_DJI_X        :frame = FrameOctA_DJI_X         ;break;
                case MOTOR_FRAME_TYPE_CW_X         :frame = FrameOctA_CW_X          ;break;

                case MOTOR_FRAME_TYPE_USER_PLUS    :frame = FrameOctA_User_I8       ;break;
                case MOTOR_FRAME_TYPE_USER_CW_PLUS :frame = FrameOctA_User_I8R      ;break;
                case MOTOR_FRAME_TYPE_USER_X       :frame = FrameOctA_User_O8       ;break;
                case MOTOR_FRAME_TYPE_USER_CW_X    :frame = FrameOctA_User_O8R      ;break;
            }break;
        }break;

        //======================4轴8桨=
        case MOTOR_FRAME_OCTAQUAD:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_PLUS         :frame = FrameOctAQuad_PLUS      ;break;
                case MOTOR_FRAME_TYPE_X            :frame = FrameOctAQuad_X         ;break;
                case MOTOR_FRAME_TYPE_V            :frame = FrameOctAQuad_V         ;break;
                case MOTOR_FRAME_TYPE_H            :frame = FrameOctAQuad_H         ;break;
                case MOTOR_FRAME_TYPE_CW_X         :frame = FrameOctAQuad_CW_X      ;break;

                case MOTOR_FRAME_TYPE_USER_X       :frame = FrameOctAQuad_User_X8   ;break;
                case MOTOR_FRAME_TYPE_USER_CW_X    :frame = FrameOctAQuad_User_X8R  ;break;
                case MOTOR_FRAME_TYPE_USER_H       :frame = FrameOctAQuad_User_X8CRP;break;
                case MOTOR_FRAME_TYPE_USER_PLUS    :frame = FrameOctAQuad_User_IX8  ;break;
                case MOTOR_FRAME_TYPE_USER_CW_PLUS :frame = FrameOctAQuad_User_IX8R ;break;
            }break;
        }break;

        //======================6轴12桨
        case MOTOR_FRAME_DODECAHEXA:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_PLUS         :frame = FrameDodecaHexA_PLUS       ;break;
                case MOTOR_FRAME_TYPE_X            :frame = FrameDodecaHexA_X          ;break;
                case MOTOR_FRAME_TYPE_USER_CW_PLUS :frame = FrameDodecaHexA_User_I12R  ;break;
                case MOTOR_FRAME_TYPE_USER_PLUS    :frame = FrameDodecaHexA_User_I12   ;break;
                case MOTOR_FRAME_TYPE_USER_X       :frame = FrameDodecaHexA_User_X12   ;break;
                case MOTOR_FRAME_TYPE_USER_CW_X    :frame = FrameDodecaHexA_User_X12R  ;break;
                case MOTOR_FRAME_TYPE_USER_H       :frame = FrameDodecaHexA_User_X12CRP;break;
            }break;
        }break;

        //======================Y6
        case MOTOR_FRAME_Y6:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_Y6B         :frame = FrameY6_Y6B            ;break;
                case MOTOR_FRAME_TYPE_Y6F         :frame = FrameY6_Y6F            ;break;
                case MOTOR_FRAME_TYPE_PLUS        :frame = FrameY6_Y6             ;break;
                case MOTOR_FRAME_TYPE_USER_X      :frame = FrameY6_User_Y6        ;break;
                case MOTOR_FRAME_TYPE_USER_CW_X   :frame = FrameY6_User_Y6R       ;break;
                case MOTOR_FRAME_TYPE_USER_PLUS   :frame = FrameY6_User_IY6        ;break;
                case MOTOR_FRAME_TYPE_USER_CW_PLUS:frame = FrameY6_User_IY6R       ;break;
            }break;
        }break;

        case MOTOR_FRAME_DECA:{
            switch(frame_type){
                case MOTOR_FRAME_TYPE_PLUS          :frame = FrameDecA_PLUS         ;break;
                case MOTOR_FRAME_TYPE_X             :frame = FrameDecA_X            ;break;

            }break;
        }break;

        default:break;
    }
    return frame;
}

bool FlyLink::set_vehicle_frame(const uint8_t &frame)
{
    if(getIs_active()&&!tDataPort.tSysInfo.state1.state.armed){
        int8_t frame_class = MOTOR_FRAME_UNDEFINED;
        int8_t frame_type = MOTOR_FRAME_TYPE_PLUS;
        switch(frame){
            // ardupilot
            case FrameQuad_Plus         :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            case FrameQuad_X            :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_X);break;
            case FrameQuad_NYT_PLUS     :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_NYT_PLUS);break;
            case FrameQuad_NYT_NYT_X    :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_NYT_X);break;
            case FrameQuad_BF_X         :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_BF_X);break;
            case FrameQuad_BF_X_REV     :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_BF_X_REV);break;
            case FrameQuad_DJI_X        :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_DJI_X);break;
            case FrameQuad_CW_X         :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_CW_X);break;
            case FrameQuad_V            :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_V);break;
            case FrameQuad_H            :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_H);break;
            case FrameQuad_VTAIL        :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_VTAIL);break;
            case FrameQuad_ATAIL        :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_ATAIL);break;
            case FrameQuad_PLUSREV      :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_PLUSREV);break;

            /* 四旋翼 USER Frame */
            case FrameQuad_User_X4      :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_USER_X);break;
            case FrameQuad_User_X4R     :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_USER_CW_X);break;
            case FrameQuad_User_I4      :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_USER_PLUS);break;
            case FrameQuad_User_I4R     :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_USER_CW_PLUS);break;
            case FrameQuad_User_H4      :frame_class = (MOTOR_FRAME_QUAD);frame_type = (MOTOR_FRAME_TYPE_USER_H);break;
            //======================六旋翼==
            // ardupilot
            case FrameHex_PLUS          :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            case FrameHex_X             :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_X);break;
            case FrameHex_H             :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_H);break;
            case FrameHex_DJI_X         :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_DJI_X);break;
            case FrameHex_CW_X          :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_CW_X);break;
            /* 六旋翼 USER Frame */
            case FrameHex_User_I6R      :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_USER_CW_PLUS);break;
            case FrameHex_User_I6       :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_USER_PLUS);break;
            case FrameHex_User_V6       :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_USER_X);break;
            case FrameHex_User_V6R      :frame_class = (MOTOR_FRAME_HEXA);frame_type = (MOTOR_FRAME_TYPE_USER_CW_X);break;
            //======================8旋翼==
            // ardupilo
            case FrameOctA_PLUS         :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            case FrameOctA_X            :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_X);break;
            case FrameOctA_V            :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_V);break;
            case FrameOctA_H            :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_H);break;
            case FrameOctA_I            :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_I);break;
            case FrameOctA_DJI_X        :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_DJI_X);break;
            case FrameOctA_CW_X         :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_CW_X);break;
            /* 8旋翼 USER Frame */
            case FrameOctA_User_I8      :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_USER_PLUS);break;
            case FrameOctA_User_I8R     :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_USER_CW_PLUS);break;
            case FrameOctA_User_O8      :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_USER_X);break;
            case FrameOctA_User_O8R     :frame_class = (MOTOR_FRAME_OCTA);frame_type = (MOTOR_FRAME_TYPE_USER_CW_X);break;
            //======================4轴8桨=
            // ardupilot
            case FrameOctAQuad_PLUS     :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            case FrameOctAQuad_X        :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_X);break;
            case FrameOctAQuad_V        :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_V);break;
            case FrameOctAQuad_H        :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_H);break;
            case FrameOctAQuad_CW_X     :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_CW_X);break;

            /* 4轴8桨 USER Frame */
            case FrameOctAQuad_User_X8  :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_USER_X);break;
            case FrameOctAQuad_User_X8R :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_USER_CW_X);break;
            case FrameOctAQuad_User_X8CRP:  frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_USER_H);break;
            case FrameOctAQuad_User_IX8 :   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_USER_PLUS);break;
            case FrameOctAQuad_User_IX8R:   frame_class = (MOTOR_FRAME_OCTAQUAD);frame_type = (MOTOR_FRAME_TYPE_USER_CW_PLUS);break;
            //======================6轴12桨
            // ardupilot
            case FrameDodecaHexA_PLUS       :frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            case FrameDodecaHexA_X          :frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_X);break;
            /* 6轴12桨 USER Frame */
            case FrameDodecaHexA_User_I12R  :frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_USER_CW_PLUS);break;
            case FrameDodecaHexA_User_I12   :frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_USER_PLUS);break;
            case FrameDodecaHexA_User_X12   :frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_USER_X);break;
            case FrameDodecaHexA_User_X12R  :frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_USER_CW_X);break;
            case FrameDodecaHexA_User_X12CRP:frame_class = (MOTOR_FRAME_DODECAHEXA);frame_type = (MOTOR_FRAME_TYPE_USER_H);break;
            //======================Y6 3轴
            // ardupilot
            case FrameY6_Y6B            :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_Y6B);break;
            case FrameY6_Y6F            :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_Y6F);break;
            case FrameY6_Y6             :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            /* Y6 3轴6桨 USER Frame */
            case FrameY6_User_Y6        :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_USER_X);break;
            case FrameY6_User_Y6R       :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_USER_CW_X);break;
            case FrameY6_User_IY6        :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_USER_PLUS);break;
            case FrameY6_User_IY6R       :frame_class = (MOTOR_FRAME_Y6);frame_type = (MOTOR_FRAME_TYPE_USER_CW_PLUS);break;
            //======================12旋翼
            // ardupilot
            case FrameDecA_PLUS         :frame_class = (MOTOR_FRAME_DECA);frame_type = (MOTOR_FRAME_TYPE_PLUS);break;
            case FrameDecA_X            :frame_class = (MOTOR_FRAME_DECA);frame_type = (MOTOR_FRAME_TYPE_X);break;
            //======================自定义构型
            default:
                frame_class = (MOTOR_FRAME_UNDEFINED);
                break;
        }

        CommonParam_t pkt{};
        bool ok = false;
        // 发送 FRAMECLASS
        char classname[]="FRAME_CLASS";
        memcpy(pkt.param_name,classname,strlen(classname));
        pkt.param_value = frame_class;
        ok|=set_CommonParameter(pkt);

        // 发送 FRAMETYPE
        memset(&pkt,0,sizeof(pkt));
        char frametypename[] = "FRAME_TYPE";
        memcpy(pkt.param_name,frametypename,strlen(frametypename));
        pkt.param_value = frame_type;
        ok|=set_CommonParameter(pkt);
        return ok;
    }
    DisplayGcsCMD(QStringLiteral("当前状态不允许配置布局"));
    return false;
}


void FlyLink::app_mission_download_init()
{
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mission_download.time_start_download = tnow;
    mission_download.time_last_request_item = 0;
    mission_download.time_last_get_item = 0;
    mission_download.time_last_request_count = 0;
    mission_download.download_request_id = 0;
    mission_download.download_item_count = 0;
    mission_download.time_last_get_count = 0;
    mission_download.progress = 0;
    mission_download.is_downloading = true;
}

void FlyLink::app_mission_download_update()
{
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if(!mission_download.is_downloading){
        return;
    }
    /* --------------------- 超时结束 -------------------*/
        // 超过5s 未收到 count
    if((mission_download.time_last_get_count == 0 && \
       (tnow - mission_download.time_start_download > 5000)) ||
        // 超时5s 未收到item
       (mission_download.time_last_get_count != 0 && \
       (tnow - mission_download.time_last_get_item > 5000) &&  \
       mission_download.time_last_get_item !=0) ||

        (mission_download.time_last_get_count != 0 && \
        (tnow - mission_download.time_last_get_count > 5000) &&  \
        mission_download.time_last_get_item ==0)){
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_download_Failed);
        DisplayGcsCMD(QStringLiteral("航线下载失败"));
        app_mission_download_end();
    }

    // 超时申请 count
    if(mission_download.time_last_get_count == 0 && (tnow - mission_download.time_last_request_count > 1000)){
        send_mission_request_list();
        mission_download.time_last_request_count = tnow;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Download_request_list);
    }

    // 超时申请 item
    if(mission_download.time_last_get_count != 0 && (tnow - mission_download.time_last_request_item > 1000)){
        send_mission_request(mission_download.download_request_id);
        mission_download.time_last_request_item = tnow;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Download_request_item);
    }
}

void FlyLink::app_mission_download_end()
{
    mission_download.time_start_download = 0;
    mission_download.time_last_request_item = 0;
    mission_download.time_last_get_item = 0;
    mission_download.time_last_request_count = 0;
    mission_download.download_request_id = 0;
    mission_download.download_item_count = 0;
    mission_download.time_last_get_count = 0;
    mission_download.progress = 0;
    mission_download.is_downloading = false;
}

void FlyLink::app_mission_download_handle_item_count(uint16_t count)
{
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mission_download.download_item_count = count;
    mission_download.time_last_get_count = tnow;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Download_get_item_count);
}

void FlyLink::app_mission_download_handle_item(mission_item_t item)
{
    // 序列是否一致
    if(mission_download.download_request_id != item.seq){
        return;
    }
    // 存储航点
    if(item.seq == 0){
    }
    else{
        if(item.seq < app_mission_item_count()){
            local_mission.mission.replace(item.seq-1,item);
        }
        else{
            local_mission.mission.append(item);
        }
    }
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mission_download.time_last_get_item = tnow;
    mission_download.progress = (float)(mission_download.download_request_id+1)/mission_download.download_item_count;
    ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Download_get_item);

    // 申请新航点
    if(mission_download.download_request_id < mission_download.download_item_count-1){
        mission_download.download_request_id++;

        send_mission_request(mission_download.download_request_id);
        mission_download.time_last_request_item = tnow;
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Download_request_item);
    }
    // 接收结束
    else{
        app_mission_download_end();
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_download_Succeed);
        DisplayGcsCMD(QStringLiteral("航线下载成功"));
    }
}

void FlyLink::handle_CommonParamter(FlyLink_RevMSG msg)
{
    CommonParam_t param{};
    if(msg.datalen == sizeof(param)){
        memcpy(&param,msg.dataptr,msg.datalen);
        QString str = QString(param.param_name);
        ParamSetValue_ByName(str,param.param_value);
        // 收到=安装方向
        if(str.contains("AHRS_ORIENTATION",Qt::CaseInsensitive)){
            tDataPort.BoardOrientation = param.param_value;
            ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetBoardOrientation);
        }
        QVariant var;
        var.setValue(param);
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_GetCommonParameter,var);

        qDebug()<<param.param_index<<param.param_name<<param.param_value;

    }
}

void FlyLink::ResetAllVariant()
{
    memset(&tDataPort,0,sizeof(tDataPort));
    memset(&tVehicleParam,0,sizeof(tVehicleParam));
}

bool FlyLink::send_ReqCommonParameter(CommonParamReq_t pkt)
{
    SendPacketByID(FlyLink_ID_COMMOM_PARAM_REQ,(void*)&pkt,sizeof(pkt));
    return true;
}

bool FlyLink::send_ReqCommonParameter(QString str)
{
    CommonParamReq_t pkt{};
    pkt.param_index = -1;
    // 转换 Name
    char *msg;
    QByteArray namebuf = str.toLatin1();
    msg = namebuf.data();
    memcpy(pkt.param_name,msg,qMin((int)strlen(msg),16));
    pkt.param_name[16] = 0;

    return send_ReqCommonParameter(pkt);
}

bool FlyLink::set_CommonParameter(CommonParam_t pkt)
{
    SendPacketByID(FlyLink_ID_COMMOM_PARAM,(void*)&pkt,sizeof(pkt));
    return true;
}

bool FlyLink::set_CommonParameter(QString str, float val)
{
    FlyLink::CommonParam_t parameters{};
    parameters.param_index = -1;

    // name
    char *msg;
    QByteArray namebuf = str.toLatin1();
    msg = namebuf.data();
    memcpy(parameters.param_name,msg,qMin((int)strlen(msg),16));
    parameters.param_name[16] = 0;

    // 转换 Value
    parameters.param_value = val;    /*<  Onboard parameter value*/
    return set_CommonParameter(parameters);
}

bool FlyLink::set_BoardOrientation(uint8_t Orientation)
{
    DisplayGcsCMD(QStringLiteral("设置安装方向"));
    if(tDataPort.tSysInfo.state1.state.isflying){
        DisplayGcsCMD(QStringLiteral("飞行中,禁止修改安装方向。"));
        return false;
    }
    return set_CommonParameter(QStringLiteral("AHRS_ORIENTATION"),Orientation);
}

bool FlyLink::req_BoardOrientation()
{
    return send_ReqCommonParameter(QStringLiteral("AHRS_ORIENTATION"));
}



int FlyLink::send_TransparentDataToFC(QByteArray arr, uint8_t Payload_type)
{
    int payload_rellen = arr.size();
    uint8_t payload_len = (payload_rellen > 128) ? 128 : payload_rellen;

    QByteArray data;
    // 第一字节 载荷类型，第二字节载荷数据长度（最大128），接下来是数据
    data.resize(payload_len + 1);
    data[0] = Payload_type;
    memcpy(data.data()+1,arr.data(),payload_len);
    SendPacketByID(FlyLink_ID_Transparent,data);
    return payload_len;
}

void FlyLink::handle_Transparent(FlyLink_RevMSG msg)
{
    // 没有有效数据
    if(msg.datalen <= 1){
        return;
    }

    QByteArray ArrData;
    ArrData.resize(msg.datalen);
    memcpy(ArrData.data(),msg.dataptr,msg.datalen);
    QByteArray Data;
    Data.resize(msg.datalen - 1);
    memcpy(Data.data(),ArrData.data()+1,Data.size());
    uint8_t PayloadType = ArrData[0];
    switch(PayloadType){
    case PayloadType_YJYVedioControl:
            Recive_Transparent_YJYVedioControl(Data);
        break;

    default:
        break;
    }
}

void FlyLink::Write_Transparent_YJYVedioControl(QByteArray arr)
{
    RXBuf_YJYVedioControl.append(arr);
}

void FlyLink::Send_Transparent_YJYVedioControl()
{
    if(RXBuf_YJYVedioControl.isEmpty()){
        return;
    }
    uint8_t sendLen = (RXBuf_YJYVedioControl.size() > 128 )?128:RXBuf_YJYVedioControl.size();
    QByteArray ArrData;
    ArrData.resize(sendLen);
    memcpy(ArrData.data(),RXBuf_YJYVedioControl.data(),sendLen);
    int removelen = send_TransparentDataToFC(ArrData,PayloadType_YJYVedioControl);
    RXBuf_YJYVedioControl.remove(0,removelen);
}

void FlyLink::Recive_Transparent_YJYVedioControl(QByteArray arr)
{
    qDebug()<<"Recive_Transparent_YJYVedioControl"<<arr;
    if( Qt::DMMM()->Payload() != nullptr){
        Qt::DMMM()->Payload()->YJYVideoControl_DataSend(arr);
    }
}

void FlyLink::app_mission_upload_update()
{
    if(!mission_upload.is_uploading){
        return;
    }

    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    // 上传超时
    if((mission_upload.time_last_get_request == 0 && (tnow - mission_upload.time_start_upload) > 5000) ||
       (mission_upload.time_last_get_request != 0 && (tnow - mission_upload.time_last_get_request) > 5000)){
        app_mission_upload_end();
        DisplayGcsCMD(QStringLiteral("任务上传失败"));
        ProtocolEvent(Q_DMMM::DMMM_GCSEvent_Mission_Upload_Failed);
    }

    // 上传count超时
    if(mission_upload.time_last_get_request == 0 && (tnow- mission_upload.time_last_upload) > 1000){
        send_mission_count(app_mission_item_count());
        mission_upload.time_last_upload = tnow;
    }
}

void FlyLink::app_mission_upload_request_handle(uint16_t request_id)
{
    if(request_id > (app_mission_item_count()-1) ){
        DisplayGcsCMD(QStringLiteral("飞控请求的任务ID错误"));
        return;
    }
    qint64 tnow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    mission_upload.time_last_get_request = tnow;

    mission_item_t pkt{};
    if(request_id == 0){
        pkt.command = 16;
        pkt.z = 100;
        pkt.x = 341527625;
        pkt.y = 1088370466;
    }
    else{
        pkt = local_mission.mission.at(request_id - 1);
    }
    pkt.seq = request_id;
    send_mission_item(pkt);
    mission_upload.upload_request_id = request_id;
    mission_upload.progress = app_mission_item_count()<=0 ? 0 : ((mission_upload.upload_request_id+1)/ (float)(app_mission_item_count()));
}

void FlyLink::DisplayMsg(const QString &str,int id)
{
    Q_UNUSED(id);
    if(Qt::DMMM() != nullptr){
        Q_DMMM::text_msg_t MSG = {};
        MSG.id = getIdentity();
        MSG.str = str;
        Qt::DMMM()->push_msg(MSG);
    }
}

void FlyLink::DisplayGcsCMD(const QString &str ,bool need_uav_pre)
{
    if(Qt::DMMM() != nullptr){
        Q_DMMM::text_msg_t MSG = {};
        MSG.id = Qt::DMMM()->getGcs_id();
        if(need_uav_pre){
            MSG.str = QStringLiteral("无人机")+QString::number(this->get_mav_id())+": "+str;
        }else{
            MSG.str = str;
        }
        Qt::DMMM()->push_msg(MSG);
    }
}

bool FlyLink::ParamGetValue_ByName(QString name, float &value, bool update)
{
    if(CommonParamMap.contains(name)){
        if(update){
            ParamValueClearFlags_ByName(name);
            return false;
        }
        ParameterState val = CommonParamMap.find(name).value();
        if(val.is_get){
            value = val.value;
            return true;
        }
    }
    else{
        ParameterState param{};
        CommonParamMap[name] = param;
        ParamValueClearFlags_ByName(name);
    }
    return false;
}

bool FlyLink::ParamValueClearFlags_ByName(QString name)
{
    if(CommonParamMap.contains(name)){
        ParameterState val = CommonParamMap.find(name).value();
        val.is_get = false;
        val.req_cnt = 0;
        CommonParamMap[name] = val;
        AllCommonParamGet = false;
        return true;
    }
    return false;
}

bool FlyLink::ParamSetToFlight_ByName(QString name, const float value)
{
    bool res = false;
    res = ParamValueClearFlags_ByName(name);
    if(res){
        set_CommonParameter(name,value);
    }
    return res;
}

bool FlyLink::ParamSetValue_ByName(QString name, const float value)
{
    ParameterState val{};
    val.is_get = true;
    val.value = value;
    CommonParamMap[name] = val;
    return true;
}

void FlyLink::Init_CommonParamMap()
{
    ParameterState state{};
    CommonParamMap["SYSID_THISMAV"] = state;
}


void FlyLink::Update_CommonParamMap()
{
    if(!link_is_active() || AllCommonParamGet){
        return;
    }
    QList<QString> keyList = CommonParamMap.keys();//存放的就是QMap的key值
    for(int i=0;i<keyList.size();i++)
    {
        if(CommonParamMap.contains(keyList.at(i))){
            ParameterState state = CommonParamMap.find(keyList.at(i)).value();
            if(state.req_cnt < 3 || keyList.at(i).contains("SYSID_THISMAV")){
                if(!state.is_get){
                    send_ReqCommonParameter(keyList.at(i));
                    state.req_cnt++;
                    CommonParamMap[keyList.at(i)] = state;
                    return;
                }
            }
            else{
                qDebug()<<keyList.at(i)<<"req failed";
            }
        }
    }

    if(CommonParamMap.contains(keyList.at(keyList.size()-1))){
        ParameterState state = CommonParamMap.find(keyList.at(keyList.size()-1)).value();
        if(state.is_get || state.req_cnt >= 3){
            AllCommonParamGet = true;
            qDebug()<<"AllCommonParamGet"<<true;

        }
    }
}

void FlyLink::InitParamMap()
{
    Init_CommonParamMap();
}

void FlyLink::Update_ParamMap()
{
    if(link_is_active()){
        Update_CommonParamMap();
    }
}

uint8_t FlyLink::getVehicleType() const
{
    return tDataPort.VehicleType;
}

void FlyLink::setVehicleType(uint8_t newVehicleType)
{
    tDataPort.VehicleType = newVehicleType;
}



#endif
