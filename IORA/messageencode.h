#ifndef MESSAGEENCODE_H
#define MESSAGEENCODE_H

#include "QString"
#include "serverRequestTypes.h"

class messageEncode
{
public:
    static QString encode(serverRequestTypes code, QString str1 = "", QString str2 = "", QString str3 = "", QString str4 = "");

private:
    messageEncode();
    messageEncode(const messageEncode& obj);
    ~messageEncode();

};

#endif // MESSAGEENCODE_H
