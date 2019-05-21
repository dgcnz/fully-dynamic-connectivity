#ifndef __FOREST_H__
#define __FOREST_H__

#include "disjoint_set.h"
#include "edge.h"
#include "et_trees.h"
#include "graph.h"
#include "gridgraph.h"
#include "node.h"
#include "rb_tree.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Forest : public Graph
{
    set<int> roots;
    vector<ET_Tree *> eulerian;

public:
    Forest(void);
    void inheritVertices(const Graph *const G);
    void getSpanningForest(const Graph *const G);
    void buildEulerian(void);
};

#endif
