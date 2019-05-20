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
    this->leave_counter = 0;
}

void RBTree::rbtreeInsert(int key, map<string, any> attr)
{
    cout << "Inserting " << key << endl;
    RBNode *node = new RBNode(key, attr);

    this->root = this->treeInsert(this->root, node);
    this->fixViolation(node);
}

void RBTree::fixViolation(RBNode *&x)
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

RBNode *RBTree::treeInsert(RBNode *&root_, RBNode *&z)
{
    if (root_ == nullptr)
        return z;

    if (z->key < root_->key)
    {
        root_->left = treeInsert(root_->left, z);
        root_->left->parent = root_;
    }
    else if (z->key > root_->key)
    {
        root_->right = treeInsert(root_->right, z);
        root_->right->parent = root_;
    }

    return root_;
}

void RBTree::setColor(RBNode *&node, RBNodeColor color)
{
    if (node == nullptr)
        return;

    node->color = color;
    node->attr["color"] = (color == BLACK ? string("black") : string("red"));
}

RBNodeColor RBTree::getColor(RBNode *&node)
{
    if (node == nullptr)
        return BLACK;

    return node->color;
}

bool RBTree::treeFind(int key, RBNode **&nodeptr)
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

void RBTree::replace_node(RBNode *node, RBNode *child)
{
    child->parent = node->parent;
    if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
}

void RBTree::delete_child(RBNode *node)
{
    RBNode *child = is_leaf(node->right) ? node->left : node->right;

    replace_node(node, child);

    if (node->color == BLACK)
    {
        if (child->color == RED)
            setColor(child, BLACK);
        else if (node->parent == nullptr)
            delete_case2(node);
    }
    delete node;
}
inline bool RBTree::is_leaf(RBNode *node) const
{
    return node->left == nullptr && node->right == nullptr;
}

void RBTree::delete_case2(RBNode *node)
{
    RBNode *s = sibling(node);

    if (s->color == RED)
    {
        setColor(node->parent, RED);
        setColor(s, BLACK);
    }
    if (node == node->parent->left)
        leftRotate(node->parent);
    else
        rightRotate(node->parent);
    delete_case3(node);
}

void RBTree::delete_case3(RBNode *node)
{
    RBNode *s = sibling(node);

    if ((node->parent->color == BLACK) && (s->color == BLACK)
        && (s->left->color == BLACK) && (s->right->color == BLACK))
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

    if ((node->parent->color == RED) && (s->color == BLACK)
        && (s->left->color == BLACK) && (s->right->color == BLACK))
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

    if (s->color == BLACK)
    {
        if ((node == node->parent->left) && (s->right->color == BLACK)
            && (s->left->color == RED))
        {
            setColor(s, RED);
            setColor(s->left, BLACK);
            rightRotate(s);
        }
        else if ((node == node->parent->right) && (s->left->color == BLACK)
            && (s->right->color == RED))
        {
            setColor(s, RED);
            setColor(s->right, BLACK);
            leftRotate(s);
        }
    }
    delete_case6(node);
}
void RBTree::delete_case6(RBNode *node)
{
    RBNode *s = sibling(node);

    setColor(s, node->parent->color);
    setColor(node->parent, BLACK);

    if (node == node->parent->left)
    {
        setColor(s->right, BLACK);
        leftRotate(node->parent);
    }
    else
    {
        setColor(s->left, BLACK);
        rightRotate(node->parent);
    }
}
RBNode *RBTree::parent(RBNode *node) const
{
    return node->parent;
}
RBNode *RBTree::grandparent(RBNode *node) const
{
    RBNode *p = parent(node);
    return p == nullptr ? nullptr : parent(p);
}
RBNode *RBTree::sibling(RBNode *node) const
{
    RBNode *p = parent(node);
    return p == nullptr ? nullptr : p->left == node ? p->right : p->left;
}
RBNode *RBTree::uncle(RBNode *node) const
{
    RBNode *p = parent(node);
    RBNode *g = grandparent(node);
    return g == nullptr ? nullptr : sibling(p);
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

RBNode *RBTree::find(int key)
{
    queue<RBNode *> node_queue;
    RBNode *base = this->root;

    if (base == nullptr)
        return nullptr;

    node_queue.push(base);
    while (!node_queue.empty())
    {
        RBNode *current = node_queue.front();
        node_queue.pop();
        if (current->key == key)
            return current;
        else
        {
            if (current->left != nullptr)
                node_queue.push(current->left);
            if (current->right != nullptr)
                node_queue.push(current->right);
        }
    }
    return nullptr;
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
