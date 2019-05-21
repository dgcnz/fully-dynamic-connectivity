#ifndef __RB_TREE_H__
#define __RB_TREE_H__
#include "rb_node.h"
/*
 * The base structure of this RED BLACK TREE was implemented by @anandarao
 * SOURCE: https://github.com/anandarao/Red-Black-Tree
 */

class RBTree
{
private:
    RBNode *root;

protected:
    void rotateLeft(RBNode *&);
    void rotateRight(RBNode *&);
    void fixInsertRBTree(RBNode *&);
    void fixDeleteRBTree(RBNode *&);
    void inorderBST(RBNode *&);
    void preorderBST(RBNode *&);
    int getColor(RBNode *&);
    void setColor(RBNode *&, RBColor);
    RBNode *minValueRBNode(RBNode *&);
    RBNode *maxValueRBNode(RBNode *&);
    RBNode *insertBST(RBNode *&, RBNode *&);
    RBNode *deleteBST(RBNode *&, int);
    int getBlackHeight(RBNode *);

public:
    RBTree();
    void insertValue(int, map<string, any>);
    void deleteValue(int);
    void merge(RBTree);
    void inorder();
    void preorder();
    string dumpDot(string filename = "") const;
    string dumpAllRanks() const;
};

#endif
