#include "C_TakeoffWidget.h"
#include "DMMM.h"
#include <QMessageBox>
C_TakeoffMenuWidget::C_TakeoffMenuWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void C_TakeoffMenuWidget::widgetInit()
{
    if(this->takeoffNameLabel == nullptr){
        this->takeoffNameLabel = new QLabel(QStringLiteral("起飞高度"));
        this->takeoffNameLabel->setObjectName("WidgetCMD");
    }

    if(this->takeoffAltitudeEdit == nullptr){
        this->takeoffAltitudeEdit = new QSpinBox();
        this->takeoffAltitudeEdit->setMinimum(0);
        this->takeoffAltitudeEdit->setMaximum(1000);
        this->takeoffAltitudeEdit->setValue(10);
        this->takeoffAltitudeEdit->setObjectName("WidgetCMD");
    }

    if(this->takeoffAffirmButton == nullptr){
        this->takeoffAffirmButton = new QPushButton(QStringLiteral("立即起飞"));
//        this->takeoffAffirmButton->setIcon(QIcon(":/img/icon/takeoffIcon.png"));
        this->takeoffAffirmButton->setToolTip(QStringLiteral("立即起飞"));
//        this->takeoffAffirmButton->setIconSize(QSize(32,32));
        this->takeoffAffirmButton->setObjectName("WidgetCMD_Action");

    }

    if(this->rollSpinBox == nullptr){
        this->rollSpinBox = new QDoubleSpinBox;
        this->rollSpinBox->setDecimals(2);
        this->rollSpinBox->setMinimum(0);
        this->rollSpinBox->setMaximum(360);
        this->rollSpinBox->setObjectName("WidgetCMD");
    }
    if(this->setRollButton == nullptr){
        this->setRollButton = new QPushButton(QStringLiteral("更改航向"));
        this->setRollButton->setIcon(QIcon(":/img/icon/setRoll.png"));
        this->setRollButton->setToolTip(QStringLiteral("更改航向"));
        this->setRollButton->setIconSize(QSize(32,32));
        this->setRollButton->setObjectName("WidgetCMD_Action");
    }

    if(this->setAltitudeSpinBox == nullptr){
        this->setAltitudeSpinBox = new QDoubleSpinBox;
        this->setAltitudeSpinBox->setDecimals(1);
        this->setAltitudeSpinBox->setMinimum(-100);
        this->setAltitudeSpinBox->setMaximum(6000);
        this->setAltitudeSpinBox->setObjectName("WidgetCMD");
    }
    if(this->setAltitudeButton == nullptr){
        this->setAltitudeButton = new QPushButton(QStringLiteral("更改高度"));
        this->setAltitudeButton->setIcon(QIcon(":/img/icon/setAlt.png"));
        this->setAltitudeButton->setToolTip(QStringLiteral("更改高度"));
        this->setAltitudeButton->setIconSize(QSize(32,32));
        this->setAltitudeButton->setObjectName("WidgetCMD_Action");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,0,4,1);
    this->widgetLayout->addWidget(this->takeoffNameLabel,1,1,1,1);
    this->widgetLayout->addWidget(this->takeoffAltitudeEdit,1,2,1,1);
    this->widgetLayout->addWidget(this->takeoffAffirmButton,2,1,1,2);
    this->widgetLayout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Fixed ),0,3,4,1);

    this->setLayout(this->widgetLayout);

}

void C_TakeoffMenuWidget::connectSignalAndSlot()
{
    connect(this->takeoffAffirmButton,&QPushButton::pressed,this,&C_TakeoffMenuWidget::takeoffAffirmButtonPressedSlot);
    connect(this->setRollButton,&QPushButton::pressed,this,&C_TakeoffMenuWidget::setRollButtonPressedSlot);
    connect(this->setAltitudeButton,&QPushButton::pressed,this,&C_TakeoffMenuWidget::setAlititudeButtonPressedSlot);
}

void C_TakeoffMenuWidget::takeoffAffirmButtonPressedSlot()
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

    msgBox.setWindowTitle(QStringLiteral("确认起飞"));
    msgBox.setText(QStringLiteral("确认是否满足起飞条件:"));
    msgBox.setInformativeText(QStringLiteral("    1. 飞行器螺旋桨附近无遮挡\t\r\n"
                                                                              "    2. 飞行高度范围内空域无遮挡\t\r\n"
                                                                              "    "));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setWindowFlag(Qt::WindowStaysOnTopHint);
    int ret = msgBox.exec();

    switch (ret) {
    case QMessageBox::Yes:{
            float alt = this->takeoffAltitudeEdit->value();
            FlyLink* link = nullptr;
            link = Qt::DMMM()->getFlyLink_main();
            if(link!=nullptr){
                link->do_takeoff(alt);
            }
        break;
    }
    default:{
        break;
    }
    }
}

void C_TakeoffMenuWidget::setRollButtonPressedSlot()
{
    float heading = this->rollSpinBox->value();
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_set_heading(heading);
    }
}

void C_TakeoffMenuWidget::setAlititudeButtonPressedSlot()
{
    float alt = this->setAltitudeSpinBox->value();
    FlyLink* link = nullptr;
    link = Qt::DMMM()->getFlyLink_main();
    if(link!=nullptr){
        link->do_set_alt_m(alt);
    }
}
