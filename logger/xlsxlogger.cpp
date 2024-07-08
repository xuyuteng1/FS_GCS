#include "xlsxlogger.h"



XlsxLogger::XlsxLogger()
{
    connect(&(this->timer),&QTimer::timeout,this,&XlsxLogger::timeroutslot);
    this->timer.start(500);
}

int XlsxLogger::addXlsxFileForID(int id,QString path)
{
    if(this->xlsxFileMap.find(id) == this->xlsxFileMap.end()){
        //ID不存在   新建
        this->xlsxFileMap.insert(id,new XlsxFileArgument(path));
        return 1;
    }else{
        return 0;
    }
}

int XlsxLogger::addXlsxFileSheetForID(int id, QString sheetName, QList<QString> fieldName)
{
    if(this->xlsxFileMap.find(id) != this->xlsxFileMap.end()){
        if(this->xlsxFileMap.find(id).value() != nullptr){
            return this->xlsxFileMap.find(id).value()->addSheet(sheetName,fieldName);
        }else{
            return 0;
        }
    }else{
        return 0;                   //当前IDxlsx文件不存在
    }
}

void XlsxLogger::addXlsxSheetValue(int id, QString sheetName, QMap<QString, QString> value)
{
    if(this->xlsxFileMap.find(id) != this->xlsxFileMap.end()){
        this->xlsxFileMap.find(id).value()->addXlsxSheetValue(sheetName,value);
    }
}

void XlsxLogger::readXlsxFile(QString path)
{
    this->readXlsxTask = new XlsxFileReadTask(path);                               //QRunnable执行完成后会自动释放资源
    connect(this->readXlsxTask,&XlsxFileReadTask::xlsxFileReadSignal,this,&XlsxLogger::xlsxFileReadSignal,Qt::DirectConnection);
    TPool::tPool->start(this->readXlsxTask);
}


void XlsxLogger::timeroutslot()
{
    QMap<int,XlsxFileArgument *>::iterator iter =  xlsxFileMap.begin();
    while(iter != xlsxFileMap.end()){
        if(iter.value() != nullptr){
            iter.value()->xlsxUpdate();
        }
        iter ++;
    }
}





XlsxSheetArgument::XlsxSheetArgument()
{

}

XlsxSheetArgument::XlsxSheetArgument(QString _sheetName, QList<QString> _headList,Document *xlsx)
{
    this->initializeXlsxSheet(_sheetName,_headList,xlsx);

}

void XlsxSheetArgument::initializeXlsxSheet(QString _sheetName, QList<QString> _headList,Document *xlsx)
{
    this->sheetName = _sheetName;
    this->headList = _headList;
    this->xlsx = xlsx;

    for(int i = 0; i < this->headList.count(); i++){
        this->columnNumHeadMap.insert(columnIndexToXlsxColumnIndexStr(i),this->headList.at(i));
        this->headColumnNumMap.insert(this->headList.at(i),columnIndexToXlsxColumnIndexStr(i));
    }
    for(int i = 1; i <= _headList.count(); i++){
        this->xlsx->selectSheet(_sheetName);
        qDebug()<<QString(this->headColumnNumMap.find(this->headList.at(i - 1)).value() + "1");
        this->xlsx->write(QString(this->headColumnNumMap.find(this->headList.at(i - 1)).value() + "1"),this->headList.at(i - 1));
    }
}

void XlsxSheetArgument::addXlsxValue(QMap<QString, QString> value)
{
    QMap<QString, QString>::iterator iter = value.begin();
    QMap<QString, QString>xlsxVal = {};
    while(iter != value.end()){
        if(this->headColumnNumMap.find(iter.key()) != this->headColumnNumMap.end()){
            xlsxVal.insert(this->headColumnNumMap.find(iter.key()).value(),iter.value());
        }
        iter ++;
    }
    this->valueMap.enqueue(xlsxVal);                    //进栈

}


QString XlsxSheetArgument::columnIndexToXlsxColumnIndexStr(int index)
{
    if(index / ('Z' - 'A' + 1) == 0){
        return QString(QChar('A' + (index % ('Z' - 'A' + 1))));
    }else{
        int tmp = index / ('Z' - 'A' + 1);
        return QString(QChar('A' + (tmp - 1) % ('Z' - 'A' + 1))) + QString(QChar('A' + index % ('Z' - 'A' + 1)));
    }
}

