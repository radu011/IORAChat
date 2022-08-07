#include "mainwindow.h"

#include <QApplication>
#include "tcpclient.h"

#define ip_server "172.0.0.1"
#define port_server 1737

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TCPClient& tcp = TCPClient::getInstance();
    tcp.start(ip_server, port_server);

    MainWindow w;
    w.show();

    return a.exec();
}
