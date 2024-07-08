#include "command_widget.h"

CommandWidget::CommandWidget(QWidget *parent)
    : QWidget(parent)
{
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowTitle(QStringLiteral("指令调试界面"));
    this->setWindowFlags ( Qt::WindowStaysOnTopHint|Qt::Window|Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    QFile file(QString(":/style/commandwidget.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
    widget_init();
    connectSignalAndSlot();
}

GuidedNavWidget *CommandWidget::getGuided_nav() const
{
    return guided_nav;
}


void CommandWidget::connectSignalAndSlot()
{

}

void CommandWidget::widget_init()
{
    if(arm_widget == nullptr){
        arm_widget = new MotorsArmWidget(this);
    }

    if(setmode_widget == nullptr){
        setmode_widget = new SetMode_Widget(this);
    }
    if(takoeff_widget == nullptr){
        takoeff_widget = new TakeoffWidget(this);
    }

    if(set_widget == nullptr){
        set_widget = new SetWidget(this);
    }

    if(sysoption_widget == nullptr){
        sysoption_widget = new SysOptionWidget(this);
    }
    if(guided_nav == nullptr){
        guided_nav = new GuidedNavWidget(this);
    }

    if(mission_widget == nullptr){
        mission_widget = new MissionWidget(this);
    }


    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(setmode_widget,0,0,1,3);
    mainlayout->addWidget(sysoption_widget,0,3,1,1);
    mainlayout->addWidget(arm_widget,1,0,1,2);
    mainlayout->addWidget(takoeff_widget,1,2,1,1);
    mainlayout->addWidget(set_widget,1,3,1,1);
    mainlayout->addWidget(guided_nav,2,0,1,2);
    mainlayout->addWidget(mission_widget,2,3,1,1);


    this->setLayout(mainlayout);
}

/**===================================================================*
 * @brief      电机解锁相关类函数
 **===================================================================*/
MotorsArmWidget::MotorsArmWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("电机解锁"));
    this->setWindowFlags (this->windowFlags()| Qt::WindowStaysOnTopHint);
    widget_init();
    connectSignalAndSlot();
}

void MotorsArmWidget::set_motors(uint8_t mode)
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        switch(mode){
        case FlyLink::ARM_MOTERS:
            link->set_motors_arm();
            break;
        case FlyLink::DISARM_MOTORS:
            link->set_motors_disarm();
            break;
        case FlyLink::ARM_MOTERS_FORCE:
            link->set_motors_force_arm();
            break;

        case FlyLink::DISARM_MOTORS_FORCE:
            link->set_motors_force_disarm();
            break;
        }
    }
}

void MotorsArmWidget::connectSignalAndSlot()
{
    connect(this->pb_arm,&QPushButton::pressed,this,&MotorsArmWidget::set_motors_arm);
    connect(this->pb_force_arm,&QPushButton::pressed,this,&MotorsArmWidget::set_motors_force_arm);
    connect(this->pb_disarm,&QPushButton::pressed,this,&MotorsArmWidget::set_motors_disarm);
    connect(this->pb_force_disarm,&QPushButton::pressed,this,&MotorsArmWidget::set_motors_force_disarm);
}

void MotorsArmWidget::widget_init()
{
    if(pb_arm == nullptr){
        pb_arm = new QPushButton(QStringLiteral("电机解锁"));
        this->pb_arm->setObjectName("arm");
    }
    if(pb_force_arm == nullptr){
        pb_force_arm = new QPushButton(QStringLiteral("强制解锁"));
        this->pb_force_arm->setObjectName("arm");
    }
    if(pb_disarm == nullptr){
        pb_disarm = new QPushButton(QStringLiteral("电机锁定"));
        this->pb_disarm->setObjectName("arm");
    }
    if(pb_force_disarm == nullptr){
        pb_force_disarm = new QPushButton(QStringLiteral("强制锁定"));
        this->pb_force_disarm->setObjectName("arm");
    }

    if(group_arm == nullptr){
        group_arm = new QGroupBox(QStringLiteral("电机开关"));
        this->group_arm->setObjectName("group");
    }

    group_arm->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group_arm);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->addWidget(pb_arm,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget(pb_force_arm,1,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget(pb_disarm,0,1,1,1,Qt::AlignCenter);
    gridLayout->addWidget(pb_force_disarm,1,1,1,1,Qt::AlignCenter);
    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group_arm,0,0,1,1);
    this->setLayout(mainlayout);


}

