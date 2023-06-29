#include "datadepacketizer.h"

///
/// \brief DataDepacketizer::DataDepacketizer
///Depacketizer constructor
DataDepacketizer::DataDepacketizer()
{

}

///
/// \brief DataDepacketizer::depacketize
/// \param packets Packets wanted to be unpacked
/// \return Unpackted data
///
QByteArray DataDepacketizer::depacketize(const QList<QByteArray> &packets)
{
    QByteArray data;
    for (int i = 0; i < packets.size(); i++) {
        const QByteArray& packet = packets.at(i);
        data.append(packet);
        qDebug() << "Packet nr: " << (i + 1) << "has been unpacketed";
    }
    return data;
}
