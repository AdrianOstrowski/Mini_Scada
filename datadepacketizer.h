#ifndef DATADEPACKETIZER_H
#define DATADEPACKETIZER_H
#include "dataoperation.h"

class DataDepacketizer: public DataOperation
{
public:
    DataDepacketizer();
    QByteArray operation() override;
};

#endif // DATADEPACKETIZER_H
