#include "cfg_copter_frame.h"
#include "DMMM.h"
#include <qmath.h>
CFG_CopterFrame::CFG_CopterFrame()
{
    widget_init();
    connectSignalAndSlot();
}


QGridLayout *CFG_CopterFrame::getWidgetLayout() const
{
    return widgetLayout;
}

void CFG_CopterFrame::connectSignalAndSlot()
{
    connect(PB_upload   , &QPushButton::released,this,[=]{this->construcationWidget->close();FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){link->set_vehicle_frame(frame);}});
    connect(PB_download   , &QPushButton::released,this,[=]{this->construcationWidget->close();FlyLink* link = Qt::DMMM()->getFlyLink_main();if(link){frameSetSlot(link->get_vehicle_frame());}});
    connect(Qt::DMMM(),&Q_DMMM::DMMM_Event,this,&CFG_CopterFrame::handle_DMMM_event);
    connect(this->FrameSelect,&QPushButton::released,this,[=]{this->construcationWidget->showNormal();});
    connect(this->construcationWidget,&ConstrucationListView::construcationChangedSignal,this,&CFG_CopterFrame::frameSetSlot);
}

void CFG_CopterFrame::widget_init()
{
    if(widgetLayout == nullptr){
        widgetLayout = new QGridLayout();
    }

    if(this->construcationWidget == nullptr){
        this->construcationWidget = new ConstrucationListView();
    }
    if(FrameSelect == nullptr){
        FrameSelect = new QToolButton();
        FrameSelect->setIconSize(QSize(200,200));
        FrameSelect->setCheckable(true);
        FrameSelect->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        this->FrameSelect->setObjectName(QStringLiteral("CFGToolButtonState"));
        FrameSelect->setText(QStringLiteral("未定义"));
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
    }

    widgetLayout->addWidget(FrameSelect,    0 ,9 ,2 ,1);

    widgetLayout_pb->addStretch(5);
    widgetLayout_pb->addWidget(PB_download,1);
    widgetLayout_pb->addWidget(PB_upload,1);
    widgetLayout_pb->addStretch(5);
    widgetLayout->addLayout(widgetLayout_pb,3,0,1,19);

    widgetLayout->setRowMinimumHeight(0,220);
    widgetLayout->setRowMinimumHeight(3,30);
    frameSetSlot(0);
}

void CFG_CopterFrame::handle_DMMM_event(int ev, int linkid)
{
    Q_UNUSED(linkid);

    // 处理事件
    switch(ev){
        case Q_DMMM::DMMM_GCSEvent_frameChanged:
        case Q_DMMM::DMMM_GCSEvent_Protocol_Actived:
        case Q_DMMM::DMMM_GCSEvent_Protocol_lost:
        {
            FlyLink* link = Qt::DMMM()->getFlyLink_main();
            if(link != nullptr){
                frameSetSlot(link->get_vehicle_frame());
            }
        }break;
        default:break;
    }
}

void CFG_CopterFrame::frameSetSlot(int id)
{
    this->FrameSelect->setIcon(QIcon(this->construcationWidget->getConstrucationIconPath().find(id).value()));
    this->FrameSelect->setText(this->construcationWidget->getConstrucationName().find(id).value());
    frame = id;
}
