#include "meet.h"

Meet::Meet(QString autor,QString titlu,QString descriere,long long timp,type tip):AbsMesaj(autor,descriere,timp,tip),titlu(titlu)
{}
QString Meet::gettitlu()const
{return this->titlu;}
