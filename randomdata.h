#ifndef RANDOMDATA_H
#define RANDOMDATA_H
#include "datagenerator.h"
#include <QRandomGenerator>

class RandomData: public DataGenerator
{
public:
    RandomData();
    QByteArray generate(QString, QString, QString);
    bool clear();
};

#endif // RANDOMDATA_H
