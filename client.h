#ifndef CLIENT_H
#define CLIENT_H

#include "networkconnection.h"
#include "clientwindow.h"

class Client: public NetworkConnection
{
   Q_OBJECT
private:
    QTcpSocket *socket;
    ClientWindow *clientWind;
    int id;

public:
    Client(QString, unsigned short, int);
    ~Client();

public slots:
    bool start() override;
    void send_data() override;
    void recv_data() override;
    bool connect_to_server();
    bool disconnect_from_server();
    void save_data();
    void save_to_clipboard();

signals:
    void connected();
    void disconnected();
    void closed();
    void data_received();
    void server_closing();
};

#endif // CLIENT_H
