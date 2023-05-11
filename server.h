#ifndef SERVER_H
#define SERVER_H

#include "networkconnection.h"

class Server : public NetworkConnection
{
private:
    QTcpServer server;
    QList<QTcpSocket> clients;
public:
    Server();
    ~Server();

public slots:
    void start() override;
    void send_data() override;
    void recv_data() override;
    void send_data_to_all();
    bool close();

signals:
    void new_connection();
    bool closed() override;
};

#endif // SERVER_H
