#include "hudwidget.h"

HUDWidget::HUDWidget()
{
    widgetInit();
}

void HUDWidget::widgetInit()
{
    if(this->hudScane == nullptr){
        this->hudScane  = new QGraphicsScene(this);

    }

    if(this->hudView == nullptr){
        this->hudView = new HUDView();
        this->hudView->setScene(this->hudScane);

    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
        this->widgetLayout->addWidget(this->hudView,0,0,1,1);
        this->widgetLayout->setSpacing(0);
        this->widgetLayout->setMargin(0);
        this->setLayout(this->widgetLayout);
    }

    this->hudScane->setSceneRect(-this->width() / 2,-this->height() / 2,this->width() - 1,this->height() - 1);
    if(this->scanePitch == nullptr){
        this->scanePitch = new HUDViewItem_ScanePitch(QRect(- this->hudScane->sceneRect().width() * 0.3f / 2,- this->hudScane->sceneRect().height() * 0.65f / 2,this->hudScane->width() * 0.3f,this->hudScane->height() * 0.65f));
    }

    if(this->scaneHeading == nullptr){
        this->scaneHeading = new HUDViewItem_Heading(QRect(- (this->hudScane->width() >  this->hudScane->height() ? (this->hudScane->height() * 0.98): (this->hudScane->width() * 0.98),this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98 / 2: this->hudScane->width() * 0.98  / 2),
                                                           -(this->hudScane->width() >  this->hudScane->height() ? (this->hudScane->height() * 0.98): (this->hudScane->width() * 0.98),this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98 / 2: this->hudScane->width() * 0.98  / 2),
                                                           this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98: this->hudScane->width() * 0.98,
                                                           this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98: this->hudScane->width() * 0.98 ));
    }

    if(this->scaneBakGround == nullptr){
        this->scaneBakGround = new HUDViewItem_BackGround(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }

    if(this->scaneBakGroundImg == nullptr){
        this->scaneBakGroundImg = new HUDViewItem_BackGroundImg(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }


    if(this->airIcon == nullptr){
        this->airIcon = new HUDViewItem_AirIcon(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }
    if(this->airInfo == nullptr){
        this->airInfo = new HUDViewItem_AirInfo(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }

//    this->hudScane->addItem(this->scaneBakGroundImg);
    this->hudScane->addItem(this->scaneBakGround);
    this->hudScane->addItem(this->scanePitch);
    this->hudScane->addItem(this->scaneHeading);
    this->hudScane->addItem(this->airIcon);
    this->hudScane->addItem(this->airInfo);


}

void HUDWidget::resizeEvent(QResizeEvent *event)
{
    if(this->hudScane != nullptr){
        this->hudScane->setSceneRect(-this->width() / 2,-this->height() / 2,this->width() - 1,this->height() - 1);
    }
    if(this->scanePitch != nullptr){
        this->scanePitch->resize(QRect(- this->hudScane->sceneRect().width() * 0.3f / 2,- this->hudScane->sceneRect().height() * 0.65f / 2,this->hudScane->width() * 0.3f,this->hudScane->height() * 0.65f));
    }
    if(this->scaneHeading != nullptr){
        this->scaneHeading->resize(QRect(- (this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98: this->hudScane->width() * 0.98,this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98 / 2: this->hudScane->width() * 0.98  / 2),
                                         -(this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98: this->hudScane->width() * 0.98,this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98 / 2: this->hudScane->width() * 0.98  / 2),
                                         this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98: this->hudScane->width() * 0.98,
                                         this->hudScane->width() >  this->hudScane->height() ? this->hudScane->height() * 0.98: this->hudScane->width() * 0.98 ));
    }

    if(this->scaneBakGround != nullptr){
        this->scaneBakGround->resize(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }
    if(this->scaneBakGroundImg != nullptr){
        this->scaneBakGroundImg->resize(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }

    if(this->airIcon != nullptr){
        this->airIcon->resize(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }

    if(this->airInfo != nullptr){
        this->airInfo->resize(QRect(- this->hudScane->sceneRect().width() / 2,- this->hudScane->sceneRect().height()  / 2,this->hudScane->width() ,this->hudScane->height() ));
    }
}

void HUDWidget::updateHUDData(float altitude, float targetAltitude, float roll, float targetRoll, float heading, float targetHeading, float pitch, float targetPitch, float speed, float targetSpeed)
{

    this->scaneHeading->setHeading(heading);
    this->scanePitch->setPitch(pitch);
    this->scaneBakGround->valueChanged(roll,pitch);
    this->airInfo->valueChanged(roll,pitch,heading,roll,pitch,altitude,speed,targetRoll,targetPitch,targetAltitude,targetSpeed);
}

