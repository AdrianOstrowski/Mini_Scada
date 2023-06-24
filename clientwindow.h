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
    void connect_to_server();
    void disconnect_from_server();
    void data_saved();
    void data_saved_to_clipboard();
    void closed();
    void display_data();
    void clear_data();

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
