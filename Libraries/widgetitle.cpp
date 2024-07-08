#include "widgetitle.h"


WidgetTitle::WidgetTitle(const QPixmap &pix_icon, const QString &title_name, QWidget *parent):
    QWidget(parent)
{
    _pix_icon = pix_icon;
    _title_name = title_name;
    widget_init();
    this->setObjectName("widgetitle");
    connect(this->pb_Close,&QPushButton::released,this,[=]{emit signalCloseEvent();});
    this->setMaximumHeight(40);
}

void WidgetTitle::widget_init()
{
    if(lb_ICON == nullptr){
        lb_ICON = new QLabel();
        lb_ICON->setFixedHeight(30);
        this->lb_ICON->setAlignment(Qt::AlignCenter);
        _pix_icon = _pix_icon.scaledToHeight(22,Qt::SmoothTransformation);
        this->lb_ICON->setPixmap(_pix_icon);
        this->lb_ICON->setObjectName("widgetitle");
    }

    if(lb_titleName == nullptr){
        lb_titleName = new QLabel(_title_name);
        this->lb_titleName->setObjectName("widgetitle");
    }

    if(pb_Close == nullptr){
        pb_Close = new QPushButton();
        pb_Close->setFixedSize(25,25);
        pb_Close->setIcon(QIcon(":/img/png/widgetclose.png"));
        pb_Close->setToolTip(QStringLiteral("关闭窗口"));
        pb_Close->setIconSize(QSize(20,20));
        this->pb_Close->setObjectName("widgetitle");
    }

    if(hBox == nullptr){
        hBox = new QHBoxLayout();
    }

    hBox->addWidget(lb_ICON);
    hBox->addWidget(lb_titleName);
    hBox->addSpacerItem(new QSpacerItem(20,20,QSizePolicy::Expanding,QSizePolicy::Minimum));
    hBox->addWidget(pb_Close);
    hBox->setContentsMargins(10,5,10,1);
    hBox->setSpacing(10);

    this->setLayout(hBox);
    this->setAttribute(Qt::WA_StyledBackground,true);
}
