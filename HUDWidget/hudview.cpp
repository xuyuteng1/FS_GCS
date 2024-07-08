#include "hudview.h"

HUDView::HUDView()
{
    initHUDView();
}

void HUDView::initHUDView()
{
    this->setBackgroundBrush(this->background_sky);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setAlignment(Qt::AlignCenter);
}
