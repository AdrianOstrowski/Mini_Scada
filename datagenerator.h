#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include "dataoperation.h"
#include "data.h"

class DataGenerator: public DataOperation
{
private:
    Data generated_data();
public:
    DataGenerator();
    Data generate();
    bool clear();
};

#endif // DATAGENERATOR_H
