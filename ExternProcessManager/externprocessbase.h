#ifndef EXTERNPROCESSBASE_H
#define EXTERNPROCESSBASE_H

#include <QString>
#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
//所有外部程序基类

class ExternProcessBase : public QObject{
    Q_OBJECT
public:
    struct ProcessParameter
    {
        //QProcess相关
        QString                     processName = {};                              //外部程序名称
        QString                     processPath = {};                               //外部程序地址

        //消息体相关
        bool                           hasInterface = false;                          //是否嵌入外部程序运行界面
        bool                           hasSharedMemory = false;                //外部程序是否包含共享内存
        bool                           hasCommunication = false;              //是否与飞控存在通讯
        bool                           hasTransmit = false;                         //是否需要飞控转发

        uchar                        communicationType  = 0;                  //与飞控通讯接口类型
        QString                     communicationAddress = {};            //与飞控通讯接口名称

        //共享内存相关
        QString                     key = "";                                             //系统唯一标识
        int                             size = 1024;                                        //共享内存大小(最大通讯协议长度)

        //嵌入界面相关
        QString                     IpClassName  = "";                            //指向一个指定了类名的空结束字符串，或一个标识类名字符串的成员的指针。假设该參数为一个成员，则它必须为前次调用theGlobafAddAtom函数产生的全局成员。该成员为16位，必须位于IpClassName的低 16位，高位必须为 0。
        QString                     IpWindowName  = "";                       //指向一个指定了窗体名（窗体标题）的空结束字符串。假设该參数为空，则为全部窗体全匹配。

        QString                     arguments  = "";                                //进程传参(默认为空)
    };

public:
    ExternProcessBase(ProcessParameter);

public:
    const QString &getProcessName() const;
    void setProcessName(const QString &newProcessName);

    const QString &getProcessPath() const;
    void setProcessPath(const QString &newProcessPath);

    bool getHasInterface() const;
    void setHasInterface(bool newHasInterface);

    bool getHasSharedMemory() const;
    void setHasSharedMemory(bool newHasSharedMemory);

    bool getHasCommunication() const;
    void setHasCommunication(bool newHasCommunication);

    bool getHasTransmit() const;
    void setHasTransmit(bool newHasTransmit);

    uchar getCommunicationType() const;
    void setCommunicationType(uchar newCommunicationType);

    const QString &getCommunicationAddress() const;
    void setCommunicationAddress(const QString &newCommunicationAddress);

    const QString &getKey() const;
    void setKey(const QString &newKey);

    int getSize() const;
    void setSize(int newSize);

    const QString &getIpClassName() const;
    void setIpClassName(const QString &newIpClassName);

    const QString &getIpWindowName() const;
    void setIpWindowName(const QString &newIpWindowName);

    bool getIsValid() const;

    bool getIsRunning() const;

    qint64 getProcessID();

private:
    ProcessParameter    parameter;

    //进程控制相关
    bool                            isValid = false;                                  //是否有效
    bool                            isRunning = false;                            //是否在运行

    QList<QString>        errorList = {};                                   //错误列表
    int                             errorCount = 0;                                 //错误次数
private:
    QProcess                    *process = nullptr;                         //外部进程
private:
    void                            initExternProcess();                        //初始化进程

public slots:
    void                            processStart();
    void                            processClose();
public:
signals:
    void                            started();

};

#endif // EXTERNPROCESSBASE_H
