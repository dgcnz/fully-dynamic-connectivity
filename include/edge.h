#ifndef __EDGE_H__
#define __EDGE_H__

#include <ostream>
#include <string>
#include <utility>

using namespace std;

class Node;

class Edge
{
    Node *nodes[2];

public:
    Edge(Node *v1, Node *v2);
    inline bool operator==(const Edge &e);
    bool is(int vFrom, int vTo) const;
    Node *operator[](int index);

    ~Edge();
    friend ostream &operator<<(ostream &os, const Edge &e);
};

#endif
