#include "Set.hpp"
#include <iostream>

StringSet::StringSet(int tamanho)
{
    this->tamanhoOriginal = tamanho;
    this->tamanhoConjunto = 0;
    this->tamanhoTabela = tamanho;
    this->tabela = new ElementoTabela[this->tamanhoTabela];
    for (int i = 0; i < tamanho; i++)
    {
        this->tabela[i].vazio = true;
        this->tabela[i].retirada = false;
    }
}
StringSet::~StringSet()
{
    delete[] this->tabela;
}
int StringSet::Hash(string s)
{
    unsigned int hash = 0;
    for (char c : s)
    {
        hash = ((31 * hash) + c);
    }
    int pos = hash % this->tamanhoTabela;
    return pos;
}
int StringSet::Rehash(int pos)
{

    return (pos+1) % this->tamanhoTabela;
}
void StringSet::Inserir(string s)
{
    if (this->Pertence(s))
        return;

    if (this->tamanhoConjunto == this->tamanhoTabela)
    {
        this->Resize(tamanhoTabela * 2);
    }
    int pos = this->Hash(s);
    while(!this->tabela[pos].vazio){
        pos = this->Rehash(pos);
    }

    this->tabela[pos].dado = s;
    this->tabela[pos].vazio = false;
    this->tamanhoConjunto++;
}
void StringSet::Resize(size_t tamanho)
{
    ElementoTabela *nova_tabela = new ElementoTabela[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        nova_tabela[i].retirada = false;
        nova_tabela[i].vazio = true;
    }
    ElementoTabela *tabela_antiga = this->tabela;
    int tamanho_antiga = this->tamanhoTabela;
    this->tamanhoTabela = tamanho;
    this->tabela = nova_tabela;
    this->tamanhoConjunto = 0;

    for (int i = 0; i < tamanho_antiga; i++)
    {
        if (!tabela_antiga[i].vazio)
        {
            string dado = tabela_antiga[i].dado;
            this->Inserir(dado);
        }
    }
    delete[] tabela_antiga;
}

void StringSet::Remover(string s)
{
    if(this->Pertence(s)){
        int posicao = this->Hash(s);
        while(this->tabela[posicao].dado != s){
            posicao = this->Rehash(posicao);
        }
        this->tabela[posicao].retirada = true;
        this->tabela[posicao].vazio = true;
        
    }
}
bool StringSet::Pertence(string s)
{
    int posicao = this->Hash(s);
    int inicio = posicao;
    do
    {
        if (this->tabela[posicao].vazio)
        {
            if (!this->tabela[posicao].retirada)
            {
                return false;
            }
        }
        else if (this->tabela[posicao].dado == s)
        {
            return true;
        }
        posicao = this->Rehash(posicao);

    } while (posicao != inicio);
    return false;
}
void StringSet::Imprimir()
{
    for (int i = 0; i < this->tamanhoTabela; i++)
    {
        if (!this->tabela[i].vazio)
        {
            std::cout << this->tabela[i].dado << std::endl;
        }
    }
}

StringSet *StringSet::Intersecao(StringSet *S)
{
}
StringSet *StringSet::Uniao(StringSet *S)
{
}
StringSet *StringSet::DiferencaSimetrica(StringSet *S)
{
}