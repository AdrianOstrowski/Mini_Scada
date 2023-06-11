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

void Server::send_data(const QByteArray &data)
{
    if(data.size() > 0 && clients.size() > 0)
    {
        DataSerializer serializer;
        DataPacketizer packetizer;
        QByteArray serializedData = serializer.operation(data);
        QList<QByteArray> packets = packetizer.packetize(serializedData);
        for (QByteArray& packet : packets) {
            this->buffer.hold_data(packet);
        }
        qDebug() <<"Dane gotowe do wysłania";
    }else qDebug() << "Brak danych do wysłania";
}
void Server::recv_data(const QByteArray &data)
{
    //TODO
}

void Server::new_client(Client* new_client)
{
    this->clients.append(new_client);
    qDebug() << "Nowy Klient połączony";
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

QByteArray Server::get_buffer_data()
{
    return this->buffer.read_data();
}

void Server::remove_client(int id)
{
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i]->get_id() == id) {
            clients.removeAt(i);
        }
    }
    qDebug() << "Klient o id: " << id << " nie jest na liście połączeń";
}
