#include "sharedmenmanger.h"

SharedMemManger::SharedMemManger()
{

}

void SharedMemManger::addNewSharedMenory(QString name,QString key)
{
    qDebug()<<"addNewSharedMenory"<<name<<key;
    if(this->sharedMemoryMap.find(key) == this->sharedMemoryMap.end()){
        QSharedMemory *memory = new QSharedMemory(this);
        memory->setKey(key);
        this->sharedMemoryMap.insert(key,memory);
        this->sharedMemKeyMap.insert(name,key);
        memory->attach();
        this->start();
    }
}

void SharedMemManger::run()
{
    while(this->sharedMemoryMap.count() > 0){
        QMap<QString,QSharedMemory *>::iterator iter = this->sharedMemoryMap.begin();
        while(iter != this->sharedMemoryMap.end()){
            if(iter.value() != nullptr){
                if(iter.value()->lock()){
                    QBuffer buffer;
                    buffer.setData(static_cast<const char *>(iter.value()->data()),iter.value()->size());
                    SharedMemDataHeader header = {};
                    QByteArray array = {};
                    SharedMemData data(SharedMemData::PackedType::UnPackData,buffer,header,array);

                    if(header.recver != 'S'){                   //从机使用
                        iter.value()->unlock();                                 //结束共享内存占用
                        iter++;
                        continue;
                    }
                    if(data.getIsValid()){
                        emit recvDataSignal(iter.key(),buffer.data());
                        memset(iter.value()->data(),0,iter.value()->size());
                    }
                }
                iter.value()->unlock();                                 //结束共享内存占用
            }
            iter++;
        }
        msleep(100);
    }
}

void SharedMemManger::writeData(QString name, QByteArray transmitArray)
{
    if(this->sharedMemKeyMap.find(name) == this->sharedMemKeyMap.end()){
        return;
    }
    QString key = this->sharedMemKeyMap.find(name).value();

    if(this->sharedMemoryMap.find(key) != this->sharedMemoryMap.end()){
        if(this->sharedMemoryMap.find(key).value() != nullptr){
            QSharedMemory *sharedMem = this->sharedMemoryMap.find(key).value();
            if(!sharedMem->isAttached()){                        //如果没有附加到进程，则先执行附加到进程
                sharedMem->attach();
            }

            if(sharedMem->isAttached()){
                if(sharedMem->lock()){
                    QBuffer buffer;
                    buffer.setData(static_cast<const char *>(sharedMem->data()),sharedMem->size());
                    SharedMemDataHeader header = {};
                    QByteArray array = {};
                    SharedMemData data(SharedMemData::PackedType::UnPackData,buffer,header,array);
                    if(!data.getIsValid()){
                        memcpy(sharedMem->data(),transmitArray.data(),sharedMem->size() < transmitArray.length() ? sharedMem->size() : transmitArray.length());
                    }
                }
                sharedMem->unlock();

            }else{
                qDebug()<<sharedMem->errorString();
            }
        }
    }
}

