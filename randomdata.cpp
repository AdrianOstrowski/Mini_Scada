#include "randomdata.h"

RandomData::RandomData()
{

}

QByteArray RandomData::generate(QString text1, QString end, QString number)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(text1.toInt(), end.toInt());

    QByteArray data;
    data.reserve(number.toInt() * sizeof(int)); // Rezerwacja miejsca dla danych całkowitoliczbowych

    for (int i = 0; i < number.toInt(); ++i) {
        int randomInt = distribution(gen);
        data.append(reinterpret_cast<const char*>(&randomInt), sizeof(int));
    }

    qDebug() << "Random data generated";
    return data;
}

bool RandomData::clear()
{
    //TODO
    return true;
}
