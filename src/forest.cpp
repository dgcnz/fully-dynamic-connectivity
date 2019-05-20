#include "../lib/forest.h"

Forest::Forest(const Graph *const G)
{
    this->size = G->size;
    this->av_nodes = 0;

    this->nodes = (Node **)malloc(sizeof(Node *) * size);
    this->inheritVertices(G);
    this->getSpanningForest(G);
}

void Forest::addNode(int v_key, map<string, any> attr)
{

    ++this->av_nodes;
    (this->nodes)[v_key] = new Node(v_key, attr);
}

void Forest::inheritVertices(const Graph *const G)
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

void Forest::getSpanningForest(const Graph *const G)
{
    DisjointSet DS(this->size);
    vector<pair<int, int>> GE;

    for (int i = 0; i < this->av_nodes; ++i)
    {
        for (auto const &v2 : this->nodes[i]->edges)
            GE.push_back(make_pair(i, v2->key));
    }

    for (auto const &[u, v] : GE)
    {
        if (DS.findSet(u) != DS.findSet(v))
        {
            this->addEdge(u, v);
            DS.unionSet(u, v);
        }
    }

    for (int i = 0; i < this->av_nodes; ++i)
        this->roots.insert(DS.findSet(i));
}

void Forest::buildETTrees()
{

}

Node *&Forest::operator[](int index)
{
    assert(index >= 0 && index < size);
    return this->nodes[index];
}
