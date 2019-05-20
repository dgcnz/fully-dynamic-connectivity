#ifndef __GRIDGRAPH_H__
#define __GRIDGRAPH_H__

#include "../lib/disjoint_set.h"
#include "../lib/gridnode.h"
#include <array>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <utility>
#include <vector>

using namespace std;

class GGraph
{
    int size;
    int av_nodes;
    GNode **nodes;

public:
    GGraph(const GGraph *const G);
    GGraph(int size);
    void addGNode(int v_key, map<string, any> attr);
    void addEdge(int v_key_from, int v_key_to);
    void removeEdge(int v_key_from, int v_key_to);
    void inheritVertices(const GGraph *const G);
    int getSize() const;
    GNode *&operator[](int index);
    GGraph *getSpanningForest();
    string dumpDot(string filename = "") const;
    friend class Forest;
};

#endif
