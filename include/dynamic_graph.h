#ifndef __DYNAMIC_GRAPH_H__
#define __DYNAMIC_GRAPH_H__

#include "forest.h"
#include "graph.h"
#include <cmath>
#include <string>

using namespace std;

class DynamicGraph
{
    Graph *G;
    Forest **hforests;
    Forest *SF;
    int lmax;
    int size;

public:
    DynamicGraph(int size);
    DynamicGraph(Graph *G);
    bool isConnected(int k1, int k2);
    void dumpDot();
};

#endif
