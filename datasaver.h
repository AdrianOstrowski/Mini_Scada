#ifndef DATASAVER_H
#define DATASAVER_H
#include "databuffer.h"
#include <fstream>
#include <QDataStream>

class DataSaver
{
private:
    ///
    /// \brief buffer
    ///Buffer with data to save
    DataBuffer buffer;
public:
    DataSaver(DataBuffer);
    bool save_data();
};

#endif // DATASAVER_H
