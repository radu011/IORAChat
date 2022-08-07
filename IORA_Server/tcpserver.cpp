#include "tcpserver.h"

TCPServer::TCPServer(QObject*parent):QTcpServer(parent)
{

}
void TCPServer::StartServer()
{
    if(!this->listen(QHostAddress::Any,1737))
    {
        qDebug()<<"Could not start server";
    }
    else{
        qDebug()<<"Listening...";
    }
}
void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<socketDescriptor<<" Connecting...";
    Thread *thread=new Thread(socketDescriptor,this);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}
