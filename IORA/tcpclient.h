#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>

#include "serverRequestTypes.h"
#include "messageencode.h"
#include "messagedecoder.h"

class QTcpSocket;
class Chat;

class TCPClient : public QObject
{
    Q_OBJECT
public:
    static TCPClient& getInstance();
    static void destroyInstance();

    void start(QString ip, unsigned short port);
    void stop();

    QString getData(QString requestMessage);

    static void setUsername(QString str) { TCPClient::clientUsername = str; }
    static QString getUsername() { return TCPClient::clientUsername; }

signals:
    void realTimeInformation(QString message);

private slots:
    QString readyRead();
    void clientDisconnected();

private:
    static TCPClient* instance;
    QTcpSocket* socket;
    static QString clientUsername;
    static QString readString;
    static bool readFlag;

    explicit TCPClient(QObject *parent = nullptr);
};

#endif // TCPCLIENT_H