/**===================================================================*
 * @brief      模式切换类相关变量
 **===================================================================*/
SetMode_Widget::SetMode_Widget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("模式切换"));
    widget_init();
    connectSignalAndSlot();
}

void SetMode_Widget::connectSignalAndSlot()
{
    connect(this->pb_stabilize,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_stabilize);
    connect(this->pb_alt_hold,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_alt_hold);
    connect(this->pb_loiter,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_loiter);
    connect(this->pb_poshold,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_poshold);
//    connect(this->pb_guided,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_guided);
    connect(this->pb_rtl,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_rtl);
    connect(this->pb_smart_rtl,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_smart_rtl);
    connect(this->pb_land,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_land);
//    connect(this->pb_auto,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_auto);
    connect(this->pb_break,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_break);
    connect(this->pb_circle,&QPushButton::pressed,this,&SetMode_Widget::slot_set_mode_circle);
}

void SetMode_Widget::widget_init()
{
    if(pb_stabilize == nullptr){
        pb_stabilize = new QPushButton(QStringLiteral("自稳模式"));
        this->pb_stabilize->setObjectName("setmode");
    }

    if(pb_alt_hold == nullptr){
        pb_alt_hold = new QPushButton(QStringLiteral("定高模式"));
        this->pb_alt_hold->setObjectName("setmode");
    }

    if(pb_loiter == nullptr){
        pb_loiter = new QPushButton(QStringLiteral("悬停模式"));
        this->pb_loiter->setObjectName("setmode");
    }

    if(pb_poshold == nullptr){
        pb_poshold = new QPushButton(QStringLiteral("位置模式"));
        this->pb_poshold->setObjectName("setmode");
    }

//    if(pb_guided == nullptr){
//        pb_guided = new QPushButton(QStringLiteral("引导模式"));
//        this->pb_guided->setObjectName("setmode");
//    }

    if(pb_rtl == nullptr){
        pb_rtl = new QPushButton(QStringLiteral("返航模式"));
        this->pb_rtl->setObjectName("setmode");
    }

    if(pb_smart_rtl == nullptr){
        pb_smart_rtl = new QPushButton(QStringLiteral("智能返航"));
        this->pb_smart_rtl->setObjectName("setmode");
    }

    if(pb_break == nullptr){
        pb_break = new QPushButton(QStringLiteral("刹车模式"));
        this->pb_break->setObjectName("setmode");
    }

//    if(pb_auto == nullptr){
//        pb_auto = new QPushButton(QStringLiteral("任务模式"));
//        this->pb_auto->setObjectName("setmode");
//    }

    if(pb_circle == nullptr){
        pb_circle = new QPushButton(QStringLiteral("绕圈模式"));
        this->pb_circle->setObjectName("setmode");
    }

    if(pb_land == nullptr){
        pb_land = new QPushButton(QStringLiteral("降落模式"));
        this->pb_land->setObjectName("setmode");
    }

    if(group_setmode == nullptr){
        group_setmode = new QGroupBox(QStringLiteral("模式切换"));
        this->group_setmode->setObjectName("group");
    }


    group_setmode->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group_setmode);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    gridLayout->addWidget( pb_stabilize,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_alt_hold,0,1,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_loiter,0,2,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_poshold,1,0,1,1,Qt::AlignCenter);
//    gridLayout->addWidget( pb_guided,1,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_rtl,1,1,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_smart_rtl,1,2,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_land,2,0,1,1,Qt::AlignCenter);
//    gridLayout->addWidget( pb_auto,2,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_break,2,1,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_circle,2,2,1,1,Qt::AlignCenter);

    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group_setmode,0,0,1,1);
    this->setLayout(mainlayout);
}

void SetMode_Widget::set_mode(uint8_t mode_number)
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->set_mode(mode_number);
        }
    }
}

/**===================================================================*
 * @brief      起飞相关函数
 **===================================================================*/
TakeoffWidget::TakeoffWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("起飞指令"));
    widget_init();
    connectSignalAndSlot();
}

void TakeoffWidget::do_takeoff()
{
    float alt = this->val_alt_m->value();
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_takeoff(alt);
    }
}

