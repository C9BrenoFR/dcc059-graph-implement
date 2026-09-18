#include "GraphMi.h"
#include "Node.h"
#include "Edge.h"
#include <string>
#include <fstream>

GraphMi::GraphMi(std::string instance)
{
    std::ifstream file("instances/" + instance);

    int numNodes;
    file >> numNodes;

    edgeCount = 0;

    for (int i = 0; i < numNodes; i++)
    {
        std::string name;
        file >> name;
        addNode(i, name);
    }

    std::string origin, destination;
    std::vector<std::pair<std::string, std::string>> edges;
    while (file >> origin >> destination)
        edges.emplace_back(origin, destination);

    for (auto &row : incidencyMatrix)
        row.reserve(edges.size());

    for (auto &e : edges)
        addEdge(e.first, e.second);
}

GraphMi::~GraphMi()
{
    for (Node *node : nodes)
        delete node;
}

void GraphMi::addNode(int id, const std::string &name)
{
    nodeIndex[name] = id;
    nodes.push_back(new Node(id, name));
    incidencyMatrix.emplace_back();
}

void GraphMi::addEdge(const std::string &origin, const std::string &destination)
{
    auto itO = nodeIndex.find(origin);
    auto itD = nodeIndex.find(destination);

    if (itO == nodeIndex.end() || itD == nodeIndex.end())
        return;

    int idO = itO->second;
    int idD = itD->second;

    for (auto &row : incidencyMatrix)
        row.push_back(0);

    incidencyMatrix[idO][edgeCount] = 1;
    incidencyMatrix[idD][edgeCount] = 1;
    edgeCount++;
}

std::vector<Edge> GraphMi::searchNodeEdges(std::string node)
{
    auto it = nodeIndex.find(node);
    if (it == nodeIndex.end())
        return {};

    int id = it->second;

    std::vector<Edge> foundEdges;

    for (int col = 0; col < edgeCount; col++)
    {
        if (incidencyMatrix[id][col] == 0)
            continue;

        for (int row = 0; row < (int)nodes.size(); row++)
        {
            if (row != id && incidencyMatrix[row][col] != 0)
            {
                std::string destination = nodes[row]->getName();
                foundEdges.push_back(Edge(node, destination));
                break;
            }
        }
    }

    return foundEdges;
}

bool GraphMi::isNodesConected(std::string node_1, std::string node_2)
{
    auto it1 = nodeIndex.find(node_1);
    auto it2 = nodeIndex.find(node_2);

    if (it1 == nodeIndex.end() || it2 == nodeIndex.end())
        return false;

    int id1 = it1->second;
    int id2 = it2->second;

    for (int col = 0; col < edgeCount; col++)
    {
        if (incidencyMatrix[id1][col] != 0 && incidencyMatrix[id2][col] != 0)
            return true;
    }

    return false;
}