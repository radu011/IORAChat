#ifndef SOLVER_H
#define SOLVER_H
#include<QTcpSocket>
#include<QString>
class Solver
{
private:
    Solver();
public:
    static void Solve(QString& s1,QString& s2,QString& s3,QString& s4,QTcpSocket*socket);
};

#endif // SOLVER_H
