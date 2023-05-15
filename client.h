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

public:
    Client(QString, unsigned short);
    ~Client();

public slots:
    bool start() override;
    void send_data(Data) override;
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
};

#endif // CLIENT_H
