#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "disjoint_set.h"
#include "edge.h"
#include "node.h"
#include "rb_tree.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Graph
{
protected:
    int size;

public:
    map<int, Node *> nodes;

public:
    Graph();
    void addNode(int v_key, map<string, any> attr);
    void addEdge(int v_key_from, int v_key_to);
    Node *&operator[](int index);
    virtual string dumpDot(string filename) const
    {

        string out = "";

        for (auto const &[k, v] : this->nodes)
            out += v->dumpNode();

        out += "\n";

        for (auto const &[k, v] : this->nodes)
            out += v->dumpEdges();

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
};

#endif
