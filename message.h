#ifndef MESSAGE_H
#define MESSAGE_H
#include "datagenerator.h"

class Message: public DataGenerator
{
public:
    Message();
    void generate() override;
    bool clear() override;
};

#endif // MESSAGE_H
