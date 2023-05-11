#ifndef DATASERIALIZER_H
#define DATASERIALIZER_H
#include "dataoperation.h"
#include "qdatastream.h"

class DataSerializer: public DataOperation
{
    QDataStream stream;
public:
    DataSerializer();
    QByteArray operation() override;
};

#endif // DATASERIALIZER_H
