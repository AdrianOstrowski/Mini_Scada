#include "datadeserializer.h"

DataDeserializer::DataDeserializer()
{

}

QByteArray DataDeserializer::operation(const QByteArray &data)
{
    QByteArray deserializedData;
    QDataStream stream(data);
    stream >> deserializedData;
    qDebug() << "Dane zdeserializowane";
    return deserializedData;
}
