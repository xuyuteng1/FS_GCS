#ifndef COMMUNICATIONSWIDGET_H
#define COMMUNICATIONSWIDGET_H

#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QSerialPortInfo>
#include <QPushButton>
#include <QLineEdit>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QMap>
#include <QTableView>
#include <QHeaderView>
#include "FlyLink.h"
#include <QItemDelegate>
#include <QListView>
#include <QLineEdit>
#include <QPainter>
#include <QMouseEvent>
#include <QModelIndex>
#include "widgetitle.h"
#include <QMessageBox>
#include "systemdata.h"
class BasicConfigWidgetButtonDelegate : public QItemDelegate{
public:
    BasicConfigWidgetButtonDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //相应item的编辑事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);


};


class BasicConfigWidgetDeviceItemDelegate : public QItemDelegate{
public:
    BasicConfigWidgetDeviceItemDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,const QModelIndex &index) const override;

private:

protected:

};



class BasicConfigWidgetTableModel : public QAbstractItemModel{
    Q_OBJECT
    Q_ENUMS(BasicDataRoutes);

public:
    BasicConfigWidgetTableModel();

    typedef struct{
        int     linkID;
        bool    isOpen;
        int     Device;             //串口,tcp或udp
        QString address;            //通讯地址串口号或IP
        QString channel;            //通讯端口或波特率
        int     res;                //通讯建立返回值
    }BasicModelData;


    enum BasicDataRoutes{
        BasicData_linkID = Qt::UserRole + 1,
        BasicData_Device,
        BasicData_addresss,
        BasicData_channel,
        BasicData_isOpen,

        BasicData_DeviceTyppeNameList,
        BasicData_DeviceSerialComList,
        BasicData_DeviceSerialBaudList,
    };

    typedef enum{
        Device_None = 0,
        Device_SerialPort,
        Device_NetUDP,
        Device_NetTCP,
        Device_end,
    }DeviceType;

public:
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QHash<int,QString> headerNames() const;

    Q_INVOKABLE QStringList  getDeviceTypeNameList() const;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addNewConnect();

private:
    void                initDeviceTypeNames();
    void                initDeviceSerialBaudMap();
    const QString       getDeviceTypeNameFromDeviceType(int type) const;
    const int           getDeviceTypeFromDeviceTypeName(QString name) const;
    const QVariant      getModelDataFromIDAndColumn(int id,int column) const;
    bool                upModelData(int row,int column,QVariant data);
    const QStringList   getDeviceSerialCom() const;
    const QStringList   getDeviceBaud() const;
private:
    QMap<int,BasicModelData>    BasicData;
    QList<int>                  BasicIDList;
    QMap<int,int>               BasicBaudMap;

    QMap<int,QString >          deviceTypeNamesMap;

signals:
    void connectButtonReleaseSignal(const QModelIndex &index);

};


class CommunicationsWidget : public QWidget{
    Q_OBJECT
public:
    friend class Q_DMMM;
    CommunicationsWidget(QWidget *parent = nullptr);

private:

    void widgetInit();
    void basicConfigWidgetInit();
    void photoelectricConfigInit();

    void parameterMapInit();

    void connectSignalAndSlot();
private:
    QTabWidget* main_tablewidget = nullptr;
    QGroupBox *basicConfigWidget = nullptr;                 //基础连接，飞行器连接
    QGridLayout *basicConfigWidgetLayout = nullptr;
    QTableView  *basicConfigTableView = nullptr;
    QPushButton *addButton = nullptr;
    QPushButton *subButton = nullptr;
    QHBoxLayout *buttonLayout = nullptr;


    QGroupBox *photoelectricConfigWidget = nullptr;         //光电，吊舱连接
    QGridLayout *photoelectricConfigWidgetLayout = nullptr;
    QGroupBox *rtspBaseBox = nullptr;                                   //基础参数
    QGroupBox *rtspAdvancedBox = nullptr;                          //高级参数配置

    QGridLayout *rtspBaseLayout = nullptr;

    QLabel          *rtspAddressLabel = nullptr;
    QComboBox *rtspAddressComboBox = nullptr;
    QPushButton *linkButton = nullptr;


    QGridLayout *rtspAdvancedLayout = nullptr;
    QLabel            *linkMode = nullptr;                                 //连接方式 (rtsp_transport)tcp/udp/rtp
    QComboBox  *linkModeComboBox = nullptr;
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


    WidgetTitle *w_title = nullptr;
    QGridLayout *mainLayout = nullptr;
    QGridLayout *WidgetLayout = nullptr;


private:
    BasicConfigWidgetTableModel *basicConfigModel = nullptr;
    BasicConfigWidgetDeviceItemDelegate *deviceItemDelegate = nullptr;
    BasicConfigWidgetButtonDelegate     *buttonDelegate = nullptr;

    QMap<QString,QString> parameterMap;

private:

signals:
    void newConnectGcsIDSignal(bool isopen,int id);

    void photoelectricStartSignal(QUrl,QMap<QString,QString>);
    void photoelectricStopSignal();
private slots:
    void basicConfigWidgetAddButtonReleaseSlot();
    void basicConfigWidgetRemoveButtonReleaseSlot();
    void connectButtonReleaseSlot(const QModelIndex &index);

    void photoelectricLinkButtonClickedSlot();
    void handle_DMMM_event(int ev, int linkid);

    void changedLinkStartForLinkID(int linkid,bool status,bool islinked = false);
public slots:
    void videoStartSlot(bool);

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




#endif // COMMUNICATIONSWIDGET_H
