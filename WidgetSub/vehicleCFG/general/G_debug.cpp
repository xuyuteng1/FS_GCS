#include "G_debug.h"
#include "DMMM.h"
#include <qmath.h>
G_CFG_Debug::G_CFG_Debug(QWidget *parent):
  QWidget(parent)
{
    widget_init();
    connectSignalAndSlot();
    this->setObjectName("systemWidget");
    this->setAttribute(Qt::WA_QuitOnClose,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("通用参数"));
    QFile file(QString(":/style/widgetStyle.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void G_CFG_Debug::set_paramters()
{
    FlyLink::CommonParam_t parameters{};
    FlyLink *link = Qt::DMMM()->getFlyLink_main();
    parameters.param_index = -1;
    // name
    char *msg;
    QByteArray namebuf = this->ParametersStr->text().toLatin1();
    msg = namebuf.data();
    memcpy(parameters.param_name,msg,qMin((int)strlen(msg),16));
    parameters.param_name[16] = 0;
    parameters.param_value = this->ParametersValue->value();    /*<  Onboard parameter value*/
    qDebug()<<parameters.param_value;
    if(link != nullptr){
        link->set_CommonParameter(parameters);
    }
}

void G_CFG_Debug::req_paramters()
{

    FlyLink::CommonParamReq_t req{};
    FlyLink *link = Qt::DMMM()->getFlyLink_main();
    req.param_index = -1;
    // name
    char *msg;
    QByteArray namebuf = this->ParametersStr->text().toLatin1();
    msg = namebuf.data();
    memcpy(req.param_name,msg,qMin((int)strlen(msg),16));
    req.param_name[16] = 0;
    if(link != nullptr){
        link->send_ReqCommonParameter(req);
    }
}


QGridLayout *G_CFG_Debug::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_Debug::connectSignalAndSlot()
{
    connect(this->ParametersSet,&QPushButton::released,this,&G_CFG_Debug::set_paramters);
    connect(this->ParametersGet,&QPushButton::released,this,&G_CFG_Debug::req_paramters);
    connect(this->FrameIDSet,&QPushButton::released,this,[=]{FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->set_vehicle_frame(this->FrameID->value());}});
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&G_CFG_Debug::handle_DMMM_event);
}

void G_CFG_Debug::widget_init()
{
    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(QStringLiteral("调试参数"));
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }
    if(this->ParametersStrName == nullptr){
        this->ParametersStrName = new QLabel(QStringLiteral("参数名称"));
        this->ParametersStrName->setObjectName(QStringLiteral("SystemInfoWidgetLabel"));
        this->ParametersStrName->setAlignment(Qt::AlignCenter);
    }
    if(this->ParametersValueName == nullptr){
        this->ParametersValueName = new QLabel(QStringLiteral("参数值"));
        this->ParametersValueName->setObjectName(QStringLiteral("SystemInfoWidgetLabel"));
        this->ParametersValueName->setAlignment(Qt::AlignCenter);
    }


    if(this->ParametersStr == nullptr){
        this->ParametersStr = new QLineEdit(QStringLiteral("......请输入参数名称......"));
        this->ParametersStr->setObjectName(QStringLiteral("widgetLineEdit"));
        this->ParametersStr->setAlignment(Qt::AlignCenter);
        this->ParametersStr->setMinimumWidth(200);
    }

    if(ParametersSet == nullptr){
        ParametersSet = new QPushButton(QStringLiteral("设置参数"));
        this->ParametersSet->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(ParametersGet == nullptr){
        ParametersGet = new QPushButton(QStringLiteral("读取参数"));
        this->ParametersGet->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }
    if(FrameIDSet == nullptr){
        FrameIDSet = new QPushButton(QStringLiteral("设置构型"));
        this->FrameIDSet->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }


    if(this->ParametersValue == nullptr){
        this->ParametersValue = new UDoubleSpinBox();
        this->ParametersValue->setObjectName(QStringLiteral("widgetDoubleSpinBox"));
        this->ParametersValue->setAlignment(Qt::AlignCenter);
        this->ParametersValue->setMinimum(-66666666);
        this->ParametersValue->setMaximum(66666666);
        this->ParametersValue->setMinimumWidth(200);

    }

    widgetLayout = new QGridLayout();

    if(this->FrameID == nullptr){
        this->FrameID = new QSpinBox();
        this->FrameID->setObjectName(QStringLiteral("widgetSpinBox"));
        this->FrameID->setAlignment(Qt::AlignCenter);
        this->FrameID->setMinimum(0);
        this->FrameID->setMaximum(255);
    }

    widgetLayout->addWidget( titleLabel,0,0,1,20);
    widgetLayout->addWidget( ParametersStrName,1,9,1,1,Qt::AlignCenter);
    widgetLayout->addWidget( ParametersValueName,1,10,1,1,Qt::AlignCenter);

    widgetLayout->addWidget( ParametersStr,2,9,1,1,Qt::AlignCenter);
    widgetLayout->addWidget( ParametersValue,2,10,1,1,Qt::AlignCenter);


    widgetLayout->addWidget( ParametersSet,3,9,1,1,Qt::AlignCenter);
    widgetLayout->addWidget( ParametersGet,3,10,1,1,Qt::AlignCenter);

    widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Expanding), 4, 0, 1, 20);
    this->widgetLayout->setContentsMargins(10,20,10,20);
//    widgetLayout->addWidget( FrameID,3,0,1,1,Qt::AlignCenter);
//    widgetLayout->addWidget( FrameIDSet,3,1,1,1,Qt::AlignCenter);

    this->widgetLayout->setVerticalSpacing(15);
    this->setLayout(widgetLayout);

}

void G_CFG_Debug::handle_DMMM_event(int ev, int linkid, QVariant var)
{
    Q_UNUSED(linkid);
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_GetCommonParameter:
    {
        FlyLink::CommonParam_t parm = var.value<FlyLink::CommonParam_t>();
        ParametersStr->setText(parm.param_name);
        ParametersValue->setValue(parm.param_value);
        ParametersValue->setChanged(false);
    }
        break;
    default:
        break;
    }
}
