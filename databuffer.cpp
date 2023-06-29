#include "databuffer.h"

///
/// \brief DataBuffer::DataBuffer
///DataBuffer constructor
DataBuffer::DataBuffer()
{

}

///
/// \brief DataBuffer::hold_data
/// \param data Data to be hold in buffer
/// \param name Name of data being hold
/// \param data_type Type of data being hold
///
void DataBuffer::hold_data(const QByteArray& data , const QString& name, const QString& data_type)
{
    this->data_name = name;
    this->data_type = data_type;
    this->buffer.append(data);
}

///
/// \brief DataBuffer::read_data
/// \return Rode data
///
QList<QByteArray> DataBuffer::read_data()
{
    return buffer;
}

///
/// \brief DataBuffer::clear
///Clears buffer
void DataBuffer::clear()
{
    this->buffer.clear();
    qDebug() << "Buffer is now empty";
}

///
/// \brief DataBuffer::get_type
/// \return Type of data hold in buffer
///
QString DataBuffer::get_type()
{
    return this->data_type;
}

///
/// \brief DataBuffer::get_name
/// \return Name of data hold in buffer
///
QString DataBuffer::get_name()
{
    return this->data_name;
}
