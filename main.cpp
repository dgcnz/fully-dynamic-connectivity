#include "lib/graph.h"
#include "lib/rb_tree.h"
#include "lib/utilities.h"
#include <cmath>
#include <cstdarg>
#include <functional>
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, const char *argv[])
{
    using namespace std::placeholders; // for _1, _2, _3...

    /*
    int size = 9;
    Graph G(size * size);
    fill_board(G, size);

    G.removeEdge(27, 36);
    G.removeEdge(28, 37);
    G.removeEdge(29, 38);
    G.removeEdge(30, 39);
    G.removeEdge(3, 4);
    G.removeEdge(12, 13);
    G.removeEdge(21, 22);
    G.removeEdge(30, 31);

    Graph *SF = G.getSpanningForest();
    // cout << G.dumpDot("G.dot");
    cout << "owo" << endl;
    cout << SF->dumpDot("SF.dot");
    */

    RBTree RBT;
    RBT.insert_node(0, { { "color", "white" } });
    RBT.insert_node(1, { { "color", "white" } });
    RBT.insert_node(2, { { "color", "white" } });
    RBT.insert_node(3, { { "color", "white" } });
    RBT.insert_node(4, { { "color", "white" } });
    RBT.insert_node(5, { { "color", "white" } });

    cout << RBT.dumpDot() << endl;
    return 0;
}
