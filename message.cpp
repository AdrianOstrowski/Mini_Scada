#include "message.h"

Message::Message()
{

}

QByteArray Message::generate(QString text, QString end, QString number)
{
    QByteArray data;
    data.append(text.toLocal8Bit());
    qDebug() << "Message generated";
    return data;
}

bool Message::clear()
{
    return true;
}
