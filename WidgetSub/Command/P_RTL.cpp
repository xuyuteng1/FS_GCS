#include "P_RTL.h"
#include "DMMM.h"
#include "gis_mapview.h"
P_CMD_RTL::P_CMD_RTL()
{
    widgetInit();
    connectSignalAndSlot();
}

void P_CMD_RTL::widgetInit()
{
    if( this->lb_lat == nullptr){
        this->lb_lat = new QLabel(QStringLiteral("纬度"));
        this->lb_lat->setObjectName("WidgetCMD");
    }
    if( this->lb_lng == nullptr){
        this->lb_lng = new QLabel(QStringLiteral("经度"));
        this->lb_lng->setObjectName("WidgetCMD");
    }
    if( this->lb_alt == nullptr){
        this->lb_alt = new QLabel(QStringLiteral("高度"));
        this->lb_alt->setObjectName("WidgetCMD");
    }
    if( this->lb_radius == nullptr){
        this->lb_radius = new QLabel(QStringLiteral("半径"));
        this->lb_radius->setObjectName("WidgetCMD");
    }

    if( this->dSpinBox_lat == nullptr){
        this->dSpinBox_lat = new QDoubleSpinBox;
        this->dSpinBox_lat->setDecimals(7);
        this->dSpinBox_lat->setMinimum(-90.00);
        this->dSpinBox_lat->setMaximum(90.00);
        this->dSpinBox_lat->setObjectName("WidgetCMD");
    }
    if( this->dSpinBox_lng == nullptr){
        this->dSpinBox_lng = new QDoubleSpinBox;
        this->dSpinBox_lng->setDecimals(7);
        this->dSpinBox_lng->setMinimum(-180.00);
        this->dSpinBox_lng->setMaximum(180.00);
        this->dSpinBox_lng->setObjectName("WidgetCMD");
    }
    if( this->dSpinBox_alt == nullptr){
        this->dSpinBox_alt = new QDoubleSpinBox;
        this->dSpinBox_alt->setDecimals(2);
        this->dSpinBox_alt->setMinimum(-200.00);
        this->dSpinBox_alt->setMaximum(10000.00);
        this->dSpinBox_alt->setValue(100);
        this->dSpinBox_alt->setObjectName("WidgetCMD");
    }
    if( this->dSpinBox_radius == nullptr){
        this->dSpinBox_radius = new QDoubleSpinBox;
        this->dSpinBox_radius->setDecimals(0);
        this->dSpinBox_radius->setMinimum(2.00);
        this->dSpinBox_radius->setMaximum(0xffff);
        this->dSpinBox_radius->setValue(100);
        this->dSpinBox_radius->setObjectName("WidgetCMD");
    }

    if( this->cb_radius_dir == nullptr){
        this->cb_radius_dir = new QCheckBox(QStringLiteral("逆时针"));
        this->cb_radius_dir->setObjectName("WidgetCMD");
    }

    if( this->btn_upload == nullptr){
        this->btn_upload = new QPushButton(QStringLiteral("设置"));
        this->btn_upload->setObjectName("WidgetCMD");
    }
    if( this->btn_downlaod == nullptr){
        this->btn_downlaod = new QPushButton(QStringLiteral("查询"));
        this->btn_downlaod->setObjectName("WidgetCMD");
    }
    if( this->btn_GetPosFromGIS == nullptr){
        this->btn_GetPosFromGIS = new QPushButton(QStringLiteral("地图点选"));
        this->btn_GetPosFromGIS->setObjectName("WidgetCMD");
    }
    if( this->btn_GetPosFromHome == nullptr){
        this->btn_GetPosFromHome = new QPushButton(QStringLiteral("原点坐标"));
        this->btn_GetPosFromHome->setObjectName("WidgetCMD");
    }

    if( this->btn_SetModeRTL == nullptr){
        this->btn_SetModeRTL = new QPushButton(QStringLiteral("立即返航"));
        this->btn_SetModeRTL->setObjectName("WidgetCMD_Action");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addWidget(lb_lat    ,0,0,1,1,Qt::AlignRight);
    this->widgetLayout->addWidget(lb_lng    ,1,0,1,1,Qt::AlignRight);
    this->widgetLayout->addWidget(lb_alt    ,2,0,1,1,Qt::AlignRight);
    this->widgetLayout->addWidget(lb_radius ,3,0,1,1,Qt::AlignRight);

    this->widgetLayout->addWidget(dSpinBox_lat ,0,1,1,2);
    this->widgetLayout->addWidget(dSpinBox_lng ,1,1,1,2);
    this->widgetLayout->addWidget(dSpinBox_alt ,2,1,1,2);
    this->widgetLayout->addWidget(dSpinBox_radius ,3,1,1,1);
    this->widgetLayout->addWidget(cb_radius_dir ,3,2,1,1);



    QGridLayout* pushlayout  = new QGridLayout();
    pushlayout->addWidget(btn_GetPosFromGIS,0,0,1,1);
    pushlayout->addWidget(btn_GetPosFromHome,0,1,1,1);
    pushlayout->addWidget(btn_downlaod,1,0,1,1);
    pushlayout->addWidget(btn_upload,1,1,1,1);
    pushlayout->addWidget(btn_SetModeRTL,2,0,1,2);

    this->widgetLayout->addLayout(pushlayout ,0,4,4,3);

    this->widgetLayout->setSpacing(5);
    this->widgetLayout->setContentsMargins(30,22,30,22);
    this->setLayout(this->widgetLayout);

}

void P_CMD_RTL::connectSignalAndSlot()
{
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&P_CMD_RTL::handle_DMMM_event);

    connect(this->btn_downlaod,&QPushButton::pressed,this,&P_CMD_RTL::handle_download);
    connect(this->btn_upload,&QPushButton::pressed,this,&P_CMD_RTL::handle_upload);
    connect(this->btn_GetPosFromGIS,&QPushButton::pressed,this,&P_CMD_RTL::handle_GetPosFromGIS);
    connect(this->btn_GetPosFromHome,&QPushButton::pressed,this,&P_CMD_RTL::handle_GetPosFromHome);
    connect(this->btn_SetModeRTL,&QPushButton::pressed,this,&P_CMD_RTL::handle_SetModeRTL);
    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            connect(Qt::GISMap()->getModel_RTLWaypoint(),&GIS_RTLWaypointModel::dataChanged,this,&P_CMD_RTL::RTLModelChange);
        }
    }
    connect(this->dSpinBox_lat,&QDoubleSpinBox::editingFinished,this,&P_CMD_RTL::update_model);
    connect(this->dSpinBox_lng,&QDoubleSpinBox::editingFinished,this,&P_CMD_RTL::update_model);
    connect(this->dSpinBox_radius,&QDoubleSpinBox::editingFinished,this,&P_CMD_RTL::update_model);

