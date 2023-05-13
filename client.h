#ifndef CLIENT_H
#define CLIENT_H

#include "networkconnection.h"

class Client: protected NetworkConnection
{
private:
    QTcpSocket *socket;
    QString ip;
    unsigned short port;

public:
    Client(QString, unsigned short);
    ~Client();

public slots:
    bool start() override;
    bool connect_to_server();
    bool disconnect_from_server();
    void send_data(Data) override;
    void recv_data() override;
    void save_data();
    void save_to_clipboard();

signals:
    bool connected();
    bool disconnected();
    bool closed();
    bool data_received();
};

#endif // CLIENT_H
