#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <vector>

/*
Grafo comum com foco total em extrutura de dados
Recebe nós e arestas como objetos e os aloca em vetores

NOTA:
Se você nunca usou a biblioteca <vector>, ela serve para otimizar o uso de vetores, com algumas funções auxiliares
Para pegar um item do vector você pode fazer de duas formas:
nodes[1] // forma comum
nodes.at(1) // Caso você acesse um item que não existe (por exemplo, indice 10 num vetor de 5 espaços) ele lança uma exceção ao invés de lixo de memória

A função push_back() usada nas funções de adicionar serve para colocar um item no final do vetor
*/
class Graph
{
private:
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

public:
    // ========================
    //  Construtor e Destrutor
    // ========================
    Graph(std::vector<Node *> nodes, std::vector<Edge *> edges) : nodes(nodes), edges(edges) {}
    Graph(std::string instance); // Carrega o grafo com base em um arquivo na pasta de instancias
    Graph() {}
    ~Graph();

    // =========
    //  Getters
    // =========
    std::vector<Node *> getNodes() { return nodes; }
    std::vector<Edge *> getEdges() { return edges; }

    // =========
    //  Setters
    // =========
    void addNode(Node node) { nodes.push_back(new Node(node)); }
    void addEdge(Edge edge) { edges.push_back(new Edge(edge)); }

    // ========
    //  Buscas
    // ========
    std::vector<Edge> searchNodeEdges(std::string node);          // Busca todas as arestas ligadas a um determinado vertice
    bool isNodesConected(std::string node_1, std::string node_2); // Verifica se existe aresta entre 2 vertices
};

#endif