void TakeoffWidget::connectSignalAndSlot()
{
     connect(this->pb_takeoff,&QPushButton::pressed,this,&TakeoffWidget::do_takeoff);
}

void TakeoffWidget::widget_init()
{
    if(pb_takeoff == nullptr){
        pb_takeoff = new QPushButton(QStringLiteral("一键起飞"));
        this->pb_takeoff->setObjectName("takeoff");
    }

    if(val_alt_m == nullptr){
        val_alt_m = new QDoubleSpinBox();
        this->val_alt_m->setObjectName(QString::fromUtf8("val_alt_m"));
        val_alt_m->setAlignment(Qt::AlignCenter);
        val_alt_m->setDecimals(1);
        val_alt_m->setMinimum(1.000000000000000);
        val_alt_m->setMaximum(120.000000000000000);
        val_alt_m->setValue(10.000000000000000);
    }

    if(group == nullptr){
        group = new QGroupBox(QStringLiteral("起飞指令"));
        this->group->setObjectName("group");
    }

    group->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    gridLayout->addWidget( val_alt_m,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_takeoff,1,0,1,1,Qt::AlignCenter);

    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group,0,0,1,1);
    this->setLayout(mainlayout);
}

/**===================================================================*
 * @brief      高度设置相关类
 **===================================================================*/
SetWidget::SetWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("设置界面"));
    widget_init();
    connectSignalAndSlot();
}

void SetWidget::do_setAlt()
{
    float alt = this->val_alt_m->value();
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_set_alt_m(alt);
    }
}

void SetWidget::do_setHeading()
{
    float heading = this->val_heading->value();
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_set_heading(heading);
    }
}

void SetWidget::connectSignalAndSlot()
{
    connect(this->pb_setAlt,&QPushButton::pressed,this,&SetWidget::do_setAlt);
    connect(this->pb_setheading,&QPushButton::pressed,this,&SetWidget::do_setHeading);
}

void SetWidget::widget_init()
{
    if(pb_setAlt == nullptr){
        pb_setAlt = new QPushButton(QStringLiteral("设置高度"));
        this->pb_setAlt->setObjectName("set");
    }

    if(pb_setheading == nullptr){
        pb_setheading = new QPushButton(QStringLiteral("设置航向"));
        this->pb_setheading->setObjectName("set");
    }

    if(val_alt_m == nullptr){
        val_alt_m = new QDoubleSpinBox();
        this->val_alt_m->setObjectName(QString::fromUtf8("val_alt_m"));
        val_alt_m->setAlignment(Qt::AlignCenter);
        val_alt_m->setDecimals(1);
        val_alt_m->setMinimum(-100.000000000000000);
        val_alt_m->setMaximum(5000.000000000000000);
        val_alt_m->setValue(10.000000000000000);
    }

    if(val_heading == nullptr){
        val_heading = new QDoubleSpinBox();
        this->val_heading->setObjectName(QString::fromUtf8("val_heading"));
        val_heading->setAlignment(Qt::AlignCenter);
        val_heading->setDecimals(1);
        val_heading->setMinimum(0);
        val_heading->setMaximum(360);
        val_heading->setValue(0);
    }

    if(group == nullptr){
        group = new QGroupBox(QStringLiteral("临时设置"));
        this->group->setObjectName("group");
    }

    group->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    gridLayout->addWidget( val_alt_m,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_setAlt,1,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( val_heading,0,1,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_setheading,1,1,1,1,Qt::AlignCenter);

    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group,0,0,1,1);
    this->setLayout(mainlayout);
}

SysOptionWidget::SysOptionWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("飞控配置"));
    widget_init();
    connectSignalAndSlot();
}

void SysOptionWidget::do_factory()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_factory();
    }
}

void SysOptionWidget::do_reboot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_reboot();
    }
}

void SysOptionWidget::connectSignalAndSlot()
{
    connect(this->pb_setfactory,&QPushButton::pressed,this,&SysOptionWidget::do_factory);
    connect(this->pb_setreboot,&QPushButton::pressed,this,&SysOptionWidget::do_reboot);
}

