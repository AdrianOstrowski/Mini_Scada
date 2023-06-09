#include "miniscada.h"
#include "ui_miniscada.h"

///
/// \brief MiniScada::MiniScada
/// \param parent Main Wigdet winodw
///Creates MainWindow
MiniScada::MiniScada(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MiniScada)
{
    ui->setupUi(this);
    this->ui->ipText->setText("127.0.0.1");
    this->ui->portText->setText("12345");
    this->server = new Server(ui->ipText->text(), ui->portText->text().toUShort());
    this->ui->dataText1->setText("0");
    this->ui->dataText2->setText("10");
    this->ui->dataNameText->setText("DataName");
    this->ui->dataSizeText->setText("5");
    QObject::connect(this, SIGNAL(server_closed()), this->server, SLOT(close()));
    QObject::connect(ui->typeBox, SIGNAL(activated(int)), this, SLOT(change_front_with_data_type()));
}

///
/// \brief MiniScada::~MiniScada
///Destructor of MainWindow
MiniScada::~MiniScada()
{
    delete ui;
    delete server;

    // Usunięcie obiektów klientów
    foreach (Client* client, clients) {
        delete client;
    }
    clients.clear();

    // Usunięcie elementów z clientListWidget
    while (this->ui->clientListWidget->count() > 0) {
        QListWidgetItem* item = this->ui->clientListWidget->takeItem(0);
        delete item;
    }
    delete client;
    delete signal_mapper;
}

///
/// \brief MiniScada::on_stopServerButton_clicked
///On stop server button client
void MiniScada::on_stopServerButton_clicked()
{
    emit server_closed();
    ui->startServerButton->setEnabled(true);
    ui->stopServerButton->setEnabled(false);
    ui->status->setStyleSheet("color: red;");
    ui->status->setText("Deactivated");
}

///
/// \brief MiniScada::on_newClientButton_clicked
///On new client button cliecked
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

///
/// \brief MiniScada::on_startServerButton_clicked
///On start sever button clicked
void MiniScada::on_startServerButton_clicked()
{
    this->server->start();
    ui->status->setStyleSheet("color: green;");
    ui->status->setText("Activated");
    ui->stopServerButton->setEnabled(true);
    ui->startServerButton->setEnabled(false);
}

///
/// \brief MiniScada::on_generateButton_clicked
///On generate data button clicked
void MiniScada::on_generateButton_clicked()
{
    if(this->server_buffer.read_data().size() > 0)
    {
        this->server_buffer.clear();
        data.clear();
        qDebug() << "Buffer ready for new data";
    }

    if(ui->typeBox->currentText() == "Message")
    {
        Message message;
        data = message.generate(ui->dataText1->text(), "", "");
    }
    else if(ui->typeBox->currentText() == "Random")
    {
        RandomData random;
        data = random.generate(ui->dataText1->text(),ui->dataText2->text(), ui->dataSizeText->text());
    }
    else if (ui->typeBox->currentText() == "Linear")
    {
        Linear linear;
        data = linear.generate(ui->dataText1->text(),ui->dataText2->text(), ui->dataSizeText->text());
    }
    else if (ui->typeBox->currentText() == "Sin(fi*x)")
    {
       Sin sin;
       data = sin.generate(ui->dataText1->text(),ui->dataText2->text(), ui->dataSizeText->text());
    }
    else if (ui->typeBox->currentText() == "x^2")
    {
        XtoSquare xtosq;
        data = xtosq.generate(ui->dataText1->text(),ui->dataText2->text(), ui->dataSizeText->text());
    }
    this->server_buffer.hold_data(data , ui->dataNameText->text() , ui->typeBox->currentText());
}

///
/// \brief MiniScada::change_front_with_data_type
///Changes display of window depends on data type chosen
void MiniScada::change_front_with_data_type()
{
    if(ui->typeBox->currentText() == "Message")
    {
        ui->textLabel->setText("Text: ");
        ui->dataText2->hide();
        ui->endLabel->hide();
        ui->numberLabel->hide();
        ui->dataSizeText->hide();
    }
    else if(ui->typeBox->currentText() == "Random")
    {
        ui->textLabel->setText("Start: ");
        ui->endLabel->setText("End: ");
        ui->numberLabel->setText("Size: ");
        ui->endLabel->show();
        ui->dataText2->show();
        ui->numberLabel->show();
        ui->dataSizeText->show();
    }
    else if(ui->typeBox->currentText() == "Linear")
    {
        ui->textLabel->setText("Start: ");
        ui->endLabel->setText("End: ");
        ui->numberLabel->setText("Const a: ");
        ui->endLabel->show();
        ui->dataText2->show();
        ui->numberLabel->show();
        ui->dataSizeText->show();
    }
    else if(ui->typeBox->currentText() == "Sin(fi*x)")
    {
        ui->textLabel->setText("Start: ");
        ui->endLabel->setText("End: ");
        ui->numberLabel->setText("fi: ");
        ui->endLabel->show();
        ui->dataText2->show();
        ui->numberLabel->show();
        ui->dataSizeText->show();
    }
    else if(ui->typeBox->currentText() == "x^2")
    {
        ui->textLabel->setText("Start: ");
        ui->endLabel->setText("End: ");
        ui->endLabel->show();
        ui->dataText2->show();
        ui->numberLabel->hide();
        ui->dataSizeText->hide();
    }
}

