#include "datadepacketizer.h"

DataDepacketizer::DataDepacketizer()
{

}

QList<QByteArray> DataDepacketizer::depacketize(const QList<QByteArray> &packets)
{
    int i = 1;
    QList<QByteArray> data;
    for (const QByteArray& packet: packets) {
        data.append(packet);
        qDebug() << "Paczka nr: " << i << " rozpakowana";
        i++;
    }
    return data;
}
