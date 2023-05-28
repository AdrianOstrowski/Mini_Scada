#ifndef MESSAGE_H
#define MESSAGE_H
#include "datagenerator.h"

class Message: public DataGenerator
{
public:
    Message();
    QByteArray generate(QString, QString, QString) override;
    bool clear() override;
};

#endif // MESSAGE_H
