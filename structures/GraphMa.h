#ifndef GRAPHMA_H
#define GRAPHMA_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <vector>

/*

Grafo com base na matriz de adjacencia


NOTA:
Se você nunca usou a biblioteca <vector>, ela serve para otimizar o uso de vetores, com algumas funções auxiliares
Para pegar um item do vector você pode fazer de duas formas:
nodes[1] // forma comum
nodes.at(1) // Caso você acesse um item que não existe (por exemplo, indice 10 num vetor de 5 espaços) ele lança uma exceção ao invés de lixo de memória

A função push_back() usada nas funções de adicionar serve para colocar um item no final do vetor
*/
class GraphMa
{
private:
    std::vector<Node *> nodes;
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    // ========================
    //  Construtor e Destrutor
    // ========================
    GraphMa(std::vector<Node *> nodes, std::vector<std::vector<int>> adjacencyMatrix) : nodes(nodes), adjacencyMatrix(adjacencyMatrix) {}
    GraphMa(std::string instance); // Carrega o grafo com base em um arquivo na pasta de instancias
    GraphMa() {}
    ~GraphMa();

    // =========
    //  Getters
    // =========
    std::vector<Node *> getNodes() { return nodes; }
    std::vector<std::vector<int>> getAdjacencyMatrix() { return adjacencyMatrix; }

    // =========
    //  Setters
    // =========
    void addNode(Node node);
    void addEdge(std::string origin, std::string destination); // Liga 2 nós já existentes (grafo não direcionado)

    // ========
    //  Buscas
    // ========
    int searchNodeIndex(std::string node);                        // Busca o indice de um nó no vetor nodes
    std::vector<Edge> searchNodeEdges(std::string node);          // Busca todas as arestas ligadas a um determinado vertice
    bool isNodesConected(std::string node_1, std::string node_2); // Verifica se existe aresta entre 2 vertices
};

#endif