#ifndef DATAOPERATION_H
#define DATAOPERATION_H
#include "networkconnection.h"
#include "databuffer.h"
#include <QDataStream>

class DataOperation
{
private:
    QString ip;
    unsigned short port;
    DataBuffer buffer;
public:
    DataOperation();
    virtual QByteArray operation(QByteArray&) = 0;
};

#endif // DATAOPERATION_H
