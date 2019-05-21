#include "rb_tree.h"
#include <bits/stdc++.h>
using namespace std;

RBTree::RBTree()
{
    this->root = nullptr;
}

int RBTree::getColor(RBNode *&node)
{
    if (node == nullptr)
        return BLACK;

    return node->color;
}

void RBTree::setColor(RBNode *&node, RBColor color)
{
    if (node == nullptr)
        return;

    node->setColor(color);
}
RBNode *RBTree::insertBST(RBNode *&root, RBNode *&ptr)
{
    if (root == nullptr)
        return ptr;

    if (ptr->key < root->key)
    {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->key > root->key)
    {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::insertValue(int key, map<string, any> attr)
{
    RBNode *node = new RBNode(key, attr);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

void RBTree::rotateLeft(RBNode *&ptr)
{
    RBNode *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(RBNode *&ptr)
{
    RBNode *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(RBNode *&ptr)
{
    RBNode *parent = nullptr;
    RBNode *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED)
    {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left)
        {
            RBNode *uncle = grandparent->right;
            if (getColor(uncle) == RED)
            {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else
            {
                if (ptr == parent->right)
                {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
        else
        {
            RBNode *uncle = grandparent->left;
            if (getColor(uncle) == RED)
            {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else
            {
                if (ptr == parent->left)
                {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(RBNode *&node)
{
    if (node == nullptr)
        return;

    if (node == root)
    {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED
        || getColor(node->right) == RED)
    {
        RBNode *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left)
        {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
        else
        {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    }
    else
    {
        RBNode *sibling = nullptr;
        RBNode *parent = nullptr;
        RBNode *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK)
        {
            parent = ptr->parent;
            if (ptr == parent->left)
            {
                sibling = parent->right;
                if (getColor(sibling) == RED)
                {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                }
                else
                {
                    if (getColor(sibling->left) == BLACK
                        && getColor(sibling->right) == BLACK)
                    {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    }
                    else
                    {
                        if (getColor(sibling->right) == BLACK)
                        {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            }
            else
            {
                sibling = parent->left;
                if (getColor(sibling) == RED)
                {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                }
                else
                {
                    if (getColor(sibling->left) == BLACK
                        && getColor(sibling->right) == BLACK)
                    {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    }
                    else
                    {
                        if (getColor(sibling->left) == BLACK)
                        {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete (node);
        setColor(root, BLACK);
    }
}

RBNode *RBTree::deleteBST(RBNode *&root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        return deleteBST(root->left, key);

    if (key > root->key)
        return deleteBST(root->right, key);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    RBNode *temp = minValueRBNode(root->right);
    root->key = temp->key;
    return deleteBST(root->right, temp->key);
}

void RBTree::deleteValue(int key)
{
    RBNode *node = deleteBST(root, key);
    fixDeleteRBTree(node);
}

void RBTree::inorderBST(RBNode *&ptr)
{
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->key << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void RBTree::inorder()
{
    inorderBST(root);
}

void RBTree::preorderBST(RBNode *&ptr)
{
    if (ptr == nullptr)
        return;

    cout << ptr->key << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void RBTree::preorder()
{
    preorderBST(root);
    cout << "-------" << endl;
}

RBNode *RBTree::minValueRBNode(RBNode *&node)
{

    RBNode *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

RBNode *RBTree::maxValueRBNode(RBNode *&node)
{
    RBNode *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

int RBTree::getBlackHeight(RBNode *node)
{
    int blackheight = 0;
    while (node != nullptr)
    {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

// Test case 1 : 5 2 9 1 6 8 0 20 30 35 40 50 0
// Test case 2 : 3 0 5 0
// Test case 3 : 2 1 3 0 8 9 4 5 0

void RBTree::merge(RBTree rbTree2)
{
    int temp;
    RBNode *c, *temp_ptr;
    RBNode *root1 = root;
    RBNode *root2 = rbTree2.root;
    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2)
    {
        c = maxValueRBNode(root1);
        temp = c->key;
        deleteValue(c->key);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1)
    {
        c = minValueRBNode(root2);
        temp = c->key;
        rbTree2.deleteValue(c->key);
        root2 = rbTree2.root;
    }
    else
    {
        c = minValueRBNode(root2);
        temp = c->key;
        rbTree2.deleteValue(c->key);
        root2 = rbTree2.root;
        if (initialblackheight1 != getBlackHeight(root2))
        {
            rbTree2.insertValue(c->key, c->attr);
            root2 = rbTree2.root;
            c = maxValueRBNode(root1);
            temp = c->key;
            deleteValue(c->key);
            root1 = root;
        }
    }
    setColor(c, RED);
    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2)
    {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c, BLACK);
        c->key = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1)
    {
        RBNode *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr))
        {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        RBNode *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->parent;
        c->left = root1;
        if (root1 != nullptr)
            root1->parent = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->parent = c;
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED)
        {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED)
        {
            fixInsertRBTree(ptr);
        }
        c->key = temp;
        root = root2;
    }
    else
    {
        RBNode *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr))
        {
            ptr = ptr->right;
        }
        RBNode *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED)
        {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED)
        {
            fixInsertRBTree(ptr);
        }
        c->key = temp;
        root = root1;
    }
    return;
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
