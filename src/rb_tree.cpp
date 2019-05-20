#include "../lib/rb_tree.h"
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

void RBTree::rbtInsert(int key, map<string, any> attr)
{
    cout << "Inserting " << key << endl;
    RBNode *node = new RBNode(key, attr);

    this->root = this->bstInsert(this->root, node);
    this->rbtInsertFixup(node);
}

void RBTree::rbtDelete(int key)
{
    RBNode **fatherptr;
    if (this->bstFind(key, fatherptr) == false)
        return;

    RBNode *node = *fatherptr;

    bstDelete(node);
    rbtDeleteFixup(node);
}

void RBTree::bstDelete(RBNode *&node)
{

    RBNode *sub;
    RBNode *old = node;
    RBColor old_original_color = getColor(old);

    if (node->left == nullptr)
    {
        sub = node->right;
        bstTransplant(node, node->right);
    }
    else if (node->right == nullptr)
    {
        sub = node->left;
        bstTransplant(node, node->left);
    }
    else
    {
        old = bstMinimum(node->right);
        old_original_color = getColor(old);
        sub = old->right;
        if (old->parent == node)
            sub->parent = node;
        else
        {
            bstTransplant(old, old->right);
            old->right = node->right;
            old->right->parent = old;
        }
        bstTransplant(node, old);
        old->left = node->left;
        old->left->parent = old;
        setColor(old, getColor(node));
    }
    delete node;
    if (old_original_color == BLACK)
        rbtDeleteFixup(old);
}

void RBTree::rbtDeleteFixup(RBNode *&old)
{
    RBNode *sibling;

    while (old != this->root && getColor(old) == BLACK)
    {
        if (old == old->parent->left)
        {
            sibling = old->parent->right;
            if (getColor(sibling) == RED)
            {
                setColor(sibling, BLACK);
                setColor(old->parent, RED);

                leftRotate(old->parent);
                sibling = old->parent->right;
            }
            if (getColor(sibling->left) == BLACK
                && getColor(sibling->right) == BLACK)
            {
                setColor(sibling, RED);
                old = old->parent;
            }
            else
            {
                if (getColor(sibling->right) == BLACK)
                {
                    setColor(sibling->left, BLACK);
                    setColor(sibling, RED);
                    rightRotate(sibling);
                    sibling = old->parent->right;
                }
                setColor(sibling, getColor(old->parent));
                setColor(old->parent, BLACK);
                setColor(sibling->right, BLACK);
                leftRotate(old->parent);
                old = this->root;
            }
        }
        else
        {
            sibling = old->parent->left;
            if (getColor(sibling) == RED)
            {
                setColor(sibling, BLACK);
                setColor(old->parent, RED);

                rightRotate(old->parent);
                sibling = old->parent->left;
            }
            if (getColor(sibling->right) == BLACK
                && getColor(sibling->left) == BLACK)
            {
                setColor(sibling, RED);
                old = old->parent;
            }
            else
            {
                if (getColor(sibling->left) == BLACK)
                {
                    setColor(sibling->right, BLACK);
                    setColor(sibling, RED);
                    leftRotate(sibling);
                    sibling = old->parent->left;
                }
                setColor(sibling, getColor(old->parent));
                setColor(old->parent, BLACK);
                setColor(sibling->left, BLACK);
                rightRotate(old->parent);
                old = this->root;
            }
        }
    }
}

void RBTree::bstTransplant(RBNode *u, RBNode *v)
{
    if (u->parent == nullptr)
        this->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

RBNode *RBTree::bstMinimum(RBNode *x)
{
    while (x->left != nullptr)
        x = x->left;
    return x;
}

RBNode *RBTree::bstMaximum(RBNode *x)
{
    while (x->right != nullptr)
        x = x->right;
    return x;
}

void RBTree::rbtInsertFixup(RBNode *&x)
{
    RBNode *parent_x = nullptr;
    RBNode *grandparent_x = nullptr;

    while (x != this->root && this->getColor(x) == RED
        && this->getColor(x->parent) == RED)
    {
        cout << x->key << " needs to be fixed\n";
        parent_x = x->parent;
        grandparent_x = parent_x->parent;
        if (parent_x == grandparent_x->left)
        {
            RBNode *uncle_x = grandparent_x->right;
            if (this->getColor(uncle_x) == RED)
            {
                setColor(uncle_x, BLACK);
                setColor(parent_x, BLACK);
                setColor(grandparent_x, RED);
                x = grandparent_x;
            }
            else
            {
                if (x == parent_x->right)
                {
                    leftRotate(parent_x);
                    x = parent_x;
                    parent_x = x->parent;
                }
                rightRotate(grandparent_x);
                swap(parent_x->color, grandparent_x->color);
                x = parent_x;
            }
        }
        else
        {
            RBNode *uncle_x = grandparent_x->left;
            if (getColor(uncle_x) == RED)
            {
                setColor(uncle_x, BLACK);
                setColor(parent_x, BLACK);
                setColor(grandparent_x, RED);
                x = grandparent_x;
            }
            else
            {
                if (x == parent_x->left)
                {
                    rightRotate(parent_x);
                    x = parent_x;
                    parent_x = x->parent;
                }
                leftRotate(grandparent_x);
                swap(parent_x->color, grandparent_x->color);
                x = parent_x;
            }
        }
    }
    setColor(this->root, BLACK);
}

RBNode *RBTree::bstInsert(RBNode *&root_, RBNode *&z)
{
    if (root_ == nullptr)
        return z;

    if (z->key < root_->key)
    {
        root_->left = bstInsert(root_->left, z);
        root_->left->parent = root_;
    }
    else if (z->key > root_->key)
    {
        root_->right = bstInsert(root_->right, z);
        root_->right->parent = root_;
    }

    return root_;
}

void RBTree::leftRotate(RBNode *&node)
{
    RBNode *r_child = node->right;
    node->right = r_child->left;

    if (node->right != nullptr)
        node->right->parent = node;

    r_child->parent = node->parent;

    if (node->parent == nullptr)
        this->root = r_child;
    else if (node == node->parent->left)
        node->parent->left = r_child;
    else
        node->parent->right = r_child;

    r_child->left = node;
    node->parent = r_child;
}

void RBTree::rightRotate(RBNode *&node)
{
    RBNode *l_child = node->left;
    node->left = l_child->right;

    if (node->left != nullptr)
        node->left->parent = node;

    l_child->parent = node->parent;

    if (node->parent == nullptr)
        this->root = l_child;
    else if (node == node->parent->left)
        node->parent->left = l_child;
    else
        node->parent->right = l_child;

    l_child->right = node;
    node->parent = l_child;
}

void RBTree::setColor(RBNode *&node, RBColor color)
{
    if (node == nullptr)
        return;

    node->color = color;
    node->attr["color"] = (color == BLACK ? string("black") : string("red"));
}

RBColor RBTree::getColor(RBNode *&node)
{
    if (node == nullptr)
        return BLACK;

    return node->color;
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
