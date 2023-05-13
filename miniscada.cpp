#include "miniscada.h"
#include "ui_miniscada.h"

MiniScada::MiniScada(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MiniScada)
{
    ui->setupUi(this);
}

MiniScada::~MiniScada()
{
    delete ui;
    delete server;
}


void MiniScada::on_start_server_clicked()
{
    this->server = new Server("", 12345);
    server->start();
    if(server != nullptr){
        ui->status->setStyleSheet("color: green;");
        ui->status->setText("Activated");
        ui->stop_server->setEnabled(true);
        ui->start_server->setEnabled(false);
    }
}

void MiniScada::on_stop_server_clicked()
{
    this->server->close();
    ui->start_server->setEnabled(true);
    ui->stop_server->setEnabled(false);
    ui->status->setStyleSheet("color: red;");
    ui->status->setText("Deactivated");
}


void MiniScada::on_new_client_clicked()
{
    client = new ClientWindow(this);
    client->setWindowTitle("Klient");
    client->show();

}


void MiniScada::on_pushButton_2_clicked()
{

}


void MiniScada::on_pushButton_3_clicked()
{

}


void MiniScada::on_pushButton_clicked()
{

}

