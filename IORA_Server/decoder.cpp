#include "decoder.h"
#include"database.h"
#include<QList>
#include<QRegularExpression>
void Decoder::decode(QString s,QString& s1,QString& s2,QString& s3,QString& s4)
{
    //s.resize(s.size()-2);
    QStringList lista=s.split("|");
    s1=lista[0];
    if(lista.length()>=2)
        s2=lista[1];
    if(lista.length()>=3)
        s3=lista[2];
    if(lista.length()>=4)
        s4=lista[3];
}
