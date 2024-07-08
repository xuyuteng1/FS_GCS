#ifndef C_LandWidget_H____
#define C_LandWidget_H____

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>



class C_LandWidget : public QWidget{
    Q_OBJECT
public:
    C_LandWidget();

private:
    QPushButton *rtlAction = nullptr;                       //返航模式
    QPushButton *smartRtlAction = nullptr;                  //智能返航
    QPushButton *landAction = nullptr;                      //降落模式



    QGridLayout *widgetLayout = nullptr;

private:
    void widgetInit();
    void connectSignalAndSlot();
    void set_mode(uint8_t mode_number);
private slots:
    void rtlActionTargetSlot();
    void smartRtlActionTargetSlot();
    void landActionTargetSlot();


};

#endif
