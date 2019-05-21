#include "forest.h"

Forest::Forest(void)
{
    this->size = 0;
}

void Forest::inheritVertices(const Graph *const G)
{
    for (auto const &[k, v] : G->nodes)
        this->addNode(v->key, v->attr);
}

void Forest::getSpanningForest(const Graph *const G)
{
    this->inheritVertices(G);

    DisjointSet DS(this->size);
    vector<pair<int, int>> GE;

    for (auto const &[k, v] : G->nodes)
    {
        for (auto const &e : v->edges)
            GE.push_back(make_pair((*e)[0]->key, (*e)[1]->key));
    }

    for (auto const &[u, v] : GE)
    {
        if (DS.findSet(u) != DS.findSet(v))
        {
            this->addEdge(u, v);
            DS.unionSet(u, v);
        }
    }

    for (int i = 0; i < this->size; ++i)
        this->roots.insert(DS.findSet(i));
}

void Forest::buildEulerian(void)
{
    for (auto const &r : this->roots)
    {
        this->eulerian.push_back(new ET_Tree(this->nodes[r]));
    }
}
