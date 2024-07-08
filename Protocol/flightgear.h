/**=================================================================**
 * @brief       : 通信协议部分
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2022-01-16     Jerry.xl     the first version
 **==================================================================**/
#ifndef FLIGHT_GEAR_H____
#define FLIGHT_GEAR_H____


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
/*====================== 类定义 ====================*/
#define FlightGearLinkID        (0xFE)

class FGNetFDM {
public:

    enum {
        FG_MAX_ENGINES = 4,
        FG_MAX_WHEELS = 3,
        FG_MAX_TANKS = 4
    };

    uint32_t version;		// increment when data values change
    uint32_t padding;		// padding

    // Positions
    double longitude;		// geodetic (radians)
    double latitude;		// geodetic (radians)
    double altitude;		// above sea level (meters)
    float agl;			    // above ground level (meters)
    float phi;			    // roll (radians)
    float theta;		    // pitch (radians)
    float psi;			    // yaw or true heading (radians)
    float alpha;        // angle of attack (radians)
    float beta;         // side slip angle (radians)

    // Velocities
    float phidot;		     // roll rate (radians/sec)
    float thetadot;		   // pitch rate (radians/sec)
    float psidot;		     // yaw rate (radians/sec)
    float vcas;          // calibrated airspeed
    float climb_rate;		 // feet per second
    float v_north;       // north velocity in local/body frame, fps
    float v_east;        // east velocity in local/body frame, fps
    float v_down;        // down/vertical velocity in local/body frame, fps
    float v_body_u;      // ECEF velocity in body axis
    float v_body_v;      // ECEF velocity in body axis
    float v_body_w;      // ECEF velocity in body axis

    // Accelerations
    float A_X_pilot;		// X accel in body frame ft/sec^2
    float A_Y_pilot;		// Y accel in body frame ft/sec^2
    float A_Z_pilot;		// Z accel in body frame ft/sec^2

    // Stall
    float stall_warning;  // 0.0 - 1.0 indicating the amount of stall
    float slip_deg;		    // slip ball deflection

    // Pressure

    // Engine status
    uint32_t num_engines;               // Number of valid engines
    uint32_t eng_state[FG_MAX_ENGINES]; // Engine state (off, cranking, running)
    float rpm[FG_MAX_ENGINES];          // Engine RPM rev/min
    float fuel_flow[FG_MAX_ENGINES];    // Fuel flow gallons/hr
    float fuel_px[FG_MAX_ENGINES];      // Fuel pressure psi
    float egt[FG_MAX_ENGINES];          // Exhuast gas temp deg F
    float cht[FG_MAX_ENGINES];          // Cylinder head temp deg F
    float mp_osi[FG_MAX_ENGINES];       // Manifold pressure
    float tit[FG_MAX_ENGINES];          // Turbine Inlet Temperature
    float oil_temp[FG_MAX_ENGINES];     // Oil temp deg F
    float oil_px[FG_MAX_ENGINES];       // Oil pressure psi

    // Consumables
    uint32_t num_tanks;		              // Max number of fuel tanks
    float fuel_quantity[FG_MAX_TANKS];

    // Gear status
    uint32_t num_wheels;
    uint32_t wow[FG_MAX_WHEELS];
    float gear_pos[FG_MAX_WHEELS];
    float gear_steer[FG_MAX_WHEELS];
    float gear_compression[FG_MAX_WHEELS];

    // Environment
    uint32_t cur_time;           // current simulation time of JSBSim
    int32_t warp;                // offset in seconds to unix time
    float visibility;            // visibility in meters (for env. effects)

    // Control surface positions (normalized values)
    float elevator;
    float elevator_trim_tab;
    float left_flap;
    float right_flap;
    float left_aileron;
    float right_aileron;
    float rudder;
    float nose_wheel;
    float speedbrake;
    float spoilers;

    // nasty hack .... JSBSim sends in little-endian
    void ByteSwap(void);
};
class FlightGear_Link : public DeviceCommunication
{
    Q_OBJECT
public:
    /*--------------构造/析构函数--------------*/
    FlightGear_Link(QObject *parent=nullptr,bool IndependentThread = false);
    virtual ~FlightGear_Link();
    void Open();
    void Close();

    void _output_to_flightgear();
public slots:
private slots:
    void handle_DMMM_event(int ev, int linkid);
private:
};

#endif // FlightGear_Link_H
