#ifndef DATABUFFER_H
#define DATABUFFER_H
#include <QByteArray>
#include "data.h"

class DataBuffer
{
private:
    QByteArray buffer;
    Data data;

public:
    DataBuffer();
    void hold_data();
    QByteArray read_data();
    void clear();
};

#endif // DATABUFFER_H
