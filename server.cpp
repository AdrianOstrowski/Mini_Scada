#include "server.h"

///
/// \brief Server::Server
/// \param ip Server ip adress
/// \param port Server port number
///
Server::Server(QString ip, unsigned short port)
{
    this->tcp_server = new QTcpServer();
    this->ip = ip;
    this->port = port;
}

///
/// \brief Server::~Server
///Server destructor
Server::~Server()
{
    delete tcp_server;
    qDebug() << "Server has been deleted";
}

///
/// \brief Server::start
/// \return Status of server running
/// Server starts to listen for new connections
bool Server::start()
{
    if (!this->tcp_server->listen(QHostAddress::Any, this->port)) {
           qDebug() << "Server can't listen on port: " << this->port;
           return 1;
       }

    qDebug() << "Server is running and listening on port: " << this->port;
    return 0;
}

///
/// \brief Server::send_data
/// \param data Data to be send
/// \param data_name Name of data to send
/// \param data_type Type of data to send
///Server send data to client
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

///
/// \brief Server::recv_data
/// \param data
/// \param data_name
/// \param data_type
///Not used
void Server::recv_data(const QList<QByteArray> &data, const QString &data_name, const QString& data_type)
{
    //TODO
}

///
/// \brief Server::new_client
/// \param new_client
///Adds new client to list of connections
void Server::new_client(Client* new_client)
{
    this->clients.append(new_client);
    qDebug() << "New client is connected";
}

///
/// \brief Server::close
/// \return Returns status of closing
///Closes server
bool Server::close()
{
    this->tcp_server->close();
    qDebug() << "Server is closed";
    emit closed();
    return 0;
}

///
/// \brief Server::get_buffer_data
/// \return Reads data hold in server buffer
///
QList<QByteArray> Server::get_buffer_data()
{
    return this->buffer.read_data();
}

///
/// \brief Server::remove_client
/// \param id Client id
/// Delets client with id from server's clients list
void Server::remove_client(int id)
{
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i]->get_id() == id) {
            clients.removeAt(i);
        }
    }
    qDebug() << "Client : " << id << " is not on the connections list";
}
