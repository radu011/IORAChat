#ifndef CANAL_H
#define CANAL_H
#include<vector>
#include<string>
#include "file.h"
#include "IMesaj.h"
using namespace std;
class Canal
{
private:
    string nume_canal;
    string descriere;
    string owner;
    vector<string> membri;
    vector<File*> fisiere;
    vector<IMesaj*> mesaje;
public:
    vector<string> getmembri()const;
    vector<File*> getfisiere()const;
    vector<IMesaj*>getmesaje()const;
    void addmembru(string user);
    void addfisier(File*f);
    void addmesaj(IMesaj*m);
    void setnume(string nume);
    void setdescriere(string descriere);
    void setowner(string nume);
    string getnume()const;
    string getdescriere()const;
    string getowner()const;

};

#endif // CANAL_H
