#ifndef CFG_PREARM_CALI__
#define CFG_PREARM_CALI__

#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QProgressBar>

class G_CFG_PreCali:public QWidget
{
    Q_OBJECT
public:
    G_CFG_PreCali(QWidget *parent = nullptr);
    QGridLayout *getWidgetLayout() const;
private:
    QLabel          *titleLabel         = nullptr;
    QGridLayout*    widgetLayout    = nullptr;
    QLabel*         LB_AccTrim      = nullptr;
    QLabel*         LB_Baro         = nullptr;
    QLabel*         LB_Gyro         = nullptr;

    QPushButton*    PB_AccTrim      = nullptr;
    QPushButton*    PB_Baro         = nullptr;
    QPushButton*    PB_Gyro         = nullptr;

    QGroupBox*      Group_AccTrim   = nullptr;
    QGroupBox*      Group_Baro      = nullptr;
    QGroupBox*      Group_Gyro      = nullptr;

    QGridLayout*    LayoutAccTrim   = nullptr;
    QGridLayout*    LayoutBaro      = nullptr;
    QGridLayout*    LayoutGyro      = nullptr;


private:
    void connectSignalAndSlot();
    void widget_init();
};



#endif // CFG_PREARM_CALI__
