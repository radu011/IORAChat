#ifndef DATABASE_H
#define DATABASE_H
#include<canal.h>
#include<vector>
#include <QSqlQuery>
#include<QtSql>
#include"IMesaj.h"
#include"thread.h"
using namespace std;

class Database
{
private:
    vector<Canal*>canale;
    static Database*instance;
    Database(){};
    Database(const Database&){};
    ~Database(){};
public:
    void GetCanalefromDB();
    void ConnectToDB();
    static Database&getinstance();
    static void destroyInstance();
    void Disconnect();
    int Login(QString username,QString parola);
    int Register(QString username,QString parola,QString email);
    int ChangePassword(QString username,QString email);
    vector<QString> GetNotifications(QString username);
    int CreateChannel(QString ChannelName,QString Descriere,QString Owner);
    vector<QString> GetChannels(QString username);
    vector<QString> GetPosts(QString canal);
    int AddMember(QString Channel,QString Owner,QString User);
    vector<QString> GetUsersFromChannel(QString canal);
    vector<QString> GetFilesFromChannel(QString canal);
    vector<QString> GetUsers();
    vector<QString> GetConversation(QString user1,QString user2);
    void AddMessageInConversation(const QString&source,const QString&destination,const QString&message);
};

#endif // DATABASE_H
