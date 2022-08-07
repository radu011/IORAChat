#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include<QDebug>
#include "thread.h"
#include<vector>
using namespace std;
class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);
    void StartServer();
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // TCPSERVER_H
