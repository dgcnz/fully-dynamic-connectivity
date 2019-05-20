#ifndef __FOREST_H__
#define __FOREST_H__

#include "../lib/disjoint_set.h"
#include "../lib/graph.h"
#include "../lib/node.h"
#include "../lib/rb_tree.h"
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
    int av_nodes;
    Node **nodes;
    set<int> roots;
    vector<RBTree *> ETTrees;

public:
    Forest(const Graph *const G);
    void inheritVertices(const Graph *const G);
    void addNode(int v_key, map<string, any> attr);
    void addEdge(int v_key_from, int v_key_to);
    void getSpanningForest(const Graph *const G);
    int getSize() const;
    Node *&operator[](int index);
};

#endif
