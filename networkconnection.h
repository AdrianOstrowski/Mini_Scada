#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <string>

class NetworkConnection : QObject
{
private:
    Q_OBJECT
    unsigned short port;
    std::string ip;

public:
    NetworkConnection();
};

#endif // NETWORKCONNECTION_H
