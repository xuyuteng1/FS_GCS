#ifndef WaypointWidget_H____
#define WaypointWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QMessageBox>

#include <QtLocation>

class C_WaypointWidget :  public QWidget{
    Q_OBJECT
public:
    C_WaypointWidget();

private:
    QPushButton *getLocalPositionButton = nullptr;          //获取当前位置
    QPushButton *getMousePressedPositionButton = nullptr;   //获取鼠标点选位置坐标

    QPushButton *flyToWayPointButton = nullptr;
    QPushButton *setAltitudeButton = nullptr;
    QPushButton *setHeadingButton = nullptr;

    QLabel      *lngLabel = nullptr;
    QLabel      *latLabel = nullptr;
    QLabel      *altLabel = nullptr;
    QLabel      *headingLabel = nullptr;

    QDoubleSpinBox    *lngSpinBox = nullptr;
    QDoubleSpinBox    *latSpinBox = nullptr;
    QDoubleSpinBox    *altitudeSpinBox = nullptr;
    QDoubleSpinBox    *HeadingSpinBox = nullptr;
    QGridLayout       *widgetLayout = nullptr;
private:
    void widgetInit();
    void connectSignalAndSlot();
private slots:
    void flayToButtonPressedSlot();

    void getLocalPositionButtonPressedSlot();
    void getMousePressedPositionButtonPressedSlot();

    void flyToWayPointButtonPressedSlot();
    void posModelChange();

    void posValueEdit();
    void handle_setAltitude();
    void handle_setHeading();

public:
signals:

    void clearWapPointSignal();
    void req_gis_loc_Signal();
    void event_edit_guidedPointModel(QGeoCoordinate coor);

};


#endif
