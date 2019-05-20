#ifndef __EDGE_H__
#define __EDGE_H__

#include <ostream>
#include <string>
#include <utility>
#include <vector>

class Node;

using namespace std;

class Edge
{
    Node *first;
    Node *second;

public:
    Edge(Node *v1, Node *v2);
    virtual ~Edge();
    Node *operator[](int index);
    template <typename T> inline bool operator==(const T &e);
    friend ostream &operator<<(ostream &os, const Edge &e);
};

class SFEdge : public Edge
{
    int level;

public:
    SFEdge(Node *v1, Node *v2, int level);
};

class NonTreeEdge : public SFEdge
{
    vector<Node **> reverse_non_tree;
};

class TreeEdge : public SFEdge
{
};

#endif
