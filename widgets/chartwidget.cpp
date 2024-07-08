#include "chartwidget.h"
#include<QRandomGenerator>
ChartWidget::ChartWidget(QWidget *parent): QWidget(parent)
{

    widgetInit();
    if(this->timer == nullptr){
        this->timer = new QTimer();
    }

    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("波形显示"));
    QFile file(QString(":/style/widgetStyle.qss"));

    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
    this->setMinimumSize(1000,600);
}

void ChartWidget::widgetInit()
{
    if(this->w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        this->w_title = new WidgetTitle(pix,QStringLiteral("波形显示"));
        this->w_title->setMaximumHeight(40);
    }

    rightMenu = new QMenu(this);
    ActionClearAllGriph = new QAction(QStringLiteral("清除所有图表"));
    this->ActionClearAllGriph->setCheckable(false);
    rightMenu->addAction(ActionClearAllGriph);

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }
    if(this->ChartLayout == nullptr){
        this->ChartLayout = new QGridLayout();
    }
    if(this->itemLayout == nullptr){
        this->itemLayout = new QGridLayout();
    }

    for(int i = 0;i< CHART_NUMBER;i++){
        buttonGroup[i] = new QButtonGroup();
        buttonGroup[i]->setExclusive(false);
        Chart[i] = new uChartView();
    }
    // 表格初始化
    this->ChartLayout->addWidget(this->Chart[0],0,0,5,20);
    this->ChartLayout->addWidget(this->Chart[1],5,0,5,20);

    this->ChartLayout->setVerticalSpacing(5);
    this->ChartLayout->setMargin(0);

    if(ItemBox == nullptr){
        ItemBox = new QToolBox();
        ItemBox->setObjectName("chartToolBox");
    }
    this->itemLayout->addWidget(ItemBox,0,0,20,20);

    chartListInit();

//    this->widgetLayout->addWidget(this->w_title,0,0,1,20);
    this->widgetLayout->addLayout(this->itemLayout,1,0,20,1);
    this->widgetLayout->addLayout(this->ChartLayout,1,1,20,19);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);


    this->setLayout(this->widgetLayout);
}

void ChartWidget::connectSignalAndSlot()
{
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
    connect(this->timer,&QTimer::timeout,this,&ChartWidget::timeroutfunc);

    connect(this->buttonGroup[0],&QButtonGroup::idToggled,this->Chart[0],&uChartView::buttonGroupToggledSlot);
    connect(this->buttonGroup[1],&QButtonGroup::idToggled,this->Chart[1],&uChartView::buttonGroupToggledSlot);
    connect(this->rightMenu,&QMenu::triggered,this,&ChartWidget::menuActionTargetSlot);
}

void ChartWidget::additemToChart(QString name, QListWidget *listwidget, bool enable1, bool enable2)
{
    if(this->nameMap.find(name) != this->nameMap.end()){
        return;
    }
    int id = nameMap.count();
    nameMap.insert(name,id);
    QCheckBox *checkBox1 = new QCheckBox();
    QLabel    *labelname = new QLabel(name+":");
    QCheckBox *checkBox2 = new QCheckBox();
    checkBox1->setChecked(enable1);
    checkBox2->setChecked(enable2);
    checkBox1->setObjectName("widgetCheckBox");
    checkBox2->setObjectName("widgetCheckBox");
    labelname->setObjectName("chartWidgetLabel");
    labelname->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    // 添加至图标
    if(this->Chart[0] != nullptr){
        this->Chart[0]->addNewGraph(id,name,enable1,false);
    }

    if(this->Chart[1] != nullptr){
        this->Chart[1]->addNewGraph(id,name,enable2,true);
    }

    // 添加至buttomgroup
    this->buttonGroup[0]->addButton(checkBox1,id);
    this->buttonGroup[1]->addButton(checkBox2,id);

    // 添加布局
    if(listwidget !=nullptr){
        QHBoxLayout* Hlayout = new QHBoxLayout();
        Hlayout->addWidget(labelname);
        Hlayout->addWidget(checkBox1);
        Hlayout->addWidget(checkBox2);
        Hlayout->setSpacing(0);
        Hlayout->setMargin(0);

        QListWidgetItem *item = new QListWidgetItem();
        QGroupBox *box = new QGroupBox();
        box->setLayout(Hlayout);
        box->setObjectName("widgetGroupBox_no_border");
        listwidget->addItem(item);
        listwidget->setItemWidget(item,box);
    }
}

