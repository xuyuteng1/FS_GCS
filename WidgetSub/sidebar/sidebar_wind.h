#ifndef SideBarWIND_H
#define SideBarWIND_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include "gaugerange.h"
#include "progressbarpercent.h"

class SideBarWindInfo:public QObject
{
    Q_OBJECT
public:
    SideBarWindInfo();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;

    QLabel* lb_wind_dir = nullptr;
    QLabel* lb_wind_speed = nullptr;
    QLabel* lb_wind_speed_z = nullptr;
    QLabel* lb_icon_wind_dir = nullptr;
    QLabel* lb_icon_wind_speed = nullptr;
    QLabel* lb_icon_wind_speed_z = nullptr;

private:
    void initDesigner();

public :
    void update_val(float wind_dir,float wind_speed,float wind_speed_z);

private slots:
    void handle_DMMM_event(int ev, int linkid);
};

#endif // POWERDESIGNER_H
