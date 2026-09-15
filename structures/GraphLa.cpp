#include "GraphLa.h"
#include "Node.h"
#include "Edge.h"
#include <string>
#include <fstream>

GraphLa::GraphLa(std::string instance)
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

GraphLa::~GraphLa()
{
    for (Node *node : nodes)
        delete node;
}

void GraphLa::addNode(Node node)
{
    nodes.emplace_back(new Node(node));
    adjacencyList.emplace_back();
}

void GraphLa::addEdge(std::string origin, std::string destination)
{
    int originIndex = searchNodeIndex(origin);
    int destinationIndex = searchNodeIndex(destination);

    if (originIndex < 0 || destinationIndex < 0)
        return;

    adjacencyList[originIndex].push_back(destination);
    adjacencyList[destinationIndex].push_back(origin);
}

int GraphLa::searchNodeIndex(std::string node)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getId() == node)
        {
            return i;
        }
    }
    return -1;
}

std::vector<std::string> GraphLa::searchNodeEdges(std::string node)
{
    int index = this->searchNodeIndex(node);

    if (index < 0)
        return {};

    return adjacencyList[index];
}

bool GraphLa::isNodesConected(std::string node_1, std::string node_2)
{
    int index = this->searchNodeIndex(node_1);

    if (index < 0)
        return false;

    std::vector<std::string> list = adjacencyList[index];

    for (std::string &node : list)
    {
        if (node == node_2)
            return true;
    }

    return false;
}