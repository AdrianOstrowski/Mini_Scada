#ifndef DATASERIALIZER_H
#define DATASERIALIZER_H
#include "dataoperation.h"
#include "qdatastream.h"

class DataSerializer: public DataOperation
{
    QDataStream stream;
public:
    DataSerializer();
    QByteArray operation(const QByteArray&) override;
};

#endif // DATASERIALIZER_H
