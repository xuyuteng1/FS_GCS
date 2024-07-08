#ifndef PM_DESIGNER_H
#define PM_DESIGNER_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include "ledlabel.h"
#include <QSpacerItem>
#include "grouplabel.h"
#include "battery.h"

class SideBarPMInfo
{
public:
    SideBarPMInfo();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;
    Battery* battry = nullptr;
    QLabel* lb_voltage = nullptr;
    QLabel* lb_cureent = nullptr;

private:
    void initPowerDesigner();

public :
    void update_val(bool state,float vol,float cureent,bool bat_usepercent = false,uint8_t per = 0);

};

#endif // POWERDESIGNER_H
