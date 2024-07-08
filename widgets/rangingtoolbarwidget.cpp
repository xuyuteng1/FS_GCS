#include "rangingtoolbarwidget.h"

RangingToolBarWidget::RangingToolBarWidget(QWidget *parent) : QToolBar(parent)
{
    widgetInit();
    connectSignalAndSlot();
}

void RangingToolBarWidget::setWidgetVisable(bool status)
{
    this->rangingButton->setChecked(false);
    this->areaButton->setChecked(false);
    this->pointButton->setChecked(false);
    this->perspectiveFollowButton->setChecked(false);
    this->seekAirButton->setChecked(false);
    this->clearAirPathButton->setChecked(false);

    this->setVisible(status);
}

void RangingToolBarWidget::widgetInit()
{

    if(this->rangingButton == nullptr){
        this->rangingButton = new QAction();
        this->rangingButton->setIcon(QIcon(":/img/icon/ranging.png"));
        this->rangingButton->setObjectName("RangingToolBar");
        this->rangingButton->setToolTip(QStringLiteral("测距"));
        this->rangingButton->setText(QStringLiteral("距离"));
        this->rangingButton->setCheckable(true);

    }
    if(this->areaButton == nullptr){
        this->areaButton = new QAction();
        this->areaButton->setIcon(QIcon(":/img/icon/area.png"));
        this->areaButton->setObjectName("RangingToolBar");
        this->areaButton->setToolTip(QStringLiteral("测量面积"));
        this->areaButton->setText(QStringLiteral("面积"));
        this->areaButton->setCheckable(true);
    }
    if(this->pointButton == nullptr){
        this->pointButton = new QAction();
        this->pointButton->setIcon(QIcon(":/img/icon/point.png"));
        this->pointButton->setObjectName("RangingToolBar");
        this->pointButton->setToolTip(QStringLiteral("测量经纬度"));
        this->pointButton->setText(QStringLiteral("位置"));
        this->pointButton->setCheckable(true);
    }

    if(this->perspectiveFollowButton == nullptr){
        this->perspectiveFollowButton = new QAction();
        this->perspectiveFollowButton->setIcon(QIcon(":/img/icon/perspectiveFollow.png"));
        this->perspectiveFollowButton->setObjectName("RangingToolBar");
        this->perspectiveFollowButton->setToolTip(QStringLiteral("飞行器视角跟随"));
        this->perspectiveFollowButton->setText(QStringLiteral("跟随"));
        this->perspectiveFollowButton->setCheckable(true);
    }

    if(this->seekAirButton == nullptr){
        this->seekAirButton = new QAction();
        this->seekAirButton->setIcon(QIcon(":/img/icon/seekAir.png"));
        this->seekAirButton->setObjectName("RangingToolBar");
        this->seekAirButton->setToolTip(QStringLiteral("飞行器居中"));
        this->seekAirButton->setText(QStringLiteral("居中"));
        this->seekAirButton->setCheckable(false);
    }

    if(this->clearAirPathButton == nullptr){
        this->clearAirPathButton = new QAction();
        this->clearAirPathButton->setIcon(QIcon(":/img/icon/clear.png"));
        this->clearAirPathButton->setObjectName("RangingToolBar");
        this->clearAirPathButton->setToolTip(QStringLiteral("清除航迹"));
        this->clearAirPathButton->setText(QStringLiteral("航迹"));
        this->clearAirPathButton->setCheckable(false);
    }

    this->addAction(this->rangingButton);
    this->addAction(this->areaButton);
    this->addAction(this->pointButton);
    this->addAction(this->perspectiveFollowButton);
    this->addAction(this->seekAirButton);
    this->addAction(this->clearAirPathButton);

}

void RangingToolBarWidget::connectSignalAndSlot()
{
    connect(this->rangingButton,&QAction::triggered,this,&RangingToolBarWidget::rangingButtonPressedSlot);
    connect(this->areaButton,&QAction::triggered,this,&RangingToolBarWidget::areaButtonPressedSlot);
    connect(this->pointButton,&QAction::triggered,this,&RangingToolBarWidget::pointButtonPressedSlot);
    connect(this->perspectiveFollowButton,&QAction::triggered,this,&RangingToolBarWidget::perspectiveFollowButtonPresssedSlot);
    connect(this->seekAirButton,&QAction::triggered,this,&RangingToolBarWidget::seekAirButtonPressedSlot);
    connect(this->clearAirPathButton,&QAction::triggered,this,&RangingToolBarWidget::clearAirPathButtonPressedSlot);
}

void RangingToolBarWidget::rangingButtonPressedSlot()
{
    qDebug()<<this->rangingButton->isChecked();
    if(!this->rangingButton->isChecked()){
        this->areaButton->setChecked(false);
        this->pointButton->setChecked(false);
    }else{
        this->rangingButton->setChecked(true);
    }

    emit rangingButtonPressedSligal(this->rangingButton->isChecked());
}

void RangingToolBarWidget::areaButtonPressedSlot()
{
    if(!this->areaButton->isChecked()){
        this->rangingButton->setChecked(false);
        this->pointButton->setChecked(false);
    }else{
        this->areaButton->setChecked(true);
    }

    emit areaButtonPressedSignal(this->areaButton->isChecked());
}

void RangingToolBarWidget::pointButtonPressedSlot()
{
    if(!this->pointButton->isChecked()){
        this->areaButton->setChecked(false);
        this->rangingButton->setChecked(false);
    }else{
        this->pointButton->setChecked(true);
    }

    emit pointButtonPressedSignal(this->pointButton->isChecked());
}

void RangingToolBarWidget::perspectiveFollowButtonPresssedSlot()
{
    if(this->perspectiveFollowButton->isChecked()){
        this->perspectiveFollowButton->setChecked(true);
    }
    emit perspectiveFollowButtonPresssedSignal(this->perspectiveFollowButton->isChecked());
}

void RangingToolBarWidget::seekAirButtonPressedSlot()
{
    emit seekAirButtonPressedSignal();
}

void RangingToolBarWidget::clearAirPathButtonPressedSlot()
{
    emit clearAirPathButtonPressedSignal();
}
