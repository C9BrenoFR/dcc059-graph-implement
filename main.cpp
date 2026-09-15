#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "GraphLa.h"
#include "GraphMa.h"
#include "GraphMi.h"
#include "Edge.h"
#include "Node.h"

namespace col
{
    const std::string reset = "\033[0m";
    const std::string bold = "\033[1m";
    const std::string dim = "\033[2m";
    const std::string cyan = "\033[36m";
    const std::string green = "\033[32m";
    const std::string yellow = "\033[33m";
    const std::string red = "\033[31m";
    const std::string magenta = "\033[35m";
}

void printHeader(const std::string &title)
{
    std::cout << "\n"
              << col::cyan << col::bold << "== " << title << " ==" << col::reset << "\n";
}

void printEdges(const std::vector<Edge> &edges)
{
    if (edges.empty())
    {
        std::cout << col::dim << "  (nenhuma aresta encontrada)" << col::reset << "\n";
        return;
    }

    for (Edge edge : edges)
        std::cout << "  " << col::yellow << edge.getOrigin() << col::reset
                  << " -- " << col::yellow << edge.getDestination() << col::reset << "\n";
}

void printAdjacency(const std::vector<std::string> &adjacentNodes)
{
    if (adjacentNodes.empty())
    {
        std::cout << col::dim << "  (nenhuma aresta encontrada)" << col::reset << "\n";
        return;
    }

    for (const std::string &node : adjacentNodes)
        std::cout << "  -> " << col::yellow << node << col::reset << "\n";
}

void printNodes(const std::vector<Node *> &nodes)
{
    if (nodes.empty())
    {
        std::cout << col::dim << "  (nenhum no encontrado)" << col::reset << "\n";
        return;
    }

    std::cout << col::dim << "  Nos (" << nodes.size() << "): " << col::reset;
    for (size_t i = 0; i < nodes.size(); i++)
        std::cout << col::yellow << nodes[i]->getId() << col::reset << (i + 1 < nodes.size() ? ", " : "\n");
}

// Lê um inteiro entre min e max, repetindo o prompt até um valor válido
int readOption(const std::string &prompt, int min, int max)
{
    int option;
    while (true)
    {
        std::cout << col::green << prompt << col::reset;
        if (std::cin >> option && option >= min && option <= max)
            return option;

        std::cout << col::red << "Opcao invalida, tente novamente." << col::reset << "\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

std::string readNode(const std::string &prompt)
{
    std::string node;
    std::cout << col::green << prompt << col::reset;
    std::cin >> node;
    return node;
}

void loadGraphs(std::string instance, Graph *graph, GraphLa *graphLa, GraphMa *graphMa, GraphMi *graphMi)
{
    std::ifstream file("instances/" + instance);

    int numNodes;
    file >> numNodes;

    for (int i = 0; i < numNodes; i++)
    {
        std::string id;
        file >> id;
        graph->addNode(Node(id));
        graphLa->addNode(Node(id));
        graphMa->addNode(Node(id));
        graphMi->addNode(Node(id));
    }

    std::string origin, destination;
    while (file >> origin >> destination)
    {
        graph->addEdge(Edge(origin, destination));
        graphLa->addEdge(origin, destination);
        graphMa->addEdge(origin, destination);
        graphMi->addEdge(origin, destination);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Erro: Faltando argumentos!\n";
        std::cout << "Uso correto: " << argv[0] << " <instancia_do_grafo>\n";
        return 1;
    }

    std::string archieve = argv[1];

    std::cout << col::magenta << col::bold
              << "*** Teoria dos Grafos - DCC059 ***" << col::reset << "\n";
    std::cout << "Carregando instancia " << col::yellow << archieve << col::reset << " ...\n";

    Graph graph;
    GraphLa graphLa;
    GraphMa graphMa;
    GraphMi graphMi;

    loadGraphs(archieve, &graph, &graphLa, &graphMa, &graphMi);

    std::cout << col::green << "Instancia carregada com sucesso!" << col::reset
              << " (" << graph.getNodes().size() << " nos)\n";

    while (true)
    {
        printHeader("Representacao");
        std::cout << "1. Grafo (vetores de nos/arestas)\n";
        std::cout << "2. Lista de adjacencia\n";
        std::cout << "3. Matriz de adjacencia\n";
        std::cout << "4. Matriz de incidencia\n";
        std::cout << "0. Sair\n";
        int representation = readOption("Escolha: ", 0, 4);

        if (representation == 0)
            break;

        while (true)
        {
            printHeader("Acao");
            std::cout << "1. Mostrar nos\n";
            std::cout << "2. Buscar arestas de um no\n";
            std::cout << "3. Verificar se dois nos sao conectados\n";
            std::cout << "0. Voltar\n";
            int action = readOption("Escolha: ", 0, 3);

            if (action == 0)
                break;

            std::cout << "\n";

            if (action == 1)
            {
                switch (representation)
                {
                case 1:
                    printNodes(graph.getNodes());
                    break;
                case 2:
                    printNodes(graphLa.getNodes());
                    break;
                case 3:
                    printNodes(graphMa.getNodes());
                    break;
                case 4:
                    printNodes(graphMi.getNodes());
                    break;
                }
            }
            else if (action == 2)
            {
                std::string node = readNode("No: ");
                std::cout << "\n";

                std::chrono::high_resolution_clock::time_point start;
                std::chrono::high_resolution_clock::time_point end;

                switch (representation)
                {
                case 1:
                {
                    start = std::chrono::high_resolution_clock::now();
                    std::vector<Edge> result_1 = graph.searchNodeEdges(node);
                    end = std::chrono::high_resolution_clock::now();
                    printEdges(result_1);
                    break;
                }
                case 2:
                {
                    start = std::chrono::high_resolution_clock::now();
                    std::vector<std::string> result_2 = graphLa.searchNodeEdges(node);
                    end = std::chrono::high_resolution_clock::now();
                    printAdjacency(result_2);
                    break;
                }
                case 3:
                {
                    start = std::chrono::high_resolution_clock::now();
                    std::vector<Edge> result_3 = graphMa.searchNodeEdges(node);
                    end = std::chrono::high_resolution_clock::now();
                    printEdges(result_3);
                    break;
                }
                case 4:
                {
                    start = std::chrono::high_resolution_clock::now();
                    std::vector<Edge> result_4 = graphMi.searchNodeEdges(node);
                    end = std::chrono::high_resolution_clock::now();
                    printEdges(result_4);
                    break;
                }
                }
                double elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();
                std::cout << col::dim << "  (busca levou " << elapsedMs << " ms)" << col::reset << "\n";
            }
            else if (action == 3)
            {
                std::string node1 = readNode("No 1: ");
                std::string node2 = readNode("No 2: ");
                bool connected = false;

                auto start = std::chrono::high_resolution_clock::now();
                switch (representation)
                {
                case 1:
                    connected = graph.isNodesConected(node1, node2);
                    break;
                case 2:
                    connected = graphLa.isNodesConected(node1, node2);
                    break;
                case 3:
                    connected = graphMa.isNodesConected(node1, node2);
                    break;
                case 4:
                    connected = graphMi.isNodesConected(node1, node2);
                    break;
                }
                auto end = std::chrono::high_resolution_clock::now();
                double elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();

                std::cout << "\n"
                          << (connected ? col::green + "Conectados!" : col::red + "Nao conectados.")
                          << col::reset << "\n";
                std::cout << col::dim << "  (busca levou " << elapsedMs << " ms)" << col::reset << "\n";
            }
        }
    }

    std::cout << col::cyan << "\nAte mais!\n"
              << col::reset;
    return 0;
}
