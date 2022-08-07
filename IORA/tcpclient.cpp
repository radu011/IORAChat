#include "tcpclient.h"
#include "QTcpSocket"
#include "QDebug"
#include "QMessageBox"
#include "QStringList"

TCPClient* TCPClient::instance = nullptr;
QString TCPClient::clientUsername;
QString TCPClient::readString;
bool TCPClient::readFlag = false;

TCPClient::TCPClient(QObject *parent)
    : QObject{parent}
{

}

QString TCPClient::readyRead()
{
    QByteArray message;
    message = socket->readAll();

    QStringList tokens = QString(message).split("|");
    if(tokens[0].toUInt() < 100)
    {
        TCPClient::readFlag = true;
        TCPClient::readString = QString(message);
    }else
    {
        emit this->realTimeInformation(QString(message));
    }

    return QString(message);
}

QString TCPClient::getData(QString requestMessage)
{
    if(socket->isWritable())
    {
        qDebug() << "request message: " << requestMessage;
        QByteArray msg = requestMessage.toUtf8();
        socket->write(msg);
        socket->waitForBytesWritten(1000);
    }
    while(TCPClient::readFlag == false)
    {
        socket->waitForReadyRead(5000);
    }
    QString msg = TCPClient::readString;
    TCPClient::readFlag = false;

    qDebug() << "answer message: " << msg;
    return msg;
}

void TCPClient::start(QString ip, unsigned short port)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

    socket->connectToHost(ip, port);
    if (socket->waitForConnected(3000))
    {
        qDebug() << "Connected...";
    }
    else
    {
        qDebug() << "Connection to server failed...";
        QMessageBox endMessage;
        endMessage.setIcon(QMessageBox::Critical);
        endMessage.setText("Can't connect to server...");
        endMessage.setInformativeText("Application will close. Press button.");
        endMessage.setStandardButtons(QMessageBox::Close);
        endMessage.setDefaultButton(QMessageBox::Close);

        endMessage.exec();
        exit(0);
    }
}

void TCPClient::clientDisconnected()
{
    this->stop();
    QMessageBox::warning(nullptr, "Server connection failed", "The server is no longer available");
    exit(0);
}

void TCPClient::stop()
{
    if (this->socket->isOpen())
    {
        this->socket->close();
    }
    qDebug() << "Socket closed...";
}

TCPClient& TCPClient::getInstance()
{
    if( TCPClient::instance == nullptr )
    {
        TCPClient::instance = new TCPClient;
    }
    return *TCPClient::instance;
}

void TCPClient::destroyInstance()
{
    if( TCPClient::instance != nullptr )
    {
        delete TCPClient::instance;
    }
    TCPClient::instance = nullptr;
}
