#include "thread.h"
#include<string.h>
#include "decoder.h"
#include "encoder.h"
#include"database.h"
Thread::Thread(int ID,QObject*parent):QThread(parent)
{
    this->socketDescriptor=ID;
}

void Thread::run()
{
    qDebug()<<socketDescriptor<<" Start thread";
    socket=new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    //connect(socket,SIGNAL(ToWrite(QByteArray q)),this,SLOT(Write(QByteArray q)),Qt::AutoConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug()<< socketDescriptor<<" Client Connected";
    exec();
}
void Thread::Solve(QString& s1,QString& s2,QString& s3,QString& s4)
{
    vector<QString>s;
    Database& db=Database::getinstance();
    if(s1=="0"){
        s.push_back("0");
        if(db.Login(s2,s3)){
                s.push_back("1");
                qDebug()<<"Utilizator conectat";
        }
        else{
            s.push_back("0");
        }

    }
    else if(s1=="1")
    {
        s.push_back("1");
       if(db.Register(s2,s3,s4))
       {
           s.push_back("1");
       }
       else
       {
           s.push_back("0");
       }
    }
    else if(s1=="2")
    {
        s.push_back("2");
        if(db.ChangePassword(s2,s3))
        {
            s.push_back("1");
        }
        else
        {

            s.push_back("0");
        }
    }
    else if(s1=="3")
    {
        vector<QString>mesaje=db.GetNotifications(s2);
        s.push_back("3");
        QString aux=QString::number(mesaje.size());
        s.push_back(aux);
        for(QString& m:mesaje)
        {
            s.push_back(m);
        }

        mesaje.clear();
    }
    else if(s1=="4")
    {
        s.push_back("4");
        if(db.CreateChannel(s2,s3,s4))
        {
            s.push_back("1");
            db.AddMember(s2,s4,s4);
        }
        else{
            s.push_back("0");
        }
    }
    else if(s1=="5")
    {
        vector<QString>canale=db.GetChannels(s2);
        s.push_back("5");
        s.push_back(QString::number(canale.size()));
        for(QString& i:canale)
            s.push_back(i);
    }
    else if(s1=="6")
    {
        vector<QString>postari=db.GetPosts(s2);
        s.push_back("6");
        s.push_back(QString::number(postari.size()));
        for(QString& post:postari)
        {
            s.push_back(post);
        }
        postari.clear();
    }
    else if(s1=="7")
    {
        vector<QString>infos=db.GetUsersFromChannel(s2);
        s.push_back("7");
        s.push_back(infos[0]);
        s.push_back(QString::number(infos.size()-1));
        for(auto i=infos.begin();i!=infos.end();i++)
        {
            if(i!=infos.begin())
                s.push_back(*i);
        }
        infos.clear();

    }
    else if(s1=="8")
    {
        vector<QString>files=db.GetFilesFromChannel(s2);
        s.push_back("8");
        s.push_back(QString::number(files.size()));
        for(QString&i:files)
        {
            s.push_back(i);
        }
    }
    else if(s1=="9")
    {
        vector<QString>users=db.GetUsers();
        s.push_back("9");
        s.push_back(QString::number(users.size()));
        for(QString&i:users)
        {
            s.push_back(i);
        }
    }
    else if(s1=="10")
    {
        vector<QString>mesaje=db.GetConversation(s2,s3);
        s.push_back("10");
        s.push_back(QString::number(mesaje.size()));
        for(QString&i:mesaje)
        {
            s.push_back(i);
        }
    }
    else if(s1=="12")
    {
        s.push_back("12");
        if(db.AddMember(s2,s3,s4))
        {
            s.push_back("1");
        }
        else
        {
            s.push_back("0");
        }
    }
    else if(s1=="16")
    {
       db.AddMessageInConversation(s2,s3,s4);
    }
    QString str=Encoder::Encode(s);
    qDebug()<<str;
    QByteArray q=str.toUtf8();
    socket->write(q);
}
void Thread::readyRead()
{
    QByteArray Data=socket->readAll();
    QString s=Data.data();
    QString s1="",s2="",s3="",s4="";
    Decoder::decode(s,s1,s2,s3,s4);
    qDebug()<<s1<<s2<<s3<<s4;
    Solve(s1,s2,s3,s4);

}
void Thread::disconnected()
{
    qDebug()<<socketDescriptor<<"Disconnected";
    //Database::getinstance().RemoveUserConnected(socket);
    socket->deleteLater();
    exit(0);
}
