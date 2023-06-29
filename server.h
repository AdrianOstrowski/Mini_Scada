 #ifndef SERVER_H
#define SERVER_H

#include "networkconnection.h"
#include "client.h"

class Server : public NetworkConnection
{
   Q_OBJECT
private:
    ///
    /// \brief tcp_server
    ///Server socket
    QTcpServer *tcp_server;
    ///
    /// \brief clients
    ///Clients list
    QList<Client*> clients;  //lista klientów podłączonych do server TODO
public:
    Server(QString, unsigned short);
    ~Server();

public slots:
    bool start() override;
    void send_data(const QByteArray&, const QString&, const QString&) override;
    void recv_data(const QList<QByteArray>&, const QString&, const QString&) override;
    void new_client(Client*);
    bool close();
    QList<QByteArray> get_buffer_data();
    void remove_client(int);

signals:
    ///
    /// \brief new_connection
    ///Signals new client connection
    void new_connection();
    ///
    /// \brief closed
    ///Signals server being closed
    void closed();
};

#endif // SERVER_H
