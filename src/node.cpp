#include "../lib/node.h"

Node::Node(int key, map<string, any> attr)
{
    this->key = key;
    this->attr = attr;
}

void Node::addEdge(Node *v)
{
    this->edges.push_back(v);
}
void Node::removeEdge(Node *v)
{
    auto position = std::find_if(edges.begin(), edges.end(),
        [&v](Node *v2) { return v2->key == v->key; });
    if (position != edges.end())
        edges.erase(position);
}
string Node::dumpNode()
{
    std::stringstream out;

    out << to_string(this->key);

    if (this->attr.size() > 0)
    {
        out << " [";
        for (auto const &[key, val] : this->attr)
        {
            out << key << "=";
            if (key.compare("pos") == 0)
                out << "\"" << any_cast<Coordinates>(val).first << ","
                    << -1 * any_cast<Coordinates>(val).second << "!"
                    << "\"";
            else
                out << any_cast<string>(val);
            out << " ";
        }
        out << "]";
    }
    out << "\n";

    return out.str();
}
string Node::dumpEdges()
{
    string out = "";

    for (auto const &v : edges)
    {
        out += std::to_string(this->key);
        out += " -- ";
        out += std::to_string(v->key);
        out += "\n";
    }
    return out;
}

/*****************************************************/

std::ostream &operator<<(std::ostream &os, const Node &v)
{
    os << "{NODE: " << v.key << "}";
    return os;
}

bool operator==(const Node &v1, const Node &v2)
{
    return v1.key == v2.key;
}
