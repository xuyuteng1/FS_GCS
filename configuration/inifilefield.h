#ifndef INIFILEFIELD_H
#define INIFILEFIELD_H

#include <QString>
#include <QVariant>
#include "configfile_ini.h"
class IniFileField
{
public:
    IniFileField();

    static QMap<QString,QVariant> getFieldMap(QString fieldName,QString uniqueIdentifier,QVariant defaultParameter = QVariant(),int fieldType = ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange,QVariant::Type  parameterType = QVariant::Type::Invalid);

private:
    QString         fieldName = "";
    QString         uniqueIdentifier = "";
    QVariant        defaultParameter = QVariant();
    int             fieldType = ConfigFile_Ini::FIELDTYPE::ifFieldExistNotChange;
    QVariant::Type  parameterType = QVariant::Type::Invalid;
};

#endif // INIFILEFIELD_H
