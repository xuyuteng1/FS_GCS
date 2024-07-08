#ifndef UCOMBO_BOX_H_
#define UCOMBO_BOX_H_
#include <QComboBox>
#include <QTimer>
#include <QStyle>
#include <QDebug>
#include <QMap>

class UComboBox : public QComboBox{
public:
    Q_OBJECT
    Q_PROPERTY(bool changed READ IsChanged WRITE setChanged)

public:
    UComboBox(QComboBox *parent=nullptr);
    ~UComboBox(){}
public:

    void setNewCurrentIndex(int index);
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
    void handle_index_changed(const QString & str);
public slots:



};

#endif // LEDLABEL_H
