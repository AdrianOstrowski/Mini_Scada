#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include "dataoperation.h"
#include "data.h"

class DataGenerator
{
private:
    Data generated_data();
public:
    DataGenerator();
    virtual void generate();
    virtual bool clear();
};

#endif // DATAGENERATOR_H
