#include "handlewidget.h"

HandleWidget::HandleWidget()
{
    widgetInit();
    connectSignalAndSlot();
}

void HandleWidget::widgetInit()
{

    if(this->gaugeprocess == nullptr){
        this->gaugeprocess = new GaugeProgressBar();
    }


    if(this->fineTuningButton == nullptr){
        this->fineTuningButton = new QPushButton();
        this->fineTuningButton->setToolTip(QStringLiteral("微调"));
        this->fineTuningButton->setIcon(QIcon(":/img/fineTuning.png"));
        this->fineTuningButton->setObjectName("fineTuningButton");
        this->fineTuningButton->setMaximumWidth(30);
        this->fineTuningButton->setCheckable(true);

    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addWidget(this->gaugeprocess,0,0,8,8);
    this->widgetLayout->addWidget(this->fineTuningButton,0,7,1,1);

    this->setLayout(this->widgetLayout);
}

void HandleWidget::connectSignalAndSlot()
{
    connect(this->gaugeprocess,&GaugeProgressBar::valueChangedSignal,this,&HandleWidget::handleProcessValueChangedSlot);
}

void HandleWidget::handleProcessValueChangedSlot(int x, int y)
{
    emit this->handleProcessValueChangedSignal(this->fineTuningButton->isChecked(),x,-y);
}
