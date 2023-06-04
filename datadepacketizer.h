#ifndef DATADEPACKETIZER_H
#define DATADEPACKETIZER_H
#include "dataoperation.h"

class DataDepacketizer
{
public:
    DataDepacketizer();
    QByteArray operation(QList<QByteArray>&);
};

#endif // DATADEPACKETIZER_H
