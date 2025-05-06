#include "heap.hpp"
#include <iostream>
#include <cstdlib>

Heap::Heap(int max_size){
    this->data = (int *)malloc(max_size * sizeof(int));
    this->size = 0;
}
Heap::~Heap(){
    free(this->data);
}

void Heap::Insert(int x){
    this->data[this->size] = x;
    int i =  this->size, ancestor = this->GetAncestor(i);
    while(this->data[i] < this->data[ancestor]){

        int temp = this->data[i];
        this->data[i]=this->data[ancestor];
        this->data[ancestor] =  temp;
        i = ancestor;
        ancestor = this->GetAncestor(i);
    }
    this->size++;
}

int Heap::GetData(int j){
    return this->data[j];
}

int Heap::Remove(){
    int value = this->data[0];
    this->data[0] = this->data[this->size -1];
    this->size--;

    int i = 0, successorLeft =this->GetSuccessorLeft(i), successorRight = GetSuccessorRight(i), successor = 0;

    if(successorLeft<this->size && successorRight<this->size){
        successor = (this->data[successorLeft] < this->data[successorRight]) ? successorLeft : successorRight;

    }else if(successorLeft < this->size){
        successor = successorLeft;
    }else if(successorRight < this->size){
        successor = successorRight;
    }else{
        return value;
    }



    while(this->data[i] > this->data[successor]){
        int temp = this->data[i];
        this->data[i]=this->data[successor];
        this->data[successor] =  temp;
        i = successor;

        successorLeft =this->GetSuccessorLeft(i);
        successorRight = this->GetSuccessorRight(i);
        // std::cout<<successor<<" "<<successorLeft<<" "<<successorRight<<std::endl;

        if(successorLeft<this->size && successorRight<this->size){
            successor = (this->data[successorLeft] < this->data[successorRight]) ? successorLeft : successorRight;
    
        }else if(successorLeft < this->size){
            successor = successorLeft;
        }else if(successorRight < this->size){
            successor = successorRight;
        }else{
            break;
        }

        successor = (this->data[successorLeft] < this->data[successorRight]) ? successorLeft : successorRight;
    }

    return value;
}  
bool Heap::Empty(){
    if(this->size == 0){
        return true;
    }else{
        return false;
    }
}
int Heap::GetAncestor(int position){
    return (position - 1) / 2;
}
int Heap::GetSuccessorLeft(int position){
    return 2 * position + 1;

}
int Heap::GetSuccessorRight(int position){
    return 2 * position + 2;
}