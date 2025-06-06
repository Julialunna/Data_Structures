#include <iostream>
#include "List.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Graph.hpp"
int main(){
    List<int> lista;
    Stack<int> pilha;
    Queue<int> fila;
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
            // pilha.pile(item);
            // pilha.print();
        }else if(comando == 'b'){
            // std::cin>>item;
            // std::cin>>posicao;
            // lista.insertAtPosition(item, posicao);
            // lista.print();
            fila.dequeue();
            fila.print();
            // pilha.unstack();
            // pilha.print();
        }else if(comando =='c'){
            
            std::cin>>item;
            std::cout<<fila.search(item)<<std::endl;
            // lista.insertEnd(item);
            // lista.print();
            // std::cout<<pilha.search(item)<<std::endl;
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

     try {
        std::cout << "=== Teste Básico: Grafo de Inteiros ===\n\n";

        // 1) Cria grafo com 3 vértices (0,1,2), sem arestas
        Graph<int> g(3);
        std::cout << "Passo 1: Grafo inicial com 3 vértices\n";
        std::cout << "VertexCount(): " << g.VertexCount() << "  (esperado 3)\n";
        std::cout << "EdgeCount():   " << g.EdgeCount()   << "  (esperado 0)\n";
        for (int v = 0; v < 3; v++) {
            std::cout << "PrintNeighbors(" << v << "): ";
            g.PrintNeighbors(v);  // deve imprimir somente uma linha em branco
        }
        std::cout << "-------------------------------------\n\n";

        // 2) Insere uma única aresta 0–1
        std::cout << "Passo 2: Inserindo aresta 0–1\n";
        g.InsertEdge(0, 1, 1, 0);
        std::cout << "VertexCount(): " << g.VertexCount() << "  (ainda 3)\n";
        std::cout << "EdgeCount():   " << g.EdgeCount()   << "  (esperado 1)\n";
        std::cout << "PrintNeighbors(0): ";
        g.PrintNeighbors(0);  // deve imprimir "1"
        std::cout << "PrintNeighbors(1): ";
        g.PrintNeighbors(1);  // deve imprimir "0"
        std::cout << "PrintNeighbors(2): ";
        g.PrintNeighbors(2);  // ainda vazio
        std::cout << "-------------------------------------\n\n";

        // 3) Insere arestas 0–2 e 1–2 para formar triângulo 0–1–2
        std::cout << "Passo 3: Inserindo aresta 0–2 e 1–2\n";
        g.InsertEdge(0, 2, 2, 0);
        g.InsertEdge(1, 2, 2, 1);
        std::cout << "VertexCount(): " << g.VertexCount() << "  (esperado 3)\n";
        std::cout << "EdgeCount():   " << g.EdgeCount()   << "  (esperado 3)\n";
        for (int v = 0; v < 3; v++) {
            std::cout << "PrintNeighbors(" << v << "): ";
            g.PrintNeighbors(v);
            // 0→1 2, 1→0 2, 2→0 1
        }
        std::cout << "-------------------------------------\n\n";

        // 4) Teste de FindNeighbors e iteração manual
        std::cout << "Passo 4: Testando FindNeighbors(1)\n";
        List<int>* viz1 = g.FindNeighbors(1);
        std::cout << "Tamanho da lista de vizinhos de 1: " << viz1->getSize() << "  (esperado 2)\n";
        std::cout << "Itens em FindNeighbors(1): ";
        for (int i = 1; i <= viz1->getSize(); i++) {
            std::cout << viz1->getItem(i) << " ";
        }
        std::cout << "\n-------------------------------------\n\n";

        // 5) Inserir vértice dinamicamente (novo vértice 3)
        std::cout << "Passo 5: InsertVertex() → adiciona vértice 3\n";
        g.InsertVertex();
        std::cout << "VertexCount(): " << g.VertexCount() << "  (esperado 4)\n";
        std::cout << "PrintNeighbors(3): ";
        g.PrintNeighbors(3);  // lista vazia
        std::cout << "-------------------------------------\n\n";

        // 6) Insere aresta 2–3
        std::cout << "Passo 6: Inserindo aresta 2–3\n";
        g.InsertEdge(2, 3, 3, 2);
        std::cout << "EdgeCount():   " << g.EdgeCount() << "  (esperado 4)\n";
        std::cout << "PrintNeighbors(2): ";
        g.PrintNeighbors(2);  // deve imprimir "0 1 3"
        std::cout << "PrintNeighbors(3): ";
        g.PrintNeighbors(3);  // deve imprimir "2"
        std::cout << "-------------------------------------\n\n";

        // 7) Teste de índices inválidos (deve lançar exceção)
        // std::cout << "Passo 7: Tentando FindNeighbors(-1) (espera exceção)\n";
        // try {
        //     g.FindNeighbors(-1);
        //     std::cout << "  ERRO: não lançou exceção para índice inválido\n";
        // } catch (const char* e) {
        //     std::cout << "  Lançou exceção corretamente: " << e << "\n";
        // }
        // std::cout << "-------------------------------------\n\n";

        // 8) Teste de impressão final do grafo inteiro
        std::cout << "Passo 8: Estado final do grafo:\n";
        std::cout << "VertexCount(): " << g.VertexCount() << "\n";
        std::cout << "EdgeCount():   " << g.EdgeCount() << "\n";
        for (int v = 0; v < g.VertexCount(); v++) {
            std::cout << "Vizinhos de " << v << ": ";
            g.PrintNeighbors(v);
        }
        std::cout << "\n=== Fim dos testes ===\n";
    }
    catch (const char* e) {
        std::cerr << "Exceção não esperada: " << e << "\n";
    }
    return 0;
}

