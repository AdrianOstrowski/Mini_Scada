#ifndef DATASAVER_H
#define DATASAVER_H
#include "databuffer.h"
#include <fstream>
#include <QDataStream>

class DataSaver
{
private:
    DataBuffer buffer;
public:
    DataSaver(DataBuffer);
    bool save_data();
};

#endif // DATASAVER_H
