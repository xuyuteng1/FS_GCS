#ifndef FC_BOARD_INFO_H_
#define FC_BOARD_INFO_H_

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QFile>
#include "DMMM.h"
#include <QApplication>
#include "widgetitle.h"
#include <QMouseEvent>
#include "uComboBox.h"
#include <QSpinBox>
class FunDebug : public QWidget
{
    Q_OBJECT
public:
    FunDebug(QWidget *parent = nullptr);

signals:

public slots:
private:
    WidgetTitle*    w_title         = nullptr;
    QGridLayout*    widgetLayout    = nullptr;
    QGridLayout*    mainLayout      = nullptr;
    QPushButton*    Pb_Attack_mode  = nullptr;
    QPushButton*    Pb_flashbootloader  = nullptr;
    QPushButton*    Pb_reboot       = nullptr;
    QPushButton*    Pb_factory      = nullptr;
    QPushButton*    Pb_WriteSN      = nullptr;
    QSpinBox*       SN_High         = nullptr;
    QSpinBox*       SN_Low         = nullptr;
//    QLabel*         UDID[2]         ;
//    QLabel*         BoardID[2]      ;
//    QLabel*         FW_Version[2]   ;
//    QLabel*         Link_Version[2] ;
//    QLabel*         FlightDis[2]    ;
//    QLabel*         FlightTime[2]   ;
//    QLabel*         MavID[2]   ;
//    UComboBox*      MavIDComBox = nullptr;
private:
    void widgetInit();
private slots:
    void handle_DMMM_event(int ev, int linkid);
    void Slot_ModeAttack();
    void Slot_Flashbootloader();

    void Slot_Reboot();
    void Slot_Factory();
    void Slot_WriteSN();
protected:
    /**========= 窗口支持鼠标拖动 =========**/
    QPoint dragPosition;
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
           dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    };

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    };
};

#endif // FCBoardINFO_H
