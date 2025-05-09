#include <iostream>
class OperationsCounter
{
    private:
    int cmp;
    int move;
    int calls;

    public:
    
    void resetcounter();
    void inccmp(int num);
    void incmove(int num);
    void inccalls(int num);
    int get_cmp();
    int get_move();
    int get_calls();
    void print_operations_counter();
};