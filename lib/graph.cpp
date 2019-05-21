#include "graph.h"

Graph::Graph()
{
}

void Graph::addNode(int v_key, map<string, any> attr)
{
    ++this->size;
    (this->nodes)[v_key] = new Node(v_key, attr);
}

void Graph::addEdge(int v_key_from, int v_key_to)
{
    this->nodes[v_key_from]->addEdge(this->nodes[v_key_to]);
    this->nodes[v_key_to]->addEdge(this->nodes[v_key_from]);
}

Node *&Graph::operator[](int index)
{
    return this->nodes[index];
}
