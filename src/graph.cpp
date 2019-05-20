#include "../lib/graph.h"

Graph::Graph(const Graph *const G)
{
    this->size = G->size;
    this->av_nodes = 0;

    this->nodes = (Node **)malloc(sizeof(Node *) * size);
    this->inheritVertices(G);
}
Graph::Graph(int size)
    : size(size)
{
    this->nodes = (Node **)malloc(sizeof(Node *) * size);
    this->av_nodes = 0;
}

void Graph::addNode(int v_key, map<string, any> attr)
{

    ++this->av_nodes;
    (this->nodes)[v_key] = new Node(v_key, attr);
}

void Graph::addEdge(int v_key_from, int v_key_to)
{
    this->nodes[v_key_from]->addEdge(this->nodes[v_key_to]);
    this->nodes[v_key_to]->addEdge(this->nodes[v_key_from]);
}

void Graph::removeEdge(int v_key_from, int v_key_to)
{
    this->nodes[v_key_from]->removeEdge(this->nodes[v_key_to]);
    this->nodes[v_key_to]->removeEdge(this->nodes[v_key_from]);
}

void Graph::inheritVertices(const Graph *const G)
{
    for (int i = 0; i < G->av_nodes; ++i)
        this->addNode(i, G->nodes[i]->attr);
}

int Graph::getSize() const
{
    return this->size;
}

Node *&Graph::operator[](int index)
{
    assert(index >= 0 && index < size);
    return this->nodes[index];
}

Graph *Graph::getSpanningForest()
{
    Graph *SF = new Graph(this);
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
            SF->addEdge(u, v);
            DS.unionSet(u, v);
        }
    }
    return SF;
}

string Graph::dumpDot(string filename) const
{
    // COMPILE: dot -Kfdp -n -Gsplines=True -Tpng filename > output.png

    string out = "";

    for (int i = 0; i < this->av_nodes; ++i)
        out += nodes[i]->dumpNode();

    out += "\n";

    for (int i = 0; i < this->av_nodes; ++i)
        out += nodes[i]->dumpEdges();

    if (!filename.empty())
    {
        cout << "Saving file to " << filename << endl;
        ofstream FILE_;
        FILE_.open(filename);
        FILE_ << "strict graph {\n";
        FILE_ << out;
        FILE_ << "}\n";
        FILE_.close();
    }
    return out;
}
