#include "file.h"

File::File(QString nume,QString autor,qlonglong timp):nume(nume),autor(autor),timp(timp)
{
}
QString File::getnume()const{return nume;}
QString File::getautor()const{return autor;}
qlonglong File::gettime()const{return timp;}
