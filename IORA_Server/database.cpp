#include "database.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include<algorithm>
#include<time.h>
#include<QtSql>
#include<QString>
#include<QDebug>
#include<string>
#include "file.h"
#include "IMesaj.h"
#include"mesaj.h"
#include"meet.h"
#include"qtcpserver.h"
using namespace std;
Database*Database::instance=nullptr;
void Database::GetCanalefromDB()
{
    ConnectToDB();
    QSqlQuery q;
    if(q.exec("SELECT * FROM Canale")){
    while(q.next())
    {
        Canal*c=new Canal;
        c->setnume(q.value(1).toString().toStdString());
        c->setdescriere(q.value(2).toString().toStdString());
        c->setowner(q.value(3).toString().toStdString());

        QString a("SELECT * from Fisiere WHERE ID_Canal = "+q.value(0).toString());
        QSqlQuery q1;
        if(q1.exec(a)){
        while(q1.next())
        {
            File*f=new File(q1.value(1).toString(),q1.value(2).toString(),q1.value(3).toLongLong());
            c->addfisier(f);
        }
        }
        q1.finish();
        QString b("SELECT u.Username from [Membri_Canale] mc INNER JOIN Utilizatori u on mc.ID_Utilizator=u.ID_Utilizator");
        QSqlQuery q2;
        if(q2.exec(b)){
        while(q2.next())
        {
            c->addmembru(q2.value(0).toString().toStdString());
        }
        }
        q2.finish();
        QString d("SELECT * FROM Mesaje_Canale WHERE ID_Canal ="+q.value(0).toString());
        QSqlQuery q3;
        if(q3.exec(d)){
        while(q3.next())
        {
           if(q3.value(3).toString().toStdString()=="-"){
               IMesaj*m=new Mesaj(q3.value(1).toString(),q3.value(2).toString(),q3.value(4).toLongLong(),IMesaj::Mesaj);
               c->addmesaj(m);
           }
           else
           {
               IMesaj*m=new Meet(q3.value(1).toString(),q3.value(2).toString(),q3.value(3).toString(),q3.value(4).toLongLong(),IMesaj::Meet);
               c->addmesaj(m);
           }
        }
        q3.finish();
        }
        this->canale.push_back(c);
    }
    }
    q.finish();
    Disconnect();
}
void Database::Disconnect()
{
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
}

