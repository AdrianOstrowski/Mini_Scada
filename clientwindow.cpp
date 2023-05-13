#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    this->client = new Client("127.0.0.1", 12345);
}

ClientWindow::~ClientWindow()
{
    delete ui;
    delete client;
}

void ClientWindow::on_clientConnectButton_clicked()
{
    if(!this->client->connect_to_server())
      {
          ui->connectionStatusLabel->setStyleSheet("color: green;");
          ui->connectionStatusLabel->setText("Connected");
          ui->clientDisconnectButton->setEnabled(true);
          ui->clientConnectButton->setEnabled(false);
      }else
      {
          ui->connectionStatusLabel->setStyleSheet("color: red;");
          ui->connectionStatusLabel->setText("No connection");
      }
}


void ClientWindow::on_clientDisconnectButton_clicked()
{
    if(!this->client->disconnect_from_server())
        {
            ui->connectionStatusLabel->setStyleSheet("color: red;");
            ui->connectionStatusLabel->setText("No connection");
            ui->clientDisconnectButton->setEnabled(false);
            ui->clientConnectButton->setEnabled(true);
        }
}

