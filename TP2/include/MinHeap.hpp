#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <cstdlib>

template <typename T>
class MinHeap {
private:
    int size;
    int capacity;
    T* data;

    int GetAncestor(int position) const;
    int GetSuccessorLeft(int position) const;
    int GetSuccessorRight(int position) const;
    void Resize();

public:
    MinHeap();
    MinHeap(int maxsize);
    ~MinHeap();

    void Insert(const T& x);
    T Remove();
    bool Empty() const;
    T GetData(int j) const;
};

template <typename T>
int MinHeap<T>::GetAncestor(int position) const {
    return (position - 1) / 2;
}

template <typename T>
int MinHeap<T>::GetSuccessorLeft(int position) const {
    return 2 * position + 1;
}

template <typename T>
int MinHeap<T>::GetSuccessorRight(int position) const {
    return 2 * position + 2;
}

//O(n), doubles data size and store items on new array
template <typename T>
void MinHeap<T>::Resize(){
    T* new_data= new T[this->capacity * 2];
    for(int i =0;i<this->size;i++){
        new_data[i] = this->data[i];
    }
    this->capacity = this->capacity * 2;
    T* data_to_delete = this->data;
    this->data =new_data;
    delete[] data_to_delete;
}

template <typename T>
MinHeap<T>::MinHeap() {
    capacity = 10;
    size = 0;
    data = new T[capacity];
}

template <typename T>
MinHeap<T>::MinHeap(int maxsize) {
    data = new T[maxsize];
    size = 0;
    if(maxsize == 0){
        //garantee minimum capacity permitted
        this->capacity = 1;
    }else{
        capacity = maxsize;
    }
}

template <typename T>
MinHeap<T>::~MinHeap() {
    delete[] data;
}

template <typename T>
void MinHeap<T>::Insert(const T& x) {
    //if heap is full, create more room for data
    if(this->size == this->capacity){
        Resize();
    }
    data[size] = x;
    int i = size;
    int ancestor = GetAncestor(i);
    //find right position to insert item 
    while (i > 0 && data[i] < data[ancestor]) {
        T temp = data[i];
        data[i] = data[ancestor];
        data[ancestor] = temp;
        i = ancestor;
        ancestor = GetAncestor(i);
    }
    size++;
}

template <typename T>
T MinHeap<T>::Remove() {
    T value = data[0];
    data[0] = data[size - 1];
    size--;
    int i = 0;
    //reorganizing data to garantee min heap properties
    while (true) {
        int left = GetSuccessorLeft(i);
        int right = GetSuccessorRight(i);
        int successor;
        //choosing smaller successor
        if (left < size && right < size) {
            //if both exists choose smaller
            successor = (data[left] < data[right]) ? left : right;
        } else if (left < size) {
            //if only left successor exists choose it
            successor = left;
        } else if (right < size) {
            //if only right successor exists choose it
            successor = right;
        } else {
            //if doesn't exists successor we can stop
            break;
        }
        //if antecessor is bigger than successor, swap it
        if (data[i] > data[successor]) {
            T temp = data[i];
            data[i] = data[successor];
            data[successor] = temp;
            i = successor;
        } else {
            break;
        }
    }
    return value;
}

//check if heap is empty
template <typename T>
bool MinHeap<T>::Empty() const {
    return size == 0;
}

//return heap data at position j 
template <typename T>
T MinHeap<T>::GetData(int j) const {
    return data[j];
}

#endif
