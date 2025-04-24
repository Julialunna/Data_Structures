#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
class No{
    private: 
        int valor;
        No *proximo;
    public:
        No();
        No(int valor_no);
        int get_valor();
        void set_valor(int valor_no);
        No* get_proximo_no();
        void set_proximo_no(No* proximo_no);
        friend class Lista;
};
#endif