#ifndef __RB_TREE_H
#define __RB_TREE_H

#include "rb_node.h"
#include <string>

using namespace std;

class RBTree
{
private:
    RBNode *root;

public:
    RBTree();

    void rbtInsert(int key, map<string, any> attr);
    void rbtDelete(int key);

    string dumpDot(string filename = "") const;
    string dumpAllRanks() const;
    bool bstFind(int key, RBNode **&nodeptr);

private:
    void leftRotate(RBNode *&node);
    void rightRotate(RBNode *&node);

    void rbtInsertFixup(RBNode *&x);
    void rbtDeleteFixup(RBNode *&x);

    RBNode *bstInsert(RBNode *&root, RBNode *&z);
    void bstDelete(RBNode *&z);
    void bstTransplant(RBNode *u, RBNode *v);

    void setColor(RBNode *&node, RBColor color);
    RBColor getColor(RBNode *&node);

    RBNode *bstMinimum(RBNode *x);
    RBNode *bstMaximum(RBNode *x);
};

#endif
