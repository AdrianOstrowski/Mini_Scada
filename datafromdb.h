#ifndef DATAFROMDB_H
#define DATAFROMDB_H
#include "datagenerator.h"

class DataFromDB: public DataGenerator
{
public:
    DataFromDB();
    ~DataFromDB();
    void generate() override;
    bool clear() override;
};

#endif // DATAFROMDB_H
