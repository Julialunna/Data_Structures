#include <iostream>
#include "OperationsCounter.hpp"


void OperationsCounter::resetcounter()
{
    this->cmp = 0;
    this->move = 0;
    this->calls = 0;
}

void OperationsCounter::inccmp(int num)
{

    this->cmp += num;
}

void OperationsCounter::incmove(int num)
{

    this->move += num;
}


void OperationsCounter::inccalls(int num)
{
    this->calls += num;
}
//increments number of comparisons
int OperationsCounter::get_cmp(){
    return this->cmp;
}
//increments number of movements
int OperationsCounter::get_move(){
    return this->move;
}
//increments number of calls
int OperationsCounter::get_calls(){
    return this->calls;
}
