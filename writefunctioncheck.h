#ifndef WRITEFUNCTIONCHECK_H
#define WRITEFUNCTIONCHECK_H

#include <QVector>

class WriteFunctionCheck
{
    struct coordinate
    {
        int x;
        int y;
        bool flag;
    };
public:
    WriteFunctionCheck();
    float feed_dot(int x, int y);
    float get_dot_right_rate(){return rate_rightdot;}
private:
    QVector<coordinate> reference_dot;
    int sum_rightdot;
    const int sum_dot=100;
    float rate_rightdot;

};

#endif // WRITEFUNCTIONCHECK_H
