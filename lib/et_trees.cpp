#include "node.h"
#include "rb_tree.h"
#include "et_trees.h"
#include <map>

ET_Tree::ET_Tree(Node *tree_root)
{
    bbst = new RBTree();
    cout << "ETTree rooted at " << tree_root->key << endl;
    this->length = 0;
    this->ET(length, tree_root, nullptr);
}

void ET_Tree::ET(int &x, Node *root, Node *parent)
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

void ET_Tree::visit(int &x, Node *node)
{
    cout << "Visited node " << node->key << " at time: " << x << endl;
    bbst->insertValue(x, { { "occurrence", node } });
    ++x;
}

string ET_Tree::dumpDot(string filename = "") const
{
    return this->bbst->dumpDot(filename);
}
