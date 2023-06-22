#include "randomdata.h"

RandomData::RandomData()
{

}

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
        qDebug() << data.toHex();
    }
    qDebug () << "Losowe dane wygenerowane";
    return data.toHex();
}