void SysOptionWidget::widget_init()
{
    if(pb_setfactory == nullptr){
        pb_setfactory = new QPushButton(QStringLiteral("恢复出厂"));
        this->pb_setfactory->setObjectName("sysoption");
    }

    if(pb_setreboot == nullptr){
        pb_setreboot = new QPushButton(QStringLiteral("飞控重启"));
        this->pb_setreboot->setObjectName("sysoption");
    }



    if(group == nullptr){
        group = new QGroupBox(QStringLiteral("系统配置"));
        this->group->setObjectName("group");
    }

    group->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    gridLayout->addWidget( pb_setfactory,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_setreboot,1,0,1,1,Qt::AlignCenter);

    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group,0,0,1,1);
    this->setLayout(mainlayout);
}

GuidedNavWidget::GuidedNavWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("航点指令"));
    widget_init();
    connectSignalAndSlot();
}

void GuidedNavWidget::set_guided_nav()
{
    FlyLink::guided_nav_wp_t WP{};
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        WP.latitude = this->val_lat->value()*1e7;
        WP.longitude = this->val_lng->value()*1e7;
        WP.alt_m = this->val_alt_m->value();
        WP.alt_frame = this->cb_alt_frame->currentIndex();
        link->set_guided_nav_wp(WP);
    }
}

void GuidedNavWidget::get_cureent_loc()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        this->val_lat->setValue(Qt::DMMM()->getData_main().flylink.tVehicle.lat*1e-7);
        this->val_lng->setValue(Qt::DMMM()->getData_main().flylink.tVehicle.lng*1e-7);
        this->val_alt_m->setValue(Qt::DMMM()->getData_main().flylink.tVehicle.pos_m[2]);
        this->cb_alt_frame->setCurrentIndex(FlyLink::MISSION_ALT_FRAME_RELATIVE_ALT);
    }
}

void GuidedNavWidget::request_from_gis()
{
    emit GuidedNavWidget::req_gis_loc();
}

void GuidedNavWidget::get_gis_loc(const double &lat, const double &lng)
{
    this->val_lat->setValue(lat);
    this->val_lng->setValue(lng);

    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        float alt_val = Qt::DMMM()->getData_main().flylink.tVehicle.pos_m[2];
        alt_val = (alt_val<10.0)?10:alt_val;
        this->val_alt_m->setValue(alt_val);
        this->cb_alt_frame->setCurrentIndex(FlyLink::MISSION_ALT_FRAME_RELATIVE_ALT);
    }
}

void GuidedNavWidget::connectSignalAndSlot()
{
    connect(this->pb_set_wp,&QPushButton::pressed,this,&GuidedNavWidget::set_guided_nav);
    connect(this->pb_get_current_loc,&QPushButton::pressed,this,&GuidedNavWidget::get_cureent_loc);
    connect(this->pb_get_fromgis,&QPushButton::pressed,this,&GuidedNavWidget::request_from_gis);
}

