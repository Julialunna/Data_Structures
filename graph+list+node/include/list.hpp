#ifndef LIST_HPP
#define LIST_HPP

class List;

class Node{
    private: 
        int value;
        Node *next;
        
    public:
        Node();
        Node(int node_value);
        int get_value();
        void set_value(int node_value);
        Node* get_next_node();
        void set_next_node(Node* next_node);
        friend class List;
};

class List{
    private:
        Node *head;
        Node *last;
        int size;
        Node* poition(int pos, bool before);
        public:
        List();
        ~List();
        void insert_at_the_end(int new_value_node);
        Node* get_head();
        int get_size();

};
#endif