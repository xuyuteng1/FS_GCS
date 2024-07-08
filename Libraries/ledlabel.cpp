#include "ledlabel.h"



LedLabel::LedLabel(QWidget *parent, Qt::WindowFlags f)
{
    this->setParent(parent);
    this->setWindowFlags(f);
    if(this->timer == nullptr){
        this->timer = new QTimer;
        connect(this->timer,&QTimer::timeout,this,&LedLabel::timeroutFunc);
    }
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(28,28);
}

LedLabel::LedLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
{
    this->setText(text);
    this->setParent(parent);
    this->setWindowFlags(f);
    if(this->timer == nullptr){
        this->timer = new QTimer;
        connect(this->timer,&QTimer::timeout,this,&LedLabel::timeroutFunc);
    }
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(28,28);
}

LedLabel::~LedLabel()
{
    this->deleteLater();
}

void LedLabel::setStatus(uchar s)
{
    if((this->ledStatus & 0x0F) != (s & 0x0F)){
        switch (s) {
            case LedStatus::UNUSED:
                this->ledStatus = LedStatus::UNUSED;
                this->timer->stop();
            break;
            case LedStatus::LED_OPEN:
                this->ledStatus = LedStatus::LED_OPEN;
                this->timer->stop();
            break;
            case LedStatus::LED_CLOSE:
                this->ledStatus = LedStatus::LED_CLOSE;
                this->timer->stop();
            break;
            case 0x03:{
                this->timer->start(500);
                break;
            }default:{
                break;
            }

        }
        style()->unpolish(this);
        style()->polish(this);
        this->update();
    }
}

LedLabel::LedStatus LedLabel::getBlinkStatus() const
{
    return blinkStatus;
}

void LedLabel::setBlinkStatus(int newBlinkStatus)
{
    if(newBlinkStatus == 0){
        blinkStatus = LedStatus::UNUSED;
    }else if(newBlinkStatus == 1){
        blinkStatus = LedStatus::LED_CLOSE;
    }else{
        blinkStatus = LedStatus::LED_OPEN;
    }
}

void LedLabel::timeroutFunc()
{
    static bool flag = false;
    if(flag){
        this->ledStatus = this->getBlinkStatus();
        flag = false;
    }else{
        this->ledStatus = UNUSED;
        flag = true;
    }

    style()->unpolish(this);
    style()->polish(this);
}
