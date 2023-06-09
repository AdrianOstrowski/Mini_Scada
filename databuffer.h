#ifndef DATABUFFER_H
#define DATABUFFER_H
#include <QByteArray>
#include <QList>

class DataBuffer
{
private:
    QByteArray buffer;
public:
    DataBuffer();
    void hold_data(const QByteArray&);
    QByteArray read_data();
    void clear();
};

#endif // DATABUFFER_H
