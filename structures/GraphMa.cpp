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

    adjacencyMatrix.assign(numNodes, std::vector<int>(numNodes, 0));

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

GraphMa::~GraphMa()
{
    for (Node *node : nodes)
        delete node;
}

void GraphMa::addNode(int id, const std::string &name)
{
    nodeIndex[name] = id;
    nodes.push_back(new Node(id, name));
}

void GraphMa::addEdge(const std::string &origin, const std::string &destination)
{
    auto itO = nodeIndex.find(origin);
    auto itD = nodeIndex.find(destination);

    if (itO == nodeIndex.end() || itD == nodeIndex.end())
        return;

    int idO = itO->second;
    int idD = itD->second;

    adjacencyMatrix[idO][idD] = 1;
    adjacencyMatrix[idD][idO] = 1;
}

std::vector<Edge> GraphMa::searchNodeEdges(std::string node)
{
    auto it = nodeIndex.find(node);
    if (it == nodeIndex.end())
        return {};

    int id = it->second;

    std::vector<Edge> foundEdges;
    for (int j = 0; j < (int)adjacencyMatrix[id].size(); j++)
    {
        if (adjacencyMatrix[id][j] != 0)
        {
            std::string destination = nodes[j]->getName();
            foundEdges.push_back(Edge(node, destination));
        }
    }

    return foundEdges;
}

bool GraphMa::isNodesConected(std::string node_1, std::string node_2)
{
    auto it1 = nodeIndex.find(node_1);
    auto it2 = nodeIndex.find(node_2);

    if (it1 == nodeIndex.end() || it2 == nodeIndex.end())
        return false;

    return adjacencyMatrix[it1->second][it2->second] != 0;
}