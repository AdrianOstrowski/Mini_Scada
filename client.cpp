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
    delete displayer;
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
            qDebug() << "Client " << this->id << " received data";
        }
    }else qDebug() << " Client can't receive data when disconnected";
}

void Client::save_data()
{
    DataSaver saver(this->buffer);
    saver.save_data();
}

void Client::save_to_clipboard()
{

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
    if(this->buffer.get_type() != "Message")
    {
        displayer = new DataDisplayer();
        displayer->display_data(this->buffer);
        qDebug() << "Data displayed";
    }
}
