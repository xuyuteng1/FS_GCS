#include "C_WaypointWidget.h"
#include "DMMM.h"
#include "gis_mapview.h"
C_WaypointWidget::C_WaypointWidget()
{

    widgetInit();
    connectSignalAndSlot();
}

void C_WaypointWidget::widgetInit()
{

    if(this->getLocalPositionButton == nullptr){
        this->getLocalPositionButton = new QPushButton(QStringLiteral("当前位置"));
        this->getLocalPositionButton->setIcon(QIcon(":/img/png/waypoint/PosCurrent.png"));
        this->getLocalPositionButton->setToolTip(QStringLiteral("获取当前点坐标"));
        this->getLocalPositionButton->setIconSize(QSize(25,25));
        this->getLocalPositionButton->setObjectName("WidgetCMD");
    }
    if(this->getMousePressedPositionButton == nullptr){
        this->getMousePressedPositionButton = new QPushButton(QStringLiteral("地图点选"));
        this->getMousePressedPositionButton->setIcon(QIcon(":/img/png/waypoint/PosSelect.png"));
        this->getMousePressedPositionButton->setToolTip(QStringLiteral("地图点选坐标"));
        this->getMousePressedPositionButton->setIconSize(QSize(25,25));
        this->getMousePressedPositionButton->setObjectName("WidgetCMD");
    }
    if(this->lngLabel == nullptr){
        this->lngLabel = new QLabel(QStringLiteral("经    度"));
        this->lngLabel->setObjectName("WidgetCMD");
    }
    if(this->latLabel == nullptr){
        this->latLabel = new QLabel(QStringLiteral("纬    度"));
        this->latLabel->setObjectName("WidgetCMD");
    }
    if( this->altLabel == nullptr){
        this->altLabel = new QLabel(QStringLiteral("相对高度"));
        this->altLabel->setObjectName("WidgetCMD");
    }
    if( this->headingLabel == nullptr){
        this->headingLabel = new QLabel(QStringLiteral("航    向"));
        this->headingLabel->setObjectName("WidgetCMD");
    }

    if(this->lngSpinBox == nullptr){
        this->lngSpinBox = new QDoubleSpinBox;
        this->lngSpinBox->setDecimals(7);
        this->lngSpinBox->setMinimum(-180.00);
        this->lngSpinBox->setMaximum(180.00);
        this->lngSpinBox->setSingleStep(0.000001);
        this->lngSpinBox->setObjectName("WidgetCMD");
    }
    if(this->latSpinBox == nullptr){
        this->latSpinBox = new QDoubleSpinBox;
        this->latSpinBox->setDecimals(7);
        this->latSpinBox->setMinimum(-90.00);
        this->latSpinBox->setMaximum(90.00);
        this->latSpinBox->setSingleStep(0.000001);
        this->latSpinBox->setObjectName("WidgetCMD");
    }
    if(this->altitudeSpinBox == nullptr){
        this->altitudeSpinBox = new QDoubleSpinBox;
        this->altitudeSpinBox->setDecimals(1);
        this->altitudeSpinBox->setMinimum(-200);
        this->altitudeSpinBox->setMaximum(8000);
        this->altitudeSpinBox->setValue(100);
        this->altitudeSpinBox->setObjectName("WidgetCMD");
    }
    if(this->flyToWayPointButton == nullptr){
        this->flyToWayPointButton = new QPushButton(QStringLiteral("飞行至航点"));
//        this->flyToWayPointButton->setIcon(QIcon(":/img/icon/flyTo.png"));
        this->flyToWayPointButton->setToolTip(QStringLiteral("飞行至航点"));
        this->flyToWayPointButton->setObjectName("WidgetCMD_Action");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->HeadingSpinBox == nullptr){
        this->HeadingSpinBox = new QDoubleSpinBox;
        this->HeadingSpinBox->setDecimals(1);
        this->HeadingSpinBox->setMinimum(0);
        this->HeadingSpinBox->setMaximum(360);
        this->HeadingSpinBox->setObjectName("WidgetCMD");
    }
    if(this->setHeadingButton == nullptr){
        this->setHeadingButton = new QPushButton(QStringLiteral("更改航向"));
//        this->setHeadingButton->setIcon(QIcon(":/img/icon/setHeading.png"));
        this->setHeadingButton->setToolTip(QStringLiteral("更改航向"));
//        this->setHeadingButton->setIconSize(QSize(32,32));
        this->setHeadingButton->setObjectName("WidgetCMD_Action");
    }


    if(this->setAltitudeButton == nullptr){
        this->setAltitudeButton = new QPushButton(QStringLiteral("更改高度"));
//        this->setAltitudeButton->setIcon(QIcon(":/img/icon/setAlt.png"));
        this->setAltitudeButton->setToolTip(QStringLiteral("更改高度"));
//        this->setAltitudeButton->setIconSize(QSize(32,32));
        this->setAltitudeButton->setObjectName("WidgetCMD_Action");
    }

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(this->getMousePressedPositionButton);
    buttonLayout->addWidget(this->getLocalPositionButton);
    buttonLayout->setSpacing(2);

    QGridLayout* Layout_PosVal = new QGridLayout();
    Layout_PosVal->addWidget(this->latLabel,0,0,1,1,Qt::AlignCenter);
    Layout_PosVal->addWidget(this->lngLabel,0,1,1,1,Qt::AlignCenter);
    Layout_PosVal->addWidget(this->altLabel,0,2,1,1,Qt::AlignCenter);

    Layout_PosVal->addWidget(this->latSpinBox,1,0,1,1,Qt::AlignCenter);
    Layout_PosVal->addWidget(this->lngSpinBox,1,1,1,1,Qt::AlignCenter);
    Layout_PosVal->addWidget(this->altitudeSpinBox,1,2,1,1,Qt::AlignCenter);

    Layout_PosVal->addWidget(this->flyToWayPointButton,2,0,1,3);
//    Layout_PosVal->addWidget(this->setAltitudeButton,2,2,1,1,Qt::AlignCenter);
    Layout_PosVal->setRowStretch(0,1);
    Layout_PosVal->setRowStretch(1,1);
    Layout_PosVal->setRowStretch(2,2);

    QGridLayout *headingLayout = new QGridLayout();

    headingLayout->addWidget(this->headingLabel,0,0,1,1,Qt::AlignCenter);
    headingLayout->addWidget(this->HeadingSpinBox,1,0,1,1,Qt::AlignCenter);
    headingLayout->addWidget(this->setHeadingButton,2,0,1,1);

    headingLayout->setRowStretch(0,1);
    headingLayout->setRowStretch(1,1);
    headingLayout->setRowStretch(2,2);

    this->widgetLayout->addLayout(buttonLayout,0,1,3,1,Qt::AlignCenter);
    this->widgetLayout->addLayout(Layout_PosVal,0,2,3,1,Qt::AlignCenter);
    this->widgetLayout->addLayout(headingLayout,0,4,3,1,Qt::AlignCenter);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,3,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,5,3,1);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,3,3,1);

