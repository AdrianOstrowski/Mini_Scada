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

void ClientWindow::on_connect_clicked()
{
    if(!this->client->connect_to_server())
    {
        ui->connection_status->setStyleSheet("color: green;");
        ui->connection_status->setText("Connected");
        ui->disconnect->setEnabled(true);
        ui->connect->setEnabled(false);
    }else
    {
        ui->connection_status->setStyleSheet("color: red;");
        ui->connection_status->setText("No connection");
    }
}

void ClientWindow::on_disconnect_clicked()
{
    if(!this->client->disconnect_from_server())
    {
        ui->connection_status->setStyleSheet("color: red;");
        ui->connection_status->setText("No connection");
        ui->disconnect->setEnabled(false);
        ui->connect->setEnabled(true);
    }
}
