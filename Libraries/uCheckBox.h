#ifndef UCHECK_BOX_H_
#define UCHECK_BOX_H_
#include <QCheckBox>
#include <QTimer>
#include <QStyle>
#include <QDebug>
#include <QMap>

class UCheckBox : public QCheckBox{
public:
    Q_OBJECT
    Q_PROPERTY(bool changed READ IsChanged WRITE setChanged)

public:
    UCheckBox(QCheckBox *parent=nullptr);
    ~UCheckBox(){}

public:

    void setNewChecked(bool);
    bool IsChanged(){return is_changed;}
    void setChanged(bool s)
    {
        is_changed = s;
        style()->unpolish(this);
        style()->polish(this);
        this->update();
    }
private:
    bool is_changed = false;
private slots:
    void handle_changed();
public slots:



};

#endif // LEDLABEL_H
