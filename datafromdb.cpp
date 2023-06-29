#include "datafromdb.h"

///
/// \brief DataFromDB::DataFromDB
///Data generator constructor
DataFromDB::DataFromDB()
{

}

///
/// \brief DataFromDB::generate
/// \param text
/// \param end
/// \param number
/// \return
///
QByteArray DataFromDB::generate(QString text, QString end, QString number)
{
    //TODO
    QByteArray data;
    data.append(text.toLocal8Bit());
    qDebug() << "Data from database is ready";
    return data;
}
