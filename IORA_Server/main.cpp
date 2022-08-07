#include <QCoreApplication>
#include <QSqlQuery>
#include<QtSql>
#include<string>
//#include "tcpserver.h"
#include"qtcpserver.h"
#include "database.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer& myserver=TcpServer::getInstance();
    return a.exec();
}
