#ifndef DATAPACKETIZER_H
#define DATAPACKETIZER_H
#include "dataoperation.h"

class DataPacketizer
{
public:
    DataPacketizer();
    QList<QByteArray> packetize(const QByteArray&);
};

#endif // DATAPACKETIZER_H
