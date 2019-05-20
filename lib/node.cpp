#include "edge.h"
#include "node.h"

Node::Node(int key, map<string, any> attr)
{
    this->key = key;
    this->attr = attr;
}

void Node::addEdge(Node *v)
{
    this->edges.push_back(new Edge(this, v));
}
void Node::removeEdge(Edge *e)
{
    auto position = std::find_if(
        edges.begin(), edges.end(), [&e](Edge *ep) { return e == ep; });
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

    for (auto const &e : this->edges)
    {
        out += std::to_string((*e)[0]->key);
        out += " -- ";
        out += std::to_string((*e)[1]->key);
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
