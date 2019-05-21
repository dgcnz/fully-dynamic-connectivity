#include "rb_node.h"
#include <typeinfo>

RBNode::RBNode(int key, map<string, any> attr)
    : key(key)
    , color(RED)
    , attr(attr)
    , left(nullptr)
    , right(nullptr)
    , parent(nullptr)
{
    this->attr["color"] = string("red");
}

void RBNode::setColor(RBColor color)
{
    this->color = color;
    if (color == BLACK)
        this->attr["color"] = string("black");
    else if (color == RED)
        this->attr["color"] = string("red");
    else if (color == DOUBLE_BLACK)
        this->attr["color"] = string("blue");
}

RBColor RBNode::getColor()
{
    return this->color;
}

inline bool RBNode::operator==(const RBNode &t) const
{
    return key == t.key;
}

inline bool RBNode::operator<(const RBNode &t) const
{
    return key < t.key;
}

string RBNode::dumpNode() const
{
    std::stringstream out;

    out << to_string(this->key);

    if (this->attr.size() > 0)
    {
        out << " [";
        for (auto const &[key, val] : this->attr)
        {
            if (key.compare("pos") == 0)
                continue;
            out << key << "=";
            cout << this->key << key << endl;
            out << any_cast<string>(val);
            cout << "casted to string \n";
            out << " ";
        }
        out << "]";
    }
    out << "\n";

    return out.str();
}
string RBNode::dumpEdges() const
{
    string out = "";

    if (this->left)
    {
        out += std::to_string(this->key);
        out += " -- ";
        out += std::to_string(this->left->key);
        out += "\n";
    }
    if (this->right)
    {
        out += std::to_string(this->key);
        out += " -- ";
        out += std::to_string(this->right->key);
        out += "\n";
    }

    return out;
}

string RBNode::dumpAllChildren() const
{
    return dumpNode() + (this->left ? this->left->dumpAllChildren() : "")
        + (this->right ? this->right->dumpAllChildren() : "");
}

string RBNode::dumpAllChildrenEdges() const
{
    return dumpEdges() + (this->left ? this->left->dumpAllChildrenEdges() : "")
        + (this->right ? this->right->dumpAllChildrenEdges() : "");
}

void RBNode::store_rank(vector<vector<int>> &ranks, int level) const
{
    if (level >= ranks.size())
        ranks.push_back({ this->key });
    else
        ranks[level].push_back(this->key);

    if (this->left)
        this->left->store_rank(ranks, level + 1);
    if (this->right)
        this->right->store_rank(ranks, level + 1);
}

/*****************************************************/

std::ostream &operator<<(std::ostream &os, const RBNode &v)
{
    os << "{NODE: " << v.key << "}";
    return os;
}
