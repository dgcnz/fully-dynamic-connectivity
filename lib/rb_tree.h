#ifndef __RB_TREE_H
#define __RB_TREE_H

#include "../lib/rb_node.h"
#include <string>

using namespace std;

class RBTree
{
public:
    RBTree();
    RBNode *find(int key);
    void insert_node(int key, map<string, any> val);
    string dumpDot(string filename = "") const;

private:
    RBNode *root;
    void replace_node(RBNode *node, RBNode *child);
    void delete_child(RBNode *node);
    void insert_repair(RBNode *node);
    void insert_case3(RBNode *node);
    void insert_case4(RBNode *node);
    void insert_case4step2(RBNode *node);

    void insert_recurse(RBNode *root_, RBNode *node);
    inline bool is_leaf(RBNode *node) const;
    void delete_case2(RBNode *node);
    void delete_case3(RBNode *node);
    void delete_case4(RBNode *node);
    void delete_case5(RBNode *node);
    void delete_case6(RBNode *node);

    RBNode *parent(RBNode *node) const;
    RBNode *grandparent(RBNode *node) const;
    RBNode *sibling(RBNode *node) const;
    RBNode *uncle(RBNode *node) const;

    void rotate_left(RBNode *node);
    void rotate_right(RBNode *node);
};

#endif
