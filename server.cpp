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
    qDebug() << "Server has been deleted";
}

bool Server::start()
{
    if (!this->tcp_server->listen(QHostAddress::Any, this->port)) {
           qDebug() << "Server can't listen on port: " << this->port;
           return 1;
       }

    qDebug() << "Server is running and listening on port: " << this->port;
    return 0;
}

void Server::send_data(const QByteArray &data, const QString& data_name, const QString& data_type)
{
    if(data.size() > 0 && clients.size() > 0)
    {
        DataSerializer serializer;
        DataPacketizer packetizer;
        QByteArray serializedData = serializer.operation(data);
        QList<QByteArray> packets = packetizer.packetize(serializedData);
        for (QByteArray& packet : packets) {
            this->buffer.hold_data(packet, data_name, data_type);
        }
        qDebug() <<"Data is ready to send";
    }else qDebug() << "No data to send";
}

void Server::recv_data(const QList<QByteArray> &data, const QString &data_name, const QString& data_type)
{
    //TODO
}

void Server::new_client(Client* new_client)
{
    this->clients.append(new_client);
    qDebug() << "New client is connected";
}

bool Server::close()
{
    this->tcp_server->close();
    qDebug() << "Server is closed";
    emit closed();
    return 0;
}

QList<QByteArray> Server::get_buffer_data()
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
    qDebug() << "Client : " << id << " is not on the connections list";
}
