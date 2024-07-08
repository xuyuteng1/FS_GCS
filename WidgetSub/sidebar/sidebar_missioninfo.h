#ifndef SideBarMissionInfo_h
#define SideBarMissionInfo_h

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include "gaugerange.h"

class SideBarMissionInfo
{
public:
    SideBarMissionInfo();
    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout *widgetLayout = nullptr;
    QVBoxLayout *vBoxHome = nullptr;
    QVBoxLayout *vBoxTarget = nullptr;
    QVBoxLayout *vBoxXtarckErr = nullptr;

    QLabel* lb_home_dis = nullptr;
    QLabel* lb_target_dis = nullptr;
    QLabel* lb_xtrack_err = nullptr;
    QLabel* lb_home_dis_icon = nullptr;
    QLabel* lb_target_dis_icon = nullptr;
    QLabel* lb_xtrack_err_icon= nullptr;

private:
    void initDesigner();

public :
    void update_val(float home_dis,float target_dis ,float xtackErr);

};

#endif // POWERDESIGNER_H
