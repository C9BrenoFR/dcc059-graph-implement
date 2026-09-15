#ifndef GRAPHLA_H
#define GRAPHLA_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <vector>

/*
Grafo com base na lista de adjacencia, os nós ainda são guardados dentro de um vetor, mas o resto é feito pela lista.

A variavel adjacencyList guarda  N itens onde N é o numero de nós no grafo,
cada indice em adjacencyList representa o nó de mesmo indice em nodes,
cada vetor de char dentro de adjacencyList guarda o id dos nós que o representado tem ligação.

Exemplo:
Supondo que temos um grafo simples completo com os nós A,B e C
Nosso vetor nodes seria:
A no indice 0
B no indice 1
C no indice 2

O adjacencyList seria:
[B,C] no indice 0 (representando os nós com quem A se liga)
[A,C] no indice 1 (representando os nós com quem B se liga)
[A,B] no indice 2 (representando os nós com quem C se liga)


NOTA:
Se você nunca usou a biblioteca <vector>, ela serve para otimizar o uso de vetores, com algumas funções auxiliares
Para pegar um item do vector você pode fazer de duas formas:
nodes[1] // forma comum
nodes.at(1) // Caso você acesse um item que não existe (por exemplo, indice 10 num vetor de 5 espaços) ele lança uma exceção ao invés de lixo de memória

A função push_back() usada nas funções de adicionar serve para colocar um item no final do vetor
*/
class GraphLa
{
private:
    std::vector<Node *> nodes;
    std::vector<std::vector<std::string>> adjacencyList;
public:
    // ========================
    //  Construtor e Destrutor
    // ========================
    GraphLa(std::vector<Node *> nodes, std::vector<std::vector<std::string>> adjacencyList) : nodes(nodes), adjacencyList(adjacencyList) {}
    GraphLa(std::string instance); // Carrega o grafo com base em um arquivo na pasta de instancias
    GraphLa() {}
    ~GraphLa();

    // =========
    //  Getters
    // =========
    std::vector<Node *> getNodes() { return nodes; }
    std::vector<std::vector<std::string>> getAdjacencyList() { return adjacencyList; }

    // =========
    //  Setters
    // =========
    void addNode(Node node);
    void addEdge(std::string origin, std::string destination); // Liga 2 nós já existentes (grafo não direcionado)

    // ========
    //  Buscas
    // ========
    int searchNodeIndex(std::string node);
    std::vector<std::string> searchNodeEdges(std::string node);   // Busca todas as arestas ligadas a um determinado vertice
    bool isNodesConected(std::string node_1, std::string node_2); // Verifica se existe aresta entre 2 vertices
};

#endif