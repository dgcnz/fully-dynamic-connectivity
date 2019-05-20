#ifndef __GRIDNODE_H__
#define __GRIDNODE_H__
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

class GNode
{
public:
    int key;
    vector<GNode *> edges;
    map<string, any> attr;

    /*****************************************************/

    GNode(int key, map<string, any> attr);

    void addEdge(GNode *v);
    void removeEdge(GNode *v);
    string dumpGNode();
    string dumpEdges();

    /*****************************************************/

    friend bool operator==(const GNode &v1, const GNode &v2);
    friend std::ostream &operator<<(std::ostream &os, const GNode &v);
};

#endif
