#ifndef DATAPACKETIZER_H
#define DATAPACKETIZER_H
#include "dataoperation.h"

class DataPacketizer: public DataOperation
{
public:
    DataPacketizer();
    QByteArray operation() override;
};

#endif // DATAPACKETIZER_H
