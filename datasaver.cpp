#include "datasaver.h"

DataSaver::DataSaver(DataBuffer buffer)
{
    this->buffer = buffer;
}

bool DataSaver::save_data()
{
    if(buffer.read_data().size() != 0)
    {
        QList<QByteArray> data = buffer.read_data();
        std::string desktopPath = "/Users/Lenovo/Desktop/";
        std::string filename = desktopPath + buffer.get_name().toStdString() + ".txt";
        std::ofstream outputFile(filename);
        QList<QByteArray> textData;
        for(int i = 0; i <data.size(); i++)
        {
            textData.append(QByteArray::fromHex(data[i]));
            qDebug() << "textData = " << textData;
            if(buffer.get_type() == "Random")
            {
                QDataStream stream(textData[i]);
                stream.setByteOrder(QDataStream::BigEndian); // Jeśli dane są w formacie Big Endian
                int value = 0;
                while (!stream.atEnd())
                {
                    stream >> value;
                    qDebug() << "Value: " << value;
                    QString stringData = QString::number(value);
                    outputFile << stringData.toStdString();
                    outputFile << " ";
                }
                outputFile.close();
                qDebug() << "File has been saved on Desktop.";
            }
            else if(buffer.get_type() == "Message")
            {
                QString stringData = QString::fromUtf8(textData[i]);
                outputFile << stringData.toStdString();
                outputFile << " ";
                outputFile.close();
                qDebug() << "File has been saved on Desktop.";
            }
            //kolejne konwersje typów danych
        }
     } else qDebug() << "File can't be created.";
        return 0;
    qDebug() << "No data to save";
    buffer.clear();
    return 0;
}
