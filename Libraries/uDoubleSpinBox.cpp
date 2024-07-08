#include "uDoubleSpinBox.h"

UDoubleSpinBox::UDoubleSpinBox(QDoubleSpinBox *parent):
    QDoubleSpinBox(parent)
{
    connect(this, SIGNAL(valueChanged(double)), this, SLOT(handle_index_changed(double)));
    this->setChanged(true);
}

void UDoubleSpinBox::SetNewValue(double val)
{
    this->setValue(val);
    this->setChanged(false);
}



void UDoubleSpinBox::handle_index_changed(double str)
{
    Q_UNUSED(str)
    this->setChanged(true);
}


