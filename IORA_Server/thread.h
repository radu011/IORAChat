#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QObject>
#include<QTcpSocket>
#include<QDebug>
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(int ID,QObject*parent=0);
    void run();
    int getdescriptor(){return this->socketDescriptor;}
    QTcpSocket* getsocket(){return this->socket;}
    void setdescriptor(int descriptor){this->socketDescriptor=descriptor;}
    void setsocket(QTcpSocket*soc){this->socket=soc;}
signals:
    void error(QTcpSocket::SocketError socketerror);
    //void ToWrite(QByteArray q);
public slots:
    void readyRead();
    void disconnected();
private:
       QTcpSocket*socket;
       int socketDescriptor;
       void Solve(QString& s1,QString& s2,QString& s3,QString& s4);
};

#endif // THREAD_H
