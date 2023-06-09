 #include "datapacketizer.h"

///
/// \brief DataPacketizer::DataPacketizer
///DataPacketizer constructor
DataPacketizer::DataPacketizer()
{

}

///
/// \brief DataPacketizer::packetize
/// \param data Data to packetize
/// \return Packets of data
///
QList<QByteArray> DataPacketizer::packetize(const QByteArray &data)
{
    int packetSize = 4;
    QList<QByteArray> packets;
    int offset = 0;
    while (offset < data.size()) {
        QByteArray packet = data.mid(offset, packetSize);
        packets.append(packet);
        offset += packet.size();
        qDebug() << "Packet nr: " << packets.size() << " is ready";
    }
    return packets;
}
