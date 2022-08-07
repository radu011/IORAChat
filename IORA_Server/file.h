#ifndef FILE_H
#define FILE_H
#include<QString>
#include<time.h>
using namespace std;

class File
{
private:
 QString nume;
 QString autor;
 qlonglong timp;
public:
    File(QString nume,QString autor,qlonglong timp);
    QString getnume()const;
    QString getautor()const;
    qlonglong gettime()const;
};

#endif // FILE_H
