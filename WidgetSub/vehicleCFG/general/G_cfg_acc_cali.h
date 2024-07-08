#ifndef CFG_ACC_CALI__
#define CFG_ACC_CALI__
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


class G_CFG_AccCali:public QWidget
{
    Q_OBJECT
public:
    G_CFG_AccCali(QWidget *parent = nullptr);
    QGridLayout *getWidgetLayout() const;
private:    
    QLabel          *titleLabel         = nullptr;
    QGridLayout*    widgetLayout        = nullptr;

    QLabel*         LB_CaliState        = nullptr;
    QLabel*         LB_3DCaliInfo       = nullptr;
    QLabel*         LB_SimpleCaliInfo   = nullptr;
    QGroupBox*      Group_3DCali        = nullptr;
    QGridLayout*    Layout3DCali        = nullptr;

    QGroupBox*      Group_SimpleCali    = nullptr;
    QGridLayout*    LayoutSimpleCali    = nullptr;
    QPushButton*    PB_3DCaliStart      = nullptr;
    QPushButton*    PB_SimpleCaliStart  = nullptr;
    QPushButton*    PB_3DCaliCancel     = nullptr;

    uint8_t         caliposition        = 0;

private:
    /* 通用函数 */
    void connectSignalAndSlot();
    void widget_init();

    /* 通用函数 */
    void update_cali_position(uint8_t pos,bool forceupdate = false);
    static QString getCaliPostionName(uint8_t pos);
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void start_or_continue_acc_cali(void);
    void cancel_acc_cali(void);
};




#endif // POWERDESIGNER_H
