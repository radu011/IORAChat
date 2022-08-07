#ifndef ABSMESAJ_H
#define ABSMESAJ_H
#include "IMesaj.h"

class AbsMesaj:public IMesaj
{
protected:
    QString text;
    QString expeditor;
    long long timp;
    type tip;
public:
    AbsMesaj(QString expeditor,QString text,long long timp,type tip);
    virtual type gettype()const;
    virtual QString getexpeditor()const;
    virtual QString getmesaj()const;
    virtual long long gettime()const;
    virtual ~AbsMesaj();
};

#endif // ABSMESAJ_H