void GuidedNavWidget::widget_init()
{

    if(pb_set_wp == nullptr){
        pb_set_wp = new QPushButton(QStringLiteral("航点飞行"));
        this->pb_set_wp->setObjectName("guided");
    }

    if(pb_get_current_loc == nullptr){
        pb_get_current_loc = new QPushButton(QStringLiteral("获取当前位置"));
        this->pb_get_current_loc->setObjectName("guided");
    }

    if(pb_get_fromgis == nullptr){
        pb_get_fromgis = new QPushButton(QStringLiteral("地图点选位置"));
        this->pb_get_fromgis->setObjectName("guided");
    }

    if(lb_lat == nullptr){
        lb_lat = new QLabel(QStringLiteral("纬度"));
        this->lb_lat->setObjectName("guided");
    }

    if(lb_lng == nullptr){
        lb_lng = new QLabel(QStringLiteral("经度"));
        this->lb_lng->setObjectName("guided");
    }

    if(val_alt_m == nullptr){
        val_alt_m = new QDoubleSpinBox();
        this->val_alt_m->setObjectName(QString::fromUtf8("guided"));
        val_alt_m->setAlignment(Qt::AlignCenter);
        val_alt_m->setDecimals(1);
        val_alt_m->setMinimum(-200);
        val_alt_m->setMaximum(6000);
        val_alt_m->setValue(50);
    }

    if(val_lat == nullptr){
        val_lat = new QDoubleSpinBox();
        this->val_lat->setObjectName(QString::fromUtf8("guided"));
        val_lat->setAlignment(Qt::AlignCenter);
        val_lat->setDecimals(7);
        val_lat->setMinimum(-90);
        val_lat->setMaximum(90.0000000);
        val_lat->setValue(34);
    }

    if(val_lng == nullptr){
        val_lng = new QDoubleSpinBox();
        this->val_lng->setObjectName(QString::fromUtf8("guided"));
        val_lng->setAlignment(Qt::AlignCenter);
        val_lng->setDecimals(7);
        val_lng->setMinimum(-180);
        val_lng->setMaximum(180);
        val_lng->setValue(108);
    }

    if(cb_alt_frame == nullptr){
        // 高度类型
        cb_alt_frame = new QComboBox();
        cb_alt_frame->addItem(QString());
        cb_alt_frame->addItem(QString());
        cb_alt_frame->addItem(QString());
        cb_alt_frame->setObjectName(QString::fromUtf8("nav_wp_alt_frame"));
        cb_alt_frame->setItemText(0,QStringLiteral("相对高度"));
        cb_alt_frame->setItemText(1,QStringLiteral("海拔高度"));
        cb_alt_frame->setItemText(2,QStringLiteral("地形高度"));
    }


    if(group == nullptr){
        group = new QGroupBox(QStringLiteral("航点配置"));
        this->group->setObjectName("group");
    }

    group->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));



    gridLayout->addWidget( pb_get_current_loc,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_get_fromgis,0,1,1,1,Qt::AlignCenter);

    gridLayout->addWidget( lb_lat,1,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( val_lat,1,1,1,1,Qt::AlignCenter);

    gridLayout->addWidget( lb_lng,2,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( val_lng,2,1,1,1,Qt::AlignCenter);

    gridLayout->addWidget( cb_alt_frame,3,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( val_alt_m,3,1,1,1,Qt::AlignCenter);


    gridLayout->addWidget( pb_set_wp,4,0,1,2,Qt::AlignCenter);

    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group,0,0,1,1);
    this->setLayout(mainlayout);

}


MissionWidget::MissionWidget(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowTitle(QStringLiteral("任务指令"));
    widget_init();
    connectSignalAndSlot();
}

void MissionWidget::connectSignalAndSlot()
{

    connect(pb_start_mission,&QPushButton::pressed,this,&MissionWidget::do_start_mission);
    connect(pb_restart_mission,&QPushButton::pressed,this,&MissionWidget::do_restart_mission);
    connect(pb_change_mission_item,&QPushButton::pressed,this,&MissionWidget::do_change_mission_item);
}

void MissionWidget::widget_init()
{
    if(pb_start_mission == nullptr){
        pb_start_mission = new QPushButton(QStringLiteral("开始任务"));
        this->pb_start_mission->setObjectName("mission");
    }

    if(pb_restart_mission == nullptr){
        pb_restart_mission = new QPushButton(QStringLiteral("重新开始"));
        this->pb_restart_mission->setObjectName("mission");
    }

    if(pb_change_mission_item == nullptr){
        pb_change_mission_item = new QPushButton(QStringLiteral("切换航点"));
        this->pb_change_mission_item->setObjectName("mission");
    }


    if(item_id == nullptr){
        item_id = new QSpinBox();
        this->item_id->setObjectName(QString::fromUtf8("mission"));
        item_id->setAlignment(Qt::AlignCenter);
        item_id->setMinimum(0);
        item_id->setMaximum(2000);
    }



    if(group == nullptr){
        group = new QGroupBox(QStringLiteral("任务指令"));
        this->group->setObjectName("group");
    }

    group->setAlignment(Qt::AlignCenter);
    gridLayout = new QGridLayout(group);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    gridLayout->addWidget( item_id,0,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_change_mission_item,0,1,1,1,Qt::AlignCenter);

    gridLayout->addWidget( pb_start_mission,1,0,1,1,Qt::AlignCenter);
    gridLayout->addWidget( pb_restart_mission,1,1,1,1,Qt::AlignCenter);

    mainlayout = new QGridLayout(this);
    mainlayout->addWidget(group,0,0,1,1);
    this->setLayout(mainlayout);
}

void MissionWidget::do_start_mission()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_startMission(false);
        }
    }
}

void MissionWidget::do_restart_mission()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_ChangeMissionItem(0);
        }
    }
}

void MissionWidget::do_change_mission_item()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        if(link->getIs_active()){
            link->do_ChangeMissionItem(item_id->value());
        }
    }
}
