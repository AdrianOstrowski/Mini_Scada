#include "client.h"

Client::Client(QString ip, unsigned short port, int id)
{
    this->ip = ip;
    this->port = port;
    this->id = id;
    this->socket = new QTcpSocket;
    this->clientWind = new ClientWindow;
    QObject::connect(this->clientWind, SIGNAL(connect_to_server()), this, SLOT(connect_to_server()));
    QObject::connect(this->clientWind, SIGNAL(disconnect_from_server()), this, SLOT(disconnect_from_server()));
    QObject::connect(this, SIGNAL(disconnected()), this->clientWind, SLOT(change_status_to_disconnected()));
    QObject::connect(this, SIGNAL(connected()), this->clientWind, SLOT(change_status_to_connected()));
    QObject::connect(this, SIGNAL(server_closing()), this->clientWind, SLOT(change_status_to_disconnected()));
    QObject::connect(this->clientWind, SIGNAL(data_saved()), this, SLOT(save_data()));
}

Client::~Client()
{
    delete socket;
    emit closed();
    delete clientWind;
}

bool Client::start()
{
    QString identificator = QString::number(id);
    this->clientWind->setWindowTitle("Klient " + identificator);
    this->clientWind->show();
    if(socket->state() != QAbstractSocket::ConnectedState)
    {
       emit disconnected();
    }
    return 0;
}

bool Client::connect_to_server()
{
    QString ip = clientWind->get_ip();
    unsigned short port = clientWind->get_port();
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

void Client::send_data(const QByteArray &data)
{
    //TODO
}

void Client::recv_data(const QByteArray &recv_data)
{
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        DataDepacketizer depacketizer;
        DataDeserializer deserializer;
        buffer.hold_data(recv_data);
        QList<QByteArray> data;
        data.append(buffer.read_data());
        if (buffer.read_data().size() >= 3) {
            QList<QByteArray> receivedPackets = depacketizer.depacketize(data);
            for (QByteArray& packet : receivedPackets) {
                QByteArray deserializedData = deserializer.operation(packet);
                this->buffer.hold_data(deserializedData);
            }
        }
    }else qDebug() << " Klient nie może odebrać danych, gdy jest rozłączony";
}

bool Client::save_data()
{
    if(this->buffer.read_data().size() != 0)
    {
        std::string desktopPath = "/Users/Lenovo/Desktop/";
        std::string filename = desktopPath + "output.txt";
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << buffer.read_data().toStdString();
            outputFile << "Inne linie tekstu.";
            outputFile.close();
            qDebug() << "Plik został zapisany na pulpicie.";
        } else {
            qDebug() << "Nie udało się otworzyć pliku.";
        }
        return 0;
    }else qDebug() << "Brak danych do zapisu";
    this->buffer.clear();
    return 0;
}

void Client::save_to_clipboard()
{

}

QByteArray Client::get_buffer_data()
{
    return this->buffer.read_data();
}

int Client::get_id()
{
    return this->id;
}
