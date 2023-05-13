#include "client.h"

Client::Client(QString ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;
    this->socket = new QTcpSocket;
}

Client::~Client()
{
    delete socket;
}


bool Client::start()
{    
    return 0;
}

bool Client::connect_to_server()
{
    this->socket->connectToHost(this->ip, this->port);
    if (socket->waitForConnected())
    {
            qDebug() << "Połączono z serwerem.";

    } else {
            qDebug() << "Błąd przy połączeniu z serwerem:" << socket->errorString();
            return 1;
    }

    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Klient jest podłączony do serwera.";

    } else {
        qDebug() << "Klient nie jest podłączony do serwera.";
        return 1;
    }

    return 0;
}

bool Client::disconnect_from_server()
{
    this->socket->disconnectFromHost();
    qDebug() << "Klient został rozłączony z serweren";
    return 0;
}

void Client::send_data(Data data)
{

}

void Client::recv_data()
{

}

void Client::save_data()
{

}

void Client::save_to_clipboard()
{

}
