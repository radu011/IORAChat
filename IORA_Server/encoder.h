#ifndef ENCODER_H
#define ENCODER_H
#include<QString>
#include<vector>
using namespace std;
class Encoder
{
private:
    Encoder();
    ~Encoder(){};
    Encoder(const Encoder&){}
public:
    static QString Encode(vector<QString>s);
};

#endif // ENCODER_H
