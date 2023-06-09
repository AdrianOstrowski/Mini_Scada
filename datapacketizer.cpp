 #include "datapacketizer.h"

DataPacketizer::DataPacketizer()
{

}

QList<QByteArray> DataPacketizer::packetize(const QByteArray &data)
{
    int packetSize = 3;
    QList<QByteArray> packets;
    int offset = 1;
    while (offset < data.size()) {
        QByteArray packet = data.mid(offset, packetSize);
        packets.append(packet);
        offset += packet.size();
        qDebug() <<"Paczka nr: " << data.size() << "gotowa";
    }
    return packets;
}
