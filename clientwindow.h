#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>
#include <QtDebug>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
    QString get_ip();
    unsigned short get_port();
    QString get_line_type();
    QString get_color();
    QString get_line_size();
    bool get_legend();

private slots:
    void on_connectToServerButton_clicked();
    void on_disconnectFromServerButton_clicked();
    void change_status_to_connected();
    void change_status_to_disconnected();
    void on_saveDataButton_clicked();
    void closed_window();
    void on_displayDataButton_clicked();
    void on_dataDeleteButton_clicked();

signals:
    ///
    /// \brief connect_to_server
    ///Signal of connect button clicked
    void connect_to_server();
    ///
    /// \brief disconnect_from_server
    ///SIgnal of disconnect button clicked
    void disconnect_from_server();
    ///
    /// \brief data_saved
    ///Signal of data save button clicked
    void data_saved();
    ///
    /// \brief data_saved_to_clipboard
    ///Signal of data save to clipboard clicked
    void data_saved_to_clipboard();
    ///
    /// \brief closed
    ///Signal of client window being closed
    void closed();
    ///
    /// \brief display_data
    ///Signal of display data button clicked
    void display_data();
    ///
    /// \brief clear_data
    ///Signal of clear data button clicked
    void clear_data();

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
