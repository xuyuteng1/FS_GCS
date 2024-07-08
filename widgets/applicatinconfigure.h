#ifndef APPLICATINCONFIGURE_H
#define APPLICATINCONFIGURE_H

#include <QWidget>
#include <QListView>
#include <QSplitter>
#include <QGridLayout>
#include <widgetitle.h>
#include <QStringListModel>
#include <QMouseEvent>
#include <QListWidget>
#include <QScroller>
#include <QScrollBar>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <Windows.h>
#include <QDebug>
#include <QCheckBox>
#include <QButtonGroup>
#include "systemdata.h"
#include <QMessageBox>
#include <QDebug>
#include "wingdi.h"
#include "WinUser.h"
#include "PluginManager/pluginmanagerwidget.h"


class DisplayConfigWidget : public QGridLayout{
    Q_OBJECT
public:
    class CGammaRamp
    {
    protected:
        HMODULE hGDI32 = NULL;
        HMODULE hUser32 = NULL;
        HDC hScreenDC;
        typedef BOOL (WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);
        typedef BOOL (WINAPI *Type_GetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);
        typedef HDC (WINAPI *Type_getDC)(HDC hDC);
        typedef int (WINAPI *Type_releaseDC)(HDC hDC, LPVOID lpRamp);

        Type_GetDeviceGammaRamp pGetDeviceGammaRamp;
        Type_SetDeviceGammaRamp pSetDeviceGammaRamp;
        Type_getDC                              pGetDC;
        Type_releaseDC                       pReleaseDC;
    public:
        CGammaRamp();
        ~CGammaRamp();
        BOOL LoadWinLibrary();
        void FreeLibrary();
        BOOL LoadLibraryIfNeeded();
        BOOL SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
        BOOL GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
        HDC   getDC(HDC hDC);
        BOOL SetBrightness(HDC hDC, WORD wBrightness);
        BOOL getBrightness(HDC hDC, WORD wBrightness);
    };

public:
    DisplayConfigWidget(QWidget *parent = nullptr);
private:
    void widgetInit();
    void connectSignalAndSlot();
    void initialize();

private:
    void changedSystemGamma(int);

private:
    QLabel      *gammaValueLabel = nullptr;
    QSpinBox *gammaValueEdit = nullptr;
    QSlider     *gammaValueSlider = nullptr;

    QLabel      *modeLabel = nullptr;
    QCheckBox *powerSavingModel = nullptr;
    QCheckBox *brightLightModel = nullptr;
    QButtonGroup *modelButtonGroup = nullptr;

private:
    DlsplayData *data = SystemData::getDisplayData();

private slots:
    void gammaValueEditChangedSlot(QString);
    void gammaValueSliderChangedSlot(int);
    void buttonClickedSlot(QAbstractButton *);

};

#if 0
/*光电连接设置*/
class PhotoelectricConfigWidget : public QGridLayout{
    Q_OBJECT
public:
    PhotoelectricConfigWidget();

private:
    void widgetInit();
    void connectSignalAndSlot();
    void initialize();
private:
    QLabel            *linkMode = nullptr;                                 //连接方式 (rtsp_transport)tcp/udp/rtp
    QComboBox  *linkModeComboBox = nullptr;
    QLabel           *urlLabel = nullptr;
    QComboBox  *urlComboBox = nullptr;
    QLabel            *codecMode = nullptr;                             //编码方式(preset)  ultrafast、superfast、veryfast、faster、fast、medium、slow、slower、veryslow、placebo
    QComboBox  *codecModeComboBox = nullptr;
    QLabel            *bufferSize = nullptr;                             //缓冲区大小(buffersize)
    QLineEdit      *bufferSizeEdit = nullptr;
    QLabel            *maxDelay = nullptr;                             //最大延时微秒(maxdelay)
    QLineEdit       *maxDelayEdit = nullptr;
    QLabel            *cfrLabel = nullptr;                                //质量(cfr)
    QComboBox   *cfrComboBox = nullptr;
    QLabel            *stimeoutLabel = nullptr;                     //超时(stimeout)
    QLineEdit      *stimeoutEdit = nullptr;
    QLabel           *fpsLabel = nullptr;                               //fps
    QComboBox *fpsComboBox = nullptr;

