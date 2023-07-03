#ifndef XTOSQUARE_H
#define XTOSQUARE_H
#include "datagenerator.h"

class XtoSquare : public DataGenerator
{
public:
    XtoSquare();
    QByteArray generate(QString, QString, QString) override;
};

#endif // XTOSQUARE_H
