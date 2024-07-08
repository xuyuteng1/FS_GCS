#ifndef SideBarFlightInfo_H
#define SideBarFlightInfo_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include "gaugerange.h"
#include "progressbarpercent.h"

class SideBarFlightInfo
{
public:
    SideBarFlightInfo();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;
    QHBoxLayout *disLayout = nullptr;
    QHBoxLayout *timeLayout = nullptr;
    GaugeRange* throttle = nullptr;

    QLabel* lb_temperature = nullptr;
    QLabel* lb_state = nullptr;

    QLabel* lb_flytime = nullptr;
    QLabel* lb_flydis = nullptr;
    QLabel* lb_flytime_icon = nullptr;
    QLabel* lb_flydis_icon = nullptr;

private:
    void initDesigner();

public :
    void update_val(int thr,float temp,qint64 flytime,qint64 flydis,bool arm ,bool fly);

};

#endif // POWERDESIGNER_H
