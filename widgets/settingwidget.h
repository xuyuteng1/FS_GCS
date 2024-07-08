#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QShowEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QTabBar>
#include <QStyle>
#include <QProxyStyle>
#include <QPainter>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QCheckBox>

enum Setting_StackWidget{
    SW_FCWidget = 1,
    SW_TTSWidget = 2,
    SW_LogWidget = 3,
    SW_ComWidget = 4,
};


/*配置界面标题栏*/
class SettingWidgetTitle : public QGroupBox{
    Q_OBJECT
public:
    SettingWidgetTitle(QString text);
    SettingWidgetTitle(QString iconPath,QString text);

private:
    QPushButton *quitButton = nullptr;                      /*退出按钮*/
    QPushButton *minSizeButton = nullptr;                   /*最小化按钮*/

    QLabel      *titleNameLabel = nullptr;                  /*窗口名称*/
    QLabel      *iconLabel = nullptr;                       /*图标显示*/

    QHBoxLayout *widgetLayout = nullptr;                    /*布局*/
    QHBoxLayout *btnLayout = nullptr;                       /*按键布局*/

private:
    void widgetInit();

signals:
    void closeButtonClickedSignal();
    void minSizeButtonClickedSignal();

};



/*通讯链路设置*/
class SettingWidgetCommun: public QWidget{
public:
    SettingWidgetCommun();


public:



private:
    QLabel *titleLabel = nullptr;

    QVBoxLayout *widgetLayout = nullptr;





private:
    void widgetInit();
};

/*日志系统设置*/
class SettingWidgetLogger : public QWidget{
public:
    SettingWidgetLogger();


public:



private:
    QLabel *titleLabel = nullptr;

    QVBoxLayout *widgetLayout = nullptr;


private:
    void widgetInit();
};

/*语音告警设置*/
class SettingWidgetTTS : public QWidget{
public:
    SettingWidgetTTS();


public:



private:
    QLabel *titleLabel = nullptr;

    QVBoxLayout *widgetLayout = nullptr;


private:
    void widgetInit();
};


class GroupCommbox : public QGroupBox{
    Q_OBJECT
public:
    GroupCommbox(QString name);
    GroupCommbox(QString name,QStringList str);

    void setComboBoxVal(QStringList str);
private:
    void widgetInit();

private:
    QLabel      *nameLabel = nullptr;
    QComboBox   *combobox = nullptr;
    QHBoxLayout *widgetLayout = nullptr;


public slots:


private slots:

signals:

};

class GroupEdit : public QGroupBox{
    Q_OBJECT
public:
    GroupEdit(QString name, QValidator *validator = nullptr);

public:


private:
    void widgetInit();

private:
    QLabel *nameLabel = nullptr;
    QLineEdit *valEdit = nullptr;
    QHBoxLayout *widgetLayout = nullptr;

};

/*飞行器设置*/
class SettingWidgetFlightControl : public QWidget{
public:
    SettingWidgetFlightControl();

private:
    void widgetInit();

};

/*控件栈*/
class SettingWidgetStack : public QStackedWidget{
    Q_OBJECT
public:
    SettingWidgetStack();

private:
    SettingWidgetFlightControl  *settingFCWidget = nullptr;                     /*飞行器参数设置*/
    SettingWidgetTTS            *settingTTSWidget = nullptr;                    /*语音告警参数设置*/
    SettingWidgetLogger         *settignLoggerWidget = nullptr;                 /*日志系统参数设置*/
    SettingWidgetCommun         *settingCommunWidget = nullptr;                 /*通讯链路参数设置*/


    QMap<Setting_StackWidget,QWidget *> widgetMap;

private:
    void widgetInit();

public slots:
    void stackWidgetSwitch(Setting_StackWidget);


};

class TabBarWidget : public QWidget{
    Q_OBJECT
public:
    TabBarWidget();

private:
    QPushButton *tabBarFCButton = nullptr;                          /*飞行器参数设置*/
    QPushButton *tabBarTTSButton = nullptr;                         /*语音告警参数设置*/
    QPushButton *tabBarLogButton = nullptr;                         /*日志系统参数设置*/
    QPushButton *tabBarComButton = nullptr;                         /*通讯链路参数设置*/

    QVBoxLayout *widgetLayout = nullptr;


private:
    void widgetInit();

private slots:
    void tabBarFCButtonClickedSlot();
    void tabBarTTSButtonClickedSlot();
    void tabBarLogButtonClickedSlot();
    void tabBarComButtonClickedSlot();
signals:
    void buttonClickedSignal(Setting_StackWidget sw);


};

/*配置界面信息栏*/
class SettingWidgetInfo : public QTabWidget{
Q_OBJECT
public:

public:
    SettingWidgetInfo();


private:
    SettingWidgetStack  *widgetStack = nullptr;
    TabBarWidget        *tabBarWidget = nullptr;

    QGridLayout         *widgetLayout = nullptr;

private:
    void widgetInit();



};

/*配置界面状态栏*/
class SettingWidgetStatus : public QGroupBox{
public:
    SettingWidgetStatus();
};


class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    SettingWidget();


private:
    QPoint dragPosition;

    SettingWidgetTitle *titleWidget = nullptr;                  /*配置界面标题栏*/
    SettingWidgetInfo  *infoWidget = nullptr;                   /*配置界面信息栏*/
    SettingWidgetStatus *statusWidget = nullptr;                /*配置界面状态栏*/

    QVBoxLayout *widgetLayout = nullptr;                        /*界面布局*/

private:
    void widgetInit();
    void signalAndSlot();

protected:
    void showEvent(QShowEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void settingWidgetShowSignal(bool);


};

#endif // SETTINGWIDGET_H
