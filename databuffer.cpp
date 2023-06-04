#include "databuffer.h"

DataBuffer::DataBuffer()
{

}

void DataBuffer::hold_data(QByteArray& data)
{
    this->buffer.append(data);
}

QByteArray DataBuffer::read_data()
{
//TODO
    QByteArray bt;
    return bt;
}

void DataBuffer::clear()
{
     this->buffer.clear();
}
