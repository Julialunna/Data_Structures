#ifndef LIST_HPP
#define LIST_HPP


class Lista;

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
        No* get_cabeca();
        int get_tamanho();

};
#endif