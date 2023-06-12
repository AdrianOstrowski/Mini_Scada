#include "message.h"

Message::Message()
{

}

QByteArray Message::generate(QString text, QString end, QString number)
{
    QByteArray data;
    data.append(text.toUtf8());
    qDebug() << "Message generated";
    return data.toHex();
}

bool Message::clear()
{
    return true;
}
