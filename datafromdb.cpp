 #include "datafromdb.h"

DataFromDB::DataFromDB()
{

}

QByteArray DataFromDB::generate(QString text, QString end, QString number)
{
    //TODO
    QByteArray data;
    data.append(text.toLocal8Bit());
    qDebug() << "Data from database is ready";
    return data;
}
