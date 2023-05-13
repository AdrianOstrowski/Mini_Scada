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

private slots:
    void on_start_server_clicked();

    void on_stop_server_clicked();

    void on_new_client_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MiniScada *ui;
    ClientWindow *clientWind;
    Server *server;
};
#endif // MINISCADA_H
