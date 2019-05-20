#include "../lib/edge.h"
#include "../lib/node.h"

#include <iostream>
#include <utility>

using namespace std;

Edge::Edge(Node *v1, Node *v2)
{
    this->nodes[0] = v1;
    this->nodes[1] = v2;
}

inline bool Edge::operator==(const Edge &e)
{
    return this->nodes[0]->key == e.nodes[0]->key
        && this->nodes[1]->key == e.nodes[1]->key;
}
bool Edge::is(int vFrom, int vTo) const
{
    return (this->nodes[0]->key == vFrom && this->nodes[1]->key == vTo);
}
Node *Edge::operator[](int index)
{
    assert(index >= 0 && index <= 1);
    return this->nodes[index];
}

std::ostream &operator<<(std::ostream &os, const Edge &e)
{
    os << "edge: (" << e.nodes[0]->key << ", " << e.nodes[1]->key << ")\n";
    return os;
}
Edge::~Edge()
{
    std::cout << "deleting " << *(this);
    this->nodes[0] = this->nodes[1] = nullptr;
    std::cout << "...    done.\n";
}
