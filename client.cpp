#include "client.h"

Client::Client(QString ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;
    this->socket = new QTcpSocket;
    this->clientWind = new ClientWindow;
    QObject::connect(this->clientWind, SIGNAL(connectToServer()), this, SLOT(connect_to_server()));
    QObject::connect(this->clientWind, SIGNAL(disconnectFromServer()), this, SLOT(disconnect_from_server()));
    QObject::connect(this, SIGNAL(disconnected()), this->clientWind, SLOT(change_status_to_disconnected()));
    QObject::connect(this, SIGNAL(connected()), this->clientWind, SLOT(change_status_to_connected()));
}

Client::~Client()
{
    delete socket;
    delete clientWind;
}

bool Client::start()
{
    this->clientWind->setWindowTitle("Klient");
    this->clientWind->show();
    if(socket->state() != QAbstractSocket::ConnectedState)
    {
       emit disconnected();
    }
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
       emit connected();
    } else {
        qDebug() << "Klient nie jest podłączony do serwera.";
        return 1;
    }

    return 0;
}

bool Client::disconnect_from_server()
{
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->disconnectFromHost();
        qDebug() << "Klient został rozłączony z serweren";
        emit disconnected();
        return 0;
    }else
    {
        qDebug() << "Klient nie był połączony z serwerem";
        return 0;
    }
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
