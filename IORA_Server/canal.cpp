#include "canal.h"

vector<string> Canal::getmembri()const
{
    return membri;
}
vector<File*> Canal::getfisiere()const
{
    return fisiere;
}
vector<IMesaj*>Canal::getmesaje()const
{
    return mesaje;
}
void Canal::addmembru(string user)
{
    this->membri.push_back(user);
}
void Canal::addfisier(File*f)
{
    this->fisiere.push_back(f);
}
void Canal::addmesaj(IMesaj*m)
{
    this->mesaje.push_back(m);
}
void Canal::setnume(string nume)
{
    this->nume_canal=nume;
}
void Canal::setdescriere(string descriere)
{
    this->descriere=descriere;
}
void Canal::setowner(string nume)
{
    this->owner=nume;
}

string Canal::getnume()const
{
    return this->nume_canal;
}
string Canal::getdescriere()const
{
    return this->descriere;
}
string Canal::getowner()const
{
    return this->owner;
}
