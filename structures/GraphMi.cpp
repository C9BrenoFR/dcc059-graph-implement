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

GraphMi::~GraphMi()
{
    for (Node *node : nodes)
        delete node;
}

void GraphMi::addNode(Node node)
{
    nodes.push_back(new Node(node));

    int numEdges = incidencyMatrix.empty() ? 0 : incidencyMatrix[0].size();
    incidencyMatrix.emplace_back(numEdges, 0);
}

void GraphMi::addEdge(std::string origin, std::string destination)
{
    int originIndex = searchNodeIndex(origin);
    int destinationIndex = searchNodeIndex(destination);

    if (originIndex < 0 || destinationIndex < 0)
        return;

    for (auto &row : incidencyMatrix)
        row.push_back(0);

    int edgeColumn = incidencyMatrix[originIndex].size() - 1;
    incidencyMatrix[originIndex][edgeColumn] = 1;
    incidencyMatrix[destinationIndex][edgeColumn] = 1;
}

int GraphMi::searchNodeIndex(std::string node)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getId() == node)
            return i;
    }
    return -1;
}

std::vector<Edge> GraphMi::searchNodeEdges(std::string node)
{
    std::vector<Edge> foundEdges;
    int index = this->searchNodeIndex(node);

    if (index < 0)
        return foundEdges;

    int numEdges = incidencyMatrix[index].size();

    for (int col = 0; col < numEdges; col++)
    {
        if (incidencyMatrix[index][col] == 0)
            continue;

        for (int row = 0; row < nodes.size(); row++)
        {
            if (row != index && incidencyMatrix[row][col] != 0)
            {
                std::string destination = nodes[row]->getId();
                foundEdges.push_back(Edge(node, destination));
                break;
            }
        }
    }

    return foundEdges;
}

bool GraphMi::isNodesConected(std::string node_1, std::string node_2)
{
    int index_1 = this->searchNodeIndex(node_1);
    int index_2 = this->searchNodeIndex(node_2);

    if (index_1 < 0 || index_2 < 0)
        return false;

    int numEdges = incidencyMatrix[index_1].size();

    for (int col = 0; col < numEdges; col++)
    {
        if (incidencyMatrix[index_1][col] != 0 && incidencyMatrix[index_2][col] != 0)
            return true;
    }

    return false;
}