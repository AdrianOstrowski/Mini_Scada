#include "linear.h"

Linear::Linear()
{

}

QByteArray Linear::generate(QString start, QString end, QString a)
{
    QList<int> dataList;
    QByteArray data;
    for (int i = start.toInt(); i < end.toInt(); ++i) {
        int number = i * a.toInt();
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
