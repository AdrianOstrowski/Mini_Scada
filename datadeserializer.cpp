#include "datadeserializer.h"

DataDeserializer::DataDeserializer()
{

}

QByteArray DataDeserializer::operation(QByteArray &data)
{
    QByteArray deserializedData;
    QDataStream stream(data);
    stream >> deserializedData;
    return deserializedData;
}
