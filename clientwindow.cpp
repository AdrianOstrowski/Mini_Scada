#include "clientwindow.h"
#include "ui_clientwindow.h"

///
/// \brief ClientWindow::ClientWindow
/// ClientWindow constructor
/// \param parent QDialog type window
///
ClientWindow::ClientWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);
    ui->server_ip->setText("127.0.0.1");
    ui->server_port->setText("12345");
    QObject::connect(this, &QDialog::finished, this, &ClientWindow::closed_window);
}

///
/// \brief ClientWindow::~ClientWindow
///ClientWindow destructor
ClientWindow::~ClientWindow()
{
    qDebug() << "Client window has been closed";
    delete ui;
}

///
/// \brief ClientWindow::on_connectToServerButton_clicked
///Emits signal about connect button being clicked
void ClientWindow::on_connectToServerButton_clicked()
{
    emit connect_to_server();
}

///
/// \brief ClientWindow::on_disconnectFromServerButton_clicked
///Emits signal about disconecct button being clicked
void ClientWindow::on_disconnectFromServerButton_clicked()
{
    emit disconnect_from_server();
}

///
/// \brief ClientWindow::change_status_to_connected
///Changes display of status on GUI to connected
void ClientWindow::change_status_to_connected()
{
    ui->connectionStatusLabel->setStyleSheet("color: green;");
    ui->connectionStatusLabel->setText("Connected");
    ui->disconnectFromServerButton->setEnabled(true);
    ui->connectToServerButton->setEnabled(false);
}

///
/// \brief ClientWindow::change_status_to_disconnected
///Changes display of status on GUI to disconnected
void ClientWindow::change_status_to_disconnected()
{
    ui->connectionStatusLabel->setStyleSheet("color: red;");
    ui->connectionStatusLabel->setText("No connection");
    ui->disconnectFromServerButton->setEnabled(false);
    ui->connectToServerButton->setEnabled(true);
}

///
/// \brief ClientWindow::get_ip
/// \return Ip wrote in GUI
///
QString ClientWindow::get_ip()
{
    return ui->server_ip->text();
}

///
/// \brief ClientWindow::get_port
/// \return Port wrote in GUI
///
unsigned short ClientWindow::get_port()
{
    return ui->server_port->text().toUShort();
}

///
/// \brief ClientWindow::on_saveDataButton_clicked
///Emits signal about save button being clicked
void ClientWindow::on_saveDataButton_clicked()
{
    emit data_saved();
}

///
/// \brief ClientWindow::closed_window
///Emits signal about window being closed
void ClientWindow::closed_window()
{
    emit closed();
}

///
/// \brief ClientWindow::on_displayDataButton_clicked
///Emits signal about display button being clicked
void ClientWindow::on_displayDataButton_clicked()
{
    emit display_data();
}

///
/// \brief ClientWindow::on_dataDeleteButton_clicked
///Emits signal about delete button being clicked
void ClientWindow::on_dataDeleteButton_clicked()
{
    emit clear_data();
}

///
/// \brief ClientWindow::get_line_type
/// \return Type of line to display data
///
QString ClientWindow::get_line_type()
{
    return ui->lineTypeCombobox->currentText();
}

///
/// \brief ClientWindow::get_color
/// \return Color of line to display data
///
QString ClientWindow::get_color()
{
    return ui->colorCombobox->currentText();
}

///
/// \brief ClientWindow::get_line_size
/// \return Size of line to display data
///
QString ClientWindow::get_line_size()
{
    return ui->lineSizeCombobox->currentText();
}

///
/// \brief ClientWindow::get_legend
/// \return State of checkbox legend required to display data
///
bool ClientWindow::get_legend()
{
    return ui->legendOnCheckbox->isChecked();
}
