#ifndef OPERATIONS_COUNTER_HPP
#define OPERATIONS_COUNTER_HPP
#include <iostream>
#include <cstring>
#ifndef KEYSIZE
#define KEYSIZE 1
#endif

#ifndef REGISTERSIZE
#define REGISTERSIZE 1
#endif

#ifndef VETSIZE
#define VETSIZE 1
#endif

#ifndef VETDISORDER
#define VETDISORDER 1
#endif

typedef struct item{
    char key[KEYSIZE];
    char payload [REGISTERSIZE];

}item_t;

bool operator<(const item& a, const item& b);
bool operator>(const item& a, const item& b);
bool operator==(const item& a, const item& b);
bool operator<=(const item& a, const item& b);
bool operator>=(const item& a, const item& b);


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

};

#endif