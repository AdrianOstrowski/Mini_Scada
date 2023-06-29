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
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include "datasaver.h"
#include "datadisplayer.h"

class NetworkConnection : public QObject
{
    Q_OBJECT
protected:
    ///
    /// \brief port
    ///Port number
    unsigned short port;
    ///
    /// \brief ip
    ///Ip adress
    QString ip;
    ///
    /// \brief buffer
    ///Buffer to hold data
    DataBuffer buffer;

public:
    NetworkConnection();

public slots:
    ///
    /// \brief start
    /// \return
    ///Virtual function, need to be overrided
    virtual bool start() = 0;
    ////
    /// \brief send_data
    ///Virtual function, need to be overrided
    virtual void send_data(const QByteArray&, const QString&, const QString&) = 0;
    ///
    /// \brief recv_data
    ///Virtual function, need to be overrided
    virtual void recv_data(const QList<QByteArray>&, const QString&, const QString&) = 0;
};

#endif // NETWORKCONNECTION_H
