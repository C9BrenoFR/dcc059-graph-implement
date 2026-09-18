#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
private:
    int id;
    std::string name;

public:
    Node(int id, std::string name) : id(id), name(name) {}
    ~Node() {}

    int getId() { return id; }
    std::string getName() { return name; }

    void setId(int id) { this->id = id; }
    void setName(std::string name) { this->name = name; }
};

#endif