///
/// \brief MiniScada::on_sendButton_clicked
///On send data button clicked
void MiniScada::on_sendButton_clicked()
{
    if(ui->clientListWidget->currentItem())
    {
        QString selectedItem = ui->clientListWidget->currentItem()->text();
        this->server->send_data(data, ui->dataNameText->text(), ui->typeBox->currentText());
        foreach (Client *client, clients) {
            if(client->get_name() == selectedItem)
            {
                client->recv_data(server->get_buffer_data(), ui->dataNameText->text(), ui->typeBox->currentText());
                qDebug() << "Data send to client" << client->get_id();
                break;
            }
        }
    }
    else
    {
        qDebug() << "No client has been chosen";
    }
}

///
/// \brief MiniScada::on_sendToAllButton_clicked
///On send to all clients button clicked
void MiniScada::on_sendToAllButton_clicked()
{
    this->server->send_data(data, ui->dataNameText->text(), ui->typeBox->currentText());
    foreach (Client *client, clients) {
        client->recv_data(server->get_buffer_data(), ui->dataNameText->text(), ui->typeBox->currentText());
        qDebug() << "Data send to clients";
    }
}

///
/// \brief MiniScada::new_client_connected
///Handles new client connection display on Client List
void MiniScada::new_client_connected()
{
    foreach (Client *client, clients) {
        for(int j = 0; j < this->current_clients_names.count(); j++)
        {
            if (client->get_name() == this->current_clients_names.at(j)) {
            // Znaleziono klienta o oczekiwanej nazwie
            this->server->new_client(client);
                for (int k = 0; k < this->ui->clientListWidget->count(); k++)
                {
                    QListWidgetItem* item = this->ui->clientListWidget->item(k);
                    if (item->text() == client->get_name())
                    {
                        item->setForeground(Qt::green);
                        break;
                    }
                 }

            }
        }
    }
    this->current_clients_names.clear();
}

///
/// \brief MiniScada::client_disconnected
///Handles client diconnection display on Client List
void MiniScada::client_disconnected()
{
    foreach (Client *client, clients) {
            for(int j = 0; j < this->current_clients_names.count(); j++)
            {
                if (client->get_name() == this->current_clients_names.at(j)) {
                    // Znaleziono klienta o oczekiwanej nazwie
                    this->server->remove_client(client->get_id());
                    for (int k = 0; k < this->ui->clientListWidget->count(); k++) {
                        QListWidgetItem* item = this->ui->clientListWidget->item(k);
                        if (item->text() == client->get_name()) {
                            item->setForeground(Qt::red);
                            break;
                        }
                    }
                }
            }
        }
        this->current_clients_names.clear();
}

///
/// \brief MiniScada::client_closed
///Handles client closing display on Client List
void MiniScada::client_closed()
{
    foreach (Client *client, clients) {
        for (int j = 0; j < this->current_clients_names.count(); j++) {
            if (client->get_name() == this->current_clients_names.at(j)) {
                // Znaleziono klienta o oczekiwanej nazwie
                clients.removeOne(client);
                for (int k = 0; k < this->ui->clientListWidget->count(); k++) {
                    QListWidgetItem* item = this->ui->clientListWidget->item(k);
                    if (item->text() == client->get_name()) {
                        this->ui->clientListWidget->takeItem(k);
                        break;
                    }
                }
            }
        }
    }
    this->current_clients_names.clear();
}

///
/// \brief MiniScada::current_clients_operations_list
/// \param clientObject Client that changes status
///
void MiniScada::current_clients_operations_list(QObject* clientObject)
{
    Client* client = qobject_cast<Client*>(clientObject);
    if (client)
    {
        QString clientName = client->get_name();
        if (!current_clients_names.contains(clientName))
        {
            this->current_clients_names.append(clientName);
            //qDebug() << "Operacja wykonywana na kliencie o id: " << client->get_id();
        }
        else
        {
            qDebug() << "Client " << clientName << " already handled.";
        }
    }
}
