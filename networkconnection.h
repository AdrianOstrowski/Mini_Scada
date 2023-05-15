#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <string>
#include "databuffer.h"
#include "dataoperation.h"
#include <QDebug>
#include <QList>
#include <QHostAddress>
#include <QString>

class NetworkConnection : public QObject
{
    Q_OBJECT
protected:
    unsigned short port;
    QString ip;

public:
    NetworkConnection();

public slots:
    virtual bool start() = 0;
    virtual void send_data(Data) = 0;
    virtual void recv_data() = 0;
};

#endif // NETWORKCONNECTION_H
