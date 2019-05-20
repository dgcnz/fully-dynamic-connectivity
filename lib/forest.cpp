#include "forest.h"

Forest::Forest(const GGraph *const G)
{
    this->inheritVertices(G);
    this->getSpanningForest(G);
}

void Forest::addNode(int v_key, map<string, any> attr)
{
    ++this->size;
    (this->nodes)[v_key] = new Node(v_key, attr);
}

void Forest::inheritVertices(const GGraph *const G)
{
    for (int i = 0; i < G->av_nodes; ++i)
        this->addNode(i, G->nodes[i]->attr);
}

int Forest::getSize() const
{
    return this->size;
}

void Forest::addEdge(int v_key_from, int v_key_to)
{
    this->nodes[v_key_from]->addEdge(this->nodes[v_key_to]);
    this->nodes[v_key_to]->addEdge(this->nodes[v_key_from]);
}

void Forest::getSpanningForest(const GGraph *const G)
{
    DisjointSet DS(this->size);
    vector<pair<int, int>> GE;

    for (auto const &[key, v] : nodes)
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

Node *&Forest::operator[](int index)
{
    assert(index >= 0 && index < size);
    return this->nodes[index];
}
