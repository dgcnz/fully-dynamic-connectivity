#ifndef __NODE_H__
#define __NODE_H__
#include <algorithm>
#include <any>
#include <experimental/optional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::experimental::optional;
using std::experimental::nullopt;
using Coordinates = pair<int, int>;

class Node
{
public:
    vector<Node *> edges;
    int key;
    map<string, any> attr;
    optional<Coordinates> xy;

    /*****************************************************/

    Node(int key, map<string, any> attr)
    {
        this->key = key;
        this->attr = attr;
    }

    void addEdge(Node *v)
    {
        this->edges.push_back(v);
    }
    void removeEdge(Node *v)
    {
        auto position = std::find_if(edges.begin(), edges.end(),
            [&v](Node *v2) { return v2->key == v->key; });
        if (position != edges.end())
            edges.erase(position);
    }
    string dumpNode()
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
    string dumpEdges()
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

    friend bool operator==(const Node &v1, const Node &v2);
    friend std::ostream &operator<<(std::ostream &os, const Node &v)
    {
        os << "{NODE: " << v.key << "}";
        return os;
    }
};

bool operator==(const Node &v1, const Node &v2)
{
    return v1.key == v2.key;
}

#endif
