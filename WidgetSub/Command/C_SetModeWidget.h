#ifndef SetModeWidget_H____
#define SetModeWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QMessageBox>

#include <QtLocation>


class C_SetModeWidget : public QWidget{
    Q_OBJECT
public:
    C_SetModeWidget();

private:
    QPushButton *stabilizeAction = nullptr;                 //自稳模式
    QPushButton *altHoldAction = nullptr;                   //定高模式
    QPushButton *loiterAction = nullptr;                    //悬停模式
    QPushButton *posHoldAction = nullptr;                   //位置模式
    QPushButton *guidedAction = nullptr;                    //引导模式

    QPushButton *breakAction = nullptr;                     //刹车模式
    QPushButton *autoAction = nullptr;                      //任务模式
    QPushButton *circleAction = nullptr;                    //绕圈模式


    QGridLayout *widgetLayout = nullptr;



private:
    void widgetInit();
    void connectSignalAndSlot();

    void set_mode(uint8_t mode_number);

private slots:
    void stabilizeActionTargetSlot();
    void altHoldActionTargetSlot();
    void loiterActionTargetSlot();
    void posHoldActionTargetSlot();
    void guidedActionTargetSlot();

    void breakActionTargetSlot();
    void autoActionTargetSlot();
    void circleActionTargetSlot();

};
#endif
