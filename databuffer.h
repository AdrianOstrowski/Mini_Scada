#ifndef DATABUFFER_H
#define DATABUFFER_H
#include <QByteArray>
#include <QList>
#include <QDebug>

class DataBuffer
{
private:
    ///
    /// \brief buffer
    ///Data hold in buffer
    QList<QByteArray> buffer;
    ///
    /// \brief data_type
    ///Data type hold in buffer
    QString data_type;
    ///
    /// \brief data_name
    ///Data name hold in buffer
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
