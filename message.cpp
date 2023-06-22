#include "message.h"

Message::Message()
{

}

QByteArray Message::generate(QString text, QString end, QString number)
{
    QByteArray data;
    data.append(text.toUtf8());
    if(data.size() > 0)
    {
        qDebug() << "Message generated";
    }

    return data.toHex();
}
