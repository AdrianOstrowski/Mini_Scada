 #ifndef SERVER_H
#define SERVER_H

#include "networkconnection.h"
#include "client.h"

class Server : public NetworkConnection
{
   Q_OBJECT
private:
    QTcpServer *tcp_server;
    QList<QTcpSocket> clients;  //lista klientów podłączonych do server TODO
public:
    Server(QString, unsigned short);
    ~Server();

public slots:
    bool start() override;
    void send_data() override;
    void recv_data() override;
    void new_client(Client);
    void send_data_to_all();
    bool close();

signals:
    void new_connection();
    void closed();
};

#endif // SERVER_H
