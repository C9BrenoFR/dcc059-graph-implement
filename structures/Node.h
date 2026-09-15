#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
private:
    std::string id;

public:
    Node(std::string id) : id(id) {}
    ~Node() {}

    std::string getId() { return id; }

    void setId(std::string id) { this->id = id; }
};

#endif