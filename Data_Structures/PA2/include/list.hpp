#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
class Lista{
    private:
        No *cabeca;
        No *ultimo;
        int tamanho;
        No* posiciona(int pos, bool antes);
        public:
        Lista();
        ~Lista();
        void insere_final(int valor_novo_no);

};
#endif