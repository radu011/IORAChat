#include "mesaj.h"

Mesaj::Mesaj(QString expeditor,QString text,long long timp,type tip):AbsMesaj(expeditor,text,timp,tip)
{}
QString Mesaj::gettitlu()const
{return "";}
