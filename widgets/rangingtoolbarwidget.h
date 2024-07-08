#ifndef RANGINGTOOLBARWIDGET_H
#define RANGINGTOOLBARWIDGET_H
#include <QToolButton>
#include <QGridLayout>
#include <QActionGroup>
#include <QDebug>
#include <QPushButton>
#include <QToolBar>
class RangingToolBarWidget : public QToolBar
{
    Q_OBJECT
public:
    RangingToolBarWidget(QWidget *parent = nullptr);

    void setWidgetVisable(bool status);
private:
    QAction *rangingButton = nullptr;           //测距
    QAction *areaButton = nullptr;              //面积测量
    QAction *pointButton = nullptr;             //点信息
    QAction *perspectiveFollowButton = nullptr;             //航点跟随
    QAction *seekAirButton = nullptr;
    QAction *clearAirPathButton = nullptr;      //清除航迹
    QAction *widgetLayout = nullptr;

private:
    void widgetInit();
    void connectSignalAndSlot();

private slots:
    void rangingButtonPressedSlot();
    void areaButtonPressedSlot();
    void pointButtonPressedSlot();
    void perspectiveFollowButtonPresssedSlot();
    void seekAirButtonPressedSlot();
    void clearAirPathButtonPressedSlot();

signals:
    void rangingButtonPressedSligal(bool);
    void areaButtonPressedSignal(bool);
    void pointButtonPressedSignal(bool);
    void perspectiveFollowButtonPresssedSignal(bool);
    void seekAirButtonPressedSignal();
    void clearAirPathButtonPressedSignal();


};

#endif // RANGINGTOOLBARWIDGET_H