//    this->widgetLayout->setSpacing(5);
    this->widgetLayout->setContentsMargins(30,22,30,22);

    this->setLayout(this->widgetLayout);

}

void C_WaypointWidget::connectSignalAndSlot()
{

    connect(this->getMousePressedPositionButton,&QPushButton::pressed,this,&C_WaypointWidget::getMousePressedPositionButtonPressedSlot);
    connect(this->getLocalPositionButton,&QPushButton::pressed,this,&C_WaypointWidget::getLocalPositionButtonPressedSlot);

    connect(this->flyToWayPointButton,&QPushButton::clicked,this,&C_WaypointWidget::flayToButtonPressedSlot);

    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            connect(Qt::GISMap()->getPointModel(),&GIS_AirPointModel::dataChanged,this,&C_WaypointWidget::posModelChange);
        }
    }


    connect(this->latSpinBox,&QDoubleSpinBox::editingFinished,this,&C_WaypointWidget::posValueEdit);
    connect(this->lngSpinBox,&QDoubleSpinBox::editingFinished,this,&C_WaypointWidget::posValueEdit);

    connect(this->setAltitudeButton,&QPushButton::pressed,this,&C_WaypointWidget::handle_setAltitude);
    connect(this->setHeadingButton,&QPushButton::pressed,this,&C_WaypointWidget::handle_setHeading);
}


