#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QAbstractVideoSurface>
#include "videocodec.h"
#include <QMouseEvent>
#include "statuswidget.h"
#include "toolwidget.h"
#include "handlewidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include "DMMM.h"
class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget();
private:
    QVideoWidget *videoWidget = nullptr;
    StatusWidget  *statusWidget = nullptr;
    ToolWidget      *toolWidget = nullptr;
    VideoCodec     *player = nullptr;
    HandleWidget *handleWidget = nullptr;
    QGridLayout *widgetLayout = nullptr;
private:
    void widgetInit();
    void connectSignalAndSlot();

private slots:
    void switchViewButtonPressedSlot();                                  //视场切换
    void overlayVideoButtonPressedSlot();                               //画中画
    void lockButtonPressedSlot();                                             //锁定
    void swicthSensorPressedSlot();                                          //切换传感器
    void target_CrossPressedSlot();                                           //十字靶
    void target_GeneralPressedSlot();                                        //通用靶
    void target_CarPressedSlot();                                               //移动靶
    //通信测试
    void Slot_SerialPortOpenPressedSlot();
    void Slot_SocketUDPOpenPressedSlot();

    void handleProcessValueChangedSlot(bool status,int x,int y);
    void videoWidgetMousePressedSlot(int x,int y);                  //波门坐标移动指令
};
#endif // WIDGET_H
