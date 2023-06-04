#include "datadepacketizer.h"

DataDepacketizer::DataDepacketizer()
{

}

QByteArray DataDepacketizer::operation(QList<QByteArray> &packets)
{
    QByteArray data;
    for (QByteArray& packet: packets) {
        data.append(packet);
    }
    return data;
}
