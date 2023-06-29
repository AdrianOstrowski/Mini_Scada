#include "dataserializer.h"

///
/// \brief DataSerializer::DataSerializer
///DataSerializer constructor
DataSerializer::DataSerializer()
{

}

///
/// \brief DataSerializer::operation
/// \param data Data to serialize
/// \return Serialized data
///
QByteArray DataSerializer::operation(const QByteArray &data)
{
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << data;
    qDebug() << "Data series is ready";
    return serializedData;
}
