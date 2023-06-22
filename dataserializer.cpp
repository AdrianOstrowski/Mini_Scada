#include "dataserializer.h"

DataSerializer::DataSerializer()
{

}

QByteArray DataSerializer::operation(const QByteArray &data)
{
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << data;
    qDebug() << "Data series is ready";
    return serializedData;
}
