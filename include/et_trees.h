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
    ET_Tree(Node *tree_root)
    {
        bbst = new RBTree();
        this->length = 0;
        this->ET(length, tree_root, nullptr);
    }
    void ET(int &x, Node *root, Node *parent)
    {
        visit(x, root);
        for (auto const &e : root->edges)
        {
            Node *child = (*e)[1];
            if (child != parent)
            {
                ET(x, child, root);
                visit(x, root);
            }
        }
    }

    void visit(int &x, Node *node)
    {
        bbst->insertValue(x, { { "occurrence", node } });
        ++x;
    }

    string dumpDot(string filename = "") const
    {
        return this->bbst->dumpDot(filename);
    }
};

#endif
