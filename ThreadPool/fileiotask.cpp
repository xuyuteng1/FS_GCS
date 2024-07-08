#include "fileiotask.h"
#include <QDebug>



FileWriteTask::FileWriteTask(QList<QString>)
{

}

int FileWriteTask::writeResults()
{
    return 0;
}

void FileWriteTask::run()
{

}




FileReadTask::FileReadTask(QString filePath,int cnt) : filePath(filePath),signalCount(cnt)
{
}


void FileReadTask::run()
{
    QFileInfo fileInfo(this->filePath);
    if(fileInfo.isFile()){
        QFile file(this->filePath);
        if(file.open(QIODevice::ReadOnly)){
            QTextStream stream(&file);
            QQueue<QString> fileData;
            fileData.clear();
            while(!stream.atEnd()){
                fileData.enqueue(stream.readLine());
                if(fileData.count() > this->signalCount){
                    QQueue<QString> readData;
                    for(int i = 0; i < signalCount; i++){
                        readData.enqueue(fileData.dequeue());
                    }
                    emit fileReadDataSignal(readData);
                }
            }
            emit fileReadDataSignal(fileData);
        }
    }
    emit fileReadFinishSignal();
}
