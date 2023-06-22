#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include "dataoperation.h"
#include <QByteArray>

class DataGenerator
{
public:
    DataGenerator();
    virtual QByteArray generate(QString, QString, QString);
};

#endif // DATAGENERATOR_H
