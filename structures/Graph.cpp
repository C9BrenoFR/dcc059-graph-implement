#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <string>
#include <vector>
#include <fstream>

Graph::Graph(std::string instance)
{
    std::ifstream file("instances/" + instance);

    int numNodes;
    file >> numNodes;

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

Graph::~Graph()
{
    for (Node *node : nodes)
        delete node;
    for (Edge *edge : edges)
        delete edge;
}

void Graph::addNode(int id, const std::string &name)
{
    nodeIndex[name] = id;
    nodes.push_back(new Node(id, name));
}

void Graph::addEdge(const std::string &origin, const std::string &destination)
{
    if (nodeIndex.find(origin) == nodeIndex.end() ||
        nodeIndex.find(destination) == nodeIndex.end())
        return;

    edges.push_back(new Edge(origin, destination));
}

std::vector<Edge> Graph::searchNodeEdges(std::string node)
{
    if (nodeIndex.find(node) == nodeIndex.end())
        return {};

    std::vector<Edge> foundEdges;
    for (Edge *edge : edges)
    {
        if (edge->getOrigin() == node || edge->getDestination() == node)
        {
            foundEdges.push_back(*edge);
        }
    }

    return foundEdges;
}

bool Graph::isNodesConected(std::string node_1, std::string node_2)
{
    if (nodeIndex.find(node_1) == nodeIndex.end() ||
        nodeIndex.find(node_2) == nodeIndex.end())
        return false;

    for (Edge *edge : edges)
    {
        if (edge->getOrigin() == node_1 || edge->getDestination() == node_1)
            if (edge->getOrigin() == node_2 || edge->getDestination() == node_2)
                return true;
    }

    return false;
}