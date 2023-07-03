#ifndef LINEAR_H
#define LINEAR_H
#include "datagenerator.h"

class Linear : public DataGenerator
{
public:
    Linear();
    QByteArray generate(QString, QString, QString) override;
};

#endif // LINEAR_H
