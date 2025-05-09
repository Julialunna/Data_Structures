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

int OperationsCounter::get_cmp(){
    return this->cmp;
}
int OperationsCounter::get_move(){
    return this->move;
}
int OperationsCounter::get_calls(){
    return this->calls;
}

void OperationsCounter::print_operations_counter()
{

    std::cout << this->cmp << " " << this->move << " " << this->calls << std::endl;
}