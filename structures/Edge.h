#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge
{
private:
    std::string origin;
    std::string destination;

public:
    Edge(std::string origin, std::string destination) : origin(origin), destination(destination) {}
    ~Edge() {}

    std::string getOrigin() { return origin; }
    std::string getDestination() { return destination; }

    void setOrigin(std::string node) { origin = node; }
    void setDestination(std::string node) { destination = node; }
};

#endif