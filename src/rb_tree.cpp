//
// Created by martin on 11/15/18.
//
#include "../lib/rb_tree.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

RBTree::RBTree()
{
    this->root = nullptr;
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
            child->color = BLACK;
        else if (node->parent == nullptr)
            delete_case2(node);
    }
    delete node;
}
void RBTree::insert_repair(RBNode *node)
{
    if (parent(node) == nullptr)
        node->color = BLACK;
    else if (parent(node)->color == BLACK)
        return;
    else if (uncle(node)->color == RED)
        insert_case3(node);
    else
        insert_case4(node);
}
void RBTree::insert_case3(RBNode *node)
{
    parent(node)->color = BLACK;
    uncle(node)->color = BLACK;
    grandparent(node)->color = RED;
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
void RBTree::insert_recurse(RBNode *root_, RBNode *node)
{
    if (root_ != nullptr && root_->key <= node->key)
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
    node->color = RED;
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
        node->parent->color = RED;
        s->color = BLACK;
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

    if ((node->parent->color == BLACK) && (s->color == BLACK)
        && (s->left->color == BLACK) && (s->right->color == BLACK))
    {
        s->color = RED;
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
        s->color = RED;
        node->parent->color = BLACK;
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
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(s);
        }
        else if ((node == node->parent->right) && (s->left->color == BLACK)
            && (s->right->color == RED))
        {
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(s);
        }
    }
    delete_case6(node);
}
void RBTree::delete_case6(RBNode *node)
{
    RBNode *s = sibling(node);

    s->color = node->parent->color;
    node->parent->color = BLACK;

    if (node == node->parent->left)
    {
        s->right->color = BLACK;
        rotate_left(node->parent);
    }
    else
    {
        s->left->color = BLACK;
        rotate_right(node->parent);
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
        n_node->left = p_node->left;
    if (p_node != nullptr)
    {
        if (node == p_node->right)
            p_node->right = node->right;
        else if (node == p_node->left)
            p_node->left = node->left;
    }
    n_node->parent = p_node;
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
void RBTree::insert_node(int key, map<string, any> attr)
{
    RBNode *root_ = this->root;
    RBNode *node = new RBNode(key, attr, nullptr);
    insert_recurse(root_, node);

    insert_repair(node);

    root_ = node;

    while (parent(root_) != nullptr)
        root_ = parent(root_);
    this->root = root_;
}

string RBTree::dumpDot(string filename) const
{
    // COMPILE: dot -Kfdp -n -Gsplines=True -Tpng filename > output.png

    string out = "";
    out += this->root->dumpAllChildren();
    out += "\n";
    out += this->root->dumpAllChildrenEdges();

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
