#include "chat.h"

void Chat::addMesaj(Mesaj*m)
{
    mesaje.push_back(m);
}
vector<Mesaj*> Chat::getconversatie()const
{
    return mesaje;
}
