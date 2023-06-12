#ifndef DATABUFFER_H
#define DATABUFFER_H
#include <QByteArray>
#include <QList>

class DataBuffer
{
private:
    QByteArray buffer;
    QString data_type;
public:
    DataBuffer();
    void hold_data(const QByteArray& , const QString&);
    QByteArray read_data();
    void clear();
    QString get_type();
};

#endif // DATABUFFER_H
