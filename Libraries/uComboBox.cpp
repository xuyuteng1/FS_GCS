#include "uComboBox.h"

UComboBox::UComboBox(QComboBox *parent):
    QComboBox(parent)
{
    connect(this, &QComboBox::currentTextChanged,this,&UComboBox::handle_index_changed);
    this->setChanged(true);
}

void UComboBox::setNewCurrentIndex(int index)
{
    this->setCurrentIndex(index);
    this->setChanged(false);
}

void UComboBox::handle_index_changed(const QString & str)
{
    Q_UNUSED(str)
    this->setChanged(true);
}


