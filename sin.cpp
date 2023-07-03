#include "sin.h"

Sin::Sin()
{

}

QByteArray Sin::generate(QString start, QString end, QString fi)
{
    QList<int> dataList;
    QByteArray data;
    double radians = fi.toDouble() * M_PI / 180.0; // zamiana na radiany
    for (int i = start.toInt(); i < end.toInt(); ++i) {
        double angleInRadians = radians * i;
        double number = std::sin(angleInRadians);
        dataList << number;
    }

    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);
    foreach (const int value , dataList) {
        stream << value;
    }
    if(dataList.size() > 0)
    {
        qDebug () << "Linear data generated";
    }
    return data.toHex();
}
