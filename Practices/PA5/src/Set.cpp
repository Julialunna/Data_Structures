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
    long long hash = 0;
    for (char c : s)
    {
        hash = ((31 * hash) + c) % this->tamanhoTabela;
    }
    return (int)hash;
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

    for (long unsigned int  i = 0; i < tamanho; i++)
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
        else if (!this->tabela[posicao].retirada && this->tabela[posicao].dado == s)
        {
            return true;
        }
        posicao = this->Rehash(posicao);

    } while (posicao != inicio);
    return false;
}
void StringSet::Imprimir()
{
    int count = 0;
    for (int i = 0; i < this->tamanhoTabela; i++)
    {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada)
        {
            count++;
        }
    }

    string* elementos = new string[count];
    int idx = 0;

    for (int i = 0; i < this->tamanhoTabela; i++)
    {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada)
        {
            elementos[idx++] = this->tabela[i].dado;
        }
    }

    for (int i = 1; i < count; i++)
    {
        string chave = elementos[i];
        int j = i - 1;
        while (j >= 0 && elementos[j] > chave)
        {
            elementos[j + 1] = elementos[j];
            j--;
        }
        elementos[j + 1] = chave;
    }

    if (count == 0)
    {
        cout << "{  }" << endl;
    }
    else
    {
        cout << "{ ";
        for (int i = 0; i < count; i++)
        {
            cout << elementos[i];
            if (i + 1 < count)
                cout << ", ";
        }
        cout << " }" << endl;
    }

    delete[] elementos;
}


StringSet *StringSet::Intersecao(StringSet *S)
{
    StringSet* resultado = new StringSet(1);
    for (int i = 0; i < this->tamanhoTabela; i++){
        if (!this->tabela[i].vazio && !this->tabela[i].retirada){
            string dado = this->tabela[i].dado;
            if(S->Pertence(dado)){
                resultado->Inserir(dado);
            }
        }
    }
    return resultado;

}
StringSet *StringSet::Uniao(StringSet *S)
{
    //tamanho máximo
    StringSet* resultado = new StringSet(S->tamanhoTabela + this->tamanhoTabela);
    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) {
            resultado->Inserir(this->tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado;
}
StringSet *StringSet::DiferencaSimetrica(StringSet *S)
{
     //tamanho máximo
    StringSet* resultado = new StringSet(S->tamanhoTabela + this->tamanhoTabela);
    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada && !S->Pertence(this->tabela[i].dado)) {
            resultado->Inserir(this->tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada && !this->Pertence(S->tabela[i].dado)) {
            resultado->Inserir( S->tabela[i].dado);
        }
    }
    return resultado;
}