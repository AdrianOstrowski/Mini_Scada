#ifndef DATAOPERATION_H
#define DATAOPERATION_H
#include "networkconnection.h"
#include "databuffer.h"

class DataOperation
{
private:
    std::string ip;
    unsigned short port;
    DataBuffer buffer;
public:
    DataOperation();
    virtual QByteArray operation() = 0;
};

#endif // DATAOPERATION_H
