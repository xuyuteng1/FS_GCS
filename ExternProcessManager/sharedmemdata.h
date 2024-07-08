#ifndef SHAREDMEMDATA_H
#define SHAREDMEMDATA_H

#include <QByteArray>
#include <QString>
#include <QBuffer>
#include <QJsonObject>

#pragma pack(push)
#pragma pack(1)//单字节对齐
struct SharedMemDataHeader
{
    uchar recver;                                   //使用者               M/S (master/slave)
    uchar mode;                                    //消息使用模式     U/T (Use/Transmit)<地面站或转发至飞控>
    uchar type;                                     //消息体类型         J/H/A/O(Json/Hex/ASCII/Other)
    int      len;                                       //有效数据长度
};
#pragma pack(pop)




class SharedMemData
{
public:
    enum PackedType{
        UnPackData = 0,
        PackData,
    };

public:
    SharedMemData(PackedType type, QBuffer &buff,SharedMemDataHeader &header,QByteArray &data);                                               //解析时使用

    bool getIsValid() const;

private:
    bool                                 isValid = false;



};

#endif // SHAREDMEMDATA_H
