#include "GraphMa.h"
#include "Node.h"
#include "Edge.h"
#include <string>
#include <fstream>

GraphMa::GraphMa(std::string instance)
{
    std::ifstream file("instances/" + instance);

    int numNodes;
    file >> numNodes;

    for (int i = 0; i < numNodes; i++)
    {
        std::string id;
        file >> id;
        addNode(Node(id));
    }

    std::string origin, destination;
    while (file >> origin >> destination)
    {
        addEdge(origin, destination);
    }
}

GraphMa::~GraphMa()
{
    for (Node *node : nodes)
        delete node;
}

void GraphMa::addNode(Node node)
{
    nodes.push_back(new Node(node));

    int numNodes = nodes.size();

    for (auto &row : adjacencyMatrix)
    {
        row.push_back(0);
    }

    adjacencyMatrix.emplace_back(numNodes, 0);
}

void GraphMa::addEdge(std::string origin, std::string destination)
{
    int originIndex = searchNodeIndex(origin);
    int destinationIndex = searchNodeIndex(destination);

    if (originIndex < 0 || destinationIndex < 0)
        return;

    adjacencyMatrix[originIndex][destinationIndex] = 1;
    adjacencyMatrix[destinationIndex][originIndex] = 1;
}

int GraphMa::searchNodeIndex(std::string node)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getId() == node)
            return i;
    }
    return -1;
}

std::vector<Edge> GraphMa::searchNodeEdges(std::string node)
{
    std::vector<Edge> foundEdges;
    int index = this->searchNodeIndex(node);

    if (index < 0)
        return foundEdges;

    for (int j = 0; j < adjacencyMatrix[index].size(); j++)
    {
        if (adjacencyMatrix[index][j] != 0)
        {
            std::string destination = nodes[j]->getId();
            foundEdges.push_back(Edge(node, destination));
        }
    }

    return foundEdges;
}

bool GraphMa::isNodesConected(std::string node_1, std::string node_2)
{
    int index_1 = this->searchNodeIndex(node_1);
    int index_2 = this->searchNodeIndex(node_2);

    if (index_1 < 0 || index_2 < 0)
        return false;

    return adjacencyMatrix[index_1][index_2] != 0;
}