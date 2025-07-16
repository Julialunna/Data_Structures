#ifndef HEAP_HPP
#define HEAP_HPP

class Heap{

    public:
        Heap(int maxsize);
        ~Heap();

        void Insert(int x);
        int Remove();

        bool Empty();
        int GetData(int j);

    private:
        int GetAncestor(int position);
        int GetSuccessorLeft(int position);
        int GetSuccessorRight(int position);

        int size;
        int* data;
};


#endif