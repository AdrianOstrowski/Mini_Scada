#include "xtosquare.h"

XtoSquare::XtoSquare()
{

}

QByteArray XtoSquare::generate(QString start, QString end, QString a)
{
    QList<int> dataList;
    QByteArray data;
    for (int i = start.toInt(); i < end.toInt(); ++i) {
        int number = i * i;
        dataList << number;
    }

    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);
    foreach (const int value , dataList) {
        stream << value;
    }
    if(dataList.size() > 0)
    {
        qDebug () << "x^2 data generated";
    }
    return data.toHex();
}
