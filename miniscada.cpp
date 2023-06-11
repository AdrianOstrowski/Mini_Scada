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
    delete signal_mapper;
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
    this->clients.append(client);
    this->ui->clientListWidget->addItem("Klient " + QString::number(client->get_id()) + " : " + client->get_ip());
    QObject::connect(this, SIGNAL(server_closed()), client, SLOT(disconnect_from_server()));
    client->start();

    signal_mapper = new QSignalMapper(this);
    QObject::connect(client, SIGNAL(connected()), signal_mapper, SLOT(map()));
    QObject::connect(client, SIGNAL(disconnected()), signal_mapper, SLOT(map()));
    QObject::connect(client, SIGNAL(closed()), signal_mapper, SLOT(map()));
    signal_mapper->setMapping(client, client);
    QObject::connect(signal_mapper, SIGNAL(mapped(QObject*)), this, SLOT(current_clients_operations_list(QObject*)));

    QObject::connect(client, SIGNAL(connected()), this, SLOT(new_client_connected()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
    QObject::connect(client, SIGNAL(closed()), this, SLOT(client_closed()));
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
        //DataFromDB database;
        //data = database.generate(ui->dataText1->text(), "", "");
    }
    server_buffer.hold_data(data);
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

void MiniScada::on_sendButton_clicked()
{

}

void MiniScada::on_sendToAllButton_clicked()
{
    this->server->send_data(data);
    foreach (Client *client, clients) {
        client->recv_data(server->get_buffer_data());
    }
}

void MiniScada::new_client_connected()
{
    for (int i = 0; i < clients.count(); i++) {
        Client* client = clients.at(i);
        for(int j = 0; j < this->current_clients_names.count(); j++)
        {
            if (client->get_name() == this->current_clients_names.at(j)) {
                // Znaleziono klienta o oczekiwanej nazwie
                this->server->new_client(client);
                for (int i = 0; i < this->ui->clientListWidget->count(); i++) {
                    QListWidgetItem* item = this->ui->clientListWidget->item(i);
                    if (item->text() == client->get_name()) {
                        item->setForeground(Qt::green);
                    }
                }
            }
            break;
        }
    }
    this->current_clients_names.clear();
}

void MiniScada::client_disconnected()
{
    for (int i = 0; i < clients.count(); i++) {
        Client* client = clients.at(i);
        for(int j = 0; j < this->current_clients_names.count(); j++)
        {
            if (client->get_name() == this->current_clients_names.at(j)) {
                // Znaleziono klienta o oczekiwanej nazwie
                this->server->remove_client(client->get_id());
                for (int i = 0; i < this->ui->clientListWidget->count(); i++) {
                    QListWidgetItem* item = this->ui->clientListWidget->item(i);
                    if (item->text() == client->get_name()) {
                        item->setForeground(Qt::red);
                    }
                }
            }
            break;
        }
    }
    this->current_clients_names.clear();
}


void MiniScada::client_closed()
{
    for (int i = 0; i < clients.count(); i++) {
        Client* client = clients.at(i);
        for(int j = 0; j < this->current_clients_names.count(); j++)
        {
            if (client->get_name() == this->current_clients_names.at(j)) {
                // Znaleziono klienta o oczekiwanej nazwie
                this->clients.removeAt(i);
                for (int i = 0; i < this->ui->clientListWidget->count(); i++) {
                    QListWidgetItem* item = this->ui->clientListWidget->item(i);
                    if (item->text() == client->get_name()) {
                        this->ui->clientListWidget->takeItem(i);
                        delete item;
                    }
                }
            }
            break;
        }
    }
    this->current_clients_names.clear();
}

void MiniScada::current_clients_operations_list(QObject* clientObject)
{
    Client* client = qobject_cast<Client*>(clientObject);
    if (client)
    {
        QString clientName = client->get_name();
        if (!current_clients_names.contains(clientName))
        {
            this->current_clients_names.append(clientName);
            qDebug() << "Operacja wykonywana na kliencie o id: " << client->get_id();
        }
        else
        {
            qDebug() << "Klient o nazwie " << clientName << " już istnieje.";
        }
    }
}
