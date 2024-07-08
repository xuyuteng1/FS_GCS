#ifndef WIDGET_TITLE_H
#define WIDGET_TITLE_H
#include <QLabel>
#include <QTimer>
#include <QStyle>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

class WidgetTitle : public QWidget{
    Q_OBJECT
public:
    WidgetTitle(const QPixmap &pix_icon,const QString&title_name,QWidget*parent = nullptr);

signals:
    void signalCloseEvent();
private:
    QHBoxLayout*    hBox            = nullptr;
    QLabel*         lb_ICON         = nullptr;
    QLabel*         lb_titleName    = nullptr;
    QPushButton*    pb_Close        = nullptr;

    QPixmap         _pix_icon;
    QString         _title_name;
/*============Function============*/
private:
    void widget_init();


};

#endif
