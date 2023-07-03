#ifndef SIN_H
#define SIN_H
#include "datagenerator.h"
#include <cmath>

class Sin : public DataGenerator
{
public:
    Sin();
    QByteArray generate(QString, QString, QString) override;
};

#endif // SIN_H
