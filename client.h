#ifndef CLIENT_H
#define CLIENT_H

#include "networkconnection.h"

class Client: protected NetworkConnection
{
private:
    QTcpSocket *socket;
    std::string ip;
    unsigned short port;

public:
    Client(std::string, unsigned short);
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
    void connected();
    void disconnected();
    bool closed();
    void data_received();
};

#endif // CLIENT_H
