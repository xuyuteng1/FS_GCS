#ifndef SIDEBAR_EXT_VOL_H
#define SIDEBAR_EXT_VOL_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>

class SideBarMonitor
{
public:
    SideBarMonitor();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;
    QLabel* lb_voltage[2] = {};
    QLabel* lb_voltage_val[2] = {};
    QLabel* lb[2] = {};
    QLabel* lb_val[2] = {};
private:
    void init();

public :
    void update_val(float val1, float val2,float rpm1,float rpm2);

};

#endif // POWERDESIGNER_H
