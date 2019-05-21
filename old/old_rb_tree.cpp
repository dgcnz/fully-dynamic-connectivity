#include "rb_tree.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

RBTree::RBTree()
{
    this->root = nullptr;
}


void RBTree::rbtInsert(int key, map<string, any> val)
{
    RBNode *root_t = this->root;
    RBNode *node = new RBNode(key, val);
    cout << "Inserting node " << key << endl;

    insert_recurse(root_t, node);

    cout << "Repairing node " << key << endl;
    insert_repair(node);

    root_t = node;

    while (parent(root_t) != nullptr)
        root_t = parent(root_t);
    this->root = root_t;
}
void RBTree::insert_recurse(RBNode *root_, RBNode *node)
{
    if (root_ != nullptr && root_->key < node->key)
    {
        if (!is_leaf(root_->left))
        {
            insert_recurse(root_->left, node);
            return;
        }
        else
            root_->left = node;
    }
    else if (root_ != nullptr)
    {
        if (!is_leaf(root_->right))
        {
            insert_recurse(root_->right, node);
            return;
        }
        else
            root_->right = node;
    }
    node->parent = root_;
    node->left = new RBNode(node);
    node->right = new RBNode(node);
    setColor(node, RED);
}
void RBTree::insert_repair(RBNode *node)
{
    if (parent(node) == nullptr)
        setColor(node, BLACK);
    else if (getColor(node) == BLACK)
        return;
    else if (getColor(uncle(node)) == RED)
        insert_case3(node);
    else
        insert_case4(node);
}
void RBTree::insert_case3(RBNode *node)
{
    setColor(parent(node), BLACK);
    setColor(uncle(node), BLACK);

    setColor(grandparent(node), RED);

    insert_repair(grandparent(node));
}
void RBTree::insert_case4(RBNode *node)
{
    RBNode *p = parent(node);
    RBNode *g = grandparent(node);

    if (node == g->left->right)
    {
        rotate_left(p);
        node = node->left;
    }
    else if (node == g->right->left)
    {
        rotate_right(p);
        node = node->right;
    }
    insert_case4step2(node);
}
void RBTree::insert_case4step2(RBNode *node)
{
    RBNode *p = parent(node);
    RBNode *g = grandparent(node);

    if (node == p->left)
        rotate_right(g);
    else
        rotate_left(g);
    p->color = BLACK;
    g->color = RED;
}
bool RBTree::is_leaf(RBNode *node)
{
    return node->left == nullptr && node->right == nullptr;
}
void RBTree::delete_case2(RBNode *node)
{
    RBNode *s = sibling(node);

    if (getColor(s) == RED)
    {
        setColor(node->parent, RED);
        setColor(s, BLACK);
    }
    if (node == node->parent->left)
        rotate_left(node->parent);
    else
        rotate_right(node->parent);
    delete_case3(node);
}
void RBTree::delete_case3(RBNode *node)
{
    RBNode *s = sibling(node);

    if (getColor(node->parent) == BLACK && getColor(s) == BLACK
        && getColor(s->left) == BLACK && getColor(s->right) == BLACK)
    {
        setColor(s, RED);
        delete_child(node->parent);
    }
    else
        delete_case4(node);
}
void RBTree::delete_case4(RBNode *node)
{
    RBNode *s = sibling(node);

    if (getColor(node->parent) == RED && getColor(s) == BLACK
        && getColor(s->left) == BLACK && getColor(s->right) == BLACK)
    {
        setColor(s, RED);
        setColor(node->parent, BLACK);
    }
    else
        delete_case5(node);
}
void RBTree::delete_case5(RBNode *node)
{
    RBNode *s = sibling(node);

    if (getColor(s) == BLACK)
    {
        if ((node == node->parent->left) && (getColor(s->right) == BLACK)
            && (getColor(s->left) == RED))
        {
            setColor(s, RED);
            setColor(s->left, BLACK);
            rotate_right(s);
        }
        else if ((node == node->parent->right) && (getColor(s->left) == BLACK)
            && (getColor(s->right) == RED))
        {
            setColor(s, RED);
            setColor(s->right, BLACK);
            rotate_left(s);
        }
    }
    delete_case6(node);
}
void RBTree::delete_case6(RBNode *node)
{
    RBNode *s = sibling(node);

    setColor(s, getColor(node->parent));
    setColor(node->parent, BLACK);

    if (node == node->parent->left)
    {
        s->right->color = BLACK;
        setColor(s->right, BLACK);
        rotate_left(node->parent);
    }
    else
    {
        s->left->color = BLACK;
        setColor(s->left, BLACK);
        rotate_right(node->parent);
    }
}
RBNode *RBTree::parent(RBNode *node)
{
    return node->parent;
}
RBNode *RBTree::grandparent(RBNode *node)
{
    RBNode *p = parent(node);
    return p == nullptr ? nullptr : parent(p);
}
RBNode *RBTree::sibling(RBNode *node)
{
    RBNode *p = parent(node);
    return p == nullptr ? nullptr : p->left == node ? p->right : p->left;
}
RBNode *RBTree::uncle(RBNode *node)
{
    RBNode *p = parent(node);
    RBNode *g = grandparent(node);
    return g == nullptr ? nullptr : sibling(p);
}
void RBTree::rotate_left(RBNode *node)
{
    RBNode *n_node = node->right;
    RBNode *p_node = parent(node);

    assert(!is_leaf(n_node));

    n_node->right = node->left;
    node = n_node->left;
    node->parent = node;

    if (node->right == nullptr)
    {
        n_node->right = p_node->right;
    }

    if (p_node != nullptr)
    {
        if (node == p_node->right)
        {
            p_node->right = node->right;
        }
        else if (node == p_node->left)
        {
            p_node->left = node->left;
        }
    }
    n_node->parent = p_node;
}
void RBTree::rotate_right(RBNode *node)
{
    RBNode *n_node = node->left;
    RBNode *p_node = parent(node);

    assert(!is_leaf(n_node));

    n_node->left = node->right;
    node = n_node->right;
    node->parent = node;

    if (node->left == nullptr)
    {
        n_node->left = p_node->left;
    }

    if (p_node != nullptr)
    {
        if (node == p_node->right)
        {
            p_node->right = node->right;
        }
        else if (node == p_node->left)
        {
            p_node->left = node->left;
        }
    }
    n_node->parent = p_node;
}

