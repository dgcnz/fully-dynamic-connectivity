#ifndef __FOREST_H__
#define __FOREST_H__

#include "disjoint_set.h"
#include "edge.h"
#include "et_trees.h"
#include "graph.h"
#include "gridgraph.h"
#include "node.h"
#include "rb_tree.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Forest
{
    int size;
    map<int, SFNode *> nodes;
    set<int> roots;
    vector<ET_Tree *> eulerian;

public:
    Forest(void);
    SFNode *&operator[](int index);

    void addNode(int v_key, map<string, any> attr);
    void addEdge(int v_key_from, int v_key_to);
    void inheritVertices(const Graph *const G);
    void getSpanningForest(const Graph *const G);
    void buildEulerian(void);
    bool isConnected(SFNode *v1, SFNode *v2)
    {
        return (eulerian[0]->findRoot(v1->first_occurrence)
            == eulerian[0]->findRoot(v2->first_occurrence));
    }
    string dumpETDot(string filename = "");
    string dumpDot(string filename) const
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
