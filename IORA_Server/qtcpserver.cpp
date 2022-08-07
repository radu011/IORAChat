#include "qtcpserver.h"
#include<decoder.h>
#include"solver.h"
TcpServer*TcpServer::instance=nullptr;
TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    connect(&_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
    if(_server.listen(QHostAddress::Any, 1737)) {
        qInfo() << "Listening ...";
    }
}

void TcpServer::sendMessage(const QString &message)
{
    emit newMessage("Server: " + message.toUtf8());
}
TcpServer& TcpServer::getInstance()
{
    if(instance==nullptr)
    {
        instance=new TcpServer();
    }
    return *instance;

}
void TcpServer::destroyInstance()
{
    if(instance)
    {
        delete []instance;
    }
}
vector<pair<QString,QTcpSocket*>>TcpServer::getUsers()
{
    return _clients;
}
void TcpServer::onNewConnection()
{
    const auto client = _server.nextPendingConnection();
    if(client == nullptr) {
        return;
    }

    qInfo() <<client->socketDescriptor()<<"New client connected.";

    connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected);
}
void TcpServer::adduser(QString&s,QTcpSocket*socket)
{
    _clients.push_back(pair(s,socket));
}
void TcpServer::onReadyRead()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }
    actualsocket=client;
    const auto message = client->readAll();

    emit newMessage(message);
}
void TcpServer::Disconnect(QTcpSocket*socket)
{
    qDebug()<<socket->socketDescriptor()<<" Disconnected";
    for(int i=0;i<(int)_clients.size();i++)
    {
        if(_clients[i].second==socket)
        {
            if(i!=(int)_clients.size()-1){
            for(int j=i;j<(int)_clients.size();j++)
                _clients[j]=_clients[j+1];
            }
            _clients.resize(_clients.size()-1);
            break;
        }
    }
}
void TcpServer::onClientDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<client->socketDescriptor();
    Disconnect(client);
    if(client == nullptr) {
        return;
    }


}

void TcpServer::onNewMessage(const QByteArray &ba)
{
    QString s=ba;
    QString s1,s2,s3,s4;
    Decoder::decode(s,s1,s2,s3,s4);
    Solver::Solve(s1,s2,s3,s4,actualsocket);
}

QString TcpServer::getClientKey(const QTcpSocket *client) const
{
    return client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}
