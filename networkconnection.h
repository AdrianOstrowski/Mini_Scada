#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <string>
#include "databuffer.h"
#include <QDebug>
#include <QList>
#include <QHostAddress>
#include <QString>
#include "dataserializer.h"
#include "datadeserializer.h"
#include "datapacketizer.h"
#include "datadepacketizer.h"
#include <fstream>
#include <QFile>

class NetworkConnection : public QObject
{
    Q_OBJECT
protected:
    unsigned short port;
    QString ip;
    DataBuffer buffer;

public:
    NetworkConnection();

public slots:
    virtual bool start() = 0;
    virtual void send_data(const QByteArray&, const QString&) = 0;
    virtual void recv_data(const QByteArray&, const QString&) = 0;
    virtual QByteArray get_buffer_data() = 0;
};

#endif // NETWORKCONNECTION_H
