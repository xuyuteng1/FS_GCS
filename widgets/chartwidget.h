#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include "widgetitle.h"
#include <QShowEvent>
#include <QCloseEvent>
#include <QDateTime>
#include "DMMM.h"
#include "uchartview.h"

#define CHART_NUMBER 2
class ChartWidget : public QWidget
{
    Q_OBJECT;
public:
    ChartWidget(QWidget *parent = nullptr);
private:
    void widgetInit();
    void connectSignalAndSlot();

    void additemToChart(QString name ,QListWidget * listwidget,bool enable1 = false,bool enable2 = false);
    void additemDataToChart(QString name ,double x,double y);

    void chartListInit();
    void updateChartData();

    void setAllItemDisable();

public:
signals:
    void signalCloseEvent();

private slots:
    void timeroutfunc();
    void menuActionTargetSlot(QAction *action);
private :


    QButtonGroup *          buttonGroup[CHART_NUMBER]      = {};
    uChartView *            Chart[CHART_NUMBER]            = {};

    QMap<QString,int>       nameMap             = {};

    QToolBox*               ItemBox             = nullptr;
    QGridLayout *           itemLayout          = nullptr;
    QGridLayout *           ChartLayout         = nullptr;
    QGridLayout *           widgetLayout        = nullptr;

    QListWidget *           ListVehicleInfo     = nullptr;
    QListWidget *           ListSysInfo         = nullptr;
    QListWidget *           ListIMU             = nullptr;
    QListWidget *           ListRCSVR           = nullptr;
    QListWidget *           ListCompass         = nullptr;
    QListWidget *           ListBaro            = nullptr;
    QListWidget *           ListTarget          = nullptr;

    WidgetTitle *           w_title             = nullptr;
    QTimer *                timer               = nullptr;
    QDateTime               showTime;
    Q_DMMM::DataPool_t datapool;

    QMenu *                 rightMenu           = nullptr;
    QAction *               ActionClearAllGriph = nullptr;

protected:
    /**========= 窗口支持鼠标拖动 =========**/
    QPoint dragPosition;
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton) {
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }else if(event->button() == Qt::RightButton){
            if(this->rightMenu != nullptr){
                this->rightMenu->exec(QCursor::pos());
            }
        }
        return QWidget::mousePressEvent(event);

    };

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
        return QWidget::mouseMoveEvent(event);
    };
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);
};

#endif // CHARTWIDGET_H
