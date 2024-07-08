#include "uSpinBox.h"

USpinBox::USpinBox(QSpinBox *parent):
    QSpinBox(parent)
{
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(handle_index_changed(int)));
//    connect(this, &QSpinBox::valueChanged,this,&USpinBox::handle_index_changed);
    this->setChanged(true);
}

void USpinBox::handle_index_changed(int str)
{
    Q_UNUSED(str)
    this->setChanged(true);
}


