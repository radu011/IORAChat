#ifndef MEET_H
#define MEET_H
#include "absmesaj.h"

class Meet: public AbsMesaj
{
private:
    QString titlu;
public:
    Meet(QString autor,QString titlu,QString descriere,long long timp,type tip);
    QString gettitlu()const;
};

#endif // MEET_H
