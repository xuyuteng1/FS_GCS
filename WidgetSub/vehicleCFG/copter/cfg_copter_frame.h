#ifndef CFG_COPTER_FRAME_
#define CFG_COPTER_FRAME_
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
class CFG_CopterFrame:public QObject
{
    Q_OBJECT
public:
    CFG_CopterFrame();

    QGridLayout *getWidgetLayout() const;

private:
    QGridLayout*    widgetLayout        = nullptr;
    QToolButton*    FrameSelect         = nullptr;

    QHBoxLayout*    widgetLayout_pb     = nullptr;
    QPushButton*    PB_download         = nullptr;
    QPushButton*    PB_upload           = nullptr;
    ConstrucationListView *construcationWidget = nullptr;
private:
    void connectSignalAndSlot();
    void widget_init();
    uint8_t frame = 0;
private slots:
    void handle_DMMM_event(int ev,int linkid = 0);
    void frameSetSlot(int id);

};

#endif // POWERDESIGNER_H
