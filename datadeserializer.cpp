#include "datadeserializer.h"

///
/// \brief DataDeserializer::DataDeserializer
///Deserializer constructor
DataDeserializer::DataDeserializer()
{

}

///
/// \brief DataDeserializer::operation
/// \param Data Data wantedd to be deserialized
/// \return Deserialized data
///
QByteArray DataDeserializer::operation(const QByteArray &data)
{
    QByteArray deserializedData;
    QDataStream stream(data);
    stream >> deserializedData;
    qDebug() << "Data is deserialized";
    return deserializedData;
}
