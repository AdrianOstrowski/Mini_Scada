 #include "datapacketizer.h"

DataPacketizer::DataPacketizer()
{

}

QList<QByteArray> DataPacketizer::packetize(const QByteArray &data)
{
    int packetSize = 4;
    QList<QByteArray> packets;
    int offset = 4;
    while (offset < data.size()) {
        QByteArray packet = data.mid(offset, packetSize);
        packets.append(packet);
        offset += packet.size();
        qDebug() <<"Paczka nr: " << offset << "gotowa";
    }
    return packets;
}