    QPushButton *connectButton = nullptr;
    QPushButton *saveButton = nullptr;


private:
    PhotoelectricData *data = SystemData::getPhotoelectricData();

private slots:
    void linkModelChangedSlot(QString text);
    void connectButtonClickedSlot();
    void saveButtonClickedSlot();


signals:
    void photoelectricConnectSignal();

};
#endif
/*语音告警设置*/
class VoiceAlarmWidget : public QGridLayout{
public:
    VoiceAlarmWidget();
private:
    void widgetInit();
    void connectSignalAndSlot();

private:
    QLabel *enableLabel = nullptr;
    QCheckBox *enableCheckBox = nullptr;
    QCheckBox *disenableCheckBox = nullptr;
    QButtonGroup *enableButtonGroup = nullptr;

    QLabel *engineLabel = nullptr;
    QComboBox *engineComboBox = nullptr;

    QLabel *languageLabel = nullptr;
    QComboBox *languageComboBox = nullptr;

    QLabel        *ttsLevelLabel = nullptr;
    QCheckBox *infoLevelCheckBox = nullptr;
    QCheckBox *worningLevelCheckBox = nullptr;
    QCheckBox *errorLevelCheckBox = nullptr;

    QLabel         *levelSortLabel = nullptr;
    QCheckBox  *levelSortCheckBox = nullptr;
    QCheckBox  *orderCheckBox = nullptr;

    QLabel         *levelBreakLabel = nullptr;
    QCheckBox  *levelBreakComboBox = nullptr;

    QLabel      *volumeLabel = nullptr;
    QSpinBox *volumeSpinBox = nullptr;
    QSlider     *volumeSlider = nullptr;

    QLabel *rateLabel = nullptr;
    QSpinBox *rateSpinBox = nullptr;
    QSlider *rateSlider = nullptr;

    QLabel *pitchLabel = nullptr;
    QSpinBox *pitchSpinBox = nullptr;
    QSlider *pitchSlider = nullptr;

private:
    TextToSpeedData *data = SystemData::getTextToSpeedData();


};

/*语言设置*/
class LanguageWidget : public QGridLayout{
public:
    LanguageWidget();

private:
    void widgetInit();
    void connectSignalAndSlot();

private:
    QLabel *languageSwitchLabel = nullptr;
    QComboBox *languageSwitchC0mboBox = nullptr;

    QPushButton *selectButton = nullptr;


private:
    LanguageData *data = SystemData::getLanguageData();

};

/*地图源设置*/
class MapSourcesWidget : public QGridLayout{
    Q_OBJECT
public:
    MapSourcesWidget();
private:
    void widgetInit();
    void connectSignalAndSlot();
    void initialize();
private:
    QLabel *mapLabel = nullptr;
    QComboBox *mapNameComboBox = nullptr;
    QLabel *mapTypeLabel = nullptr;
    QComboBox *mapTypeComboBox = nullptr;

    QLabel *levelLabel = nullptr;
    QLabel *mapMinLevelLabel = nullptr;
    QSpinBox *mapMinLevelSpinBox = nullptr;
    QLabel *mapMaxLevelLabel = nullptr;
    QSpinBox *mapMaxLevelSpinBox = nullptr;
    QLabel *mapLevelLabel = nullptr;
    QSpinBox *mapLevelSpinBox = nullptr;

    QPushButton *connectButton = nullptr;
    QPushButton *saveButton = nullptr;

private:
    MapData *data = SystemData::getMapData();

    int lastMinVal = 0;
    int lastMaxVal = 21;
    int lastDefVal = 17;


private slots:
    void mapNameChangedSlot(QString name);
    void connectButtonClickedSlot();
    void saveButtonClickedSlot();
    void spinValueChangedSlot(int val);
signals:
    void mapSourcesChangedSignal();
};

/*HUD设置*/
class HUDConfigWidget : public QGridLayout{
public:
    HUDConfigWidget();

private:
    void widgetInit();
    void connectSignalAndSlot();
private:


};

