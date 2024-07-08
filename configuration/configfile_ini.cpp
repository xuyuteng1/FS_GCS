#include "configfile_ini.h"
#include "qurl.h"



ConfigFile_Ini::ConfigFile_Ini(QObject *parent) : QObject(parent)
{

}

void ConfigFile_Ini::createNewSettings(QString name,QString path){
    QStringList mapName = settingFileMap.keys();
    if(mapName.contains(name)){
        //settingFileMap 中已存在 name
    }else{
        QString dirPath = path.mid(0,path.lastIndexOf("/"));
        if(!dirIsExist(dirPath)){
            QDir dir;
            dir.mkpath(dirPath);        //创建文件夹 多级目录
        }

        if(dirIsExist(dirPath)){
            QSettings *setting = new QSettings(path,QSettings::IniFormat);
            setting->setIniCodec(QTextCodec::codecForName("GBK"));
            settingFileMap.insert(name,setting);
        }else{
            //创建文件夹失败，路径错误
        }
    }
}


bool ConfigFile_Ini::fileIsExist(QString path){
    QFileInfo fileInfo(path);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

bool ConfigFile_Ini::dirIsExist(QString path){

    QFileInfo fileInfo(path);
    if(fileInfo.isDir())
    {
      return true;
    }
    return false;
}


void ConfigFile_Ini::addNewField(QString name,QString groupName,QString fieldName,QVariant val){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }

    settingFileMap[name]->beginGroup(groupName);
    switch(val.type()){
    case QVariant::Type::Color:{
        QColor color = val.value<QColor>().value();
        settingFileMap[name]->setValue(fieldName,color);
        break;
    }case QVariant::Type::Double:{
        settingFileMap[name]->setValue(fieldName,val.toDouble());
        break;
    }case QVariant::Type::Int:{
        settingFileMap[name]->setValue(fieldName,val.toInt());
        break;
    }case QVariant::Type::UInt:{
        settingFileMap[name]->setValue(fieldName,val.toUInt());
        break;
    }case QVariant::Type::LongLong:{
        settingFileMap[name]->setValue(fieldName,val.toLongLong());
        break;
    }case QVariant::Type::ULongLong:{
        settingFileMap[name]->setValue(fieldName,val.toULongLong());
        break;
    }case QVariant::Type::String:{
        settingFileMap[name]->setValue(fieldName,val.toString());
        break;
    }case QVariant::Type::Date:{
        settingFileMap[name]->setValue(fieldName,val.toDate().toString("yyyy-MM-dd"));
        break;
    }case QVariant::Type::Time:{
        settingFileMap[name]->setValue(fieldName,val.toTime().toString("hh:mm:ss.zzz"));
        break;
    }case QVariant::Type::DateTime:{
        settingFileMap[name]->setValue(fieldName,val.toDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
        break;
    }case QVariant::Type::Url:{
        settingFileMap[name]->setValue(fieldName,val.toUrl().toString());
        break;
    }case QVariant::Type::Bool:{
        settingFileMap[name]->setValue(fieldName,val.toBool());
        break;
    }default:{
        settingFileMap[name]->setValue(fieldName,val);
        break;
    }

    }
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::addNewField(QString name,QString groupName,QString fieldName,QVariant val,FIELDTYPE type){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }

    QStringList fields = settingFileMap[name]->allKeys();
    if(type == ifFieldExistNotChange){
        if(fields.contains(QString("%1/%2").arg(groupName).arg(fieldName))){
            //字段存在
        }else{
//            settingFileMap[name]->setValue(QString("%1/%2").arg(groupName).arg(fieldName),val);
            addNewField(name,groupName,fieldName,val);
        }
    }else{
//        settingFileMap[name]->setValue(QString("%1/%2").arg(groupName).arg(fieldName),val);
        addNewField(name,groupName,fieldName,val);
    }
}

void ConfigFile_Ini::changedField(QString name,QString groupName,QString fieldName,QVariant val){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    settingFileMap[name]->setValue(fieldName,val);
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, QVariant &ret){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName);
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, uchar &ret)
{
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName).toChar().toLatin1();
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, int &ret){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName).toInt();
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, QString &ret){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName).toString();
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, double &ret){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName).toDouble();
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, float &ret){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName).toFloat();
    settingFileMap[name]->endGroup();
}

void ConfigFile_Ini::getFieldValue(QString name, QString groupName, QString fieldName, bool &ret){
    if(this->settingFileMap.find(name) == this->settingFileMap.end()){
        return;
    }
    settingFileMap[name]->beginGroup(groupName);
    ret = settingFileMap[name]->value(fieldName).toBool();
    settingFileMap[name]->endGroup();
}

QStringList ConfigFile_Ini::getFieldKeys(QString name)
{
    QStringList strList;
    strList.clear();
    QMap <QString ,QSettings *>::iterator iter = settingFileMap.find(name);
    if(iter != settingFileMap.end()){
        return iter.value()->allKeys();
    }else{
        return strList;
    }
}

QStringList ConfigFile_Ini::getAllGroups(QString name)
{
    QStringList strList;
    strList.clear();
    QMap <QString ,QSettings *>::iterator iter = settingFileMap.find(name);
    if(iter != settingFileMap.end()){
        return iter.value()->childGroups();
    }else{
        return strList;
    }
}
