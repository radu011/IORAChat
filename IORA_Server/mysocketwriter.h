#ifndef MYSOCKETWRITER_H
#define MYSOCKETWRITER_H

#include<QObject>
#include<QTcpSocket>
class MySocketWriter : public QObject
{
    Q_OBJECT

public:
    MySocketWriter(QObject *Parent = 0,QTcpSocket*socket)
        : QObject(Parent)
    {
        // If this is on another thread, connection will be queue
        connect(this, SIGNAL(Write(QByteArray)), socket, SLOT(Write(QBytrArray Data)));
        QByteArray Data;
        // Fill with data

        // An event gets put onto thread 1's event queue after this
        emit Write(Data);
    }

signals:
    void Write(QByteArray Data);
};

#endif // MYSOCKETWRITER_H
