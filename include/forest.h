#ifndef __FOREST_H__
#define __FOREST_H__

#include "disjoint_set.h"
#include "edge.h"
#include "gridgraph.h"
#include "node.h"
#include "rb_tree.h"
#include <array>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Forest
{
    int size;
    map<int, Node *> nodes;
    set<int> roots;

public:
    Forest(const GGraph *const G);
    void inheritVertices(const GGraph *const G);
    void addNode(int v_key, map<string, any> attr);
    void addEdge(int v_key_from, int v_key_to);
    void getSpanningForest(const GGraph *const G);
    int getSize() const;
    Node *&operator[](int index);
};

#endif
