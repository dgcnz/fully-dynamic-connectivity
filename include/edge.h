#ifndef __EDGE_H__
#define __EDGE_H__

#include <ostream>
#include <string>
#include <utility>
#include <vector>

class Node;
class SFNode;

using namespace std;

class Edge
{
protected:
    Node *first;
    Node *second;

public:
    Edge(Node *v1, Node *v2);
    Edge();
    virtual ~Edge();
    Node *operator[](int index);
    template <typename T> inline bool operator==(const T &e);
    friend ostream &operator<<(ostream &os, const Edge &e);
};

class SFEdge
{
    SFNode *first;
    SFNode *second;
    int level;

public:
    SFEdge(SFNode *v1, SFNode *v2, int level = 0);
    SFNode *operator[](int index);
};

#endif
