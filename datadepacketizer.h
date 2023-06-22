#ifndef DATADEPACKETIZER_H
#define DATADEPACKETIZER_H
#include "dataoperation.h"

class DataDepacketizer
{
public:
    DataDepacketizer();
    QByteArray depacketize(const QList<QByteArray>&);
};

#endif // DATADEPACKETIZER_H
