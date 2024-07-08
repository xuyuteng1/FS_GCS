#include "grouplabel.h"

GroupLabel::GroupLabel( QString Name, QString unit,QString objectName)
{

    this->type = GroupLabel::GROUPLABELTYPE::NameValUnit;


    this->nameLabel = new QLabel(Name);
    this->valueLabel = new QLabel(" ");
    this->unitLabel = new QLabel(unit);

    this->nameLabel->setObjectName(objectName + "_Name");                             /*设置ObjectName,qss中使用 */
    this->valueLabel->setObjectName(objectName + "_Val");
    this->unitLabel->setObjectName(objectName + "_Unit");

    this->groupLayout = new QGridLayout();

    this->groupLayout->addWidget(this->nameLabel,0,0,1,2);
    this->groupLayout->addWidget(this->valueLabel,0,2,1,3);
    this->groupLayout->addWidget(this->unitLabel,0,5,1,1);

    this->groupLayout->setMargin(0);
    this->groupLayout->setSpacing(0);
    this->setLayout(this->groupLayout);

    this->nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);               //设置文字居中显示
    this->valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);            //设置文字居中显示
    this->unitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);             //设置文字居中显示


    this->setObjectName(objectName);

}

GroupLabel::GroupLabel(QString Name,QString objectName)
{

    this->type = GroupLabel::GROUPLABELTYPE::NameVal;

    this->nameLabel = new QLabel(Name);
    this->valueLabel = new QLabel;

    this->nameLabel->setObjectName(objectName + "_Name");            /*设置ObjectName,qss中使用 */
    this->valueLabel->setObjectName(objectName + "_Val");

    this->groupLayout = new QGridLayout();

    this->groupLayout->addWidget(this->nameLabel,0,0,1,2);
    this->groupLayout->addWidget(this->valueLabel,0,2,1,3);

    this->groupLayout->setMargin(0);
    this->groupLayout->setSpacing(0);
    this->setLayout(this->groupLayout);

    this->nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);             //设置文字居中显示
    this->valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);             //设置文字居中显示
    this->setObjectName(objectName);
}

QString GroupLabel::getUnitVal() const
{
    return unitVal;
}

void GroupLabel::setUnitVal(const QString &value)
{
    if(this->type == GroupLabel::GROUPLABELTYPE::NameValUnit){
        unitVal = value;
        this->unitLabel->setText(unitVal);
    }
}

QString GroupLabel::getValueVal() const
{
    return valueVal;
}

void GroupLabel::setValueVal(const QString &value)
{
    valueVal = value;
    this->valueLabel->setText(valueVal);
}




GroupLabelPixMap::GroupLabelPixMap(QString name, QString objectName, Qt::Orientation orientation, QSize pixmappSize)
{

    if(this->nameLabel == nullptr){
        this->nameLabel = new QLabel(name);
        this->nameLabel->setObjectName(objectName + "_Name");
    }

    if(this->pixMapLabel == nullptr){
        this->pixMapLabel = new LabelPixmap();
        this->pixMapLabel->setObjectName(objectName + "_Pix");
        this->pixMapLabel->setFixedSize(pixmappSize);
    }

    if(this->groupLayout == nullptr){
        this->groupLayout = new QGridLayout();
    }

    if(orientation == Qt::Vertical){
        this->groupLayout->addWidget(this->pixMapLabel,0,0,1,1);
        this->groupLayout->addWidget(this->nameLabel,1,0,1,1);
    }else{
        this->groupLayout->addWidget(this->nameLabel,0,0,1,1);
        this->groupLayout->addWidget(this->pixMapLabel,0,1,1,1);
    }

    this->groupLayout->setHorizontalSpacing(5);
    this->groupLayout->setMargin(5);
    this->groupLayout->setAlignment( Qt::AlignLeft | Qt::AlignVCenter);

    this->setLayout(this->groupLayout);
    this->setObjectName(objectName);

}

void GroupLabelPixMap::setStatus(int status)
{
    this->pixMapLabel->setStatus(status);
}


LabelPixmap::LabelPixmap()
{

}

int LabelPixmap::getStatus() const
{
    return statusVal;
}

void LabelPixmap::setStatus(int newStatusVal)
{
    if(newStatusVal != statusVal){
        statusVal = newStatusVal;
        style()->unpolish(this);
        style()->polish(this);
        this->update();
    }
}
