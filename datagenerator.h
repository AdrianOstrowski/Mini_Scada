#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include "dataoperation.h"
#include <QByteArray>

class DataGenerator
{
public:
    DataGenerator();
    ///
    /// \brief generate
    /// \return Generated daa
    ///Virtual function without implementation
    virtual QByteArray generate(QString, QString, QString) = 0;
};

#endif // DATAGENERATOR_H
