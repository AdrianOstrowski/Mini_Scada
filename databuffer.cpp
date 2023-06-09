#include "databuffer.h"

DataBuffer::DataBuffer()
{

}

void DataBuffer::hold_data(const QByteArray& data)
{
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
