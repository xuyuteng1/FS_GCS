#include "sharedmemdata.h"

SharedMemData::SharedMemData(PackedType type, QBuffer &buff,SharedMemDataHeader &header,QByteArray &data)
{
    if(type == PackedType::UnPackData){                                 //解包
            this->isValid = false;
            if(buff.data().length() > sizeof(SharedMemDataHeader)){
                memcpy(&header,buff.data().data(),sizeof(SharedMemDataHeader));
                if(header.recver != 'M' && header.recver != 'S' ){                                      //当消息消费者标记不为Slove,则退出
                    return;
                }
                if(header.mode != 'U' &&  header.mode != 'T'){
                    return;
                }
                if(header.type != 'J' && header.type != 'H' && header.type != 'A' && header.type != 'O'){
                    return;
                }
                if(header.len + sizeof(SharedMemDataHeader) >= buff.data().length()){
                    return;
                }

                data.resize(header.len);
                memcpy(data.data(),buff.data().data() + sizeof(SharedMemDataHeader),header.len);
                this->isValid = true;
            }
    }else if(type == PackedType::PackData){
        QByteArray array;
        array.resize(sizeof(header) + data.length());
        memcpy(array.data(),&header,sizeof(header));
        memcpy(array.data() + sizeof(header),data.data(),data.length());

        if(!buff.open(QIODevice::WriteOnly) || buff.write(array) <= 0){
            this->isValid = false;
        }else{
            this->isValid = true;
        }
    }
}



bool SharedMemData::getIsValid() const
{
    return isValid;
}
