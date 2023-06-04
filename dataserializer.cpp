#include "dataserializer.h"

DataSerializer::DataSerializer()
{

}

QByteArray DataSerializer::operation(QByteArray &data)
{
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << data;
    return serializedData;
}
