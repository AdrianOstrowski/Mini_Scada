#ifndef CLIENT_H
#define CLIENT_H

#include "networkconnection.h"

class Client: public NetworkConnection
{
private:
    QTcpSocket socket;

public:
    Client();
    ~Client();

public slots:
    void start() override;
    bool connect_to_server();
    bool disconnect_from_server();
    void send_data() override;
    void recv_data() override;
    void save_data();
    void save_to_clipboard();

signals:
    void connected() override;
    void disconnected() override;
    bool closed() override;
    void data_received();
};

#endif // CLIENT_H
