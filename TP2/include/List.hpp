#ifndef LIST_HPP
#define LIST_HPP
typedef int itemType;
typedef int keyType;

class List;

class ListNode {
public:
    ListNode();
private:
    itemType item; 
    ListNode* next;
    friend class List;
};

class List{
    public:
    List();
    ~List();
    itemType getItem(int position);
    void setItem(itemType item, int position);
    void insertBeginning(itemType item);
    void insertEnd(itemType item);
    void insertAtPosition(itemType item, int position);
    itemType removeBeginning();
    itemType removeEnd();
    itemType removeAtPosition(int position);
    itemType search(keyType key);
    void print();
    void clean();
    private:
    int size;
    ListNode* first;
    ListNode* last;
    ListNode* position(int position);
};
#endif