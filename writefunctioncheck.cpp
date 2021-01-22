#include "writefunctioncheck.h"

WriteFunctionCheck::WriteFunctionCheck():sum_rightdot(0)
{
    reference_dot.resize(100);/*
    foreach(QVector<coordinate> Item , &reference_dot){
        Item.data()->x=i;
        Item.data()->y=12*i;
        Item.data()->flag = false;
        i++;
    }*/
}

float WriteFunctionCheck::feed_dot(int x, int y)
{
    for (coordinate Item : reference_dot) {
        if(Item.x == x){
            if(Item.y == y){
                Item.flag = true;
                sum_rightdot++;
                rate_rightdot = sum_rightdot/sum_dot;
            }
            break;
        }
    }
    return rate_rightdot;
}
