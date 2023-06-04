#include "server.h"

Server::Server(QString ip, unsigned short port)
{
    this->tcp_server = new QTcpServer();
    this->ip = ip;
    this->port = port;
}

Server::~Server()
{
    delete tcp_server;
    qDebug() << "Serwer został usunięty";
}

bool Server::start()
{
    if (!this->tcp_server->listen(QHostAddress::Any, this->port)) {
           qDebug() << "Serwer nie może nasłuchiwać na porcie: " << this->port;
           return 1;
       }

    qDebug() << "Serwer jest uruchomiony i nasłuchuje na porcie: " << this->port;
    return 0;
}

void Server::send_data()
{

}

void Server::recv_data()
{

}

void Server::new_client(Client* new_client)
{
    this->clients.push_back(new_client);
    qDebug() << "Nowy Klient połącony";
}

void Server::send_data_to_all()
{

}

bool Server::close()
{
    this->tcp_server->close();
    qDebug() << "Serwer został zamknięty";
    emit closed();
    return 0;
}
