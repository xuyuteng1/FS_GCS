#include "configfile_xml.h"

Configfile_xml::Configfile_xml()
{
    xmlConfigInit();
}

void Configfile_xml::xmlConfigInit()
{
    QString path = QString(QCoreApplication::applicationDirPath() + "/config/basicconfig.xml");
    QDomDocument doc;
    QFileInfo info(path);
    if(info.exists()){
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly)){
            qDebug()<<QStringLiteral("文件打开失败，PATH:") << path;
            return;
        }

        if(!doc.setContent(&file)){
            qDebug()<<QStringLiteral("doc content error");
            return;
        }

        /*初始化读取systemConfig*/
        QDomElement root = doc.firstChildElement("SystemConfig");

//        qDebug()<<root.childNodes().count();
        QMap<QString ,QVariant> nodeMap;
        QDomNode node = root.firstChild();
        while(!node.isNull() && node.isElement()){
            readXmlData(node.toElement(),node.nodeName(),nodeMap);
            node = node.nextSibling();
        }

    }else{
        QDir dir(info.dir());
        if(!dir.exists()){
            dir.mkdir(info.dir().dirName());
        }



        QDomProcessingInstruction xmlInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
        QDomComment styleInstruction = doc.createComment(QStringLiteral("此xml文件为系统运行必须文件，主要用于配置系统运行过程中默认配置文件信息。此文件存储部分系统默认信息，当配置文件(ini文件)损坏或需恢复默认参数时使用该文件创建。同时，系统程序根据该文件读取系统需要的配置文件信息"));
        doc.appendChild(xmlInstruction);  // 开始文档（XML 声明）
        doc.appendChild(styleInstruction);

        QDomElement rootNode = doc.createElement("SystemConfig");
        doc.appendChild(rootNode);

        QDomElement subNode = doc.createElement("widgetConfig");
        QMap<QString, QVariant> propertyMap;
        propertyMap.insert("name","hudwidget");
        propertyMap.insert("path",QCoreApplication::applicationDirPath() + "/config/widgetConfig.ini" );
        writeXmlData(rootNode,subNode,propertyMap);

        propertyMap.clear();
        propertyMap.insert("field","color_hudSky");
        propertyMap.insert("type","color_hudSky");
        propertyMap.insert("uniqueIdentifier","widgetConfig.hudwidget.color_hudSky");
        writeXmlData(subNode,doc.createElement("color_hudSky"),propertyMap);




        QFile file(path);
        if(!file.open(QIODevice::WriteOnly)){
            return ;
        }
        QTextStream stream(&file);
        stream.setCodec("UTF-8"); //使用utf-8格

        doc.save(stream, 4, QDomNode::EncodingFromTextStream);
        file.close();
    }
}

void Configfile_xml::readXmlData(QDomElement element, QString IdentifierParentName, QMap<QString, QVariant> &dataMap)
{
    QDomNamedNodeMap attrs = element.attributes();
//    qDebug()<<attrs.count()<<element.nodeName(),element.text();
    qDebug()<<"IdentifierParentName = "<<IdentifierParentName;
    QDomNode child = element.firstChild();

    for (int i = 0; i < attrs.count(); i++)
    {
        QDomNode attr =  attrs.item(i);
        if (!attr.isNull() && attr.isAttr()) {
            qDebug() << "-" << attr.nodeName() << attr.nodeValue();
        }
    }


    while (!child.isNull() && child.isElement())
    {
        QDomElement childele = child.toElement(); // try to convert the node to an element.
        readXmlData(childele,IdentifierParentName + "." + element.nodeName(),dataMap);
        child = child.nextSibling();
    }
}


void Configfile_xml::writeXmlData(QDomNode parentNode, QDomElement node, QMap<QString, QVariant> propertyMap)
{
    QMap<QString, QVariant>::iterator iter = propertyMap.begin();
    while(iter != propertyMap.end()){

        switch(iter.value().type()){
        case QVariant::Type::Int:{
            node.setAttribute(iter.key(),iter.value().toInt());
            break;
        }case QVariant::Type::UInt: {
            node.setAttribute(iter.key(),iter.value().toUInt());
            break;
        }case QVariant::Type::LongLong:{
            node.setAttribute(iter.key(),iter.value().toLongLong());
            break;
        }case QVariant::Type::ULongLong:{
            node.setAttribute(iter.key(),iter.value().toULongLong());
            break;
        }case QVariant::Type::Double:{
            node.setAttribute(iter.key(),iter.value().toDouble());
            break;
        }case QVariant::Type::String:{
            node.setAttribute(iter.key(),iter.value().toString());
            break;
        }case QVariant::Type::Time:{
            node.setAttribute(iter.key(),iter.value().toTime().toString("hh:mm:ss.zzz"));
            break;
        }case QVariant::Type::DateTime:{
            node.setAttribute(iter.key(),iter.value().toDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"));
            break;
        }case QVariant::Type::Bool:{
            node.setAttribute(iter.key(),iter.value().toBool());
            break;
        }case QVariant::Type::Url:{
            node.setAttribute(iter.key(),iter.value().toUrl().toString());
            break;
        }case QVariant::Type::StringList:{
            node.setAttribute(iter.key(),iter.value().toStringList().join(" "));
            break;
        }
        default:{

            break;
        }

        }
        parentNode.appendChild(node);
        iter ++;
    }
}


