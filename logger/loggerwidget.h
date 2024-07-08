#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QTableView>
#include <QTreeView>
#include <QDir>
#include <QGridLayout>
#include <QFileSystemModel>
#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QRunnable>
#include <QQueue>
#include "fileiotask.h"
#include "threadpool.h"
#include "loggermanagement.h"
#include <QTimer>
#include <QObject>
#include <QPushButton>
#include <QTabWidget>
#include <QCheckBox>
#include <QSplitter>
#include <QStyledItemDelegate>
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>
#include <QComboBox>
#include <QProgressBar>
#include <QLineEdit>
#include <QGroupBox>
//#include "ExternProcessDrive/loggerreplay.h"
#include <QFileDialog>
#include <QShowEvent>
#include <QMainWindow>
#include <QSize>
#include "widgetitle.h"
#include <QHeaderView>

using namespace Log;

struct LogInfo
{
    QDateTime   logTime;
    int                 logType;
    QString         logName;
    QString         text;
};

class InfoViewModel : public QAbstractItemModel{
    Q_OBJECT
public:


public:
    InfoViewModel();
    enum LogInfoRoles{
        LogTime = Qt::UserRole + 1,
        LogType,
        LogName,
        LogText,
    };

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

    QHash<int,QByteArray> headerNames() const;

    void changedLogFile(QString filePath);

public slots:
    void addLogMap(QMap<int,LogInfo> map);


    void addLogMapForQueue(QQueue<LogInfo> map);
private:
    QMap<int,LogInfo> logMap;

};



class LogFileCerializeTask : public QObject,public QRunnable{
    Q_OBJECT
public:
    LogFileCerializeTask(int cnt);
protected:
    void run();

private:
    QQueue<QString> fileData;
    QQueue<LogInfo> cerializeData;

    bool readFinish = false;
    int  signalCount = 1;

public slots:
    void addCerializeData(QQueue<QString>);
    void fileReadFinishSlot();

signals:
    void resultsCerializeDataSignal(QQueue<LogInfo> );
    void cerializeFinishSignal();
};





class FileSystemModel : public QFileSystemModel{
public:
    int columnCount(const QModelIndex &parent) const{
        Q_UNUSED(parent)
        return 1;                   //只显示名称
    }
};

//系统运行日志
class SystemLogWidget : public QSplitter {
    Q_OBJECT
public:
    SystemLogWidget();
private:
    QTreeView *fileView = nullptr;
    QTableView  *infoView = nullptr;
    QGridLayout *widgetLayout = nullptr;

    FileSystemModel *fileModel = nullptr;
    InfoViewModel   *logModel = nullptr;

    QString logFilePath = {};

    FileReadTask               *readTask = nullptr;
    LogFileCerializeTask  *cerializeTask = nullptr;

    bool readFinish = true;
    bool cerializeFinist = true;

private:
    void widgetInit();
    void connectSignalAndSlot();
private slots:
    void doubleClickedSlot(const QModelIndex &index);
};


//系统数据日志
class SystemLogDataWidget : public QSplitter{
public:
    SystemLogDataWidget();

private:

};




class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CheckBoxDelegate(QObject *parent = 0);

    void setColumn(int col);

protected:
    void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
    bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index);

private:
    int column;         //设置复选框的列
};


class ProgressBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ProgressBarDelegate(QObject *parent = 0);

    void setColumn(int col, int min, int max);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex	&index) const
    {
            return NULL;
    }

protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    int column;
    int maxValue;			// 设置最大值
    int minValue;			// 设置最小值
};


class PlaneLogDownLoadModel : public QAbstractItemModel{
    Q_OBJECT
public:
    struct PlaneLogInfo
    {
        bool               logCheck;                //下载被勾选状态
        int                 logID;                      //日志序号
        QString             logName;                 //文件名
        QDateTime           logTme;                   //时间
        int                 logSize;                    //文件大小
        int                 status;                      //状态    0:未下载          1:等待下载    2:正在下载      3:下载完成      -1:下载失败
        int                 loadSize;                 //已下载大小
    };

public:
    PlaneLogDownLoadModel();

