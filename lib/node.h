#ifndef __NODE_H__
#define __NODE_H__
#include <algorithm>
#include <any>
#include <experimental/optional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::experimental::nullopt;
using std::experimental::optional;
using Coordinates = pair<int, int>;

class Node
{
public:
    int key;
    vector<Node *> edges;
    map<string, any> attr;

    /*****************************************************/

    Node(int key, map<string, any> attr);

    void addEdge(Node *v);
    void removeEdge(Node *v);
    string dumpNode();
    string dumpEdges();

    /*****************************************************/

    friend bool operator==(const Node &v1, const Node &v2);
    friend std::ostream &operator<<(std::ostream &os, const Node &v);
};

#endif
