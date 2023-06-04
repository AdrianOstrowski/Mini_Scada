 #include "datapacketizer.h"

DataPacketizer::DataPacketizer()
{

}

QList<QByteArray> DataPacketizer::operation(QByteArray &data)
{
    int packetSize = 3;
    QList<QByteArray> packets;
    int offset = 0;
    while (offset < data.size()) {
        QByteArray packet = data.mid(offset, packetSize);
        packets.append(packet);
        offset += packet.size();
    }
    return packets;
}
