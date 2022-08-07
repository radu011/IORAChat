#ifndef MESAJ_H
#define MESAJ_H
#include "absmesaj.h"

class Mesaj:public AbsMesaj
{
public:
    Mesaj(QString expeditor,QString text,long long timp,type tip);
    QString gettitlu()const;
};

#endif // MESAJ_H
