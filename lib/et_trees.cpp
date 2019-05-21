#include "et_trees.h"
#include "node.h"
#include "rb_tree.h"
#include <map>

ET_Tree::ET_Tree(SFNode *tree_root)
{
    bbst = new RBTree();
    cout << "ETTree rooted at " << tree_root->key << endl;
    this->length = 0;
    this->ET(length, tree_root, nullptr);
}

void ET_Tree::ET(int &x, SFNode *root, SFNode *parent)
{
    visit(x, root);
    for (auto const &e : root->edges)
    {
        SFNode *child = (*e)[1];
        if (child != parent)
        {
            ET(x, child, root);
            visit(x, root);
        }
    }
}

void ET_Tree::visit(int &x, SFNode *node)
{
    cout << "Visited node " << node->key << " at time: " << x << endl;
    bbst->insertValue(x, { { "occurrence", node } });
    if (!visited[node->key])
    {
        RBNode **fatherptr;
        this->bbst->find(x, fatherptr);
        node->first_occurrence = node->last_occurrence = *fatherptr;
        visited[node->key] = true;
    }
    else
    {
        RBNode **fatherptr;
        this->bbst->find(x, fatherptr);
        node->last_occurrence = *fatherptr;
    }
    ++x;
}

string ET_Tree::dumpDot(string filename = "") const
{
    return this->bbst->dumpDot(filename);
}