QQueue<QMap<QString, QString>> XlsxSheetArgument::getValueMap()
{
    QQueue<QMap<QString, QString>> retQueue;
    int count = this->valueMap.count();
    for(int i = 0; i < count; i++){
        retQueue.enqueue(this->valueMap.dequeue());
    }
    return retQueue;
}





XlsxFileArgument::XlsxFileArgument(QString path) : filePath(path)
{
    if(this->xlsx == nullptr){
        QFileInfo info(filePath);
        QDir dir(info.dir());
        if(!dir.exists()){
            dir.mkpath(info.dir().absolutePath());
        }
        this->xlsx = new Document(this->filePath);
        this->xlsx->saveAs(this->filePath);
    }
}

XlsxFileArgument::~XlsxFileArgument()
{
    if(this->xlsx != nullptr){
        this->xlsx->save();
    }
}

int XlsxFileArgument::addSheet(QString sheetName, QList<QString> field)
{
    if(this->sheetMap.find(sheetName) == this->sheetMap.end()){
        if(this->xlsx->addSheet(sheetName)){
            this->sheetMap.insert(sheetName,new XlsxSheetArgument(sheetName,field,this->xlsx));
            this->xlsx->saveAs(this->filePath);
        }
        return 1;
    }else{
        return 0;
    }
}

void XlsxFileArgument::addXlsxSheetValue(QString sheetName, QMap<QString, QString> value)
{
    if(this->sheetMap.find(sheetName) != this->sheetMap.end()){
        this->sheetMap.find(sheetName).value()->addXlsxValue(value);
    }
}

void XlsxFileArgument::xlsxUpdate()
{
    if(writeFlag == false){
        QMap<QString,XlsxSheetArgument *>::iterator iter = sheetMap.begin();
        while(iter != this->sheetMap.end()){
            if(iter.value() != nullptr){
                QQueue<QMap<QString, QString>> value = iter.value()->getValueMap();
                if(value.count() > 0){
                    this->task = new XlsxFileWriteTask(this->xlsx,iter.key(),value);            //QRunnable执行完后自动释放资源
                    this->writeFlag = true;
                    connect(this->task,&XlsxFileWriteTask::writeXlsxFinishSignal,this,[=]{writeFlag = false;},Qt::DirectConnection);
                    TPool::tPool->tryStart(task);
                    break;
                }
            }
            iter ++;
        }

    }
}

XlsxFileWriteTask::XlsxFileWriteTask(Document *doc, QString _sheetName, QQueue<QMap<QString, QString> > value)
{
    this->doc = doc;
    this->sheetName = _sheetName;
    this->value = value;
}

void XlsxFileWriteTask::run()
{
    if(this->doc == nullptr){
        return;
    }
    this->doc->selectSheet(this->sheetName);
    int valCount = value.count();
    for(int i = 0; i < valCount; i++){
        int count = this->doc->dimension().lastRow();

        QMap<QString,QString> map = value.dequeue();
        QMap<QString,QString>::iterator iter = map.begin();

        while(iter != map.end()){
            this->doc->write(iter.key() + QString::number(count + 1),iter.value());
            iter++;
        }
    }
    this->doc->save();
    emit writeXlsxFinishSignal();

}

XlsxFileReadTask::XlsxFileReadTask(QString _filePath)
{
    this->filePath = _filePath;
}

void XlsxFileReadTask::run()
{
    QFileInfo info(this->filePath);
    if(!info.isFile()){
        return;
    }

    xlsxData.clear();
    Document doc(this->filePath);
    QXlsx::Workbook *workBook = doc.workbook();
    int sheetCount = workBook->sheetCount();

    for(int i = 0; i < sheetCount; i++){
        Worksheet *sheet = static_cast<QXlsx::Worksheet *>(workBook->sheet(i));
        this->xlsxData.clear();

        int rowCount = sheet->dimension().rowCount();
        for(int j = 1;j <= rowCount; j++){
            QMap<QString,QString> rowData = {};
            for(int k = 1; k <= sheet->dimension().columnCount(); k++){

                QXlsx::Cell *cell = sheet->cellAt(j,k);
                if(cell != nullptr){
                    rowData.insert(columnIndexToXlsxColumnIndexStr(k - 1),cell->value().toString());
                }
            }
            this->xlsxData.enqueue(rowData);
        }
        emit xlsxFileReadSignal(sheet->sheetName(),this->xlsxData);

    }
}

