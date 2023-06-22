 #include "datapacketizer.h"

DataPacketizer::DataPacketizer()
{

}

QList<QByteArray> DataPacketizer::packetize(const QByteArray &data)
{
    int packetSize = 4;
    QList<QByteArray> packets;
    int offset = 0;
    while (offset < data.size()) {
        QByteArray packet = data.mid(offset, packetSize);
        packets.append(packet);
        offset += packet.size();
        qDebug() << "Paczka nr:" << packets.size() << "gotowa";
    }
    return packets;
}
