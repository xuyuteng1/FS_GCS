#include "uCheckBox.h"

UCheckBox::UCheckBox(QCheckBox *parent):
    QCheckBox(parent)
{
    connect(this, &QCheckBox::stateChanged,this,&UCheckBox::handle_changed);
    this->setChanged(true);
}

void UCheckBox::setNewChecked(bool val)
{
    this->setChecked(val);
    this->setChanged(false);
}

void UCheckBox::handle_changed()
{
    this->setChanged(true);
}