QString XlsxFileReadTask::columnIndexToXlsxColumnIndexStr(int index)
{
    if(index / ('Z' - 'A' + 1) == 0){
        return QString(QChar('A' + (index % ('Z' - 'A' + 1))));
    }else{
        int tmp = index / ('Z' - 'A' + 1);
        return QString(QChar('A' + (tmp - 1) % ('Z' - 'A' + 1))) + QString(QChar('A' + index % ('Z' - 'A' + 1)));
    }
}









TextLoggerSaveAsXlsxFileTask::TextLoggerSaveAsXlsxFileTask(QTextStream *textStream)
{

}

void TextLoggerSaveAsXlsxFileTask::run()
{

}



















TextLogger::TextLogger()
{
    if(this->textLoggerTask == nullptr){
        this->textLoggerTask = new TextLoggerWriteTask();
    }
}

TextLogger::~TextLogger()
{
    qDebug()<<"TextLogger";
    if(this->textLoggerTask != nullptr){
        this->textLoggerTask->taskFinished();

    }
}

QList<int> TextLogger::getTextLoggerLinkList()
{
    return this->textStreamMap.keys();
}

void TextLogger::textLoggerWriteForTaskSlot(QTextStream *stream, QMap<QString, QString> value, QList<QString> fieldList)
{
    if(this->textLoggerTask != nullptr){
        this->textLoggerTask->newTextLoggerWrite(TextLoggerWriteTask::TextWrite(stream,value,fieldList));
    }
}

void TextLogger::textLogBeginSlot(int id, QString fileName, QList<QString> fieldList, QString filePath)
{
    if(this->textStreamMap.find(id) != this->textStreamMap.end()){                                          //查找当前LinkID对应日志文件
        QMap<QString,TextInfo *>infoMap = this->textStreamMap.find(id).value();                  //获取当前linkID日志信息
        TextInfo *info = infoMap.value(fileName,nullptr);                                                               //获取当前fileName对应textInfo指针，若存在，返回对应textInf信息，若不存在，返回nullptr

        if(info != nullptr){
            disconnect(info,&TextInfo::textLoggerWriteForTask,this,&TextLogger::textLoggerWriteForTaskSlot);
            info->textLogWriteFinish();                                                                                                //当前filleName对应textInfo执行日志写完毕指令
            info->deleteLater();                                                                                                              //当前filleName对应textInfo释放资源
        }
        TextInfo *infoPtr = new TextInfo(id,fileName,fieldList);                                                      //创建当前fileName对应textInfo指针
        if(infoPtr->getIsValid()){                                                                                                    //textInfo有效时
            this->textStreamMap[id][fileName] = infoPtr;                                                            //修改当前fileName对应textInfo指针。
            connect(infoPtr,&TextInfo::textLoggerWriteForTask,this,&TextLogger::textLoggerWriteForTaskSlot);
        }else{                                                                                                                                     //textInfo无效时
            infoPtr->deleteLater();                                                                                                   //释放textInfo资源
        }
    }else{
        TextInfo *infoPtr = new TextInfo(id,fileName,fieldList);                                                      //创建当前fileName对应textInfo指针
        qDebug()<<"infoPtr->getIsValid() = "<<infoPtr->getIsValid();
        if(infoPtr->getIsValid()){                                                                                                    //textInfo有效时
            connect(infoPtr,&TextInfo::textLoggerWriteForTask,this,&TextLogger::textLoggerWriteForTaskSlot);
            QMap<QString,TextInfo *>infoMap;
            infoMap.clear();
            infoMap.insert(fileName,infoPtr);
            this->textStreamMap.insert(id,infoMap);
        }else{                                                                                                                                     //textInfo无效时
            infoPtr->deleteLater();                                                                                                   //释放textInfo资源
        }
    }
}

