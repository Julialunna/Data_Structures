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
typedef struct item{
    char key[KEYSIZE];
    char payload [REGISTERSIZE];

    bool operator < (const item& other) const {
        return std::strcmp(this->key, other.key) < 0;
    }

    bool operator>(const item& other) const {
        return std::strcmp(this->key, other.key) > 0;
    }

    bool operator==(const item& other) const {
        return std::strcmp(this->key, other.key) == 0;
    }
    bool operator<=(const item& other) const {
    return std::strcmp(this->key, other.key) <= 0;
    }

    bool operator>=(const item& other) const {
        return std::strcmp(this->key, other.key) >= 0;
    }

}item_t;

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