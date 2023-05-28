#include "miniscada.h"
#include "ui_miniscada.h"

MiniScada::MiniScada(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MiniScada)
{
    ui->setupUi(this);
    this->ui->ipText->setText("127.0.0.1");
    this->ui->portText->setText("12345");
    this->server = new Server(ui->ipText->text(), ui->portText->text().toUShort());
    QObject::connect(this, SIGNAL(server_closed()), this->server, SLOT(close()));
    QObject::connect(ui->typeBox, SIGNAL(activated(int)), this, SLOT(change_front_with_data_type()));
}

MiniScada::~MiniScada()
{
    delete ui;
    delete server;
    delete client;
}

void MiniScada::on_stopServerButton_clicked()
{
    emit server_closed();
    ui->startServerButton->setEnabled(true);
    ui->stopServerButton->setEnabled(false);
    ui->status->setStyleSheet("color: red;");
    ui->status->setText("Deactivated");
}

void MiniScada::on_newClientButton_clicked()
{
    id++;
    client = new Client(ui->ipText->text(), ui->portText->text().toUShort() , id);
    QObject::connect(this, SIGNAL(server_closed()), client, SLOT(disconnect_from_server()));
    client->start();
}

void MiniScada::on_startServerButton_clicked()
{
    this->server->start();
    ui->status->setStyleSheet("color: green;");
    ui->status->setText("Activated");
    ui->stopServerButton->setEnabled(true);
    ui->startServerButton->setEnabled(false);
}

void MiniScada::on_generateButton_clicked()
{
    if(ui->typeBox->currentText() == "Message")
    {
        Message message;
        data = message.generate(ui->dataText1->text(), "", "");
    }
    else if(ui->typeBox->currentText() == "Random")
    {
        RandomData random;
        data = random.generate(ui->dataText1->text(),ui->dataText2->text(), ui->numberText->text());
    }
    else
    {
        //TODO
        //DataFromDB database;
        //data = database.generate(ui->dataText1->text(), "", "");
    }

}

void MiniScada::change_front_with_data_type()
{
    if(ui->typeBox->currentText() == "Message")
    {
        ui->textLabel->setText("Text: ");
        ui->dataText2->hide();
        ui->endLabel->hide();
        ui->numberLabel->hide();
        ui->numberText->hide();
    }
    else if(ui->typeBox->currentText() == "Random")
    {
        ui->textLabel->setText("Start: ");
        ui->endLabel->setText("End: ");
        ui->endLabel->show();
        ui->dataText2->show();
        ui->numberLabel->show();
        ui->numberText->show();
    }
    else
    {
        ui->textLabel->setText("Link: ");
        ui->dataText2->hide();
        ui->endLabel->hide();
        ui->numberLabel->hide();
        ui->numberText->hide();
    }
}

