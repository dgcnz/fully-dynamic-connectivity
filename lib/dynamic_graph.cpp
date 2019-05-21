#include "dynamic_graph.h"
#include "forest.h"
#include "graph.h"
#include <cmath>
#include <string>

using namespace std;

DynamicGraph::DynamicGraph(int size)
{
    this->lmax = (int)floor(log2(this->size));
    this->hforests = (Forest **)malloc(sizeof(Forest *) * lmax);
}

DynamicGraph::DynamicGraph(Graph *G)
{
    this->G = G;
    this->SF = new Forest();
    this->SF->getSpanningForest(G);
    this->SF->buildEulerian();
}

bool DynamicGraph::isConnected(int k1, int k2)
{
    return SF->isConnected((*SF)[k1], (*SF)[k2]);
}
void DynamicGraph::dumpDot()
{
    cout << this->G->dumpDot("exports/dot/graph.dot") << endl;
    cout << this->SF->dumpDot("exports/dot/spanning.dot") << endl;
    cout << this->SF->dumpETDot("exports/dot/euler.dot") << endl;
}
