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
    void send_data(const QByteArray&) override;
    void recv_data(const QByteArray&) override;
    bool connect_to_server();
    bool disconnect_from_server();
    bool save_data();
    void save_to_clipboard();
    QByteArray get_buffer_data() override;
    int get_id();

signals:
    void connected();
    void disconnected();
    void closed();
    void data_saved();
    void server_closing();
};

#endif // CLIENT_H
