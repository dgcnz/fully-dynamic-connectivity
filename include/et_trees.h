#ifndef __ET_TREES_H__
#define __ET_TREES_H__

#include "node.h"
#include "rb_tree.h"
#include <map>

class ET_Tree
{
    int length;
    RBTree *bbst;

public:
    ET_Tree(Node *tree_root);

    void ET(int &x, Node *root, Node *parent);
    void visit(int &x, Node *node);
    string dumpDot(string filename) const;
};

#endif
