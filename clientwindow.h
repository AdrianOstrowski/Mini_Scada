#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QDialog>

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

private slots:
    void on_connectToServerButton_clicked();
    void on_disconnectFromServerButton_clicked();
    void change_status_to_connected();
    void change_status_to_disconnected();

signals:
    void connectToServer();
    void disconnectFromServer();
private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
