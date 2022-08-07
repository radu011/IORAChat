#ifndef CHAT_H
#define CHAT_H
#include"mesaj.h"
#include<vector>
using namespace std;
class Chat
{
private:
    vector<Mesaj*>mesaje;
public:
    void addMesaj(Mesaj*m);
    vector<Mesaj*> getconversatie()const;
};

#endif // CHAT_H
