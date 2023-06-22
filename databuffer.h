#ifndef DATABUFFER_H
#define DATABUFFER_H
#include <QByteArray>
#include <QList>
#include <QDebug>

class DataBuffer
{
private:
    QList<QByteArray> buffer;
    QString data_type;
    QString data_name;
public:
    DataBuffer();
    void hold_data(const QByteArray& , const QString&, const QString&);
    QList<QByteArray> read_data();
    void clear();
    QString get_type();
    QString get_name();
};

#endif // DATABUFFER_H
