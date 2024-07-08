#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QResizeEvent>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QDateTime>
#include <QDebug>
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include "SIMCfg.h"
#include "PlaneConfig.h"
#include "general_config.h"
class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    TitleWidget();

    void setVersionStr(const QString &newVersionStr);

    void setAirIDStr(const QString &newAirIDStr);

    void setLngVal(double newLngVal);

    void setLatVal(double newLatVal);

    void setAlititudeVal(float newAlititudeVal);

    void setSateNumStr(int newSateNumStr);

    void setPositionPerStr(float newPositionPerStr);

    void setDateTime(const QDateTime &newDateTime);

    void setCommuncationStr(const QString &newCommuncationStr);

    void setfirmwareversionStr(const QString &newVersionStr);
private:
    void widgetInit();
    void selectButtonInit();
    void connectSignalAndSlot();
private:
    QLabel   *logoLabel = nullptr;

    QLabel   *versionIconLabel = nullptr;           //版本信息
    QLabel   *versionLabel = nullptr;
    QLabel   *firmwareversionLabel = nullptr;
    QGridLayout *versionLayout = nullptr;


    QLabel   *locationIconLabel = nullptr;
    QLabel   *locationLatLabel = nullptr;
    QLabel   *locationLngLabel = nullptr;
    QGridLayout *locationLayout = nullptr;


    QLabel   *altitudeIconLabel = nullptr;
    QLabel   *altitudeLabel = nullptr;
    QHBoxLayout *altitudeLayout = nullptr;


    QLabel   *sateNumIconLabel = nullptr;
    QLabel   *sateNumLabel = nullptr;
    QHBoxLayout *sateLayout = nullptr;

    QLabel   *positionPerIconLabel = nullptr;
    QLabel   *positionPerLabel = nullptr;
    QHBoxLayout *positionPerLayout = nullptr;


    QLabel   *dateTimeIconLabel = nullptr;
    QLabel   *dateTimeLabel = nullptr;
    QHBoxLayout *dateTimeLayout = nullptr;

    QLabel   *lb_GCS_Version = nullptr;
    QLabel   *lb_GCS_Version_Icon = nullptr;
    QHBoxLayout *HLayout_GCS_Version = nullptr;

    QLabel   *nowAirIconLabel = nullptr;
    QLabel   *nowAirIDLabel = nullptr;
    QHBoxLayout *nowAirIDLayout = nullptr;

    QPushButton *connectionButton = nullptr;
    QPushButton *closeButton = nullptr;
    QPushButton *minimizeButton = nullptr;
    QToolButton *selectButton = nullptr;

    QMenu          *selectMenu      = nullptr;
    QMenu          *GCSMenu         = nullptr;
    QMenu          *GeneralCfgMenu  = nullptr;
    QMenu          *CommonCfgMenu   = nullptr;
    QMenu          *CopterCfgMenu   = nullptr;
    QMenu          *PlaneCfgMenu    = nullptr;

    QAction *GCSCFGAction           = nullptr;
    QAction *CommonCfgAction        = nullptr;
    QAction *GeneralCfgAction       = nullptr;
    QAction *CopterCfgAction        = nullptr;
    QAction *PlaneCfgAction         = nullptr;

    /* FixWing parameters config action */
    QAction *Action_PlaneParamCFG   = nullptr;


    QAction *basicConfigAction = nullptr;                      //基础配置
    QAction *systemConfigAction = nullptr;                     //系统配置
    QAction *parameterConfigAciton = nullptr;                  //参数配置
    QAction *communicationConfigAction = nullptr;              //通讯接口配置
    QAction *loggerManagerAction = nullptr;                    //系统日志
    QAction *realTimeDataAction = nullptr;                     //系统实时数据
    QAction *panelDataAction = nullptr;                        //数据面板
    QAction *pluginManagerAction = nullptr;
    QAction *FCBoardInfo = nullptr;                            //飞控硬件信息
    QAction *SIMCFGAction = nullptr;                           //飞控仿真配置
#ifdef GCS_DEBUG_ENABLE
    QAction *FunDebugPort = nullptr;                           //调试界面入口
#endif
    QHBoxLayout *buttonGroupLayout = nullptr;
    QGridLayout *widgetLayout = nullptr;
    QString AirIconType = ":/img/icon/AirBlack.png";
protected:
    void resizeEvent(QResizeEvent *e);

private:
    QString     versionStr = QStringLiteral("N/A");
    QString     firmwareversionStr = QStringLiteral("N/A");
    QString     airIDStr = QStringLiteral("未连接");
    double      lngVal = -1;
    double      latVal = -1;
    float       alititudeVal = -1;
    int         sateNumStr = -1;
    float       positionPerStr = -1;
    QDateTime   dateTime = QDateTime::currentDateTime();

    QString     communcationStr = QStringLiteral("未连接");
    uint8_t     vehicletype = 255;

    /* widget */
    SIM_CFG*            WidgetSIMCfg = nullptr;
    PlaneConfigWidget*  widget_PlaneCFG = nullptr;
    WidgetGeneralConfig* widget_GeneralCFG = nullptr;
    void updatestate();
signals:
    void closeButtonPressedSignal();
    void minimizeButtonPressedSignal();
    void selectButtonPressedSignal();
    void connectionButtonPressedSignal();

    void basicConfigActionTriggeredSignal();
    void systemConfigActionTriggeredSignal();
    void parameterConfigAcitonTriggeredSignal();
    void communicationConfigActionTriggeredSignal();
    void loggerManagerActionTriggeredSignal();
    void realTimeDataActionTriggeredSignal();
    void panelDataActionTriggeredSignal();
    void pluginManagerActionTriggeredSignal();
    void FCBoardInfoActionTriggeredSignal();
    void FundbgPortActionTriggeredSignal();

public slots:

private slots:
    void handle_DMMM_event(int ev, int linkid);

    void handle_SIMCfgAction();
    void handle_Action_PlaneParamCFG();
    void handle_Action_GeneralCfg();
};

#endif // TITLEWIDGET_H
