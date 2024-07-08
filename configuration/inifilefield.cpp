#include "inifilefield.h"

IniFileField::IniFileField()
{

}

QMap<QString, QVariant> IniFileField::getFieldMap(QString fieldName,QString uniqueIdentifier, QVariant defaultParameter, int fieldType, QVariant::Type parameterType)
{
    QMap<QString, QVariant> retMap;

    retMap.clear();
    retMap.insert("field",fieldName);
    retMap.insert("type",fieldType);

    return retMap;
}
