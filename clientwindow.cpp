#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->server_ip->setText("127.0.0.1");
    ui->server_port->setText("12345");
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::on_connectToServerButton_clicked()
{
    emit connectToServer();
}

void ClientWindow::on_disconnectFromServerButton_clicked()
{
    emit disconnectFromServer();
}

void ClientWindow::change_status_to_connected()
{
    ui->connectionStatusLabel->setStyleSheet("color: green;");
    ui->connectionStatusLabel->setText("Connected");
    ui->disconnectFromServerButton->setEnabled(true);
    ui->connectToServerButton->setEnabled(false);
}

void ClientWindow::change_status_to_disconnected()
{
    ui->connectionStatusLabel->setStyleSheet("color: red;");
    ui->connectionStatusLabel->setText("No connection");
    ui->disconnectFromServerButton->setEnabled(false);
    ui->connectToServerButton->setEnabled(true);
}
