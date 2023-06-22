#include "databuffer.h"

DataBuffer::DataBuffer()
{

}

void DataBuffer::hold_data(const QByteArray& data , const QString& name, const QString& data_type)
{
    this->data_name = name;
    this->data_type = data_type;
    this->buffer.append(data);
}

QList<QByteArray> DataBuffer::read_data()
{
    return buffer;
}

void DataBuffer::clear()
{
    this->buffer.clear();
    qDebug() << "Buffer is now empty";
}

QString DataBuffer::get_type()
{
    return this->data_type;
}

QString DataBuffer::get_name()
{
    return this->data_name;
}
