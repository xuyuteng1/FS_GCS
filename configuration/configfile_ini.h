#ifndef CONFIGFILE_INI_H
#define CONFIGFILE_INI_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QMap>
#include <QTextCodec>
#include <QColor>
#include <QDate>
#include <QDateTime>
#include <QDebug>

class ConfigFile_Ini : public QObject
{
    Q_ENUMS(FIELDTYPE)
    Q_OBJECT
public:
    ConfigFile_Ini(QObject *parent = nullptr);

 public:
     enum FIELDTYPE{
         ifFieldExistwillChange = 0,         //新建时，存在则修改
         ifFieldExistNotChange = 1           //新建时，存在则不修改
     };

 private:

     //用于存储所有QSettings,Key名是唯一识别标识
     QMap <QString, QSettings *>settingFileMap;

 private:
     bool fileIsExist(QString path);         //判断文件是否存在
     bool dirIsExist(QString path);          //判断路径是否存在

 signals:


 public slots:
     /* -- 创建新的QSettings,name为settingFileMap中唯一标识，path为配置文件路径    -- */
     void createNewSettings(QString name,QString path);

     /* -- 创建一个新的字段，name为settingFileMap中唯一标识,groupName为分组名，fieldName为字段名,val为字段值  -- */
     void addNewField(QString name,QString groupName,QString fieldName,QVariant val);                //默认存在则修改
     void addNewField(QString name,QString groupName,QString fieldName,QVariant val,ConfigFile_Ini::FIELDTYPE type);

     /* -- 修改一个新的字段，name为settingFileMap中唯一标识,groupName为分组名，fieldName为字段名,val为字段值  -- */
     void changedField(QString name,QString groupName,QString fieldName,QVariant val);               //默认存在则重新建立

     void getFieldValue(QString name,QString groupName,QString fieldName,QVariant &ret);
     void getFieldValue(QString name,QString groupName,QString fieldName,uchar &ret);
     void getFieldValue(QString name,QString groupName,QString fieldName,int &ret);
     void getFieldValue(QString name,QString groupName,QString fieldName,QString &ret);
     void getFieldValue(QString name,QString groupName,QString fieldName,double &ret);
     void getFieldValue(QString name,QString groupName,QString fieldName,float &ret);
     void getFieldValue(QString name,QString groupName,QString fieldName,bool &ret);


     QStringList getFieldKeys(QString name);
     QStringList getAllGroups(QString name);

};

#endif // CONFIGFILE_INI_H
