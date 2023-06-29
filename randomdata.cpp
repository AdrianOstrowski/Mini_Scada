#include "randomdata.h"

///
/// \brief RandomData::RandomData
///Random data generatpr constructor
RandomData::RandomData()
{

}

///
/// \brief RandomData::generate
/// \param start Min number
/// \param end Max number
/// \param size Size of number list
/// \return Random data
///
QByteArray RandomData::generate(QString start, QString end, QString size)
{
    QList<int> dataList;
    QByteArray data;
    QRandomGenerator randomGenerator;
    for (int i = 0; i < size.toInt(); ++i) {
        int randomNumber = randomGenerator.bounded(start.toInt(), end.toInt() + 1);
        dataList << randomNumber;
    }

    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);
    foreach (const int value , dataList) {
        stream << value;
    }
    if(dataList.size() > 0)
    {
        qDebug () << "Random data generated";
    }
    return data.toHex();
}
