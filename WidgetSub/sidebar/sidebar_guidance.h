#ifndef SideBarGuidance_H
#define SideBarGuidance_H

#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include "lightbutton.h"
class SideBarGuidance
{
public:
    SideBarGuidance();
    QGridLayout *getWidgetLayout() const;
private:
    QGridLayout *widgetLayout = nullptr;
    LightButton* LED_GuidanceDevice = nullptr;
    QLabel* lb_State = nullptr;
    QLabel* lb_PitchErr = nullptr;
    QLabel* lb_YawErr = nullptr;
    QLabel* lb_TrackingResponsivity = nullptr;

private:
    void initDesigner();

public :
    void update_val(bool is_health,float pitch,float yaw, float TrackRes,QString state);

};

#endif // POWERDESIGNER_H
