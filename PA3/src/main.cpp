#include <iostream>
#include "heap.hpp"

int main(){
    int heap_size = 0;
    std::cin>>heap_size;

    Heap min_heap(heap_size);
    int new_element =0;
    for(int i=0;i<heap_size;i++){
        std::cin>>new_element;
        min_heap.Insert(new_element);
    }

    int item_removed = 0;

    for(int i=0;i<heap_size;i++){
        item_removed = min_heap.Remove();
        if(i==heap_size-1){
            std::cout<<item_removed<<std::endl;
        }else{
            std::cout<<item_removed<<" "<<std::ends;  
        }

    }


    return 0;
}