    enum PlaneLogInfoRoles{
        PlaneLogCheck = Qt::UserRole + 1,
        PlaneLogID,
        PlaneLogName,
        PlaneLogTime,
        PlaneLogSize,
        PlaneLogDownloadSize,
        PlaneLogStatus,
        PlaneLogLoadSize,
    };

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    Q_INVOKABLE QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

    QHash<int,QByteArray> headerNames() const;

    QHash<int,QByteArray> statusNames() const;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void clearPlaneLogMap();

    void addPlaneLogFileList(int id,QString fileName,QDateTime time,int size);

    void updatePlaneLogFileLoadSize(int id,int loadSize);

    void selectAllFile(bool );                                           //全选

    QList<int> getSelectedFileId();                                 //获取被选中文件的ID

    QList<int> getDownloadingFileID();                         //获取当前正在下载中的文件列表

    QList<int> getNotCompletedDownloadFileID();     //获取当前正在下载中或等待下载的文件列表

    void setDownloadFileList(QList<int>);

    void setCancelDownloadFileList(QList<int>);
private:
    QMap<int,PlaneLogInfo *>planeLogMap;
    QList<int> mapIndexList;


public:
signals:
    void selectFileChangedSignal();
};


//机载日志
class PlaneLogDownLoadWidget: public QWidget{
    Q_OBJECT
public:
    PlaneLogDownLoadWidget();

private:
    QTableView  *fileListView = nullptr;

    QCheckBox    *seleceAllCheckBox = nullptr;                  //全选与取下全选
    QPushButton *getFileListButton = nullptr;                   //获取文件列表
    QPushButton *downLoadButton = nullptr;                   //下载选中
    QPushButton *cancelButton = nullptr;                         //取消当前下载
    QPushButton *cancelAllButton = nullptr;                     //取消全部下载
    QPushButton *ClearLogButton = nullptr;                     //取消全部下载

    QGridLayout *widgetLayout = nullptr;

private:
    PlaneLogDownLoadModel *planeLogModel = nullptr;
    CheckBoxDelegate              *checkBoxDelegate = nullptr;
    ProgressBarDelegate          *progressBarDelegate = nullptr;
private:
    void widgetInit();
    void connectSignalAndSlot();

private slots:
    void seleceAllCheckBoxChangedSlot(int status);
    void getFileListButtonPressedSlot();
    void downloadButtonPressedSlot();
    void cancelButtonPressedSlot();
    void cancelAllButtonPresssedSlot();
    void ClearLogButtonPresssedSlot();

    void handle_DMMM_event(int ev,int linkid = 0);
public slots:
    //当获取到文件列表后通过此函数向用户界面添加获到的文件信息
    void addPlaneLogFileListSlot(int id,QString fileName,QDateTime time,int size);
    //通过此函数获取文件下载大小
    void updatePlaneLogFileLoadSizeSlot(int id,int loadSize);

    void selectFileChangedSlot();                               //选中状态发生改变

};


class ReplayWidget : public QMainWindow{
    Q_OBJECT
public:
    ReplayWidget();

private:
//    LoggerReplay                *loggerRelpayWidget = nullptr;

protected:
    void                showEvent(QShowEvent *e);

};


class LoggerWidget : public QWidget
{
    Q_OBJECT
public:
    LoggerWidget(QWidget *parent = nullptr);

private:
    WidgetTitle *w_title = nullptr;
    QGridLayout *mainLayout = nullptr;

    QTabWidget *tableWidget = nullptr;

    SystemLogWidget         *systemLogWidget = nullptr;
    SystemLogDataWidget  *systemDataWidget = nullptr;
    PlaneLogDownLoadWidget *planeLogDownWidget = nullptr;
    ReplayWidget          *loggerReplayWidget = nullptr;
private:
    void widgetInit();

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

#endif // LOGGERWIDGET_H
