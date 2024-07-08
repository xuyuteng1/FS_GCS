#ifndef P_P_CMD_Waypoint_H__
#define P_P_CMD_Waypoint_H__

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QTimer>
#include <QMessageBox>

#include <QtLocation>

class P_CMD_Waypoint :  public QWidget{
    Q_OBJECT
public:
    P_CMD_Waypoint();

private:
    QLabel          *lb_lat         = nullptr;
    QLabel          *lb_lng         = nullptr;
    QLabel          *lb_alt         = nullptr;
    QLabel          *lb_radius      = nullptr;

    QDoubleSpinBox  *dSpinBox_lat   = nullptr;
    QDoubleSpinBox  *dSpinBox_lng   = nullptr;
    QDoubleSpinBox  *dSpinBox_alt   = nullptr;
    QDoubleSpinBox  *dSpinBox_radius= nullptr;
    QCheckBox       *cb_radius_dir  = nullptr;

    QPushButton     *btn_GetPosFromGIS = nullptr;
    QPushButton     *btn_GetPosFromCurrent = nullptr;
    QPushButton     *btn_SetModeRTL = nullptr;
    QGridLayout     *widgetLayout   = nullptr;
private:
    void widgetInit();
    void connectSignalAndSlot();
private slots:

    void handle_GetPosFromGIS();
    void handle_GetPosFromCurrent();
    VOID handle_SetModeRTL();
    void update_model();
    void RTLModelChange();
public:
signals:
};


#endif
