#ifndef __RB_NODE_H__
#define __RB_NODE_H__

#include <any>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum RBColor
{
    BLACK = 0,
    RED = 1,
    DOUBLE_BLACK = 2
};

struct RBNode
{
    int key;
    RBColor color;
    map<string, any> attr;
    RBNode *left;
    RBNode *right;
    RBNode *parent;

    explicit RBNode(int key, map<string, any> attr);
    inline bool operator==(const RBNode &t) const;
    inline bool operator<(const RBNode &t) const;

    string dumpNode() const;
    string dumpEdges() const;
    string dumpAllChildren() const;
    string dumpAllChildrenEdges() const;
    void store_rank(vector<vector<int>> &ranks, int level) const;

    friend std::ostream &operator<<(std::ostream &os, const RBNode &v);
};

#endif
