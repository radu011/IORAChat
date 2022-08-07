#ifndef IMESAJ_H
#define IMESAJ_H
#include<QString>
using namespace std;
class IMesaj
{
public:
    enum type{Mesaj,Meet};
    virtual QString getmesaj()const=0;
    virtual QString getexpeditor()const=0;
    virtual long long gettime()const=0;
    virtual QString gettitlu()const=0;
    virtual type gettype()const=0;
};

#endif // IMESAJ_H
