#ifndef DATADESERIALIZER_H
#define DATADESERIALIZER_H
#include "dataoperation.h"
#include "QDataStream"

class DataDeserializer: public DataOperation
{
private:
    QDataStream stream;
public:
    DataDeserializer();
    QByteArray operation(QByteArray&) override;
};

#endif // DATADESERIALIZER_H
