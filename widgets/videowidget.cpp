#include "videowidget.h"

VideoWidget::VideoWidget()
{
    initWidget();
}

void VideoWidget::addWidget(QWidget *wid)
{
    if(wid != nullptr && this->widgetLayout != nullptr){
        this->widgetLayout->addWidget(wid,0,0,10,10);
    }
}

void VideoWidget::initWidget()
{
    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->setMargin(0);
    this->widgetLayout->setSpacing(0);

    this->setLayout( this->widgetLayout );
}
