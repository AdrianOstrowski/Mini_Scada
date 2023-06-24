#ifndef CLIENT_H
#define CLIENT_H

#include "networkconnection.h"
#include "clientwindow.h"

class Client: public NetworkConnection
{
   Q_OBJECT
private:
    QTcpSocket *socket;
    ClientWindow clientWind;
    int id;
    QString name;
    DataDisplayer *displayer;

public:
    Client(QString, unsigned short, int);
    ~Client();

public slots:
    bool start() override;
    void send_data(const QByteArray&, const QString&, const QString&) override;
    void recv_data(const QList<QByteArray>&, const QString&, const QString&) override;
    bool connect_to_server();
    bool disconnect_from_server();
    void save_data();
    int get_id();
    QString get_ip();
    QString get_name();
    void on_client_window_closed();
    void clear_data();
    void display_data();

signals:
    void connected();
    void disconnected();
    void closed();
    void data_saved();
    void server_closing();
};

#endif // CLIENT_H
