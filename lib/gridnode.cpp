#include "gridnode.h"

GNode::GNode(int key, map<string, any> attr)
{
    this->key = key;
    this->attr = attr;
}

void GNode::addEdge(GNode *v)
{
    this->edges.push_back(v);
}
void GNode::removeEdge(GNode *v)
{
    auto position = std::find_if(edges.begin(), edges.end(),
        [&v](GNode *v2) { return v2->key == v->key; });
    if (position != edges.end())
        edges.erase(position);
}
string GNode::dumpGNode()
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
string GNode::dumpEdges()
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

std::ostream &operator<<(std::ostream &os, const GNode &v)
{
    os << "{NODE: " << v.key << "}";
    return os;
}

bool operator==(const GNode &v1, const GNode &v2)
{
    return v1.key == v2.key;
}
