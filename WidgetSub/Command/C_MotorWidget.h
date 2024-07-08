#ifndef MotorUnlockWidget_H____
#define MotorUnlockWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>



class C_MotorUnlockWidget : public QWidget{
    Q_OBJECT
public:
    C_MotorUnlockWidget();

private:
    QGridLayout *widgetLayout = nullptr;
    QPushButton *motorUnlockAction = nullptr;               //电机解锁
    QPushButton *motorLockAction = nullptr;                 //电机锁定
    QPushButton *motorUnlockForceAction = nullptr;          //强制解锁
    QPushButton *motorLockForceAction = nullptr;            //强制解锁


private:
    void widgetInit();

    void connectSignalAndSlot();
    void set_motors(uint8_t mode);
private slots:
    void motorUnlockActionTargetSlot();
    void motorLockActionTargetSlot();
    void motorUnlockForceActionTargetSlot();
    void motorLockForceActionTargetSlot();

};

#endif // POWERDESIGNER_H
