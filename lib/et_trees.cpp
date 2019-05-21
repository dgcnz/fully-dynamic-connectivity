#include "node.h"
#include "rb_tree.h"

class ET_Tree
{
    int length;
    RBTree *bbst;

public:
    ET_Tree(Node *tree_root)
    {
        this->length = 0;
        this->ET(length, tree_root, nullptr);
    }
    void ET(int &x, Node *root, Node *parent)
    {
        bbst->insertValue(x++, { { "occurrence", root } });
        for (auto const &e : root->edges)
        {
            Node *child = (*e)[1];
            if (child != parent)
            {
                ++x;
                ET(x, child, root);
                bbst->insertValue(x, { { "occurrence", root } });
            }
        }
    }
    string dumpDot(string filename = "") const
    {
        return this->bbst->dumpDot(filename);
    }
};
