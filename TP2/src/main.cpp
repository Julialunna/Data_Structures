#include <iostream>
#include "List.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
int main(){
    List lista;
    Stack pilha;
    Queue fila;
    char comando = ' ';
    int item, posicao;

    while(comando != 'g'){
        std::cin>>comando;
        if(comando == 'a'){
            std::cin>>item;
            // lista.insertBeginning(item);
            // lista.print();
            fila.queue(item);
            fila.print();
        }else if(comando == 'b'){
            // std::cin>>item;
            // std::cin>>posicao;
            // lista.insertAtPosition(item, posicao);
            // lista.print();
            fila.dequeue();
            fila.print();
        }else if(comando =='c'){
            
            std::cin>>item;
            std::cout<<fila.search(item)<<std::endl;
            // lista.insertEnd(item);
            // lista.print();
        }else if(comando == 'd'){
             lista.removeBeginning();
             lista.print();
        }else if(comando == 'e'){
             lista.removeEnd();
             lista.print();
        }else if(comando == 'f'){
            std::cin>>posicao;
            lista.removeAtPosition(posicao);
            lista.print();
        }else if(comando == 'h'){
            std::cin>>item;
            std::cout<<lista.search(item)<<std::endl;
        }
    }


}