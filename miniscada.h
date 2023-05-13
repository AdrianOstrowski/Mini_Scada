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

    void on_startServerButton_clicked();

    void on_newClientButton_clicked();

    void on_stopServerButton_clicked();

    void on_generateDataButton_clicked();

    void on_sendDataButton_clicked();

    void on_sendToAllButton_clicked();

private:
    Ui::MiniScada *ui;
    ClientWindow *clientWind;
    Server *server;
};
#endif // MINISCADA_H
