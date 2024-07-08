#include "systeminfowidget.h"
#include "DMMM.h"
#include "qmath.h"
#include <QSettings>
SystemInfoWidget::SystemInfoWidget(QWidget *parent)
    : QListWidget(parent)
{

    widgetInit();
    connectSignalAndSlot();
    setIsShow(true);

}

QPushButton *SystemInfoWidget::getMiniButton() const
{
    return miniButton;
}

bool SystemInfoWidget::getIsShow() const
{
    return isShow;
}

void SystemInfoWidget::setIsShow(bool newIsShow)
{
    isShow = newIsShow;
}

void SystemInfoWidget::widgetInit()
{
    // 读取配置文件
    QSettings setting("./cfg/Setting.ini", QSettings::IniFormat);
    bool item_visable = false;

    if(this->menu == nullptr){
        this->menu = new QMenu(this);
        this->menu->setObjectName("SystemInfoWidgetMenu");
    }

    if(this->miniButton == nullptr){
        this->miniButton = new QPushButton(">>");
    }

    if(SysStatus == nullptr){
        SysStatus = new SideBarSysStatus(this);
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("状态信息")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("状态信息")).toBool();
        }
        this->addNewWidgetForListWidget(QStringLiteral("状态信息"),this->SysStatus->getWidgetLayout(),item_visable);
    }
    if(statewidget == nullptr){
        statewidget = new SideBarSensorInfo(this);
//        this->addNewWidgetForListWidget(QStringLiteral("状态信息1"),this->statewidget->getWidgetLayout(),false);
    }
    if(pm_designer == nullptr){
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("电源管理")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("电源管理")).toBool();
        }
        pm_designer = new SideBarPMInfo();
        this->addNewWidgetForListWidget(QStringLiteral("电源管理"),this->pm_designer->getWidgetLayout(),item_visable);
    }
    if(flight_designer == nullptr){
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("飞行信息")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("飞行信息")).toBool();
        }
        flight_designer = new SideBarFlightInfo();
        this->addNewWidgetForListWidget(QStringLiteral("飞行信息"),this->flight_designer->getWidgetLayout(),item_visable);
    }


    if(MoveInfo == nullptr){
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("运动信息")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("运动信息")).toBool();
        }
        MoveInfo = new SideBarMoveInfo();
        this->addNewWidgetForListWidget(QStringLiteral("运动信息"),this->MoveInfo->getWidgetLayout(),item_visable);
    }

    if(AutoInfo == nullptr){
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("距离信息")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("距离信息")).toBool();
        }
        AutoInfo = new SideBarMissionInfo();
        this->addNewWidgetForListWidget(QStringLiteral("距离信息"),this->AutoInfo->getWidgetLayout(),item_visable);
    }
    if(WindInfo == nullptr){
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("风速信息")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("风速信息")).toBool();
        }
        WindInfo = new SideBarWindInfo();
        this->addNewWidgetForListWidget(QStringLiteral("风速信息"),this->WindInfo->getWidgetLayout(),item_visable);
    }
    if(ExtMonitor == nullptr){
        item_visable  = true;
        if(!setting.value("SideBar/"+QStringLiteral("外部监测")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("外部监测")).toBool();
        }
        ExtMonitor = new SideBarMonitor();
        this->addNewWidgetForListWidget(QStringLiteral("外部监测"),this->ExtMonitor->getWidgetLayout(),item_visable);
    }
    if(Guidance == nullptr){
        item_visable  = false;
        if(!setting.value("SideBar/"+QStringLiteral("导引信息")).isNull()){
            item_visable = setting.value("SideBar/"+QStringLiteral("导引信息")).toBool();
        }
        Guidance = new SideBarGuidance();
        this->addNewWidgetForListWidget(QStringLiteral("导引信息"),this->Guidance->getWidgetLayout(),item_visable);
    }

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setObjectName("SystemInfoWidget");
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

void SystemInfoWidget::connectSignalAndSlot()
{
    connect(this,&QListWidget::customContextMenuRequested,this,&SystemInfoWidget::mouseRightButtonPressedSlot);
    connect(this->menu,&QMenu::triggered,this,&SystemInfoWidget::menuActionTargetSlot);
    connect(this->miniButton,&QPushButton::clicked,this,&SystemInfoWidget::miniButtonPressedSlot);
}

void SystemInfoWidget::addGroupBoxToListWidget(QListWidgetItem *item, QGroupBox *box)
{
    if(item == nullptr || box ==nullptr){
        return;
    }

//    item->setSizeHint(box->sizePolicy());
    item->setSizeHint(box->minimumSizeHint());
    this->addItem(item);
    this->setItemWidget(item,box);
//    this->setFixedHeight(this->height()+box->height());
}


