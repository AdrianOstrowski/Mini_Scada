#ifndef DATAFROMDB_H
#define DATAFROMDB_H
#include "datagenerator.h"

class DataFromDB: public DataGenerator
{
public:
    DataFromDB();
    ~DataFromDB();
    QByteArray generate(QString, QString, QString) override;
};

#endif // DATAFROMDB_H
