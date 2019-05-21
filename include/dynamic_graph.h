#ifndef __DYNAMIC_GRAPH_H__
#define __DYNAMIC_GRAPH_H__

#include "forest.h"
#include "graph.h"
#include <cmath>

using namespace std;

class DynamicGraph : public Graph
{
    Forest **hforests;
    int lmax;

public:
    DynamicGraph(int size)
    {
        this->lmax = (int)floor(log2(this->size));
        this->hforests = (Forest **)malloc(sizeof(Forest *) * lmax);
    }
};

#endif
