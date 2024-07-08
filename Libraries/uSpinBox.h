#ifndef USPIN_BOX_H_
#define USPIN_BOX_H_
#include <QComboBox>
#include <QTimer>
#include <QStyle>
#include <QDebug>
#include <QMap>
#include <QSpinBox>

class USpinBox : public QSpinBox{
public:
    Q_OBJECT
    Q_PROPERTY(bool changed READ IsChanged WRITE setChanged)

public:
    USpinBox(QSpinBox *parent=nullptr);
    ~USpinBox(){}
public:


    bool IsChanged(){return index_is_changed;}
    void setChanged(bool s)
    {
        index_is_changed = s;
        style()->unpolish(this);
        style()->polish(this);
        this->update();
    }
private:
    bool index_is_changed = false;
private slots:
    void handle_index_changed(int  str);
public slots:



};

#endif // LEDLABEL_H
