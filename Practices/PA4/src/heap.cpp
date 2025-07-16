#include "heap.hpp"
#include <iostream>
#include <cstdlib>

Heap::Heap(int max_size){
    this->data = (s_edge *)malloc(max_size * sizeof(s_edge));
    this->size = 0;
}
Heap::~Heap(){
    free(this->data);
}

void Heap::Insert(s_edge x){
    this->data[this->size] = x;
    int i =  this->size, ancestor = this->GetAncestor(i);
    while(this->data[i].custo < this->data[ancestor].custo){

        s_edge temp = this->data[i];
        this->data[i]=this->data[ancestor];
        this->data[ancestor] =  temp;
        i = ancestor;
        ancestor = this->GetAncestor(i);
    }
    this->size++;
}

s_edge Heap::GetData(int j){
    return this->data[j];
}

s_edge Heap::Remove(){
    s_edge value = this->data[0];
    this->data[0] = this->data[this->size -1];
    this->size--;

    int i = 0, successorLeft =this->GetSuccessorLeft(i), successorRight = GetSuccessorRight(i), successor = 0;

    if(successorLeft < this->size && successorRight < this->size){
        successor = (this->data[successorLeft].custo < this->data[successorRight].custo) ? successorLeft : successorRight;

    }else if(successorLeft < this->size){
        successor = successorLeft;
    }else if(successorRight < this->size){
        successor = successorRight;
    }else{
        return value;
    }

    while(this->data[i].custo > this->data[successor].custo){
        s_edge temp = this->data[i];
        this->data[i]=this->data[successor];
        this->data[successor] =  temp;
        i = successor;

        successorLeft =this->GetSuccessorLeft(i);
        successorRight = this->GetSuccessorRight(i);

        if(successorLeft<this->size && successorRight<this->size){
            successor = (this->data[successorLeft].custo < this->data[successorRight].custo) ? successorLeft : successorRight;
    
        }else if(successorLeft < this->size){
            successor = successorLeft;
        }else if(successorRight < this->size){
            successor = successorRight;
        }else{
            break;
        }

        successor = (this->data[successorLeft].custo < this->data[successorRight].custo) ? successorLeft : successorRight;
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