void TextLogger::textLogWriteSlot(int id, QString fileName, QMap<QString, QString> valueMap)
{
    if(this->textStreamMap.find(id) != this->textStreamMap.end()){
        if(this->textStreamMap.find(id).value().find(fileName) != this->textStreamMap.find(id).value().end()){
            this->textStreamMap.value(id).value(fileName)->writeText(valueMap);
        }
    }
}

void TextLogger::textLogFinishSlot(int id, QString fileName)
{
    if(this->textStreamMap.find(id) != this->textStreamMap.end()){
        if(this->textStreamMap.find(id).value().find(fileName) != this->textStreamMap.find(id).value().end()){
            this->textStreamMap.value(id).value(fileName)->textLogWriteFinish();
            this->textStreamMap.remove(id);
        }
    }
}



TextInfo::TextInfo(int id,QString fileName, QList<QString> fieldList, QString filePath)
{
    this->id = id;
    this->fieldNameList = fieldList;
    this->dirPath = filePath;
    this->fileName = fileName + QString("_%1_").arg(QString::number(id)) +QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss")+".csv";

    this->isValid = this->textInfoInitialize();
}

TextInfo::~TextInfo()
{
    if(this->stream != nullptr){
        this->stream->flush();
    }

    if(this->file.isOpen()){
        this->file.close();
    }
}

void TextInfo::writeText(QMap<QString, QString> valueMap)
{
    if(!this->isValid || this->stream == nullptr){
        return;
    }
    emit textLoggerWriteForTask(this->stream,valueMap,this->fieldNameList);
}

void TextInfo::textLogWriteFinish()
{
    this->stream->flush();
    this->file.close();
}

bool TextInfo::getIsValid() const
{
    return isValid;
}

bool TextInfo::textInfoInitialize()
{
    if(this->fieldNameList.count() <= 0){                                               //fieldList必须要有数据，在写入时会根据fieldNameList中的数据查找map来匹配文本所在位置
        return false;
    }else{
        this->columnCount = this->fieldNameList.count();
    }

    QString filePath = this->dirPath + "/" + this->fileName;

    QDir dir(this->dirPath);
    if(!dir.exists()){
        if(!dir.mkpath(this->dirPath)){                                                          //若路径不存在则创建路径
            return false;                                                                                       //无法创建路径则返回 false
        }
    }

    this->file.setFileName(filePath);
    if(file.open(QIODevice::Text | QIODevice::WriteOnly)){
        if(this->stream == nullptr){                                                                //初始化stream
            this->stream = new QTextStream(&file);
//            this->stream->setFieldWidth(24);                                                  //设置默认字宽为224
            this->stream->setFieldAlignment(QTextStream::AlignCenter);  //设置字段对齐方式为居中对齐
//            this->stream->setPadChar(' ');                                                       //设置填充字符为‘ ’
        }
    }else{
        return false;
    }


    for(int i = 0; i < this->fieldNameList.count(); i++){
        *(this->stream)<<this->fieldNameList.at(i)<<',';
    }
    *(this->stream)<<"\n";
    this->stream->flush();

    return true;
}

TextLoggerWriteTask::TextLoggerWriteTask()
{
    this->start();
}

TextLoggerWriteTask::~TextLoggerWriteTask()
{
    this->finished = true;
}

void TextLoggerWriteTask::taskFinished()
{
    this->finished = false;
}

void TextLoggerWriteTask::newTextLoggerWrite(TextWrite text)
{
    this->writeQueue.enqueue(text);
}

void TextLoggerWriteTask::run()
{
    do{
        int count = this->writeQueue.count();
        for(int writeCount = 0; writeCount < count;writeCount++){
            TextWrite textWrite = this->writeQueue.dequeue();
            if(textWrite.stream == nullptr){
                continue;
            }

            for(int i = 0; i < textWrite.writeField.count(); i++){
                if(textWrite.writeVal.find(textWrite.writeField.at(i)) != textWrite.writeVal.end()){
                    *(textWrite.stream)<<QString(textWrite.writeVal.value(textWrite.writeField.at(i))).remove('\r').remove('\n').remove('\t')<<",";
                }else{
                    *(textWrite.stream)<<"0"<<",";
                }
            }
            *(textWrite.stream)<<"\n";
            textWrite.stream->flush();
        }
        QThread::msleep(50);
    }while(!finished);
}