/*快捷键设置*/
class ShortcutsConfigWidget : public QGridLayout{
public:
    ShortcutsConfigWidget();
private:
    void widgetInit();
    void connectSignalAndSlot();

private:


};

/*日志系统设置*/
class LogSystemConfigWidget : public QGridLayout{
public:
    LogSystemConfigWidget();
private:
    void widgetInit();
    void connectSignalAndSlot();
private:

};

/*转发与透传*/
class TransmitWidget : public QGridLayout{
public:
    TransmitWidget();
private:
    void widgetInit();
    void connectSignalAndSlot();
private:


};

/*存储与缓存清理*/
class StorageAndCachingClearWidget: public QGridLayout{
public:
    StorageAndCachingClearWidget();

private:
    void widgetInit();
    void connectSignalAndSlot();

};

/*系统重置*/
class SystemResetWidget : public QGridLayout{
public:
    SystemResetWidget();
private:
    void widgetInit();
    void connectSignalAndSlot();
};


class ApplicatinConfigure : public QWidget
{
    Q_OBJECT
public:
    class StringListModel : public QStringListModel{
    public:
        inline StringListModel(QObject *parent = nullptr) : QStringListModel(parent){};
        inline QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const{
            if(role == Qt::TextAlignmentRole){
                return Qt::AlignCenter;
            }else{
                return QStringListModel::data(index,role);
            }
        };
    };
public:
    ApplicatinConfigure(QWidget *parent = nullptr) ;

private:
    void initWidget();
    void connectSignalAndSlot();

    void listWidgetInit();
private:
    QListView *actionWidget = nullptr;
    QListWidget *listWidget = nullptr;
    QSplitter *splitterWidget = nullptr;
    QGridLayout *widgetLayout = nullptr;
    WidgetTitle *w_title = nullptr;


private:
    DisplayConfigWidget           *displayConfigWidget = nullptr;                  //显示设置
//    PhotoelectricConfigWidget *photoConfigWidget = nullptr;                     //光电吊舱参数设置
    VoiceAlarmWidget               *voiceAlarmConfigWidget = nullptr;           //语音告警参数设置
    LanguageWidget                   *languageConfigWidget = nullptr;               //语言家设置
    MapSourcesWidget              *mapSourcesConfigWidget = nullptr;         //地图源设置
    HUDConfigWidget                 *hudConfigWidget = nullptr;                        //HUD显示设置
    ShortcutsConfigWidget        *shortcutsConfigWidget = nullptr;              //系统快捷键设置
    LogSystemConfigWidget      *logSystemConfigWidget = nullptr;            //日志系统设置
    TransmitWidget                    *transmitWidget = nullptr;                          //转发与透传
    StorageAndCachingClearWidget *storageClearWidget = nullptr;           //内存清理
    SystemResetWidget              *systemResetWidget = nullptr;                  //系统还原

private:
    QMap<QString,QListWidgetItem *>widgetMap = {};
    StringListModel *listViewModel = nullptr;

protected:
//    /**========= 窗口支持鼠标拖动 =========**/
//    QPoint dragPosition;
//    void mousePressEvent(QMouseEvent *event)
//    {
//        if (event->button() == Qt::LeftButton) {
//           dragPosition = event->globalPos() - frameGeometry().topLeft();
//            event->accept();
//        }
//    };

//    void mouseMoveEvent(QMouseEvent *event)
//    {
//        if (event->buttons() & Qt::LeftButton) {
//            move(event->globalPos() - dragPosition);
//            event->accept();
//        }
//    };
public:
signals:
    void signalCloseEvent();

public slots:
    void addNewWidget(QString,QGridLayout*);
    void listWidgetItemPressedSlot(QModelIndex index);

public:
signals:
    void mapSourcesChangedSignal();                                     //地图源设置界面“选择”按钮
    void photoelectricConnectSignal();                                    //光电吊舱参数设置界面"连接"按钮

private slots:

};

#endif // APPLICATINCONFIGURE_H