void SystemInfoWidget::update_pm_widget()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link == nullptr){
        return;
    }


    FlyLink::DataPort_t data = link->getTDataPort();
    FlyLink::VehicleParam_t param = link->getTVehicleParam();

    if(!param.UpdateFlags.failsafe){
        this->pm_designer->update_val(data.tSysInfo.sensor_state.state.power,
                                      data.tSysInfo.Battery_voltage_mv*0.001f,
                                      data.tSysInfo.Battery_Current_CA*0.01f
                                      );
    }
    else{

        // 1级保护要作为20%的电池
        float percent = 0.0f;
        bool use_percent = false;
        if( param.failsafe._batt_voltage_max > 0 &&
            param.failsafe._batt_voltage_min > 0 &&
            param.failsafe._batt_voltage_max > param.failsafe._batt_voltage_min&&
            param.failsafe.battery_level1_voltage < param.failsafe._batt_voltage_max &&
            param.failsafe.battery_level1_voltage > param.failsafe._batt_voltage_min    ){

            float cur_vol = data.tSysInfo.Battery_voltage_mv/100.0f;

            // 0~25%
            if( cur_vol <  param.failsafe.battery_level1_voltage){
                percent  = (float)(cur_vol - param.failsafe._batt_voltage_min)/(param.failsafe.battery_level1_voltage - param.failsafe._batt_voltage_min);
                percent = percent<0?0:percent;
                percent *=0.25;
            }
            else{
                percent  = (float)(cur_vol - param.failsafe.battery_level1_voltage)/(param.failsafe._batt_voltage_max - param.failsafe.battery_level1_voltage);
                percent *= 0.75;
                percent += 0.25;
            }
            use_percent = true;
        }

        this->pm_designer->update_val(data.tSysInfo.sensor_state.state.power,
                                      data.tSysInfo.Battery_voltage_mv*0.001f,
                                      data.tSysInfo.Battery_Current_CA*0.01f,
                                      use_percent,
                                      percent*100
                                      );
    }

}

void SystemInfoWidget::update_flight_widget()
{
    Q_DMMM* flight = Qt::DMMM();
    if(flight == nullptr){
        return;
    }

    Q_DMMM::DataPool_t data = flight->getData_main();
//    int thr, float temp, qint64 flytime, qint64 flydis, bool arm, bool fly
    this->flight_designer->update_val(data.flylink.tSysInfo.throttle,
                                      data.flylink.tSysInfo.temperture*0.01f,
                                      data.flylink.tSysInfo.flight_time_s,
                                      data.flylink.tSysInfo.flight_dis_m,
                                      data.flylink.tSysInfo.state1.state.armed,
                                      data.flylink.tSysInfo.state1.state.isflying
                                      );
}

void SystemInfoWidget::update_autoinfo_widget()
{
    Q_DMMM* flight = Qt::DMMM();
    if(flight == nullptr){
        return;
    }

    Q_DMMM::DataPool_t data = flight->getData_main();
//    int thr, float temp, qint64 flytime, qint64 flydis, bool arm, bool fly
    this->AutoInfo->update_val(data.flylink.tSysInfo.home_dist_m,
                               data.flylink.tSysInfo.wp_dist_m,
                               data.flylink.tSysInfo.xtrack_error);
}

void SystemInfoWidget::update_ExtMonitor_widget()
{
    Q_DMMM* flight = Qt::DMMM();
    if(flight == nullptr){
        return;
    }

    Q_DMMM::DataPool_t data = flight->getData_main();

    this->ExtMonitor->update_val(data.flylink.extVol.val[0],data.flylink.extVol.val[1],data.flylink.RPM.val[0],data.flylink.RPM.val[1]);
}

void SystemInfoWidget::update_MoveInfo_widget()
{
    Q_DMMM* flight = Qt::DMMM();
    if(flight == nullptr){
        return;
    }

    Q_DMMM::DataPool_t data = flight->getData_main();
    float horVe = qSqrt(data.flylink.tVehicle.vel_cmps[0]*data.flylink.tVehicle.vel_cmps[0]+data.flylink.tVehicle.vel_cmps[1]*data.flylink.tVehicle.vel_cmps[1]);
    this->MoveInfo->update_val(horVe*0.01f,data.flylink.tVehicle.vel_cmps[2]*0.01f,data.flylink.tVehicle.pos_m[2],data.flylink.tVehicle.airSpeed);
}

