#include "client.h"

///
/// \brief Client::Client
/// Client constructor
/// \param ip Client ip adress
/// \param port Client port number
/// \param id This is unique identificator for client
///
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
///
/// \brief Client::~Client
/// Client destructor
///
Client::~Client()
{
    emit closed();
    qDebug() << "Client " << this->id << " has been deleted";
    delete socket;
    delete displayer;
}

///
/// \brief Client::start
/// Handles start of client window
/// \return
///
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

///
/// \brief Client::connect_to_server
/// Handles client connection to server
/// \return Returns status of connection process
///
bool Client::connect_to_server()
{
    QString ip = clientWind.get_ip();
    unsigned short port = clientWind.get_port();
    this->socket->connectToHost(ip, port);
    if (socket->waitForConnected())
    {
        qDebug() << "Connected to server.";
        emit connected();
    } else {
        qDebug() << "Error with connection: " << socket->errorString();
        emit disconnected();
        return 1;
    }

    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Client " << id << " is connected to the server.";
        emit connected();
    } else {
        qDebug() << "Client " << id << " is not connected to the server.";
        emit disconnected();
        return 1;
    }

    return 0;
}

///
/// \brief Client::disconnect_from_server
/// Handles disconnection client from server
/// \return Returns status of disconnection process
///
bool Client::disconnect_from_server()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        this->socket->disconnectFromHost();
        qDebug() << "Client " << id << " has been disconnected";
        emit disconnected();
        return 0;
    }else
    {
        qDebug() << "Client " << id << " was not connected";
        emit disconnected();
        return 0;
    }
    return 1;
}

///
/// \brief Client::send_data
/// This method is not used for client, beacouse only server can send data in this project
/// \param data
/// \param data_name
/// \param data_type
///
void Client::send_data(const QByteArray &data, const QString &data_name, const QString& data_type)
{
    //TODO
}

///
/// \brief Client::recv_data
/// Handles client data receiving from server
/// \param recv_data List of data packets
/// \param data_name Name of data
/// \param data_type Type of data
///
void Client::recv_data(const QList<QByteArray> &recv_data, const QString &data_name, const QString &data_type)
{
    clear_data();
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        DataDepacketizer depacketizer;
        DataDeserializer deserializer;
        QByteArray deserializedData;
        if (recv_data.size() >= 1) {
            QByteArray receivedPackets = depacketizer.depacketize(recv_data);
            deserializedData = deserializer.operation(receivedPackets);
            this->buffer.hold_data(deserializedData, data_name, data_type);
            qDebug() << "Client " << this->id << " received data";
        }
    }else qDebug() << " Client can't receive data when disconnected";
}

///
/// \brief Client::save_data
///This method saves data on Desktop as .txt file
void Client::save_data()
{
    if(this->buffer.read_data().size() > 0)
    {
        DataSaver saver(this->buffer);
        saver.save_data();
    }
    else
    {
        qDebug() << "No data to save";
    }
}

///
/// \brief Client::get_id
/// Gets client identificator
/// \return Returns client id
///
int Client::get_id()
{
    return this->id;
}

///
/// \brief Client::get_ip
/// Gets client ip adress
/// \return Returns client ip adress
///
QString Client::get_ip()
{
    return this->ip;
}

///
/// \brief Client::get_name
/// Gets client name tag
/// \return Returns client name tag
///
QString Client::get_name()
{
    return this->name;
}

///
/// \brief Client::on_client_window_closed
///Deletes client if client window was closed
void Client::on_client_window_closed()
{
    delete this;
}

///
/// \brief Client::clear_data
///Clears client buffer data
void Client::clear_data()
{
    if(this->buffer.read_data().size() > 0)
    {
        this->buffer.clear();
    }
    else
    {
        qDebug() << "No data to delete";
    }
}

///
/// \brief Client::display_data
///Creates data display as widget window
void Client::display_data()
{
    if(this->buffer.read_data().size() > 0 && displayer == NULL)
    {
        displayer = new DataDisplayer();
        displayer->set_parameters(clientWind.get_line_type(), clientWind.get_color(), clientWind.get_line_size(), clientWind.get_legend());
        displayer->display_data(this->buffer);
        qDebug() << "Data displayed";
    }
    else if(this->buffer.read_data().size() == 0)
    {
        qDebug() << "No data to display";
    }
    else
    {
        qDebug() << "Data already displayed";
    }  
    displayer = NULL;
}
