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
    bool treeFind(int key, RBNode **&nodeptr);
    RBNode *treeInsert(RBNode *&root, RBNode *&z);

    void rbtreeInsert(int key, map<string, any> attr);
    void insert_node(int key, map<string, any> val);
    inline bool is_leaf(RBNode *node) const;
    inline int getNewLeaveUUID()
    {
        return --(this->leave_counter);
    }
    void setColor(RBNode *&node, RBNodeColor color);
    RBNodeColor getColor(RBNode *&node);
    void fixViolation(RBNode *&x);

    string dumpDot(string filename = "") const;
    string dumpAllRanks() const;

private:
    RBNode *root;
    int leave_counter;

    void replace_node(RBNode *node, RBNode *child);
    void delete_child(RBNode *node);
    void insert_repair(RBNode *node);
    void insert_case3(RBNode *node);
    void insert_case4(RBNode *node);
    void insert_case4step2(RBNode *node);
    void insert_recurse(RBNode *root_, RBNode *node);

    void delete_case2(RBNode *node);
    void delete_case3(RBNode *node);
    void delete_case4(RBNode *node);
    void delete_case5(RBNode *node);
    void delete_case6(RBNode *node);

    RBNode *parent(RBNode *node) const;
    RBNode *grandparent(RBNode *node) const;
    RBNode *sibling(RBNode *node) const;
    RBNode *uncle(RBNode *node) const;

    void leftRotate(RBNode *&node);
    void rightRotate(RBNode *&node);
};

#endif
