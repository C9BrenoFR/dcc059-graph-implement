#ifndef GRAPHMA_H
#define GRAPHMA_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <vector>
#include <unordered_map>

/*
Grafo com base na matriz de adjacência.

Cada nó recebe um id numérico sequencial que é usado como índice direto
nas linhas e colunas da matriz. O unordered_map nodeIndex resolve
nome → id em O(1), eliminando a busca linear do antigo searchNodeIndex().

Verificar conexão entre dois nós é O(1): basta acessar adjacencyMatrix[id1][id2].
*/
class GraphMa
{
private:
    std::vector<Node *> nodes;
    std::vector<std::vector<int>> adjacencyMatrix;
    std::unordered_map<std::string, int> nodeIndex; // nome → id

public:
    // ========================
    //  Construtor e Destrutor
    // ========================
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
    void addNode(int id, const std::string &name);
    void addEdge(const std::string &origin, const std::string &destination);

    // ========
    //  Buscas
    // ========
    std::vector<Edge> searchNodeEdges(std::string node);          // Busca todas as arestas ligadas a um determinado vertice
    bool isNodesConected(std::string node_1, std::string node_2); // Verifica se existe aresta entre 2 vertices — O(1)!
};

#endif