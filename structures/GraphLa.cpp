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

    capacity = numNodes;
    adjacencyList = new LinkedList[capacity];

    for (int i = 0; i < numNodes; i++)
    {
        std::string name;
        file >> name;
        addNode(i, name);
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
    delete[] adjacencyList;
}

void GraphLa::addNode(int id, const std::string &name)
{
    nodeIndex[name] = id;
    nodes.push_back(new Node(id, name));
}

void GraphLa::addEdge(const std::string &origin, const std::string &destination)
{
    auto itO = nodeIndex.find(origin);
    auto itD = nodeIndex.find(destination);

    if (itO == nodeIndex.end() || itD == nodeIndex.end())
        return;

    int idO = itO->second;
    int idD = itD->second;

    adjacencyList[idO].insert(idD);
    adjacencyList[idD].insert(idO);
}

std::vector<std::string> GraphLa::searchNodeEdges(std::string node)
{
    auto it = nodeIndex.find(node);
    if (it == nodeIndex.end())
        return {};

    int id = it->second;

    std::vector<std::string> result;
    result.reserve(adjacencyList[id].size());

    for (int neighborId : adjacencyList[id])
        result.push_back(nodes[neighborId]->getName());

    return result;
}

bool GraphLa::isNodesConected(std::string node_1, std::string node_2)
{
    auto it1 = nodeIndex.find(node_1);
    auto it2 = nodeIndex.find(node_2);

    if (it1 == nodeIndex.end() || it2 == nodeIndex.end())
        return false;

    int id1 = it1->second;
    int id2 = it2->second;

    return adjacencyList[id1].contains(id2);
}