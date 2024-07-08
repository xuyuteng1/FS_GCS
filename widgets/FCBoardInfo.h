#ifndef FC_BOARD_INFO_HH_
#define FC_BOARD_INFO_HH_

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

class FCBoardINFO : public QWidget
{
    Q_OBJECT
public:
    FCBoardINFO(QWidget *parent = nullptr);
    enum {
        FCBoardManufactor_KWYWAY_KYFly_FC_V100      = 10031,
        FCBoardManufactor_KWYWAY_KYFly_GPS_V100     = 10032,
        FCBoardManufactor_XYFly_FC_V100             = 10001,
        FCBoardManufactor_XYFly_FC_V200             = 10002,
        FCBoardManufactor_XYFly_GPS_V100            = 10003,
        FCBoardManufactor_XYFly_FC_V300             = 10004,
        FCBoardManufactor_XYFly_FC_V310             = 10005,
        FCBoardManufactor_XYFly_FC_V330E_J30J       = 10006,
        FCBoardManufactor_XYFly_FT_INS_V100         = 10007,
        FCBoardManufactor_XYFly_FT_CTRL_V100        = 10008,
        FCBoardManufactor_CUAV_X7                   = 1010,
        FCBoardManufactor_CUAVv5                    = 50,
        FCBoardManufactor_CUAVNora                  = 1009,
    }FCBoardManufactorModel;
    static QString getFCBoardModelString(uint32_t id);
    static QString getFCBoardSimPleString(uint32_t id);
    void setData(const Q_DMMM::DataPool_t &newData);
signals:
    void signalCloseEvent();
public slots:
private:
    WidgetTitle*    w_title         = nullptr;
    QGridLayout*    widgetLayout    = nullptr;
    QGridLayout*    mainLayout      = nullptr;
    QLabel*         UDID[2]         ;
    QLabel*         BoardID[2]      ;
    QLabel*         BoardSN[2]      ;
    QLabel*         FW_Version[2]   ;
    QLabel*         Link_Version[2] ;
    QLabel*         FlightDis[2]    ;
    QLabel*         FlightTime[2]   ;
    QLabel*         MavID[2]   ;
    UComboBox*      MavIDComBox = nullptr;
#ifdef GCS_DEBUG_ENABLE
    QPushButton*    PB_saveinfo = nullptr;
#endif
private:
    qint64 last_req_ms;//
    bool   is_getinfo;//
private:
    void widgetInit();
private slots:
    void handle_DMMM_event(int ev, int linkid);
    void slot_MavIdChanged(int index);
#ifdef GCS_DEBUG_ENABLE
    void SaveBoardInfo();
#endif
public:
    void req_boardinfo();
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
