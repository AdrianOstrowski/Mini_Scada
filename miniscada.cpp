#include "miniscada.h"
#include "ui_miniscada.h"

MiniScada::MiniScada(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MiniScada)
{
    ui->setupUi(this);
    this->server = new Server("127.0.0.1", 12345);
}

MiniScada::~MiniScada()
{
    delete ui;
    delete server;
    delete clientWind;
}

void MiniScada::on_startServerButton_clicked()
{
    server->start();
    ui->status->setStyleSheet("color: green;");
    ui->status->setText("Activated");
    ui->stopServerButton->setEnabled(true);
    ui->startServerButton->setEnabled(false);
}

void MiniScada::on_newClientButton_clicked()
{
    clientWind = new ClientWindow(this);
    clientWind->setWindowTitle("Klient");
    clientWind->show();
}

void MiniScada::on_stopServerButton_clicked()
{
    this->server->close();
    ui->startServerButton->setEnabled(true);
    ui->stopServerButton->setEnabled(false);
    ui->status->setStyleSheet("color: red;");
    ui->status->setText("Deactivated");
}


void MiniScada::on_generateDataButton_clicked()
{

}


void MiniScada::on_sendDataButton_clicked()
{

}


void MiniScada::on_sendToAllButton_clicked()
{

}

