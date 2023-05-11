#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <string>
#include "data.h"

class NetworkConnection : QObject
{
private:
    Q_OBJECT
    unsigned short port;
    std::string ip;

public:
    NetworkConnection();
    ~NetworkConnection();

public slots:
    virtual void start() = 0;
    virtual void send_data() = 0;
    virtual void recv_data() = 0;

signals:
    virtual void connected() = 0;
    virtual void disconnected() = 0;
    virtual bool closed() = 0;
};

#endif // NETWORKCONNECTION_H
