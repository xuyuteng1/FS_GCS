#ifndef CONFIGFILE_XML_H
#define CONFIGFILE_XML_H

#include <QDomComment>
#include <QDomDocument>
#include <QXmlSimpleReader>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMetaType>
#include <QTime>
#include <QUrl>
#include <QColor>
#include <QMap>
#include <QVariant>



#include <QDebug>

class Configfile_xml
{
public:
    Configfile_xml();


private:
    void xmlConfigInit();

    void readXmlData(QDomElement element,QString IdentifierParentName,QMap<QString,QVariant> &dataMap);
    void writeXmlData(QDomNode parentNode, QDomElement node,QMap<QString,QVariant>propertyMap);

private:


};

#endif // CONFIGFILE_XML_H
