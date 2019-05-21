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

private:
    void leftRotate(RBNode *&node);
    void rightRotate(RBNode *&node);

    void setColor(RBNode *node, RBColor color);
    RBColor getColor(RBNode *node);

    RBNode *bstMinimum(RBNode *x);
    RBNode *bstMaximum(RBNode *x);

private:
    bool bstFind(int key, RBNode **&nodeptr);
    void replace_node(RBNode *node, RBNode *child);
    void delete_child(RBNode *node);
    void insert_repair(RBNode *node);
    void insert_case3(RBNode *node);
    void insert_case4(RBNode *node);
    void insert_case4step2(RBNode *node);
    void insert_recurse(RBNode *root, RBNode *node);
    bool is_leaf(RBNode *node);
    void delete_case2(RBNode *node);
    void delete_case3(RBNode *node);
    void delete_case4(RBNode *node);
    void delete_case5(RBNode *node);
    void delete_case6(RBNode *node);
    RBNode *parent(RBNode *node);
    RBNode *grandparent(RBNode *node);
    RBNode *sibling(RBNode *node);
    RBNode *uncle(RBNode *node);
    void rotate_left(RBNode *node);
    void rotate_right(RBNode *node);
    void insert_node(int key, map<string, any> val);
};

#endif
