#include "list.hpp"

Lista::Lista(){
    this->cabeca = new No();
    this->ultimo = this->cabeca;
    this->tamanho = 0;
}

Lista::~Lista(){
    No* no_atual = this->cabeca;
    while(no_atual != nullptr){
        No* no_a_deletar = no_atual;
        no_atual = no_atual->get_proximo_no();
        delete no_a_deletar;
    }
    this->tamanho = 0;
}

// No* Lista::posiciona(int pos, bool antes){
//     No *no_atual;
//     if(pos > tamanho || pos <= 0){
//         throw "Erro posicao invalida";
//     }
    
//     no_atual = this->cabeca;
    
//     for(int i =0; i<pos;i++){
//         no_atual = no_atual->get_proximo_no();
//     }

//     if(antes){
//         return no_atual;
//     }else{
//         return no_atual->get_proximo_no();
//     }
// }

void Lista::insere_final(int valor_novo_no){
    No *novo_no = new No(valor_novo_no);
    this->ultimo->set_proximo_no(novo_no);
    this->ultimo = novo_no;
    this->tamanho++;
}