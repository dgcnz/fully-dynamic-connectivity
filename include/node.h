#ifndef __NODE_H__
#define __NODE_H__

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

class Node
{
public:
    int key;
    vector<Edge *> edges;
    map<string, any> attr;

    /*****************************************************/

    Node(int key, map<string, any> attr);

    void addEdge(Node *v);
    void removeEdge(Edge *e);
    string dumpNode();
    string dumpEdges();

    /*****************************************************/

    friend bool operator==(const Node &v1, const Node &v2);
    friend std::ostream &operator<<(std::ostream &os, const Node &v);
};

#endif
