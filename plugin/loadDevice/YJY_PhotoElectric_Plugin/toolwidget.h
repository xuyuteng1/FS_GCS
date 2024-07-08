#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QAction>
#include <QButtonGroup>
#include <QActionGroup>
#include <QSpacerItem>
class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    ToolWidget();

    QPushButton *switchViewButton = nullptr;                                    //切换视场
    QPushButton *overlayVideoButton = nullptr;                                  //画中画
    QPushButton *lockButton = nullptr;                                              //锁定
    QPushButton *swicthSensor = nullptr;                                            //切換传感器
    QPushButton          *target_Cross = nullptr;                                     //十字靶标
    QPushButton          *target_General = nullptr;                                 //通用靶标
    QPushButton          *target_Car = nullptr;                                        //车辆靶标
    QPushButton          *SerialPortOpen = nullptr;                                  //车辆靶标
    QPushButton          *SocketUDPOpen = nullptr;
    QButtonGroup         *targetButtonGroup = nullptr;

    QGridLayout *widgetLayout = nullptr;

private:
    void widgetInit();
    void connectSignalAndSlot();

public:
signals:
    void switchViewButtonPressedSignal();
    void overlayVideoButtonPressedSignal();
    void lockButtonPressedSignal();
    void swicthSensorPressedSignal();
    void target_CrossPressedSignal();
    void target_GeneralPressedSignal();
    void target_CarPressedSignal();
    void SerialPortOpenPressedSignal();
    void SocketUDPOpenPressedSignal();


public slots:
    void        lockedStatusChangedSlot(bool);


};

#endif // TOOLWIDGET_H
