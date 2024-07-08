#ifndef SIDEBAR_RPM_INFO_H
#define SIDEBAR_RPM_INFO_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>

class SideBarRPMInfo
{
public:
    SideBarRPMInfo();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;
    QLabel* lb[2] = {};
    QLabel* lb_val[2] = {};

private:
    void init();

public :
    void update_val(float val1,float val2);

};

#endif // POWERDESIGNER_H
