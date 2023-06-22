 #ifndef SERVER_H
#define SERVER_H

#include "networkconnection.h"
#include "client.h"

class Server : public NetworkConnection
{
   Q_OBJECT
private:
    QTcpServer *tcp_server;
    QList<Client*> clients;  //lista klientów podłączonych do server TODO
public:
    Server(QString, unsigned short);
    ~Server();

public slots:
    bool start() override;
    void send_data(const QByteArray&, const QString&, const QString&) override;
    void recv_data(const QList<QByteArray>&, const QString&, const QString&) override;
    void new_client(Client*);
    void send_data_to_all();
    bool close();
    QList<QByteArray> get_buffer_data() override;
    void remove_client(int);

signals:
    void new_connection();
    void closed();
};

#endif // SERVER_H
