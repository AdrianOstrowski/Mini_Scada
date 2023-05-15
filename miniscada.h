#ifndef MINISCADA_H
#define MINISCADA_H

#include <QMainWindow>
#include "networkconnection.h"
#include "clientwindow.h"
#include "server.h"
#include "client.h"

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

private:
    Ui::MiniScada *ui;
    Client *client;
    Server *server;
};
#endif // MINISCADA_H