void C_WaypointWidget::flayToButtonPressedSlot()
{
    QMessageBox msgBox;
    msgBox.setStyleSheet(QString("QMessageBox {\
                                 color:#FFFFFF;\
                                 font: 400 11pt \"Microsoft YaHei\";\
                                 background-color:rgba(6,7,19,255);\
                                 border: 0px solid gray;  \
                             }\
                             \
                             QMessageBox QLabel {\
                                 color:#FFFFFF;\
                                 font: 400 9.5pt \"Microsoft YaHei\";\
                             }\
                             \
                             QMessageBox QPushButton {\
                                 color:#FFFFFF;\
                                 font: 400 9pt \"Microsoft YaHei\";\
                                 background-color:rgba(22, 119, 255,255);\
                             }\
                             \
                             QMessageBox QPushButton:hover{\
                                 color:#FFFFFF;\
                                 font: 400 9pt \"Microsoft YaHei\";\
                                 background-color:rgba(239, 87, 103,255);\
                             }\
                             \
                             QMessageBox QPushButton:pressed{\
                                 color:#FFFFFF;\
                                 font: 400 9.5pt \"Microsoft YaHei\";\
                                 background-color:rgba(239, 87, 103,200);\
                             }"));
    msgBox.setWindowTitle(QStringLiteral("确认飞行至航点"));
    msgBox.setInformativeText(QStringLiteral("是否确认飞行至航点： \r\n"
                                             "    经度:%1\r\n"
                                             "    纬度:%2\r\n"
                                             "    高度:%3").arg(this->lngSpinBox->value()).arg(this->latSpinBox->value()).arg(this->altitudeSpinBox->value()));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
            flyToWayPointButtonPressedSlot();break;
    }
}

void C_WaypointWidget::getLocalPositionButtonPressedSlot()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        this->latSpinBox->setValue(Qt::DMMM()->getData_main().flylink.tVehicle.lat*1e-7);
        this->lngSpinBox->setValue(Qt::DMMM()->getData_main().flylink.tVehicle.lng*1e-7);
        this->altitudeSpinBox->setValue(Qt::DMMM()->getData_main().flylink.tVehicle.pos_m[2]);
        posValueEdit();
    }
}

void C_WaypointWidget::getMousePressedPositionButtonPressedSlot()
{
    if(Qt::GISMap()){
        Qt::GISMap()->setMapMode(5);
    }
}

void C_WaypointWidget::flyToWayPointButtonPressedSlot()
{
    FlyLink::guided_nav_wp_t WP{};
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        WP.latitude = this->latSpinBox->value()*1e7;
        WP.longitude = this->lngSpinBox->value()*1e7;
        WP.alt_m = this->altitudeSpinBox->value();
        link->set_guided_nav_wp(WP);
    }
}

void C_WaypointWidget::posModelChange()
{
    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            QGeoCoordinate coor = Qt::GISMap()->getPointModel()->getCoor();
            this->latSpinBox->setValue(coor.latitude());
            this->lngSpinBox->setValue(coor.longitude());
        }
    }
}

void C_WaypointWidget::posValueEdit()
{
    if(Qt::GISMap()){
        if(Qt::GISMap()->getPointModel()){
            Qt::GISMap()->getPointModel()->update_Waypoint(this->latSpinBox->value(),this->lngSpinBox->value(),this->altitudeSpinBox->value(),0,true);
        }
    }
}

void C_WaypointWidget::handle_setAltitude()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_set_alt_m(this->altitudeSpinBox->value());
    }
}

void C_WaypointWidget::handle_setHeading()
{
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_set_heading(this->HeadingSpinBox->value());
    }
}
