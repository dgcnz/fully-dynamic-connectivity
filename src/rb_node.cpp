#include "../lib/rb_node.h"

RBNode::RBNode(int key, map<string, any> attr, RBNode *parent)
    : key(key)
    , color(BLACK)
    , attr(attr)
    , left(nullptr)
    , right(nullptr)
    , parent(parent)
{
}

RBNode::RBNode(RBNode *parent)
    : left(nullptr)
    , right(nullptr)
    , parent(parent)
{
}

inline bool RBNode::operator==(const RBNode &t) const
{
    return key == t.key;
}

inline bool RBNode::operator<(const RBNode &t) const
{
    return key < t.key;
}

void RBNode::changeColor(RBNodeColor color)
{
    this->color = color;
    if (color == BLACK)
        this->attr["color"] = "black";
    else if (color == RED)
        this->attr["color"] = "red";
}

string RBNode::dumpNode() const
{
    std::stringstream out;

    out << to_string(this->key);

    if (this->attr.size() > 0)
    {
        out << " [";
        for (auto &[key, val] : this->attr)
        {
            if (key.compare("pos") == 0)
                continue;
            out << key << "=";
            out << any_cast<string>(val);

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

    out += std::to_string(this->key);
    out += " -- ";
    out += std::to_string(this->left->key);
    out += "\n";

    out += std::to_string(this->key);
    out += " -- ";
    out += std::to_string(this->right->key);
    out += "\n";

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

/*****************************************************/

std::ostream &operator<<(std::ostream &os, const RBNode &v)
{
    os << "{NODE: " << v.key << "}";
    return os;
}
