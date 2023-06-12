#include "databuffer.h"

DataBuffer::DataBuffer()
{

}

void DataBuffer::hold_data(const QByteArray& data , const QString& data_type)
{
    this->data_type = data_type;
    this->buffer.append(data);
}

QByteArray DataBuffer::read_data()
{
    return buffer;
}

void DataBuffer::clear()
{
     this->buffer.clear();
}

QString DataBuffer::get_type()
{
    return this->data_type;
}