void SystemInfoWidget::update_Guidance_widget()
{
    Q_DMMM* flight = Qt::DMMM();
    if(flight == nullptr){
        return;
    }

    Q_DMMM::DataPool_t data = flight->getData_main();
    QString str;
    if(data.flylink.GuidanceInfo.WorkState & 0b1){
        str += QStringLiteral("跟踪有效 - ");
    }else{
        str += QStringLiteral("目标丢失 - ");
    }

    if(data.flylink.GuidanceInfo.WorkState & 0b10){
        str += QStringLiteral("攻击 - ");
    }else{
        str += QStringLiteral("搜索 - ");
    }

    if(data.flylink.GuidanceInfo.WorkState & 0b10000){
        str += QStringLiteral("盲区 - ");
    }else{
        str += QStringLiteral("非盲区 - ");
    }

    data.flylink.GuidanceInfo.WorkState >>=2;
    switch(data.flylink.GuidanceInfo.WorkState&0b11){
        case 0b00:str += QStringLiteral("可见光");break;
        case 0b01:str += QStringLiteral("可见光");break;
        case 0b10:str += QStringLiteral("红外白热");break;
        case 0b11:str += QStringLiteral("红外黑热");break;
    }

    if(!data.flylink.tSysInfo.sensor_state.state.GuidanceDevice){
        str = QStringLiteral("设备通信异常");
    }
    this->Guidance->update_val(data.flylink.tSysInfo.sensor_state.state.GuidanceDevice,\
                               data.flylink.GuidanceInfo.PitchErr,\
                               data.flylink.GuidanceInfo.YawErr,\
                               data.flylink.GuidanceInfo.TrackingResponsivity,\
                               str);
}


bool SystemInfoWidget::addNewWidgetForListWidget(QString widgetName, QGridLayout *widgetLayout, bool isShow)
{
    if(this->widgetNameMap.find(widgetName) != this->widgetNameMap.end()){
        return false;
    }
    if(widgetLayout == nullptr){
        return false;
    }

    QGroupBox *box = new QGroupBox();
    box->setObjectName("SystemInfoWidgetGroupBox");

    box->setLayout(widgetLayout);
    QListWidgetItem *item = new QListWidgetItem(widgetName);

    this->widgetMap.insert(item,box);
    this->widgetNameMap.insert(widgetName,item);

    QAction *action = new QAction(widgetName);
    if(this->menu != nullptr){
        action->setCheckable(true);
        action->setChecked(isShow);
        this->menu->addAction(action);
        this->actionMap.insert(action,item);
    }

    this->addGroupBoxToListWidget(item,box);

    if(!isShow){
        menuActionTargetSlot(action);
    }
    return true;
}

void SystemInfoWidget::mouseRightButtonPressedSlot(const QPoint &point)
{
    Q_UNUSED(point);
    this->menu->exec(QCursor::pos());
}

void SystemInfoWidget::menuActionTargetSlot(QAction *action)
{
    if(action == nullptr || this->actionMap.find(action) == this->actionMap.end()){
        return;
    }

    QListWidgetItem *item = this->actionMap.find(action).value();

    if( this->widgetMap.find(item) == this->widgetMap.end() || item == nullptr ){
        return;
    }

    // 计算当前有几个处于显示状态
    QMap<QListWidgetItem *,QGroupBox *>::iterator iter = this->widgetMap.begin();
    uint8_t checked_cnt = 0;
    while(iter != this->widgetMap.end()){
        if(!iter.key()->isHidden()){
            checked_cnt++;
        }
        iter ++;
    }

    // 如果仅剩一个，则不允许再隐藏
    if(checked_cnt < 2 && !action->isChecked()){
        action->setChecked(true);
        return;
    }

    bool isChecked = action->isChecked();
    QGroupBox* box = this->widgetMap.find(item).value();
    QSettings setting("./cfg/Setting.ini", QSettings::IniFormat);
    setting.setValue("SideBar/"+item->text(),isChecked);
    if(isChecked ){
        item->setHidden(false);
    }else{
        item->setHidden(true);
    }

}

void SystemInfoWidget::miniButtonPressedSlot()
{
    if(this->isVisible()){
        this->setVisible(false);
        this->miniButton->setText("<<");
    }else{
        this->setVisible(true);
        this->miniButton->setText(">>");
    }
}

void SystemInfoWidget::update_sysinfo()
{
    if(!this->isVisible())return;
    update_pm_widget();
    update_flight_widget();
    update_autoinfo_widget();
    update_ExtMonitor_widget();
    update_MoveInfo_widget();
    update_Guidance_widget();
}