void RBTree::replace_node(RBNode *node, RBNode *child)
{
    child->parent = node->parent;
    if (node == node->parent->left)
    {
        node->parent->left = child;
    }
    else
    {
        node->parent->right = child;
    }
}

void RBTree::rbtDelete(int key)
{
    RBNode **parentptr;
    if (bstFind(key, parentptr) == false)
        return;

    RBNode *node = *parentptr;

    delete_child(node);
}

bool RBTree::bstFind(int key, RBNode **&nodeptr)
{
    nodeptr = &(this->root);
    if (!this->root)
        return false;
    else
    {
        while ((*nodeptr)->key != key)
        {
            nodeptr = key > (*nodeptr)->key ? &((*nodeptr)->right)
                                            : &((*nodeptr)->left);
            if (!(*nodeptr))
                return false;
        }
        return true;
    }
}

void RBTree::delete_child(RBNode *node)
{
    RBNode *child = is_leaf(node->right) ? node->left : node->right;

    replace_node(node, child);

    if (getColor(node) == BLACK)
    {
        if (getColor(child) == RED)
            setColor(child, BLACK);
        else if (node->parent == nullptr)
            delete_case2(node);
    }
    delete node;
}
void RBTree::setColor(RBNode *node, RBColor color)
{
    if (node == nullptr)
        return;

    node->color = color;
    node->attr["color"] = (color == BLACK ? string("black") : string("red"));
}

RBColor RBTree::getColor(RBNode *node)
{
    if (node == nullptr)
        return BLACK;

    return node->color;
}

string RBTree::dumpDot(string filename) const
{
    // COMPILE: dot -Kfdp -n -Gsplines=True -Tpng filename > output.png

    string out = "";
    cout << "Dumping all children\n";
    out += this->root->dumpAllChildren();
    out += "\n";
    cout << "Dumping all Edges\n";
    out += this->root->dumpAllChildrenEdges();
    out += "\n";
    cout << "Dumping ranks\n";
    out += dumpAllRanks();
    cout << "Finished dumping\n";
    if (!filename.empty())
    {
        cout << "Saving file to " << filename << endl;
        ofstream FILE_;
        FILE_.open(filename);
        FILE_ << "strict graph {\n";
        FILE_ << out;
        FILE_ << "}\n";
        FILE_.close();
    }
    return out;
}

string RBTree::dumpAllRanks() const
{
    vector<vector<int>> ranks;
    this->root->store_rank(ranks, 0);
    stringstream out;

    for (auto level : ranks)
    {
        out << "{rank=same; ";
        for (auto key : level)
        {
            out << key << "; ";
        }
        out << "}\n";
    }
    return out.str();
}
