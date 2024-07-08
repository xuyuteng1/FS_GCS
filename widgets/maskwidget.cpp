#include "maskwidget.h"

MaskWidget::MaskWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::SplashScreen|Qt::FramelessWindowHint);
}
