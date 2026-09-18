#ifndef GRAPHMI_H
#define GRAPHMI_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <vector>
#include <unordered_map>

/*
Grafo com base na matriz de incidência.

Cada nó recebe um id numérico sequencial que é usado como índice direto
nas linhas da matriz. As colunas representam as arestas.
O unordered_map nodeIndex resolve nome → id em O(1).

Matriz: N linhas (nós) x E colunas (arestas)
incidencyMatrix[nodeId][edgeCol] = 1 se o nó participa da aresta
*/
class GraphMi
{
private:
    std::vector<Node *> nodes;
    std::vector<std::vector<bool>> incidencyMatrix;
    std::unordered_map<std::string, int> nodeIndex; // nome → id
    int edgeCount;                                   

public:
    // ========================
    //  Construtor e Destrutor
    // ========================
    GraphMi(std::string instance); // Carrega o grafo com base em um arquivo na pasta de instancias
    GraphMi() : edgeCount(0) {}
    ~GraphMi();

    // =========
    //  Getters
    // =========
    std::vector<Node *> getNodes() { return nodes; }
    std::vector<std::vector<bool>> getIncidencyMatrix() { return incidencyMatrix; }

    // =========
    //  Setters
    // =========
    void addNode(int id, const std::string &name);
    void addEdge(const std::string &origin, const std::string &destination); 

    // ========
    //  Buscas
    // ========
    std::vector<Edge> searchNodeEdges(std::string node);          // Busca todas as arestas ligadas a um determinado vertice
    bool isNodesConected(std::string node_1, std::string node_2); // Verifica se existe aresta entre 2 vertices
};

#endif