//    connect(this->getMousePressedPositionButton,&QPushButton::pressed,this,&P_CMD_RTL::getMousePressedPositionButtonPressedSlot);
//    connect(this->getLocalPositionButton,&QPushButton::pressed,this,&P_CMD_RTL::getLocalPositionButtonPressedSlot);

//    connect(this->flyToWayPointButton,&QPushButton::clicked,this,&P_CMD_RTL::flayToButtonPressedSlot);

//    if(Qt::GISMap()){
//        if(Qt::GISMap()->getPointModel()){
//            connect(Qt::GISMap()->getPointModel(),&GIS_AirPointModel::dataChanged,this,&P_CMD_RTL::posModelChange);
//        }
//    }




//    connect(this->setHeadingButton,&QPushButton::pressed,this,&P_CMD_RTL::handle_setHeading);
}


void P_CMD_RTL::handle_DMMM_event(int ev, int linkid)
{
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_RTL_Waypoint_received:
    {
        FlyLink* link = Qt::DMMM()->getFlyLink_main();
        if(link != nullptr){
            Q_DMMM::DataPool_t data = Qt::DMMM()->getData_main();
            dSpinBox_lat->setValue(1e-7*(double)data.flylink.RTL.loc.x);
            dSpinBox_lng->setValue(1e-7*(double)data.flylink.RTL.loc.y);
            dSpinBox_alt->setValue(1e-2*(double)data.flylink.RTL.loc.z);
            dSpinBox_radius->setValue(qAbs(data.flylink.RTL.loc.radius));
            if(data.flylink.RTL.loc.radius < 0){
                cb_radius_dir->setChecked(true);
            }else{

                cb_radius_dir->setChecked(false);
            }

            update_model();
        }
    }
    break;

        default:break;
    }
}

void P_CMD_RTL::handle_download()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->do_req_RTLWaypoint();
    }
}

void P_CMD_RTL::handle_upload()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        FlyLink::waypoint_new_t pkt{};
        pkt.frame = FlyLink::AltFrame_ABOVE_HOME;
        pkt.x = dSpinBox_lat->value()*1e7;
        pkt.y = dSpinBox_lng->value()*1e7;
        pkt.z = dSpinBox_alt->value()*1e2;
        pkt.radius = dSpinBox_radius->value();
        if(cb_radius_dir->isChecked()){
            pkt.radius = -qAbs(pkt.radius);
        }
        link->set_RTLWaypoint(pkt);
        update_model();
    }
}

void P_CMD_RTL::handle_GetPosFromGIS()
{
    if(Qt::GISMap()){
        Qt::GISMap()->setMapMode(6);
    }
}

void P_CMD_RTL::handle_GetPosFromHome()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        Q_DMMM::DataPool_t data = Qt::DMMM()->getData_main();
        if(data.flylink.tHome.is_get){
            dSpinBox_lat->setValue(1e-7*(double)data.flylink.tHome.loc.latitude);
            dSpinBox_lng->setValue(1e-7*(double)data.flylink.tHome.loc.longitude);
            update_model();
        }
    }
}

void P_CMD_RTL::handle_SetModeRTL()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        link->set_PlaneMode_RTL();
    }
}

void P_CMD_RTL::update_model()
{
    if(Qt::GISMap()){
        if(Qt::GISMap()->getModel_RTLWaypoint()!=nullptr){


                Qt::GISMap()->getModel_RTLWaypoint()->update_Waypoint(dSpinBox_lat->value(),\
                                                         dSpinBox_lng->value(),\
                                                         dSpinBox_alt->value(),
                                                         dSpinBox_radius->value(), \
                                                         true);
        }
    }
}

void P_CMD_RTL::RTLModelChange()
{
    if(Qt::GISMap()){
        if(Qt::GISMap()->getModel_RTLWaypoint()){
            QGeoCoordinate coor = Qt::GISMap()->getModel_RTLWaypoint()->getCoor();
            this->dSpinBox_lat->setValue(coor.latitude());
            this->dSpinBox_lng->setValue(coor.longitude());
        }
    }
}



