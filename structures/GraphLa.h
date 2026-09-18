#ifndef GRAPHLA_H
#define GRAPHLA_H

#include "Node.h"
#include "Edge.h"
#include "LinkedList.h"
#include <string>
#include <vector>
#include <unordered_map>

/*
Grafo com base na lista de adjacência usando lista encadeada.

Cada nó recebe um id numérico sequencial (0, 1, 2, ...) que serve como
índice direto no array de listas encadeadas (adjacencyList).

O unordered_map nodeIndex mapeia nome → id em O(1).
A lista encadeada (LinkedList) permite inserção O(1) na cabeça.

Exemplo:
Supondo que temos um grafo simples completo com os nós A,B e C
  A recebe id=0, B recebe id=1, C recebe id=2

O adjacencyList seria:
  adjacencyList[0] → 1 → 2       (A se liga com B e C)
  adjacencyList[1] → 0 → 2       (B se liga com A e C)
  adjacencyList[2] → 0 → 1       (C se liga com A e B)
*/
class GraphLa
{
private:
    std::vector<Node *> nodes;
    LinkedList *adjacencyList;    
    int capacity;                 
    std::unordered_map<std::string, int> nodeIndex; // nome → id

public:
    // ========================
    //  Construtor e Destrutor
    // ========================
    GraphLa(std::string instance); // Carrega o grafo com base em um arquivo na pasta de instancias
    GraphLa() : adjacencyList(nullptr), capacity(0) {}
    ~GraphLa();

    // =========
    //  Getters
    // =========
    std::vector<Node *> getNodes() { return nodes; }

    // =========
    //  Setters
    // =========
    void addNode(int id, const std::string &name);
    void addEdge(const std::string &origin, const std::string &destination);
    
    // ========
    //  Buscas
    // ========
    std::vector<std::string> searchNodeEdges(std::string node);   // Busca todas as arestas ligadas a um determinado vertice
    bool isNodesConected(std::string node_1, std::string node_2); // Verifica se existe aresta entre 2 vertices
};

#endif