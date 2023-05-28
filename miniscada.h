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

private slots:

    void on_stopServerButton_clicked();
    void on_newClientButton_clicked();
    void on_startServerButton_clicked();
    void on_generateButton_clicked();
    void change_front_with_data_type();

private:
    Ui::MiniScada *ui;
    int id = 0;
    Client *client;
    Server *server;
    QByteArray data;
};
#endif // MINISCADA_H
