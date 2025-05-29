#ifndef HEAP_HPP
#define HEAP_HPP
#include "UnionFind.hpp"

/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Alteracoes no arquivo so podem ser feitas quando explicitadas
 */

class Heap{

    public:
        Heap(int maxsize);
        ~Heap();

        void Insert(s_edge x);
        s_edge Remove();

        //Retorna true caso o heap esteja vazio, false caso contrário.
        bool Empty();
        s_edge GetData(int j);

    private:
        int GetAncestor(int position);
        int GetSuccessorLeft(int position);
        int GetSuccessorRight(int position);

        int size;
        s_edge* data;
};


#endif