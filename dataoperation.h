#pragma once
#ifndef DATAOPERATION_H
#define DATAOPERATION_H
#include "databuffer.h"
#include <QDataStream>
#include <QDebug>

class DataOperation
{
private:
    ///
    /// \brief buffer
    ///Buffer to hold data
    DataBuffer buffer;
public:
    DataOperation();
    ///
    /// \brief operation
    /// \return Changed data
    ///Virtual function, need to be overrided
    virtual QByteArray operation(const QByteArray&) = 0;
};

#endif // DATAOPERATION_H
