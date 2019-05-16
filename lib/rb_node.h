#ifndef __RB_NODE_H__
#define __RB_NODE_H__

#include <any>
#include <map>
#include <sstream>
#include <string>

using namespace std;

enum RBNodeColor
{
    BLACK = 0,
    RED = 1
};

struct RBNode
{
    int key;
    RBNodeColor color;
    map<string, any> attr;
    RBNode *left;
    RBNode *right;
    RBNode *parent;

    explicit RBNode(int key, map<string, any> attr, RBNode *parent);
    explicit RBNode(RBNode *parent);
    inline bool operator==(const RBNode &t) const;
    inline bool operator<(const RBNode &t) const;
    void changeColor(RBNodeColor color);

    string dumpNode() const;
    string dumpEdges() const;
    string dumpAllChildren() const;
    string dumpAllChildrenEdges() const;

    friend std::ostream &operator<<(std::ostream &os, const RBNode &v);
};

#endif
