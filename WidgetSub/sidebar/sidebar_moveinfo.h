#ifndef SIDEBAR_RPM_INFO_H
#define SIDEBAR_RPM_INFO_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include "gaugerange.h"
#include "gaugearc.h"
class SideBarMoveInfo
{
public:
    SideBarMoveInfo();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;
    QLabel* lb[3] = {};
    QLabel* lb_val[3] = {};
    GaugeRange* speed = nullptr;

private:
    void init();

public :
    void update_val(float val1, float val2 ,float val3 ,float val4);

};

#endif // POWERDESIGNER_H
