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
    int idx = nodes.size();
    nodeIndex[node.getId()] = idx;
    nodes.emplace_back(new Node(node));
    adjacencyList.emplace_back();
}

void GraphLa::addEdge(std::string origin, std::string destination)
{
    auto itO = nodeIndex.find(origin);
    auto itD = nodeIndex.find(destination);

    if (itO == nodeIndex.end() || itD == nodeIndex.end())
        return;

    adjacencyList[itO->second].push_back(itD->second);
    adjacencyList[itD->second].push_back(itO->second);
}

int GraphLa::searchNodeIndex(std::string node)
{
    auto it = nodeIndex.find(node);
    return it != nodeIndex.end() ? it->second : -1;
}

std::vector<std::string> GraphLa::searchNodeEdges(std::string node)
{
    int idx = searchNodeIndex(node);

    if (idx < 0)
        return {};

    std::vector<std::string> result;
    result.reserve(adjacencyList[idx].size());
    for (int neighborIdx : adjacencyList[idx])
        result.push_back(nodes[neighborIdx]->getId());
    return result;
}

bool GraphLa::isNodesConected(std::string node_1, std::string node_2)
{
    int idx1 = searchNodeIndex(node_1);
    int idx2 = searchNodeIndex(node_2);

    if (idx1 < 0 || idx2 < 0)
        return false;

    for (int neighborIdx : adjacencyList[idx1])
    {
        if (neighborIdx == idx2)
            return true;
    }

    return false;
}