/**=================================================================**
 * @brief       : Parameter Config Widget Template
 * @Email       : 476623721@qq.com
 * @VersionNotes:
 * 2023-02-23     Jerry.xl     the first version
 **==================================================================**/
#include "G_cfg_template.h"
#include "DMMM.h"
#include <qmath.h>

G_CFG_Template::G_CFG_Template(QWidget *parent, QString title):
    QWidget(parent),
    _widgetTitle(title)
{

}

QGridLayout *G_CFG_Template::getWidgetLayout() const
{
    return widgetLayout;
}

void G_CFG_Template::ParamCFGInit_DoubleSpinBox(QLabel *&label, UDoubleSpinBox *&box, QString name, QString Tooltip, double range_min, double range_max, double single_step, int prec)
{
    if( label == nullptr){
        label = new QLabel(name);
        label->setObjectName(QString::fromUtf8("widgetNameLabel"));
        label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        label->setToolTip(Tooltip);
    }

    if( box == nullptr){
        box = new UDoubleSpinBox();
        box->setRange(range_min,range_max);
        box->setValue(0);
        box->setAlignment(Qt::AlignCenter);
        box->setSingleStep(single_step);
        box->setDecimals(prec);
        box->setToolTip(Tooltip);
    }
}

void G_CFG_Template::showEvent(QShowEvent *event)
{
    update_value();
    QWidget::showEvent(event);
}

void G_CFG_Template::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);
    // 处理事件
    switch(ev){
    case Q_DMMM::DMMM_GCSEvent_GetCommonParameter:
    {
        update_value();
    }break;
    case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
    case Q_DMMM::DMMM_GCSEvent_NewVehicleType:
    {
        update_value(true);
    }break;
        default:break;
    }
}

void G_CFG_Template::f_WidgetInit()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout(this);
        widgetLayout->setObjectName(QString::fromUtf8("widgetLayout"));
    }

    if(this->titleLabel == nullptr){
        this->titleLabel = new QLabel(_widgetTitle);
        this->titleLabel->setAlignment(Qt::AlignCenter);
        this->titleLabel->setObjectName("CfgWIdgetTitle");
    }

    if(PB_download == nullptr){
        PB_download = new QPushButton(QStringLiteral("查询"));
        PB_download->setObjectName(QStringLiteral("WidgetCMD_Action"));

    }
    if(PB_upload == nullptr){
        PB_upload = new QPushButton(QStringLiteral("设置"));
        PB_upload->setObjectName(QStringLiteral("WidgetCMD_Action"));
    }


    if(widgetLayout_pb == nullptr){
        widgetLayout_pb = new QHBoxLayout();
        widgetLayout_pb->setObjectName(QString::fromUtf8("widgetLayout"));
        widgetLayout_pb->addStretch(5);
        widgetLayout_pb->addWidget(PB_download,1);
        widgetLayout_pb->addWidget(PB_upload,1);
        widgetLayout_pb->addStretch(5);
    }
    WidgetInit();
}

void G_CFG_Template::f_connectSignalAndSlot()
{
    connect(Qt::DMMM()    , &Q_DMMM::DMMM_Event,   this,&G_CFG_Template::handle_DMMM_event);
    connect(PB_download   , &QPushButton::released,this,[=]{update_value(true);});
    connect(PB_upload     , &QPushButton::released,this,[=]{Upload_Parameters();});
    connectSignalAndSlot();
}
