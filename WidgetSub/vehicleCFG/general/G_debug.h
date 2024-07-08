#ifndef option_debug_h___
#define option_debug_h___
#include <QWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include "construcationwidget.h"
#include <QToolButton>
#include "UDoubleSpinBox.h"

class G_CFG_Debug:public QWidget
{
    Q_OBJECT
public:
    G_CFG_Debug(QWidget *parent = nullptr);
    QGridLayout *getWidgetLayout() const;
private:
    QLabel          *titleLabel         = nullptr;

private slots:
    void set_paramters();
    void req_paramters();
private:
    /* 设置高度 */
    QGridLayout*    widgetLayout = nullptr;
    QLabel*         ParametersIDName = nullptr;
    QSpinBox*       ParametersID = nullptr;

    QLabel*         ParametersStrName = nullptr;
    QLineEdit*      ParametersStr = nullptr;

    QLabel*         ParametersValueName = nullptr;
    UDoubleSpinBox* ParametersValue = nullptr;
    QPushButton*    ParametersSet = nullptr;
    QPushButton*    ParametersGet = nullptr;

    QSpinBox*       FrameID = nullptr;
    QPushButton*    FrameIDSet = nullptr;

    void connectSignalAndSlot();
    void widget_init();

private slots:
    void handle_DMMM_event(int ev,int linkid , QVariant var);

};



#endif // POWERDESIGNER_H
