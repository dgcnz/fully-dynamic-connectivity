#include "graph.h"

Graph::Graph()
{
    this->size = 0;
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

void Graph::removeEdge(int v_key_from, int v_key_to)
{
    this->nodes[v_key_from]->removeEdge(this->nodes[v_key_to]);
    this->nodes[v_key_to]->removeEdge(this->nodes[v_key_from]);
}
