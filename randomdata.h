#ifndef RANDOMDATA_H
#define RANDOMDATA_H
#include "datagenerator.h"

class RandomData: public DataGenerator
{
public:
    RandomData();
    void generate();
    bool clear();
};

#endif // RANDOMDATA_H
