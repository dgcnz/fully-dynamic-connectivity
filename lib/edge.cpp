#include "edge.h"
#include "node.h"

#include <iostream>
#include <utility>

using namespace std;

Edge::Edge(Node *v1, Node *v2)
{
    this->first = v1;
    this->second = v2;
}

template <typename T> inline bool Edge::operator==(const T &e)
{
    return this->first->key == e.first->key
        && this->second->key == e.second->key;
}

Node *Edge::operator[](int index)
{
    assert(index >= 0 && index <= 1);
    if (index == 0)
        return this->first;
    else
        return this->second;
}

std::ostream &operator<<(std::ostream &os, const Edge &e)
{
    os << "edge: (" << e.first->key << ", " << e.second->key << ")\n";
    return os;
}
Edge::~Edge()
{
    std::cout << "deleting " << *(this);
    this->first = this->second = nullptr;
    std::cout << "...    done.\n";
}

/************* EXPLICIT INSTATIATIONS *******************/

template bool Edge::operator==(const Edge &e);
template bool Edge::operator==(const pair<Node *, Node *> &e);
