#include "P_Waypoint.h"
#include "DMMM.h"
#include "gis_mapview.h"
P_CMD_Waypoint::P_CMD_Waypoint()
{
    widgetInit();
    connectSignalAndSlot();
}

void P_CMD_Waypoint::widgetInit()
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
        this->dSpinBox_lat->setSingleStep(0.000001);
        this->dSpinBox_lat->setObjectName("WidgetCMD");
    }
    if( this->dSpinBox_lng == nullptr){
        this->dSpinBox_lng = new QDoubleSpinBox;
        this->dSpinBox_lng->setDecimals(7);
        this->dSpinBox_lng->setMinimum(-180.00);
        this->dSpinBox_lng->setMaximum(180.00);
        this->dSpinBox_lng->setSingleStep(0.000001);
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

    if( this->btn_GetPosFromGIS == nullptr){
        this->btn_GetPosFromGIS = new QPushButton(QStringLiteral("地图点选"));
        this->btn_GetPosFromGIS->setObjectName("WidgetCMD");
    }
    if( this->btn_GetPosFromCurrent == nullptr){
        this->btn_GetPosFromCurrent = new QPushButton(QStringLiteral("当前位置"));
        this->btn_GetPosFromCurrent->setObjectName("WidgetCMD");
    }

    if( this->btn_SetModeRTL == nullptr){
        this->btn_SetModeRTL = new QPushButton(QStringLiteral("飞向此点"));
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
    pushlayout->addWidget(btn_GetPosFromCurrent,0,1,1,1);
    pushlayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 1, 0, 1, 2);
    pushlayout->addWidget(btn_SetModeRTL,2,0,1,2);

    this->widgetLayout->addLayout(pushlayout ,0,4,4,3);

    this->widgetLayout->setSpacing(5);
    this->widgetLayout->setContentsMargins(30,22,30,22);
    this->setLayout(this->widgetLayout);

}

void P_CMD_Waypoint::connectSignalAndSlot()
{

    connect(this->btn_GetPosFromGIS,&QPushButton::pressed,this,&P_CMD_Waypoint::handle_GetPosFromGIS);
    connect(this->btn_GetPosFromCurrent,&QPushButton::pressed,this,&P_CMD_Waypoint::handle_GetPosFromCurrent);
    connect(this->btn_SetModeRTL,&QPushButton::pressed,this,&P_CMD_Waypoint::handle_SetModeRTL);

    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            connect(Qt::GISMap()->getPointModel(),&GIS_AirPointModel::dataChanged,this,&P_CMD_Waypoint::RTLModelChange);
        }
    }
    connect(this->dSpinBox_lat,&QDoubleSpinBox::editingFinished,this,&P_CMD_Waypoint::update_model);
    connect(this->dSpinBox_lng,&QDoubleSpinBox::editingFinished,this,&P_CMD_Waypoint::update_model);
    connect(this->dSpinBox_radius,&QDoubleSpinBox::editingFinished,this,&P_CMD_Waypoint::update_model);
}


void P_CMD_Waypoint::handle_GetPosFromGIS()
{
    if(Qt::GISMap()){
        Qt::GISMap()->setMapMode(5);
    }
}

void P_CMD_Waypoint::handle_GetPosFromCurrent()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        Q_DMMM::DataPool_t data = Qt::DMMM()->getData_main();
        if(data.flylink.tGNSS->fix_type >= FlyLink::GPS_FIX_TYPE_2D_FIX){
            dSpinBox_lat->setValue(1e-7*(double)data.flylink.tVehicle.lat);
            dSpinBox_lng->setValue(1e-7*(double)data.flylink.tVehicle.lng);
            dSpinBox_alt->setValue((double)data.flylink.tVehicle.pos_m[2]);
            update_model();
        }
    }
}

void P_CMD_Waypoint::handle_SetModeRTL()
{
    FlyLink* link = Qt::DMMM()->getFlyLink_main();
    if(link != nullptr){
        FlyLink::guided_nav_wp_t pkt{};
        pkt.alt_frame = FlyLink::MISSION_ALT_FRAME_RELATIVE_ALT;
        pkt.latitude = dSpinBox_lat->value()*1e7;
        pkt.longitude= dSpinBox_lng->value()*1e7;
        pkt.alt_m = dSpinBox_alt->value();
        pkt.radius = dSpinBox_radius->value();
        if(cb_radius_dir->isChecked()){
            pkt.radius = -qAbs(pkt.radius);
        }
        link->set_guided_nav_wp(pkt);
    }
}

void P_CMD_Waypoint::update_model()
{
    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            Qt::GISMap()->getPointModel()->update_Waypoint(this->dSpinBox_lat->value(),this->dSpinBox_lng->value(),this->dSpinBox_alt->value(),this->dSpinBox_radius->value(),true);
        }
    }
}

void P_CMD_Waypoint::RTLModelChange()
{
    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            QGeoCoordinate coor = Qt::GISMap()->getPointModel()->getCoor();
            this->dSpinBox_lat->setValue(coor.latitude());
            this->dSpinBox_lng->setValue(coor.longitude());
            update_model();
        }
    }
}



