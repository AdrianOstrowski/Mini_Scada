#include "client.h"

Client::Client(QString ip, unsigned short port, int id)
{
    this->ip = ip;
    this->port = port;
    this->id = id;
    this->socket = new QTcpSocket;
    QObject::connect(&this->clientWind, SIGNAL(connect_to_server()), this, SLOT(connect_to_server()));
    QObject::connect(&this->clientWind, SIGNAL(disconnect_from_server()), this, SLOT(disconnect_from_server()));
    QObject::connect(this, SIGNAL(disconnected()), &this->clientWind, SLOT(change_status_to_disconnected()));
    QObject::connect(this, SIGNAL(connected()), &this->clientWind, SLOT(change_status_to_connected()));
    QObject::connect(this, SIGNAL(server_closing()), &this->clientWind, SLOT(change_status_to_disconnected()));
    QObject::connect(&this->clientWind, SIGNAL(data_saved()), this, SLOT(save_data()));
    QObject::connect(&this->clientWind, SIGNAL(closed()), this, SLOT(on_client_window_closed()));
    QObject::connect(&this->clientWind, SIGNAL(clear_data()), this, SLOT(clear_data()));
    QObject::connect(&this->clientWind, SIGNAL(display_data()), this, SLOT(display_data()));
    this->name = "Klient " + QString::number(this->id) + " : " + this->ip;
}

Client::~Client()
{
    emit closed();
    qDebug() << "Klient o id:" << this->id << " został usunięty";
    delete socket;
//    delete chartView->chart(); // Usunięcie obiektu wykresu
//    delete chartView;
//    delete series;
}

bool Client::start()
{
    QString identificator = QString::number(id);
    this->clientWind.setWindowTitle("Klient " + identificator);
    this->clientWind.show();
    if(socket->state() != QAbstractSocket::ConnectedState)
    {
       emit disconnected();
    }
    return 0;
}

bool Client::connect_to_server()
{
    QString ip = clientWind.get_ip();
    unsigned short port = clientWind.get_port();
    this->socket->connectToHost(ip, port);
    if (socket->waitForConnected())
    {
        qDebug() << "Połączono z serwerem.";
        emit connected();
    } else {
        qDebug() << "Błąd przy połączeniu z serwerem:" << socket->errorString();
        emit disconnected();
        return 1;
    }

    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Klient " << id << " jest podłączony do serwera.";
        emit connected();
    } else {
        qDebug() << "Klient " << id << " nie jest podłączony do serwera.";
        emit disconnected();
        return 1;
    }

    return 0;
}

bool Client::disconnect_from_server()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->disconnectFromHost();
        qDebug() << "Klient " << id << " został rozłączony z serweren";
        emit disconnected();
        return 0;
    }else
    {
        qDebug() << "Klient " << id << " nie był połączony z serwerem";
        emit disconnected();
        return 0;
    }
}

void Client::send_data(const QByteArray &data, const QString &data_name, const QString& data_type)
{
    //TODO
}

void Client::recv_data(const QList<QByteArray> &recv_data, const QString &data_name, const QString &data_type)
{
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        DataDepacketizer depacketizer;
        DataDeserializer deserializer;
        QByteArray deserializedData;
        if (recv_data.size() >= 1) {
            QByteArray receivedPackets = depacketizer.depacketize(recv_data);
            deserializedData = deserializer.operation(receivedPackets);
            this->buffer.hold_data(deserializedData, data_name, data_type);
            qDebug() << "Klient " << this->id << " odtrzymał dane";
        }
    }else qDebug() << " Klient nie może odebrać danych, gdy jest rozłączony";
}

bool Client::save_data()
{
    if(this->buffer.read_data().size() != 0)
    {
        QList<QByteArray> data = buffer.read_data();
        std::string desktopPath = "/Users/Lenovo/Desktop/";
        std::string filename = desktopPath + this->buffer.get_name().toStdString() + ".txt";
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
                    qDebug() << "Odczytana wartość:" << value;
                    QString stringData = QString::number(value);
                    outputFile << stringData.toStdString();
                    outputFile << " ";
                }
                outputFile.close();
                qDebug() << "Plik został zapisany na pulpicie.";
            }
            else if(buffer.get_type() == "Message")
            {
                QString stringData = QString::fromUtf8(textData[i]);
                outputFile << stringData.toStdString();
                outputFile << " ";
                outputFile.close();
                qDebug() << "Plik został zapisany na pulpicie.";
            }
            //kolejne konwersje typów danych
        }
     } else qDebug() << "Nie udało się otworzyć pliku.";
        return 0;
    qDebug() << "Brak danych do zapisu";
    this->buffer.clear();
    return 0;
}

void Client::save_to_clipboard()
{

}

QList<QByteArray> Client::get_buffer_data()
{
    return this->buffer.read_data();
}

int Client::get_id()
{
    return this->id;
}

QString Client::get_ip()
{
    return this->ip;
}

QString Client::get_name()
{
    return this->name;
}

void Client::on_client_window_closed()
{
    delete this;
}

void Client::clear_data()
{
    this->buffer.clear();
}

void Client::display_data()
{
    qDebug() << "Data displayed";
}
