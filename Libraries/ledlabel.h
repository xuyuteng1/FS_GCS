#ifndef LEDLABEL_H
#define LEDLABEL_H
#include <QLabel>
#include <QTimer>
#include <QStyle>
#include <QDebug>


class LedLabel : public QLabel{
public:
    Q_OBJECT
    Q_ENUMS(LedStatus)
    Q_PROPERTY(LedStatus status READ getStatus WRITE setStatus)

public:
    LedLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    LedLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    ~LedLabel();
public:
    enum LedStatus{
        UNUSED = 0,
        LED_CLOSE = 1,
        LED_OPEN = 2,
    };
    inline LedStatus getStatus(){return ledStatus;}
    void setStatus(uchar s);
    LedStatus getBlinkStatus() const;
    void setBlinkStatus(int);

private:
    LedStatus blinkStatus = LedStatus::UNUSED;          /*闪烁状态*/
    LedStatus ledStatus = LedStatus::UNUSED;
    QTimer *timer = nullptr;


private slots:
    void timeroutFunc();

public slots:



};

#endif // LEDLABEL_H