void Database::destroyInstance()
{
    if(instance!=nullptr){
        instance->Disconnect();
        delete []instance;
    }
}
void Database::ConnectToDB()
{
    QString servername="localhost";
    QString dbname="POO Proiect";
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC");
    db1.setConnectOptions();
    QString dsn=QString("DRIVER={SQL Server Native Client 11.0};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(servername,dbname);
    db1.setDatabaseName(dsn);
    if(db1.open())
        qDebug()<<"Open completed\n";
    else
    {
        qDebug()<<"OPEN FAILED\n"<<db1.lastError().text();
        exit(0);
    }
}
int Database::Login(QString username,QString parola)
{
    ConnectToDB();
    vector<pair<QString,QTcpSocket*>>usersconnected=TcpServer::getInstance().getUsers();
    for(pair<QString,QTcpSocket*>i:usersconnected)
    {
        if(i.first==username)
            return 0;
    }
    QString s("SELECT * FROM Utilizatori WHERE Username = '"+username+"' AND Parola = '"+parola+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        q.finish();
        Disconnect();
        return 1;
    }

    q.finish();
    Disconnect();
    return 0;
}
int Database::Register(QString username,QString parola,QString email)
{
    ConnectToDB();
    QString s("SELECT * FROM Utilizatori WHERE Username = '"+username+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    if(username==""||parola==""||email=="")
        return 0;
    while(q.next())
    {
        return 0;
    }
    QString s1("INSERT INTO Utilizatori(Username,Parola,Email) VALUES ('"+username+"','"+parola+"','"+email+"')");
    q.prepare(s1);
    q.exec();
    q.finish();
    Disconnect();
    return 1;
}
void NewPassword(QString&pass)
{
    srand(time(0));
    for(int i=0;i<8;i++)
        pass.push_back(char(rand()%96+32));
}
int Database::ChangePassword(QString username,QString email)
{
    ConnectToDB();
    QString s("SELECT * FROM Utilizatori WHERE Username = '"+username+"' AND Email = '"+email+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        QString pass="";
        NewPassword(pass);
        QString s1("UPDATE Utilizatori Set Parola='"+pass+"' WHERE Username = '"+username+"' AND "+"Email='"+email+"'");
        q.prepare(s1);
        q.exec();
        return 1;
    }
    q.finish();
    Disconnect();
    return 0;

}
Database&Database::getinstance()
{
    if(instance==nullptr)
    {
        instance=new Database();
    }
    return *instance;
}
vector<QString> Database::GetNotifications(QString username)
{
    ConnectToDB();
    QString s("SELECT Notificare,Timp_incarcare FROM Notificari n INNER JOIN Utilizatori u on n.ID_Destinatar=u.ID_Utilizator WHERE u.Username='"+username+"' ORDER BY Timp_incarcare DESC");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    vector<QString>mesaje;
    while(q.next())
    {
        QString mes;
        QDateTime t=QDateTime::fromSecsSinceEpoch(q.value(1).toLongLong());
        mes="["+t.toString()+"]"+q.value(0).toString();
        mesaje.push_back(mes);
    }

    q.finish();
    Disconnect();
    return mesaje;
}
int Database::CreateChannel(QString ChannelName,QString Descriere,QString Owner)
{
    ConnectToDB();
    QString s("SELECT * FROM Canale Where Nume_Canal='"+ChannelName+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        return 0;
    }
    q.finish();
    s="INSERT INTO Canale(Nume_Canal,Descriere,Owner) VALUES('"+ChannelName+"','"+Descriere+"','"+Owner+"')";
    qDebug()<<s;
    q.prepare(s);
    q.exec();
    q.finish();
    Disconnect();
    return 1;
}
vector<QString> Database::GetChannels(QString username)
{
     ConnectToDB();
     QString s("SELECT Nume_Canal FROM Canale c	inner join Membri_Canale mc on c.ID_Canal=mc.ID_Canal inner join Utilizatori u on u.ID_Utilizator=mc.ID_Utilizator where u.Username='"+username+"'");
     QSqlQuery q;
     q.prepare(s);
     q.exec();
     vector<QString>canale;
     while(q.next())
     {
         canale.push_back(q.value(0).toString());
     }
     Disconnect();
     return canale;
}
vector<QString> Database::GetPosts(QString canal)
{
    ConnectToDB();
    vector<QString>mesaje;
    QString s("SELECT Timp_incarcare,Expeditor,Titlu,Text From Mesaje_Canale mc INNER JOIN Canale c on c.ID_Canal=mc.ID_Canal WHERE Nume_Canal='"+canal+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        IMesaj*m;
        if(q.value(2).toString()=="-"){
            m=new Mesaj(q.value(1).toString(),q.value(3).toString(),q.value(0).toLongLong(),IMesaj::Mesaj);
            qDebug()<<m->getexpeditor()+m->getmesaj();
        }
        else
        {
            m=new Meet(q.value(1).toString(),q.value(2).toString(),q.value(3).toString(),q.value(0).toLongLong(),IMesaj::Meet);
        }
        QDateTime data=QDateTime::fromSecsSinceEpoch(m->gettime());
        QString mes("["+data.toString()+QString("]")+m->getexpeditor()+": "+m->gettitlu()+"  "+m->getmesaj());
        mesaje.push_back(mes);
    }
    Disconnect();
    return mesaje;

}
int Database::AddMember(QString Channel,QString Owner,QString User)
{
    ConnectToDB();
    QString s("SELECT * FROM Utilizatori WHERE Username='"+User+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    bool ok=false;
    while(q.next())
    {
        ok=true;
    }
    if(!ok)
        return 0;
    s="SELECT ID_Canal FROM Canale WHERE Nume_Canal='"+Channel+"' AND Owner='"+Owner+"'";
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        s="SELECT * FROM Membri_Canale mc INNER JOIN Canale c on c.ID_Canal=mc.ID_Canal INNER JOIN Utilizatori u on u.ID_Utilizator=mc.ID_Utilizator WHERE u.Username='"+User+"' and c.Nume_Canal='"+Channel+"'";
        QSqlQuery q1;
        q1.prepare(s);
        q1.exec();
        while(q1.next())
        {
            return 0;
        }
        q1.finish();
        s="INSERT INTO Membri_Canale(ID_Canal,ID_Utilizator) VALUES ("+q.value(0).toString()+",(SELECT ID_Utilizator FROM Utilizatori Where Username='"+User+"'))";
        QSqlQuery q2;
        q2.prepare(s);
        q2.exec();
        q2.finish();
        QString notificare=Owner+" "+"v-a adaugat in canalul "+Channel;
        QSqlQuery ask;
        ask.prepare("SELECT Username FROM Utilizatori u INNER JOIN Membri_Canale mc on u.ID_Utilizator=mc.ID_Utilizator INNER JOIN Canale c on c.ID_Canal=mc.ID_Canal WHERE c.Nume_Canal='"+Channel+"'");
        ask.exec();
        vector<QString>useri;
        while(ask.next())
        {
            useri.push_back(ask.value(0).toString());
        }
        QSqlQuery q3;
        for(QString user:useri){
            qDebug()<<Owner<<user;
            if(user!=Owner){
            s="INSERT INTO Notificari(Notificare,Timp_incarcare,ID_Destinatar) VALUES ('"+notificare+"',"+QString::number(time(0))+",(SELECT ID_Utilizator FROM Utilizatori WHERE Username='"+user+"'))";
            QTcpSocket*socket;
            vector<pair<QString,QTcpSocket*>>users=TcpServer::getInstance().getUsers();
            for(pair<QString,QTcpSocket*>p:users)
                for(QString& s:useri)
                    if(s==p.first)
                        p.second->write(("101|"+s+"|"+notificare).toUtf8());
            qDebug()<<s;
            q3.prepare(s);
            q3.exec();
            q3.finish();
            }
        }
        vector<pair<QString,QTcpSocket*>>usersconnected=TcpServer::getInstance().getUsers();
        for(pair<QString,QTcpSocket*>i:usersconnected)
        {
            if(i.first==User){
                i.second->write(("101|"+notificare).toUtf8());
                break;
            }
        }
        q.finish();
        Disconnect();
        return 1;
    }

    Disconnect();
    return 0;

}
vector<QString> Database::GetUsersFromChannel(QString canal)
{
    ConnectToDB();
    vector<QString>ToTransmit;
    QString s("SELECT Descriere from Canale Where Nume_Canal='"+canal+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        ToTransmit.push_back(q.value(0).toString());
    }
    s="SELECT Username from Utilizatori u INNER JOIN Membri_Canale mc on mc.ID_Utilizator=u.ID_Utilizator INNER JOIN Canale c on mc.ID_Canal=c.ID_Canal WHERE c.Nume_Canal='"+canal+"'";
    q.prepare(s);
    q.exec();

    while(q.next())
    {
        ToTransmit.push_back(q.value(0).toString());
    }
    Disconnect();
    return ToTransmit;

}
vector<QString> Database::GetFilesFromChannel(QString canal)
{
    ConnectToDB();
    vector<QString>files;
    QString s("SELECT Nume_Fisier,Nume_Autor,Timp_Incarcare FROM Fisiere WHere ID_Canal=(SELECT ID_Canal FROM Canale WHERE Nume_Canal='"+canal+"')");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        File f(q.value(0).toString(),q.value(1).toString(),q.value(2).toLongLong());
        QDateTime t=t.fromSecsSinceEpoch(f.gettime());
        QString fisier=f.getnume()+" ("+f.getautor()+") "+QDateTime::fromSecsSinceEpoch(f.gettime()).toString();
        files.push_back(fisier);
    }
    Disconnect();
    return files;
}
vector<QString> Database::GetUsers()
{
    ConnectToDB();
    vector<QString>users;
    QString s("SELECT Username FROM Utilizatori");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    while(q.next())
    {
        users.push_back(q.value(0).toString());
    }
    q.finish();
    Disconnect();
    return users;
}
vector<QString> Database::GetConversation(QString user1,QString user2)
{
    vector<QString>users=GetUsers();
    ConnectToDB();
    QSqlQuery q;
    for(int i=0;i<(int)users.size();i++)
        for(int j=i+1;j<(int)users.size();j++)
        {
            QString s("SELECT * FROM Conversatii WHERE Utilizator1='"+users[i]+"' AND Utilizator2='"+users[j]+"'");

            q.prepare(s);
            q.exec();
            while(q.next())
            {
                continue;
            }
            s="INSERT INTO Conversatii(Utilizator1,Utilizator2) VALUES('"+users[i]+"','"+users[j]+"')";
            q.prepare(s);
            q.exec();
        }
    q.finish();
    bool ok=true;
    for(QString& i:users)
    {
        if(i==user1)
         {
            ok=true;
            break;
        }
        if(i==user2)
        {
            ok=false;
            break;
        }

    }
    if(ok==false)
        swap(user1,user2);
    QString s("SELECT ID_Conversatie FROM Conversatii WHERE Utilizator1='"+user1+"' AND Utilizator2='"+user2+"'");
    q.prepare(s);
    q.exec();
    vector<QString>mesaje;
    while(q.next())
    {
    QString s("SELECT Emitator,Mesaj,Timp_incarcare FROM Mesaje_Conversatii WHERE ID_Conversatie="+q.value(0).toString());
    QSqlQuery q1;
    q1.prepare(s);
    q1.exec();


        while(q1.next())
        {
            QString mes;
            QDateTime t=QDateTime::fromSecsSinceEpoch(q1.value(2).toLongLong());
            mes="["+t.toString()+"]"+q1.value(0).toString()+": "+q1.value(1).toString();
            mesaje.push_back(mes);
        }
    }
    Disconnect();
    return mesaje;
}

void Database::AddMessageInConversation(const QString&source,const QString&destination,const QString&message)
{
    vector<QString>users=GetUsers();
    ConnectToDB();
    bool ok=true;
    for(QString& i:users)
    {
        if(i==source)
         {
            ok=true;
            break;
        }
        if(i==destination)
        {
            ok=false;
            break;
        }

    }
    QString user1,user2;
    if(ok)
    {
        user1=source;
        user2=destination;
    }
    else
    {
        user1=destination;
        user2=source;
    }
    QString s("SELECT ID_Conversatie FROM Conversatii WHERE Utilizator1='"+user1+"' AND Utilizator2='"+user2+"'");
    QSqlQuery q;
    q.prepare(s);
    q.exec();
    QTcpSocket*source_socket=nullptr;
    QTcpSocket*dest_socket=nullptr;
    vector<pair<QString,QTcpSocket*>>usersconnected=TcpServer::getInstance().getUsers();
    for(pair<QString,QTcpSocket*>i:usersconnected)
    {
        if(i.first==source)
            source_socket=i.second;
        else if(i.first==destination)
            dest_socket=i.second;
    }
    while(q.next())
    {
        s="INSERT INTO Mesaje_Conversatii(Mesaj,ID_Conversatie,Emitator,Timp_incarcare) VALUES ('"+message+"',"+q.value(0).toString()+",'"+source+"',"+QString::number(time(0))+")";
        QSqlQuery q1;
        q1.prepare(s);
        q1.exec();
        QDateTime t=QDateTime::fromSecsSinceEpoch(time(0));
        QString mes="["+t.toString()+"]"+source+": "+message;
        source_socket->write(("16|1|"+mes).toUtf8());
        if(dest_socket!=nullptr){
            dest_socket->write(("103|"+destination+"|"+mes).toUtf8());
            qDebug()<<"Ok"<<dest_socket->socketDescriptor();
        }
        q1.finish();
        Disconnect();
        return;
    }
    q.finish();
    source_socket->write("16|0");
    Disconnect();
}

