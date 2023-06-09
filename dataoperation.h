#pragma once
#ifndef DATAOPERATION_H
#define DATAOPERATION_H
#include "databuffer.h"
#include <QDataStream>
#include <QDebug>

class DataOperation
{
private:
    DataBuffer buffer;
public:
    DataOperation();
    virtual QByteArray operation(const QByteArray&) = 0;
};

#endif // DATAOPERATION_H
