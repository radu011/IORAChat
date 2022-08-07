#include "encoder.h"
#include<qdebug.h>
QString Encoder::Encode(vector<QString>s)
{
    QString ToReturn="";
    for(QString str:s)
    {
        ToReturn+=str;
        ToReturn+="|";
    }
    if(ToReturn!="")
        ToReturn.resize(ToReturn.size()-1);
    return ToReturn;
}
