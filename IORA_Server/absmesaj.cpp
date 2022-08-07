#include "absmesaj.h"

AbsMesaj::AbsMesaj(QString expeditor,QString text,long long timp,type tip):text(text),expeditor(expeditor),timp(timp),tip(tip)
{
}
AbsMesaj::type AbsMesaj::gettype()const
{
    return tip;
}
QString AbsMesaj::getexpeditor()const
{
    return expeditor;
}
QString AbsMesaj::getmesaj()const
{
    return text;
}
long long AbsMesaj::gettime()const
{
    return timp;
}
AbsMesaj::~AbsMesaj()
{
    this->text="";
    this->expeditor="";

}