void ChartWidget::additemDataToChart(QString name, double x, double y)
{
    if(this->nameMap.find(name) == this->nameMap.end()){
        return;
    }
    int id = this->nameMap.find(name).value();
    for(int i = 0; i < CHART_NUMBER;i++){
        if(this->Chart[i] != nullptr){
            this->Chart[i]->addGraphData(id,x,y);
        }
    }
}

void ChartWidget::chartListInit()
{
    this->ListVehicleInfo     = new QListWidget();
    this->ListVehicleInfo->setObjectName("chartWidget");
    this->ListVehicleInfo->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(this->ListVehicleInfo,QScroller::LeftMouseButtonGesture);
    this->ListVehicleInfo->verticalScrollBar()->setSingleStep(8);
//    this->ListVehicleInfo->verticalScrollBar()->setVisible(false);


    this->ListSysInfo = new QListWidget();
    this->ListSysInfo->setObjectName("chartWidget");
    this->ListSysInfo->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(this->ListSysInfo,QScroller::LeftMouseButtonGesture);
    this->ListSysInfo->verticalScrollBar()->setSingleStep(8);

    this->ListIMU = new QListWidget();
    this->ListIMU->setObjectName("chartWidget");
    this->ListIMU->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//    QScroller::grabGesture(this->ListIMU,QScroller::LeftMouseButtonGesture);
    this->ListIMU->verticalScrollBar()->setSingleStep(4);
//    this->ListIMU->verticalScrollBar()->setVisible(false);

    this->ListRCSVR = new QListWidget();
    this->ListRCSVR->setObjectName("chartWidget");
    this->ListRCSVR->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ListRCSVR->verticalScrollBar()->setSingleStep(4);

    this->ListCompass = new QListWidget();
    this->ListCompass->setObjectName("chartWidget");
    this->ListCompass->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ListCompass->verticalScrollBar()->setSingleStep(4);

    this->ListBaro = new QListWidget();
    this->ListBaro->setObjectName("chartWidget");
    this->ListBaro->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ListBaro->verticalScrollBar()->setSingleStep(4);

    this->ListTarget = new QListWidget();
    this->ListTarget->setObjectName("chartWidget");
    this->ListTarget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->ListTarget->verticalScrollBar()->setSingleStep(4);


    if(ItemBox != nullptr){
        ItemBox->setMaximumWidth(180);
        ItemBox->addItem(ListVehicleInfo,       QStringLiteral("机体信息"));
        ItemBox->addItem(ListTarget,            QStringLiteral("目标信息"));
        ItemBox->addItem(ListSysInfo,           QStringLiteral("系统信息"));
        ItemBox->addItem(ListIMU,               QStringLiteral("IMU信息"));
        ItemBox->addItem(ListCompass,           QStringLiteral("罗盘信息"));
        ItemBox->addItem(ListBaro,              QStringLiteral("气压信息"));
        ItemBox->addItem(ListRCSVR,             QStringLiteral("输入输出"));
        ItemBox->setCurrentWidget(ListRCSVR);
    }

    // SysInfo_t
    this->additemToChart(QStringLiteral("CPU负载" ),ListSysInfo);
    this->additemToChart(QStringLiteral("飞行航时" ),ListSysInfo);
    this->additemToChart(QStringLiteral("累计航时" ),ListSysInfo);
    this->additemToChart(QStringLiteral("飞行航程" ),ListSysInfo);
    this->additemToChart(QStringLiteral("累计航程" ),ListSysInfo);
    this->additemToChart(QStringLiteral("当前电压" ),ListSysInfo);
    this->additemToChart(QStringLiteral("当前电流" ),ListSysInfo);
    this->additemToChart(QStringLiteral("油 门 值" ),ListSysInfo);
    this->additemToChart(QStringLiteral("当前温度" ),ListSysInfo);
    this->additemToChart(QStringLiteral("离家距离" ),ListSysInfo);
    this->additemToChart(QStringLiteral("家 航 向" ),ListSysInfo);
    this->additemToChart(QStringLiteral("目标距离" ),ListSysInfo);
    this->additemToChart(QStringLiteral("高度差值" ),ListSysInfo);
    this->additemToChart(QStringLiteral("侧偏距离" ),ListSysInfo);


    // TargetInfo
    this->additemToChart(QStringLiteral("目标纬度" ),ListTarget);
    this->additemToChart(QStringLiteral("目标经度" ),ListTarget);
    this->additemToChart(QStringLiteral("目标海拔" ),ListTarget);
    this->additemToChart(QStringLiteral("目标高度" ),ListTarget);
    this->additemToChart(QStringLiteral("期望高度" ),ListTarget);
    this->additemToChart(QStringLiteral("目标速度E" ),ListTarget);
    this->additemToChart(QStringLiteral("目标速度N" ),ListTarget);
    this->additemToChart(QStringLiteral("目标速度U" ),ListTarget);
    this->additemToChart(QStringLiteral("目标Roll" ),ListTarget);
    this->additemToChart(QStringLiteral("目标Pitch" ),ListTarget);
    this->additemToChart(QStringLiteral("目标Yaw" ),ListTarget);
    this->additemToChart(QStringLiteral("目标加速度X" ),ListTarget);
    this->additemToChart(QStringLiteral("目标加速度Y" ),ListTarget);
    this->additemToChart(QStringLiteral("目标加速度Z" ),ListTarget);
    this->additemToChart(QStringLiteral("目标角速度X" ),ListTarget);
    this->additemToChart(QStringLiteral("目标角速度Y" ),ListTarget);
    this->additemToChart(QStringLiteral("目标角速度Z" ),ListTarget);

//    // vehicle_t
    this->additemToChart(QStringLiteral("Roll"      ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("Pitch"     ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("Yaw"       ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("加速度X"    ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("加速度Y"    ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("加速度Z"    ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("角速度X"    ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("角速度Y"    ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("角速度Z"    ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("纬度"       ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("经度"       ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("海拔高度"   ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("相对位置X"  ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("相对位置Y"  ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("相对位置Z"  ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("速度X"      ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("速度Y"      ),ListVehicleInfo);
    this->additemToChart(QStringLiteral("速度Z"      ),ListVehicleInfo);

    // IMU
    for(int i=0;i<3;i++){
        this->additemToChart(QStringLiteral("加计")+QString::number(i+1)+"-X"   ,ListIMU);
        this->additemToChart(QStringLiteral("加计")+QString::number(i+1)+"-Y"   ,ListIMU);
        this->additemToChart(QStringLiteral("加计")+QString::number(i+1)+"-Z"   ,ListIMU);
        this->additemToChart(QStringLiteral("陀螺")+QString::number(i+1)+"-X"   ,ListIMU);
        this->additemToChart(QStringLiteral("陀螺")+QString::number(i+1)+"-Y"   ,ListIMU);
        this->additemToChart(QStringLiteral("陀螺")+QString::number(i+1)+"-Z"   ,ListIMU);
        this->additemToChart(QStringLiteral("震动")+QString::number(i+1)+"-X"   ,ListIMU);
        this->additemToChart(QStringLiteral("震动")+QString::number(i+1)+"-Y"   ,ListIMU);
        this->additemToChart(QStringLiteral("震动")+QString::number(i+1)+"-Z"   ,ListIMU);
        this->additemToChart(QStringLiteral("IMU温度")  +QString::number(i+1)      ,ListIMU);
        this->additemToChart(QStringLiteral("过载数") +QString::number(i+1)     ,ListIMU);
    }

    // 输入输出
    for(int i = 0; i< 16 ; i++){
        this->additemToChart(QStringLiteral("R C")+QString::number(i+1),ListRCSVR);
    }

    for(int i = 0; i< 16 ; i++){
        this->additemToChart(QStringLiteral("OUT")+QString::number(i+1),ListRCSVR);
    }

    // 罗盘信息
    for(int  i = 0;i < 3 ;i++){

        this->additemToChart(QStringLiteral("Mag")+QString::number(i+1)+"-X",ListCompass);
        this->additemToChart(QStringLiteral("Mag")+QString::number(i+1)+"-Y",ListCompass);
        this->additemToChart(QStringLiteral("Mag")+QString::number(i+1)+"-Z",ListCompass);
    }

    // 气压信息
    for(int  i = 0;i < 3 ;i++){

        this->additemToChart(QStringLiteral("当前气压")+QString::number(i+1),ListBaro);
        this->additemToChart(QStringLiteral("气压温度")+QString::number(i+1),ListBaro);
        this->additemToChart(QStringLiteral("大气密度系数")+QString::number(i+1),ListBaro);
    }


}

void ChartWidget::updateChartData()
{
    QDateTime nowTime = QDateTime::currentDateTime();
    double diffTime = abs(nowTime.msecsTo(this->showTime))/1000.0f;

    if(Qt::DMMM()->getLinkActive()){
        this->datapool = Qt::DMMM()->getData_main();
        additemDataToChart(QStringLiteral("横滚"),diffTime,this->datapool.flylink.tVehicle.roll_cd*0.01f);
        additemDataToChart(QStringLiteral("俯仰"),diffTime,this->datapool.flylink.tVehicle.pitch_cd*0.01f);
        additemDataToChart(QStringLiteral("航向"),diffTime,this->datapool.flylink.tVehicle.yaw_cd*0.01f);
        // SysInfo_t
        additemDataToChart(QStringLiteral("CPU负载"),diffTime,this->datapool.flylink.tSysInfo.CPULoad);
        additemDataToChart(QStringLiteral("飞行航时"),diffTime,this->datapool.flylink.tSysInfo.flight_time_s);
        additemDataToChart(QStringLiteral("累计航时"),diffTime,this->datapool.flylink.tSysInfo.total_flight_time_s);
        additemDataToChart(QStringLiteral("飞行航程"),diffTime,this->datapool.flylink.tSysInfo.flight_dis_m);
        additemDataToChart(QStringLiteral("累计航程"),diffTime,this->datapool.flylink.tSysInfo.total_flight_dis_m);
        additemDataToChart(QStringLiteral("当前电压"),diffTime,this->datapool.flylink.tSysInfo.Battery_voltage_mv*0.001f);
        additemDataToChart(QStringLiteral("当前电流"),diffTime,this->datapool.flylink.tSysInfo.Battery_Current_CA*0.01f);
        additemDataToChart(QStringLiteral("油 门 值"),diffTime,this->datapool.flylink.tSysInfo.throttle);
        additemDataToChart(QStringLiteral("当前温度"),diffTime,this->datapool.flylink.tSysInfo.temperture*0.01f);
        additemDataToChart(QStringLiteral("离家距离"),diffTime,this->datapool.flylink.tSysInfo.home_dist_m);
        additemDataToChart(QStringLiteral("家 航 向"),diffTime,this->datapool.flylink.tSysInfo.home_bearing_cd*0.01f);
        additemDataToChart(QStringLiteral("目标距离"),diffTime,this->datapool.flylink.tSysInfo.wp_dist_m);
        additemDataToChart(QStringLiteral("高度差值"),diffTime,this->datapool.flylink.tSysInfo.alt_error);
        additemDataToChart(QStringLiteral("侧偏距离"),diffTime,this->datapool.flylink.tSysInfo.xtrack_error);

        additemDataToChart(QStringLiteral("Roll"      ),diffTime,this->datapool.flylink.tVehicle.roll_cd*0.01f);
        additemDataToChart(QStringLiteral("Pitch"     ),diffTime,this->datapool.flylink.tVehicle.pitch_cd*0.01f);
        additemDataToChart(QStringLiteral("Yaw"       ),diffTime,this->datapool.flylink.tVehicle.yaw_cd*0.01f);
        additemDataToChart(QStringLiteral("加速度X"      ),diffTime,this->datapool.flylink.tVehicle.acc_mpss[0]);
        additemDataToChart(QStringLiteral("加速度Y"      ),diffTime,this->datapool.flylink.tVehicle.acc_mpss[1]);
        additemDataToChart(QStringLiteral("加速度Z"      ),diffTime,this->datapool.flylink.tVehicle.acc_mpss[2]);
        additemDataToChart(QStringLiteral("角速度X"      ),diffTime,this->datapool.flylink.tVehicle.gyro_dps[0]);
        additemDataToChart(QStringLiteral("角速度Y"      ),diffTime,this->datapool.flylink.tVehicle.gyro_dps[1]);
        additemDataToChart(QStringLiteral("角速度Z"      ),diffTime,this->datapool.flylink.tVehicle.gyro_dps[2]);
        additemDataToChart(QStringLiteral("纬度"        ),diffTime,this->datapool.flylink.tVehicle.lat*1e-7);
        additemDataToChart(QStringLiteral("经度"        ),diffTime,this->datapool.flylink.tVehicle.lng*1e-7);
        additemDataToChart(QStringLiteral("海拔高度"      ),diffTime,this->datapool.flylink.tVehicle.alt_m);
        additemDataToChart(QStringLiteral("相对位置X"     ),diffTime,this->datapool.flylink.tVehicle.pos_m[0]);
        additemDataToChart(QStringLiteral("相对位置Y"     ),diffTime,this->datapool.flylink.tVehicle.pos_m[1]);
        additemDataToChart(QStringLiteral("相对位置Z"     ),diffTime,this->datapool.flylink.tVehicle.pos_m[2]);
        additemDataToChart(QStringLiteral("速度X"       ),diffTime,this->datapool.flylink.tVehicle.vel_cmps[0]*0.01f);
        additemDataToChart(QStringLiteral("速度Y"       ),diffTime,this->datapool.flylink.tVehicle.vel_cmps[1]*0.01f);
        additemDataToChart(QStringLiteral("速度Z"       ),diffTime,this->datapool.flylink.tVehicle.vel_cmps[2]*0.01f);

        // TargetInfo
        additemDataToChart(QStringLiteral("目标纬度" ),diffTime,this->datapool.flylink.tTarget.TargetLat*1e-7);
        additemDataToChart(QStringLiteral("目标经度" ),diffTime,this->datapool.flylink.tTarget.TargetLng*1e-7);
        additemDataToChart(QStringLiteral("目标海拔" ),diffTime,this->datapool.flylink.tTarget.TargetASL_m);
        additemDataToChart(QStringLiteral("目标高度" ),diffTime,this->datapool.flylink.tTarget.TargetAlt_m);
        additemDataToChart(QStringLiteral("期望高度" ),diffTime,this->datapool.flylink.tTarget.DesiredAlt_m);
        additemDataToChart(QStringLiteral("目标速度E" ),diffTime,this->datapool.flylink.tTarget.TargetVel_e_cmps*0.01f);
        additemDataToChart(QStringLiteral("目标速度N" ),diffTime,this->datapool.flylink.tTarget.TargetVel_n_cmps*0.01f);
        additemDataToChart(QStringLiteral("目标速度U" ),diffTime,this->datapool.flylink.tTarget.TargetVel_u_cmps*0.01f);
        additemDataToChart(QStringLiteral("目标Roll" ),diffTime,this->datapool.flylink.tTarget.NavRoll_cd*0.01f);
        additemDataToChart(QStringLiteral("目标Pitch" ),diffTime,this->datapool.flylink.tTarget.NavPitch_cd*0.01f);
        additemDataToChart(QStringLiteral("目标Yaw" ),diffTime,this->datapool.flylink.tTarget.NavYaw_cd*0.01f);
        additemDataToChart(QStringLiteral("目标加速度X" ),diffTime,this->datapool.flylink.tTarget.TargetAcc_mpss[0]*0.01f);
        additemDataToChart(QStringLiteral("目标加速度Y" ),diffTime,this->datapool.flylink.tTarget.TargetAcc_mpss[1]*0.01f);
        additemDataToChart(QStringLiteral("目标加速度Z" ),diffTime,this->datapool.flylink.tTarget.TargetAcc_mpss[2]*0.01f);
        additemDataToChart(QStringLiteral("目标角速度X" ),diffTime,this->datapool.flylink.tTarget.TargetGyro_dps[0]*0.01f);
        additemDataToChart(QStringLiteral("目标角速度Y" ),diffTime,this->datapool.flylink.tTarget.TargetGyro_dps[1]*0.01f);
        additemDataToChart(QStringLiteral("目标角速度Z" ),diffTime,this->datapool.flylink.tTarget.TargetGyro_dps[2]*0.01f);
        // IMU
        for(int i=0;i<3;i++){

            this->additemDataToChart(QStringLiteral("加计")+QString::number(i+1)+"-X" ,diffTime,this->datapool.flylink.tIMU[i].acc_mpss[0]);
            this->additemDataToChart(QStringLiteral("加计")+QString::number(i+1)+"-Y" ,diffTime,this->datapool.flylink.tIMU[i].acc_mpss[1]);
            this->additemDataToChart(QStringLiteral("加计")+QString::number(i+1)+"-Z" ,diffTime,this->datapool.flylink.tIMU[i].acc_mpss[2]);
            this->additemDataToChart(QStringLiteral("陀螺")+QString::number(i+1)+"-X" ,diffTime,this->datapool.flylink.tIMU[i].gyro_dps[0]);
            this->additemDataToChart(QStringLiteral("陀螺")+QString::number(i+1)+"-Y" ,diffTime,this->datapool.flylink.tIMU[i].gyro_dps[1]);
            this->additemDataToChart(QStringLiteral("陀螺")+QString::number(i+1)+"-Z" ,diffTime,this->datapool.flylink.tIMU[i].gyro_dps[2]);
            this->additemDataToChart(QStringLiteral("震动")+QString::number(i+1)+"-X" ,diffTime,this->datapool.flylink.tIMU[i].vibrations[0]);
            this->additemDataToChart(QStringLiteral("震动")+QString::number(i+1)+"-Y" ,diffTime,this->datapool.flylink.tIMU[i].vibrations[1]);
            this->additemDataToChart(QStringLiteral("震动")+QString::number(i+1)+"-Z" ,diffTime,this->datapool.flylink.tIMU[i].vibrations[2]);
            this->additemDataToChart(QStringLiteral("IMU温度")  +QString::number(i+1)    ,diffTime,this->datapool.flylink.tIMU[i].temperture*0.01f);
            this->additemDataToChart(QStringLiteral("过载数") +QString::number(i+1)   ,diffTime,this->datapool.flylink.tIMU[i].clips);
        }

        // 输入输出
        for(int i = 0; i< 16 ; i++){
            this->additemDataToChart(QStringLiteral("R C")+QString::number(i+1),diffTime,this->datapool.flylink.tRC_OUT.rc[i]);
        }

        for(int i = 0; i< 16 ; i++){
            this->additemDataToChart(QStringLiteral("OUT")+QString::number(i+1),diffTime,this->datapool.flylink.tRC_OUT.out[i]);
        }

        // 罗盘信息
        for(int  i = 0;i < 3 ;i++){
            additemDataToChart(QStringLiteral("Mag")+QString::number(i+1)+"-X",diffTime,this->datapool.flylink.tCompass[i].mag_mG[0]);
            additemDataToChart(QStringLiteral("Mag")+QString::number(i+1)+"-Y",diffTime,this->datapool.flylink.tCompass[i].mag_mG[1]);
            additemDataToChart(QStringLiteral("Mag")+QString::number(i+1)+"-Z",diffTime,this->datapool.flylink.tCompass[i].mag_mG[2]);
        }

        // 气压信息
        for(int  i = 0;i < 3 ;i++){
            additemDataToChart(QStringLiteral("当前气压")+QString::number(i+1),diffTime,this->datapool.flylink.tBaro[i].Press_Pa);
            additemDataToChart(QStringLiteral("气压温度")+QString::number(i+1),diffTime,this->datapool.flylink.tBaro[i].temperture*0.01f);
            additemDataToChart(QStringLiteral("大气密度系数")+QString::number(i+1),diffTime,this->datapool.flylink.tBaro[i].air_density_ratio);
        }
    }
}

void ChartWidget::setAllItemDisable()
{
    for(int i = 0; i < CHART_NUMBER;i++){
        int count = buttonGroup[i]->buttons().count();
        for(int j = 0;j < count;j++){
            buttonGroup[i]->buttons().at(j)->setChecked(false);
        }
    }
}


void ChartWidget::showEvent(QShowEvent *e)
{
    this->showTime = QDateTime::currentDateTime();
    this->timer->start(100);
    return QWidget::showEvent(e);
}

void ChartWidget::closeEvent(QCloseEvent *e)
{
    this->timer->stop();
    for(int i = 0;i < CHART_NUMBER;i++){
        Chart[i]->clearGraphics();
        setAllItemDisable();
    }
    return QWidget::closeEvent(e);
}

void ChartWidget::timeroutfunc()
{
    updateChartData();
    for(int i = 0;i < CHART_NUMBER;i++)
    {
        if(this->Chart[i] != nullptr){
            this->Chart[i]->updateData();
        }
    }
}

void ChartWidget::menuActionTargetSlot(QAction *action)
{
    if(action == nullptr ){
        return;
    }
    // 清除图表
    if(action == this->ActionClearAllGriph){
        setAllItemDisable();
    }
}
