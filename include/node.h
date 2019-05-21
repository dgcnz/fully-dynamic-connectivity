#ifndef __NODE_H__
#define __NODE_H__

#include "edge.h"
#include "rb_node.h"
#include <algorithm>
#include <any>
#include <experimental/optional>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::experimental::nullopt;
using std::experimental::optional;
using Coordinates = pair<int, int>;

class Edge;
class SFNode;

class Node
{
public:
    int key;
    vector<Edge *> edges;
    map<string, any> attr;

    /*****************************************************/
    Node();
    Node(int key, map<string, any> attr);

    virtual void addEdge(Node *v);
    virtual void removeEdge(Node *v);
    string dumpNode();
    string dumpEdges();

    /*****************************************************/

    friend bool operator==(const Node &v1, const Node &v2);
    friend std::ostream &operator<<(std::ostream &os, const Node &v);
};

class SFNode
{
public:
    int key;
    map<string, any> attr;
    vector<SFEdge *> edges;
    RBNode *first_occurrence;
    RBNode *last_occurrence;

public:
    SFNode(int key, map<string, any> attr)
    {
        this->key = key;
        this->attr = attr;
        this->first_occurrence = this->last_occurrence = nullptr;
    }
    void addEdge(SFNode *v);
    void removeEdge(SFEdge *e);
    string dumpNode();
    string dumpEdges();
};

#endif
