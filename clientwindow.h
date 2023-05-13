#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>
#include "client.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void on_clientConnectButton_clicked();

    void on_clientDisconnectButton_clicked();

private:
    Ui::ClientWindow *ui;
    Client *client;
};

#endif // CLIENTWINDOW_H
