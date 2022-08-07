#include "messageencode.h"


messageEncode::messageEncode()
{

}

QString messageEncode::encode(serverRequestTypes code, QString str1, QString str2, QString str3, QString str4)
{
    QString message = "";

    message.append(QString::number((int)code));
    if (str1.length() > 0)
    {
        message.append('|');
        message.append(str1);
    }
    if (str2.length() > 0)
    {
        message.append('|');
        message.append(str2);
    }
    if (str3.length() > 0)
    {
        message.append('|');
        message.append(str3);
    }
    if (str4.length() > 0)
    {
        message.append('|');
        message.append(str4);
    }

    return message;
}
