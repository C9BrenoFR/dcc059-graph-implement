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
        std::string id;
        file >> id;
        addNode(Node(id));
    }

    std::string origin, destination;
    while (file >> origin >> destination)
    {
        addEdge(Edge(origin, destination));
    }
}

Graph::~Graph()
{
    for (Node *node : nodes)
        delete node;
    for (Edge *edge : edges)
        delete edge;
}

std::vector<Edge> Graph::searchNodeEdges(std::string node)
{
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

    for (Edge *edge : edges)
    {
        if (edge->getOrigin() == node_1 || edge->getDestination() == node_1)
            if (edge->getOrigin() == node_2 || edge->getDestination() == node_2)
                return true;
    }

    return false;
}