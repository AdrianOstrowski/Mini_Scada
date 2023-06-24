#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->server_ip->setText("127.0.0.1");
    ui->server_port->setText("12345");
    QObject::connect(this, &QDialog::finished, this, &ClientWindow::closed_window);
}

ClientWindow::~ClientWindow()
{
    qDebug() << "Client window has been closed";
    delete ui;
}

void ClientWindow::on_connectToServerButton_clicked()
{
    emit connect_to_server();
}

void ClientWindow::on_disconnectFromServerButton_clicked()
{
    emit disconnect_from_server();
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

QString ClientWindow::get_ip()
{
    return ui->server_ip->text();
}

unsigned short ClientWindow::get_port()
{
    return ui->server_port->text().toUShort();
}

void ClientWindow::on_saveDataButton_clicked()
{
    emit data_saved();
}

void ClientWindow::closed_window()
{
    emit closed();
}

void ClientWindow::on_displayDataButton_clicked()
{
    emit display_data();
}

void ClientWindow::on_dataDeleteButton_clicked()
{
    emit clear_data();
}

QString ClientWindow::get_line_type()
{
    return ui->lineTypeCombobox->currentText();
}

QString ClientWindow::get_color()
{
    return ui->colorCombobox->currentText();
}

QString ClientWindow::get_line_size()
{
    return ui->lineSizeCombobox->currentText();
}

bool ClientWindow::get_legend()
{
    return ui->legendOnCheckbox->isChecked();
}
