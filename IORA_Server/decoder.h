#ifndef DECODER_H
#define DECODER_H
#include<QString>

class Decoder
{
public:
    static void decode(QString s,QString& s1,QString& s2,QString& s3,QString& s4);
private:
    Decoder(){};
    ~Decoder(){}
    Decoder(const Decoder&);
};

#endif // DECODER_H
