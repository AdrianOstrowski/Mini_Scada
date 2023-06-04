#ifndef DATABUFFER_H
#define DATABUFFER_H
#include <QByteArray>

class DataBuffer
{
private:
    QByteArray buffer;
public:
    DataBuffer();
    void hold_data(QByteArray&);
    QByteArray read_data();
    void clear();
};

#endif // DATABUFFER_H
