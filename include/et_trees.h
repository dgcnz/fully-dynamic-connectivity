#ifndef __ET_TREES_H__
#define __ET_TREES_H__

#include "node.h"
#include "rb_tree.h"
#include <map>

class ET_Tree
{
    int length;
    map<int, bool> visited;
    RBTree *bbst;

public:
    ET_Tree(SFNode *tree_root);

    void ET(int &x, SFNode *root, SFNode *parent);
    void visit(int &x, SFNode *node);
    string dumpDot(string filename) const;
    RBNode *findRoot(RBNode *v)
    {
        RBNode *temp = v;
        while (temp->parent)
            temp = temp->parent;

        while (temp->left)
            temp = temp->left;

        return temp;
    }
};

#endif
