#ifndef TakeoffMenuWidget_H____
#define TakeoffMenuWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>


class C_TakeoffMenuWidget : public QWidget{
    Q_OBJECT
public:
    C_TakeoffMenuWidget();

private:
    QLabel    *takeoffNameLabel = nullptr;
    QSpinBox *takeoffAltitudeEdit = nullptr;           //起飞高度输入框
    QPushButton *takeoffAffirmButton = nullptr;         //起飞确认按钮

    QDoubleSpinBox *rollSpinBox = nullptr;
    QPushButton   *setRollButton = nullptr;

    QDoubleSpinBox *setAltitudeSpinBox = nullptr;
    QPushButton   *setAltitudeButton = nullptr;

    QGridLayout *widgetLayout = nullptr;


private:
    void widgetInit();
    void connectSignalAndSlot();


private slots:
    void takeoffAffirmButtonPressedSlot();
    void setRollButtonPressedSlot();
    void setAlititudeButtonPressedSlot();

};

#endif
