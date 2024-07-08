#ifndef P_LandWidget_H____
#define P_LandWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>



class P_LandWidget : public QWidget{
    Q_OBJECT
public:
    P_LandWidget();

private:
    QPushButton *goAround_Action = nullptr;                  //复飞
    QPushButton *landAction = nullptr;                      //降落模式

    QDoubleSpinBox* goAroundAlt = nullptr;
    QLabel      * goAroundAlt_name = nullptr;
    QGridLayout *widgetLayout = nullptr;

private:
    void widgetInit();
    void connectSignalAndSlot();
private slots:
    void landActionTargetSlot();
    void goAroundActionTargetSlot();

};

#endif
