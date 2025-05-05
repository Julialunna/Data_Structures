#include <iostream>
class OperationsCounter
{
    int cmp;
    int move;
    int calls;

    public:
    
    void resetcounter();
    void inccmp(int num);
    void incmove(int num);
    void inccalls(int num);
    void print_operations_counter();
};