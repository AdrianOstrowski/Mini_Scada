#ifndef MINISCADA_H
#define MINISCADA_H

#include <QMainWindow>
#include "networkconnection.h"
#include "clientwindow.h"
#include "server.h"
#include "client.h"
#include "message.h"
#include "datafromdb.h"
#include "randomdata.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MiniScada; }
QT_END_NAMESPACE

class MiniScada : public QMainWindow
{
    Q_OBJECT

public:
    MiniScada(QWidget *parent = nullptr);
    ~MiniScada();
signals:
    void server_closed();
    void client_connected();

private slots:

    void on_stopServerButton_clicked();
    void on_newClientButton_clicked();
    void on_startServerButton_clicked();
    void on_generateButton_clicked();
    void change_front_with_data_type();
    void on_sendButton_clicked();
    void on_sendToAllButton_clicked();
    void new_client_connected();
    void client_disconnected();

private:
    Ui::MiniScada *ui;
    int id = 0;
    Client *client;
    Server *server;
    QByteArray data;
    DataBuffer server_buffer;
    std::vector<Client*> clients;
};
#endif // MINISCADA_H
