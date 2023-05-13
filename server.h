 #ifndef SERVER_H
#define SERVER_H

#include "networkconnection.h"

class Server : protected NetworkConnection
{
private:
    unsigned short port;
    QString ip;
    QTcpServer *tcp_server;
    QList<QTcpSocket> clients;

public:
    Server(QString, unsigned short);
    ~Server();

public slots:
    bool start() override;
    void send_data(Data) override;
    void recv_data() override;
    void new_client(QTcpSocket);
    void send_data_to_all(Data);
    bool close();

signals:
    void new_connection();
    bool closed();
};

#endif // SERVER_H
