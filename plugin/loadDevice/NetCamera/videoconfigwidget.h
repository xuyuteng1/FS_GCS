#ifndef VIDEOCONFIGWIDGET_H
#define VIDEOCONFIGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

#include "videoparameter.h"

class VideoConfigWidget : public QWidget
{
    Q_OBJECT
public:
    VideoConfigWidget();

private:
    void widgetInit();
    void connectSignalAndSlot();
    void initialize();
private:
    QLabel           *linkMode = nullptr;                                 //连接方式 (rtsp_transport)tcp/udp/rtp
    QComboBox  *linkModeComboBox = nullptr;
    QLabel           *urlLabel = nullptr;
    QComboBox  *urlComboBox = nullptr;
    QLabel            *codecMode = nullptr;                             //编码方式(preset)  ultrafast、superfast、veryfast、faster、fast、medium、slow、slower、veryslow、placebo
    QComboBox  *codecModeComboBox = nullptr;
    QLabel            *bufferSize = nullptr;                             //缓冲区大小(buffersize)
    QLineEdit      *bufferSizeEdit = nullptr;
    QLabel            *maxDelay = nullptr;                             //最大延时微秒(maxdelay)
    QLineEdit       *maxDelayEdit = nullptr;
    QLabel            *cfrLabel = nullptr;                                //质量(cfr)
    QComboBox   *cfrComboBox = nullptr;
    QLabel            *stimeoutLabel = nullptr;                     //超时(stimeout)
    QLineEdit      *stimeoutEdit = nullptr;
    QLabel           *fpsLabel = nullptr;                               //fps
    QComboBox *fpsComboBox = nullptr;

    QPushButton *connectButton = nullptr;
    QPushButton *saveButton = nullptr;

    QGridLayout *widgetLayout = nullptr;

private:
    VideoParameter *data = nullptr;

private slots:
    void linkModelChangedSlot(QString text);
    void connectButtonClickedSlot();
    void saveButtonClickedSlot();


signals:
    void photoelectricConnectSignal();

};

#endif // VIDEOCONFIGWIDGET_H
