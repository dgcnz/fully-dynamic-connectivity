#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "../lib/disjoint_set.h"
#include "../lib/node.h"
#include <array>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <utility>
#include <vector>

using namespace std;

class Graph
{
    int size;
    int av_nodes;
    Node **nodes;

public:
    Graph(const Graph *const G);
    Graph(int size);
    void addNode(int v_key, map<string, any> attr);
    void addEdge(int v_key_from, int v_key_to);
    void removeEdge(int v_key_from, int v_key_to);
    void inheritVertices(const Graph *const G);
    int getSize() const;
    Node *&operator[](int index);
    Graph *getSpanningForest();
    string dumpDot(string filename = "") const;
    friend class Forest;
};

#endif
