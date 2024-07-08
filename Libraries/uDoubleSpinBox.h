#ifndef UDOUBLE_SPIN_BOX_H_
#define UDOUBLE_SPIN_BOX_H_
#include <QComboBox>
#include <QTimer>
#include <QStyle>
#include <QDebug>
#include <QMap>
#include <QDoubleSpinBox>

class UDoubleSpinBox : public QDoubleSpinBox{
public:
    Q_OBJECT
    Q_PROPERTY(bool changed READ IsChanged WRITE setChanged)

public:
    UDoubleSpinBox(QDoubleSpinBox *parent=nullptr);
    ~UDoubleSpinBox(){}
public:


    bool IsChanged(){return index_is_changed;}
    void setChanged(bool s)
    {
        index_is_changed = s;
        style()->unpolish(this);
        style()->polish(this);
        this->update();
    }
    void SetNewValue(double val);
private:
    bool index_is_changed = false;
private slots:
    void handle_index_changed(double str);
public slots:



};

#endif // LEDLABEL_H
