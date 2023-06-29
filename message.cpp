#include "message.h"

///
/// \brief Message::Message
///Message constructor
Message::Message()
{

}

///
/// \brief Message::generate
/// \param text Message text
/// \param end not used
/// \param number not used
/// \return Generated message
///
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
