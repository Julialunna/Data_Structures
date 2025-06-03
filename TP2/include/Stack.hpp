#ifndef STACK_HPP
#define STACK_HPP
typedef int itemType;
typedef int keyType;
class Stack;

class StackNode {
public:
    StackNode();
private:
    itemType item; 
    StackNode* next;
    friend class Stack;
};

class Stack{
    public: 
    Stack();
    ~Stack();
    void pile(itemType item);
    itemType unstack();
    void clean();
    void print();
    private:
    StackNode *top;
    int size;
};

#endif